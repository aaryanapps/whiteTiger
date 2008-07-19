#ifndef _WT_PACKETDB_H__
#define _WT_PACKETDB_H__

#include "Globals.h"
#include "WtObjectDb.h"

class CPacketHeader;

typedef std::map<WtoHandle, CPacketHeader *> PacketHdrDb;

#define PACKETHDRHND_NULL 0

class CPacketHeaderDb {

public:
	CPacketHeaderDb();
	~CPacketHeaderDb();
	
	static CPacketHeaderDb& Instance();

	WtoHandle AddNewHeader(WtoHandle parentPkt,
						   uint32_t hdrType,
						   const uint32_t hdrOffset, 
						   const uint8_t* pktData);
	
	CPacketHeader* GetHeader(WtoHandle pHnd);
	
private:
	//TODO: Remove this as this is not needed and is duplicate with WtObjectDb
	PacketHdrDb m_hdrDb;
};

#endif /*_WT_PACKETDB_H__*/
