/**
 * @author Ali Mirmohammad
 * @file udi.h
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
 *  - UDI driver util.
 * @ref https://wiki.osdev.org/UDI_Device_Enumeration
*/

/*Enumeration values */

#define UDI_ENUMERATE_START 1
#define UDI_ENUMERATE_START_RESCAN 2
#define UDI_ENUMERATE_NEXT 3
#define UDI_ENUMERATE_NEW 4
#define UDI_ENUMERATE_DIRECTED 5
#define UDI_ENUMERATE_RELEASE 6

/* Values for enumeration_result */
#define UDI_ENUMERATE_OK 0
#define UDI_ENUMERATE_LEAF 1
#define UDI_ENUMERATE_DONE 2
#define UDI_ENUMERATE_RESCAN 3
#define UDI_ENUMERATE_REMOVED 4
#define UDI_ENUMERATE_REMOVED_SELF 5
#define UDI_ENUMERATE_RELEASED 6
#define UDI_ENUMERATE_FAILED 255