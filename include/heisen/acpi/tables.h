#ifndef PRIV_ACPI_TABLES_DRIVER_H_HESIEN
#define PRIV_ACPI_TABLES_DRIVER_H_HESIEN


#include <heisen/typing.h>

#define MADT_SIG "APIC" //!< MADT
#define FADT_SIG "FACP" //!< FADT
#define HPET_SIG "HPET" //!< HPET Table
#define MCFG_SIG "MCFG" //!< MCFG Table


/**
 * Rsdt pointer table
*/

typedef struct {
    char signature[8];
    uint8_t checkSum;
    char OEMID[6];
    uint8_t Revision;
    uint32_t RsdtAddress;
} __attribute__((packed)) RSDPDescriptor;


typedef struct {
    RSDPDescriptor firstPart;
    uint32_t len;
    uint64_t XsdtAddress;
    uint8_t ExtendedChecksum;
    uint8_t reserved[3];
};


#endif // PRIV_ACPI_TABLES_DRIVER_H_HEISEN