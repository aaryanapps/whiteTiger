#ifndef _WT_CAPTUREDISPLAYMANAGER_H__
#define _WT_CAPTUREDISPLAYMANAGER_H__

//#include "Globals.h"
#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/defs.h>
#include <wx/notebook.h>
//#include <wx/listbook.h>
#include "CaptureDisplayGrid.h"

typedef struct {
    uint32_t _id;
    CCaptureDisplayGrid* _pn;
} CapGuiInfo;

typedef std::map<int, CapGuiInfo> captureGuiComponents ;

//! Capture Display Manager Class which maintains all the open capture tabs.
class CCaptureDisplayManager : public wxNotebook
{
public:
    CCaptureDisplayManager(wxWindow *parent);
    ~CCaptureDisplayManager();
    bool AddLiveCapture();
    bool AddOfflineCapture(std::vector<std::string>& files);

private:
    uint32_t GetNextCaptureGridId();
    captureGuiComponents m_captures;

    CCaptureDisplayGrid* AddNewGrid(int size = 1000000);
    CCaptureDisplayGrid* AddEmptyCaptureGrid();

};

#endif // _WT_CAPTUREDISPLAYMANAGER_H__
