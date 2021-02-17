#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

//#define GPIO2_BASE        0x44e07000
//#define GPIO2_END         0x44e07fff
#define GPIO2_BASE        0x481ac000
#define GPIO2_END         0x481acfff
#define GPIO_SIZE         (GPIO2_END - GPIO2_BASE)
#define GPIO_DATAOUT      0x13c
#define GPIO_OE           0x134
#define GPIO_CLRDATAOUT   0x190
#define GPIO_SETDATAOUT   0x194
#define GPIO67_TOGGLE     (1<<3)
#define GPIO67_OUT        (0xfffffff & ~(1<<3))

volatile unsigned int *gpio_oe;
volatile unsigned int *gpio_dataout;
volatile unsigned int *gpio_clrdataout;
volatile unsigned int *gpio_setdataout;

int main(int argc, char **argv)
{
    int fd;
    char msg[50];
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        sprintf(msg, "%s %d : ", __FILE__, (__LINE__ - 3));
        perror(msg);
        return -1;
    }

    void *gpio2_base;
    if((gpio2_base = mmap(0, GPIO_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO2_BASE)) < 0)
    {
        sprintf(msg, "%s %d : ", __FILE__, (__LINE__ - 3));
        perror(msg);
        return -1;
    }

    gpio_oe = (volatile unsigned int*)(gpio2_base + GPIO_OE);
    gpio_dataout = (volatile unsigned int*)(gpio2_base + GPIO_DATAOUT);
    gpio_clrdataout = (volatile unsigned int*)(gpio2_base + GPIO_CLRDATAOUT);
    gpio_setdataout = (volatile unsigned int*)(gpio2_base + GPIO_SETDATAOUT);

#ifdef DATAOUT
    *gpio_dataout |= (1<<3);
    printf("dataout defined\n\n");
#else
    *gpio_oe &= GPIO67_OUT;
    printf("dataout not defined\n\n");
#endif

    printf("gpio_oe : %p\n", gpio_oe);
    printf("gpio_dataout : %p\n", gpio_dataout);
    printf("gpio_clrdataout : %p\n", gpio_clrdataout);
    printf("gpio_setdataout : %p\n", gpio_setdataout);

    for(int i = 0; i<3; i++)
    {
        *gpio_setdataout |= GPIO67_TOGGLE;
        sleep(1);
        *gpio_clrdataout |= GPIO67_TOGGLE;
        sleep(1);
    }

    munmap(gpio2_base, GPIO_SIZE);
    close(fd);
    return 0;
}
