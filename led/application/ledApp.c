#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>

#define DEVICE_NAME "/dev/led"

int main(int argc, char** argv)
{
    int fd;
    if((fd= open(DEVICE_NAME, O_RDWR)) < 0)
    {
        perror("[APP] led device driver open error\n");
        return -1;
    }

#ifdef LOOP
    while(1)
    {
    }
#else
    for(int i = 0; i<3; i++)
    {
        ioctl(fd, 0, 1);
        sleep(1);

        ioctl(fd, 0, 0);
        sleep(1);
    }
#endif

    close(fd);
    return 0;
}
