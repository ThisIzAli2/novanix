#ifndef _HEISEN_ELF_KERNEL_INCLUDE_H
#define _HEISEN_ELF_KERNEL_INCLUDE_H


#include <heisen/typing.h>

#define EI_NIDENT 16

struct elf32_elf_header{
    uint8_t e_indent[EI_NIDENT];
    uint16_t e_type;
    uint16_t e_machine;      /* Architecture */
    uint32_t e_version;      /* Object file version */
    uint32_t e_entry;        /* Entry point virtual address */
    uint32_t e_phoff;        /* Program header table file offset */
    uint32_t e_shoff;        /* Section header table file offset */
    uint32_t e_flags;        /* Processor-specific flags */
    uint16_t e_ehsize;       /* ELF header size in bytes */
    uint16_t e_phentsize;    /* Program header table entry size */
    uint16_t e_phnum;        /* Program header table entry count */
    uint16_t e_shentsize;    /* Section header table entry size */
    uint16_t e_shnum;        /* Section header table entry count */
    uint16_t e_shstrndx;     /* Section header string table index */
};


struct elf32_program_header {
    uint32_t pType;
    uint32_t pOffset;
    uint32_t p_vaddr;        /* Segment virtual address */
    uint32_t p_paddr;        /* Segment physical address */
    uint32_t p_filesz;       /* Segment size in file */
    uint32_t p_memsz;        /* Segment size in memory */
    uint32_t p_flags;        /* Segment flags */
    uint32_t p_align;        /* Segment alignment */
};

#define ELF32_IDENTITY_ELF 0x464c457f
#define ELF32_CLASS_ELF32 0x1
#define ELF32_ENDIAN_LITTLE 0x1

#define ELF32_TYPE_EXEC 0x2
#define ELF32_MACHINE_I386 0x3 

#define PROGRAM_TYPE_LOAD 1
#define PROGRAM_READ (1 << 2)
#define PROGRAM_WRITE (1 << 1)
#define PROGRAM_EXECUTE (1 << 0)
int
validate_static_elf32_format(uint8_t * mem, int32_t length);

int32_t
load_static_elf32(uint8_t * mem, uint8_t * command, uint32_t * ptask_id);


#endif // _HEISEN_ELF_KERNEL_INCLUDE_H