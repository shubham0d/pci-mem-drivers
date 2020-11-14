# pci-mem-drivers
Sample drivers to help analyzing pci configuration registers.

## Files description
`pci_io.c` - Access PCI configuration space using I/O ports 
<br/>
`pci_mem.c` - Access PCI configuration space using memory i.e MMIO
<br/>
`pci_bar.c` - Using BAR register to get PCI device base addresses
<br/>
`pciexbar.c` - Using PCIEXBAR to retrieve base address of PCI configuration space

## Usage
* Update the C file
* Change the filename in `Makefile` and run `make` command.
* Load the driver using `sudo insmod filename.ko`
* Check the output using `sudo dmesg |tail`
