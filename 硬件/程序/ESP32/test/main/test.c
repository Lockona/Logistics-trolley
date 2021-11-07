/* BSD Socket API Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "driver/uart.h"
#include "driver/i2c.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "sdkconfig.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "driver/twai.h"

/* --------------------- Definitions and static variables ------------------ */

//Example Configurations
#define NO_OF_MSGS 100
#define NO_OF_ITERS 3
#define TX_GPIO_NUM 5
#define RX_GPIO_NUM 4
#define TX_TASK_PRIO 8   //Sending task priority
#define RX_TASK_PRIO 9   //Receiving task priority
#define CTRL_TSK_PRIO 10 //Control task priority
#define MSG_ID 0x0F6     //11 bit standard format ID
#define EXAMPLE_TAG "TWAI Self Test"

static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
//Filter all other IDs except MSG_ID
static const twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
//Set to NO_ACK mode due to self testing with single module
static const twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(TX_GPIO_NUM, RX_GPIO_NUM, TWAI_MODE_NORMAL);

#define PORT 5000
#define KEEPALIVE_IDLE 60
#define KEEPALIVE_INTERVAL 5
#define KEEPALIVE_COUNT 5
#define buffer_size 1024 * 2
#define uart_num UART_NUM_0
#define WIFI_SSID "ESP32_CAR"
#define WIFI_PASSW "12345678"

static const char *TAG = "example";
struct car_message
{
    char type;
    char msg[8];
};
struct car_message move_msg = {.type = 'M'};
struct car_message heading_msg = {.type = 'A'};

struct position_pid
{
    float KP;
    float KI;
    float KD;
    float old_error;
    float new_error;
    float sum_error;
};

struct position_pid angle_pid = {26, 0.14, 0, 0, 0, 0};

int16_t move_heading_flag = 1;
float real_angle = 0, expect_angle = 0;
static i2c_port_t i2c_port_num = I2C_NUM_0;

// static QueueHandle_t gpio_evt_queue = NULL;
static QueueHandle_t uart0_queue;
static QueueHandle_t angle_queue;
static SemaphoreHandle_t angle_update_sem = NULL;
static SemaphoreHandle_t move_msg_send_sem = NULL;
static SemaphoreHandle_t heading_msg_send_sem = NULL;
static SemaphoreHandle_t twai_send_mux = NULL;
static SemaphoreHandle_t client_ready_sem = NULL;
static int accept_sock;
char rx_buffer[8];
uint8_t start_flag = 0;

