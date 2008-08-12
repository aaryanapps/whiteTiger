#ifndef _WT_PACKETDB_H__
#define _WT_PACKETDB_H__

#include "Globals.h"
#include "WtObjectDb.h"

#define PACKETHDRHND_NULL 0

namespace wt {
namespace core {

class CPacketHeader;
typedef std::map<wt::framework::WtoHandle, CPacketHeader *> PacketHdrDb;


class CPacketHeaderDb {

public:
	CPacketHeaderDb();
	~CPacketHeaderDb();

	static CPacketHeaderDb& Instance();

	wt::framework::WtoHandle AddNewHeader(wt::framework::WtoHandle parentPkt,
						   uint32_t hdrType,
						   const uint32_t hdrOffset,
						   const uint8_t* pktData);

	CPacketHeader* GetHeader(wt::framework::WtoHandle pHnd);

private:
	//TODO: Remove this as this is not needed and is duplicate with WtObjectDb
	PacketHdrDb m_hdrDb;
};
}
}

#endif /*_WT_PACKETDB_H__*/
