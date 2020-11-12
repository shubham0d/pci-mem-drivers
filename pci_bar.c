#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <sound/initval.h>

static int my_init(void)
{
	struct pci_dev *dev;
	u32 pci_data;
    printk(KERN_INFO "Inside driver.\n");
    //get pci device
    dev = pci_get_device(0x8086, 0x9c31, NULL);
    if (!dev)
    {
		printk(KERN_INFO "FAILED to get pci device\n");
		pci_dev_put(dev);
		return -ENODEV;
	}
	printk(KERN_INFO "Attached to the pci device\n");
	//read dword value from pci device
	pci_read_config_dword(dev, 0x10, &pci_data);
	
	// getting the base address
	pci_data = pci_data & 0xFFFFFFF0;
	printk(KERN_INFO "Base address is %x.\n", pci_data);
	
	// Getting the PIC device BAR limit
	pci_write_config_dword(dev, 0x10, 0xFFFFFFFF);

	pci_read_config_dword(dev, 0x10, &pci_data);
	pci_data = pci_data & 0xFFFFFFF0;
	pci_data = ~pci_data;
	printk(KERN_INFO "BAR limit is %x.\n", pci_data);

	//cleanup after use
	pci_dev_put(dev);

    
    return  0;
}
   
static void my_exit(void)
{
    printk(KERN_INFO "Exit driver.\n");

    return;
}
   
module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shubham Dubey <shubham0d@protonmail.coms>");
MODULE_DESCRIPTION("PCI config MMIO driver");
