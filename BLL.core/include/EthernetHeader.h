#ifndef _WT_ETHERNETHEADER_H__
#define _WT_ETHERNETHEADER_H__

#include "Globals.h"
#include "PacketHeader.h"
#include "net/ether.h"
#include "net/MacAddress.h"

namespace wt {
namespace core {

class CEthernetHeader : public CPacketHeader {

public:
	CEthernetHeader();
	CEthernetHeader(uint32_t hnd,  uint32_t hdrOffset, const uint8_t* pktData);
    virtual ~CEthernetHeader();

    std::string GetHeaderAbbrName()
    {
    	std::string s("EthII");
    	return s;
    }

    uint32_t GetHeaderLength() {return m_hdrLen;}
    const char* GetSrcAddr(){return NULL;}
    const char* GetDstAddr(){return NULL;}

    virtual std::string GetSrcAddrString(){return m_srcMac.ToString();}
    virtual std::string GetDstAddrString(){return m_dstMac.ToString();}
    virtual std::string GetProtocolString(){return m_hdrTypeInStr;}
    virtual std::string GetInfoString();

    virtual bool IsStringCapable(uint16_t colId);

    virtual uint32_t HeaderToCreateNext();

    bool Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData);

    virtual void GetInheritedTypes(wt::framework::WtoTypeIdsVec& typeIdVec)
    {
    	CPacketHeader::GetInheritedTypes(typeIdVec);
    	typeIdVec.push_back(CEthernetHeader::m_classId);
    	return;
    }

    /*Returns the Class Id*/
	virtual uint32_t 	GetClassId() {return m_classId; }

	static wt::framework::CWtObject* Create();

protected:
	static uint32_t m_classId;

	virtual bool ValidateHeader();
	virtual bool ParseHeader();

private:

	uint32_t m_hdrHnd;
	uint32_t m_hdrLen;
	std::string m_hdrTypeInStr;
	const uint8_t *m_hdrData;
	uint16_t m_hdrType;

	ether_hdr *m_hdr;
	wt::framework::types::CMacAddress m_srcMac;
	wt::framework::types::CMacAddress m_dstMac;

};
}
}
#endif // _WT_ETHERNETHEADER_H__
