// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "SelectAdapterDialog.h"
#include "PcapUtils.h"
#include "PcapHandler.h"

#include "wx/string.h"
#include <iostream>
/*!
 * CDialogSelectSource event table definition
 */

BEGIN_EVENT_TABLE( CSelectAdapterDialog, wxDialog )

END_EVENT_TABLE()


/*!
 * CDialogSelectSource constructors
 */

CSelectAdapterDialog::CSelectAdapterDialog()
{
    Init();
}

CSelectAdapterDialog::CSelectAdapterDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

// Find size of buffer needed 
// allocate a conversion buffer -always presume 32-bit wide wchar_t's! 
// change UTF-8 towide-character unicode
// Assign to a wxString 
#define CONVERT(astring,ustring) uint32_t len = wxConvUTF8.MB2WC(NULL,astring,0); \
buf = (wchar_t *)malloc((len*4)+4);\
len = wxConvUTF8.MB2WC((wchar_t *)buf,astring,len+1); \
ustring = buf; \
free((void *)buf);  // deallocate the conversion buffer 

/*!
 * CDialogSelectSource creator
 */

bool CSelectAdapterDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    char Errbuf[PCAP_ERRBUF_SIZE];

    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();

    //wxListCtrl *adptrList = (wxListCtrl *) FindWindowById(ID_LISTCTRL, this) ;

    adptrList->InsertColumn(0, _T("Adapter Name"), wxLIST_FORMAT_LEFT);
    adptrList->InsertColumn(1, _T("Adapter Description"), wxLIST_FORMAT_LEFT);

    pcap_if_t* ifs;
    ifs = NULL;
    bool status = CPcapUtils::GetAdapterList(&ifs, Errbuf);
    if (!status)
    {
        //Error occured while getting adapter list.
        return false;
    }

    wxCSConv conv_ascii(_T("ISO-8859-1"));

    uint32_t i = 0;
    while (ifs)
    {

        wxString tmp;

        if (ifs->name)
        {
            wxString str(ifs->name, *wxConvCurrent);
            tmp = str;
        }
        else
        {
            tmp = wxEmptyString;
        }
        int32_t ires = adptrList->InsertItem(i, tmp);
	    if ( ires != -1 )
        {
            adptrList->SetItemData(ires, i);
        }
        else
        {
            return false;
        }

	    ires = adptrList->SetItem(i, 0, tmp);

        ++i;

        ifs= ifs->next;
    }

    adptrList->SetColumnWidth( 0, wxLIST_AUTOSIZE_USEHEADER );
    adptrList->SetColumnWidth( 1, wxLIST_AUTOSIZE_USEHEADER );

    return true;
}


/*!
 * CDialogSelectSource destructor
 */

CSelectAdapterDialog::~CSelectAdapterDialog()
{
////@begin CDialogSelectSource destruction

    delete adptrList;

////@end CDialogSelectSource destruction
}


/*!
 * Member initialisation
 */

void CSelectAdapterDialog::Init()
{
////@begin CDialogSelectSource member initialisation
////@end CDialogSelectSource member initialisation
}


/*!
 * Control creation for CDialogSelectSource
 */

void CSelectAdapterDialog::CreateControls()
{
////@begin CDialogSelectSource content construction
    CSelectAdapterDialog* thisDlg = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    thisDlg->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(thisDlg, wxID_ANY, DIALOG_SELECTSOURCE_AVAILABLE_SOURCES);
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxHORIZONTAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    //wxListCtrl* adptrList = new wxListCtrl;
    adptrList = new wxListCtrl;
    adptrList->Create( thisDlg, ID_LISTCTRL, wxDefaultPosition, wxSize(500, 150), wxLC_REPORT|wxLC_SINGLE_SEL|wxSUNKEN_BORDER );
    itemStaticBoxSizer3->Add(adptrList, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* okButton = new wxButton;
    okButton->Create( thisDlg, wxID_OK, DIALOG_BUTTON_OK, wxDefaultPosition, wxDefaultSize, 0 );
    okButton->SetDefault();
    itemBoxSizer5->Add(okButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* canButton = new wxButton;
    canButton->Create( thisDlg, wxID_CANCEL, DIALOG_BUTTON_CANCEL, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(canButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end CDialogSelectSource content construction
}

bool CSelectAdapterDialog::IsAdapterSelected(long& idx)
{
    idx = adptrList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if ( idx != -1 )
        return true;
	
	return false;
}

std::string CSelectAdapterDialog::GetSelectedAdapter()
{
	std::string s("");

    long item = -1;         // It keeps the currently selected adapter
    wxListItem info;        // It is needed to retrieve name/description of the selected adapter 
    wxString tmpstr;        // needed to print the currently selected adapter

    if (!IsAdapterSelected(item))
    {
    	return s;
    }
    
    // We need to initialize the wxListItem struct
    info.m_itemId= item;        // initialize to the elemente to retrieve
    info.m_mask= wxLIST_MASK_TEXT | wxLIST_MASK_DATA;   // list of fields that must be filled by the following GetItem()

    // Update the currently selected sources
    info.m_col= 0;
    if (!adptrList->GetItem(info))
    {
    	return s;
    }
	
    std::stringstream ss;
    ss << info.m_text.mb_str();

	return ss.str();
}

