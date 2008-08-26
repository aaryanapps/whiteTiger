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

using namespace wt::core;
using namespace wt::framework;

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
									  wt::core::capturelibrary::CapturedPkt* pkt,
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

	return pktObj;

}

uint32_t CPacketParser::GetClassIdToCreate(uint32_t datalink)
{
	return CEthernetPacket_Class_Id;
}


