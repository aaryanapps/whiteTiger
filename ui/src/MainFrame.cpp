
#include "wx/wx.h"
#include "wx/notebook.h"
#include "wx/defs.h"
#include "wx/panel.h"
#include "wx/splitter.h"
//#include "wxGlobal.h"

#include "MainFrame.h"
#include "MenuDefs.h"

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
    EVT_MENU(ID_FILE_QUIT, CMainFrame::OnFileQuit)
    EVT_MENU(ID_FILE_NEW, CMainFrame::OnFileNew)
    EVT_MENU(ID_FILE_OPEN, CMainFrame::OnFileOpen)
    EVT_MENU(ID_FILE_SAVEAS, CMainFrame::OnFileSaveAs)
    EVT_MENU(ID_HELP_ABOUT, CMainFrame::OnHelpMenu)

    EVT_MENU(ID_CAPTURE_START, CMainFrame::OnCaptureStartCapture)
    EVT_MENU(ID_CAPTURE_STOP, CMainFrame::OnCaptureStopCapture)
    
END_EVENT_TABLE()

CMainFrame::CMainFrame(const wxString& title,
                  const wxPoint& pos, const wxSize& size, long style)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{

    CreateMainMenuFileMenu();
    CreateMainMenuEditMenu();
    CreateMainMenuCaptureMenu();
    CreateMainMenuViewMenu();
    CreateMainMenuAnalyzeMenu();
    CreateMainMenuStatsMenu();
    CreateMainMenuHelpMenu();

    // now append the freshly created menu to the menu bar...
    m_menuBar = new wxMenuBar();
    m_menuBar->Append(m_fileMenu, MENU_FILE);
    m_menuBar->Append(m_editMenu, MENU_EDIT);
    m_menuBar->Append(m_viewMenu, MENU_VIEW);
    m_menuBar->Append(m_captureMenu, MENU_CAPTURE);
    m_menuBar->Append(m_analyzeMenu, MENU_ANALYZE);
    m_menuBar->Append(m_statsMenu, MENU_STATISTICS);
    m_menuBar->Append(m_helpMenu, MENU_HELP);

    SetMenuBar( m_menuBar );

    CreateStatusBar(3);
    SetStatusText( STATUS_BAR_DEFAULT_STRING );
    
	// Creates two Split windows
	wxSplitterWindow *topSplitter = new wxSplitterWindow(this, -1, 
														wxDefaultPosition,wxDefaultSize, wxSP_NOBORDER);
		
	wxSplitterWindow *bottomSplitter = new wxSplitterWindow(topSplitter, -1,
														wxDefaultPosition, wxDefaultSize, wxSP_NOBORDER);
    
	wxPanel *dummy1 = new wxPanel(bottomSplitter,wxID_ANY);
	wxPanel *dummy2 = new wxPanel(bottomSplitter,wxID_ANY);
	
	// Prevent from UnSplit
	topSplitter->SetMinimumPaneSize(5);
	bottomSplitter->SetMinimumPaneSize(5);
	
    m_cdm = new CCaptureDisplayManager(topSplitter);

	// Split the Frame
	topSplitter->SplitHorizontally(m_cdm, bottomSplitter);
	bottomSplitter->SplitVertically(dummy1, dummy2);
	
    topSplitter->Show(true);
    bottomSplitter->Show(true);

}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnFileQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}


void CMainFrame::OnFileNew(wxCommandEvent &event)
{
    CreateNewTrace();
}

void CMainFrame::OnFileOpen(wxCommandEvent &event)
{
    // Several files can be opened at same time
    wxFileDialog dialog(this, DLG_OPEN_FILES, _T(""), _T(""), DLG_CAPTUREOPEN_TYPES, 
        wxFD_OPEN | wxFD_MULTIPLE | wxFD_FILE_MUST_EXIST);  

    if (dialog.ShowModal() == wxID_OK)
    {
		wxArrayString selFiles;
		dialog.GetPaths(selFiles);
		if (selFiles.IsEmpty())
		{
			//Log, nothing seleted by user.
			return;
		}
		std::vector<std::string> files;
		uint16_t selCnt = selFiles.GetCount();
		for (int i = 0; i < selCnt; ++i)
		{
			std::string s(selFiles.Item(i).mb_str());
			files.push_back(s);
			//wxString fname = selFiles.Item(i);
			//m_cdm->AddNewOfflineCapture();
		}
		
		m_cdm->AddOfflineCapture(files);
		
    }

}

void CMainFrame::OnFileSave(wxCommandEvent &event)
{
}

