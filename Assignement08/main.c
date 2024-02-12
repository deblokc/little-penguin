// SPDX-License-Identifier: GPL-2.0+
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Louis Solofrizzo <louis@ne02ptzero.me>");
MODULE_DESCRIPTION("Useless module");

static ssize_t myfd_read(struct file *fp, char __user *user, size_t size, loff_t *offs);
static ssize_t myfd_write(struct file *fp, const char __user *user, size_t size, loff_t *offs);

static struct file_operations myfd_fops = {
	.owner = THIS_MODULE,
	.read = &myfd_read,
	.write = &myfd_write
};

static struct miscdevice myfd_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "reverse",
	.fops = &myfd_fops
};

char str[PAGE_SIZE];
char *tmp;

static int __init myfd_init(void)
{
	int error = misc_register(&myfd_device);
	if (error)
		return error;
	return 0;
}

static void __exit myfd_cleanup(void) {
	misc_deregister(&myfd_device);
}

ssize_t myfd_read(struct file *fp, char __user *user, size_t size, loff_t *offs)
{
	if (strlen(str) == 0)
		return 0;

	int j, i;
	tmp = kmalloc(sizeof(char) * (strlen(str) + 1), GFP_KERNEL);
	if (!tmp)
		return -EINVAL;
	for (i = 0, j = strlen(str) - 1; j >= 0; j--, i++)
		tmp[i] = str[j];
	tmp[i] = '\0';
	return simple_read_from_buffer(user, size, offs, tmp, i);
}

ssize_t myfd_write(struct file *fp, const char __user *user, size_t size, loff_t *offs)
{
	ssize_t ret;
	ret = simple_write_to_buffer(str, PAGE_SIZE - strlen(str), offs, user, size) + 1;
	str[size + 1] = '\0';
	return ret;
}

module_init(myfd_init);
module_exit(myfd_cleanup);
