
#include "StdAfx.h"

#include "ArpHeader.h"
#include "Globals.h"
#include "net/HeaderTypes.h"
#include "PcapDefs.h"
#include "CommonPacketUtils.h"
#include "ArpHeaderIpImpl.h"
#include "CoreConsts.h"

using namespace wt::core;

uint32_t CArpHeader::m_classId = CArpHeader_Class_Id;

CArpHeader::CArpHeader() :
						  m_hdrLen(0),
						  m_Impl(0),
						  m_typeId(CArpHeader_Class_Id)
{

}

CArpHeader::~CArpHeader()
{
	delete m_Impl;
}

bool CArpHeader::Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData)
{

	if (!pktData)
	{
		/*No Data*/
		return false;
	}

	m_hdrLen = WT_ARP_HDRLEN;
	//TODO: Get the parent Packet instance and check the captured length to header length.

	uint8_t* data = const_cast<uint8_t*> (pktData + hdrOffset);
	m_hdr = (arp_hdr *)	data;

	if (!m_hdr)
		return false;

	m_arHrd = CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->ar_hrd);
	m_arPro = CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->ar_pro);

	CreateArpType(hdrOffset, pktData);

	if (!m_Impl)
		return false;

	if (!ValidateHeader())
		return false;

	if (!ParseHeader())
		return false;

	return true;
}

bool CArpHeader::IsStringCapable(uint16_t colId)
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

std::string CArpHeader::GetSrcAddrString()
{
	std::stringstream s;
	s << "";
	return s.str();
}

std::string CArpHeader::GetDstAddrString()
{
	std::stringstream s;
	s << "";
	return s.str();
}

std::string CArpHeader::GetProtocolString()
{
	return m_Impl->GetProtocolString();
}

std::string CArpHeader::GetInfoString()
{
	return m_Impl->GetInfoString();
}

bool CArpHeader::ValidateHeader()
{
	//m_Impl->ValidateHeader();
	return true;
}

bool CArpHeader::ParseHeader()
{
	//m_Impl->ParseHeader();
	return true;
}

uint32_t CArpHeader::HeaderToCreateNext()
{
	return WT_UNKWN;
}

std::string CArpHeader::GetHeaderAbbrName()
{
	if (m_Impl)
		return m_Impl->GetHeaderAbbrName();

	std::string s("ARP");
	return s;
}

/////// Private Methods;


void CArpHeader::CreateArpType(uint32_t hdrOffset, const uint8_t* pktData)
{
	switch (m_arPro)
	{
	case WT_ARP_ETHERTYPE_IP:
		m_Impl = (CArpHeaderImpl *) new CArpHeaderIpImpl(hdrOffset, pktData);
		break;
	default:
		m_Impl = NULL;
		break;
	}
}