void CMainFrame::OnFileSaveAs(wxCommandEvent &event)
{
    // Several files can be opened at same time
    wxFileDialog dialog(this, DLG_SAVE_FILE, _T(""), _T(""), DLG_CAPTURESAVE_TYPES,
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (dialog.ShowModal() == wxID_OK)
    {

    }

}

void CMainFrame::OnFileExport(wxCommandEvent &event)
{
}

void CMainFrame::OnFilePrint(wxCommandEvent &event)
{
}

void CMainFrame::OnEditFindPacket(wxCommandEvent &event)
{
}

void CMainFrame::OnEditFindNextPacket(wxCommandEvent &event)
{
}

void CMainFrame::OnEditFindPreviousPacket(wxCommandEvent &event)
{
}

void CMainFrame::OnEditCutPacket(wxCommandEvent &event)
{
}

void CMainFrame::OnEditCopyPacket(wxCommandEvent &event)
{
}

void CMainFrame::OnEditPastePacket(wxCommandEvent &event)
{
}

void CMainFrame::OnEditGotoPacket(wxCommandEvent &event)
{
}

void CMainFrame::OnEditAppPreferences(wxCommandEvent &event)
{
}

void CMainFrame::OnCaptureStartCapture(wxCommandEvent &event)
{
	m_cdm->AddLiveCapture();
}

void CMainFrame::OnCaptureStopCapture(wxCommandEvent &event)
{
	
}

void CMainFrame::OnCapturePauseCapture(wxCommandEvent &event)
{
}

void CMainFrame::OnCaptureResumeCapture(wxCommandEvent &event)
{
}

void CMainFrame::OnCaptureCaptureOptions(wxCommandEvent &event)
{
}

void CMainFrame::OnCaptureCaptureFilters(wxCommandEvent &event)
{
}

void CMainFrame::OnHelpMenu(wxCommandEvent& event)
{
    switch (event.GetId())
    {
        case ID_HELP_CONTENTS:
        {

        }; break;
        case ID_HELP_MANUAL:
        {

        }; break;
        case ID_HELP_EXAMPLES:
        {

        }; break;
        case ID_HELP_ABOUT:
        {
            wxMessageBox(MENU_HELP_ABOUT,MENU_HELP_ABOUT_STRING,
                wxOK | wxICON_INFORMATION, this);

        }; break;
        default:
            break;
    }

}

void CMainFrame::OnCloseWindow(wxCloseEvent &event)
{
    Close(TRUE);
}


//Private Methods
void CMainFrame::CreateMainMenuFileMenu()
{
    m_fileMenu = new wxMenu(_T(""), wxMENU_TEAROFF);
    m_fileMenu->Append(ID_FILE_NEW, MENU_FILE_NEW, MENU_FILE_NEW_STRING);
    m_fileMenu->Append(ID_FILE_OPEN, MENU_FILE_OPEN, MENU_FILE_OPEN_STRING);
    m_fileMenu->AppendSeparator();
    m_fileMenu->Append(ID_FILE_SAVE, MENU_FILE_SAVE, MENU_FILE_SAVE_STRING);
    m_fileMenu->Append(ID_FILE_SAVEAS, MENU_FILE_SAVEAS, MENU_FILE_SAVEAS_STRING);
    m_fileMenu->AppendSeparator();
    m_fileMenu->Append(ID_FILE_QUIT, MENU_FILE_QUIT, MENU_FILE_QUIT_STRING);

}

void CMainFrame::CreateMainMenuEditMenu()
{
    m_editMenu = new wxMenu(_T(""), wxMENU_TEAROFF);
    m_editMenu->Append(ID_EDIT_FIND_PACKET, MENU_EDIT_FIND_PACKET, MENU_EDIT_FIND_PACKET_STRING);
    m_editMenu->AppendSeparator();
    m_editMenu->Append(ID_EDIT_COPY_PACKET, MENU_EDIT_COPY_PACKET, MENU_EDIT_COPY_PACKET_STRING);
    m_editMenu->Append(ID_EDIT_CUT_PACKET, MENU_EDIT_CUT, MENU_EDIT_CUT_STRING);
    m_editMenu->Append(ID_EDIT_PASTE_PACKET, MENU_EDIT_PASTE, MENU_EDIT_PASTE_STRING);

}

void CMainFrame::CreateMainMenuCaptureMenu()
{
    m_captureMenu = new wxMenu(_T(""), wxMENU_TEAROFF);
    m_captureMenu->Append(ID_CAPTURE_START, MENU_CAPTURE_START_CAPTURE, MENU_CAPTURE_START_CAPTURE_STRING);
    m_captureMenu->Append(ID_CAPTURE_STOP, MENU_CAPTURE_STOP_CAPTURE, MENU_CAPTURE_STOP_CAPTURE_STRING);

}

void CMainFrame::CreateMainMenuViewMenu()
{
    m_viewMenu = new wxMenu(_T(""), wxMENU_TEAROFF);
}

void CMainFrame::CreateMainMenuAnalyzeMenu()
{
    m_analyzeMenu = new wxMenu(_T(""), wxMENU_TEAROFF);
}

void CMainFrame::CreateMainMenuStatsMenu()
{
    m_statsMenu = new wxMenu(_T(""), wxMENU_TEAROFF);
}

void CMainFrame::CreateMainMenuHelpMenu()
{
    m_helpMenu = new wxMenu(_T(""), wxMENU_TEAROFF);
    m_helpMenu->Append(ID_HELP_ABOUT, MENU_HELP_ABOUT, MENU_HELP_ABOUT_STRING);
}

bool CMainFrame::CreateNewTrace()
{
	std::vector<std::string> emptyList;
	return m_cdm->AddOfflineCapture(emptyList);
}
/*
void CMainFrame::OnRightClick(wxMouseEvent & event)
{
    if (!m_rMenu)
    {
        m_rMenu = new wxMenu ;

        m_rMenu->Append(ID_LEFT_EXIT, _T("E&xit"));
    }
    PopupMenu(m_rMenu, event.GetPosition());
}
*/



//! Handler called when the user drops a file on the main frame
bool CDropFileHandler::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& FileNames)
{
    return true;
}

