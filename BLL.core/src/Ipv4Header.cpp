#include "StdAfx.h"

#include "Ipv4Header.h"
#include "Globals.h"
#include "net/HeaderTypes.h"
#include "PacketHeaderDb.h"
#include "PcapDefs.h"
#include "CommonPacketUtils.h"
#include "WtLogger.h"
#include "CoreConsts.h"

using namespace wt::core;

//DEFINE_STATIC_LOGGER("bll.Ipv4Header", devLogger);

CIpv4Header::CIpv4Header() :
							m_typeId(CIpv4Header_Class_Id),
							m_hdrLen(0),
							m_hdr(0)
{

}

CIpv4Header::~CIpv4Header()
{

}

bool CIpv4Header::Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData)
{
	m_hdrType = WT_IP_HDR;
	m_hdrTypeInStr = WT_IP_STR;
	m_hdrHnd = hnd;

	if (!pktData)
	{
		/*No Data*/
		return false;
	}

	//TODO: Get the parent Packet instance and check the captured length to header length.

	m_hdrData = const_cast<uint8_t*> (pktData + hdrOffset);
	m_hdr = (ip_hdr *)	  m_hdrData;

	if (!m_hdr)
		return false;

	if (!ValidateHeader())
		return false;

	if (!ParseHeader())
		return false;

	return true;
}

bool CIpv4Header::IsStringCapable(uint16_t colId)
{
	switch (colId)
	{
	case Column_SrcAddr_String:
		return true;
	case Column_DstAddr_String:
		return true;
	case Column_Protocol_String:
		return true;
	case Column_Info_String:
		return true;
	default:
		return false;
	}

	return false;
}

std::string CIpv4Header::GetSrcAddrString()
{
	return m_srcAddr.toString();
}

std::string CIpv4Header::GetDstAddrString()
{
	return m_dstAddr.toString();
}

std::string CIpv4Header::GetProtocolString()
{
	std::string s(WT_IP_STR);
	return s;
}

std::string CIpv4Header::GetInfoString()
{
	std::stringstream ss;
	ss << "IP Packet : Next Hdr " << (uint32_t) m_hdr->ip_p  ;
	return ss.str();
}

bool CIpv4Header::ValidateHeader()
{
	return true;
}

bool CIpv4Header::ParseHeader()
{
	m_hdrLen = 4 * m_hdr->ip_hl ;

	std::string sIpStr = CCommonPacketUtils::GetIpFromNetU32(m_hdr->ip_src) ;
	Poco::Net::IPAddress::tryParse(sIpStr, m_srcAddr);

	std::string dIpStr = CCommonPacketUtils::GetIpFromNetU32(m_hdr->ip_dst) ;
	Poco::Net::IPAddress::tryParse(dIpStr, m_dstAddr);

	return true;
}

uint32_t CIpv4Header::HeaderToCreateNext()
{
	return (uint32_t) m_hdr->ip_p;
}
