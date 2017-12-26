/*
  Code set up to find the whether the task or process the user has input is currently running.
  All writen on the kernel.
  To access kernel readings (on separate terminal):
  >tail -f /var/log/kern.log
  To initialize the findTask code:
  >sudo insmod findTask.ko name=INPUT
  To finalize the findTask code:
  >sudo rmmod findTask
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_PARAM_DESC(name, "To display in /var/log/kern.log");

static char *name = "world"; //default if there is no input

static int __init findTask_init(void) {
  printk(KERN_INFO "Initializing Module \n");
  struct task_struct *task;
  bool check = false;
    for_each_process(task) {
      if(!strcmp(task->comm,name)) {
        printk(KERN_INFO "Found process %s with Process ID %i\n", task->comm, task->pid);
        check = true;
      }
    }
    if(!check) {
      printk(KERN_INFO "Process not found\n");
    }
    return 0;
}

static int __exit findTask_exit(void) {
  printk(KERN_INFO "Exiting Module\n");
}
module_init(findTask_init);
module_exit(findTask_exit);
