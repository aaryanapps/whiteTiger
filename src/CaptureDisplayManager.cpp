
#include "CaptureDisplayManager.h"
#include "CaptureDisplayGrid.h"
#include "SelectAdapterDialog.h"
#include "CentralCaptureManager.h"
#include "WtObjectDb.h"
#include "Globals.h"

CCaptureDisplayManager::CCaptureDisplayManager(wxWindow *parent) :
    wxNotebook (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT )
{

}

CCaptureDisplayManager::~CCaptureDisplayManager()
{
}

bool CCaptureDisplayManager::AddLiveCapture()
{
    CSelectAdapterDialog cb(this);

    //cb.Create(this);

    if (cb.ShowModal() == wxID_OK)
    {
    	long itemIdx = -1;
        if (!cb.IsAdapterSelected(itemIdx))
        {
        	return false;
        }
        
    	int id = GetNextCaptureGridId();
        
    	std::string sAdptr = cb.GetSelectedAdapter();
    	
        CCentralCaptureManager& cm = CCentralCaptureManager::Instance();
        uint32_t capHnd = cm.StartCapture(sAdptr.c_str());

        CCaptureDisplayGrid *emptyTr = new CCaptureDisplayGrid(this, id);
        if (!emptyTr)
        {
        	if (capHnd != WTOBJECT_HND_NULL)
        	{
        		//TODO:
        		//Stop the capture. 
        		//Remove the capture
        		//Remove all packets and child headers, if any
        	}
        	return false;
        }

        emptyTr->SetCaptureHnd(capHnd);
        
        CapGuiInfo cgi;
        cgi._pn = emptyTr;
        m_captures.insert(std::make_pair(capHnd, cgi));

        wxString _name(sAdptr.c_str(),wxConvUTF8) ;
        this->AddPage(emptyTr, _name, true);
        return true;
    }

    return false;

}

bool CCaptureDisplayManager::AddOfflineCapture(std::vector<std::string>& files)
{
    if (files.empty())
    {
    	CCaptureDisplayGrid *cdg = AddEmptyCaptureGrid();
    	if (!cdg)
    	{
    		return false;
    	}
        return true;
    }

    CCentralCaptureManager& cm = CCentralCaptureManager::Instance();    
    for (uint32_t i = 0; i <  files.size(); ++i)
    {
	    CCaptureDisplayGrid *emptyTr = AddNewGrid();
	    if (!emptyTr)
	    {
	    	//Delete wto capture object.
	    	//Log Error
	    	continue;
	    }
	    
	    uint32_t capHnd = cm.OpenSavedCapture(files.at(i).c_str());
	    if (capHnd == WTOBJECT_HND_NULL)
	    {
	    	delete emptyTr;
	    	continue;
	    }
    	
	    emptyTr->SetCaptureHnd(capHnd);

	    CapGuiInfo cgi;
	    cgi._pn = emptyTr;
	    m_captures.insert(std::make_pair(capHnd, cgi));

	    std::stringstream ss;
	    ss << files.at(i);
	    wxString tmp(ss.str().c_str(), wxConvUTF8);
	    this->AddPage(emptyTr, tmp, true);

    }	
	
	return true;
}


//// Private methods
uint32_t CCaptureDisplayManager::GetNextCaptureGridId()
{
    static uint32_t _next = 50000;
    ++_next;
    return _next;
}

CCaptureDisplayGrid* CCaptureDisplayManager::AddNewGrid(int size)
{
    int id = GetNextCaptureGridId();
	CCaptureDisplayGrid *emptyTr = new CCaptureDisplayGrid(this, id, size);
	if (!emptyTr)
	{
		return NULL;
	}
	
    return emptyTr;
}

CCaptureDisplayGrid* CCaptureDisplayManager::AddEmptyCaptureGrid()
{
	static int emptyId = 0;
	++emptyId;
	
	CCentralCaptureManager& cm = CCentralCaptureManager::Instance();
	uint32_t capHnd = cm.OpenEmptyCapture();
    
	CCaptureDisplayGrid *emp = NULL;
	emp = AddNewGrid(50);
    emp->SetCaptureHnd(capHnd);
    
    std::stringstream ss;
    ss << "Untitled";
    ss << emptyId ;
    wxString tmp(ss.str().c_str(), *wxConvCurrent);
    
    this->AddPage(emp, tmp, true);	
    
    return emp;
}