static void do_retransmit(const int sock)
{
    int len;
    int16_t val_int = 0;
    float val_f = 0.0f;
    char *p;
    while (1)
    {
        len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
        if (len < 0)
        {
            // ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
        }
        else if (len == 0)
        {
            ESP_LOGW(TAG, "Connection closed");
        }
        else
        {
            p = strchr(&rx_buffer[1], '\r');
            if (p)
            {
                *(p) = '\0';
            }
            switch (rx_buffer[0])
            {
            case 'M':
                val_int = atoi(&rx_buffer[1]);
                move_heading_flag = (val_int >= 0) ? 1 : -1;
                start_flag = (val_int != 0) ? 1 : 0;
                if (!start_flag)
                {
                    angle_pid.new_error = 0;
                    angle_pid.old_error = 0;
                    angle_pid.sum_error = 0;
                }
                strcpy(move_msg.msg, &rx_buffer[1]);
                xSemaphoreGive(move_msg_send_sem);
                break;
            case 'A':
                val_f = atof(&rx_buffer[1]);
                xQueueSend(angle_queue, &val_f, 0);
                break;
            case 'P':
                val_int = atoi(&rx_buffer[1]);
                angle_pid.KP = val_int;
                break;
            case 'I':
                val_f = atof(&rx_buffer[1]);
                angle_pid.KI = val_f;
                break;
            case 'D':
                val_int = atoi(&rx_buffer[1]);
                angle_pid.KD = val_int;
                break;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

static void tcp_server_task(void *pvParameters)
{
    char addr_str[128];
    int addr_family = (int)pvParameters;
    int ip_protocol = 0;
    int keepAlive = 1;
    int keepIdle = KEEPALIVE_IDLE;
    int keepInterval = KEEPALIVE_INTERVAL;
    int keepCount = KEEPALIVE_COUNT;
    struct sockaddr_storage dest_addr;

    if (addr_family == AF_INET)
    {
        struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
        dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
        dest_addr_ip4->sin_family = AF_INET;
        dest_addr_ip4->sin_port = htons(PORT);
        ip_protocol = IPPROTO_IP;
    }

    int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
    if (listen_sock < 0)
    {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        vTaskDelete(NULL);
        return;
    }
    int opt = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    ESP_LOGI(TAG, "Socket created");

    int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err != 0)
    {
        ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        ESP_LOGE(TAG, "IPPROTO: %d", addr_family);
        goto CLEAN_UP;
    }
    ESP_LOGI(TAG, "Socket bound, port %d", PORT);

    err = listen(listen_sock, 1);
    if (err != 0)
    {
        ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
        goto CLEAN_UP;
    }

    while (1)
    {

        ESP_LOGI(TAG, "Socket listening");

        struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
        socklen_t addr_len = sizeof(source_addr);
        accept_sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);
        if (accept_sock < 0)
        {
            ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
            break;
        }

        // Set tcp keepalive option
        setsockopt(accept_sock, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(int));
        setsockopt(accept_sock, IPPROTO_TCP, TCP_KEEPIDLE, &keepIdle, sizeof(int));
        setsockopt(accept_sock, IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(int));
        setsockopt(accept_sock, IPPROTO_TCP, TCP_KEEPCNT, &keepCount, sizeof(int));
        // Convert ip address to string
        if (source_addr.ss_family == PF_INET)
        {
            inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addr_str, sizeof(addr_str) - 1);
        }

        ESP_LOGI(TAG, "Socket accepted ip address: %s", addr_str);
        xSemaphoreGive(client_ready_sem);
        do_retransmit(accept_sock);

        shutdown(accept_sock, 0);
        close(accept_sock);
    }

CLEAN_UP:
    close(listen_sock);
    vTaskDelete(NULL);
}

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED)
    {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
        ESP_LOGI(TAG, "station " MACSTR " join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
    else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)
    {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *)event_data;
        ESP_LOGI(TAG, "station " MACSTR " leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}

void wifi_init_softap(void)
{
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = WIFI_SSID,
            .ssid_len = strlen(WIFI_SSID),
            .password = WIFI_PASSW,
            .max_connection = 5,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK},
    };
    if (strlen(WIFI_PASSW) == 0)
    {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    // ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
    //          EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS, EXAMPLE_ESP_WIFI_CHANNEL);
}
static void uart_event_task(void *param)
{
    uart_event_t event;
    char *p = NULL;
    int16_t val_int = 0;
    float val_f = 0.0f;
    char *dtemp = (char *)malloc(buffer_size);
    for (;;)
    {
        if (xQueueReceive(uart0_queue, (void *)&event, (portTickType)portMAX_DELAY))
        {
            bzero(dtemp, buffer_size);
            switch (event.type)
            {
            //Event of UART receving data
            /*We'd better handler data event fast, there would be much more data events than
                other types of events. If we take too much time on data event, the queue might
                be full.*/
            case UART_DATA:
                uart_read_bytes(uart_num, dtemp, event.size, portMAX_DELAY);
                p = strchr(&dtemp[1], '\r');
                if (p)
                {
                    *(p) = '\0';
                }
                val_int = atoi(&dtemp[1]);
                switch (dtemp[0])
                {
                case 'M':
                    move_heading_flag = (val_int >= 0) ? 1 : -1;
                    start_flag = (val_int != 0) ? 1 : 0;
                    if (!start_flag)
                    {
                        angle_pid.new_error = 0;
                        angle_pid.old_error = 0;
                        angle_pid.sum_error = 0;
                    }
                    strcpy(move_msg.msg, &dtemp[1]);
                    xSemaphoreGive(move_msg_send_sem);
                    break;
                case 'A':
                    xQueueSend(angle_queue, &val_int, 0);
                    break;
                case 'P':
                    angle_pid.KP = val_int;
                    break;
                case 'I':
                    val_f = atof(&dtemp[1]);
                    angle_pid.KI = val_f;
                    break;
                case 'D':
                    angle_pid.KD = val_int;
                    break;
                }
                break;
            //Event of HW FIFO overflow detected
            case UART_FIFO_OVF:
                // If fifo overflow happened, you should consider adding flow control for your application.
                // The ISR has already reset the rx FIFO,
                // As an example, we directly flush the rx buffer here in order to read more data.
                uart_flush_input(uart_num);
                xQueueReset(uart0_queue);
                break;
            //Event of UART ring buffer full
            case UART_BUFFER_FULL:
                // If buffer full happened, you should consider encreasing your buffer size
                // As an example, we directly flush the rx buffer here in order to read more data.
                uart_flush_input(uart_num);
                xQueueReset(uart0_queue);
                break;
            //Event of UART RX break detected
            case UART_BREAK:
                break;
            //Event of UART parity check error
            case UART_PARITY_ERR:
                break;
            //Event of UART frame error
            case UART_FRAME_ERR:
                break;
            //UART_PATTERN_DET
            case UART_PATTERN_DET:
                // uart_get_buffered_data[]en(uart_num, &buffer_size);
                // int pos = uart_pattern_pop_pos(uart_num);
                // if (pos == -1)
                // {
                //     // There used to be a UART_PATTERN_DET event, but the pattern position queue is full so that it can not
                //     // record the position. We should set a larger queue size.
                //     // As an example, we directly flush the rx buffer here.
                //     uart_flush_input(uart_num);
                // }
                // else
                // {
                //     uart_read_bytes(uart_num, dtemp, pos, 100 / portTICK_PERIOD_MS);
                //     uint8_t pat[PATTERN_CHR_NUM + 1];
                //     memset(pat, 0, sizeof(pat));
                //     uart_read_bytes(uart_num, pat, PATTERN_CHR_NUM, 100 / portTICK_PERIOD_MS);
                // }
                break;
            //Others
            default:
                printf("uart event type: %d", event.type);
                break;
            }
        }
    }
    free(dtemp);
    dtemp = NULL;
    vTaskDelete(NULL);
}
void move_msg_send_task(void *param)
{
    static twai_message_t tx_msg = {.identifier = 0x0, .data_length_code = 0, .data = {0, 0, 0, 0, 0, 0, 0, 0}};
    while (1)
    {
        if (pdTRUE == xSemaphoreTake(move_msg_send_sem, portMAX_DELAY))
        {
            tx_msg.data_length_code = strlen(move_msg.msg);
            tx_msg.identifier = move_msg.type;
            strcpy((char *)(tx_msg.data), move_msg.msg);
            if (tx_msg.data_length_code < 8 && (tx_msg.data_length_code > 0))
            {
                if (pdTRUE == xSemaphoreTake(twai_send_mux, portMAX_DELAY))
                {
                    twai_transmit(&tx_msg, pdMS_TO_TICKS(50));
                    xSemaphoreGive(twai_send_mux);
                }
            }
        }
    }
}
void heading_msg_send_task(void *param)
{
    static twai_message_t tx_msg = {.identifier = 0x0, .data_length_code = 0, .data = {0, 0, 0, 0, 0, 0, 0, 0}};
    while (1)
    {
        if (pdTRUE == xSemaphoreTake(heading_msg_send_sem, portMAX_DELAY))
        {
            tx_msg.data_length_code = strlen(heading_msg.msg);
            tx_msg.identifier = heading_msg.type;
            strcpy((char *)(tx_msg.data), heading_msg.msg);
            if (tx_msg.data_length_code < 8 && (tx_msg.data_length_code > 0))
            {
                if (pdTRUE == xSemaphoreTake(twai_send_mux, portMAX_DELAY))
                {
                    twai_transmit(&tx_msg, pdMS_TO_TICKS(50));
                    xSemaphoreGive(twai_send_mux);
                }
            }
        }
    }
}

static void twai_receive_task(void *arg)
{
    while (1)
    {
        //Receive data messages from slave
        twai_message_t rx_msg;
        if (pdTRUE == twai_receive(&rx_msg, pdMS_TO_TICKS(200)))
        {
            if (rx_msg.identifier == 0x50)
            {
                uint32_t data = 0;
                for (int i = 0; i < rx_msg.data_length_code; i++)
                {
                    data |= (rx_msg.data[i] << (i * 8));
                }
                ESP_LOGI(EXAMPLE_TAG, "Received data value %d", data);
            }
        }
    }
    vTaskDelete(NULL);
}

static void jy901s_read_task(void *pvParameters)
{
    uint8_t data[32];
    i2c_cmd_handle_t cmd;
    char buffer[32];
    int ret = 0, i = 0;
    float AX = 0, AY = 0, AZ = 0, GX = 0, GY = 0, GZ = 0, HX = 0, HY = 0;
    float H = 0, RX = 0, RY = 0, RZ = 0;
    xSemaphoreTake(client_ready_sem, portMAX_DELAY);
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, 0x50 << 1, 1);
    i2c_master_write_byte(cmd, 0x34, 1);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (0x50 << 1) + 1, 1);
    i2c_master_read(cmd, data, 24, 2);
    // i2c_master_read_byte(cmd, &data[5], 1);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(i2c_port_num, cmd, 200 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret == 0)
    {
        expect_angle = (float)(signed short)(data[23] << 8 | data[22]) / 32768 * 180;
    }
    while (1)
    {
        cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, 0x50 << 1, 1);
        i2c_master_write_byte(cmd, 0x34, 1);
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (0x50 << 1) + 1, 1);
        i2c_master_read(cmd, data, 24, 2);
        // i2c_master_read_byte(cmd, &data[5], 1);
        i2c_master_stop(cmd);
        ret = i2c_master_cmd_begin(i2c_port_num, cmd, 200 / portTICK_RATE_MS);
        i2c_cmd_link_delete(cmd);
        if (ret == 0)
        {
            // AX = (float)(signed short)(data[1] << 8 | data[0]) / 32768 * 16;
            // AY = (float)(signed short)(data[3] << 8 | data[2]) / 32768 * 16;
            // AZ = (float)(signed short)(data[5] << 8 | data[4]) / 32768 * 16;
            // GX = (float)(signed short)(data[7] << 8 | data[6]) / 32768 * 2000;
            // GY = (float)(signed short)(data[9] << 8 | data[8]) / 32768 * 2000;
            // GZ = (float)(signed short)(data[11] << 8 | data[10]) / 32768 * 2000;
            // HX = (float)(data[13] << 8 | data[12]);
            // HY = (float)(data[15] << 8 | data[14]);
            // H = (float)(data[17] << 8 | data[16]);
            RX = (float)(signed short)(data[19] << 8 | data[18]) / 32768 * 180;
            RY = (float)(signed short)(data[21] << 8 | data[20]) / 32768 * 180;
            RZ = (float)(signed short)(data[23] << 8 | data[22]) / 32768 * 180;
            i++;
            if (i == 3)
            {
                i = 0;
                sprintf((char *)buffer, "\r\nRX=%.2f,RY=%.2f,RZ=%.2f", RX, RY, RZ);
                int len = strlen(buffer) + 1;
                int to_write = len;
                if (accept_sock > 0)
                {
                    while (to_write > 0)
                    {
                        int written = send(accept_sock, buffer + (len - to_write), to_write, 0);
                        if (written < 0)
                        {
                            break;
                        }
                        to_write -= written;
                    }
                    //uart_write_bytes(uart_num, buffer, strlen(buffer));
                }
            }
            if (start_flag)
            {
                real_angle = RZ;
                xSemaphoreGive(angle_update_sem);
            }
            // sprintf((char *)buffer, "\r\nAX = %.3f,AY = %.3f,AZ = %.3f,", AX, AY, AZ);
            // uart_write_bytes(uart_num, buffer, strlen(buffer));
            // sprintf((char *)buffer, "\r\nGX = %.3f,GY = %.3f,GZ = %.3f,", GX, GY, GZ);
            // uart_write_bytes(uart_num, buffer, strlen(buffer));
            // sprintf((char *)buffer, "\r\nHX = %.3f,HY = %.3f,HZ = %.3f,", HX, HY, H);
            // uart_write_bytes(uart_num, buffer, strlen(buffer));
        }
        vTaskDelay(pdMS_TO_TICKS(40));
    }
    vTaskDelete(NULL);
}

