#ifndef _WT_ETHER_H__
#define _WT_ETHER_H__

#include "Globals.h"
/*
 * Ethernet address length
 */
#define ETHER_ADDR_LEN          6

/*
 * Ethernet header
 */
typedef struct ether_hdr {
    uint8_t  ether_dhost[ETHER_ADDR_LEN];
    uint8_t  ether_shost[ETHER_ADDR_LEN];
    uint16_t ether_type;
} ether_hdr;

/*
 * Length of a DEC/Intel/Xerox or 802.3 Ethernet header; note that some
 * compilers may pad "struct ether_header" to a multiple of 4 bytes,
 * for example, so "sizeof (struct ether_header)" may not give the right
 * answer.
 */
#define ETHER_HDRLEN    14

#endif /*_WT_ETHER_H__*/
