#include "StdAfx.h"

#include "NetworkInterfaceAdapter.h"
#include "CaptureLibraryInterface.h"

#include "WtLogger.h"
#include "FastDelegate.h"

#include "Poco/BasicEvent.h"
#include "Poco/Thread.h"

using namespace wt::core::networkintf;
using namespace wt::core::capturelibrary;
using namespace wt::framework;

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

bool CNetworkInterfaceAdapter::RegisterOnNewPacket(Poco::Delegate<CWtObject, WtoHandle>& dl)
{

	NewPacket += dl;

	return true;
}

/* prototype of the packet handler */
void CNetworkInterfaceAdapter::OnNewPacket(u_char *param,
						const struct pcap_pkthdr *header,
						const u_char *pkt_data)
{
	return;
}


void CNetworkInterfaceAdapter::run()
{
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

	ret = cli.StartCapture();

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


bool CNetworkInterfaceAdapter::InitAdapter()
{
	if (_capLibInt->InitInterface())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CNetworkInterfaceAdapter::NotifyNewPacket(WtoHandle pHnd)
{
	NewPacket.notifyAsync((CWtObject*)this, pHnd);

	std::stringstream ss;
	ss 	<< "Sent new Packet Notification on Adapter: "
		<< this->_strAdapName ;

	LOG_DEBUG( devLogger() , ss.str() );

	return;
}


void CNetworkInterfaceAdapter::OnNewPacket(WtoHandle pktHnd, void* data)
{
	LOG_DEBUG(devLogger(), "Received new packet notification");
	return;
}

