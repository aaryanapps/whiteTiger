#include "StdAfx.h"

#include "CaptureLibraryInterface.h"
#include "CaptureLibraryAdapter.h"
#include "WtLogger.h"

#include "pcap.h"

#include "Poco/Thread.h"

using namespace wt::core::capturelibrary;

DEFINE_STATIC_LOGGER("bll.core.CaptureLibraryInterface", devLogger)

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

	//TODO: MayBe? Check if AdapterList is already populated

	pcap_if_t** ifs = NULL;
	char* err = NULL;

    // Retrieve the interfaces list
    if (pcap_findalldevs(ifs, err) == -1)
    {
    	LOG_ERROR( devLogger() , "Error occurred while fetching list of interfaces")
    	return;
    }

    if (ifs == NULL)
    {
    	//TODO: Log Warn in log
    	LOG_WARN( devLogger() , "No Interface found for capture")
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
	//Search for adapter in map
	ActiveAdapters::iterator ait = _mActAdapters.find(adpName);

	if (ait != _mActAdapters.end())
	{
		//Found adapter in list. Query the Object.
		return ait->second._capLibAdp->IsCaptureRunning();
	}
	return false;
}

uint32_t
CCaptureLibraryInterface::RegisterNewPacketNotification(std::string& adpName,
												NewPktDelegateInfo* pktDelInfo)
{
	static uint32_t _regId = 0;

	if (AdapterExists(adpName))
	{
		_regId++;
		bool ret = GetCaptureLibraryAdp(adpName)->RegisterNewPacketNotification(_regId,
												pktDelInfo);

		if (!ret)
		{
			return 0;
		}
		else
		{
			return _regId;
		}

	}
	else
	{
		return 0;
	}
}


bool
CCaptureLibraryInterface::StartCapture(std::string& adpName)
{
	if (AdapterExists(adpName))
	{
		if (GetCaptureLibraryAdp(adpName)->IsCaptureRunning())
		{
			return true;
		}
		else
		{
			if (!StartCaptureInThread(adpName))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	return false;
}



// Private

bool CCaptureLibraryInterface::CreateCaptureLibraryAdapter(std::string& adpName)
{

	ActiveAdapters::const_iterator ait = _mActAdapters.find(adpName);

	if (ait != _mActAdapters.end())
	{
		return true;
	}

	CCaptureLibraryAdapter* capAdp = new CCaptureLibraryAdapter(adpName);

	if (NULL == capAdp)
	{
		return false;
	}
	else
	{
		Poco::Thread* pTh = CreateThreadForAdp(adpName);
		if (NULL == pTh)
		{
			delete capAdp;
			return false;
		}
		else
		{
			AdapterInfo adpInfo;
			adpInfo._capLibAdp = capAdp;
			adpInfo._pThread = pTh;

			_mActAdapters.insert(std::make_pair(adpName,adpInfo));
			//TODO: Check if added to map. If not, delete both objects.
		}
		return true;
	}

	return false;
}

Poco::Thread* CCaptureLibraryInterface::CreateThreadForAdp(std::string& adpName)
{
	std::stringstream thName;
    thName << "Interface: " << adpName ;

    Poco::Thread* _pThread = new Poco::Thread(thName.str());
    if (NULL == _pThread)
    {
        return NULL;
    }

    _pThread->setPriority(Poco::Thread::PRIO_NORMAL);

    return _pThread;
}

Poco::Thread* CCaptureLibraryInterface::GetThreadForAdp(std::string& adpName)
{
	ActiveAdapters::const_iterator ait = _mActAdapters.find(adpName);

	if (ait != _mActAdapters.end())
	{
		return ait->second._pThread;
	}

	return NULL;
}

CCaptureLibraryAdapter*
CCaptureLibraryInterface::GetCaptureLibraryAdp(std::string& adpName)
{
	ActiveAdapters::const_iterator ait = _mActAdapters.find(adpName);

	if (ait != _mActAdapters.end())
	{
		return ait->second._capLibAdp;
	}

	return NULL;
}


bool CCaptureLibraryInterface::StartCaptureInThread(std::string& adpName)
{
	Poco::Thread* pTh = GetThreadForAdp(adpName);

	if (NULL == pTh)
	{
		return false;
	}
	else
	{
		pTh->start(*GetCaptureLibraryAdp(adpName));
	}


	return false;
}


bool CCaptureLibraryInterface::AdapterExists(std::string& adpName)
{
	ActiveAdapters::const_iterator ait = _mActAdapters.find(adpName);

	if (ait != _mActAdapters.end())
	{
		return true;
	}

	return false;
}
