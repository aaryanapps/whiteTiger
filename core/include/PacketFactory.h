
#include "PcapDefs.h"
#include "EthernetPacket.h"

class CPacketFactory {

public:	
	CPacketFactory();
	~CPacketFactory();	
	CPacket* Create(uint32_t DataLink);
	
private:
	
};


CPacketFactory::CPacketFactory()
{
	
}

CPacketFactory::~CPacketFactory()
{
	
}

CPacket* CPacketFactory::Create(uint32_t dataLink)
{
	switch (dataLink) {
	case DLT_EN10MB:
		return new CEthernetPacket();
/*	case DLT_PPP:
		return new PppPacket();
*/
	default :
		return NULL;
	}
}
