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
	u32 pciexbar;
	uint32_t pci_data;
	uint32_t lbus  = 0x0;
    uint32_t ldevice = 0x0;
    uint32_t lfunc = 0x0;
    uint16_t offset = 0x2;
    printk(KERN_INFO "Inside driver.\n");
    //get pci device
    dev = pci_get_device(0x8086, 0x0A04, NULL);
    if (!dev)
    {
		printk(KERN_INFO "FAILED to get pci device\n");
		pci_dev_put(dev);
		return -ENODEV;
	}
	printk(KERN_INFO "Attached to the pci device\n");
	//read PCIEXBAR value
	pci_read_config_dword(dev, 0x60, &pciexbar);
	
	// retrieving pci configuration space starting address
	pciexbar = pciexbar & 0xF0000000;
	printk(KERN_INFO "PCI Configuration space starts at %x.\n", pciexbar);
	
	// retrieving the DWORD value for pci device 0:0:0 offset 2
	pci_data = (uint32_t)(pciexbar | (lbus << 20) | (ldevice << 15) | (lfunc << 12) | (offset & 0xFFF));
	printk(KERN_INFO "PCI device data is at physical location %x.\n", pci_data);


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
MODULE_DESCRIPTION("PCIEXBAR MMIO driver");
