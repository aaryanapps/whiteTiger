/*
 * ICMP: Internet Control Message Protocol
 *  RFC: 792
 * 
 * (!c) 2002 by Ighighi
 * Venezuela
 */

/*
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _WT_ICMP_H__
#define _WT_ICMP_H__	1

#include "Globals.h"

/*
 * Internal of an ICMP Router Advertisement
 */
struct icmp_ra_addr
{
    uint32_t	ira_addr;
    uint32_t	ira_preference;
};

/*
 * ICMP header
 */
struct icmp_hdr
{
    uint8_t	icmp_type;	/* type of message, see below */
    uint8_t	icmp_code;	/* type sub code */
    uint16_t	icmp_cksum;	/* ones complement checksum of struct */
    union
    {
	uint8_t	ih_pptr;	/* ICMP_PARAMPROB */
	uint32_t	ih_gwaddr;	/* gateway address */
	struct ih_idseq			/* echo datagram */
	{
	    uint16_t	icd_id;
	    uint16_t	icd_seq;
	} ih_idseq;
	uint32_t	ih_void;

	/* ICMP_TRACEROUTE (RFC1393) */
	struct ih_idvoid
	{
	    uint16_t	itr_id;
	    uint16_t itr_void;
	} ih_idvoid;
	
	/* ICMP_UNREACH_NEEDFRAG -- Path MTU Discovery (RFC1191) */
	struct ih_pmtu
	{
	    uint16_t	ipm_void;
	    uint16_t	ipm_nextmtu;
	} ih_pmtu;

	struct ih_rtradv
	{
	    uint8_t	irt_num_addrs;
	    uint8_t	irt_wpa;
	    uint16_t	irt_lifetime;
	} ih_rtradv;
    } icmp_hun;
#define	icmp_pptr	icmp_hun.ih_pptr
#define	icmp_gwaddr	icmp_hun.ih_gwaddr
#define	icmp_id		icmp_hun.ih_idseq.icd_id
#define	icmp_seq	icmp_hun.ih_idseq.icd_seq
#define	icmp_void	icmp_hun.ih_void
#define	icmp_pmvoid	icmp_hun.ih_pmtu.ipm_void
#define	icmp_nextmtu	icmp_hun.ih_pmtu.ipm_nextmtu
#define	icmp_num_addrs	icmp_hun.ih_rtradv.irt_num_addrs
#define	icmp_wpa	icmp_hun.ih_rtradv.irt_wpa
#define	icmp_lifetime	icmp_hun.ih_rtradv.irt_lifetime
#define icmp_trid	icmp_hun.ih_idvoid.itr_id
#define icmp_trvoid	icmp_hun.ih_idvoid.itr_void    
    union
    {
	struct
	{
	    uint32_t	its_otime;
	    uint32_t	its_rtime;
	    uint32_t	its_ttime;
	} id_ts;
	
	/* ICMP_TRACEROUTE (RFC1393) */
	struct
	{
	    uint16_t	itr_ohc;
	    uint16_t	itr_rhc;
	    uint32_t	itr_speed;
	    uint32_t	itr_mtu;
	} id_tr;
	
	/* options and then 64 bits of data */	
/*
	struct
	{
	    struct ip_hdr	idi_ip;

	} id_ip;
 */
	
	struct icmp_ra_addr	id_radv;
	uint32_t	id_mask;
	uint8_t	id_data[1];
    } icmp_dun;
#define	icmp_otime	icmp_dun.id_ts.its_otime
#define	icmp_rtime	icmp_dun.id_ts.its_rtime
#define	icmp_ttime	icmp_dun.id_ts.its_ttime
/* #define	icmp_ip		icmp_dun.id_ip.idi_ip */
#define	icmp_radv	icmp_dun.id_radv
#define	icmp_mask	icmp_dun.id_mask
#define	icmp_data	icmp_dun.id_data
#define icmp_ohc	icmp_dun.id_tr.itr_ohc
#define icmp_rhc	icmp_dun.id_tr.itr_rhc
#define icmp_speed	icmp_dun.id_tr.itr_speed
#define icmp_mtu	icmp_dun.id_tr.itr_mtu    

};

/*
 * Lower bounds on packet lengths for various types.
 * For the error advice packets must first insure that the
 * packet is large enough to contain the returned ip header.
 * Only then can we do the check to see if 64 bits of packet
 * data have been returned, since we need to check the returned
 * ip header length.
 */
