#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/gpio.h>
#include <linux/types.h>

#define MAJOR_NUMBER 240
#define DEVICE_NAME "led"
#define GPIO_OUT_PIN 67
#define LED_CLEAR 0
#define LED_SET 1

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KJW");
MODULE_DESCRIPTION("led control module");

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

ssize_t led_unlocked_ioctl(struct file *file, unsigned int command, unsigned long argument)
{
	switch(command)
	{
	case 0:
		if(argument == 0)
		{
			gpio_set_value(GPIO_OUT_PIN, 0);
			printk("[DEV] led_ioctl() command: %d, argument: %lf\n", command, argument);
		}
		break;

	default:
		printk("[DEV] led_ioctl() error\n");
		break;
	}
	return 0;
}	

struct file_operations led_fops = {
	.open = led_open,
	.release = led_release,
	.unlocked_ioctl = .led_unlocked_ioctl
};

int led_init(void)
{
	if(gpio_request(GPIO_OUT_PIN, "LED_TEST") < 0)
		printk("[DEV] request error\n");

	if(gpio_export(GPIO_OUT_PIN, 1) < 0)
		printk("[DEV] export error\n");

	//use gpio_direction_output() instead of gpio_set_value()
	if(gpio_direction_output(GPIO_OUT_PIN, 1) != 0)
		printk("[DEV] direction error\n");

	if(register_chrdev(MAJOR_NUMBER, DEVICE_NAME, &led_fops) < 0)
	{
		printk("[DEV] LEd initialization failed\n");
		return -1;
	}
	else
	{
		printk("[DEV] LED initialization success\n");
		return 0;
	}
}

int led_exit(void)
{
	printk("[DEV] LED module closed\n");
	gpio_free(GPIO_OUT_PIN);
	unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME);
	return 0;
}

module_init(led_init);
module_exit(led_exit);
