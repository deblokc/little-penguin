// SPDX-License-Identifier: GPL-2.0+
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

/* 
 * That was a long sleep, tell userspace about it 
 */

static int do_work(int *my_int)
{
	int i = 0;
	int value = *my_int;

	for (i = 0; i < *my_int; ++i)
		udelay(10);
	if (value < 10)
		pr_info("We slept a long time!");
	return i * value;
}

static int my_init(void)
{
	int my_int = 10;

	return do_work(&my_int);
}

static void my_exit(void)
{
}

module_init(my_init);
module_exit(my_exit);