#define	ICMP_MINLEN	8				/* abs minimum */
#define	ICMP_TSLEN	(8 + 3 * sizeof (n_time))	/* timestamp */
#define	ICMP_MASKLEN	12				/* address mask */
#define	ICMP_ADVLENMIN	(8 + sizeof (struct ip) + 8)	/* min */
#ifndef _IP_VHL
#define	ICMP_ADVLEN(p)	(8 + ((p)->icmp_ip.ip_hl << 2) + 8)
	/* N.B.: must separately check that ip_hl >= 5 */
#else
#define	ICMP_ADVLEN(p)	(8 + (IP_VHL_HL((p)->icmp_ip.ip_vhl) << 2) + 8)
	/* N.B.: must separately check that header length >= 5 */
#endif

/* Definition of type and code fields. */
#define ICMP_ECHOREPLY		0		/* echo reply */
#define	ICMP_UNREACH		3		/* dest unreachable, codes: */
#define	ICMP_SOURCEQUENCH	4		/* packet lost, slow down */
#define ICMP_REDIRECT		5		/* redirect */
#define ICMP_ECHO		8		/* echo request */
#define	ICMP_ROUTERADVERT	9		/* router advertisement */
#define	ICMP_ROUTERSOLICIT	10		/* router solicitation */
#define	ICMP_TIMXCEED		11		/* time exceeded, code: */
#define	ICMP_PARAMPROB		12		/* ip header bad */
#define	ICMP_TSTAMP		13		/* timestamp request */
#define	ICMP_TSTAMPREPLY	14		/* timestamp reply */
#define	ICMP_IREQ		15		/* information request */
#define	ICMP_IREQREPLY		16		/* information reply */
#define	ICMP_MASKREQ		17		/* address mask request */
#define	ICMP_MASKREPLY		18		/* address mask reply */

/* rfc 1393 */
#define ICMP_TRACEROUTE		30		/* traceroute */

/* #define	ICMP_MAXTYPE		18 */

#define ICMP_MAXTYPE		30

/* UNREACH codes */
#define	ICMP_UNREACH_NET	        0	/* bad net */
#define	ICMP_UNREACH_HOST	        1	/* bad host */
#define	ICMP_UNREACH_PROTOCOL	        2	/* bad protocol */
#define	ICMP_UNREACH_PORT	        3	/* bad port */
#define	ICMP_UNREACH_NEEDFRAG	        4	/* IP_DF caused drop */
#define	ICMP_UNREACH_SRCFAIL	        5	/* src route failed */
#define	ICMP_UNREACH_NET_UNKNOWN        6	/* unknown net */
#define	ICMP_UNREACH_HOST_UNKNOWN       7	/* unknown host */
#define	ICMP_UNREACH_ISOLATED	        8	/* src host isolated */
#define	ICMP_UNREACH_NET_PROHIB	        9	/* net denied */
#define	ICMP_UNREACH_HOST_PROHIB        10	/* host denied */
#define	ICMP_UNREACH_TOSNET	        11	/* bad tos for net */
#define	ICMP_UNREACH_TOSHOST	        12	/* bad tos for host */
#define	ICMP_UNREACH_FILTER_PROHIB      13	/* admin prohib */
#define	ICMP_UNREACH_HOST_PRECEDENCE    14	/* host prec vio. */
#define	ICMP_UNREACH_PRECEDENCE_CUTOFF  15	/* prec cutoff */

/* REDIRECT codes */
#define	ICMP_REDIRECT_NET	0		/* for network */
#define	ICMP_REDIRECT_HOST	1		/* for host */
#define	ICMP_REDIRECT_TOSNET	2		/* for tos and net */
#define	ICMP_REDIRECT_TOSHOST	3		/* for tos and host */

/* TIMEXCEED codes */
#define	ICMP_TIMXCEED_INTRANS	0		/* ttl==0 in transit */
#define	ICMP_TIMXCEED_REASS	1		/* ttl==0 in reass */

/* PARAMPROB codes */
#define	ICMP_PARAMPROB_OPTABSENT 1		/* req. opt. absent */

#define	ICMP_INFOTYPE(type) \
	((type) == ICMP_ECHOREPLY || (type) == ICMP_ECHO || \
	(type) == ICMP_ROUTERADVERT || (type) == ICMP_ROUTERSOLICIT || \
	(type) == ICMP_TSTAMP || (type) == ICMP_TSTAMPREPLY || \
	(type) == ICMP_IREQ || (type) == ICMP_IREQREPLY || \
	(type) == ICMP_MASKREQ || (type) == ICMP_MASKREPLY)

#endif	/* _WT_ICMP_H__ */
