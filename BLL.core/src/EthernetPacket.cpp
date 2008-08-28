#include "StdAfx.h"

#include "EthernetPacket.h"
#include "CommonPacketUtils.h"
#include "PacketHeader.h"
#include "WtDataStore.h"
#include "CoreConsts.h"
#include "WtObjectDb.h"
#include "WtLogger.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"
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

