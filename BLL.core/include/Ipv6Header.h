#ifndef _WT_IPV6HEADER_H__
#define _WT_IPV6HEADER_H__

#include "Globals.h"
#include "IpHeader.h"
#include "Poco/Net/IPAddress.h"
#include "net/ip.h"

using namespace Poco::Net;

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
    virtual uint32_t GetTypeId() {return m_typeId; }
    
    uint32_t GetHeaderLength() {return m_hdrLen;}

    std::string GetSrcAddrString();
    std::string GetDstAddrString();	
    std::string GetProtocolString();
    std::string GetInfoString();
    
    virtual bool IsStringCapable(uint16_t colId);
    
    virtual uint32_t HeaderToCreateNext();
    
    bool Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData);
    
protected:
	virtual bool ValidateHeader();
	virtual bool ParseHeader();
	
private:
	uint32_t 	m_typeId;
	
	uint32_t m_hdrHnd;
	uint32_t m_hdrLen;
	std::string m_hdrTypeInStr;
	uint8_t *m_hdrData;
	uint16_t m_hdrType;
	
	IPAddress m_srcAddr;
	IPAddress m_dstAddr;

};
#endif // _WT_IPV6HEADER_H__