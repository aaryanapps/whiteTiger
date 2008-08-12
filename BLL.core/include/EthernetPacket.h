#ifndef _WT_ETHERNETPACKET_H__
#define _WT_ETHERNETPACKET_H__

#include "Packet.h"
#include "PcapDefs.h"


namespace wt {
namespace core {

class CPacketHeader;

class CEthernetPacket : public CPacket {

public:
	CEthernetPacket();
	virtual ~CEthernetPacket();
	virtual bool Init(uint32_t hnd, const pcapPktHdr *pkt, const uint8_t* pktData);

	virtual uint32_t GetTypeId() {return m_typeId; }

    virtual void GetInheritedTypes(wt::framework::WtoTypeIdsVec& typeIdVec);


protected :
	static uint32_t m_classId;

	virtual bool ValidatePacket();
	virtual bool ParsePacket();

private:
	uint32_t 	m_typeId;
	virtual void CreatePacketInfoText();
	virtual bool CreateHeaders();
	void OnNewPacketHeader(CPacketHeader* pktHdr);
};
}
}

#endif /*_WT_ETHERNETPACKET_H__*/
