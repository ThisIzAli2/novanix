#ifndef _HEISEN_GUI_DEF_H
#define _HEISEN_GUI_DEF_H

#include <heisen/typing.h>


#if defined(__midl)
typedef struct {
    unsigned long data1;
    unsigned short data2;
    unsigned short data3;
    byte data4[8];
}GUID;
#else
typedef struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
} GUID;

#endif

#endif // _HEISEN_GUI_DEF_H