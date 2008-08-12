#include "StdAfx.h"

#include "PacketHeader.h"
#include "CoreConsts.h"

using namespace wt::core;

uint32_t CPacketHeader::m_classId = CPacketHeader_Class_Id ;

CPacketHeader::CPacketHeader() :
								m_typeId(CPacketHeader_Class_Id)
{

}

CPacketHeader::~CPacketHeader()
{

}

bool CPacketHeader::Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData)
{
	return false;
}
