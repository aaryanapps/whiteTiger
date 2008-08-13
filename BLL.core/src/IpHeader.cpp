#include "StdAfx.h"

#include "IpHeader.h"
#include "Globals.h"
#include "net/HeaderTypes.h"
#include "CoreConsts.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"

using namespace wt::core;

//uint32_t CIpHeader::m_classId = CIpHeader_Class_Id ;
uint32_t CIpHeader::m_classId = REGISTER_CREATOR(CIpHeader_Class_Id, CIpHeader::Create);


CIpHeader::CIpHeader()
{

}

CIpHeader::~CIpHeader()
{

}

wt::framework::CWtObject* CIpHeader::Create()
{
	return NULL;
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
