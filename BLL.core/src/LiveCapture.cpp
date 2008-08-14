#include "StdAfx.h"

#include "LiveCapture.h"
#include "Packet.h"
#include "Globals.h"
#include "CoreConsts.h"
#include "WtLogger.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"

using namespace wt::core;
using namespace wt::framework;

//DEFINE_STATIC_LOGGER("core.LiveCapture", devLogger)

//uint32_t CLiveCapture::m_classId = 0x00000264 ;
uint32_t CLiveCapture::m_classId = REGISTER_CREATOR(CLiveCapture_Class_Id, CLiveCapture::Create);

CLiveCapture::CLiveCapture()
{

}

CLiveCapture::CLiveCapture(std::string& name)
{

}

CWtObject* CLiveCapture::Create()
{
	return new CLiveCapture();
}

CLiveCapture::~CLiveCapture()
{

}

void CLiveCapture::Init()
{

}


/* Callback function invoked for every incoming packet */
void CLiveCapture::OnNewPacket(WtoHandle pkt, void *data)
{


	//TODO: Fix this. Here the packet handle is received and already populated.
	//
/*
	CLiveCapture *self = (CLiveCapture *) (data);

    CPacketDb& pdb = CPacketDb::Instance();
    WtoHandle pktHnd = pdb.AddNewPacket(self->GetWtoHandle(),
    									self->GetDataLinkType(),
										header, pkt_data);


    CPacket* pkt = pdb.GetPacket(pktHnd);
    if (pkt)
    {
    	std::stringstream ss;
    	ss << pkt->GetTimeStamp()
    			  << ", Length: " <<
					pkt->GetPacketLength();

    	LOG_ERROR( devLogger() , ss.str() );

    }
    else
    {
    	// Could not create the Packet
    	// Various Reasons: no memory, unsupported datalink, etc
    	//
    }

    self->AddPacketToMap(pktHnd);
    self->NotifyNewPacket(pktHnd);
*/
}

void CLiveCapture::NotifyNewPacket(WtoHandle pHnd)
{
    //NewNetworkPacket.notifyAsync((CWtObject*)this, pHnd);
}


bool CLiveCapture::RegisterNewPacketNotification()
{
	return false;
}

