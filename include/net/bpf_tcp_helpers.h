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
#ifndef __ALINIX_KERNEL_BPF_TCP_HELPERS_H
#define __ALINIX_KERNEL_BPF_TCP_HELPERS_H

#include <alinix/types.h>



#ifndef SOL_TCP
#define SOL_TCP 6
#endif

#ifndef TCP_CA_NAME_MAX
#define TCP_CA_NAME_MAX	16
#endif

struct sock_common {
	unsigned char	skc_state;
	uint16_t		skc_num;
} __attribute__((preserve_access_index));

enum sk_pacing {
	SK_PACING_NONE		= 0,
	SK_PACING_NEEDED	= 1,
	SK_PACING_FQ		= 2,
};


struct sock {
	struct sock_common	__sk_common;
#define sk_state		__sk_common.skc_state
	unsigned long		sk_pacing_rate;
	uint32_t			sk_pacing_status; /* see enum sk_pacing */
} __attribute__((preserve_access_index));



struct inet_sock {
	struct sock		sk;
} __attribute__((preserve_access_index));


struct inet_connection_sock {
	struct inet_sock	  icsk_inet;
	uint8_t			  icsk_ca_state:6,
				  icsk_ca_setsockopt:1,
				  icsk_ca_dst_locked:1;
	struct {
		uint8_t		  pending;
	} icsk_ack;
	uint64_t			  icsk_ca_priv[104 / sizeof(uint64_t)];
} __attribute__((preserve_access_index));

struct request_sock {
	struct sock_common		__req_common;
} __attribute__((preserve_access_index));



struct tcp_sock {
	struct inet_connection_sock	inet_conn;

	uint32_t	rcv_nxt;
	uint32_t	snd_nxt;
	uint32_t	snd_una;
	uint32_t	window_clamp;
	uint8_t	ecn_flags;
	uint32_t	delivered;
	uint32_t	delivered_ce;
	uint32_t	snd_cwnd;
	uint32_t	snd_cwnd_cnt;
	uint32_t	snd_cwnd_clamp;
	uint32_t	snd_ssthresh;
	uint8_t	syn_data:1,	/* SYN includes data */
		syn_fastopen:1,	/* SYN includes Fast Open option */
		syn_fastopen_exp:1,/* SYN includes Fast Open exp. option */
		syn_fastopen_ch:1, /* Active TFO re-enabling probe */
		syn_data_acked:1,/* data in SYN is acked by SYN-ACK */
		save_syn:1,	/* Save headers of SYN packet */
		is_cwnd_limited:1,/* forward progress limited by snd_cwnd? */
		syn_smc:1;	/* SYN includes SMC */
	uint32_t	max_packets_out;
	uint32_t	lsndtime;
	uint32_t	prior_cwnd;
	uint64_t	tcp_mstamp;	/* most recent packet received/sent */
	bool	is_mptcp;
} __attribute__((preserve_access_index));

static __always_inline struct inet_connection_sock *inet_csk(const struct sock *sk)
{
	return (struct inet_connection_sock *)sk;
}

static __always_inline void *inet_csk_ca(const struct sock *sk)
{
	return (void *)inet_csk(sk)->icsk_ca_priv;
}

static __always_inline struct tcp_sock *tcp_sk(const struct sock *sk)
{
	return (struct tcp_sock *)sk;
}

static __always_inline bool before(uint32_t seq1, uint32_t seq2)
{
	return (sint32_t)(seq1-seq2) < 0;
}
#define after(seq2, seq1) 	before(seq1, seq2)

#define	TCP_ECN_OK		1
#define	TCP_ECN_QUEUE_CWR	2
#define	TCP_ECN_DEMAND_CWR	4
#define	TCP_ECN_SEEN		8

enum inet_csk_ack_state_t {
	ICSK_ACK_SCHED	= 1,
	ICSK_ACK_TIMER  = 2,
	ICSK_ACK_PUSHED = 4,
	ICSK_ACK_PUSHED2 = 8,
	ICSK_ACK_NOW = 16	/* Send the next ACK immediately (once) */
};

enum tcp_ca_event {
	CA_EVENT_TX_START = 0,
	CA_EVENT_CWND_RESTART = 1,
	CA_EVENT_COMPLETE_CWR = 2,
	CA_EVENT_LOSS = 3,
	CA_EVENT_ECN_NO_CE = 4,
	CA_EVENT_ECN_IS_CE = 5,
};

