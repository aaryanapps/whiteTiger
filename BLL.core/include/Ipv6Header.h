#ifndef _WT_IPV6HEADER_H__
#define _WT_IPV6HEADER_H__

#include "Globals.h"
#include "IpHeader.h"
#include "Poco/Net/IPAddress.h"
#include "net/ip.h"

using namespace Poco::Net;

namespace wt {
namespace core {

class CIpv6Header : public CIpHeader {

public:
	CIpv6Header();
	CIpv6Header(uint32_t hnd,  uint32_t len, const uint8_t* hdrData);
    virtual ~CIpv6Header();

    std::string GetHeaderAbbrName()
    {
    	std::string s("Ipv6");
    	return s;
	}

    /*Returns the Class Id*/
	virtual uint32_t 	GetClassId() {return m_classId; }

	static wt::framework::CWtObject* Create();

	uint32_t GetHeaderLength() {return m_hdrLen;}

    std::string GetSrcAddrString();
    std::string GetDstAddrString();
    std::string GetProtocolString();
    std::string GetInfoString();

    virtual bool IsStringCapable(uint16_t colId);

    virtual uint32_t HeaderToCreateNext();

    bool Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData);

    virtual void GetInheritedTypes(wt::framework::WtoTypeIdsVec& typeIdVec)
    {
    	CPacketHeader::GetInheritedTypes(typeIdVec);
    	typeIdVec.push_back(CIpv6Header::m_classId);
    	return;
    }


protected:
	static uint32_t m_classId;

	virtual bool ValidateHeader();
	virtual bool ParseHeader();

private:
	uint32_t 	m_typeId;

	uint32_t 	m_hdrHnd;
	uint32_t 	m_hdrLen;
	std::string m_hdrTypeInStr;
	uint8_t*	m_hdrData;
	uint16_t 	m_hdrType;

	IPAddress 	m_srcAddr;
	IPAddress 	m_dstAddr;

};
}
}

#endif // _WT_IPV6HEADER_H__
