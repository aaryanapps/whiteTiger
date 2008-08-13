#include "StdAfx.h"

#include "NetworkInterfaceAdapter.h"
#include "CaptureLibraryInterface.h"
#include "CoreConsts.h"
#include "PacketDb.h"
#include "WtLogger.h"
#include "FastDelegate.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"

#include "Poco/BasicEvent.h"
#include "Poco/Thread.h"

using namespace wt::core;
using namespace wt::core::capturelibrary;
using namespace wt::framework;

uint32_t CNetworkInterfaceAdapter::m_classId = REGISTER_CREATOR(CNetworkInterfaceAdapter_Class_Id, CNetworkInterfaceAdapter::Create);

DEFINE_STATIC_LOGGER("core.netintf.NetworkInterfaceAdapter", devLogger)

CNetworkInterfaceAdapter::CNetworkInterfaceAdapter(std::string& adpName) :
													_strAdapName(adpName),
													_captureStatus(CAPTURE_IDLE)
{

	_dNewPkt = fastdelegate::MakeDelegate(this, &CNetworkInterfaceAdapter::OnNewPacket);



}

CNetworkInterfaceAdapter::~CNetworkInterfaceAdapter()
{

}

CWtObject* CNetworkInterfaceAdapter::Create()
{
	std::string s("Default");
	return new CNetworkInterfaceAdapter(s);
}

bool CNetworkInterfaceAdapter::RegisterOnNewPacket(Poco::Delegate<CWtObject, WtoHandle>& dl)
{

	NewPacket += dl;

	return true;
}

bool CNetworkInterfaceAdapter::StartCapture()
{
	SetCaptureStatus (CAPTURE_BEING_STARTED);

	bool ret = false;

	/* Get CaptureLibraryInterface Instance
	 * Register for new packet notification
	 * StartCapture
	 */

	CCaptureLibraryInterface& cli = CCaptureLibraryInterface::Instance();

	ret = cli.StartCapture(_strAdapName);

	if ( !ret )
    {
    	SetCaptureStatus (CAPTURE_STOPPED);
    	LOG_ERROR( devLogger() , "Error occured when starting Capture on Adapter: " );
    	return false;
    }
	else
	{
		return true;
	}

	return false;
}

// Private

void CNetworkInterfaceAdapter::NotifyNewPacket(WtoHandle pHnd)
{
	NewPacket.notifyAsync((CWtObject*)this, pHnd);

	std::stringstream ss;
	ss 	<< "Sent new Packet Notification on Adapter: "
		<< this->_strAdapName ;

	LOG_DEBUG( devLogger() , ss.str() );

	return;
}


void CNetworkInterfaceAdapter::OnNewPacket(CapturedPkt* pkt, void* data)
{
	LOG_DEBUG(devLogger(), "Received new packet notification");

	//TODO: Addlogic to process new packet notification
	/*
    CPacketDb& pdb = CPacketDb::Instance();
    WtoHandle pktHnd = pdb.AddNewPacket(this->GetWtoHandle(),
    									this->GetDataLinkType(),
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

	 */

	return;
}

