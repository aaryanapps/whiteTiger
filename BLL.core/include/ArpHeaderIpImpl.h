#ifndef _WT_ARPHEADERIPIMPL_H__
#define _WT_ARPHEADERIPIMPL_H__

#include "Globals.h"
#include "ArpHeaderImpl.h"
#include "net/arp.h"
#include "net/MacAddress.h"
#include "Poco/Net/IPAddress.h"


class CArpHeaderIpImpl : public CArpHeaderImpl {

public:
	CArpHeaderIpImpl();
	CArpHeaderIpImpl(uint32_t hdrOffSet, const uint8_t* pktData);
	virtual ~CArpHeaderIpImpl();

	
	bool ValidateHeader();
	bool ParseHeader();	
	
	std::string GetHeaderAbbrName() ;
	std::string GetProtocolString(){ return m_protoStr;}
	std::string GetInfoString(){ return m_infoStr;}
	
private:
	std::string m_protoStr;
	std::string m_infoStr;
	
	ether_arp 	*m_etArpHdr;
	uint16_t 	m_opCode;
	wt::framework::types::CMacAddress m_src;
	wt::framework::types::CMacAddress m_dst;
	Poco::Net::IPAddress m_srcIp;
	Poco::Net::IPAddress m_dstIp;
	
	std::string GetProtoFromOpCode();
	std::string GetInfoStr();
};

#endif /*_WT_ARPHEADERIPIMPL_H__*/
