#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

#include <linux/sched.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/interrupt.h> /* mark_bh */

#include <linux/in.h>
#include <linux/netdevice.h>   /* struct device, and other headers */
#include <linux/etherdevice.h> /* eth_type_trans */
#include <linux/ip.h>          /* struct iphdr */
#include <linux/tcp.h>         /* struct tcphdr */
#include <linux/skbuff.h>
#include <linux/in6.h>
#include <asm/checksum.h>

struct snull_priv {
	struct net_device *dev;
	struct napi_struct napi;
	struct net_device_stats stats;
	int status;
	/* struct snull_packet *ppool; */
	/* struct snull_packet *rx_queue;  /\* List of incoming packets *\/ */
	int rx_int_enabled;
	int tx_packetlen;
	u8 *tx_packetdata;
	struct sk_buff *skb;
	spinlock_t lock;
};

static struct net_device *snull_devs[2];

int snull_open(struct net_device *dev)
{
	return 0;
}

int snull_release(struct net_device *dev)
{
	return 0;
}

int snull_tx(struct sk_buff *skb, struct net_device *dev)
{
	return 0;
}

void snull_tx_timeout (struct net_device *dev)
{
	struct snull_priv *priv = netdev_priv(dev);

	return;
}

int snull_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	return 0;
}

struct net_device_stats *snull_stats(struct net_device *dev)
{
	struct snull_priv *priv = netdev_priv(dev);
	return &priv->stats;
}

int snull_change_mtu(struct net_device *dev, int new_mtu)
{
	unsigned long flags;
	struct snull_priv *priv = netdev_priv(dev);
	spinlock_t *lock = &priv->lock;

	/* check ranges */
	if ((new_mtu < 68) || (new_mtu > 1500))
		return -EINVAL;
	/*
	 * Do anything you need, and the accept the value
	 */
	spin_lock_irqsave(lock, flags);
	dev->mtu = new_mtu;
	spin_unlock_irqrestore(lock, flags);
	return 0; /* success */
}

static const struct net_device_ops snull_netdev_ops = {
	.ndo_open		= snull_open,
	.ndo_stop		= snull_release,
	.ndo_start_xmit		= snull_tx,
	.ndo_do_ioctl		= snull_ioctl,
	.ndo_get_stats		= snull_stats,
	.ndo_change_mtu		= snull_change_mtu,
	.ndo_tx_timeout         = snull_tx_timeout,
};

void snull_init(struct net_device *dev)
{
	struct snull_priv *priv = netdev_priv(dev);

  memset(priv,0,sizeof(struct snull_priv));

  spin_lock_init(&priv->lock);

  priv->dev = dev;

  ether_setup(dev);

  /* dev->watchdog_timeo = timeout; */

  dev->flags |= IFF_NOARP;
  dev->features |= NETIF_F_HW_CSUM;
  dev->netdev_ops = &snull_netdev_ops;

}

void net_deinit(void)
{
  int i;
  for(i=0;i<2;i++){
    if(snull_devs[i]){
      unregister_netdev(snull_devs[i]);
      free_netdev(snull_devs[i]);
    }
  }
}

int net_init(void)
{
  int i,ret = 0;

  snull_devs[0] = alloc_netdev(sizeof(struct snull_priv),"sn%d",NET_NAME_UNKNOWN,snull_init);
  snull_devs[1] = alloc_netdev(sizeof(struct snull_priv),"sn%d",NET_NAME_UNKNOWN,snull_init);
  if(snull_devs[0] == NULL || snull_devs[1] == NULL){
    ret = -1;
    goto end;
  }

  for(i=0;i<2;i++){
    if((ret = register_netdev(snull_devs[i]))){
      printk("snull:error %i registering device %s\n",ret,snull_devs[i]->name);
    }
  }

 end:
  if(ret)
    net_deinit();
	return ret;
}


module_init(net_init);
module_exit(net_deinit);
