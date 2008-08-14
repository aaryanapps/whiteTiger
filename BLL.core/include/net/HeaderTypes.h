#ifndef _WT_HEADERTYPES_H__
#define _WT_HEADERTYPES_H__

/*
   0200       Xerox PUP
   0201       Xerox PUP Address Translation
   0600       Xerox NS IDP
   0800       Internetworking Protocol (IP)
   0801       X.75
   0802       NBS
   0803       ECMA
   0804       Chaosnet
   0805       X.25 Packet (Level 3)
   0806       Address Resolution Protocol (ARP)
   0807       XNS Compatibility
   1000       Berkeley Trailer
   5208       BBN Simnet
   6001       DEC MOP (Dump/Load)
   6002       DEC MOP (Remote Console)
   6003       DECNET Phase 4
   6004       DEC LAT
   6005       DEC
   6006       DEC
   8005       HP Probe
   8010       Excelan
   8035       Reverse ARP
   8038       DEC LANBridge
   809B       AppleTalk
   80F3       AppleTalk ARP
   8137       NetWare IPX/SPX
*/
#define WT_UNKWN 0
#define WT_ETH 1

#define WT_IP 0x0800
#define WT_IPV6 0x86DD
#define WT_ARP 0x0806
#define WT_RARP 0x8035

/*
0	HOPOPT, IPv6 Hop-by-Hop Option.	RFC 1883
1	ICMP, Internet Control Message Protocol.	RFC 792
2	IGAP, IGMP for user Authentication Protocol.
	IGMP, Internet Group Management Protocol.
	RGMP, Router-port Group Management Protocol.
3	GGP, Gateway to Gateway Protocol.
4	IP in IP encapsulation.
5	ST, Internet Stream Protocol.
6	TCP, Transmission Control Protocol.
7	UCL, CBT.
8	EGP, Exterior Gateway Protocol.
9	IGRP, Interior Gateway Routing Protocol.
10	BBN RCC Monitoring.
11	NVP, Network Voice Protocol.
12	PUP.
13	ARGUS.
14	EMCON, Emission Control Protocol.
15	XNET, Cross Net Debugger.
16	Chaos.
17	UDP, User Datagram Protocol.
18	TMux, Transport Multiplexing Protocol.
19	DCN Measurement Subsystems.
20	HMP, Host Monitoring Protocol.
21	Packet Radio Measurement.
22	XEROX NS IDP.
23	Trunk-1.
24	Trunk-2.
25	Leaf-1.
26	Leaf-2.
27	RDP, Reliable Data Protocol.
28	IRTP, Internet Reliable Transaction Protocol.
29	ISO Transport Protocol Class 4.
30	NETBLT, Network Block Transfer.
31	MFE Network Services Protocol.
32	MERIT Internodal Protocol.
33	DCCP, Datagram Congestion Control Protocol.
34	Third Party Connect Protocol.
35	IDPR, Inter-Domain Policy Routing Protocol.
36	XTP, Xpress Transfer Protocol.
37	Datagram Delivery Protocol.
38	IDPR, Control Message Transport Protocol.
39	TP++ Transport Protocol.
40	IL Transport Protocol.
41	IPv6 over IPv4.
42	SDRP, Source Demand Routing Protocol.
43	IPv6 Routing header.
44	IPv6 Fragment header.
45	IDRP, Inter-Domain Routing Protocol.
46	RSVP, Reservation Protocol.
47	GRE, General Routing Encapsulation.
48	DSR, Dynamic Source Routing Protocol.
49	BNA.
50	ESP, Encapsulating Security Payload.
51	AH, Authentication Header.
52 	I-NLSP, Integrated Net Layer Security TUBA.
53 	SWIPE, IP with Encryption.
54	NARP, NBMA Address Resolution Protocol.
55	Minimal Encapsulation Protocol.
56	TLSP, Transport Layer Security Protocol using Kryptonet key management.
57	SKIP.
58	ICMPv6, Internet Control Message Protocol for IPv6.
	MLD, Multicast Listener Discovery.
59	IPv6 No Next Header.
60	IPv6 Destination Options.
61	Any host internal protocol.
62 	CFTP.
63 	Any local network.
64 	SATNET and Backroom EXPAK.
65 	Kryptolan.
66 	MIT Remote Virtual Disk Protocol.
67 	Internet Pluribus Packet Core.
68 	Any distributed file system.
69 	SATNET Monitoring.
70 	VISA Protocol.
71 	Internet Packet Core Utility.
72 	Computer Protocol Network Executive.
73 	Computer Protocol Heart Beat.
74 	Wang Span Network.
75 	Packet Video Protocol.
76 	Backroom SATNET Monitoring.
77 	SUN ND PROTOCOL-Temporary.
78 	WIDEBAND Monitoring.
79	WIDEBAND EXPAK.
80	ISO-IP.
81	VMTP, Versatile Message Transaction Protocol.
82	SECURE-VMTP
83	VINES.
84	TTP.
85 	NSFNET-IGP.
86 	Dissimilar Gateway Protocol.
87 	TCF.
88 	EIGRP.
89	OSPF, Open Shortest Path First Routing Protocol.
MOSPF, Multicast Open Shortest Path First.
90	Sprite RPC Protocol.
91	Locus Address Resolution Protocol.
92	MTP, Multicast Transport Protocol.
93 	AX.25.
94 	IP-within-IP Encapsulation Protocol.
95 	Mobile Internetworking Control Protocol.
96 	Semaphore Communications Sec. Pro.
97 	EtherIP.
98 	Encapsulation Header.
99 	Any private encryption scheme.
100 	GMTP.
101 	IFMP, Ipsilon Flow Management Protocol.
102 	PNNI over IP.
103 	PIM, Protocol Independent Multicast.
104 	ARIS.
105 	SCPS.
106 	QNX.
107 	Active Networks.
108 	IPPCP, IP Payload Compression Protocol.
109 	SNP, Sitara Networks Protocol.
110 	Compaq Peer Protocol.
111 	IPX in IP.
112	VRRP, Virtual Router Redundancy Protocol.
113	PGM, Pragmatic General Multicast.
114 	any 0-hop protocol.
115	L2TP, Level 2 Tunneling Protocol.
116	DDX, D-II Data Exchange.
117	IATP, Interactive Agent Transfer Protocol.
118	ST, Schedule Transfer.
119	SRP, SpectraLink Radio Protocol.
120	UTI.
121	SMP, Simple Message Protocol.
122	SM.
123	PTP, Performance Transparency Protocol.
124	ISIS over IPv4.
125	FIRE.
126	CRTP, Combat Radio Transport Protocol.
127	CRUDP, Combat Radio User Datagram.
128	SSCOPMCE.
129	IPLT.
130	SPS, Secure Packet Shield.
131	PIPE, Private IP Encapsulation within IP.
132	SCTP, Stream Control Transmission Protocol.
133	Fibre Channel.
134	RSVP-E2E-IGNORE.
135	Mobility Header.
136	UDP-Lite, Lightweight User Datagram Protocol.
137	MPLS in IP.
*/

