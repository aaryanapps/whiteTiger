#ifndef _WT_IPHEADER_H__
#define _WT_IPHEADER_H__

#include "Globals.h"
#include "PacketHeader.h"

namespace wt {
namespace core {

class CIpHeader : public CPacketHeader {

public:
	CIpHeader();
	CIpHeader(uint32_t hnd,  uint32_t len, const uint8_t* hdrData);
    virtual ~CIpHeader();

    virtual uint32_t GetTypeId() {return m_typeId; }

    virtual std::string GetHeaderAbbrName() = 0;
    virtual uint32_t GetHeaderLength() = 0;
    const char* GetSrcAddr(){return NULL;}
    const char* GetDstAddr(){return NULL;}

    virtual std::string GetSrcAddrString();
    virtual std::string GetDstAddrString();
    virtual std::string GetProtocolString();
    virtual std::string GetInfoString();

    virtual bool IsStringCapable(uint16_t colId) {return false;};

    virtual uint32_t HeaderToCreateNext();

    bool Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData);

    virtual void GetInheritedTypes(wt::framework::WtoTypeIdsVec& typeIdVec)
    {
    	CPacketHeader::GetInheritedTypes(typeIdVec);
    	typeIdVec.push_back(CIpHeader::m_classId);
    	return;
    }


protected:
	static uint32_t m_classId;

	virtual bool ValidateHeader() = 0;
	virtual bool ParseHeader() = 0;

private:
	uint32_t 	m_typeId;
	uint32_t m_hdrHnd;
	uint32_t m_hdrLen;
	std::string m_hdrTypeInStr;
	uint8_t *m_hdrData;
	uint16_t m_hdrType;

};
}
}

#endif // _WT_IPHEADER_H__
