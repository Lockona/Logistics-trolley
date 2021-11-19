#include "YoloDet.h"
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int fd;
std::vector<unsigned char> buffer;
struct timeval timeout;

static speed_t
getBaudrate(int baudrate)
{
    switch (baudrate)
    {
    case 0:
        return B0;
    case 50:
        return B50;
    case 75:
        return B75;
    case 110:
        return B110;
    case 134:
        return B134;
    case 150:
        return B150;
    case 200:
        return B200;
    case 300:
        return B300;
    case 600:
        return B600;
    case 1200:
        return B1200;
    case 1800:
        return B1800;
    case 2400:
        return B2400;
    case 4800:
        return B4800;
    case 9600:
        return B9600;
    case 19200:
        return B19200;
    case 38400:
        return B38400;
    case 57600:
        return B57600;
    case 115200:
        return B115200;
    case 230400:
        return B230400;
    case 460800:
        return B460800;
    case 500000:
        return B500000;
    case 576000:
        return B576000;
    case 921600:
        return B921600;
    case 1000000:
        return B1000000;
    case 1152000:
        return B1152000;
    case 1500000:
        return B1500000;
    case 2000000:
        return B2000000;
    case 2500000:
        return B2500000;
    case 3000000:
        return B3000000;
    case 3500000:
        return B3500000;
    case 4000000:
        return B4000000;
    default:
        return -1;
    }
}
void *com_read(void *param)
{
    int ret, len;
    fd_set rd;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    char buf[128];
    while (1)
    {
        FD_ZERO(&rd);
        FD_SET(fd, &rd);
        ret = select(fd + 1, &rd, NULL, NULL, &timeout);
        switch (ret)
        {
        case -1:
            printf("error!!!\r\n");
            break;
        case 0:
            break;
        default:
            if (FD_ISSET(fd, &rd))
            {
                if ((len = read(fd, buf, sizeof(buf))) > 0)
                    printf("%s", buf);
            }
            break;
        }
    }
    pthread_exit(0);
}
void *com_input(void *param)
{
    char buf[8];
    while (1)
    {
        bzero(buf, sizeof(buf));
        printf("function:");
        scanf("%s", buf);
        if (strlen(buf) > 0)
        {
            printf("%s", buf);
            write(fd, buf, strlen(buf));
        }
    }
    pthread_exit(NULL);
}
int drawBoxes(cv::Mat srcImg, std::vector<TargetBox> boxes)
{
    printf("Detect box num: %d\n", boxes.size());
    for (int i = 0; i < boxes.size(); i++)
    {
        cv::rectangle(srcImg, cv::Point(boxes[i].x1, boxes[i].y1),
                      cv::Point(boxes[i].x2, boxes[i].y2),
                      cv::Scalar(255, 255, 0), 2, 2, 0);

        std::string cate = std::to_string(boxes[i].cate);
        std::string Ttext = "Category:" + cate;
        cv::Point Tp = cv::Point(boxes[i].x1, boxes[i].y1 - 20);
        cv::putText(srcImg, Ttext, Tp, cv::FONT_HERSHEY_TRIPLEX, 0.5,
                    cv::Scalar(0, 255, 0), 1, CV_AA);

        std::string score = std::to_string(boxes[i].score);
        std::string Stext = "Score:" + score;
        cv::Point Sp = cv::Point(boxes[i].x1, boxes[i].y1 - 5);
        cv::putText(srcImg, Stext, Sp, cv::FONT_HERSHEY_TRIPLEX, 0.5,
                    cv::Scalar(0, 0, 255), 1, CV_AA);
    }
    return 0;
}

