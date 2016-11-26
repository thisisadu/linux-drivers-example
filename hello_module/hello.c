/***
    a simple module that just say hello
*/
#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void)
{
  printk("Hello Kernel World!");
  return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
  printk("Byebye Kernel World!");
}
module_exit(hello_exit);

MODULE_AUTHOR("duyahui <877904574@qq.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("a simple module");
