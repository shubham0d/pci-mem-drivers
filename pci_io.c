#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <sound/initval.h>
#include <asm/io.h>
static int my_init(void)
{

	u32 io_addr_response;
	u32 io_data;
	
	uint32_t address;
	//change according to B::D::F value
    uint32_t lbus  = 0x0;
    uint32_t ldevice = 0x1f;
    uint32_t lfunc = 0x0;
    uint8_t offset = 0x10;
	
	printk(KERN_INFO "Inside driver.\n");
	
    // create configuration address as per format CONFIG_ADDRESS
    address = (uint32_t)((lbus << 16) | (ldevice << 11) |
              (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));
    
	
	//write the address
	outl(0xCF8, address);
	
	//check if PCI I/O request to device is enable
	io_addr_response = inl(0xcf8);
	io_addr_response = io_addr_response & 0x80000000;
	if (io_addr_response == 0)
	{
		printk(KERN_INFO "I/O port access for device is not enabled.\n" );
	}
	
	io_data = inl(0xcfc);
	
	printk(KERN_INFO "Data recieved is %x.\n", io_data);
	
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
MODULE_DESCRIPTION("I/O operation test driver");
