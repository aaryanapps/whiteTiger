#include "StdAfx.h"

#include "EthernetPacket.h"
#include "net/HeaderTypes.h"
#include "CommonPacketUtils.h"
#include "PacketHeader.h"
#include "WtDataStore.h"
#include "CoreConsts.h"
#include "WtObjectDb.h"
#include "RelationInfo.h"
#include "WtLogger.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"
#include "PacketHeaderFactory.h"
#include "CaptureLibraryDefs.h"

using namespace wt::core;
using namespace wt::framework;

//uint32_t CEthernetPacket::m_classId = CEthernetPacket_Class_Id ;
uint32_t CEthernetPacket::m_classId = REGISTER_CREATOR(CEthernetPacket_Class_Id, CEthernetPacket::Create);


DEFINE_STATIC_LOGGER("core.EthernetPacket", devLogger)


CEthernetPacket::CEthernetPacket()
{
	AddAsDerivedClassId(CEthernetPacket_Class_Id);
}

CEthernetPacket::~CEthernetPacket()
{

}

CWtObject* CEthernetPacket::Create()
{
	return new CEthernetPacket();
}

bool CEthernetPacket::Init(wt::core::capturelibrary::CapturedPkt* pkt)
{
	CPacket::Init(pkt);

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
	wt::framework::CWtDataStore &ds = wt::framework::CWtDataStore::Instance();
	CPacketHeaderFactory &phf = CPacketHeaderFactory::Instance();

	uint32_t hdrOffset = 0 ;
	uint32_t hdr = WT_ETH ;
	WtoHandle curHnd ;
	WtoHandle preHnd ;
	bool status = true ;
	bool isFirstHdr = true ;
	std::stringstream dbg;

	for (; hdr != WT_UNKWN; )
	{
		curHnd = ds.AddObject(phf.GetClassIdForHdrType(hdr), (CWtObject*)this);

		if (WTOBJECT_HND_NULL == curHnd)
		{
			/*Unknown header or insufficient memory.
			 */
			hdr = WT_UNKWN;
			status = false;
			continue;
		}

		CPacketHeader *pktHdr = dynamic_cast<CPacketHeader *>(ds.GetObjectFromHnd(curHnd));

		pktHdr->Init(hdrOffset, &(m_pktData.front()));

		if (isFirstHdr)
		{
			ds.AddRelationship(GetWtoHandle(), curHnd, RelationType(BottomMostHeader()));
		}
		else
		{
			ds.AddRelationship(GetWtoHandle(), curHnd, RelationType(StackedOnHeader()));
			dbg << " : " ;
		}

		OnNewPacketHeader(pktHdr);

		hdrOffset += pktHdr->GetHeaderLength();
		hdr = pktHdr->HeaderToCreateNext();
		isFirstHdr = false;
		preHnd = curHnd;
		dbg << pktHdr->GetHeaderAbbrName();
	}

	if (WTOBJECT_HND_NULL != curHnd)
	{
		//Add TopMostHeader Relation
		ds.AddRelationship(GetWtoHandle(), curHnd, RelationType(TopMostHeader()));
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
