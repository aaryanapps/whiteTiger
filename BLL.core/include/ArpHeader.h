#ifndef _WT_ARPHEADER_H__
#define _WT_ARPHEADER_H__

#include "Globals.h"
#include "PacketHeader.h"
#include "net/arp.h"
#include "ArpHeaderImpl.h"

namespace wt {
namespace core {

class CArpHeader : public CPacketHeader {

public:
	CArpHeader();
	CArpHeader(uint32_t hnd,  uint32_t len, const uint8_t* hdrData);
    virtual ~CArpHeader();

    static CWtObject* Create();

    std::string GetHeaderAbbrName() ;
    uint32_t GetHeaderLength() {return m_hdrLen;}
    virtual bool Init(uint32_t hdrOffset, const uint8_t* pktData);

	virtual uint32_t HeaderToCreateNext();

    virtual std::string GetSrcAddrString();
    virtual std::string GetDstAddrString();
    virtual std::string GetProtocolString();
    virtual std::string GetInfoString();

    virtual bool IsStringCapable(uint16_t colId);

    /*Returns the Class Id*/
	virtual uint32_t 	GetClassId() {return m_classId; }

protected:
	static uint32_t m_classId;

	static uint32_t m_hdrType;

	virtual bool ValidateHeader();
	virtual bool ParseHeader();

private:
	uint32_t 	m_hdrLen;
	arp_hdr		*m_hdr;
	CArpHeaderImpl *m_Impl;

	uint16_t 	m_arHrd;
	uint16_t 	m_arPro;

	void CreateArpType(uint32_t hdrOffset, const uint8_t* pktData);

};
}
}

#endif // _WT_PACKETHEADER_H__
