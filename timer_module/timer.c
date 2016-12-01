/**
   usage:
   sudo dmesg -c
   sudo insmod timer.ko
   sudo dmesg -T //you can see the log every two seconds until the module is removed
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/timer.h>

static struct timer_list my_timer;

static void timer_func(unsigned long data)
{
  printk("<3>you can see me every two seconds\n");

  mod_timer(&my_timer,jiffies + 2*HZ);
}

static int __init timer_init(void)
{
  printk("<3>timer come into the kernel\n");

  init_timer(&my_timer);
  my_timer.expires = jiffies + 2 * HZ;
  my_timer.function = timer_func;
  my_timer.data = 0;

  add_timer(&my_timer);
  return 0;
}
module_init(timer_init);

static void __exit timer_exit(void)
{
  del_timer(&my_timer);
  printk("<3>timer leave the kernel\n");
}
module_exit(timer_exit);
