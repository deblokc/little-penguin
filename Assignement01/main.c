// SPDX-License-Identifier: GPL-2.0+
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("tnaton");
MODULE_DESCRIPTION("A simple hello world");

static int init_hello_world(void)
{
	pr_info("Hello world !\n");
	return 0;
}

static void cleanup_hello_world(void)
{
	pr_info("Cleaning up module.\n");
}

module_init(init_hello_world);
module_exit(cleanup_hello_world);
