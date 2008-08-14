
#ifndef _WT_PACKETHEADERFACTORY_
#define _WT_PACKETHEADERFACTORY_

#include "Globals.h"
#include "net/HeaderTypes.h"

namespace wt {
namespace core {

typedef std::map<uint32_t, uint32_t> HdrType2IdMap;

class CPacketHeaderFactory {

public:
	static 	CPacketHeaderFactory& Instance();

	uint32_t	RegisterHeader(uint32_t hdrType, uint32_t hdrClassId);

	uint32_t GetClassIdForHdrType(uint32_t hdrType);

private:
	CPacketHeaderFactory();
	~CPacketHeaderFactory();

	HdrType2IdMap* GetHeaderMap();

};
}
}

#endif /*_WT_PACKETHEADERFACTORY_*/
