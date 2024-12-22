/**
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

#ifndef _UAPI_HESIEN_STM_H
#define _UAPI_HESIEN_STM_H
/*
SMT stands for Simultaneous Multi-Threading. It is a technology that allows multiple threads to run concurrently on a single processor core*/

#include <heisen/typing.h>


#define STP_MASTER_MASK 0xffff
#define STP_CHANNEL_MAX	0xffff

struct stp_policy_id{
    uint32_t size;
    uint16_t master;
    uint16_t channel;
    uint16_t width;
    /*padding*/
	uint16_t	__reserved_0;
	uint32_t		__reserved_1;
	char		id[];
};

#define STP_POLICY_ID_SET	_IOWR('%', 0, struct stp_policy_id)
#define STP_POLICY_ID_GET	_IOR('%', 1, struct stp_policy_id)
#define STP_SET_OPTIONS		_IOW('%', 2, __u64)


#endif // _UAPI_HESIEN_STM_H