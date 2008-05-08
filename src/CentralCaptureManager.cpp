
#include "CentralCaptureManager.h"
#include "PcapHandler.h"
#include "BoundCapture.h"
#include "Poco/Thread.h"
#include "WtObjectDb.h"
#include "OfflineCapture.h"

CCentralCaptureManager::CCentralCaptureManager()
{
}


CCentralCaptureManager::~CCentralCaptureManager()
{
}

CCentralCaptureManager& CCentralCaptureManager::Instance()
{
    static CCentralCaptureManager _ccm;
    return _ccm;
}

uint32_t CCentralCaptureManager::StartCapture(const char* devName)
{
    std::string _dev(devName);
    CPcapHandler& ph = CPcapHandler::Instance();

    WtoHandle capHnd = ph.StartLiveCapture(_dev);
    return capHnd;
}

bool CCentralCaptureManager::StopCapture(uint32_t capHnd)
{
	return true;
}

bool CCentralCaptureManager::SaveCapture(uint32_t capHnd)
{
	return true;
}

uint32_t CCentralCaptureManager::OpenSavedCapture(const char* fName)
{
	std::string file(fName);
	CPcapHandler& ph = CPcapHandler::Instance();
	
	WtoHandle wHnd = ph.ParseOfflineFile(file);
	if(wHnd == WTOBJECT_HND_NULL)
	{
		//TODO: Log Error
		return WTOBJECT_HND_NULL;
	}
	
	return wHnd;
	
}

uint32_t CCentralCaptureManager::OpenEmptyCapture()
{
//    CWtObject *wobj = dynamic_cast<CWtObject *> (new COfflineCapture());
    CWtObject *wobj = new COfflineCapture();

    //Get from wtodb
    CWtObjectDb& wdb = CWtObjectDb::Instance();
    WtoHandle wHnd = wdb.AddObject(wobj);

    if (wHnd == WTOBJECT_HND_NULL)
    {
    	//Log Error
    	return WTOBJECT_HND_NULL;
    }

    wobj->SetWtoHandle(wHnd);
    
    return wHnd;
	
}


CCapture * CCentralCaptureManager::GetCapture(uint32_t capId)
{
    if (capId == 0)
    	return NULL;
    CWtObjectDb& wdb = CWtObjectDb::Instance();
    CCapture * cc = dynamic_cast <CCapture*> (wdb.GetObject(capId)); 
    return cc;
}

//Private methods

uint32_t CCentralCaptureManager::GetNextCaptureId()
{
    static uint32_t _next = 1;
    ++_next;
    return _next;
}

