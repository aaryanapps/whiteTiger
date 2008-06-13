#ifndef _WT_PACKETDB_H__
#define _WT_PACKETDB_H__

#include "Globals.h"
#include "PcapDefs.h"
#include "FastDelegate.h"
#include "WtObjectDb.h"

class CPacket;

typedef uint32_t PacketHandle;
typedef std::map<WtoHandle, CPacket *> PacketDb;
typedef std::map<WtoHandle, NewPktHeaderDelegate> NewPktHdrDelegateMap;

#define PACKETHND_NULL 0

class CPacketDb {

public:
	CPacketDb();
	~CPacketDb();
	
	static CPacketDb& Instance();
	WtoHandle AddNewPacket(WtoHandle parentCap,
						   uint32_t DataLink, 
						   const pcapPktHdr *pkt, 
						   const uint8_t* pktData);

	CPacket* GetPacket(WtoHandle pHnd);
	
private:

	PacketDb m_pktDb;
	NewPktHdrDelegateMap m_newHdrCbs;
};

#endif /*_WT_PACKETDB_H__*/
