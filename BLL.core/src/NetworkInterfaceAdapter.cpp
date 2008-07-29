#include "StdAfx.h"

#include "NetworkInterfaceAdapter.h"
#include "NetworkInterfaceAdapterManager.h"
#include "WtLogger.h"
#include "CaptureLibraryInterface.h"
#include "Poco/BasicEvent.h"
#include "Poco/Thread.h"

using namespace wt::framework::networkintf;
using namespace wt::framework::capturelibrary;


DEFINE_STATIC_LOGGER("frmwrk.netintf.NetworkInterfaceAdapter", devLogger)

CNetworkInterfaceAdapter::CNetworkInterfaceAdapter(std::string& adpName) :
													_strAdapName(adpName),
													_pThread(NULL),
													_captureStatus(CAPTURE_IDLE),
													_capLibInt(NULL)
{
	_capLibInt = new CCaptureLibraryInterface(adpName);

}

CNetworkInterfaceAdapter::~CNetworkInterfaceAdapter()
{

}

bool CNetworkInterfaceAdapter::RegisterOnNewPacket(Poco::Delegate<CWtObject, WtoHandle>& dl)
{

	NewNetworkPacket += dl;

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
	_captureStatus = CAPTURE_RUNNING;
	int32_t ret = _capLibInt->Capture();
    if (ret == -1)
    {
    	_captureStatus = CAPTURE_STOPPED;
    	//TODO: Log Error
    	LOG_ERROR( devLogger() , "Error occured when Capture stopped on Adapter: " );
    	return;
    }
}

bool CNetworkInterfaceAdapter::StartCapture()
{
	_captureStatus = CAPTURE_BEING_STARTED;

	//Start the Thread. i.e capture
	_pThread->start(*this);

	return true;

}

// Private

bool CNetworkInterfaceAdapter::CreateThread()
{
	std::stringstream thName;
    thName << "Capture on Network Adapter :" << _strAdapName ;

    _pThread = new Poco::Thread(thName.str());
    if (!_pThread)
    {
        return false;
    }

    _pThread->setPriority(Poco::Thread::PRIO_NORMAL);

    return false;
}

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
	NewNetworkPacket.notifyAsync((CWtObject*)this, pHnd);

	std::stringstream ss;
	ss 	<< "Sent new Packet Notification on Adapter: "
		<< this->_strAdapName ;

	LOG_DEBUG( devLogger() , ss.str() );

	return;
}
