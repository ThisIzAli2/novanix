/**
 * @author Ali Mirmohammad
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @file pci.h
 * @abstraction:
 * 	- Kernel PCI driver implementation header file.
*/
#ifndef __ALINIX_KERNEL_PCI_H
#define __ALINIX_KERNEL_PCI_H

#define DEVICE_COUNT_RESOURCE 1024
/* Number of reset methods used in pci_reset_fn_methods array in pci.c */
#define PCI_NUM_RESET_METHODS 7



#include <alinix/types.h>
#include <alinix/io_dev.h>
#include <alinix/device.h>
#include <alinix/spinlock_types.h>

struct pci_vpd {
	// struct mutex	lock;
	unsigned int	len;
	uint8_t		cap;
};

typedef unsigned int pci_channel_state_t;
typedef int pci_power_t;
typedef short pci_dev_flags_t;

/**
 * @ref https://github.com/torvalds/linux/blob/master/include/linux/pci.h#L322
*/


/* The pci_dev structure describes PCI devices */
struct pci_dev {
	struct list_head bus_list;	/* Node in per-bus list */
	struct pci_bus	*bus;		/* Bus this device is on */
	struct pci_bus	*subordinate;	/* Bus this device bridges to */

	void		*sysdata;	/* Hook for sys-specific extension */
	struct proc_dir_entry *procent;	/* Device entry in /proc/bus/pci */
	struct pci_slot	*slot;		/* Physical slot this device is in */

	unsigned int	devfn;		/* Encoded device & function index */
	unsigned short	vendor;
	unsigned short	device;
	unsigned short	subsystem_vendor;
	unsigned short	subsystem_device;
	#ifndef __cplusplus
	unsigned int	class;		/* 3 bytes: (base,sub,prog-if) */
	#else
	unsigned int	cls;		/* 3 bytes: (base,sub,prog-if) */
	#endif /*__cplusplus*/
	uint8_t		revision;	/* PCI revision, low byte of class word */
	uint8_t		hdr_type;	/* PCI header type (`multi' flag masked out) */
#ifdef CONFIG_PCIEAER
	uint16_t		aer_cap;	/* AER capability offset */
	struct aer_stats *aer_stats;	/* AER stats for this device */
#endif /*CONFIG_PCIEAER*/
#ifdef CONFIG_PCIEPORTBUS
	struct rcec_ea	*rcec_ea;	/* RCEC cached endpoint association */
	struct pci_dev  *rcec;          /* Associated RCEC device */
#endif /*CONFIG_PCIEPORTBUS*/
	uint32_t		devcap;		/* PCIe Device Capabilities */
	uint8_t		pcie_cap;	/* PCIe capability offset */
	uint8_t		msi_cap;	/* MSI capability offset */
	uint8_t		msix_cap;	/* MSI-X capability offset */
	uint8_t		pcie_mpss:3;	/* PCIe Max Payload Size Supported */
	uint8_t		rom_base_reg;	/* Config register controlling ROM */
	uint8_t		pin;		/* Interrupt pin this device uses */
	uint16_t		pcie_flags_reg;	/* Cached PCIe Capabilities Register */
	unsigned long	*dma_alias_mask;/* Mask of enabled devfn aliases */

	struct pci_driver *driver;	/* Driver bound to this device */
	uint64_t		dma_mask;	/* Mask of the bits of bus address this
					   device implements.  Normally this is
					   0xffffffff.  You only need to change
					   this if your device has broken DMA
					   or supports 64-bit transfers.  */

	struct device_dma_parameters dma_parms;

	pci_power_t	current_state;	/* Current operating state. In ACPI,
					   this is D0-D3, D0 being fully
					   functional, and D3 being off. */
	uint8_t		pm_cap;		/* PM capability offset */
	unsigned int	imm_ready:1;	/* Supports Immediate Readiness */
	unsigned int	pme_support:5;	/* Bitmask of states from which PME#
					   can be generated */
	unsigned int	pme_poll:1;	/* Poll device's PME status bit */
	unsigned int	d1_support:1;	/* Low power state D1 is supported */
	unsigned int	d2_support:1;	/* Low power state D2 is supported */
	unsigned int	no_d1d2:1;	/* D1 and D2 are forbidden */
	unsigned int	no_d3cold:1;	/* D3cold is forbidden */
	unsigned int	bridge_d3:1;	/* Allow D3 for bridge */
	unsigned int	d3cold_allowed:1;	/* D3cold is allowed by user */
	unsigned int	mmio_always_on:1;	/* Disallow turning off io/mem
						   decoding during BAR sizing */
	unsigned int	wakeup_prepared:1;
	unsigned int	skip_bus_pm:1;	/* Internal: Skip bus-level PM */
	unsigned int	ignore_hotplug:1;	/* Ignore hotplug events */
	unsigned int	hotplug_user_indicators:1; /* SlotCtl indicators
						      controlled exclusively by
						      user sysfs */
	unsigned int	clear_retrain_link:1;	/* Need to clear Retrain Link
						   bit manually */
	unsigned int	d3hot_delay;	/* D3hot->D0 transition time in ms */
	unsigned int	d3cold_delay;	/* D3cold->D0 transition time in ms */

