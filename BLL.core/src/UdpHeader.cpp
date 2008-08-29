#include "StdAfx.h"

#include "UdpHeader.h"
#include "Globals.h"
#include "net/HeaderTypes.h"
#include "CommonPacketUtils.h"
#include "CoreConsts.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"
#include "PacketHeaderFactory.h"

using namespace wt::core;

uint32_t CUdpHeader::m_classId = REGISTER_CREATOR(CUdpHeader_Class_Id, CUdpHeader::Create);
uint32_t CUdpHeader::m_hdrType = REGISTER_HDRTYPE(WT_UDP,CUdpHeader_Class_Id) ;

std::string CUdpHeader::m_hdrTypeInStr = WT_UDP_STR;
uint32_t  	CUdpHeader::m_hdrLen = WT_UDP_HDRLEN ;

CUdpHeader::CUdpHeader() :
						m_hdr(NULL),
						m_sPort(0),
						m_dPort(0),
						m_len(0),
						m_chksum(0)
{
	AddAsDerivedClassId(CUdpHeader_Class_Id);
}

wt::framework::CWtObject* CUdpHeader::Create()
{
	return new CUdpHeader();
}

CUdpHeader::~CUdpHeader()
{

}

bool CUdpHeader::Init(uint32_t hdrOffset, const uint8_t* pktData)
{
	if (!pktData)
	{
		/*No Data*/
		return false;
	}

	//TODO: Get the parent Packet instance and check the captured length to header length.

	uint8_t* data = const_cast<uint8_t*> (pktData + hdrOffset);
	m_hdr = (udp_hdr *)	data;

	if (!m_hdr)
		return false;

	if (!ValidateHeader())
		return false;

	if (!ParseHeader())
		return false;

	return true;
}

bool CUdpHeader::IsStringCapable(uint16_t colId)
{
	switch (colId)
	{
	case Column_SrcAddr_String:
		return false;
	case Column_DstAddr_String:
		return false;
	case Column_Protocol_String:
		return true;
	case Column_Info_String:
		return true;
	default:
		return false;
	}

	return false;
}

std::string CUdpHeader::GetSrcAddrString()
{
	std::stringstream s;
	s << "";
	return s.str();
}

std::string CUdpHeader::GetDstAddrString()
{
	std::stringstream s;
	s << "";
	return s.str();
}

std::string CUdpHeader::GetProtocolString()
{
	//std::string s(WT_UDP_STR);
	return m_hdrTypeInStr;
	//return s;
}

std::string CUdpHeader::GetInfoString()
{
	std::stringstream ss;

	ss << m_sPort << " > ";
	ss << m_dPort << " " ;
	ss << ": Length=" ;
	ss << m_len;

	return ss.str();
}

bool CUdpHeader::ValidateHeader()
{
	return true;
}

bool CUdpHeader::ParseHeader()
{
	m_sPort 	= CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->uh_sport);
	m_dPort 	= CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->uh_dport);
	m_len 		= CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->uh_ulen);
	m_chksum	= CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->uh_sum);

	return true;
}

uint32_t CUdpHeader::HeaderToCreateNext()
{

	//TODO: Create the appropriate Data class e.g Http, Https, Telnet, Ftp, etc.
	return WT_UNKWN;
}


/////// Private Methods;


