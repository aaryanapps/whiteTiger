#include "StdAfx.h"

#include "NetworkInterfaceAdapter.h"
#include "WtLogger.h"
#include "Poco/BasicEvent.h"
#include "Poco/Thread.h"

using namespace wt::framework::networkintf;


DEFINE_STATIC_LOGGER("frmwrk.netintf.NetworkInterfaceAdapter", devLogger)

CNetworkInterfaceAdapter::CNetworkInterfaceAdapter(std::string& adpName) :
													_pPcapDesc(NULL),
													_strAdapName(adpName),													
													_pThread(NULL)
{
	
	
}

CNetworkInterfaceAdapter::~CNetworkInterfaceAdapter()
{
	if (_pPcapDesc)
	{
    	//close Pcap desc
    	pcap_close(_pPcapDesc);
	}
	
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

bool CNetworkInterfaceAdapter::InitAdapter()
{
    char Errbuf[PCAP_ERRBUF_SIZE];

    _pPcapDesc = pcap_open_live (_strAdapName.c_str(), 65535, 0, 0, Errbuf);

    if (_pPcapDesc == NULL)
    {
        return false;
    }
    
    return true;
}


void CNetworkInterfaceAdapter::run()
{
    pcap_t *cDesc = _pPcapDesc;
    uint8_t *uData = (uint8_t *) (this);
    int32_t ret = pcap_loop(cDesc,-1, &CNetworkInterfaceAdapter::OnNewPacket, 
    						 uData);
    if (ret == -1)
    {
    	//TODO: Log Error
    }
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

void CNetworkInterfaceAdapter::NotifyNewPacket(WtoHandle pHnd)
{
	NewNetworkPacket.notifyAsync((CWtObject*)this, pHnd);

	std::stringstream ss;
	ss 	<< "Sent new Packet Notification on Adapter: " 
		<< this->_strAdapName ;
	
	LOG_DEBUG( devLogger() , ss.str() );
	
	return;
}
