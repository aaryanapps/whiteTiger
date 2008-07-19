/*
 * TCP: Transmission Control Protocol
 * RFC: 793
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

#ifndef _WT_TCP_H
#define _WT_TCP_H	1

#include "Globals.h"

/*
 * TCP header (without options)
 */
typedef struct tcp_hdr
{
    uint16_t	th_sport;	/* source port */
    uint16_t	th_dport;	/* destination port */
    uint32_t	th_seq;		/* sequence number */
    uint32_t	th_ack;		/* acknowledgement number */
#if	__BYTE_ORDER == __LITTLE_ENDIAN    
    uint8_t	th_x2	: 4;	/* (unused) */
    uint8_t	th_off	: 4;	/* data offset */
#elif	__BYTE_ORDER == __BIG_ENDIAN    
    uint8_t	th_off	: 4;	/* data offset */
    uint8_t	th_x2	: 4;	/* (unused) */
#else
#error	"Please #define __BYTE_ORDER"
#endif
    uint8_t	th_flags;	/* control flags */
#define	TH_FIN	0x01
#define	TH_SYN	0x02
#define	TH_RST	0x04
#define	TH_PUSH	0x08
#define	TH_ACK	0x10
#define	TH_URG	0x20
/* RFC 3168 */
#define TH_ECE	0x40
/* RFC 3168 */
#define TH_CWR	0x80    
    uint16_t	th_win;		/* window */
    uint16_t	th_sum;		/* checksum */
    uint16_t	th_urp;		/* urgent pointer */
} tcp_hdr;

#define	TCPOPT_EOL		0
#define	TCPOPT_NOP		1
#define	TCPOPT_MAXSEG		2
#define TCPOLEN_MAXSEG		4
/* rfc 1323 */
#define TCPOPT_WINDOW		3
#define TCPOLEN_WINDOW		3
#define TCPOPT_WSCALE		TCPOPT_WINDOW
#define TCPOLEN_WSCALE		TCPOLEN_WINDOW
/* rfc 2018 */
#define TCPOPT_SACK_PERMITTED	4
#define TCPOLEN_SACK_PERMITTED	2
#define TCPOPT_SACKOK		TCPOPT_SACK_PERMITTED
#define TCPOLEN_SACKOK		TCPOLEN_SACK_PERMITTED
/* rfc 2018 */
#define TCPOPT_SACK		5
/* rfc 1072 */
#define TCPOPT_ECHO		6
#define TCPOLEN_ECHO		6
/* rfc 1072 */
#define TCPOPT_ECHOREPLY	7
#define TCPOLEN_ECHOREPLY	6
/* rfc 1323 */
#define TCPOPT_TIMESTAMP	8
#define TCPOLEN_TIMESTAMP	10
/* rfc 1644 */
#define TCPOPT_CC		11
#define TCPOLEN_CC		6
/* rfc 1644 */
#define TCPOPT_CCNEW		12
#define TCPOLEN_CCNEW		6
/* rfc 1644 */
#define TCPOPT_CCECHO		13
#define TCPOLEN_CCECHO		6
/* rfc 2385 */
#define TCPOPT_MD5		19
#define TCPOLEN_MD5		18

#endif	/* tcp.h */
