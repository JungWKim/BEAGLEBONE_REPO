#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x516e49f9, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xfe990052, "gpio_free" },
	{ 0xbc477a2, "irq_set_irq_type" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0xaf09f062, "gpiod_to_irq" },
	{ 0xa140bc36, "__register_chrdev" },
	{ 0x3e8ff20c, "gpiod_direction_input" },
	{ 0x4e8b35ac, "gpiod_direction_output_raw" },
	{ 0xda575cc, "gpiod_export" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xddc1fca4, "gpiod_set_raw_value" },
	{ 0x395c5ae9, "gpio_to_desc" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x7c32d0f0, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

