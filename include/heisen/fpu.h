#ifndef _HEISEN_FPU_H
#define _HEISEN_FPU_H
void fp_platform_init(void);

int fp_platform_getstatesize(void);

int fp_platform_getalign(void);

void fp_platform_getstate(void *buf);

void fp_platform_setstate(void *buf);

void fp_platform_getdefaultstate(void *buf);

#endif // _HEISEN_FPU_H