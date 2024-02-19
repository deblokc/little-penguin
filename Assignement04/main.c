// SPDX-License-Identifier: GPL-2.0+
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/hid.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("tnaton");
MODULE_DESCRIPTION("A simple hello world when a keyboard is connected");

/*
 * USB_INTERFACE_INFO create a usb_device_id
 *
 * USB_INTERFACE_CLASS_HID is a class for Human Interface Device (such as keyboard)
 * USB_INTERFACE_SUBCLASS_BOOT idk its like the only possible argument ?????
 * USB_INTERFACE_PROTOCOL_KEYBOARD is because we want a keyboard
 */

static int my_probe(struct usb_interface *in, const struct usb_device_id *id)
{
	pr_info("Got a probe\n");
	return 0;
}

static void my_disconnect(struct usb_interface *in)
{
	pr_info("Adios probe\n");
}

static const struct usb_device_id id_table[] = {
	{
		USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
				USB_INTERFACE_SUBCLASS_BOOT,
				USB_INTERFACE_PROTOCOL_KEYBOARD)
	},
	{}
};

MODULE_DEVICE_TABLE(usb, id_table);

static struct usb_driver my_driver = {
	.name = "my_driver",
	.id_table = id_table,
	.probe = my_probe,
	.disconnect = my_disconnect,
};

static int init_hello_world(void)
{
	pr_info("Hello world !\n");
	return usb_register(&my_driver);
}

static void cleanup_hello_world(void)
{
	pr_info("Cleaning up module.\n");
	usb_deregister(&my_driver);
}

module_init(init_hello_world);
module_exit(cleanup_hello_world);