	uint16_t		l1ss;		/* L1SS Capability pointer */
#ifdef CONFIG_PCIEASPM
	struct pcie_link_state	*link_state;	/* ASPM link state */
	unsigned int	ltr_path:1;	/* Latency Tolerance Reporting
					   supported from root to here */
#endif /*CONFIG_PCIEASPM*/
	unsigned int	pasid_no_tlp:1;		/* PASID works without TLP Prefix */
	unsigned int	eetlp_prefix_path:1;	/* End-to-End TLP Prefix */

	pci_channel_state_t error_state;	/* Current connectivity state */
	struct device	dev;			/* Generic device interface */

	int		cfg_size;		/* Size of config space */

	/*
	 * Instead of touching interrupt line and base address registers
	 * directly, use the values stored here. They might be different!
	 */
	unsigned int	irq;
	struct resource resource[DEVICE_COUNT_RESOURCE]; /* I/O and memory regions + expansion ROMs */
	struct resource driver_exclusive_resource;	 /* driver exclusive resource ranges */

	bool		match_driver;		/* Skip attaching driver */

	unsigned int	transparent:1;		/* Subtractive decode bridge */
	unsigned int	io_window:1;		/* Bridge has I/O window */
	unsigned int	pref_window:1;		/* Bridge has pref mem window */
	unsigned int	pref_64_window:1;	/* Pref mem window is 64-bit */
	unsigned int	multifunction:1;	/* Multi-function device */

	unsigned int	is_busmaster:1;		/* Is busmaster */
	unsigned int	no_msi:1;		/* May not use MSI */
	unsigned int	no_64bit_msi:1;		/* May only use 32-bit MSIs */
	unsigned int	block_cfg_access:1;	/* Config space access blocked */
	unsigned int	broken_parity_status:1;	/* Generates false positive parity */
	unsigned int	irq_reroute_variant:2;	/* Needs IRQ rerouting variant */
	unsigned int	msi_enabled:1;
	unsigned int	msix_enabled:1;
	unsigned int	ari_enabled:1;		/* ARI forwarding */
	unsigned int	ats_enabled:1;		/* Address Translation Svc */
	unsigned int	pasid_enabled:1;	/* Process Address Space ID */
	unsigned int	pri_enabled:1;		/* Page Request Interface */
	unsigned int	is_managed:1;		/* Managed via devres */
	unsigned int	is_msi_managed:1;	/* MSI release via devres installed */
	unsigned int	needs_freset:1;		/* Requires fundamental reset */
	unsigned int	state_saved:1;
	unsigned int	is_physfn:1;
	unsigned int	is_virtfn:1;
	unsigned int	is_hotplug_bridge:1;
	unsigned int	shpc_managed:1;		/* SHPC owned by shpchp */
	unsigned int	is_thunderbolt:1;	/* Thunderbolt controller */
	/*
	 * Devices marked being untrusted are the ones that can potentially
	 * execute DMA attacks and similar. They are typically connected
	 * through external ports such as Thunderbolt but not limited to
	 * that. When an IOMMU is enabled they should be getting full
	 * mappings to make sure they cannot access arbitrary memory.
	 */
	unsigned int	untrusted:1;
	/*
	 * Info from the platform, e.g., ACPI or device tree, may mark a
	 * device as "external-facing".  An external-facing device is
	 * itself internal but devices downstream from it are external.
	 */
	unsigned int	external_facing:1;
	unsigned int	broken_intx_masking:1;	/* INTx masking can't be used */
	unsigned int	io_window_1k:1;		/* Intel bridge 1K I/O windows */
	unsigned int	irq_managed:1;
	unsigned int	non_compliant_bars:1;	/* Broken BARs; ignore them */
	unsigned int	is_probed:1;		/* Device probing in progress */
	unsigned int	link_active_reporting:1;/* Device capable of reporting link active */
	unsigned int	no_vf_scan:1;		/* Don't scan for VFs after IOV enablement */
	unsigned int	no_command_memory:1;	/* No PCI_COMMAND_MEMORY */
	unsigned int	rom_bar_overlap:1;	/* ROM BAR disable broken */
	unsigned int	rom_attr_enabled:1;	/* Display of ROM attribute enabled? */
	pci_dev_flags_t dev_flags;
	atomic_t	enable_cnt;	/* pci_enable_device has been called */

