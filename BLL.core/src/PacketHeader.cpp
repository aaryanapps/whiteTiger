#include "StdAfx.h"

#include "PacketHeader.h"
#include "CoreConsts.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"

using namespace wt::core;

//uint32_t CPacketHeader::m_classId = CPacketHeader_Class_Id ;
uint32_t CPacketHeader::m_classId = REGISTER_CREATOR(CPacketHeader_Class_Id, CPacketHeader::Create);

CPacketHeader::CPacketHeader()
{

}

CPacketHeader::~CPacketHeader()
{

}

bool CPacketHeader::Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData)
{
	return false;
}


wt::framework::CWtObject* CPacketHeader::Create()
{
	return NULL;
}