void testCam()
{
    YoloDet api;
    //Init model
    api.init("model/yolo-fastest-1.1.param",
             "model/yolo-fastest-1.1.bin");

    cv::Mat frame;
    std::vector<TargetBox> output;

    std::vector<int> param = std::vector<int>(2);
    param[0] = CV_IMWRITE_JPEG_QUALITY;
    param[1] = 95;
    cv::VideoCapture cap(0);

    while (true)
    {
        printf("=========================\n");
        cap >> frame;
        if (frame.empty())
            break; //如果某帧为空则退出循环

        double start = ncnn::get_current_time();
        api.detect(frame, output);
        double end = ncnn::get_current_time();
        double time = end - start;
        printf("Detect Time:%7.2f \n", time);
        // if (output.size() != 0)
        // {
        //     printf("x1:%d,x2:%d,y1:%d,y2:%d \n", output[0].x1, output[0].x2, output[0].y1, output[0].y2);
        //     if ((output[0].y2 - output[0].y1) > 360)
        //     {
        //         printf("M-300\r\n");
        //         write(fd, "M-300\r\n", strlen("M-300\r\n") + 1);
        //     }
        //     else if ((output[0].y2 - output[0].y1) < 200)
        //     {
        //         printf("M300\r\n");
        //         write(fd, "M300\r\n", strlen("M300\r\n") + 1);
        //     }
        //     else
        //     {
        //         printf("M0\r\n");
        //         write(fd, "M0\r\n", strlen("M0\r\n") + 1);
        //     }
        // }
        // else
        // {
        //     printf("M0\r\n");
        //     write(fd, "M0\r\n", strlen("M0\r\n") + 1);
        // }
        drawBoxes(frame, output);
        output.clear();
        if (fd > 0)
        {
            cv::imencode(".jpg", frame, buffer, param);
            // send(fd, &buffer[0], buffer.size(), 0);
            int size = buffer.size();
            int i = 0;
            while ((size - i) >= 1024)
            {
                send(fd, &buffer[i], 1024, 0);
                i += 1024;
            }
            size = size - i;
            if (size > 0)
            {
                send(fd, &buffer[i], size, 0);
            }
        }
        //cv::imshow("demo", frame);
        cv::waitKey(15);
    }

    cap.release(); //释放资源
    //pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    //struct termios old_t, new_t;
    // pthread_t r_pid, w_pid, cam_pid;
    if (argc < 2)
    {
        printf("Usage error!!!\r\n");
        return -1;
    }
    // fd = open(argv[1], O_RDWR | O_NONBLOCK | O_NOCTTY | O_NDELAY);
    // if (fd < 0)
    // {
    //     printf("open error!!!\r\n");
    //     return -1;
    // }
    // speed_t speed = getBaudrate(115200);
    // bzero(&new_t, sizeof(new_t));
    // tcgetattr(fd, &old_t);
    // tcflush(fd, TCIFLUSH);
    // new_t.c_cflag |= speed | CS8 | CLOCAL | CREAD;
    // new_t.c_cflag &= ~CSTOPB;
    // new_t.c_cflag &= ~PARENB;
    // new_t.c_iflag = IGNBRK;
    // new_t.c_oflag = 0;
    // tcsetattr(fd, TCSANOW, &new_t);
    // tcgetattr(fd, &old_t);
    // pthread_create(&r_pid, NULL, com_read, NULL);
    // pthread_create(&w_pid, NULL, com_input, NULL);
    // pthread_create(&cam_pid, NULL, testCam, NULL);
    struct sockaddr_in seraddr;
    int nSendBuf = 150 * 1024;
    memset(&seraddr, 0, sizeof(struct sockaddr));
    fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (const char *)&nSendBuf, sizeof(int));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(atoi(argv[1]));
    seraddr.sin_addr.s_addr = inet_addr("192.168.137.1");
    if (connect(fd, (struct sockaddr *)&seraddr, sizeof(struct sockaddr)) < 0)
    {
        perror("connect\r\n");
        close(fd);
        return -1;
    }
    testCam();
    // pthread_join(r_pid, NULL);
    // pthread_join(w_pid, NULL);
    // pthread_join(cam_pid, NULL);
    return 0;
}
