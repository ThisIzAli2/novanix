/**
 * @author Ali Mirmohammad
 * @file smbios.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 * @file smbios.h
 * @abstraction:
 *  - Kernel SM bios header file implementation.
*/

#ifndef __ALINIX_KERNEL_SMBIOS_H
#define __ALINIX_KERNEL_SMBIOS_H

#include <alinix/types.h>

enum SMBIOSTableType 
{
    BIOSInformation = 0,
    SystemInformation = 1,
    BaseBoardInformation = 2,
    EnclosureInformation = 3,
    ProcessorInformation = 4,
    MemoryControllerInformation = 5,
    MemoryModuleInformation = 6,
    CacheInformation = 7,
    PortConnectorInformation = 8,
    SystemSlotsInformation = 9,
    OnBoardDevicesInformation = 10,
    OEMStrings = 11,
    SystemConfigurationOptions = 12,
    BIOSLanguageInformation = 13,
    GroupAssociations = 14,
    SystemEventLog = 15,
    PhysicalMemoryArray = 16,
    MemoryDevice = 17,
    MemoryErrorInformation = 18,
    MemoryArrayMappedAddress = 19,
    MemoryDeviceMappedAddress = 20,
    SystemBootInformation = 32,
    EndOfTable = 127
};

struct SMBIOSTag
{
    uint8_t type;
    uint8_t length;
    uint16_t handle;
} __attribute__((packed));

struct SMBIOSBiosInfo 
{
    uint8_t vendor;
    uint8_t version;
    uint16_t startSegment;
    uint8_t releaseDate;
    uint8_t romSize;
    uint64_t characteristics;
    // for 2.4+
    uint8_t extensionChar1;
    uint8_t extensionChar2;
    uint8_t biosMajorRelease;
    uint8_t biosMinorRelease;
    uint8_t controllerMajorRelease;
    uint8_t controllerMinorRelease;
} __attribute__((packed));

struct SMBIOSSystemInfo 
{
    uint8_t manufacturer;
    uint8_t productName;
    uint8_t version;
    uint8_t serialNumber;

    struct
    {
        uint32_t time_low;
        uint16_t time_mid;
        uint16_t timeHiAndVersion;
        uint8_t clockSeqHiAndReserved;
        uint8_t clockSeqLow;
        uint8_t node[6];
    } uuid;

    uint8_t wakeupType;

    uint8_t sku;
    uint8_t family;
} __attribute__((packed));


struct SMBIOSBaseBoardInformation 
{
    uint8_t manufacturer;
    uint8_t product;
    uint8_t version;
    uint8_t serial;
    uint8_t assertTag;
    uint8_t features;
    uint8_t locationInChassis;
    uint16_t chassisHandle;
    uint8_t boardType;
    uint8_t numObjHandles;
    uint16_t objectHandles[1]; 
} __attribute__((packed));

struct SMBIOSSystemEnclosureInformation 
{
    uint8_t manufacturer;
    uint8_t type;
    uint8_t version;
    uint8_t serialNumber;
    uint8_t assetTag;
    uint8_t bootupState;
    uint8_t psuState;
    uint8_t thermalState;
    uint8_t securityStatus;
    uint8_t oemSpecific[4];
    uint8_t height;
    uint8_t numOfPowerCords;
    uint8_t numOfElements;
    uint8_t elementRecordLength;

    struct element
    {
        uint8_t type;
        uint8_t minimum;
        uint8_t maximum;
    } elements[1];
} __attribute__((packed));

struct SMBIOSProcessorInformation 
{
    uint8_t socketDesignation;
    uint8_t processorType;
    uint8_t processorFamily;
    uint8_t manufacturer;
    uint64_t processorID;
    uint8_t version;
    uint8_t voltage;
    uint16_t clock;
    uint16_t maxSpeed;
    uint16_t currentSpeed;
    uint8_t status;
    uint8_t upgrade;
    uint16_t L1;
    uint16_t L2;
    uint16_t L3;

    //2.3
    uint8_t serialNumber;
    uint8_t assertTag;
    uint8_t partNumber;

    //2.5
    uint8_t totalCores;
    uint8_t activeCores;
    uint8_t threads;
    uint16_t characteristics;
} __attribute__((packed));

