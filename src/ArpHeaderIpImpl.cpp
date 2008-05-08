
#include "ArpHeaderIpImpl.h"
#include "net/arp.h"
#include "net/HeaderTypes.h"
#include "CommonPacketUtils.h"
#include "net/MacAddress.h"
#include "Globals.h"

CArpHeaderIpImpl::CArpHeaderIpImpl() :
							m_protoStr(""),
							m_infoStr(""),
							m_etArpHdr(NULL),
							m_srcIp(""),
							m_dstIp("")
							
{
	
}

CArpHeaderIpImpl::~CArpHeaderIpImpl()
{
	
}

CArpHeaderIpImpl::CArpHeaderIpImpl(uint32_t hdrOffset,
								   const uint8_t* pktData)
{
	if (!pktData)
	{
		/*No Data*/
		return;
	}
	m_etArpHdr = NULL;
	uint8_t* data = const_cast<uint8_t*> (pktData + hdrOffset);
	m_etArpHdr = (ether_arp *)	data;
	
	if (!m_etArpHdr)
		return;

	ValidateHeader();
	
	ParseHeader();
}

bool CArpHeaderIpImpl::ValidateHeader()
{
	return true;
}

bool CArpHeaderIpImpl::ParseHeader()
{
	std::string tmp("");
	m_opCode = CCommonPacketUtils::GetNetworkToHostOrder(m_etArpHdr->ea_hdr.ar_op);

	//uint32_t ip = (uint32_t)(*(pBytes + 0) << 24 | *(pBytes + 1) << 16 | *(pBytes + 2) << 8 | *(pBytes + 3));
	uint32_t ip = CCommonPacketUtils::GetU32(&(m_etArpHdr->arp_spa[0]));

	std::string sIp = CCommonPacketUtils::GetIpFromNetU32(ip);
	Poco::Net::IPAddress::tryParse(sIp, m_srcIp);

	ip = CCommonPacketUtils::GetU32(&(m_etArpHdr->arp_tpa[0]));	
	std::string dIp = CCommonPacketUtils::GetIpFromNetU32(ip);
	Poco::Net::IPAddress::tryParse(dIp, m_dstIp);	
	
	m_src.CopyFrom(&(m_etArpHdr->arp_sha[0]));
	m_dst.CopyFrom(&(m_etArpHdr->arp_tha[0]));

	m_protoStr = GetProtoFromOpCode();
	m_infoStr  = GetInfoStr();

	return true;
}

std::string CArpHeaderIpImpl::GetHeaderAbbrName()
{
	return GetProtoFromOpCode();
}


//////Private Methods

std::string CArpHeaderIpImpl::GetProtoFromOpCode()
{
	std::stringstream ss;
	switch(m_opCode)
	{
	case WT_ARPOP_REQUEST:
	case WT_ARPOP_REPLY:
		ss << "ARP";
		break;
	case WT_ARPOP_RREQUEST:
	case WT_ARPOP_RREPLY:
		ss << "RARP";
		break;
	case WT_ARPOP_IREQUEST:
	case WT_ARPOP_IREPLY:
		ss << "InARP";
		break;
	}
	
	return ss.str();
}

std::string CArpHeaderIpImpl::GetInfoStr()
{
	std::stringstream ss;
	CMacAddress tMac;
	switch(m_opCode)
	{
	case WT_ARPOP_REQUEST:
		ss << "Who has ";
		ss << m_dstIp.toString();
		ss << " ?   " ;
		ss << "Tell " ;
		ss << m_srcIp.toString();
		ss << " ";
		break;
	case WT_ARPOP_REPLY:
		ss << m_dstIp.toString();
		ss << " is at ";
		ss << m_src.ToString();
		break;
	case WT_ARPOP_RREQUEST:
	case WT_ARPOP_RREPLY:
		ss << "RARP";
		break;
	case WT_ARPOP_IREQUEST:
	case WT_ARPOP_IREPLY:
		ss << "InARP";
		break;
	default:
		break;
	}
	
	return ss.str();
}
