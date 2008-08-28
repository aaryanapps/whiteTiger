#ifndef __WT_PACKETPARSER_
#define __WT_PACKETPARSER_

#include "Globals.h"
#include "CaptureLibraryDefs.h"
#include "WtObject.h"
#include "PacketHeader.h"

namespace wt {
namespace core {

class CPacket;

class CPacketParser {

public:

	static CPacketParser& Instance();

	/*Parse the given packet and create headers accordingly.*/
	wt::framework::CWtObject* ParsePacket(wt::framework::CWtObject* parent,
						   wt::core::capturelibrary::CapturedPkt* pkt,
						   uint32_t DataLink);

private:
	CPacketParser();
	~CPacketParser();

	uint32_t GetClassIdToCreate(uint32_t datalink);

	/*Create headers for the new packet */
	bool CreateHeaders(CPacket* parentPkt,
						wt::core::capturelibrary::CapturedPkt* pkt);

	/*Populate the various string fields*/
	void OnNewPacketHeader(CPacketHeader* pktHdr);


};

}
}

#endif /*__WT_PACKETPARSER_ */
