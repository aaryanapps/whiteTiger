/*
 */

#include "MainApp.h"
#include "wx/wx.h" 
#include "MainFrame.h"

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
    CMainFrame *frame = new CMainFrame( _T("White Tiger"), wxPoint(50,50), wxSize(650,500), 0);
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
} 
