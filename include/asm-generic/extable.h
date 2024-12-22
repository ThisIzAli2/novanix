#ifndef __ASM_GENERIC_EXTABLE_H
#define __ASM_GENERIC_EXTABLE_H

struct exception_table_entry{
    unsigned long insn,fixup;
};


#endif // __ASM_GENERIC_EXTABLE_H