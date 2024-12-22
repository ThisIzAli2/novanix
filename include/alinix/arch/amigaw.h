/**
 * @file amigaw.h
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
 *  - Kernel arch section header file.
*/
#ifndef __ALINIX_KERNEL_AMIGAW_H
#define __ALINIX_KERNEL_AMIGAW_H


#define PIA_REG_PADWIDTH 255

#define zTwoBase (0x80000000)
#define ZTWO_PADDR(x) (((unsigned long)(x))-zTwoBase)
#define ZTWO_VADDR(x) ((void *)(((unsigned long)(x))+zTwoBase))




struct CUSTOM {
    unsigned short bltddat;
    unsigned short dmaconr;
    unsigned short vposr;
    unsigned short vhposr;
    unsigned short dskdatr;
    unsigned short joy0dat;
    unsigned short joy1dat;
    unsigned short clxdat;
    unsigned short adkconr;
    unsigned short pot0dat;
    unsigned short pot1dat;
    unsigned short potgor;
    unsigned short serdatr;
    unsigned short dskbytr;
    unsigned short intenar;
    unsigned short intreqr;
    unsigned char  *dskptr;
    unsigned short dsklen;
    unsigned short dskdat;
    unsigned short refptr;
    unsigned short vposw;
    unsigned short vhposw;
    unsigned short copcon;
    unsigned short serdat;
    unsigned short serper;
    unsigned short potgo;
    unsigned short joytest;
    unsigned short strequ;
    unsigned short strvbl;
    unsigned short strhor;
    unsigned short strlong;
    unsigned short bltcon0;
    unsigned short bltcon1;
    unsigned short bltafwm;
    unsigned short bltalwm;
    unsigned char  *bltcpt;
    unsigned char  *bltbpt;
    unsigned char  *bltapt;
    unsigned char  *bltdpt;
    unsigned short bltsize;
    unsigned char  pad2d;
    unsigned char  bltcon0l;
    unsigned short bltsizv;
    unsigned short bltsizh;
    unsigned short bltcmod;
    unsigned short bltbmod;
    unsigned short bltamod;
    unsigned short bltdmod;
    unsigned short spare2[4];
    unsigned short bltcdat;
    unsigned short bltbdat;
    unsigned short bltadat;
    unsigned short spare3[3];
    unsigned short deniseid;
    unsigned short dsksync;
    unsigned short *cop1lc;
    unsigned short *cop2lc;
    unsigned short copjmp1;
    unsigned short copjmp2;
    unsigned short copins;
    unsigned short diwstrt;
    unsigned short diwstop;
    unsigned short ddfstrt;
    unsigned short ddfstop;
    unsigned short dmacon;
    unsigned short clxcon;
    unsigned short intena;
    unsigned short intreq;
    unsigned short adkcon;
    struct {
	unsigned short	*audlc;
	unsigned short audlen;
	unsigned short audper;
	unsigned short audvol;
	unsigned short auddat;
	unsigned short audspare[2];
    } aud[4];
    unsigned char  *bplpt[8];
    unsigned short bplcon0;
    unsigned short bplcon1;
    unsigned short bplcon2;
    unsigned short bplcon3;
    unsigned short bpl1mod;
    unsigned short bpl2mod;
    unsigned short bplcon4;
    unsigned short clxcon2;
    unsigned short bpldat[8];
    unsigned char  *sprpt[8];
    struct {
	unsigned short pos;
	unsigned short ctl;
	unsigned short dataa;
	unsigned short datab;
    } spr[8];
    unsigned short color[32];
    unsigned short htotal;
    unsigned short hsstop;
    unsigned short hbstrt;
    unsigned short hbstop;
    unsigned short vtotal;
    unsigned short vsstop;
    unsigned short vbstrt;
    unsigned short vbstop;
    unsigned short sprhstrt;
    unsigned short sprhstop;
    unsigned short bplhstrt;
    unsigned short bplhstop;
    unsigned short hhposw;
    unsigned short hhposr;
    unsigned short beamcon0;
    unsigned short hsstrt;
    unsigned short vsstrt;
    unsigned short hcenter;
    unsigned short diwhigh;
    unsigned short spare4[11];
    unsigned short fmode;
};



struct CIA {
    unsigned char pra;		char pad0[0xff];
    unsigned char prb;		char pad1[0xff];
    unsigned char ddra;		char pad2[0xff];
    unsigned char ddrb;		char pad3[0xff];
    unsigned char talo;		char pad4[0xff];
    unsigned char tahi;		char pad5[0xff];
    unsigned char tblo;		char pad6[0xff];
    unsigned char tbhi;		char pad7[0xff];
    unsigned char todlo;	char pad8[0xff];
    unsigned char todmid;	char pad9[0xff];
    unsigned char todhi;	char pada[0x1ff];
    unsigned char sdr;		char padb[0xff];
    unsigned char icr;		char padc[0xff];
    unsigned char cra;		char padd[0xff];
    unsigned char crb;		char pade[0xff];
};


#define CUSTOM_PHYSADDR     (0xdff000)
#define amiga_custom ((*(volatile struct CUSTOM *)(zTwoBase+CUSTOM_PHYSADDR)))

struct pia {
	union {
		volatile unsigned char pra;
		volatile unsigned char ddra;
	} ua;
	unsigned char pad1[PIA_REG_PADWIDTH];
	volatile unsigned char cra;
	unsigned char pad2[PIA_REG_PADWIDTH];
	union {
		volatile unsigned char prb;
		volatile unsigned char ddrb;
	} ub;
	unsigned char pad3[PIA_REG_PADWIDTH];
	volatile unsigned char crb;
	unsigned char pad4[PIA_REG_PADWIDTH];
};


#define CIAA_PHYSADDR	  (0xbfe001)
#define CIAB_PHYSADDR	  (0xbfd000)
#define ciaa   ((*(volatile struct CIA *)(zTwoBase + CIAA_PHYSADDR)))
#define ciab   ((*(volatile struct CIA *)(zTwoBase + CIAB_PHYSADDR)))

#endif /*__ALINIX_KERNEL_AMIGAW_H*/