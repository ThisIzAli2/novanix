/**
 * @file acpi.h
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
 * @abstraction:
 *  - UACPI util.
*/


#ifndef __ALINIX_UACPI_ACPI_ACPI_H__INCLUDED
#define __ALINIX_UACPI_ACPI_ACPI_H__INCLUDED

#include <alinix/types.h>
#include <alinix/compiler.h>

#define ACPI_RSDP_SIGNATURE "RSD PTR "
#define ACPI_RSDT_SIGNATURE "RSDT"
#define ACPI_XSDT_SIGNATURE "XSDT"
#define ACPI_MADT_SIGNATURE "APIC"
#define ACPI_FADT_SIGNATURE "FACP"
#define ACPI_FACS_SIGNATURE "FACS"
#define ACPI_MCFG_SIGNATURE "MCFG"
#define ACPI_HPET_SIGNATURE "HPET"
#define ACPI_SRAT_SIGNATURE "SRAT"
#define ACPI_SLIT_SIGNATURE "SLIT"
#define ACPI_DSDT_SIGNATURE "DSDT"
#define ACPI_SSDT_SIGNATURE "SSDT"
#define ACPI_PSDT_SIGNATURE "PSDT"
#define ACPI_ECDT_SIGNATURE "ECDT"

#define ACPI_AS_ID_SYS_MEM       0x00
#define ACPI_AS_ID_SYS_IO        0x01
#define ACPI_AS_ID_PCI_CFG_SPACE 0x02
#define ACPI_AS_ID_EC            0x03
#define ACPI_AS_ID_SMBUS         0x04
#define ACPI_AS_ID_SYS_CMOS      0x05
#define ACPI_AS_ID_PCI_BAR_TGT   0x06
#define ACPI_AS_ID_IPMI          0x07
#define ACPI_AS_ID_GP_IO         0x08
#define ACPI_AS_ID_GENERIC_SBUS  0x09
#define ACPI_AS_ID_PCC           0x0A
#define ACPI_AS_ID_FFH           0x7F
#define ACPI_AS_ID_OEM_BASE      0xC0
#define ACPI_AS_ID_OEM_END       0xFF

#define ACPI_ACCESS_UD    0
#define ACPI_ACCESS_BYTE  1
#define ACPI_ACCESS_WORD  2
#define ACPI_ACCESS_DWORD 3
#define ACPI_ACCESS_QWORD 4

UACPI_PACKED(struct acpi_gas {
    u8 address_space_id;
    u8 register_bit_width;
    u8 register_bit_offset;
    u8 access_size;
    u64 address;
})

UACPI_PACKED(struct acpi_rsdp {
    char signature[8];
    u8 checksum;
    char oemid[6];
    u8 revision;
    u32 rsdt_addr;

    // vvvv available if .revision >= 2.0 only
    u32 length;
    u64 xsdt_addr;
    u8 extended_checksum;
    u8 rsvd[3];
})
// UACPI_EXPECT_SIZEOF(struct acpi_rsdp, 36);

UACPI_PACKED(struct acpi_sdt_hdr {
    char signature[4];
    u32 length;
    u8 revision;
    u8 checksum;
    char oemid[6];
    char oem_table_id[8];
    u32 oem_revision;
    u32 creator_id;
    u32 creator_revision;
})
// UACPI_EXPECT_SIZEOF(struct acpi_sdt_hdr, 36);

UACPI_PACKED(struct acpi_rsdt {
    struct acpi_sdt_hdr hdr;
    u32 entries[];
})

UACPI_PACKED(struct acpi_xsdt {
    struct acpi_sdt_hdr hdr;
    u64 entries[];
})

UACPI_PACKED(struct acpi_entry_hdr {
    /*
     * - acpi_madt_entry_type for the APIC table
     * - acpi_srat_entry_type for the SRAT table
     */
    u8 type;
    u8 length;
})

// acpi_madt->flags
#define ACPI_PCAT_COMPAT (1 << 0)

enum acpi_madt_entry_type {
    ACPI_MADT_ENTRY_TYPE_LAPIC = 0,
    ACPI_MADT_ENTRY_TYPE_IOAPIC = 1,
    ACPI_MADT_ENTRY_TYPE_INTERRUPT_SOURCE_OVERRIDE = 2,
    ACPI_MADT_ENTRY_TYPE_NMI_SOURCE = 3,
    ACPI_MADT_ENTRY_TYPE_LAPIC_NMI = 4,
    ACPI_MADT_ENTRY_TYPE_LAPIC_ADDRESS_OVERRIDE = 5,
    ACPI_MADT_ENTRY_TYPE_IOSAPIC = 6,
    ACPI_MADT_ENTRY_TYPE_LSAPIC = 7,
    ACPI_MADT_ENTRY_TYPE_PLATFORM_INTERRUPT_SOURCES = 8,
    ACPI_MADT_ENTRY_TYPE_LOCAL_X2APIC = 9,
    ACPI_MADT_ENTRY_TYPE_LOCAL_X2APIC_NMI = 0xA,
    ACPI_MADT_ENTRY_TYPE_GICC = 0xB,
    ACPI_MADT_ENTRY_TYPE_GICD = 0xC,
    ACPI_MADT_ENTRY_TYPE_GIC_MSI_FRAME = 0xD,
    ACPI_MADT_ENTRY_TYPE_GICR = 0xE,
    ACPI_MADT_ENTRY_TYPE_GIC_ITS = 0xF,
    ACPI_MADT_ENTRY_TYPE_MULTIPROCESSOR_WAKEUP = 0x10,
    ACPI_MADT_ENTRY_TYPE_CORE_PIC = 0x11,
    ACPI_MADT_ENTRY_TYPE_LIO_PIC = 0x12,
    ACPI_MADT_ENTRY_TYPE_HT_PIC = 0x13,
    ACPI_MADT_ENTRY_TYPE_EIO_PIC = 0x14,
    ACPI_MADT_ENTRY_TYPE_MSI_PIC = 0x15,
    ACPI_MADT_ENTRY_TYPE_BIO_PIC = 0x16,
    ACPI_MADT_ENTRY_TYPE_LPC_PIC = 0x17,
    ACPI_MADT_ENTRY_TYPE_RESERVED = 0x18, // 0x18..0x7F
    ACPI_MADT_ENTRY_TYPE_OEM = 0x80, // 0x80..0xFF
};

