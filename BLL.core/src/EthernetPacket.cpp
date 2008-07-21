#include "StdAfx.h"

#include "EthernetPacket.h"
#include "PacketHeaderDb.h"
#include "net/HeaderTypes.h"
#include "CommonPacketUtils.h"
#include "PacketHeader.h"
#include "PacketDb.h"
#include "RelationManager.h"
#include "AppConsts.h"
#include "WtObjectDb.h"
#include "RelationInfo.h"
#include "WtLogger.h"

DEFINE_STATIC_LOGGER("bll.EthernetPacket", devLogger);


CEthernetPacket::CEthernetPacket() :
									m_typeId(CEthernetPacket_Class_Id)
{
	
}

CEthernetPacket::~CEthernetPacket()
{
	
}

bool CEthernetPacket::Init(uint32_t hnd,
						   const pcapPktHdr *pkt, 
						   const uint8_t* pktData)
{
	CPacket::Init(hnd, pkt, pktData);
	
	CreateHeaders();
	
	return true;
}

void CEthernetPacket::CreatePacketInfoText()
{
	
}

bool CEthernetPacket::ValidatePacket()
{
	return true;
}

bool CEthernetPacket::ParsePacket()
{
	return true;
}


bool CEthernetPacket::CreateHeaders()
{
	wt::framework::CRelationManager *rm = wt::framework::CRelationManager::Instance();
	CPacketHeaderDb& phd = CPacketHeaderDb::Instance();
	
	uint32_t hdrOffset = 0 ;
	uint32_t hdr = WT_ETH ;
	WtoHandle curHnd ;
	WtoHandle preHnd ;
	bool status = true ;
	bool isFirstHdr = true ;
	std::stringstream dbg;

	for (; hdr != WT_UNKWN; )
	{
		curHnd = phd.AddNewHeader(GetWtoHandle(),hdr, hdrOffset, &(m_pktData.front()));

		if (PACKETHDRHND_NULL == curHnd)
		{
			/*Unknown header or insufficient memory.
			 */
			hdr = WT_UNKWN;
			status = false;
			continue;
		}
		
		WtoHandle wHnd = phd.GetHeader(curHnd)->GetWtoHandle();
		
		if (isFirstHdr)
		{
			rm->AddRelation(GetWtoHandle(), wHnd, RelationType(BottomMostHeader()));
		}
		else
		{
			rm->AddRelation(GetWtoHandle(), wHnd, RelationType(StackedOnHeader()));
			dbg << " : " ;
		}
		
		CPacketHeader *pktHdr = phd.GetHeader(curHnd);

		OnNewPacketHeader(pktHdr);
		
		hdrOffset += pktHdr->GetHeaderLength();		
		hdr = pktHdr->HeaderToCreateNext();
		isFirstHdr = false;
		preHnd = curHnd;
		dbg << pktHdr->GetHeaderAbbrName();
	}

	if (PACKETHDRHND_NULL != curHnd)
	{
		WtoHandle wHnd = phd.GetHeader(curHnd)->GetWtoHandle();
		//Add TopMostHeader Relation
		rm->AddRelation(GetWtoHandle(), wHnd, RelationType(TopMostHeader()));
	}
	
	LOG_INFO( devLogger(), dbg.str()) ;
	
	return status;
}

void CEthernetPacket::OnNewPacketHeader(CPacketHeader* pktHdr)
{
	if (!pktHdr)
	{
		return;
	}

	if (pktHdr->IsStringCapable(Column_SrcAddr_String))
	{
		std::string s = pktHdr->GetSrcAddrString();
		SetStringValues((uint16_t)Column_SrcAddr_String, s) ;
	}

	if (pktHdr->IsStringCapable(Column_DstAddr_String))
	{
		std::string s = pktHdr->GetDstAddrString();
		SetStringValues(Column_DstAddr_String, s) ;
	}
	
	if (pktHdr->IsStringCapable(Column_Protocol_String))
	{
		std::string s = pktHdr->GetProtocolString();
		SetStringValues(Column_Protocol_String, s) ;
	}

	if (pktHdr->IsStringCapable(Column_Info_String))
	{
		std::string s = pktHdr->GetInfoString();
		SetStringValues(Column_Info_String, s) ;
	}
	
}
