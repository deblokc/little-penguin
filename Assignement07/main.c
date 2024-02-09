// SPDX-License-Identifier: GPL-2.0+
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/debugfs.h>
#include <linux/string.h>

#define LOGIN     "tnaton"
#define LOGIN_LEN 6

MODULE_LICENSE("GPL");
MODULE_AUTHOR("tnaton");
MODULE_DESCRIPTION("A simple debugfs module");

static struct dentry *directory;
static struct dentry *id_file;
//static struct dentry *jiffies_file;
static struct dentry *foo_file;

static ssize_t ft_read_id(struct file *f, char *buf, size_t len, loff_t *offset);
static ssize_t ft_write_id(struct file *f, const char *buf, size_t len, loff_t *offset);

struct file_operations fops_id = {
	.read = ft_read_id,
	.write = ft_write_id,
};

static ssize_t ft_read_id(struct file *f, char *buf, size_t len, loff_t *offset)
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

static ssize_t ft_write_id(struct file *f, const char *buf, size_t len, loff_t *offset)
{
	if (!buf || len != LOGIN_LEN)
		return -EINVAL;
	else if (strncmp(buf, LOGIN, len))
		return -EINVAL;
	return LOGIN_LEN;
}

static ssize_t ft_read_foo(struct file *f, char *buf, size_t len, loff_t *offset);
static ssize_t ft_write_foo(struct file *f, const char *buf, size_t len, loff_t *offset);

struct file_operations fops_foo = {
	.read = ft_read_foo,
	.write = ft_write_foo,
};

static char foo_buf[PAGE_SIZE];
static ssize_t foo_len = 0;

DEFINE_MUTEX(foo_mutex);

static ssize_t ft_read_foo(struct file *f, char *buf, size_t len, loff_t *offset)
{
	int readlen;

	if (!buf)
		return -EINVAL;

	mutex_lock(&foo_mutex);

	if (*offset >= foo_len) {
		mutex_unlock(&foo_mutex);
		return 0;
	} else if (*offset + len > foo_len) {
		readlen = foo_len - *offset;
	} else {
		readlen = len;
	}

	readlen -= copy_to_user(buf, foo_buf, readlen);
	mutex_unlock(&foo_mutex);
	*offset += readlen;
	return readlen;
}

static ssize_t ft_write_foo(struct file *f, const char *buf, size_t len, loff_t *offset)
{
	int writelen;

	if (!buf)
		return -EINVAL;
	else if (*offset >= PAGE_SIZE)
		return -EFBIG;

	mutex_lock(&foo_mutex);

	if (*offset == 0) {
		memset(foo_buf, 0, foo_len);
		foo_len = 0;
	}
	if (*offset + len > PAGE_SIZE)
		writelen = PAGE_SIZE - *offset - 1;
	else
		writelen = len;
	writelen -= copy_from_user(foo_buf, buf, writelen);
	foo_len += writelen;

	mutex_unlock(&foo_mutex);
	*offset += writelen;
	return writelen;
}

static int init_debug_module(void)
{
	pr_info("Hello world !\n");
	directory = debugfs_create_dir("fortytwo", NULL);

	if (IS_ERR(directory)) {
		if (directory == ERR_PTR(-ENODEV))
			pr_warn("Kernel doesnt support debugfs\n");
		return PTR_ERR(directory);
	}

	id_file = debugfs_create_file("id", 0666, directory, NULL, &fops_id);
	if (IS_ERR(id_file))
		return PTR_ERR(id_file);

	debugfs_create_ulong("jiffies", 0444, directory, (unsigned long *)&jiffies);

	foo_file = debugfs_create_file("foo", 0644, directory, NULL, &fops_foo);
	if (IS_ERR(foo_file))
		return PTR_ERR(foo_file);

	mutex_init(&foo_mutex); // can't it fail ??
	return 0;
}

static void cleanup_debug_module(void)
{
	debugfs_remove_recursive(directory);
	pr_info("Cleaning up module.\n");
}

module_init(init_debug_module);
module_exit(cleanup_debug_module);
