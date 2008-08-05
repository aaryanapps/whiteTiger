#include "StdAfx.h"

#include "NetworkInterfaceAdapterManager.h"
#include "pcap.h"

using namespace wt::framework::capturelibrary;


CCaptureLibraryInterface::CCaptureLibraryInterface()
{

}

CCaptureLibraryInterface::~CCaptureLibraryInterface()
{

}

CCaptureLibraryInterface&
CCaptureLibraryInterface::Instance()
{
	static CCaptureLibraryInterface _am;
	return _am;
}

void
CCaptureLibraryInterface::GetAdaptersList(adapterVec& adVec)
{

	adVec.clear();

	pcap_if_t** ifs = NULL;
	char* err = NULL;

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
CCaptureLibraryInterface::IsAdapterCapturing(std::string& adpName)
{
	return false;
}

bool
CCaptureLibraryInterface::RegisterNewPacketNotification(std::string& adpName,
												Poco::Delegate<CWtObject, WtoHandle>& dl)
{
	return false;
}


bool
CCaptureLibraryInterface::StartCapture(std::string& adpName,
											  Poco::Delegate<CWtObject, WtoHandle>& dl)
{
	return false;
}

