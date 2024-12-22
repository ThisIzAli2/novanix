/**
 * @file fcntl.h
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
 *  - Kernel FCNTL implementation for ASM section.
*/
#ifndef __ALINIX_KERNEL_ASM_FCNTL_INCLUDED_H
#define __ALINIX_KERNEL_ASM_FCNTL_INCLUDED_H

#define O_ACCMODE	00000003
#define O_RDONLY	00000000
#define O_WRONLY	00000001
#define O_RDWR		00000002
#ifndef O_CREAT
#define O_CREAT		00000100	/* not fcntl */
#endif /*O_CREAT*/
#ifndef O_EXCL
#define O_EXCL		00000200	/* not fcntl */
#endif /*O_EXCL*/
#ifndef O_NOCTTY
#define O_NOCTTY	00000400	/* not fcntl */
#endif /*O_NOCTTY*/
#ifndef O_TRUNC
#define O_TRUNC		00001000	/* not fcntl */
#endif /*O_TRUNC*/
#ifndef O_APPEND
#define O_APPEND	00002000
#endif /*O_APPEND*/
#ifndef O_NONBLOCK
#define O_NONBLOCK	00004000
#endif /*O_NONBLOCK*/
#ifndef O_DSYNC
#define O_DSYNC		00010000	/* used to be O_SYNC, see below */
#endif /*O_DSYNC*/
#ifndef FASYNC
#define FASYNC		00020000	/* fcntl, for BSD compatibility */
#endif /*FASYNC*/
#ifndef O_DIRECT
#define O_DIRECT	00040000	/* direct disk access hint */
#endif /*O_DIRECT*/
#ifndef O_LARGEFILE
#define O_LARGEFILE	00100000
#endif /*O_LARGEFILE*/
#ifndef O_DIRECTORY
#define O_DIRECTORY	00200000	/* must be a directory */
#endif /*O_DIRECTORY*/
#ifndef O_NOFOLLOW
#define O_NOFOLLOW	00400000	/* don't follow links */
#endif /*O_NOFOLLOW*/
#ifndef O_NOATIME
#define O_NOATIME	01000000
#endif /*O_NOATIME*/
#ifndef O_CLOEXEC
#define O_CLOEXEC	02000000	/* set close_on_exec */
#endif /*O_CLOEXEC*/


#endif // __ALINIX_KERNEL_ASM_FCNTL_INCLUDED_H