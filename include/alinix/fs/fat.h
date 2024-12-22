/**
 * @file fat.h
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


#ifndef __ALINIX_KERNEL_FS_FAT_H
#define __ALINIX_KERNEL_FS_FAT_H

// Cluster Special Values
#define CLUSTER_END_32  0x0FFFFFF8
#define CLUSTER_BAD_32  0x0FFFFFF7
#define CLUSTER_FREE_32 0x00000000

#define CLUSTER_END_16  0xFFF8
#define CLUSTER_BAD_16  0xFFF7
#define CLUSTER_FREE_16 0x0000

#define CLUSTER_END_12  0xFF8
#define CLUSTER_BAD_12  0xFF7
#define CLUSTER_FREE_12 0x000

// For easy Access
#define CLUSTER_END     (this->FatType == FAT12 ? CLUSTER_END_12 : (this->FatType == FAT16 ? CLUSTER_END_16 : CLUSTER_END_32))
#define CLUSTER_FREE    (this->FatType == FAT12 ? CLUSTER_FREE_12 : (this->FatType == FAT16 ? CLUSTER_FREE_16 : CLUSTER_FREE_32))
#define CLUSTER_BAD     (this->FatType == FAT12 ? CLUSTER_BAD_12 : (this->FatType == FAT16 ? CLUSTER_BAD_16 : CLUSTER_BAD_32))

#define ATTR_READ_ONLY  0x01
#define ATTR_HIDDEN 	0x02
#define ATTR_SYSTEM     0x04
#define ATTR_VOLUME_ID  0x08
#define ATTR_DIRECTORY	0x10
#define ATTR_ARCHIVE    0x20
#define ATTR_LONG_NAME 	(ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID)

#define ENTRY_END       0x00
#define ENTRY_UNUSED    0xE5
#define LFN_ENTRY_END   0x40


#include <alinix/types.h>
#include <alinix/enums.h>
#include <alinix/node.h>

Disk* Disk_create(uint32_t controllerIndex, void* controller, DiskType type, uint64_t size, uint32_t blocks, uint32_t blocksize);


char Disk_ReadSector(Disk* disk, uint32_t lba, uint8_t* buf);
char Disk_WriteSector(Disk* disk, uint32_t lba, uint8_t* buf);


struct FAT32_FSInfo
{
    uint32_t    signature1;
    uint8_t     reserved1[480];
    uint32_t    signature2;
    uint32_t    lastFreeCluster;
    uint32_t    startSearchCluster;
    uint8_t     reserved2[12];
    uint32_t    signature3;
} __attribute__((packed));

enum FATType
{
    FAT12,
    FAT16,
    FAT32
};
struct FAT32_BPB
{
    uint8_t     bootCode[3];
    uint8_t     Oem_Id[8];
    uint16_t    bytesPerSector;
    uint8_t     SectorsPerCluster;
    uint16_t    ReservedSectors;
    uint8_t     NumOfFats;
    uint16_t    NumDirEntries;
    uint16_t    TotalSectorsSmall;
    uint8_t     MediaDescriptorType;
    uint16_t    SectorsPerFat12_16;
    uint16_t    SectorsPerTrack;
    uint16_t    NumHeads;
    uint32_t    HiddenSectors;
    uint32_t    TotalSectorsBig;

    //Beginning of fat32 values
    uint32_t    SectorsPerFat32;
    uint16_t    Flags;
    uint16_t    FATVersionNum;
    uint32_t    RootDirCluster;
    uint16_t    FSInfoSector;
    uint16_t    BackupBootSector;
    uint8_t     Reserved[12];
    uint8_t     DriveNum;
    uint8_t     WinNTFlags;
    uint8_t     Signature;
    uint32_t    VolumeIDSerial;
    uint8_t     VolumeLabel[11];
    uint8_t     SystemIDString[8];
    uint8_t     BootCode[420];
    uint16_t    BootSignature;
} __attribute__((packed));



struct DirectoryEntry
{
    uint8_t     FileName[11];       // 8.3 Filename
    uint8_t     Attributes;         // Entry Flags
    uint8_t     Reserved;           // Not Used
    uint8_t     CreationTimeTenth;  // Creation time in tenths of a second. Range 0-199 inclusive. 
    uint16_t    CreationTime;       // The time that the file was created. Multiply Seconds by 2. 
    uint16_t    CreationDate;       // The date on which the file was created. 
    uint16_t    AccessDate;         // Last accessed date. Same format as the creation date. 
    uint16_t    HighFirstCluster;   // High word of this entry’s first cluster number (always 0 for a FAT12 or FAT16 volume).
    uint16_t    ModifyTime;         // Last modification time. Same format as the creation time. 
    uint16_t    ModifyDate;         // Last modification date. Same format as the creation date. 
    uint16_t    LowFirstCluster;    // The low 16 bits of this entry's first cluster number. Use this number to find the first cluster for this entry. 
    uint32_t    FileSize;           // The size of the file in bytes
} __attribute__((packed));

struct LFNEntry
{
    uint8_t entryIndex;             // The order of this entry in the sequence of long file name entries.
    uint8_t namePart1[10];          // The first 5, 2-byte characters of this entry. 
    uint8_t Attributes;             // Attribute. Always equals 0x0F. (the long file name attribute) 
    uint8_t reserved_1;             // Long entry type. Zero for name entries. 
    uint8_t checksum;               // Checksum generated of the short file name when the file was created. 
    uint8_t namePart2[12];          // The next 6, 2-byte characters of this entry. 
    uint16_t reserved_2;            // Always Zero
    uint8_t namePart3[4];           // The final 2, 2-byte characters of this entry. 
} __attribute__((packed));

typedef struct {
    enum FATType FatType;
    char* FatTypeString ;
    uint16_t bytesPerSector ;        // Bytes per sector, usually 512
    uint32_t rootDirSectors ;        // How many sectors does the root directory use?
    uint8_t sectorsPerCluster ;      // How many sectors does one cluster contain?
    uint32_t clusterSize ;           // Size of one cluster in bytes

    uint32_t firstDataSector ;       // LBA Address of first sector of the data region
    uint32_t firstFatSector ;        // The first sector in the File Allocation Table
    uint32_t rootDirCluster ;        // Cluster of the root directory, only used by FAT32
    uint32_t totalClusters ;         // Total amount of clusters used by data region

    uint8_t* readBuffer ;            // Buffer used for reading the disk
    struct FAT32_FSInfo fsInfo;                // Structure used by FAT32 for extra info
    ////////////////////////////////////////////////////////////////
    // All the Extra functions should be defined here
    ////////////////////////////////////////////////////////////////
}FAT;

uint32_t ClusterToSector(uint32_t cluster);

// Reads the FAT table and returns the value for the specific cluster
uint32_t ReadTable(uint32_t cluster);

// Writes a new value into the FAT table for the cluster
void WriteTable(uint32_t cluster, uint32_t value);

// Allocate a new cluster in the FAT Table
uint32_t AllocateCluster();

// Clear the data of a cluster
void ClearCluster(uint32_t cluster);

// Parse a list of long file name entries, also pass the 8.3 entry for the checksum
char* ParseLFNEntries(List* entries, struct DirectoryEntry sfnEntry);

// Turn a FAT filename into a readable one
char* ParseShortFilename(char* fatName);

// Calculate checksum for 8.3 filename
uint8_t Checksum(char* filename);

///////////////////////
/// Read Functions
///////////////////////

List  GetDirectoryEntries(uint32_t dirCluster, bool rootDirectory );

// Search in a directory for a specific entry and return this entry if found
struct FATEntryInfo* SeachInDirectory(char* name, uint32_t dirCluster, bool rootDirectory );

// Return the entry specified by a complete filename path
struct FATEntryInfo* GetEntryByPath(char* path);

///////////////////////
/// Write Functions
///////////////////////

// Create a list of LFN entries from a filename
List CreateLFNEntriesFromName(char* name, int num, uint8_t checksum);

// Create a 8.3 filename from a regular filename
char* CreateShortFilename(char* name);

// Write a series of LFN entries to the disk
bool WriteLongFilenameEntries(List* entries, uint32_t targetCluster, uint32_t targetSector, uint32_t sectorOffset, bool rootDirectory);

// Write a regulair Directory entry to the disk
bool WriteDirectoryEntry(struct DirectoryEntry entry, uint32_t targetSector, uint32_t sectorOffset, bool rootDirectory);

// Find a starting point for entries in a directory. Returns cluster and sector offset inside cluster.
bool FindEntryStartpoint(uint32_t cluster, uint32_t entryCount, bool rootdir, uint32_t* targetCluster, uint32_t* targetSector, uint32_t* sectorOffset);

// Create a entry in the directory specified by parentCluster
// Returns pointer to created entry present in readbuffer
struct DirectoryEntry* CreateEntry(uint32_t parentCluster, char* name, uint8_t attr, bool rootdir, uint32_t targetCluster, uint32_t* sectorPlaced);

// Easy way to create a new file or directory by path, is almost the same for file/directory creation
int CreateNewDirFileEntry(const char* path, uint8_t attributes);

// Modify a existing entry on disk by applying the variables from newVersion
// Be Carefoul when using this to change cluster numbers and filenames
// You should get the original entry, modify some stuff, and then pass it as newVersion
bool ModifyEntry(struct FATEntryInfo* entry, struct DirectoryEntry newVersion);

///////////////////////
/// Time/Date Functions
///////////////////////

// Returns current time in fat format
uint16_t FatTime();

// Returns current date in fat format
uint16_t FatDate();
#endif /*__ALINIX_KERNEL_FS_FAT_H*/