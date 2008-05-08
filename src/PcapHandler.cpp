
#include "PcapHandler.h"
#include "Poco/Thread.h"
#include "LiveCapture.h"
#include "WtObjectDb.h"
#include <iostream>
#include "WtObject.h"
#include "OfflineCapture.h"

using namespace Poco;

CPcapHandler::CPcapHandler()
{
}

CPcapHandler::~CPcapHandler()
{
}

CPcapHandler& CPcapHandler::Instance()
{
    static CPcapHandler _ph;
    return _ph;
}


WtoHandle CPcapHandler::StartLiveCapture(std::string& dev)
{

    if (IsCaptureRunning(dev))
    {
        return GetCaptureIdFromString(dev);
    }

    /*Create Env for the New capture*/
    uint32_t cid = CreateLiveCapture(dev);
    
    /* Start a new Live Capture */
    StartLiveCapture(cid);

    return cid;
}


bool CPcapHandler::StopLiveCapture(uint32_t capHnd)
{

    CaptureDetailsMap::iterator cit = m_capDetails.find(capHnd);

    if (cit == m_capDetails.end())
    {
        return false;
    }
	
	//Call breakLoop
    pcap_breakloop(cit->second._capDesc);
    
    //Wait for the thread to stop
    
    //Cleanup
	return true;
}

WtoHandle CPcapHandler::ParseOfflineFile(std::string& fname)
{
	//TODO check if file exists or not.
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t * hnd;	
    hnd = pcap_open_offline(fname.c_str(), errbuf);
    if (hnd == NULL)
    {
        //TODO: Log Error and print pcap error message
    	return WTOBJECT_HND_NULL;
    }

    CWtObject *wobj = dynamic_cast<CWtObject *> (new COfflineCapture());

    //Get from wtodb
    CWtObjectDb& wdb = CWtObjectDb::Instance();
    WtoHandle wHnd = wdb.AddObject(wobj);

    if (wHnd == WTOBJECT_HND_NULL)
    {
    	pcap_close(hnd);
        return WTOBJECT_HND_NULL;
    }
    
    //TODO: Add parent child relation, parent = system
    
    PcapHandle p = GetNextPcapHnd();
    m_pcapHnds.insert(std::make_pair(p, hnd));
	wobj->SetWtoHandle(wHnd);
	COfflineCapture* cap = dynamic_cast<COfflineCapture *>(wobj);
	cap->SetPcapHandle(p);
	cap->run();
    
	return wHnd;
}



bool CPcapHandler::RegisterNewPacketNotification(WtoHandle dev,
                                            Poco::Delegate<CBoundCapture, PacketHandle>& dl)
{
    CaptureDetailsMap::iterator cit = m_capDetails.find(dev);

    if (cit == m_capDetails.end())
    {
        return false;
    }
    
    CWtObjectDb& wdb = CWtObjectDb::Instance();
    CLiveCapture * lc = dynamic_cast<CLiveCapture*> (wdb.GetObject(cit->second._lvCap));    
    if (lc)
    {
    	lc->NewNetworkPacket += dl;
    	return true;
    }

    return false;
}

void CPcapHandler::CleanUp(uint32_t capHnd)
{
    std::string tmp = GetCaptureStringFromId(capHnd);
    RemoveLiveCapture(tmp);
    RemoveLiveCapture(capHnd);
    
}


/////////// ////////// ///////  Private methods

bool CPcapHandler::IsCaptureRunning(std::string& dev)
{
    dev2IdMap::const_iterator dit = m_actCaptures.find(dev);
    if (dit != m_actCaptures.end())
    {
        return true;
    }
    else
    {
        return false;
    }

}

uint32_t CPcapHandler::GetCaptureIdFromString(std::string& dev)
{
    dev2IdMap::const_iterator dit = m_actCaptures.find(dev);
    if (dit != m_actCaptures.end())
    {
        return dit->second;
    }
    else
    {
        return 0;
    }

}

std::string CPcapHandler::GetCaptureStringFromId(uint32_t capHnd)
{
    CaptureDetailsMap::iterator cit = m_capDetails.find(capHnd);

    if (cit != m_capDetails.end())
    {
        return cit->second._devName;
    }
    else
    {
        return "";
    }

}

uint32_t CPcapHandler::GetNextCaptureId(std::string& dev)
{
    static uint32_t _next = 1;
    
    dev2IdMap::const_iterator dit = m_actCaptures.find(dev);
    if (dit != m_actCaptures.end())
    {
        //Should not reach here. Some clean was not done properly
        return INVALID_LV_CAP_ID;
    }

    ++_next;
    m_actCaptures.insert(std::make_pair(dev,_next));

    return _next;
}

uint32_t CPcapHandler::GetNextPcapHnd()
{
    static uint32_t _next = 1000;
    ++_next;
    return _next;
}

