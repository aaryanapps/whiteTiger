#ifndef _WT_MAINFRAME_H__
#define _WT_MAINFRAME_H__

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/dnd.h>                             // For wxFileDropTarget
#include <wx/defs.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <vector>
#include <map>

#include "CaptureDisplayManager.h"

class CDropFileHandler;

//! Main application frame
class CMainFrame : public wxFrame
{
public:
        //! Standard constructor
        CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size, long style);
        ~CMainFrame();

        // event handlers (these functions should _not_ be virtual)
        void OnFileNew(wxCommandEvent &event);
        void OnFileOpen(wxCommandEvent &event);
        void OnFileSave(wxCommandEvent &event);
        void OnFileSaveAs(wxCommandEvent &event);
        void OnFileExport(wxCommandEvent &event);
        void OnFilePrint(wxCommandEvent &event);
        void OnFileQuit(wxCommandEvent &event);                 //!< Menu handler

        void OnEditFindPacket(wxCommandEvent &event);           //!< Menu handler
        void OnEditFindNextPacket(wxCommandEvent &event);
        void OnEditFindPreviousPacket(wxCommandEvent &event);

        void OnEditCutPacket(wxCommandEvent &event);
        void OnEditCopyPacket(wxCommandEvent &event);
        void OnEditPastePacket(wxCommandEvent &event);
        void OnEditGotoPacket(wxCommandEvent &event);
        void OnEditAppPreferences(wxCommandEvent &event);

        void OnCaptureStartCapture(wxCommandEvent &event);      //!< Menu handler
        void OnCaptureStopCapture(wxCommandEvent &event);      //!< Menu handler
        void OnCapturePauseCapture(wxCommandEvent &event);      //!< Menu handler
        void OnCaptureResumeCapture(wxCommandEvent &event);      //!< Menu handler
        void OnCaptureCaptureOptions(wxCommandEvent &event);      //!< Menu handler
        void OnCaptureCaptureFilters(wxCommandEvent &event);      //!< Menu handler

        void OnHelpMenu(wxCommandEvent &event);             //!< Menu handler
        void OnCloseWindow(wxCloseEvent &event);                //!< Called when the window is about to close

        void OnChildFrameClosing(wxEvent &Event);
        void OnChildFrameClosingAbort(wxEvent &Event);

        //wxWindowList m_FrameList;       //!< Keeps the list of the child frames currently opened

        //void OnRightClick(wxMouseEvent & event);

private:
        // any class wishing to process wxWindows events must use this macro
        DECLARE_EVENT_TABLE()
/*
        void CreateCaptureBasicMenuToolbar();
        void CreateAnalyzeBasicMenuToolbar();
        void CreateReportBasicMenuToolbar();
        void CreateHelpBasicMenuToolbar();
*/

        void CreateMainMenuFileMenu();
        void CreateMainMenuEditMenu();
        void CreateMainMenuCaptureMenu();
        void CreateMainMenuViewMenu();
        void CreateMainMenuAnalyzeMenu();
        void CreateMainMenuStatsMenu();
        void CreateMainMenuHelpMenu();

        bool CreateNewTrace();
        //int  GetNextNewTraceId();


        wxMenuBar *m_menuBar;
        wxMenu *m_fileMenu;
        wxMenu *m_editMenu;
        wxMenu *m_viewMenu;
        wxMenu *m_captureMenu;
        wxMenu *m_analyzeMenu;
        wxMenu *m_statsMenu;
        wxMenu *m_helpMenu;

        //wxMenu *m_rMenu;
        
        CCaptureDisplayManager *m_cdm;

        bool m_closingAborted;          //!< 'true' when we decided not to close the application after we pressed 'exit'
        bool m_closingInProgress;       //!< 'true' when we're polling child frames and waiting them to close
};


class CDropFileHandler : public wxFileDropTarget
{
public:
        CDropFileHandler(wxFrame *mainFrame) { m_mainFrame= mainFrame; }
        bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& FileNames);

private:
        wxFrame *m_mainFrame;
};

#endif // _WT_MAINFRAME__