struct ack_sample {
	uint32_t pkts_acked;
	sint32_t rtt_us;
	uint32_t in_flight;
} __attribute__((preserve_access_index));

struct rate_sample {
	uint64_t prior_mstamp; /* starting timestamp for interval */
	uint32_t  prior_delivered;	/* tp->delivered at "prior_mstamp" */
	sint32_t  delivered;		/* number of packets delivered over interval */
	long interval_us;	/* time for tp->delivered to incr "delivered" */
	uint32_t snd_interval_us;	/* snd interval for delivered packets */
	uint32_t rcv_interval_us;	/* rcv interval for delivered packets */
	long rtt_us;		/* RTT of last (S)ACKed packet (or -1) */
	int  losses;		/* number of packets marked lost upon ACK */
	uint32_t  acked_sacked;	/* number of packets newly (S)ACKed upon ACK */
	uint32_t  prior_in_flight;	/* in flight before this ACK */
	bool is_app_limited;	/* is sample from packet with bubble in pipe? */
	bool is_retrans;	/* is sample from retransmission? */
	bool is_ack_delayed;	/* is this (likely) a delayed ACK? */
} __attribute__((preserve_access_index));

#define TCP_CA_NAME_MAX		16
#define TCP_CONG_NEEDS_ECN	0x2

struct tcp_congestion_ops {
	char name[TCP_CA_NAME_MAX];
	uint32_t flags;

	/* initialize private data (optional) */
	void (*init)(struct sock *sk);
	/* cleanup private data  (optional) */
	void (*release)(struct sock *sk);

	/* return slow start threshold (required) */
	uint32_t (*ssthresh)(struct sock *sk);
	/* do new cwnd calculation (required) */
	void (*cong_avoid)(struct sock *sk, uint32_t ack, uint32_t acked);
	/* call before changing ca_state (optional) */
	void (*set_state)(struct sock *sk, uint8_t new_state);
	/* call when cwnd event occurs (optional) */
	void (*cwnd_event)(struct sock *sk, enum tcp_ca_event ev);
	/* call when ack arrives (optional) */
	void (*in_ack_event)(struct sock *sk, uint32_t flags);
	/* new value of cwnd after loss (required) */
	uint32_t  (*undo_cwnd)(struct sock *sk);
	/* hook for packet ack accounting (optional) */
	void (*pkts_acked)(struct sock *sk, const struct ack_sample *sample);
	/* override sysctl_tcp_min_tso_segs */
	uint32_t (*min_tso_segs)(struct sock *sk);
	/* returns the multiplier used in tcp_sndbuf_expand (optional) */
	uint32_t (*sndbuf_expand)(struct sock *sk);
	/* call when packets are delivered to update cwnd and pacing rate,
	 * after all the ca_state processing. (optional)
	 */
	void (*cong_control)(struct sock *sk, const struct rate_sample *rs);
	void *owner;
};

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min_not_zero(x, y) ({			\
	typeof(x) __x = (x);			\
	typeof(y) __y = (y);			\
	__x == 0 ? __y : ((__y == 0) ? __x : min(__x, __y)); })

static __always_inline bool tcp_in_slow_start(const struct tcp_sock *tp)
{
	return tp->snd_cwnd < tp->snd_ssthresh;
}



static __always_inline bool tcp_is_cwnd_limited(const struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);

	/* If in slow start, ensure cwnd grows to twice what was ACKed. */
	if (tcp_in_slow_start(tp))
		return tp->snd_cwnd < 2 * tp->max_packets_out;

	// return !!BPF_CORE_READ_BITFIELD(tp, is_cwnd_limited);
}

static __always_inline bool tcp_cc_eq(const char *a, const char *b)
{
	int i;

	for (i = 0; i < TCP_CA_NAME_MAX; i++) {
		if (a[i] != b[i])
			return false;
		if (!a[i])
			break;
	}

	return true;
}

extern uint32_t tcp_slow_start(struct tcp_sock *tp, uint32_t acked) __ksym;
extern void tcp_cong_avoid_ai(struct tcp_sock *tp, uint32_t w, uint32_t acked) __ksym;

struct mptcp_sock {
	struct inet_connection_sock	sk;

	uint32_t		token;
	struct sock	*first;
	char		ca_name[TCP_CA_NAME_MAX];
} __attribute__((preserve_access_index));

#endif // __ALINIX_KERNEL_BPF_TCP_HELPERS_H