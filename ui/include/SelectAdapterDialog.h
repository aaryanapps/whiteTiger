#ifndef _WT_SELECTADAPTERDIALOG_H__
#define _WT_SELECTADAPTERDIALOG_H__

#define DIALOG_ID 50050
#define DIALOG_STRING _T("Select the adapter to start Capture")
#define DIALOG_STYLE wxLC_REPORT | wxLC_SINGLE_SEL | wxSUNKEN_BORDER
#define DIALOG_SELECTSOURCE_AVAILABLE_SOURCES _T("Available Sources:")
#define DIALOG_BUTTON_OK _T("Start")
#define DIALOG_BUTTON_CANCEL _T("Cancel")
#define ID_LISTCTRL 50051

class CSelectAdapterDialog: public wxDialog
{

public:
    /// Constructors
    CSelectAdapterDialog();
    CSelectAdapterDialog( wxWindow* parent, wxWindowID id = DIALOG_ID, const wxString& caption = DIALOG_STRING, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = DIALOG_ID, const wxString& caption = DIALOG_STRING, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

    /// Destructor
    ~CSelectAdapterDialog();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

    /// Should we show tooltips?
    //static bool ShowToolTips();

	std::string GetSelectedAdapter();
	
	bool IsAdapterSelected(long& idx);
    
private:
    wxListCtrl *adptrList;
    DECLARE_EVENT_TABLE()

};

#endif // _WT_SELECTADAPTERDIALOG_H__
