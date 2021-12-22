#ifndef _SERIAL_PORT_HPP
#define _SERIAL_PORT_HPP

#include <sys/time.h>

class serial_port
{
private:
    int serial_fd;
    struct timeval timeout;

public:
    serial_port(const char *com, int baudrate);

    int send(const char *buf, int len);

    int recv(char *buf, int len);

    void set_timeout(int timeout_sec, int timeout_usec);

    ~serial_port();
};

#endif // !_SERIAL_H