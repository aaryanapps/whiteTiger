#ifndef _WT_IPV4HEADER_H__
#define _WT_IPV4HEADER_H__

#include "Globals.h"
#include "IpHeader.h"
#include "Poco/Net/IPAddress.h"
#include "net/ip.h"

namespace wt {
namespace core {

class CIpv4Header : public CIpHeader {

public:
	CIpv4Header();
	CIpv4Header(uint32_t len, const uint8_t* hdrData);
    virtual ~CIpv4Header();

    std::string GetHeaderAbbrName()
    {
    	std::string s("Ipv4");
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

    bool Init(uint32_t hdrOffset, const uint8_t* pktData);


protected:
	static uint32_t m_classId;

	static uint32_t m_hdrType;

	virtual bool ValidateHeader();
	virtual bool ParseHeader();

private:

	uint32_t 	m_hdrLen;
	std::string m_hdrTypeInStr;
	uint8_t*	m_hdrData;

	ip_hdr*		m_hdr;
	Poco::Net::IPAddress m_srcAddr;
	Poco::Net::IPAddress m_dstAddr;

};
}
}

#endif // _WT_IPV4HEADER_H__
