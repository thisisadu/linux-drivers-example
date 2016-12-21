/***
    dm9000a driver from scratch
*/
#include <linux/init.h>
#include <linux/module.h>

static int __devinit dm9000_probe(struct platform_device *pdev)
{
}

static int __devexit dm9000_remove(struct platform_device *pdev)
{
}

static struct platform_driver dm9000_driver = {
	.driver	= {
		.name    = "dm9000",
		.owner	 = THIS_MODULE,
		//.pm	 = &dm9000_drv_pm_ops,
	},
	.probe   = dm9000_probe,
	.remove  = __devexit_p(dm9000_remove),
};

static int __init dm9000_init(void)
{
  printk("Hello Kernel World!");
  return 0;
}
module_init(dm9000_init);

static void __exit dm9000_exit(void)
{
  printk("Byebye Kernel World!");
}
module_exit(dm9000_exit);

MODULE_AUTHOR("duyahui <877904574@qq.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("a simple net driver");
