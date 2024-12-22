#ifndef _HEISEN_HUGETLB_INLINE_H
#define _HEISEN_HUGETLB_INLINE_H

#ifdef CONFIG_HUGETLB_PAGE

#include <heisen/mm.h>

static inline bool is_vm_hugetlb_page(struct vm_area_struct *vma)
{
	return !!(vma->vm_flags & VM_HUGETLB);
}

#else

static inline bool is_vm_hugetlb_page(struct vm_area_struct *vma)
{
	return false;
}

#endif

#endif