/////////////////////////////////////////////////////////////////////////////
// Name:        control.h
// Purpose:
// Author:      Robert Roebling
// Id:          $Id: control.h,v 1.34 2006/08/30 05:55:50 PC Exp $
// Copyright:   (c) 1998 Robert Roebling, Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_GTK_CONTROL_H_
#define _WX_GTK_CONTROL_H_

typedef struct _GtkLabel GtkLabel;
typedef struct _GtkFrame GtkFrame;

//-----------------------------------------------------------------------------
// wxControl
//-----------------------------------------------------------------------------

// C-linkage function pointer types for GetDefaultAttributesFromGTKWidget
extern "C" {
    typedef GtkWidget* (*wxGtkWidgetNew_t)(void);
    typedef GtkWidget* (*wxGtkWidgetNewFromStr_t)(const gchar*);
    typedef GtkWidget* (*wxGtkWidgetNewFromAdj_t)(GtkAdjustment*);
}

class WXDLLIMPEXP_CORE wxControl : public wxControlBase
{
public:
    wxControl();
    wxControl(wxWindow *parent, wxWindowID id,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize, long style = 0,
             const wxValidator& validator = wxDefaultValidator,
             const wxString& name = wxControlNameStr)
    {
        Create(parent, id, pos, size, style, validator, name);
    }

    bool Create(wxWindow *parent, wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxControlNameStr);

    virtual void SetLabel( const wxString &label );
    virtual wxString GetLabel() const;

    virtual wxVisualAttributes GetDefaultAttributes() const;

    virtual void OnInternalIdle();

protected:
    virtual wxSize DoGetBestSize() const;
    void PostCreation(const wxSize& size);

    // sets the label to the given string and also sets it for the given widget
    void GTKSetLabelForLabel(GtkLabel *w, const wxString& label);

    // GtkFrame helpers
    GtkWidget* GTKCreateFrame(const wxString& label);
    void GTKSetLabelForFrame(GtkFrame *w, const wxString& label);
    void GTKFrameApplyWidgetStyle(GtkFrame* w, GtkRcStyle* rc);
    void GTKFrameSetMnemonicWidget(GtkFrame* w, GtkWidget* widget);

    // remove mnemonics ("&"s) from the label
    static wxString GTKRemoveMnemonics(const wxString& label);

    // converts wx label to GTK+ label, i.e. basically replace "&"s with "_"s
    //
    // for GTK+ 1 (which doesn't support mnemonics) this is the same as
    // GTKRemoveMnemonics()
    static wxString GTKConvertMnemonics(const wxString &label);

    // These are used by GetDefaultAttributes
    static wxVisualAttributes
        GetDefaultAttributesFromGTKWidget(GtkWidget* widget,
                                          bool useBase = false,
                                          int state = -1);
    static wxVisualAttributes
        GetDefaultAttributesFromGTKWidget(wxGtkWidgetNew_t,
                                          bool useBase = false,
                                          int state = -1);
    static wxVisualAttributes
        GetDefaultAttributesFromGTKWidget(wxGtkWidgetNewFromStr_t,
                                          bool useBase = false,
                                          int state = -1);

    static wxVisualAttributes
        GetDefaultAttributesFromGTKWidget(wxGtkWidgetNewFromAdj_t,
                                          bool useBase = false,
                                          int state = -1);

    // Widgets that use the style->base colour for the BG colour should
    // override this and return true.
    virtual bool UseGTKStyleBase() const { return false; }

    // this field contains the label in wx format, i.e. with "&" mnemonics
    wxString m_label;

private:
    DECLARE_DYNAMIC_CLASS(wxControl)
};

#endif // _WX_GTK_CONTROL_H_
