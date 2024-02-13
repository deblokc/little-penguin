// SPDX-License-Identifier: GPL-2.0+
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/nsproxy.h>
#include <linux/list.h>
#include <../fs/mount.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("tnaton");
MODULE_DESCRIPTION("A simple mounts proc file");

static struct proc_dir_entry *entry;

static int mymount_show(struct seq_file *m, void *p)
{
	struct mount *tmp;
	struct path  tmp_path;

	list_for_each_entry(tmp, &current->nsproxy->mnt_ns->list, mnt_list) {
		if (!strcmp(tmp->mnt_devname, "rootfs"))
			continue;
		seq_printf(m, "%s ", tmp->mnt_devname);
		tmp_path.mnt = &tmp->mnt;
		tmp_path.dentry = tmp->mnt.mnt_root;
		seq_path(m, &tmp_path, "");
		seq_putc(m, '\n');
	}
	return 0;
}

static int mymount_open(struct inode *inode, struct file *file)
{
	return single_open(file, &mymount_show, NULL);
}

static const struct proc_ops mymount_proc_ops = {
	.proc_open = mymount_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};

static int init_mymounts(void)
{
	pr_info("Creating /proc/mymounts\n");
	entry = proc_create("mymounts", 0644, NULL, &mymount_proc_ops);
	if (!entry)
		return -ENOMEM;
	return 0;
}

static void cleanup_mymounts(void)
{
	remove_proc_entry("mymounts", NULL);
	pr_info("Cleaning up /proc/mymounts\n");
}

module_init(init_mymounts);
module_exit(cleanup_mymounts);
