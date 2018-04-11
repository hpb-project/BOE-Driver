/*
 * This file is part of the BOE Ethernet driver for Linux.
 * Author: loushl
 * Copyright (C) 2018 HPB.  All rights reserved.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the LICENSE file included in this
 * release for licensing terms and conditions.
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/bitmap.h>
#include <linux/crc32.h>
#include <linux/debugfs.h>
#include <linux/etherdevice.h>
#include <linux/firmware.h>
#include <linux/if_vlan.h>
#include <linux/log2.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/mutex.h>
#include <linux/netdevice.h>
#include <linux/pci.h>
#include <linux/aer.h>
#include <linux/rtnetlink.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/sockios.h>
#include <linux/vmalloc.h>
#include <linux/workqueue.h>
#include <net/neighbour.h>
#include <net/netevent.h>
#include <net/addrconf.h>
#include <asm/uaccess.h>
#include <linux/dma-mapping.h>
#include <linux/mii.h>
#include <linux/proc_fs.h>
#include <linux/sort.h>
#include <linux/notifier.h>
#include <linux/string_helpers.h>
#include <net/inet6_hashtables.h>
#include <linux/crash_dump.h>
#include <net/udp_tunnel.h>

#include "BOE_debug.h"
#include "common.h"



static const struct pci_device_id pci_ids[] = {
	{ PCI_DEVICE(VENDOR_ID, DEV_ID), },
}

//pci struct
static struct pci_driver boe_driver = {
	.name     = KBUILD_MODNAME,
	.id_table = boe_pci_tbl,
	//pci device add
	.probe    = init_one,
	//pci device remove
	.remove   = remove_one,
	.shutdown = shutdown_one,
	.err_handler = &boe_eeh,
};
/*module init */
static int __init boe_init_module(void)
{
	int ret;

	ret = pci_register_driver(&boe_driver);
	if (ret < 0)
		dbg_init(boe_debugfs_root);
	return ret;
}

/*module exit*/
static void __exit cxgb4_cleanup_module(void)
{

}

module_init(boe_init_module);
module_exit(boe_exit_module);

