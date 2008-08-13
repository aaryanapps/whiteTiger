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

    virtual void GetInheritedTypes(wt::framework::WtoTypeIdsVec& typeIdVec);

    /*Returns the Class Id*/
	virtual uint32_t 	GetClassId() {return m_classId; }

	static wt::framework::CWtObject* Create();

protected :
	static uint32_t m_classId;

	virtual bool ValidatePacket();
	virtual bool ParsePacket();

private:

	virtual void CreatePacketInfoText();
	virtual bool CreateHeaders();
	void OnNewPacketHeader(CPacketHeader* pktHdr);
};
}
}

#endif /*_WT_ETHERNETPACKET_H__*/
