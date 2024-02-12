// SPDX-License-Identifier: GPL-2.0+
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/nsproxy.h>
#include <linux/mount.h>
#include <linux/mnt_namespace.h>
#include <linux/list.h>
#include "../linux/fs/mount.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("tnaton");
MODULE_DESCRIPTION("A simple mounts proc file");

static struct proc_dir_entry *entry;

static int mymount_show(struct seq_file *m, void *p)
{
	struct mount *mnt;
//	current->nsproxy->mnt_ns->list;
	list_for_each_entry(mnt, &current->nsproxy->mnt_ns->list, mnt_list)
		seq_printf(m, "test\n");
	return 0;
}

static int mymount_open(struct inode *inode, struct file *file)
{
	return single_open(file, &mymount_show, NULL);
}

static const struct file_operations mymount_file_ops = {
	.owner = THIS_MODULE,
	.open = mymount_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int init_mymounts(void)
{
	pr_info("Creating /proc/mymounts\n");
	entry = proc_create("mymounts", 0644, NULL, &mymount_file_ops);
	if (!entry)
		return -ENOMEM;
	return 0;
}

static void cleanup_mymounts(void)
{
	pr_info("Cleaning up /proc/mymounts\n");
}

module_init(init_mymounts);
module_exit(cleanup_mymounts);
