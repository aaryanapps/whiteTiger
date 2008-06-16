#ifndef _WT_CAPTUREDISPLAYGRID_H__
#define _WT_CAPTUREDISPLAYGRID_H__

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/listctrl.h>

class CCapture;

//! Capture Grid Class to list all the packets in the capture.
class CCaptureDisplayGrid : public wxListCtrl
{
public:
    CCaptureDisplayGrid(wxWindow* parent, int id, int size = 1000000);
    ~CCaptureDisplayGrid();
    void Init();
    
    void SetCaptureHnd(uint32_t capId) {m_assCap = capId;}
    
    uint32_t GetCaptureHnd(){return m_assCap;}

    
protected:

    //virtual list ctrl implementation
    virtual int OnGetItemImage(long item) const;
    virtual wxString OnGetItemText(long item, long col) const;

private:

    CCapture* GetCaptureInt() const;
    
	wxWindow *m_parent;
    int m_winId;
    uint32_t m_assCap;
};

#endif // _WT_CAPTUREDISPLAYGRID_H__