struct SMBIOSCacheInformation 
{
    uint8_t socketDesignation;
    uint16_t cacheConfiguration;
    uint16_t maximumCacheSize;
    uint16_t installedSize;
    uint16_t supportedSRAMType;
    uint16_t currentSRAMType;

    //2.1+
    uint8_t cacheSpeed;
    uint8_t errorCorrectionType;
    uint8_t systemCacheType;
    uint8_t associativity;

    //3.1+
    uint32_t maximumCacheSize2;
    uint32_t installedSize2;
} __attribute__((packed));

struct SMBIOSSystemSlotInformation 
{
    uint8_t slotDesignation;
    uint8_t slotType;
    uint8_t slotDataBusWidth;
    uint8_t currentUsage;
    uint8_t slotLength;
    uint16_t slotID;
    uint8_t slotCharacteristics1;

    //2.1+
    uint8_t slotCharacteristics2;

    //2.6+
    uint16_t segmentGroupNumber;
    uint8_t busNumber;
    uint8_t deviceFunctionNumber;

    //3.2
    uint8_t dataBusWidth;
} __attribute__((packed));

struct SMBIOSPhysicalMemoryArray 
{
    //2.1+
    uint8_t location;
    uint8_t use;
    uint8_t memoryErrorCorrection;
    uint32_t maximumCapacity;
    uint16_t memoryErrorInformationHandle;
    uint16_t numberOfMemoryDevices;

    //2.7+
    uint64_t extendedMaximumCapacity;
} __attribute__((packed));

struct SMBIOSMemoryDevice 
{
    //2.1+
    uint16_t memoryArrayHandle;
    uint16_t memoryErrorInformationHandle;
    uint16_t totalWidth;
    uint16_t dataWidth;
    uint16_t size;
    uint8_t formFactor;
    uint8_t deviceSet;
    uint8_t deviceLocator;
    uint8_t bankLocator;
    uint8_t memoryType;
    uint16_t typeDetail;

    //2.3+
    uint16_t speed;
    uint8_t manufacturer;
    uint8_t serialNumber;
    uint8_t assetTag;
    uint8_t partNumber;

    //2.6+
    uint8_t attributes;

    //2.7+
    uint32_t extendedSize;
    uint16_t configuredMemorySpeed;

    //2.8+
    uint16_t minimumVoltage;
    uint16_t maximumVoltage;
    uint16_t configuredVoltage;

    //3.2+
    uint8_t memoryTechnology;
    uint16_t memoryOperatingModeCapability;
    uint8_t firwareVersion;
    uint16_t moduleManufacturerID;
    uint16_t moduleProductID;
    uint16_t memorySubsystemControllerManufacturerID;
    uint16_t memorySubsystemControllerProductID;
    uint64_t nonVolatileSize;
    uint64_t volatileSize;
    uint64_t cacheSize;
    uint64_t logicalSize;
} __attribute__((packed));

struct SMBIOSBootInformation 
{
    uint8_t reserved[6];
    uint8_t bootStatus;
} __attribute__((packed));

struct SMBIOSEntryPoint
{
    char EntryPointString[4];               //This is _SM_
    uint8_t Checksum;               //This value summed with all the values of the table, should be 0 (overflow)
    uint8_t Length;                 //Length of the Entry Point Table. Since version 2.1 of SMBIOS, this is 0x1F
    uint8_t MajorVersion;           //Major Version of SMBIOS
    uint8_t MinorVersion;           //Minor Version of SMBIOS
    uint16_t MaxStructureSize;      //Maximum size of a SMBIOS Structure (we will se later)
    uint8_t EntryPointRevision;     //...
    char FormattedArea[5];                  //...
    char EntryPointString2[5];              //This is _DMI_
    uint8_t Checksum2;              //Checksum for values from EntryPointString2 to the end of table
    uint16_t TableLength;           //Length of the Table containing all the structures
    uint32_t TableAddress;	        //Address of the Table
    uint16_t NumberOfStructures;    //Number of structures in the table
    uint8_t BCDRevision;            //Unused
} __attribute__((packed));



#endif /*__ALINIX_KERNEL_SMBIOS_H*/