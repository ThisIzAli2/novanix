/**
 * @author Ali Mirmohammad
 * @file system.h
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
 * @abstraction:
 *  - System header file for the kernel basic system settings.
*/


#ifndef __ALINIX_KERNEL_SYSTEM_HEADER_H
#define __ALINIX_KERNEL_SYSTEM_HEADER_H

#include <alinix/enums.h>
#include <alinix/types.h>

static bool gdbEnabled;
static bool Initialized;
#define SYSTEM_INFO_ADDR 0xBFFEE000


/////////////////////////////////
/**
 * @brief Macros defined for the System clock
*/
#define	NBUF	15		/* size of buffer cache */
#define	NINODE	100		/* number of in core inodes */
#define	NFILE	100		/* number of in core file structures */
#define	NMOUNT	5		/* number of mountable file systems */
#define	NEXEC	3		/* number of simultaneous exec's */
#define	MAXMEM	(64*32)		/* max core per process - first # is Kw */
#define	SSIZE	20		/* initial stack size (*64 bytes) */
#define	SINCR	20		/* increment of stack (*64 bytes) */
#define	NOFILE	15		/* max open files per process */
#define	CANBSIZ	256		/* max size of typewriter line */
#define	CMAPSIZ	100		/* size of core allocation area */
#define	SMAPSIZ	100		/* size of swap allocation area */
#define	NCALL	20		/* max simultaneous time callouts */
#define	NPROC	50		/* max number of processes */
#define	NTEXT	40		/* max number of pure texts */
#define	NCLIST	100		/* max total clist size */
#define	HZ	60		/* Ticks/second of the clock */


struct callo{
    int c_time;
    int c_arg;
    int	(*c_func)();	/* routine */
};

#endif /*__ALINIX_KERNEL_SYSTEM_HEADER_H*/