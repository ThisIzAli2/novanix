#ifndef _HEISEN_RANGE_H
#define _HEISEN_RANGE_H
#include <heisen/types.h>

struct range {
	uint64_t   start;
	uint64_t   end;
};

static inline uint64_t range_len(const struct range *range)
{
	return range->end - range->start + 1;
}

static inline bool range_contains(struct range *r1, struct range *r2)
{
	return r1->start <= r2->start && r1->end >= r2->end;
}

int add_range(struct range *range, int az, int nr_range,
		uint64_t start, uint64_t end);


int add_range_with_merge(struct range *range, int az, int nr_range,
				uint64_t start, uint64_t end);

void subtract_range(struct range *range, int az, uint64_t start, uint64_t end);

int clean_sort_range(struct range *range, int az);

void sort_range(struct range *range, int nr_range);

#endif