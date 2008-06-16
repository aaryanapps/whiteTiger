
#include "CaptureDisplayGrid.h"
#include "wx/wx.h"
#include "Capture.h"
#include "CentralCaptureManager.h"
#include "Packet.h"
#include <iostream>


/*
 * Register for Event Notifications
 */

CCaptureDisplayGrid::CCaptureDisplayGrid(wxWindow *parent, int id, int size) :
            wxListCtrl(parent, id, wxDefaultPosition, wxDefaultSize, wxLC_REPORT| wxLC_VIRTUAL| wxLC_HRULES | wxBORDER_SUNKEN),
            m_parent(parent), m_winId(id), m_assCap(0)
{
    InsertColumn(0, _("No"), wxLIST_FORMAT_LEFT, 50);
    InsertColumn(1, _("Time"), wxLIST_FORMAT_LEFT, 150);
    InsertColumn(2, _("Source"), wxLIST_FORMAT_LEFT, 135);
    InsertColumn(3, _("Destination"), wxLIST_FORMAT_LEFT, 135);
    InsertColumn(4, _("Protocol"), wxLIST_FORMAT_LEFT, 100);
    InsertColumn(5, _("Infomation      "), wxLIST_FORMAT_LEFT, 475);

    //Specify Count
    SetItemCount(size);

    //Specify the 

}

CCaptureDisplayGrid::~CCaptureDisplayGrid()
{
}

void CCaptureDisplayGrid::Init()
{

}

int CCaptureDisplayGrid::OnGetItemImage(long item) const
{
	return 0;
}

wxString CCaptureDisplayGrid::OnGetItemText(long item, long col) const
{

	CCapture* cp = this->GetCaptureInt();
	CPacket *pkt = NULL;
	if (cp)
	{
		pkt = cp->GetPacketAt(item);
		if (pkt)
		{
			std::stringstream ss;
			std::string s;
			switch(col){
			case 0:
				ss << item;
				return wxString(ss.str().c_str(), *wxConvCurrent);
			case 1:
				s = pkt->GetTimeStamp();
				return wxString(s.c_str(), *wxConvCurrent);
			case 2:
				s = pkt->GetSrcAddr();
				return wxString(s.c_str(), *wxConvCurrent);
			case 3:
				s = pkt->GetDstAddr();
				return wxString(s.c_str(), *wxConvCurrent);
			case 4:
				s = pkt->GetProtocol();
				return wxString(s.c_str(), *wxConvCurrent);
			case 5:
				s = pkt->GetInfoText();
				return wxString(s.c_str(), *wxConvCurrent);
			default:
				return wxString(_T(""));
			}
		}
	}
	
	return wxString(_T(""));
}


CCapture* CCaptureDisplayGrid::GetCaptureInt() const
{
	if (m_assCap == 0)
		return NULL;
	
	return CCentralCaptureManager::Instance().GetCapture(m_assCap);	
}