	spinlock_t	pcie_cap_lock;		/* Protects RMW ops in capability accessors */
	uint32_t		saved_config_space[16]; /* Config space saved at suspend time */
	struct hlist_head saved_cap_space;
	struct bin_attribute *res_attr[DEVICE_COUNT_RESOURCE]; /* sysfs file for resources */
	struct bin_attribute *res_attr_wc[DEVICE_COUNT_RESOURCE]; /* sysfs file for WC mapping of resources */

#ifdef CONFIG_HOTPLUG_PCI_PCIE
	unsigned int	broken_cmd_compl:1;	/* No compl for some cmds */
#endif /*CONFIG_HOTPLUG_PCI_PCIE*/
#ifdef CONFIG_PCIE_PTM
	uint16_t		ptm_cap;		/* PTM Capability */
	unsigned int	ptm_root:1;
	unsigned int	ptm_enabled:1;
	uint8_t		ptm_granularity;
#endif /*CONFIG_PCIE_PTM*/
#ifdef CONFIG_PCI_MSI
	void __iomem	*msix_base;
	raw_spinlock_t	msi_lock;
#endif /*CONFIG_PCI_MSI*/
	struct pci_vpd	vpd;
#ifdef CONFIG_PCIE_DPC
	uint16_t		dpc_cap;
	unsigned int	dpc_rp_extensions:1;
	uint8_t		dpc_rp_log_size;
#endif /*CONFIG_PCIE_DPC*/
#ifdef CONFIG_PCI_ATS
	union {
		struct pci_sriov	*sriov;		/* PF: SR-IOV info */
		struct pci_dev		*physfn;	/* VF: related PF */
	};
	uint16_t		ats_cap;	/* ATS Capability offset */
	uint8_t		ats_stu;	/* ATS Smallest Translation Unit */
#endif /*CONFIG_PCI_ATS*/
#ifdef CONFIG_PCI_PRI
	uint16_t		pri_cap;	/* PRI Capability offset */
	uint32_t		pri_reqs_alloc; /* Number of PRI requests allocated */
	unsigned int	pasid_required:1; /* PRG Response PASID Required */
#endif /*CONFIG_PCI_PRI*/
#ifdef CONFIG_PCI_PASID
	uint16_t		pasid_cap;	/* PASID Capability offset */
	uint16_t		pasid_features;
#endif /*CONFIG_PCI_PASID*/
#ifdef CONFIG_PCI_P2PDMA
	struct pci_p2pdma __rcu *p2pdma;
#endif /*CONFIG_PCI_P2PDMA*/
#ifdef CONFIG_PCI_DOE
	struct xarray	doe_mbs;	/* Data Object Exchange mailboxes */
#endif /*CONFIG_PCI_DOE*/
	uint16_t		acs_cap;	/* ACS Capability offset */
	phys_addr_t	rom;		/* Physical address if not from BAR */
	size_t		romlen;		/* Length if not from BAR */
	/*
	 * Driver name to force a match.  Do not set directly, because core
	 * frees it.  Use driver_set_override() to set or clear it.
	 */
	const char	*driver_override;

	unsigned long	priv_flags;	/* Private flags for the PCI driver */

	/* These methods index pci_reset_fn_methods[] */
	uint8_t reset_methods[PCI_NUM_RESET_METHODS]; /* In priority order */
};


////////////////////////////////////////////////////////////

uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint16_t pciCheckVendor(uint8_t bus, uint8_t slot);
void checkDevice(uint8_t bus, uint8_t device);
void checkAllBuses(void);
void checkBus(uint8_t bus);
void checkFunction(uint8_t bus, uint8_t device, uint8_t function);
void checkAllBuses(void);
uint64_t arch_msi_address(uint64_t *data, size_t vector, uint32_t processor, uint8_t edgetrigger, uint8_t deassert);


#endif // __ALINIX_KERNEL_PCI_H