#define WT_TCP 6
#define WT_UDP 17
#define WT_ICMP 1
#define WT_ICMP_V6 58
#define WT_IGAP_IGMP_RGMP 2
#define WT_IPV6_OV_V4 41
#define WT_IPV6_FRAG 44


#define WT_ETH_STR "ETHII"
#define WT_ARP_STR "ARP"
#define WT_RARP_STR "RARP"
#define WT_IP_STR "IP"
#define WT_IPV6_STR "IPv6"
#define WT_TCP_STR "TCP"
#define WT_UDP_STR "UDP"
#define WT_ICMP_STR "ICMP"
#define WT_ICMPV6_STR "ICMPv6"

#define WT_UNKWN_STR "UNKWN"


#define WT_UNKWN 0
#define WT_ETH 1

#define WT_IP_HDR 0x0800
#define WT_IPV6_HDR 0x86DD
#define WT_ARP_HDR 0x0806
#define WT_RARP_HDR 0x8035

#define WT_TCP_HDR 6
#define WT_UDP_HDR 17
#define WT_ICMP_HDR 1
#define WT_ICMP_V6_HDR 58


#define WT_ETH_HDRLEN 14
#define WT_IP_HDRLEN 20
#define WT_IPV6_HDRLEN 128
#define WT_TCP_HDRLEN 20
#define WT_UDP_HDRLEN 8
#define WT_ARP_HDRLEN 8
#define WT_UNKWN_HDRLEN 0


#define WT_ARP_ETHERTYPE_IP 0x800
#define WT_ARP_ETHERTYPE_IPV6 0x86dd
#define WT_ARP_ETHERTYPE_

/*
 * Columns informaiton that each header can support
 * For e.g. Ethernet can support srcAddr as mac address
 * Ip can support ip address
 */

#define Column_SrcAddr_String 5
#define Column_DstAddr_String 6
#define Column_Protocol_String 7
#define Column_Info_String 8

#define REGISTER_HDRTYPE(hdr,cls) \
	wt::core::CPacketHeaderFactory::Instance().RegisterHeader(hdr , cls)

#endif /*_WT_HEADERTYPES_H__*/
