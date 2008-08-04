#include "StdAfx.h"

#include "UdpHeader.h"
#include "Globals.h"
#include "net/HeaderTypes.h"
#include "PacketHeaderDb.h"
#include "PcapDefs.h"
#include "CommonPacketUtils.h"
#include "CoreConsts.h"

using namespace wt::core;

CUdpHeader::CUdpHeader() :
						  m_typeId(CUdpHeader_Class_Id)
{

}

CUdpHeader::~CUdpHeader()
{

}

bool CUdpHeader::Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData)
{
	m_hdrType = WT_UDP_HDR;
	m_hdrTypeInStr = WT_UDP_STR;
	m_hdrLen = WT_UDP_HDRLEN ;

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
	std::string s(WT_UDP_STR);
	return s;
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

	//TODO: Create the appropriate Data class e.g Http, Https, Telnet, Ftp, etc.

	return true;
}

uint32_t CUdpHeader::HeaderToCreateNext()
{
	return WT_UNKWN;
}


/////// Private Methods;