UACPI_PACKED(struct acpi_madt {
    struct acpi_sdt_hdr hdr;
    u32 local_interrupt_controller_address;
    u32 flags;
    struct acpi_entry_hdr entries[];
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt, 44);

/*
 * - acpi_madt_lapic->flags
 * - acpi_madt_lsapic->flags
 * - acpi_madt_x2apic->flags
 */
#define ACPI_PIC_ENABLED (1 << 0)
#define ACPI_PIC_ONLINE_CAPABLE (1 << 1)

UACPI_PACKED(struct acpi_madt_lapic {
    struct acpi_entry_hdr hdr;
    u8 uid;
    u8 id;
    u32 flags;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_lapic, 8);

UACPI_PACKED(struct acpi_madt_ioapic {
    struct acpi_entry_hdr hdr;
    u8 id;
    u8 rsvd;
    u32 address;
    u32 gsi_base;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_ioapic, 12);

/*
 * - acpi_madt_interrupt_source_override->flags
 * - acpi_madt_nmi_source->flags
 * - acpi_madt_lapic_nmi->flags
 * - acpi_madt_platform_interrupt_source->flags
 * - acpi_madt_x2apic_nmi->flags
 */
#define ACPI_MADT_POLARITY_MASK 0b11
#define ACPI_MADT_POLARITY_CONFORMING 0b00
#define ACPI_MADT_POLARITY_ACTIVE_HIGH 0b01
#define ACPI_MADT_POLARITY_ACTIVE_LOW 0b11

#define ACPI_MADT_TRIGGERING_MASK 0b1100
#define ACPI_MADT_TRIGGERING_CONFORMING 0b0000
#define ACPI_MADT_TRIGGERING_EDGE 0b0100
#define ACPI_MADT_TRIGGERING_LEVEL 0b1100

UACPI_PACKED(struct acpi_madt_interrupt_source_override {
    struct acpi_entry_hdr hdr;
    u8 bus;
    u8 source;
    u32 gsi;
    u16 flags;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_interrupt_source_override, 10);

UACPI_PACKED(struct acpi_madt_nmi_source {
    struct acpi_entry_hdr hdr;
    u16 flags;
    u32 gsi;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_nmi_source, 8);

UACPI_PACKED(struct acpi_madt_lapic_nmi {
    struct acpi_entry_hdr hdr;
    u8 uid;
    u16 flags;
    u8 lint;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_lapic_nmi, 6);

UACPI_PACKED(struct acpi_madt_lapic_address_override {
    struct acpi_entry_hdr hdr;
    u16 rsvd;
    u64 address;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_lapic_address_override, 12);

UACPI_PACKED(struct acpi_madt_iosapic {
    struct acpi_entry_hdr hdr;
    u8 id;
    u8 rsvd;
    u32 gsi_base;
    u64 address;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_iosapic, 16);

UACPI_PACKED(struct acpi_madt_lsapic {
    struct acpi_entry_hdr hdr;
    u8 acpi_id;
    u8 id;
    u8 eid;
    u8 reserved[3];
    u32 flags;
    u32 uid;
    char uid_string[];
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_lsapic, 16);

// acpi_madt_platform_interrupt_source->platform_flags
#define ACPI_CPEI_PROCESSOR_OVERRIDE (1 << 0)

UACPI_PACKED(struct acpi_madt_platform_interrupt_source {
    struct acpi_entry_hdr hdr;
    u16 flags;
    u8 type;
    u8 processor_id;
    u8 processor_eid;
    u8 iosapic_vector;
    u32 gsi;
    u32 platform_flags;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_platform_interrupt_source, 16);

UACPI_PACKED(struct acpi_madt_x2apic {
    struct acpi_entry_hdr hdr;
    u16 rsvd;
    u32 id;
    u32 flags;
    u32 uid;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_x2apic, 16);

UACPI_PACKED(struct acpi_madt_x2apic_nmi {
    struct acpi_entry_hdr hdr;
    u16 flags;
    u32 uid;
    u8 lint;
    u8 reserved[3];
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_x2apic_nmi, 12);

// acpi_madt_gicc->flags
#define ACPI_GICC_ENABLED (1 << 0)
#define ACPI_GICC_PERF_INTERRUPT_MODE (1 << 1)
#define ACPI_GICC_VGIC_MAINTENANCE_INTERRUPT_MODE (1 << 2)
#define ACPI_GICC_ONLINE_CAPABLE (1 << 3)

// ACPI_GICC_*_INTERRUPT_MODE
#define ACPI_GICC_TRIGGERING_EDGE 1
#define ACPI_GICC_TRIGGERING_LEVEL 0

UACPI_PACKED(struct acpi_madt_gicc {
    struct acpi_entry_hdr hdr;
    u16 rsvd0;
    u32 interface_number;
    u32 acpi_id;
    u32 flags;
    u32 parking_protocol_version;
    u32 perf_interrupt_gsiv;
    u64 parked_address;
    u64 address;
    u64 gicv;
    u64 gich;
    u32 vgic_maitenante_interrupt;
    u64 gicr_base_address;
    u64 mpidr;
    u8 power_efficiency_class;
    u8 rsvd1;
    u16 spe_overflow_interrupt;
    u16 trbe_interrupt;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_gicc, 82);

UACPI_PACKED(struct acpi_madt_gicd {
    struct acpi_entry_hdr hdr;
    u16 rsvd0;
    u32 id;
    u64 address;
    u32 system_vector_base;
    u8 gic_version;
    u8 reserved1[3];
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_gicd, 24);

// acpi_madt_gic_msi_frame->flags
#define ACPI_SPI_SELECT (1 << 0)

UACPI_PACKED(struct acpi_madt_gic_msi_frame {
    struct acpi_entry_hdr hdr;
    u16 rsvd;
    u32 id;
    u64 address;
    u32 flags;
    u16 spi_count;
    u16 spi_base;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_gic_msi_frame, 24);

UACPI_PACKED(struct acpi_madt_gicr {
    struct acpi_entry_hdr hdr;
    u16 rsvd;
    u64 address;
    u32 length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_gicr, 16);

UACPI_PACKED(struct acpi_madt_gic_its {
    struct acpi_entry_hdr hdr;
    u16 rsvd0;
    u32 id;
    u64 address;
    u32 rsvd1;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_gic_its, 20);

UACPI_PACKED(struct acpi_madt_multiprocessor_wakeup {
    struct acpi_entry_hdr hdr;
    u16 mailbox_version;
    u32 rsvd;
    u64 mailbox_address;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_multiprocessor_wakeup, 16);

#define ACPI_CORE_PIC_ENABLED (1 << 0)

UACPI_PACKED(struct acpi_madt_core_pic {
    struct acpi_entry_hdr hdr;
    u8 version;
    u32 acpi_id;
    u32 id;
    u32 flags;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_core_pic, 15);

UACPI_PACKED(struct acpi_madt_lio_pic {
    struct acpi_entry_hdr hdr;
    u8 version;
    u64 address;
    u16 size;
    u16 cascade_vector;
    u64 cascade_vector_mapping;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_lio_pic, 23);

UACPI_PACKED(struct acpi_madt_ht_pic {
    struct acpi_entry_hdr hdr;
    u8 version;
    u64 address;
    u16 size;
    u64 cascade_vector;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_ht_pic, 21);

UACPI_PACKED(struct acpi_madt_eio_pic {
    struct acpi_entry_hdr hdr;
    u8 version;
    u8 cascade_vector;
    u8 node;
    u64 node_map;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_eio_pic, 13);

UACPI_PACKED(struct acpi_madt_msi_pic {
    struct acpi_entry_hdr hdr;
    u8 version;
    u64 address;
    u32 start;
    u32 count;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_msi_pic, 19);

UACPI_PACKED(struct acpi_madt_bio_pic {
    struct acpi_entry_hdr hdr;
    u8 version;
    u64 address;
    u16 size;
    u16 hardware_id;
    u16 gsi_base;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_bio_pic, 17);

UACPI_PACKED(struct acpi_madt_lpc_pic {
    struct acpi_entry_hdr hdr;
    u8 version;
    u64 address;
    u16 size;
    u16 cascade_vector;
})
// UACPI_EXPECT_SIZEOF(struct acpi_madt_lpc_pic, 15);

enum acpi_srat_entry_type {
    ACPI_SRAT_ENTRY_TYPE_PROCESSOR_AFFINITY = 0,
    ACPI_SRAT_ENTRY_TYPE_MEMORY_AFFINITY = 1,
    ACPI_SRAT_ENTRY_TYPE_X2APIC_AFFINITY = 2,
    ACPI_SRAT_ENTRY_TYPE_GICC_AFFINITY = 3,
    ACPI_SRAT_ENTRY_TYPE_GIC_ITS_AFFINITY = 4,
    ACPI_SRAT_ENTRY_TYPE_GENERIC_INITIATOR_AFFINITY = 5,
    ACPI_SRAT_ENTRY_TYPE_GENERIC_PORT_AFFINITY = 6,
    ACPI_SRAT_ENTRY_TYPE_RINTC_AFFINITY = 7,
};

UACPI_PACKED(struct acpi_srat {
    struct acpi_sdt_hdr hdr;
    u32 rsvd0;
    u64 rsvd1;
    struct acpi_entry_hdr entries[];
})
// UACPI_EXPECT_SIZEOF(struct acpi_srat, 48);

/*
 * acpi_srat_processor_affinity->flags
 * acpi_srat_x2apic_affinity->flags
 */
#define ACPI_SRAT_PROCESSOR_ENABLED (1 << 0)

UACPI_PACKED(struct acpi_srat_processor_affinity {
    struct acpi_entry_hdr hdr;
    u8 proximity_domain_low;
    u8 id;
    u32 flags;
    u8 eid;
    u8 proximity_domain_high[3];
    u32 clock_domain;
})
// UACPI_EXPECT_SIZEOF(struct acpi_srat_processor_affinity, 16);

// acpi_srat_memory_affinity->flags
#define ACPI_SRAT_MEMORY_ENABLED (1 << 0)
#define ACPI_SRAT_MEMORY_HOTPLUGGABLE (1 << 1)
#define ACPI_SRAT_MEMORY_NON_VOLATILE (1 << 2)

UACPI_PACKED(struct acpi_srat_memory_affinity {
    struct acpi_entry_hdr hdr;
    u32 proximity_domain;
    u16 rsvd0;
    u64 address;
    u64 length;
    u32 rsvd1;
    u32 flags;
    u64 rsdv2;
})
// UACPI_EXPECT_SIZEOF(struct acpi_srat_memory_affinity, 40);

UACPI_PACKED(struct acpi_srat_x2apic_affinity {
    struct acpi_entry_hdr hdr;
    u16 rsvd0;
    u32 proximity_domain;
    u32 id;
    u32 flags;
    u32 clock_domain;
    u32 rsvd1;
})
// UACPI_EXPECT_SIZEOF(struct acpi_srat_x2apic_affinity, 24);

// acpi_srat_gicc_affinity->flags
#define ACPI_SRAT_GICC_ENABLED (1 << 0)

UACPI_PACKED(struct acpi_srat_gicc_affinity {
    struct acpi_entry_hdr hdr;
    u32 proximity_domain;
    u32 uid;
    u32 flags;
    u32 clock_domain;
})
// UACPI_EXPECT_SIZEOF(struct acpi_srat_gicc_affinity, 18);

UACPI_PACKED(struct acpi_srat_gic_its_affinity {
    struct acpi_entry_hdr hdr;
    u32 proximity_domain;
    u16 rsvd;
    u32 id;
})
// UACPI_EXPECT_SIZEOF(struct acpi_srat_gic_its_affinity, 12);

// acpi_srat_generic_affinity->flags
#define ACPI_GENERIC_AFFINITY_ENABLED (1 << 0)
#define ACPI_GENERIC_AFFINITY_ARCH_TRANSACTIONS (1 << 1)

UACPI_PACKED(struct acpi_srat_generic_affinity {
    struct acpi_entry_hdr hdr;
    u8 rsvd0;
    u8 handle_type;
    u32 proximity_domain;
    u8 handle[16];
    u32 flags;
    u32 rsvd1;
})
// UACPI_EXPECT_SIZEOF(struct acpi_srat_generic_affinity, 32);

// acpi_srat_rintc_affinity->flags
#define ACPI_SRAT_RINTC_AFFINITY_ENABLED (1 << 0)

UACPI_PACKED(struct acpi_srat_rintc_affinity {
    struct acpi_entry_hdr hdr;
    u16 rsvd;
    u32 proximity_domain;
    u32 uid;
    u32 flags;
    u32 clock_domain;
})
// UACPI_EXPECT_SIZEOF(struct acpi_srat_rintc_affinity, 20);

UACPI_PACKED(struct acpi_slit {
    struct acpi_sdt_hdr hdr;
    u64 num_localities;
    u8 matrix[];
})
// UACPI_EXPECT_SIZEOF(struct acpi_slit, 44);

// acpi_fdt->iapc_flags
#define ACPI_IA_PC_LEGACY_DEVS  (1 << 0)
#define ACPI_IA_PC_8042         (1 << 1)
#define ACPI_IA_PC_NO_VGA       (1 << 2)
#define ACPI_IA_PC_NO_MSI       (1 << 3)
#define ACPI_IA_PC_NO_PCIE_ASPM (1 << 4)
#define ACPI_IA_PC_NO_CMOS_RTC  (1 << 5)

// acpi_fdt->flags
#define ACPI_WBINVD                    (1 << 0)
#define ACPI_WBINVD_FLUSH              (1 << 1)
#define ACPI_PROC_C1                   (1 << 2)
#define ACPI_P_LVL2_UP                 (1 << 3)
#define ACPI_PWR_BUTTON                (1 << 4)
#define ACPI_SLP_BUTTON                (1 << 5)
#define ACPI_FIX_RTC                   (1 << 6)
#define ACPI_RTC_S4                    (1 << 7)
#define ACPI_TMR_VAL_EXT               (1 << 8)
#define ACPI_DCK_CAP                   (1 << 9)
#define ACPI_RESET_REG_SUP             (1 << 10)
#define ACPI_SEALED_CASE               (1 << 11)
#define ACPI_HEADLESS                  (1 << 12)
#define ACPI_CPU_SW_SLP                (1 << 13)
#define ACPI_PCI_EXP_WAK               (1 << 14)
#define ACPI_USE_PLATFORM_CLOCK        (1 << 15)
#define ACPI_S4_RTC_STS_VALID          (1 << 16)
#define ACPI_REMOTE_POWER_ON_CAPABLE   (1 << 17)
#define ACPI_FORCE_APIC_CLUSTER_MODEL  (1 << 18)
#define ACPI_FORCE_APIC_PHYS_DEST_MODE (1 << 19)
#define ACPI_HW_REDUCED_ACPI           (1 << 20)
#define ACPI_LOW_POWER_S0_IDLE_CAPABLE (1 << 21)

// acpi_fdt->arm_flags
#define ACPI_ARM_PSCI_COMPLIANT (1 << 0)
#define ACPI_ARM_PSCI_USE_HVC   (1 << 1)

UACPI_PACKED(struct acpi_fadt {
    struct acpi_sdt_hdr hdr;
    u32 firmware_ctrl;
    u32 dsdt;
    u8 int_model;
    u8 preferred_pm_profile;
    u16 sci_int;
    u32 smi_cmd;
    u8 acpi_enable;
    u8 acpi_disable;
    u8 s4bios_req;
    u8 pstate_cnt;
    u32 pm1a_evt_blk;
    u32 pm1b_evt_blk;
    u32 pm1a_cnt_blk;
    u32 pm1b_cnt_blk;
    u32 pm2_cnt_blk;
    u32 pm_tmr_blk;
    u32 gpe0_blk;
    u32 gpe1_blk;
    u8 pm1_evt_len;
    u8 pm1_cnt_len;
    u8 pm2_cnt_len;
    u8 pm_tmr_len;
    u8 gpe0_blk_len;
    u8 gpe1_blk_len;
    u8 gpe1_base;
    u8 cst_cnt;
    u16 p_lvl2_lat;
    u16 p_lvl3_lat;
    u16 flush_size;
    u16 flush_stride;
    u8 duty_offset;
    u8 duty_width;
    u8 day_alrm;
    u8 mon_alrm;
    u8 century;
    u16 iapc_boot_arch;
    u8 rsvd;
    u32 flags;
    struct acpi_gas reset_reg;
    u8 reset_value;
    u16 arm_boot_arch;
    u8 fadt_minor_verison;
    u64 x_firmware_ctrl;
    u64 x_dsdt;
    struct acpi_gas x_pm1a_evt_blk;
    struct acpi_gas x_pm1b_evt_blk;
    struct acpi_gas x_pm1a_cnt_blk;
    struct acpi_gas x_pm1b_cnt_blk;
    struct acpi_gas x_pm2_cnt_blk;
    struct acpi_gas x_pm_tmr_blk;
    struct acpi_gas x_gpe0_blk;
    struct acpi_gas x_gpe1_blk;
    struct acpi_gas sleep_control_reg;
    struct acpi_gas sleep_status_reg;
    u64 hypervisor_vendor_identity;
})
// UACPI_EXPECT_SIZEOF(struct acpi_fadt, 276);

// acpi_facs->flags
#define ACPI_S4BIOS_F               (1 << 0)
#define ACPI_64BIT_WAKE_SUPPORTED_F (1 << 1)

// acpi_facs->ospm_flags
#define ACPI_64BIT_WAKE_F           (1 << 0)

UACPI_PACKED(struct acpi_facs {
    char signature[4];
    u32 length;
    u32 hardware_signature;
    u32 firmware_waking_vector;
    u32 global_lock;
    u32 flags;
    u64 x_firmware_waking_vector;
    u8 version;
    char rsvd0[3];
    u32 ospm_flags;
    char rsvd1[24];
})
// UACPI_EXPECT_SIZEOF(struct acpi_facs, 64);

UACPI_PACKED(struct acpi_mcfg_allocation {
    u64 address;
    u16 segment;
    u8 start_bus;
    u8 end_bus;
    u32 rsvd;
})
// UACPI_EXPECT_SIZEOF(struct acpi_mcfg_allocation, 16);

UACPI_PACKED(struct acpi_mcfg {
    struct acpi_sdt_hdr hdr;
    u64 rsvd;
    struct acpi_mcfg_allocation entries[];
})
// UACPI_EXPECT_SIZEOF(struct acpi_mcfg, 44);

// acpi_hpet->block_id
#define ACPI_HPET_PCI_VENDOR_ID_SHIFT 16
#define ACPI_HPET_LEGACY_REPLACEMENT_IRQ_ROUTING_CAPABLE (1 << 15)
#define ACPI_HPET_COUNT_SIZE_CAP_COUNTER_SIZE (1 << 13)
#define ACPI_HPET_NUMBER_OF_COMPARATORS_SHIFT 8
#define ACPI_HPET_NUMBER_OF_COMPARATORS_MASK 0b11111
#define ACPI_HPET_HARDWARE_REV_ID_MASK 0b11111111

// acpi_hpet->flags
#define ACPI_HPET_PAGE_PROTECTION_MASK 0b11
#define ACPI_HPET_PAGE_NO_PROTECTION 0
#define ACPI_HPET_PAGE_4K_PROTECTED 1
#define ACPI_HPET_PAGE_64K_PROTECTED 2

UACPI_PACKED(struct acpi_hpet {
    struct acpi_sdt_hdr hdr;
    u32 block_id;
    struct acpi_gas address;
    u8 number;
    u16 min_clock_tick;
    u8 flags;
})
// UACPI_EXPECT_SIZEOF(struct acpi_hpet, 56);

// PM1{a,b}_STS
#define ACPI_PM1_STS_TMR_STS_IDX 0
#define ACPI_PM1_STS_BM_STS_IDX 4
#define ACPI_PM1_STS_GBL_STS_IDX 5
#define ACPI_PM1_STS_PWRBTN_STS_IDX 8
#define ACPI_PM1_STS_SLPBTN_STS_IDX 9
#define ACPI_PM1_STS_RTC_STS_IDX 10
#define ACPI_PM1_STS_IGN0_IDX 11
#define ACPI_PM1_STS_PCIEXP_WAKE_STS_IDX 14
#define ACPI_PM1_STS_WAKE_STS_IDX 15

#define ACPI_PM1_STS_TMR_STS_MASK (1 << ACPI_PM1_STS_TMR_STS_IDX)
#define ACPI_PM1_STS_BM_STS_MASK (1 << ACPI_PM1_STS_BM_STS_IDX)
#define ACPI_PM1_STS_GBL_STS_MASK (1 << ACPI_PM1_STS_GBL_STS_IDX)
#define ACPI_PM1_STS_PWRBTN_STS_MASK (1 << ACPI_PM1_STS_PWRBTN_STS_IDX)
#define ACPI_PM1_STS_SLPBTN_STS_MASK (1 << ACPI_PM1_STS_SLPBTN_STS_IDX)
#define ACPI_PM1_STS_RTC_STS_MASK (1 << ACPI_PM1_STS_RTC_STS_IDX)
#define ACPI_PM1_STS_IGN0_MASK (1 << ACPI_PM1_STS_IGN0_IDX)
#define ACPI_PM1_STS_PCIEXP_WAKE_STS_MASK (1 << ACPI_PM1_STS_PCIEXP_WAKE_STS_IDX)
#define ACPI_PM1_STS_WAKE_STS_MASK (1 << ACPI_PM1_STS_WAKE_STS_IDX)

#define ACPI_PM1_STS_CLEAR 1

// PM1{a,b}_EN
#define ACPI_PM1_EN_TMR_EN_IDX 0
#define ACPI_PM1_EN_GBL_EN_IDX 5
#define ACPI_PM1_EN_PWRBTN_EN_IDX 8
#define ACPI_PM1_EN_SLPBTN_EN_IDX 9
#define ACPI_PM1_EN_RTC_EN_IDX 10
#define ACPI_PM1_EN_PCIEXP_WAKE_DIS_IDX 14

#define ACPI_PM1_EN_TMR_EN_MASK (1 << ACPI_PM1_EN_TMR_EN_IDX)
#define ACPI_PM1_EN_GBL_EN_MASK (1 << ACPI_PM1_EN_GBL_EN_IDX)
#define ACPI_PM1_EN_PWRBTN_EN_MASK (1 << ACPI_PM1_EN_PWRBTN_EN_IDX)
#define ACPI_PM1_EN_SLPBTN_EN_MASK (1 << ACPI_PM1_EN_SLPBTN_EN_IDX)
#define ACPI_PM1_EN_RTC_EN_MASK (1 << ACPI_PM1_EN_RTC_EN_IDX)
#define ACPI_PM1_EN_PCIEXP_WAKE_DIS_MASK (1 << ACPI_PM1_EN_PCIEXP_WAKE_DIS_IDX)

// PM1{a,b}_CNT_BLK
#define ACPI_PM1_CNT_SCI_EN_IDX 0
#define ACPI_PM1_CNT_BM_RLD_IDX 1
#define ACPI_PM1_CNT_GBL_RLS_IDX 2
#define ACPI_PM1_CNT_RSVD0_IDX 3
#define ACPI_PM1_CNT_RSVD1_IDX 4
#define ACPI_PM1_CNT_RSVD2_IDX 5
#define ACPI_PM1_CNT_RSVD3_IDX 6
#define ACPI_PM1_CNT_RSVD4_IDX 7
#define ACPI_PM1_CNT_RSVD5_IDX 8
#define ACPI_PM1_CNT_IGN0_IDX 9
#define ACPI_PM1_CNT_SLP_TYP_IDX 10
#define ACPI_PM1_CNT_SLP_EN_IDX 13
#define ACPI_PM1_CNT_RSVD6_IDX 14
#define ACPI_PM1_CNT_RSVD7_IDX 15

#define ACPI_SLP_TYP_MAX 0b111

#define ACPI_PM1_CNT_SCI_EN_MASK (1 << ACPI_PM1_CNT_SCI_EN_IDX)
#define ACPI_PM1_CNT_BM_RLD_MASK (1 << ACPI_PM1_CNT_BM_RLD_IDX)
#define ACPI_PM1_CNT_GBL_RLS_MASK (1 << ACPI_PM1_CNT_GBL_RLS_IDX)
#define ACPI_PM1_CNT_SLP_TYP_MASK (ACPI_SLP_TYP_MAX << ACPI_PM1_CNT_SLP_TYP_IDX)
#define ACPI_PM1_CNT_SLP_EN_MASK (1 << ACPI_PM1_CNT_SLP_EN_IDX)

/*
 * SCI_EN is not in this mask even though the spec says it must be preserved.
 * This is because it's known to be bugged on some hardware that relies on
 * software writing 1 to it after resume (as indicated by a similar comment in
 * ACPICA)
 */
#define ACPI_PM1_CNT_PRESERVE_MASK ( \
    (1 << ACPI_PM1_CNT_RSVD0_IDX) |  \
    (1 << ACPI_PM1_CNT_RSVD1_IDX) |  \
    (1 << ACPI_PM1_CNT_RSVD2_IDX) |  \
    (1 << ACPI_PM1_CNT_RSVD3_IDX) |  \
    (1 << ACPI_PM1_CNT_RSVD4_IDX) |  \
    (1 << ACPI_PM1_CNT_RSVD5_IDX) |  \
    (1 << ACPI_PM1_CNT_IGN0_IDX ) |  \
    (1 << ACPI_PM1_CNT_RSVD6_IDX) |  \
    (1 << ACPI_PM1_CNT_RSVD7_IDX)    \
)

// PM2_CNT
#define ACPI_PM2_CNT_ARB_DIS_IDX 0
#define ACPI_PM2_CNT_ARB_DIS_MASK (1 << ACPI_PM2_CNT_ARB_DIS_IDX)

// All bits are reserved but this first one
#define ACPI_PM2_CNT_PRESERVE_MASK (~((u64)ACPI_PM2_CNT_ARB_DIS_MASK))

// SLEEP_CONTROL_REG
#define ACPI_SLP_CNT_RSVD0_IDX 0
#define ACPI_SLP_CNT_IGN0_IDX 1
#define ACPI_SLP_CNT_SLP_TYP_IDX 2
#define ACPI_SLP_CNT_SLP_EN_IDX 5
#define ACPI_SLP_CNT_RSVD1_IDX 6
#define ACPI_SLP_CNT_RSVD2_IDX 7

#define ACPI_SLP_CNT_SLP_TYP_MASK (ACPI_SLP_TYP_MAX << ACPI_SLP_CNT_SLP_TYP_IDX)
#define ACPI_SLP_CNT_SLP_EN_MASK (1 << ACPI_SLP_CNT_SLP_EN_IDX)

#define ACPI_SLP_CNT_PRESERVE_MASK ( \
    (1 << ACPI_SLP_CNT_RSVD0_IDX) |  \
    (1 << ACPI_SLP_CNT_IGN0_IDX)  |  \
    (1 << ACPI_SLP_CNT_RSVD1_IDX) |  \
    (1 << ACPI_SLP_CNT_RSVD2_IDX)    \
)

// SLEEP_STATUS_REG
#define ACPI_SLP_STS_WAK_STS_IDX 7

#define ACPI_SLP_STS_WAK_STS_MASK (1 << ACPI_SLP_STS_WAK_STS_IDX)

// All bits are reserved but this last one
#define ACPI_SLP_STS_PRESERVE_MASK (~((u64)ACPI_SLP_STS_WAK_STS_MASK))

#define ACPI_SLP_STS_CLEAR 1

UACPI_PACKED(struct acpi_dsdt {
    struct acpi_sdt_hdr hdr;
    u8 definition_block[];
})

UACPI_PACKED(struct acpi_ssdt {
    struct acpi_sdt_hdr hdr;
    u8 definition_block[];
})

/*
 * ACPI 6.5 specification:
 * Bit [0] - Set if the device is present.
 * Bit [1] - Set if the device is enabled and decoding its resources.
 * Bit [2] - Set if the device should be shown in the UI.
 * Bit [3] - Set if the device is functioning properly (cleared if device
 *           failed its diagnostics).
 * Bit [4] - Set if the battery is present.
 */
#define ACPI_STA_RESULT_DEVICE_PRESENT (1 << 0)
#define ACPI_STA_RESULT_DEVICE_ENABLED (1 << 1)
#define ACPI_STA_RESULT_DEVICE_SHOWN_IN_UI (1 << 2)
#define ACPI_STA_RESULT_DEVICE_FUNCTIONING (1 << 3)
#define ACPI_STA_RESULT_DEVICE_BATTERY_PRESENT (1 << 4)

#define ACPI_REG_DISCONNECT 0
#define ACPI_REG_CONNECT 1

UACPI_PACKED(struct acpi_ecdt {
    struct acpi_sdt_hdr hdr;
    struct acpi_gas ec_control;
    struct acpi_gas ec_data;
    u32 uid;
    u8 gpe_bit;
    char ec_id[];
})
// UACPI_EXPECT_SIZEOF(struct acpi_ecdt, 65);

#define ACPI_LARGE_ITEM (1 << 7)

#define ACPI_SMALL_ITEM_NAME_IDX 3
#define ACPI_SMALL_ITEM_NAME_MASK 0b1111
#define ACPI_SMALL_ITEM_LENGTH_MASK 0b111

#define ACPI_LARGE_ITEM_NAME_MASK 0b1111111

// Small items
#define ACPI_RESOURCE_IRQ 0x04
#define ACPI_RESOURCE_DMA 0x05
#define ACPI_RESOURCE_START_DEPENDENT 0x06
#define ACPI_RESOURCE_END_DEPENDENT 0x07
#define ACPI_RESOURCE_IO 0x08
#define ACPI_RESOURCE_FIXED_IO 0x09
#define ACPI_RESOURCE_FIXED_DMA 0x0A
#define ACPI_RESOURCE_VENDOR_TYPE0 0x0E
#define ACPI_RESOURCE_END_TAG 0x0F

// Large items
#define ACPI_RESOURCE_MEMORY24 0x01
#define ACPI_RESOURCE_GENERIC_REGISTER 0x02
#define ACPI_RESOURCE_VENDOR_TYPE1 0x04
#define ACPI_RESOURCE_MEMORY32 0x05
#define ACPI_RESOURCE_FIXED_MEMORY32 0x06
#define ACPI_RESOURCE_ADDRESS32 0x07
#define ACPI_RESOURCE_ADDRESS16 0x08
#define ACPI_RESOURCE_EXTENDED_IRQ 0x09
#define ACPI_RESOURCE_ADDRESS64 0x0A
#define ACPI_RESOURCE_ADDRESS64_EXTENDED 0x0B
#define ACPI_RESOURCE_GPIO_CONNECTION 0x0C
#define ACPI_RESOURCE_PIN_FUNCTION 0x0D
#define ACPI_RESOURCE_SERIAL_CONNECTION 0x0E
#define ACPI_RESOURCE_PIN_CONFIGURATION 0x0F
#define ACPI_RESOURCE_PIN_GROUP 0x10
#define ACPI_RESOURCE_PIN_GROUP_FUNCTION 0x11
#define ACPI_RESOURCE_PIN_GROUP_CONFIGURATION 0x12
#define ACPI_RESOURCE_CLOCK_INPUT 0x13

/*
 * Resources as encoded by the raw AML byte stream.
 * For decode API & human usable structures refer to uacpi/resources.h
 */
UACPI_PACKED(struct acpi_small_item {
    u8 type_and_length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_small_item,  1);

UACPI_PACKED(struct acpi_resource_irq {
    struct acpi_small_item common;
    u16 irq_mask;
    u8 flags;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_irq, 4);

UACPI_PACKED(struct acpi_resource_dma {
    struct acpi_small_item common;
    u8 channel_mask;
    u8 flags;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_dma, 3);

UACPI_PACKED(struct acpi_resource_start_dependent {
    struct acpi_small_item common;
    u8 flags;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_start_dependent, 2);

UACPI_PACKED(struct acpi_resource_end_dependent {
    struct acpi_small_item common;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_end_dependent, 1);

UACPI_PACKED(struct acpi_resource_io {
    struct acpi_small_item common;
    u8 information;
    u16 minimum;
    u16 maximum;
    u8 alignment;
    u8 length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_io, 8);

UACPI_PACKED(struct acpi_resource_fixed_io {
    struct acpi_small_item common;
    u16 address;
    u8 length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_fixed_io, 4);

UACPI_PACKED(struct acpi_resource_fixed_dma {
    struct acpi_small_item common;
    u16 request_line;
    u16 channel;
    u8 transfer_width;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_fixed_dma, 6);

UACPI_PACKED(struct acpi_resource_vendor_defined_type0 {
    struct acpi_small_item common;
    u8 byte_data[];
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_vendor_defined_type0, 1);

UACPI_PACKED(struct acpi_resource_end_tag {
    struct acpi_small_item common;
    u8 checksum;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_end_tag, 2);

UACPI_PACKED(struct acpi_large_item {
    u8 type;
    u16 length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_large_item, 3);

UACPI_PACKED(struct acpi_resource_memory24 {
    struct acpi_large_item common;
    u8 information;
    u16 minimum;
    u16 maximum;
    u16 alignment;
    u16 length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_memory24, 12);

UACPI_PACKED(struct acpi_resource_vendor_defined_type1 {
    struct acpi_large_item common;
    u8 byte_data[];
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_vendor_defined_type1, 3);

UACPI_PACKED(struct acpi_resource_memory32 {
    struct acpi_large_item common;
    u8 information;
    u32 minimum;
    u32 maximum;
    u32 alignment;
    u32 length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_memory32, 20);

UACPI_PACKED(struct acpi_resource_fixed_memory32 {
    struct acpi_large_item common;
    u8 information;
    u32 address;
    u32 length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_fixed_memory32, 12);

UACPI_PACKED(struct acpi_resource_address {
    struct acpi_large_item common;
    u8 type;
    u8 flags;
    u8 type_flags;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_address, 6);

UACPI_PACKED(struct acpi_resource_address64 {
    struct acpi_resource_address common;
    u64 granularity;
    u64 minimum;
    u64 maximum;
    u64 translation_offset;
    u64 length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_address64, 46);

UACPI_PACKED(struct acpi_resource_address32 {
    struct acpi_resource_address common;
    u32 granularity;
    u32 minimum;
    u32 maximum;
    u32 translation_offset;
    u32 length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_address32, 26);

UACPI_PACKED(struct acpi_resource_address16 {
    struct acpi_resource_address common;
    u16 granularity;
    u16 minimum;
    u16 maximum;
    u16 translation_offset;
    u16 length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_address16, 16);

UACPI_PACKED(struct acpi_resource_address64_extended {
    struct acpi_resource_address common;
    u8 revision_id;
    u8 rsvd;
    u64 granularity;
    u64 minimum;
    u64 maximum;
    u64 translation_offset;
    u64 length;
    u64 attributes;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_address64_extended, 56);

UACPI_PACKED(struct acpi_resource_extended_irq {
    struct acpi_large_item common;
    u8 flags;
    u8 num_irqs;
    u32 irqs[];
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_extended_irq, 5);

UACPI_PACKED(struct acpi_resource_generic_register {
    struct acpi_large_item common;
    u8 address_space_id;
    u8 bit_width;
    u8 bit_offset;
    u8 access_size;
    u64 address;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_generic_register, 15);

UACPI_PACKED(struct acpi_resource_gpio_connection {
    struct acpi_large_item common;
    u8 revision_id;
    u8 type;
    u16 general_flags;
    u16 connection_flags;
    u8 pull_configuration;
    u16 drive_strength;
    u16 debounce_timeout;
    u16 pin_table_offset;
    u8 source_index;
    u16 source_offset;
    u16 vendor_data_offset;
    u16 vendor_data_length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_gpio_connection, 23);

#define ACPI_SERIAL_TYPE_I2C 1
#define ACPI_SERIAL_TYPE_SPI 2
#define ACPI_SERIAL_TYPE_UART 3
#define ACPI_SERIAL_TYPE_CSI2 4
#define ACPI_SERIAL_TYPE_MAX ACPI_SERIAL_TYPE_CSI2

UACPI_PACKED(struct acpi_resource_serial {
    struct acpi_large_item common;
    u8 revision_id;
    u8 source_index;
    u8 type;
    u8 flags;
    u16 type_specific_flags;
    u8 type_specific_revision_id;
    u16 type_data_length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_serial, 12);

UACPI_PACKED(struct acpi_resource_serial_i2c {
    struct acpi_resource_serial common;
    u32 connection_speed;
    u16 slave_address;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_serial_i2c, 18);

UACPI_PACKED(struct acpi_resource_serial_spi {
    struct acpi_resource_serial common;
    u32 connection_speed;
    u8 data_bit_length;
    u8 phase;
    u8 polarity;
    u16 device_selection;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_serial_spi, 21);

UACPI_PACKED(struct acpi_resource_serial_uart {
    struct acpi_resource_serial common;
    u32 baud_rate;
    u16 rx_fifo;
    u16 tx_fifo;
    u8 parity;
    u8 lines_enabled;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_serial_uart, 22);

UACPI_PACKED(struct acpi_resource_serial_csi2 {
    struct acpi_resource_serial common;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_serial_csi2, 12);

UACPI_PACKED(struct acpi_resource_pin_function {
    struct acpi_large_item common;
    u8 revision_id;
    u16 flags;
    u8 pull_configuration;
    u16 function_number;
    u16 pin_table_offset;
    u8 source_index;
    u16 source_offset;
    u16 vendor_data_offset;
    u16 vendor_data_length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_pin_function, 18);

UACPI_PACKED(struct acpi_resource_pin_configuration {
    struct acpi_large_item common;
    u8 revision_id;
    u16 flags;
    u8 type;
    u32 value;
    u16 pin_table_offset;
    u8 source_index;
    u16 source_offset;
    u16 vendor_data_offset;
    u16 vendor_data_length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_pin_configuration, 20);

UACPI_PACKED(struct acpi_resource_pin_group {
    struct acpi_large_item common;
    u8 revision_id;
    u16 flags;
    u16 pin_table_offset;
    u16 source_lable_offset;
    u16 vendor_data_offset;
    u16 vendor_data_length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_pin_group, 14);

UACPI_PACKED(struct acpi_resource_pin_group_function {
    struct acpi_large_item common;
    u8 revision_id;
    u16 flags;
    u16 function;
    u8 source_index;
    u16 source_offset;
    u16 source_lable_offset;
    u16 vendor_data_offset;
    u16 vendor_data_length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_pin_group_function, 17);

UACPI_PACKED(struct acpi_resource_pin_group_configuration {
    struct acpi_large_item common;
    u8 revision_id;
    u16 flags;
    u8 type;
    u32 value;
    u8 source_index;
    u16 source_offset;
    u16 source_lable_offset;
    u16 vendor_data_offset;
    u16 vendor_data_length;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_pin_group_configuration, 20);

UACPI_PACKED(struct acpi_resource_clock_input {
    struct acpi_large_item common;
    u8 revision_id;
    u16 flags;
    u16 divisor;
    u32 numerator;
    u8 source_index;
})
// UACPI_EXPECT_SIZEOF(struct acpi_resource_clock_input, 13);



#endif  /*__ALINIX_UACPI_ACPI_ACPI_H__INCLUDED*/