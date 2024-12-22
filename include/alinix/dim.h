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
 * @file dim.h
 * @abstraction:
 * 	- Kernel DIM header file implemented.
*/

/**
 * @ref https://github.com/torvalds/linux/blob/master/include/linux/dim.h
*/

#ifndef __ALINIX_KERNEL_DIM_H
#define __ALINIX_KERNEL_DIM_H

#include <alinix/kernel.h>
#include <alinix/math.h>
#include <alinix/uapi/const.h>

#define DIM_NEVENTS 64

#define IS_SIGNIFICANT_DIFF(val, ref) \
	((ref) && (((100UL * abs((val) - (ref))) / (ref)) > 10))
#define BIT_GAP(bits, end, start) ((((end) - (start)) + BIT_ULL(bits)) \
		& (BIT_ULL(bits) - 1))


struct dim_cq_moder{
	uint8_t usec;
	uint16_t pkts;
	uint16_t comps;
	uint8_t dim_cq_moder;
};


struct dim_sample{
	ktime_t time;
	uint32_t pkt_ctr;
	uint32_t byte_ctr;
	uint16_t event_ctr;
	uint32_t comp_ctr;
};


struct dim_stats {
	int ppms; /* packets per msec */
	int bpms; /* bytes per msec */
	int epms; /* events per msec */
	int cpms; /* completions per msec */
	int cpe_ratio; /* ratio of completions to events */
};

struct dim {
	uint8_t state;
	struct dim_stats prev_stats;
	struct dim_sample start_sample;
	struct dim_sample measuring_sample;
	// struct work_struct work; //?Uncommnet?
	void *priv;
	uint8_t profile_ix;
	uint8_t mode;
	uint8_t tune_state;
	uint8_t steps_right;
	uint8_t steps_left;
	uint8_t tired;
};

enum dim_cq_period_mode {
	DIM_CQ_PERIOD_MODE_START_FROM_EQE = 0x0,
	DIM_CQ_PERIOD_MODE_START_FROM_CQE = 0x1,
	DIM_CQ_PERIOD_NUM_MODES
};

enum dim_state {
	DIM_START_MEASURE,
	DIM_MEASURE_IN_PROGRESS,
	DIM_APPLY_NEW_PROFILE,
};

enum dim_tune_state {
	DIM_PARKING_ON_TOP,
	DIM_PARKING_TIRED,
	DIM_GOING_RIGHT,
	DIM_GOING_LEFT,
};

/**
 * enum dim_stats_state - DIM algorithm statistics states
 *
 * These will determine the verdict of current iteration.
 *
 * @DIM_STATS_WORSE: Current iteration shows worse performance than before
 * @DIM_STATS_SAME:  Current iteration shows same performance than before
 * @DIM_STATS_BETTER: Current iteration shows better performance than before
 */
enum dim_stats_state {
	DIM_STATS_WORSE,
	DIM_STATS_SAME,
	DIM_STATS_BETTER,
};

/**
 * enum dim_step_result - DIM algorithm step results
 *
 * These describe the result of a step.
 *
 * @DIM_STEPPED: Performed a regular step
 * @DIM_TOO_TIRED: Same kind of step was done multiple times - should go to
 * tired parking
 * @DIM_ON_EDGE: Stepped to the most left/right profile
 */
enum dim_step_result {
	DIM_STEPPED,
	DIM_TOO_TIRED,
	DIM_ON_EDGE,
};

/**
 *	dim_on_top - check if current state is a good place to stop (top location)
 *	@dim: DIM context
 *
 * Check if current profile is a good place to park at.
 * This will result in reducing the DIM checks frequency as we assume we
 * shouldn't probably change profiles, unless traffic pattern wasn't changed.
 */
bool dim_on_top(struct dim *dim);

/**
 *	dim_turn - change profile altering direction
 *	@dim: DIM context
 *
 * Go left if we were going right and vice-versa.
 * Do nothing if currently parking.
 */
void dim_turn(struct dim *dim);

/**
 *	dim_park_on_top - enter a parking state on a top location
 *	@dim: DIM context
 *
 * Enter parking state.
 * Clear all movement history.
 */
void dim_park_on_top(struct dim *dim);

/**
 *	dim_park_tired - enter a tired parking state
 *	@dim: DIM context
 *
 * Enter parking state.
 * Clear all movement history and cause DIM checks frequency to reduce.
 */
void dim_park_tired(struct dim *dim);

/**
 *	dim_calc_stats - calculate the difference between two samples
 *	@start: start sample
 *	@end: end sample
 *	@curr_stats: delta between samples
 *
 * Calculate the delta between two samples (in data rates).
 * Takes into consideration counter wrap-around.
 * Returned boolean indicates whether curr_stats are reliable.
 */
bool dim_calc_stats(struct dim_sample *start, struct dim_sample *end,
		    struct dim_stats *curr_stats);



PRIVATE __always_inline VOID dim_update_sample(uint16_t event_ctr,uint64_t packets,uint64_t bytes, struct dim_sample *s){
	// s->time = ktime_get(); // TODO: Try uncomment this
	s->pkt_ctr   = packets;
	s->byte_ctr  = bytes;
	s->event_ctr = event_ctr;
}

PRIVATE __always_inline VOID dim_update_sample_with_comps(uint16_t event_ctr, uint64_t packets, uint64_t bytes, uint64_t comps,
			     struct dim_sample *s){
	dim_update_sample(event_ctr, packets, bytes, s);
	s->comp_ctr = comps;
		}



/**
 *	net_dim_get_rx_moderation - provide a CQ moderation object for the given RX profile
 *	@cq_period_mode: CQ period mode
 *	@ix: Profile index
 */
struct dim_cq_moder net_dim_get_rx_moderation(u8 cq_period_mode, int ix);

/**
 *	net_dim_get_def_rx_moderation - provide the default RX moderation
 *	@cq_period_mode: CQ period mode
 */
struct dim_cq_moder net_dim_get_def_rx_moderation(u8 cq_period_mode);

/**
 *	net_dim_get_tx_moderation - provide a CQ moderation object for the given TX profile
 *	@cq_period_mode: CQ period mode
 *	@ix: Profile index
 */
struct dim_cq_moder net_dim_get_tx_moderation(u8 cq_period_mode, int ix);

/**
 *	net_dim_get_def_tx_moderation - provide the default TX moderation
 *	@cq_period_mode: CQ period mode
 */
struct dim_cq_moder net_dim_get_def_tx_moderation(u8 cq_period_mode);

/**
 *	net_dim - main DIM algorithm entry point
 *	@dim: DIM instance information
 *	@end_sample: Current data measurement
 *
 * Called by the consumer.
 * This is the main logic of the algorithm, where data is processed in order
 * to decide on next required action.
 */
void net_dim(struct dim *dim, struct dim_sample end_sample);

/* RDMA DIM */

/*
 * RDMA DIM profile:
 * profile size must be of RDMA_DIM_PARAMS_NUM_PROFILES.
 */
#define RDMA_DIM_PARAMS_NUM_PROFILES 9
#define RDMA_DIM_START_PROFILE 0

/**
 * rdma_dim - Runs the adaptive moderation.
 * @dim: The moderation struct.
 * @completions: The number of completions collected in this round.
 *
 * Each call to rdma_dim takes the latest amount of completions that
 * have been collected and counts them as a new event.
 * Once enough events have been collected the algorithm decides a new
 * moderation level.
 */
void rdma_dim(struct dim *dim, u64 completions);


#endif /*__ALINIX_KERNEL_DIM_H*/