bool CPcapHandler::StartLiveCapture(uint32_t capHnd)
{
    CaptureDetailsMap::iterator cit = m_capDetails.find(capHnd);

    if (cit == m_capDetails.end())
    {
        return false;
    }

    CWtObjectDb& wdb = CWtObjectDb::Instance();
    CLiveCapture * lc = dynamic_cast<CLiveCapture*> (wdb.GetObject(cit->second._lvCap));    
    if (lc)
    {
    	cit->second._th->start(*lc);
    	return true;
    }

    return false;
}


pcap_t* CPcapHandler::GetCaptureDesc(uint32_t capHnd)
{
    CaptureDetailsMap::iterator cit = m_capDetails.find(capHnd);

    if (cit == m_capDetails.end())
    {
        return INVALID_PCAP_HND;
    }
    return GetCaptureDesc(cit->second._pcapHnd);
}

pcap_t* CPcapHandler::GetPcapDesc(PcapHandle pHnd)
{
    PcapHnd2DescMap::iterator pit = m_pcapHnds.find(pHnd);

    if (pit == m_pcapHnds.end())
    {
        return INVALID_PCAP_HND;
    }
    return pit->second;
}

uint32_t CPcapHandler::CreateLiveCapture(std::string& dev)
{
   
    CLiveCapture *lc = new CLiveCapture(dev);
    if (!lc)
    {
        return INVALID_LV_CAP_ID;
    }
    
    CWtObjectDb& wdb = CWtObjectDb::Instance();
    WtoHandle wHnd = wdb.AddObject((CWtObject *)lc);
    
    if (WTOBJECT_HND_NULL == wHnd)
    {
    	delete lc;
    	return INVALID_LV_CAP_ID;
    }
    
    lc->SetWtoHandle(wHnd);
    
	m_actCaptures.insert(std::make_pair(dev,wHnd));
	
	LiveCaptureDetails cd ;
	cd._devName = dev;
	cd._lvCap = wHnd;
	
	if (!m_capDetails.insert(std::make_pair(wHnd,cd)).second)
	{
	    std::cout << "Error occured while entering new Capture Details"
	            << std::endl;
	    return INVALID_LV_CAP_ID;
	}

	if (!CreateLiveCaptureEnv(wHnd))
    {
		delete lc;
		wdb.RemoveObject(wHnd);
        return INVALID_LV_CAP_ID;    
    }
    
    /* Open interface for capture */
    if (!PrepareLiveCaptureInterface(wHnd))
    {
        CleanUp(wHnd);
        return INVALID_LV_CAP_ID;
    }
    
    return wHnd;
}


bool CPcapHandler::CreateLiveCaptureEnv(WtoHandle capHnd)
{
    CaptureDetailsMap::iterator cit = m_capDetails.find(capHnd);
    if (cit == m_capDetails.end())
    {
        return false;
    }
 
    std::string thName("Capture") ;
    thName += " " ;
    thName += cit->second._devName ;
    thName += "( " ;
    thName += capHnd ;
    thName += " )" ;
    
    Thread *th = new Thread(thName);
    if (!th)
    {
        m_capDetails.erase(cit);
        return false;
    }

    cit->second._th = th;

    th->setPriority(Poco::Thread::PRIO_NORMAL);

    return true;
}

bool CPcapHandler::PrepareLiveCaptureInterface(WtoHandle capHnd)
{
    CaptureDetailsMap::iterator cit = m_capDetails.find(capHnd);

    if (cit == m_capDetails.end())
    {
        return false;
    }

    char Errbuf[PCAP_ERRBUF_SIZE];
    pcap_t * hnd;
    hnd = pcap_open_live (cit->second._devName.c_str(), 65535, 0, 0, Errbuf);

    if (hnd == NULL)
    {
        return false;
    }
    
    //Get from wtodb
    CWtObjectDb& wdb = CWtObjectDb::Instance();
    CLiveCapture * lc = dynamic_cast<CLiveCapture*> (wdb.GetObject(capHnd));

    if (lc)
    {
        PcapHandle p = GetNextPcapHnd();
        m_pcapHnds.insert(std::make_pair(p, hnd));
        cit->second._pcapHnd = p;
    	lc->SetPcapHandle(p);
    	return true;
    }
    else
    {
    	//close Pcap desc
    	pcap_close(hnd);
    }
    
    return false;
}


void CPcapHandler::RemoveLiveCapture(std::string& dev)
{
    dev2IdMap::iterator dit = m_actCaptures.find(dev);
    if (dit != m_actCaptures.end())
    {
        m_actCaptures.erase(dit);
    }
    
}

void CPcapHandler::RemoveLiveCapture(uint32_t capHnd)
{
    CaptureDetailsMap::iterator cit = m_capDetails.find(capHnd);
    if (cit != m_capDetails.end())
    {
        if (cit->second._lvCap)
        {
            CWtObjectDb& wdb = CWtObjectDb::Instance();
            CLiveCapture * lc = dynamic_cast<CLiveCapture*> (wdb.GetObject(cit->second._lvCap));        	
            delete lc;
        }
        
        if (cit->second._th)
        {
            delete cit->second._th;
        }
    }
}
