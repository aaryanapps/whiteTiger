/*
 *  IP: Internet Protocol (version 4)
 * RFC: 791
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

#ifndef _IP_H
#define _IP_H	1

#include "Globals.h"

/*
 * IP header (without options)
 */
typedef struct ip_hdr
{
#if	__BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t	ip_hl	: 4;	/* header length */
    uint8_t	ip_v	: 4;	/* version */
#elif	__BYTE_ORDER == __BIG_ENDIAN
    uint8_t	ip_v	: 4;	/* version */
    uint8_t	ip_hl	: 4;	/* header length */
#else
#error	"Please #define __BYTE_ORDER"
#endif
    uint8_t	ip_tos;		/* type of service */
    uint16_t	ip_len;		/* total length */
    uint16_t	ip_id;		/* identification */
    uint16_t	ip_off;		/* fragment offset field */
#define	IP_RF	0x8000		/* reserved fragment flag */
#define	IP_DF	0x4000		/* dont fragment flag */
#define	IP_MF	0x2000		/* more fragments flag */
#define	IP_OFFMASK	0x1fff	/* mask for fragmenting bits */
    uint8_t		ip_ttl;		/* time to live */
    uint8_t		ip_p;		/* protocol */
    uint16_t	ip_sum;		/* checksum */
    uint32_t	ip_src;		/* source address */
    uint32_t	ip_dst;		/* destination address */
} ip_hdr;

/*
 * Time stamp option structure.
 */
struct ip_timestamp
  {
    uint8_t ipt_code;			/* IPOPT_TS */
    uint8_t ipt_len;			/* size of structure (variable) */
    uint8_t ipt_ptr;			/* index of current entry */
#if	__BYTE_ORDER == __LITTLE_ENDIAN      
    uint8_t ipt_flg:4;			/* flags, see below */
    uint8_t ipt_oflw:4;		/* overflow counter */
#elif	__BYTE_ORDER == __BIG_ENDIAN
    uint8_t ipt_oflw:4;		/* overflow counter */
    uint8_t ipt_flg:4;			/* flags, see below */
#else
#error	"Please #define __BYTE_ORDER"
#endif
    uint32_t data[9];
  };

#define	IPVERSION	4               /* IP version number */
#define	IP_MAXPACKET	65535		/* maximum packet size */

/*
 * Definitions for IP type of service (ip_tos)
 */
#define	IPTOS_TOS_MASK		0x1E
#define	IPTOS_TOS(tos)		((tos) & IPTOS_TOS_MASK)
#define	IPTOS_LOWDELAY		0x10
#define	IPTOS_THROUGHPUT	0x08
#define	IPTOS_RELIABILITY	0x04
#define	IPTOS_LOWCOST		0x02
#define	IPTOS_MINCOST		IPTOS_LOWCOST

/*
 * Definitions for IP precedence (also in ip_tos) (hopefully unused)
 */
#define	IPTOS_PREC_MASK			0xe0
#define	IPTOS_PREC(tos)                ((tos) & IPTOS_PREC_MASK)
#define	IPTOS_PREC_NETCONTROL		0xe0
#define	IPTOS_PREC_INTERNETCONTROL	0xc0
#define	IPTOS_PREC_CRITIC_ECP		0xa0
#define	IPTOS_PREC_FLASHOVERRIDE	0x80
#define	IPTOS_PREC_FLASH		0x60
#define	IPTOS_PREC_IMMEDIATE		0x40
#define	IPTOS_PREC_PRIORITY		0x20
#define	IPTOS_PREC_ROUTINE		0x00

/*
 * Definitions for options.
 */
#define	IPOPT_COPY		0x80
#define	IPOPT_CLASS_MASK	0x60
#define	IPOPT_NUMBER_MASK	0x1f

#define	IPOPT_COPIED(o)		((o) & IPOPT_COPY)
#define	IPOPT_CLASS(o)		((o) & IPOPT_CLASS_MASK)
#define	IPOPT_NUMBER(o)		((o) & IPOPT_NUMBER_MASK)

#define	IPOPT_CONTROL		0x00
#define	IPOPT_RESERVED1		0x20
#define	IPOPT_DEBMEAS		0x40
#define	IPOPT_MEASUREMENT       IPOPT_DEBMEAS
#define	IPOPT_RESERVED2		0x60

#define	IPOPT_EOL		0		/* end of option list */
#define	IPOPT_END		IPOPT_EOL
#define	IPOPT_NOP		1		/* no operation */
#define	IPOPT_NOOP		IPOPT_NOP

#define	IPOPT_RR		7		/* record packet route */
#define	IPOPT_TS		68		/* timestamp */
#define	IPOPT_TIMESTAMP		IPOPT_TS
#define	IPOPT_SECURITY		130		/* provide s,c,h,tcc */
#define	IPOPT_SEC		IPOPT_SECURITY
/* rfc 1108 */
#define IPOPT_EXTENDEDSECURITY	133
#define	IPOPT_LSRR		131		/* loose source route */
#define	IPOPT_SATID		136		/* satnet id */
#define	IPOPT_SID		IPOPT_SATID
#define	IPOPT_SSRR		137		/* strict source route */
/* rfc 2113 */
#define	IPOPT_RA		148		/* router alert */
#define IPOPT_ROUTERALERT	IPOPT_RA
/* rfc 1393 */
#define IPOPT_TRACEROUTE	82
#define IPOPT_TR		IPOPT_TRACEROUTE

/*
 * Offsets to fields in options other than EOL and NOP.
 */
#define	IPOPT_OPTVAL		0		/* option ID */
#define	IPOPT_OLEN		1		/* option length */
#define	IPOPT_OFFSET		2		/* offset within option */
#define	IPOPT_MINOFF		4		/* min value of above */

#define	MAX_IPOPTLEN		40

/* flag bits for ipt_flg */
#define	IPOPT_TS_TSONLY		0		/* timestamps only */
#define	IPOPT_TS_TSANDADDR	1		/* timestamps and addresses */
#define	IPOPT_TS_PRESPEC	3		/* specified modules only */

#if 0	/* old (rfc791) */
/* bits for security (not byte swapped) */
#define	IPOPT_SECUR_UNCLASS	0x0000
#define	IPOPT_SECUR_CONFID	0xf135
#define	IPOPT_SECUR_EFTO	0x789a
#define	IPOPT_SECUR_MMMM	0xbc4d
#define	IPOPT_SECUR_RESTR	0xaf13
#define	IPOPT_SECUR_SECRET	0xd788
#define	IPOPT_SECUR_TOPSECRET	0x6bc5
#else	/* new (rfc1108) */
#define IPOPT_SECUR_UNCLASS	0xab
#define IPOPT_SECUR_CONFID	0x96
#define IPOPT_SECUR_SECRET	0x5a
#define IPOPT_SECUR_TOPSECRET	0x3d
#endif

#endif	/* ip.h */
