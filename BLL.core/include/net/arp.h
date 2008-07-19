/*
 *   ARP: Address Resolution Protocol
 *   RFC: 826
 * 
 *  RARP: Reverse Address Resolution Protocol
 *   RFC: 903
 *
 * InARP: Inverse Address Resolution Protocol
 *   RFC: 1293
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

#ifndef _WT_ARP_H__
#define _WT_ARP_H__	1

#include "Globals.h"

/*
 * ARP header (without variable-sized fields)
 */
typedef struct arp_hdr
{
    uint16_t	ar_hrd;		/* Format of hardware address.  */
    uint16_t	ar_pro;		/* Format of protocol address.  */
    uint8_t		ar_hln;		/* Length of hardware address.  */
    uint8_t		ar_pln;		/* Length of protocol address.  */
    uint16_t	ar_op;		/* ARP opcode (command).  */
#if 0
    /* variable-sized fields: */
    uint8_t	__ar_sha[];	/* Sender hardware address.  */
    uint8_t	__ar_sip[];	/* Sender IP address.  */
    uint8_t	__ar_tha[];	/* Target hardware address.  */
    uint8_t	__ar_tip[];	/* Target IP address.  */
#endif
} arp_hdr;

/* ARP protocol opcodes. */
#define	WT_ARPOP_REQUEST	1	/* ARP request.  */
#define	WT_ARPOP_REPLY	2	/* ARP reply.  */
#define	WT_ARPOP_RREQUEST	3	/* RARP request.  */
#define	WT_ARPOP_RREPLY	4	/* RARP reply.  */
#define WT_ARPOP_REVREQUEST	WT_ARPOP_RREQUEST
#define WT_ARPOP_REVREPLY		WT_ARPOP_RREPLY
#define WT_ARPOP_IREQUEST	8	/* InARP request. */
#define WT_ARPOP_IREPLY	9	/* InARP reply. */
#define WT_ARPOP_INVREQUEST	WT_ARPOP_IREQUEST
#define WT_ARPOP_INVREPLY		WT_ARPOP_IREPLY

/* ARP protocol HARDWARE identifiers. */
#define WT_ARPHRD_NETROM	0	/* From KA9Q: NET/ROM pseudo. */
#define WT_ARPHRD_ETHER 	1	/* Ethernet 10/100Mbps.  */
#define	WT_ARPHRD_EETHER	2	/* Experimental Ethernet.  */
#define	WT_ARPHRD_AX25	3	/* AX.25 Level 2.  */
#define	WT_ARPHRD_PRONET	4	/* PROnet token ring.  */
#define	WT_ARPHRD_CHAOS	5	/* Chaosnet.  */
#define	WT_ARPHRD_IEEE802	6	/* IEEE 802.2 Ethernet/TR/TB.  */
#define	WT_ARPHRD_ARCNET	7	/* ARCnet.  */
#define	WT_ARPHRD_APPLETLK	8	/* APPLEtalk.  */
#define WT_ARPHRD_DLCI	15	/* Frame Relay DLCI.  */
#define WT_ARPHRD_METRICOM	23	/* Metricom STRIP (new IANA id).  */

/* Dummy types for non ARP hardware */
#define ARPHRD_SLIP	256
#define ARPHRD_CSLIP	257
#define ARPHRD_SLIP6	258
#define ARPHRD_CSLIP6	259
#define ARPHRD_RSRVD	260	/* Notional KISS type.  */
#define ARPHRD_ADAPT	264
#define ARPHRD_ROSE	270
#define ARPHRD_X25	271	/* CCITT X.25.  */
#define ARPHRD_PPP	512
#define ARPHRD_HDLC	513	/* (Cisco) HDLC.  */
#define ARPHRD_LAPB	516	/* LAPB.  */
#define ARPHRD_ASH	517	/* ASH.  */

#define ARPHRD_TUNNEL	768	/* IPIP tunnel.  */
#define ARPHRD_TUNNEL6	769	/* IPIP6 tunnel.  */
#define ARPHRD_FRAD	770	/* Frame Relay Access Device.  */
#define ARPHRD_SKIP	771	/* SKIP vif.  */
#define ARPHRD_LOOPBACK	772	/* Loopback device.  */
#define ARPHRD_LOCALTLK 773	/* Localtalk device.  */
#define ARPHRD_FDDI	774	/* Fiber Distributed Data Interface. */
#define ARPHRD_BIF      775	/* AP1000 BIF.  */
#define ARPHRD_SIT	776	/* sit0 device - IPv6-in-IPv4.  */

/*
 * Ethernet Address Resolution Protocol.
 *
 * See RFC 826 for protocol description.  Structure below is adapted
 * to resolving internet addresses.  Field names used correspond to
 * RFC 826.
 */
typedef struct ether_arp {
    arp_hdr	 ea_hdr;		/* fixed-size header */
    uint8_t	 arp_sha[6];	/* sender hardware address */
    uint8_t arp_spa[4];		/* sender protocol address */
    uint8_t	 arp_tha[6];	/* target hardware address */
    uint8_t arp_tpa[4];		/* target protocol address */
} ether_arp;

#define	arp_hrd	ea_hdr.ar_hrd
#define	arp_pro	ea_hdr.ar_pro
#define	arp_hln	ea_hdr.ar_hln
#define	arp_pln	ea_hdr.ar_pln
#define	arp_op	ea_hdr.ar_op

#endif	/* arp.h */
