#ifndef __WT_PACKETPARSER_
#define __WT_PACKETPARSER_

#include "Globals.h"
#include "CaptureLibraryDefs.h"
#include "WtObject.h"

namespace wt {
namespace core {

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

};

}
}

#endif /*__WT_PACKETPARSER_ */
