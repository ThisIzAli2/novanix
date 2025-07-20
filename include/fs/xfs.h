/**
 * @author Ali Mirmohammad
 * @file xfs.h
 ** This file is part of Novanix.

**Novanix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**Novanix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with Novanix. If not, see <https://www.gnu.org/licenses/>.
*/

#define BLOCK_SIZE 512  // 512 bytes per block
#define NUM_BLOCKS 1024 // Number of blocks in the file system
#define NUM_INODES 128  // Number of inodes

// Superblock structure
struct Superblock {
    unsigned int magic;        // Magic number to identify the file system
    unsigned int block_size;   // Block size
    unsigned int num_blocks;   // Total number of blocks
    unsigned int num_inodes;   // Number of inodes
    unsigned int inode_table;  // Start of inode table
    unsigned int data_start;   // Start of data blocks
};

// Inode structure
struct Inode {
    unsigned int file_size;      // Size of the file
    unsigned int block_pointers[8]; // Pointers to data blocks (8 blocks max)
    unsigned short mode;         // File permissions (simplified)
    unsigned short uid;          // User ID
    unsigned short gid;          // Group ID
    unsigned int atime;          // Last access time
    unsigned int mtime;          // Last modification time
    unsigned int ctime;          // Creation time
};

// Simple File System class
class SimpleFS {
public:
    Superblock superblock;
    Inode inodes[NUM_INODES];
    char blocks[NUM_BLOCKS][BLOCK_SIZE]; // Simulate disk with blocks

    SimpleFS() {
        // Initialize blocks and inodes to zero
        for (int i = 0; i < NUM_BLOCKS; i++) {
            for (int j = 0; j < BLOCK_SIZE; j++) {
                blocks[i][j] = 0;
            }
        }
        for (int i = 0; i < NUM_INODES; i++) {
            inodes[i] = Inode();
        }

        superblock.magic = 0x12345678;  // Magic number for our file system
        superblock.block_size = BLOCK_SIZE;
        superblock.num_blocks = NUM_BLOCKS;
        superblock.num_inodes = NUM_INODES;
        superblock.inode_table = sizeof(Superblock); // Inode table starts after the superblock
        superblock.data_start = superblock.inode_table + NUM_INODES * sizeof(Inode); // Data starts after the inode table
    }

    void format() {
        // Format the file system (initialize the superblock and inode table)
        // Initialize superblock, inode table, and free block map
        for (int i = 0; i < NUM_BLOCKS; i++) {
            for (int j = 0; j < BLOCK_SIZE; j++) {
                blocks[i][j] = 0;  // Clear all blocks
            }
        }
        blocks[0][0] = superblock.magic & 0xFF;  // Write magic number to the first block
        blocks[0][1] = (superblock.magic >> 8) & 0xFF;
        blocks[0][2] = (superblock.magic >> 16) & 0xFF;
        blocks[0][3] = (superblock.magic >> 24) & 0xFF;
    }

    void write_inode(unsigned int inode_num, Inode inode) {
        // Write an inode to the inode table
        if (inode_num < NUM_INODES) {
            inodes[inode_num] = inode;
        }
    }

    Inode read_inode(unsigned int inode_num) {
        // Read an inode from the inode table
        if (inode_num < NUM_INODES) {
            return inodes[inode_num];
        }
        return Inode();  // Return empty inode if not found
    }

    void write_data_block(unsigned int block_num, char* data) {
        // Write data to a block
        if (block_num < NUM_BLOCKS) {
            for (unsigned int i = 0; i < BLOCK_SIZE; i++) {
                blocks[block_num][i] = data[i];
            }
        }
    }

    void read_data_block(unsigned int block_num, char* buffer) {
        // Read data from a block
        if (block_num < NUM_BLOCKS) {
            for (unsigned int i = 0; i < BLOCK_SIZE; i++) {
                buffer[i] = blocks[block_num][i];
            }
        }
    }

    void create_file(const char* filename) {
        // Find a free inode
        unsigned int inode_num = -1;
        for (unsigned int i = 0; i < NUM_INODES; i++) {
            if (inodes[i].file_size == 0) {
                inode_num = i;
                break;
            }
        }

        if (inode_num == -1) {
            return;  // No free inodes available
        }

        // Create a new inode
        Inode new_inode;
        new_inode.file_size = 0;
        new_inode.mode = 0644;  // Default file permissions
        new_inode.uid = 1000;   // Default user ID
        new_inode.gid = 1000;   // Default group ID

        // Assign a data block (for simplicity, we only allocate one block)
        unsigned int block_num = 1;  // Assume block 1 is free
        new_inode.block_pointers[0] = block_num;

        // Write the inode to the inode table
        write_inode(inode_num, new_inode);
    }

    void write_to_file(unsigned int inode_num, char* data, unsigned int size) {
        // Write data to a file
        Inode inode = read_inode(inode_num);
        unsigned int block_num = inode.block_pointers[0];

        // Write data to the first data block
        write_data_block(block_num, data);

        // Update file size
        inode.file_size = size;
        write_inode(inode_num, inode);
    }

    void read_from_file(unsigned int inode_num, char* buffer) {
        // Read data from a file
        Inode inode = read_inode(inode_num);
        unsigned int block_num = inode.block_pointers[0];

        // Read data from the first data block
        read_data_block(block_num, buffer);
    }
};
