#include "StdAfx.h"

#include "IpHeader.h"
#include "Globals.h"
#include "net/HeaderTypes.h"
#include "CoreConsts.h"

using namespace wt::core;

CIpHeader::CIpHeader() :
						m_typeId(CIpHeader_Class_Id)
{

}

CIpHeader::~CIpHeader()
{

}

bool CIpHeader::Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData)
{
	return false;
}

uint32_t CIpHeader::HeaderToCreateNext()
{
	return WT_UNKWN;
}

std::string CIpHeader::GetSrcAddrString()
{
	std::string s("IP Base Src");
	return s;
}

std::string CIpHeader::GetDstAddrString()
{
	std::string s("IP Base Dst");
	return s;
}


std::string CIpHeader::GetProtocolString()
{
	std::string s("IPBASE");
	return s;
}

std::string CIpHeader::GetInfoString()
{
	std::string s("IP Base Packet");
	return s;
}
