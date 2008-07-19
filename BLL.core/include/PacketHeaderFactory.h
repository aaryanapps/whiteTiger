
#include "net/HeaderTypes.h"
#include "EthernetHeader.h"
#include "Ipv4Header.h"
#include "Ipv6Header.h"
#include "TcpHeader.h"
#include "ArpHeader.h"
#include "UdpHeader.h"

class CPacketHeaderFactory {

public:	
	CPacketHeaderFactory();
	~CPacketHeaderFactory();	
	CPacketHeader* Create(uint32_t hdrType);
	
private:
	
};


CPacketHeaderFactory::CPacketHeaderFactory()
{
	
}

CPacketHeaderFactory::~CPacketHeaderFactory()
{
	
}

//TODO: Remove the switch statement and create a map

CPacketHeader* CPacketHeaderFactory::Create(uint32_t hdrType)
{
	CPacketHeader *pHdr = NULL;
	switch (hdrType) {
	case WT_ETH:
		pHdr = new CEthernetHeader();
		break;
	case WT_ARP:
		pHdr = new CArpHeader();
		break;
	case WT_IP:
		pHdr = new CIpv4Header();
		break;
	case WT_IPV6:
		pHdr = new CIpv6Header();
		break;
	case WT_TCP:
		pHdr = new CTcpHeader();
		break;
	case WT_UDP:
		pHdr = new CUdpHeader();
		break;
	default :
		pHdr = NULL;
		break;
	}

	return pHdr;
}

