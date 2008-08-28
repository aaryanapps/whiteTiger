/*
 * PacketParser.cpp
 *
 *  Created on: Aug 25, 2008
 *      Author: smehta
 */

#include "StdAfx.h"
#include "PacketParser.h"
#include "Packet.h"
#include "WtObjectDefs.h"
#include "WtLogger.h"
#include "CoreConsts.h"
#include "WtDataStore.h"
#include "CaptureLibraryDefs.h"
#include "WtDataStore.h"
#include "net/HeaderTypes.h"
#include "RelationInfo.h"
#include "PacketHeaderFactory.h"

using namespace wt::core;
using namespace wt::framework;
using namespace wt::core::capturelibrary;

DEFINE_STATIC_LOGGER("core.PacketParser", devLogger)

CPacketParser::CPacketParser()
{

}

CPacketParser::~CPacketParser()
{

}

CPacketParser& CPacketParser::Instance()
{
	static CPacketParser pp;

	return pp;
}

CWtObject* CPacketParser::ParsePacket(CWtObject* parent,
									  CapturedPkt* pkt,
									  uint32_t dataLink)
{
	if (NULL == parent)
	{
		LOG_ERROR(devLogger() , "No Parent Capture for packet")
		return WTOBJECT_HND_NULL;
	}

	uint32_t clsId = GetClassIdToCreate(dataLink);

	CWtDataStore &ds = CWtDataStore::Instance();

	WtoHandle pktHnd = ds.AddObject(clsId, parent);
	CPacket* pktObj = dynamic_cast<CPacket* > (ds.GetObjectFromHnd(pktHnd));

	if (WTOBJECT_HND_NULL == pktObj)
	{
		//TODO: Log Error
		return pktObj;
	}

	pktObj->Init(pkt);

	CreateHeaders(pktObj,pkt);

	return pktObj;

}

uint32_t CPacketParser::GetClassIdToCreate(uint32_t datalink)
{
	return CEthernetPacket_Class_Id;
}


bool CPacketParser::CreateHeaders(CPacket* parentPkt, CapturedPkt* pkt)
{

	if (NULL == parentPkt || NULL == pkt)
	{
		return false;
	}

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
		curHnd = ds.AddObject(phf.GetClassIdForHdrType(hdr), (CWtObject*)parentPkt);

		if (WTOBJECT_HND_NULL == curHnd)
		{
			/*
			 * Unknown header or insufficient memory.
			 */
			hdr = WT_UNKWN;
			status = false;
			continue;
		}

		CPacketHeader *pktHdr = dynamic_cast<CPacketHeader *>(ds.GetObjectFromHnd(curHnd));


		pktHdr->Init(hdrOffset, &(pkt->_pktData.front()));

		if (isFirstHdr)
		{
			ds.AddRelationship(parentPkt->GetWtoHandle(), curHnd, RelationType(BottomMostHeader()));
		}
		else
		{
			ds.AddRelationship(parentPkt->GetWtoHandle(), curHnd, RelationType(StackedOnHeader()));
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
		ds.AddRelationship(parentPkt->GetWtoHandle(), curHnd, RelationType(TopMostHeader()));
	}

	LOG_INFO( devLogger(), dbg.str()) ;

	return status;
}

void CPacketParser::OnNewPacketHeader(CPacketHeader* pktHdr)
{
	if (NULL == pktHdr)
	{
		//TODO: LOG ERROR. Should not happen!
		return;
	}

	CPacket* parentPkt = dynamic_cast<CPacket*> (pktHdr->GetParent());

	if (pktHdr->IsStringCapable(Column_SrcAddr_String))
	{
		std::string s = pktHdr->GetSrcAddrString();
		parentPkt->SetStringValues((uint16_t)Column_SrcAddr_String, s) ;
	}

	if (pktHdr->IsStringCapable(Column_DstAddr_String))
	{
		std::string s = pktHdr->GetDstAddrString();
		parentPkt->SetStringValues(Column_DstAddr_String, s) ;
	}

	if (pktHdr->IsStringCapable(Column_Protocol_String))
	{
		std::string s = pktHdr->GetProtocolString();
		parentPkt->SetStringValues(Column_Protocol_String, s) ;
	}

	if (pktHdr->IsStringCapable(Column_Info_String))
	{
		std::string s = pktHdr->GetInfoString();
		parentPkt->SetStringValues(Column_Info_String, s) ;
	}

}