static void angle_pid_ctrl_task(void *pvParameters)
{
    int8_t angle_flag = -1;
    int16_t pwm = 0;
    float err = 0, sum_error;
    float last_angle = 0;
    while (1)
    {
        xQueueReceive(angle_queue, &expect_angle, 0);
        if (xSemaphoreTake(angle_update_sem, portMAX_DELAY) == pdTRUE)
        {
            if (expect_angle >= 0)
            {
                angle_flag = ((real_angle > (expect_angle - 180)) && (real_angle < 180)) ? (-1 * move_heading_flag) : (move_heading_flag);
            }
            else
            {
                angle_flag = ((real_angle > -180) && (real_angle < (expect_angle + 180))) ? (-1 * move_heading_flag) : (move_heading_flag);
            }
            angle_pid.new_error = expect_angle - real_angle;
            if ((angle_pid.new_error >= -0.5) && (angle_pid.new_error <= 0.5))
            {
                angle_pid.new_error = 0;
            }
            // err = angle_pid.new_error - angle_pid.old_error;
            err = real_angle - last_angle;
            last_angle = real_angle;
            angle_pid.sum_error += angle_pid.new_error;
            sum_error = angle_pid.sum_error;
            pwm = (int)(angle_pid.KP * angle_pid.new_error + angle_pid.KI * sum_error + angle_pid.KD * err) * angle_flag;
            if (pwm < -1000)
            {
                pwm = -1000;
            }
            else if (pwm > 1000)
            {
                pwm = 1000;
            }
            angle_pid.old_error = angle_pid.new_error;
            sprintf(heading_msg.msg, "%d", 1500 + pwm);
            xSemaphoreGive(heading_msg_send_sem);
        }
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    wifi_init_softap();
    //Install TWAI driver
    ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, &f_config));
    ESP_ERROR_CHECK(twai_start());
    xTaskCreatePinnedToCore(twai_receive_task, "TWAI_rx", 4096 * 2, NULL, RX_TASK_PRIO, NULL, tskNO_AFFINITY);

    uart_config_t uart_config =
        {
            .baud_rate = 115200,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
            .source_clk = UART_SCLK_APB,
        };
    uart_driver_install(uart_num, buffer_size, buffer_size, 10, &uart0_queue, 0);
    uart_param_config(uart_num, &uart_config);
    uart_set_pin(uart_num, 21, 20, -1, -1);
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = 19,
        .scl_io_num = 18,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000,
    };
    i2c_param_config(i2c_port_num, &i2c_config);
    ESP_ERROR_CHECK(i2c_driver_install(i2c_port_num, i2c_config.mode, 0, 0, 0));

    angle_queue = xQueueCreate(10, sizeof(float));

    move_msg_send_sem = xSemaphoreCreateBinary();
    heading_msg_send_sem = xSemaphoreCreateBinary();
    angle_update_sem = xSemaphoreCreateBinary();
    twai_send_mux = xSemaphoreCreateMutex();
    client_ready_sem = xSemaphoreCreateBinary();

    //Create tasks and synchronization primitives

    ESP_LOGI(EXAMPLE_TAG, "Driver installed");
    xTaskCreate(move_msg_send_task, "move_msg_send_task", 1024 * 5, NULL, 8, NULL);
    xTaskCreate(heading_msg_send_task, "heading_msg_send_task", 1024 * 5, NULL, 8, NULL);
    xTaskCreate(uart_event_task, "uart-event", 1024 * 2, NULL, 12, NULL);
    xTaskCreate(tcp_server_task, "tcp_server", 4096, (void *)AF_INET, 5, NULL);
    xTaskCreate(jy901s_read_task, "jy901s_read", 1024 * 5, NULL, 6, NULL);
    xTaskCreate(angle_pid_ctrl_task, "angle_pid_ctrl", 4096, NULL, 7, NULL);
    uart_write_bytes(uart_num, "start!!!\r\n", strlen("start!!!\r\n"));
    // vTaskStartScheduler();
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
