// SPDX-License-Identifier: GPL-2.0+
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define LOGIN "tnaton"
#define LOGIN_LEN 6

MODULE_LICENSE("GPL");
MODULE_AUTHOR("tnaton");
MODULE_DESCRIPTION("A simple device");

static ssize_t ft_read(struct file *f, char *buf, size_t len, loff_t *offset);
static ssize_t ft_write(struct file *f, const char *buf, size_t len, loff_t *offset);

static const struct file_operations fops = {
	.read = ft_read,
	.write = ft_write,
};

static struct miscdevice device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "fortytwo",
	.fops = &fops,
};

static ssize_t ft_read(struct file *f, char *buf, size_t len, loff_t *offset)
{
	int readlen;

	if (!buf)
		return -EINVAL;
	else if (*offset >= LOGIN_LEN)
		return 0;
	else if (*offset + len > LOGIN_LEN)
		readlen = LOGIN_LEN - *offset;
	else
		readlen = len;
	readlen -= copy_to_user(buf, LOGIN + *offset, readlen);
	*offset += readlen;
	return (readlen);
}

static ssize_t ft_write(struct file *f, const char *buf, size_t len, loff_t *offset)
{
	char tmp[LOGIN_LEN];

	if (!buf || len != LOGIN_LEN)
		return -EINVAL;
	if (strncpy_from_user(tmp, buf, LOGIN_LEN) != LOGIN_LEN)
		return -EFAULT;
	if (strncmp(tmp, LOGIN, LOGIN_LEN))
		return -EINVAL;
	return LOGIN_LEN;
}

static int init_device(void)
{
	pr_info("Registering device\n");
	misc_register(&device);
	return 0;
}

static void cleanup_device(void)
{
	pr_info("Unregistering device\n");
	misc_deregister(&device);
}

module_init(init_device);
module_exit(cleanup_device);
