
#include "PacketHeader.h"
#include "AppConsts.h"

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
