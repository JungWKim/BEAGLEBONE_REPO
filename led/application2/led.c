#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#define GPIO2_BASE        0x481ac000
#define GPIO2_END         0x481acfff
#define GPIO_SIZE         (GPIO2_END - GPIO2_BASE)
#define GPIO_OE           0x134
#define GPIO_CLRDATAOUT   0x190
#define GPIO_SETDATAOUT   0x194

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

    char *gpio2_base;
    if((gpio2_base = mmap(0, GPIO_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO2_BASE)) < 0)
    {
        sprintf(msg, "%s %d : ", __FILE__, (__LINE__ - 3));
        perror(msg);
        return -1;
    }
    
    volatile unsigned int *gpio_base;
    volatile unsigned int *gpio_oe;
    volatile unsigned int *gpio_clrdataout;
    volatile unsigned int *gpio_setdataout;
    
    gpio_base = (volatile unsigned int*)gpio2_base;
    gpio_oe = gpio_base + (GPIO_OE/4);
    gpio_clrdataout = gpio_base + (GPIO_CLRDATAOUT/4);
    gpio_setdataout = gpio_base + (GPIO_SETDATAOUT/4);

    printf("gpio_oe : %p\n", gpio_oe);
    printf("gpio_clrdataout : %p\n", gpio_clrdataout);
    printf("gpio_setdataout : %p\n", gpio_setdataout);

    *gpio_oe &= ~(1<<3);
    
    for(int i = 0; i<3; i++)
    {
        *gpio_setdataout |= (1<<3);
        sleep(1);
        *gpio_clrdataout |= (1<<3);
        sleep(1);
    }

    munmap(gpio2_base, GPIO_SIZE);
    close(fd);
    return 0;
}
