/**
 * @author Ali Mirmohammad
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
 * @file etherdevice.h
 * Purpose:
 *      - Provide utility functions for Ethernet devices.
*/
#ifndef __ALINIX_KERNEL_ETHER_DEVICE_H
#define __ALINIX_KERNEL_ETHER_DEVICE_H

#include <alinix/types.h>

/**
 * @brief Check if the given Ethernet address is all zeros.
 *
 * The `is_zero_ether_addr` function checks whether the given Ethernet address
 * (MAC address) is all zeros. This function is implemented to handle Ethernet
 * frames efficiently.
 *
 * @param addr Pointer to the Ethernet address, represented as an array of
 *             uint8_t (bytes).
 *
 * @return `true` if the Ethernet address is all zeros, `false` otherwise.
 *
 * @note This function is implemented as a static inline function to avoid
 *       function call overhead and to allow the compiler to optimize its
 *       usage more effectively.
 */
static inline bool is_zero_ether_addr(const uint8_t *addr)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	return ((*(const u32 *)addr) | (*(const uint16_t *)(addr + 4))) == 0;
#else
	return (*(const uint16_t *)(addr + 0) |
		*(const uint16_t *)(addr + 2) |
		*(const uint16_t *)(addr + 4)) == 0;
#endif
}

/**
 * @brief Check if the given Ethernet address is a multicast address.
 *
 * The `is_multicast_ether_addr` function checks whether the given Ethernet
 * address (MAC address) is a multicast address. This function is implemented
 * to handle Ethernet frames efficiently.
 *
 * @param addr Pointer to the Ethernet address, represented as an array of
 *             uint8_t (bytes).
 *
 * @return `true` if the Ethernet address is a multicast address, `false`
 *         otherwise.
 *
 * @note This function is implemented as a static inline function to avoid
 *       function call overhead and to allow the compiler to optimize its
 *       usage more effectively.
 */
static inline bool is_multicast_ether_addr(const uint8_t *addr)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	u32 a = *(const u32 *)addr;
#else
	uint16_t a = *(const uint16_t *)addr;
#endif
#ifdef __BIG_ENDIAN
	return 0x01 & (a >> ((sizeof(a) * 8) - 8));
#else
	return 0x01 & a;
#endif
}


/**
 * @brief Check if the given 64-bit Ethernet address is a multicast address.
 *
 * The `is_multicast_ether_addr_64bits` function checks whether the given 64-bit
 * Ethernet address (MAC address) is a multicast address. This function is
 * implemented to handle 64-bit Ethernet addresses efficiently, if supported.
 * If efficient access is not supported or the address is not 64 bits long,
 * it falls back to the `is_multicast_ether_addr` function.
 *
 * @param addr Pointer to the Ethernet address, represented as an array of
 *             uint8_t (bytes).
 *
 * @return `true` if the Ethernet address is a multicast address, `false`
 *         otherwise.
 *
 * @note This function is implemented as a static inline function to avoid
 *       function call overhead and to allow the compiler to optimize its
 *       usage more effectively.
 */
static inline bool is_multicast_ether_addr_64bits(const uint8_t *addr)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
#ifdef __BIG_ENDIAN
	return 0x01 & ((*(const u64 *)addr) >> 56);
#else
	return 0x01 & (*(const u64 *)addr);
#endif
#else
	return is_multicast_ether_addr(addr);
#endif
}


/**
 * @brief Check if the given Ethernet address is a locally administered address.
 *
 * The `is_local_ether_addr` function checks whether the given Ethernet
 * address (MAC address) is a locally administered address. This function
 * checks the second least significant bit of the first byte of the address
 * to determine if it is a locally administered address.
 *
 * @param addr Pointer to the Ethernet address, represented as an array of
 *             uint8_t (bytes).
 *
 * @return `true` if the Ethernet address is a locally administered address,
 *         `false` otherwise.
 *
 * @note This function is implemented as a static inline function to avoid
 *       function call overhead and to allow the compiler to optimize its
 *       usage more effectively.
 */
static inline bool is_local_ether_addr(const uint8_t *addr){
    return 0x02 & addr[0];
}


/**
 * @brief Check if the given Ethernet address is a broadcast address.
 *
 * The `is_broadcast_ether_addr` function checks whether the given Ethernet
 * address (MAC address) is a broadcast address. This function compares the
 * address to the broadcast address (all ones) to determine if it is a
 * broadcast address.
 *
 * @param addr Pointer to the Ethernet address, represented as an array of
 *             uint8_t (bytes).
 *
 * @return `true` if the Ethernet address is a broadcast address, `false`
 *         otherwise.
 *
 * @note This function is implemented as a static inline function to avoid
 *       function call overhead and to allow the compiler to optimize its
 *       usage more effectively.
 */
static inline bool is_broadcast_ether_addr(const uint8_t *addr)
{
	return (*(const uint16_t *)(addr + 0) &
		*(const uint16_t *)(addr + 2) &
		*(const uint16_t *)(addr + 4)) == 0xffff;
}

/**
 * @brief Check if the given Ethernet address is a unicast address.
 *
 * The `is_unicast_ether_addr` function checks whether the given Ethernet
 * address (MAC address) is a unicast address. This function simply negates
 * the result of the `is_multicast_ether_addr` function to determine if the
 * address is not a multicast address, which implies it is a unicast address.
 *
 * @param addr Pointer to the Ethernet address, represented as an array of
 *             uint8_t (bytes).
 *
 * @return `true` if the Ethernet address is a unicast address, `false`
 *         otherwise.
 *
 * @note This function is implemented as a static inline function to avoid
 *       function call overhead and to allow the compiler to optimize its
 *       usage more effectively.
 */
static inline bool is_unicast_ether_addr(const uint8_t *addr)
{
	return !is_multicast_ether_addr(addr);
}

/**
 * @brief Check if the given Ethernet address is a valid unicast address.
 *
 * The `is_valid_ether_addr` function checks whether the given Ethernet
 * address (MAC address) is a valid unicast address. It does so by ensuring
 * that the address is not a multicast address and not the all-zeros address,
 * which are both considered invalid for unicast communication.
 *
 * @param addr Pointer to the Ethernet address, represented as an array of
 *             uint8_t (bytes).
 *
 * @return `true` if the Ethernet address is a valid unicast address, `false`
 *         otherwise.
 *
 * @note This function is implemented as a static inline function to avoid
 *       function call overhead and to allow the compiler to optimize its
 *       usage more effectively.
 */
static inline bool is_valid_ether_addr(const uint8_t *addr)
{
	/* FF:FF:FF:FF:FF:FF is a multicast address so we don't need to
	 * explicitly check for it here. */
	return !is_multicast_ether_addr(addr) && !is_zero_ether_addr(addr);
}




#endif // __ALINIX_KERNEL_ETHER_DEVICE_H