#ifndef _WT_PACKETDB_H__
#define _WT_PACKETDB_H__

#include "Globals.h"
#include "PcapDefs.h"
#include "FastDelegate.h"
#include "WtObjectDb.h"

//class wt::core::;

namespace wt {
namespace core {

class CPacket;
typedef uint32_t PacketHandle;
typedef std::map<wt::framework::WtoHandle, CPacket *> PacketDb;
typedef std::map<wt::framework::WtoHandle, NewPktHeaderDelegate> NewPktHdrDelegateMap;

#define PACKETHND_NULL 0

class CPacketDb {

public:
	CPacketDb();
	~CPacketDb();

	static CPacketDb& Instance();
	wt::framework::WtoHandle AddNewPacket(wt::framework::WtoHandle parentCap,
						   uint32_t DataLink,
						   const pcapPktHdr *pkt,
						   const uint8_t* pktData);

	CPacket* GetPacket(wt::framework::WtoHandle pHnd);

private:

	PacketDb m_pktDb;
	NewPktHdrDelegateMap m_newHdrCbs;
};
}
}

#endif /*_WT_PACKETDB_H__*/
