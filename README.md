# little-penguin

This project is based on the Eudyptula challenge which is a series of programming exercises for the Linux Kernel.

## 0

Todo :
* Download Linus's latest git tree from git.kernel.org, build it, install it and boot it.  CONFIG_LOCALVERSION_AUTO must be set to y.

Turn in :
* Kernel boot log.
* Kernel config.

## 1

Todo :
* Build a "Hello World module" that print "Hello World !" when inserted and "Cleaning up module." when removed.

Turn in:
* Makefile and source code.

## 2

Todo :
* Take the kernel git tree from assignment 00 and change the Makefile to modify the EXTRAVERSION field by adding "-thor_kernel" in the version string.

Turn in :
* Kernel boot log.
* A patch to the original Makefile compliant with linux standards.

## 3

Todo :
* Take the given file and rewrite it to match the Linux coding style.

Turn in :
* The cleaned code.

## 4

Todo :
* Take the kernel module from task 01 and modify it so that when any USB keyboard is plugged in the module will be automatically loaded by the correct userspace hotplug tools.

Turn in :
* The source code.
* The rules files.
* Some proof it works.

## 5

Todo :
* Take the kernel module from task 01 and modify it to be a misc char device driver.
* The misc device should be created with a dynamic minor number.
* The misc device should implement the read and write functions.
* The misc device node should show up in /dev/fortytwo.
* When the character device node is read from, your student login is returned to the caller.
* When the character device node is written to, the data sent to the kernel needs to be checked. If it matches your assigned student login, then return a correct write return value. If the value does not match your assigned student login, return the "invalid value" error value.
* The misc device should be registered when your module is loaded, and unregistered when it is unloaded.

Turn in :
* The source code.
* Some proof it works.

## 6

Todo :
* Download the linux-next kernel for today. Build it. Boot it.

Turn in :
* Kernel boot log.

## 7

Todo :
* Take the kernel module from task 01 and modify it to be create a debugfs subdirectory called "fortytwo". In that directory, create 3 virtual files called "id", "jiffies", and "foo".
* The file "id" operates just like it did for assignment 05. The file must be readable and writable by any user.
* The file "jiffies" is to be read only by any user, and when read, should return the current value of the jiffies kernel timer.
* The file "foo" needs to be writable only by root, but readable by anyone. When writing to it, the value must be stored, up to one page of data. When read, which can be done by any user, the value stored in it must be returned. Properly handle the fact that someone could be reading from the file while someone else is writing to it.
* When the module is unloaded, all of the debugfs files are cleaned up, and any memory allocated is freed.

Turn in :
* The source code.
* Some proof it works

## 8

Todo :
* Take the file, fix the coding style, and fix the behaviour of the code.

Turn in :
* The cleaned code.

## 9

Todo :
* Create a module that can list mount points on your system, with the associated
name.
* The file must be named /proc/mymounts

Turn in :
* The module code, with a Makefile
