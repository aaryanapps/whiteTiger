#ifndef _WT_PCAPDEFS_H__
#define _WT_PCAPDEFS_H__

#include "DataTypes.h"
#include "Poco/Net/IPAddress.h"
#include "pcap.h"
#include "FastDelegate.h"
//#include "Time.h"

using namespace Poco::Net;

typedef std::vector<IPAddress> IpVec;

/*
typedef struct timeval {
    uint32_t _ts;
    uint32_t _tv;

} timeval;
*/

/* 4 bytes IP address */
typedef struct ip_address{
    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;
    uint8_t byte4;
} ip_address;

/* IPv4 header */
typedef struct ip_header{
    uint8_t  ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
    uint8_t  tos;            // Type of service
    uint16_t tlen;           // Total length
    uint16_t identification; // Identification
    uint16_t flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
    uint8_t  ttl;            // Time to live
    uint8_t  proto;          // Protocol
    uint16_t crc;            // Header checksum
    ip_address  saddr;      // Source address
    ip_address  daddr;      // Destination address
    uint32_t   op_pad;         // Option + Padding
} ip_header;

/* UDP header*/
typedef struct udp_header{
    uint16_t sport;          // Source port
    uint16_t dport;          // Destination port
    uint16_t len;            // Datagram length
    uint16_t crc;            // Checksum
} udp_header;

/*
 * TCP header (without options)
 */
typedef struct tcp_header
{
    uint16_t	th_sport;	/* source port */
    uint16_t	th_dport;	/* destination port */
    uint32_t	th_seq;		/* sequence number */
    uint32_t	th_ack;		/* acknowledgement number */
    uint8_t		th_off;		/* data offset */
    uint8_t		th_flags;	/* control flags */
    uint16_t	th_win;		/* window */
    uint16_t	th_sum;		/* checksum */
    uint16_t	th_urp;		/* urgent pointer */
} tcp_header;

/*
#define	TH_FIN	0x01
#define	TH_SYN	0x02
#define	TH_RST	0x04
#define	TH_PUSH	0x08
#define	TH_ACK	0x10
#define	TH_URG	0x20
*/
/* RFC 3168 */
//#define TH_ECE	0x40
/* RFC 3168 */
//#define TH_CWR	0x80


typedef struct ifInfo {

    std::string name;
    std::string desc;
    IpVec ip;
    IpVec netmask;
    IpVec brdcast;

} ifInfo;

typedef struct pkt {
    timeval _ts;
    uint32_t _len;
    uint32_t _caplen;
    char* _data;
} pkt;

typedef fastdelegate::FastDelegate1<pkt> newPktCallBack;

typedef struct pcap_pkthdr pcapPktHdr;

typedef uint32_t PcapHandle ;
typedef std::map<PcapHandle, pcap_t *> PcapHnd2DescMap;
typedef fastdelegate::FastDelegate1<uint32_t> NewPktHeaderDelegate;

#define INVALID_PCAP_HND 0

#endif //_WT_PCAPDEFS_H__
