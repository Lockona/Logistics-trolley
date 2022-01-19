#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

static speed_t getBaudrate(int baudrate)
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

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage fail!!!\n");
        return -1;
    }
    int fd = open("/dev/ttyUSB0", O_RDONLY | O_NOCTTY | O_NONBLOCK | O_NDELAY);
    if (fd < 0)
    {
        perror("USB");
        return -1;
    }
    struct termios old_t, new_t;
    struct timeval timeout;
    speed_t speed = getBaudrate(115200);
    bzero(&new_t, sizeof(new_t));
    tcgetattr(fd, &old_t);
    tcflush(fd, TCIFLUSH);
    new_t.c_cflag = speed | CS8 | CLOCAL | CREAD;
    new_t.c_cflag &= ~CSTOPB;
    new_t.c_cflag &= ~PARENB;
    new_t.c_iflag = IGNBRK;
    new_t.c_oflag = 0;
    tcsetattr(fd, TCSANOW, &new_t);
    tcgetattr(fd, &old_t);
    char buf[64];
    bzero(buf, 64);
    fd_set rd;
    int ret, len = 0;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    while (1)
    {
        FD_ZERO(&rd);
        FD_SET(fd, &rd);
        ret = select(fd + 1, &rd, NULL, NULL, &timeout);
        switch (ret)
        {
        case 0:
            break;
        case -1:
            printf("error!!!\n");
            break;
        default:
            if (FD_ISSET(fd, &rd))
            {
                if ((len = read(fd, buf, 64)) > 0)
                {
                    printf("%s\r\n", buf);
                    system("sudo kill -2 $(pgrep duoji)");
                }
            }
            break;
        }
    }
    close(fd);
    return 0;
}