/**
 * @author Ali Mirmohammad
 * @file cmdline.hpp
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





/**
 * Command line functions delcared here.
 */

#ifndef __CMD_LINE_NOVANIX_KERNEL_HPP
#define __CMD_LINE_NOVANIX_KERNEL_HPP





#include <keymap.hpp>
#include <system/log.h>
#include <system/bootconsole.h>
#include <common/string.h>
#include <help.hpp>
#include <typing.hpp>
#include <network/oldcomm.hpp>
#include <shutdownsys.h>
#include <buffer.h>
#include <putchar.h>
#include <novanix/dir.h>
#include <novanix/user.h>
#include <novanix/access.h>
#include <novanix/time/time.hpp>
#include <common/listfiles.hpp>
#include <filehandle.h>
#include <timer.h>
#include <charstr.hpp>
#include <network/ip.h>
#include <network/tcp.h>
#include <network/udp.h>
#include <common/gaming.h>
#include <drivers/sound.h>
#include <common/clean.h>



VOID cmdline();

extern INTEGER counter_terminal;


// Defined for convenience 
#ifndef VGA_WHITE
#define VGA_WHITE VGA_COLOR_WHITE
#endif /*VGA_WHITE*/

#ifndef VGA_RED 
#define VGA_RED VGA_COLOR_RED
#endif /*VGA_RED*/


#ifndef VGA_BLUE
#define VGA_BLUE VGA_COLOR_BLUE
#endif /*VGA_BLUE*/

#ifndef VGA_GREEN
#define VGA_GREEN VGA_COLOR_GREEN
#endif /*VGA_GREEN*/

#endif /*__CMD_LINE_NOVANIX_KERNEL_HPP*/ 