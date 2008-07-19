
#include "NetworkInterfaceAdapterManager.h"
#include "pcap.h"

using namespace wt::framework::networkintf;


CNetworkInterfaceAdapterManager::CNetworkInterfaceAdapterManager()
{
	
}

CNetworkInterfaceAdapterManager::~CNetworkInterfaceAdapterManager()
{
	
}

CNetworkInterfaceAdapterManager& 
CNetworkInterfaceAdapterManager::Instance()
{
	static CNetworkInterfaceAdapterManager _am;
	return _am;
}

void 
CNetworkInterfaceAdapterManager::GetAdaptersList(adapterVec& adVec)
{

	adVec.clear();
	
	pcap_if_t** ifs;
	char* err;
	
    // Retrieve the interfaces list
    if (pcap_findalldevs(ifs, err) == -1)
    {
    	//TODO: Log the error
        return;
    }

    if (ifs == NULL)
    {
    	//TODO: Log Warn in log
        return;
    }

    while (*ifs)
    {
        if ((*ifs)->name)
        {
    		adVec.push_back(std::string((*ifs)->name));
        }
        
        (*ifs) = (*ifs)->next;
    }
    
	return;
}


bool 
CNetworkInterfaceAdapterManager::IsAdapterCapturing(std::string& adpName)
{
	
	return false;
}

bool 
CNetworkInterfaceAdapterManager::RegisterNewPacketNotification(std::string& adpName,
												Poco::Delegate<CWtObject, WtoHandle>& dl)
{
	return false;
}


bool
CNetworkInterfaceAdapterManager::StartCapture(std::string& adpName,
											  Poco::Delegate<CWtObject, WtoHandle>& dl)
{
	return false;
}
