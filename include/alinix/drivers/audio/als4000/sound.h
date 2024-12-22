/**
 * @file sound.h
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
 *  - Kernel audio util.
*/

#ifndef __SOUND_DRIVER_SOUND_H
#define __SOUND_DRIVER_SOUND_H


enum Device
{
  Master,     /* Master volume */
  Dac,        /* DSP, digitized sound */
  Fm,         /* Fm synthesized sound */
  Cd,         /* Compact */
  Line,       /* Line in */
  Mic,        /* Microphone */
  Speaker,    /* Pc speaker */
  Treble,     /* Treble */
  Bass        /* Bass */
};

enum InputState
{
  ON, OFF
};

/* Volume levels range from 0 to 31, bass & treble range from 0 to 15 */
struct volume_level
{
  enum Device	device; 
  int 	 	left;   	
  int 	 	right;
};

struct inout_ctrl
{
  enum Device   	device;
  enum InputState 	left;
  enum InputState 	right;
};

#endif /*__SOUND_DRIVER_SOUND_H*/