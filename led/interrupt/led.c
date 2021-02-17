#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/interrupt.h>

#define MAJOR_NUMBER 100
#define GPIO_OUT_PIN 67
#define GPIO_IN_PIN 44
#define GPIO_DEBOUNCE_TIME 100
#define DEVICE_NAME "led"
#define LED_CLEAR 0
#define LED_SET 1

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KJW");
MODULE_DESCRIPTION("led control interrupt");

int gpio_irq_num = 0;
char toggle = 1;

int led_open(struct inode *inode, struct file *filp)
{
    printk("[DEV] led_open() major: %d, minor: %d\n", MAJOR(inode->i_rdev), MINOR(inode->i_rdev));
    return 0;
}

int led_release(struct inode *inode, struct file *filp)
{
    printk("[DEV] led_release()\n");
    return 0;
}

long led_unlocked_ioctl(struct file *filp, unsigned int command, unsigned long argument)
{
    if(command == 0)
    {
        if(argument == 0)
        {
            gpio_set_value(GPIO_OUT_PIN, 0);
            printk("[DEV] led_ioctl() argument: %ld\n", argument);
        }
        else
        {
            gpio_set_value(GPIO_OUT_PIN, 1);
            printk("[DEV] led_ioctl() argument: %ld\n", argument);
        }
    }
    else
    {
        printk("[DEV] led_ioctl() error\n");
    }
    return 0;
}

irqreturn_t irq_gpio(int irq, void *ident)
{
    printk("[DEV] interrupted by GPIO44\n");
    if(toggle)
    {
        toggle = !toggle;
        gpio_set_value(GPIO_OUT_PIN, 1);
        printk("[DEV] 1\n");
    }
    else
    {
        toggle = !toggle;
        gpio_set_value(GPIO_OUT_PIN, 0);
        printk("[DEV] 0\n");
    }
    return IRQ_HANDLED;
}

struct file_operations led_fops = {
    .open = led_open,
    .unlocked_ioctl = led_unlocked_ioctl,
    .release = led_release
};

static int led_init(void)
{
    printk("[DEV] led module init\n");

    if(gpio_request(GPIO_OUT_PIN, "LED_OUT") < 0)
        printk("[DEV] out_pin request error\n");

    if(gpio_request(GPIO_IN_PIN, "LED_IN") < 0)
        printk("[DEV] in_pin request error\n");

    if(gpio_export(GPIO_OUT_PIN, 1) < 0)
        printk("[DEV] out_pin export error\n");

    if(gpio_export(GPIO_IN_PIN, 1) < 0)
        printk("[DEV] in_pin export error\n");

    if(gpio_direction_output(GPIO_OUT_PIN, 1) != 0)
        printk("[DEV] out_pin direction error\n");

    if(gpio_direction_input(GPIO_IN_PIN) != 0)
        printk("[DEV] in_pin direction error\n");

    if(register_chrdev(MAJOR_NUMBER, DEVICE_NAME, &led_fops) < 0)
    {
        printk("[DEV] led initialization failed\n");
        return -1;
    }

    //gpio_set_debounce(GPIO_IN_PIN, GPIO_DEBOUNCE_TIME);

    gpio_irq_num = gpio_to_irq(GPIO_IN_PIN);
    if(request_irq(gpio_irq_num, irq_gpio, 0, "gpio44", NULL) < 0)
        printk("[DEV] request irq error\n");

    irq_set_irq_type(gpio_irq_num, IRQ_TYPE_EDGE_RISING);

    printk("[DEV] LED initialization success\n");
    return 0;
}

static void led_exit(void)
{
    printk("[DEV] led module exit\n");
    gpio_free(GPIO_OUT_PIN);
    gpio_free(GPIO_IN_PIN);
    free_irq(gpio_irq_num, NULL);
    unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME);
    return;
}

module_init(led_init);
module_exit(led_exit);
