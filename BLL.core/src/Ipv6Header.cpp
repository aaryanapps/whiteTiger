#include "StdAfx.h"

#include "Ipv6Header.h"
#include "Globals.h"
#include "net/HeaderTypes.h"
#include "CoreConsts.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"
#include "PacketHeaderFactory.h"

using namespace wt::core;

uint32_t CIpv6Header::m_classId = REGISTER_CREATOR(CIpv6Header_Class_Id, CIpv6Header::Create);
uint32_t CIpv6Header::m_hdrType = REGISTER_HDRTYPE(WT_IPV6,CIpv6Header_Class_Id) ;

CIpv6Header::CIpv6Header()
{
	AddAsDerivedClassId(CIpv6Header_Class_Id);
}

CIpv6Header::~CIpv6Header()
{

}

wt::framework::CWtObject* CIpv6Header::Create()
{
	return new CIpv6Header();
}

bool CIpv6Header::Init(uint32_t hdrOffset, const uint8_t* pktData)
{
	return true;
}


bool CIpv6Header::IsStringCapable(uint16_t colId)
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

std::string CIpv6Header::GetSrcAddrString()
{
	return m_srcAddr.toString();
}

std::string CIpv6Header::GetDstAddrString()
{
	return m_dstAddr.toString();
}


std::string CIpv6Header::GetProtocolString()
{
	std::string s(WT_IPV6_STR);
	return s;
}

std::string CIpv6Header::GetInfoString()
{
	std::string s("IPv6 Packet");
	return s;
}

bool CIpv6Header::ValidateHeader()
{
	return true;
}

bool CIpv6Header::ParseHeader()
{
	return true;
}

uint32_t CIpv6Header::HeaderToCreateNext()
{
	return WT_UNKWN;
}

