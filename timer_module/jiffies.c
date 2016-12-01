/**
   usage:
   sudo dmesg -c
   sudo insmod jiffies.ko //this will wait about 3 seconds
   sudo dmesg -T //you can see the time interval between [jiffies delay begin] and [jiffies delay end] is about 3 seconds
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>

static int __init jiffies_init(void)
{
  unsigned long timeout = jiffies + 3 * HZ;
  printk("<3>jiffies delay begin\n");
  while(1){
    if(time_after(jiffies,timeout))
      break;
	}
  printk("<3>jiffies delay end\n");
  return 0;
}
module_init(jiffies_init);

static void __exit jiffies_exit(void)
{
  printk("<3>jiffies leave the kernel\n");
}
module_exit(jiffies_exit);
