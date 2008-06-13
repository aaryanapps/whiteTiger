#ifndef _WT_MENUDEFS_H__
#define _WT_MENUDEFS_H__

// IDs for the controls and the menu commands
enum
{
    // Main menu items
    //File
    ID_FILE_NEW = 1,
    ID_FILE_OPEN,
    ID_FILE_OPEN_RECENT,
    ID_FILE_CLOSE,
    ID_FILE_SAVE,
    ID_FILE_SAVEAS,
    ID_FILE_EXPORT,
    ID_FILE_PRINT,
    ID_FILE_QUIT,

    //EDIT
    ID_EDIT_FIND_PACKET,
    ID_EDIT_FIND_NEXT,
    ID_EDIT_FIND_PREVIOUS,
    ID_EDIT_CUT_PACKET,
    ID_EDIT_COPY_PACKET,
    ID_EDIT_PASTE_PACKET,
    ID_EDIT_COPY_PACKET_SUMMARY,
    ID_EDIT_GOTO_PACKET,
    ID_EDIT_APP_PREFERENCES,

    //View
    ID_VIEW_INTERFACES,
    ID_VIEW_ACTIVE_CAPTURES,
    ID_VIEW_TOOLBARS,

    //CAPTURE
    ID_CAPTURE_START,
    ID_CAPTURE_STOP,
    ID_CAPTURE_PAUSE,
    ID_CAPTURE_RESUME,
    ID_CAPTURE_FILTERS,
    ID_CAPTURE_RMT_CAPTURE_START,
    ID_CAPTURE_RMT_CAPTURE_STOP,
    ID_CAPTURE_RMT_CAPTURE_LIST,
    ID_CAPTURE_RMT_CAPTURE_CLOSE,

    //ANALYZE
    ID_ANALYZE_DISPLAY_FILTERS,
    ID_ANALYZE_TCP_STREAM,

    //TOOLS
    ID_TOOL_NETWORK_TOOLS,
    
    //STATISTICS


    //HELP
    ID_HELP_CONTENTS,
    ID_HELP_MANUAL,
    ID_HELP_EXAMPLES,
    ID_HELP_ABOUT,
};


// Menu Definitions
#define STATUS_BAR_DEFAULT_STRING                   _T("Ready")
#define STATUS_BAR_CLOSING                          _T("Application is closing, please wait...")

// Main menu bar
#define MENU_FILE                                   _T("&File")
#define MENU_EDIT                                   _T("&Edit")
#define MENU_VIEW                                   _T("&View")
#define MENU_CAPTURE                                _T("&Capture")
#define MENU_STATISTICS                             _T("S&tatistics")
#define MENU_ANALYZE                                _T("&Analyze")
#define MENU_HELP                                   _T("&Help")

// Main Menu Items
#define MENU_FILE_NEW                               _T("Open new &Capture\tCtrl-N")
#define MENU_FILE_NEW_STRING                        _T("Create a new capture file")
#define MENU_FILE_OPEN                              _T("&Open existing Capture\tCtrl-O")
#define MENU_FILE_OPEN_STRING                       _T("Open an existing Capture Trace")
#define MENU_FILE_SAVE                              _T("&Save Capture\tCtrl-S")
#define MENU_FILE_SAVE_STRING                       _T("Save the active capture")
#define MENU_FILE_SAVEAS                            _T("&Save Capture As\tCtrl-S")
#define MENU_FILE_SAVEAS_STRING                     _T("Save the active capture As")
#define MENU_FILE_QUIT                              _T("E&xit\tAlt-X")
#define MENU_FILE_QUIT_STRING                       _T("Quit this program")


#define MENU_EDIT_FIND_PACKET                       _T("&Find\tCtrl-F")
#define MENU_EDIT_FIND_PACKET_STRING                _T("Search for packet")

#define MENU_EDIT_COPY_PACKET                       _T("&Copy Packets\tCtrl-C")
#define MENU_EDIT_COPY_PACKET_STRING                _T("Copies the packet")
#define MENU_EDIT_COPY_INDEX                        _T("&Copy Packets Summary\tCtrl-D")
#define MENU_EDIT_COPY_INDEX_STRING                 _T("Copies the content of the packet summary window")
#define MENU_EDIT_CUT                               _T("&Cut Packets\tCtrl-X")
#define MENU_EDIT_CUT_STRING                        _T("Cut the selected items")
#define MENU_EDIT_PASTE                             _T("&Paste Packets\tCtrl-V")
#define MENU_EDIT_PASTE_STRING                      _T("Paste the items")


#define MENU_CAPTURE_START_CAPTURE                  _T("Start &Capture\tAlt-C")
#define MENU_CAPTURE_START_CAPTURE_STRING           _T("Start a new Live capture session")
#define MENU_CAPTURE_STOP_CAPTURE                   _T("Stop Capture")
#define MENU_CAPTURE_STOP_CAPTURE_STRING            _T("Stop a Live capture session in Progress")
#define MENU_CAPTURE_OPEN_CAPTURE                   _T("&Open Capture\tAlt-O")
#define MENU_CAPTURE_OPEN_CAPTURE_STRING            _T("Open an existing capture file")
#define MENU_CAPTURE_EMPTY_CAPTURE                  _T("New &Empty capture\tAlt-E")
#define MENU_CAPTURE_EMPTY_CAPTURE_STRING           _T("Create a new empy capture file")
#define MENU_CAPTURE_RMTACTIVE                      _T("Remote Capture (Active Mode)")
#define MENU_CAPTURE_RMTACTIVE_STRING               _T("Manages a remote capture in Active Mode (the capture server opens a connection to us)"
#define MENU_CAPTURE_RMTACTIVE_ACCEPT               _T("&Accept active connection\tAlt-A")
#define MENU_CAPTURE_RMTACTIVE_ACCEPT_STRING        _T("Accept a new active connection from a remote server")
#define MENU_CAPTURE_RMTACTIVE_LIST                 _T("&List active connection\tAlt-L")
#define MENU_CAPTURE_RMTACTIVE_LIST_STRING          _T("List the currently active connections from remote servers")
#define MENU_CAPTURE_RMTACTIVE_CLOSE                _T("&Close active connection\tAlt-C")
#define MENU_CAPTURE_RMTACTIVE_CLOSE_STRING         _T("Close one active connection from remote servers")

#define MENU_TOOLS_NETWORK_TOOLS_PING				_T("Ping a remote Host")
#define MENU_TOOLS_NETWORK_TOOLS_PING_STRING		_T("Allows to ping a remote host ")

#define MENU_HELP_ABOUT                             _T("About WhiteTiger")
#define MENU_HELP_ABOUT_STRING                      _T("WhiteTiger allows to capture data on the network and perform analysis on the data")

#define DLG_OPEN_FILES                              _T("Open Capture trace(s)")
#define DLG_CAPTUREOPEN_TYPES                       _T("All files (*.*)|*.*")

#define DLG_SAVE_FILE                               _T("Save Capture trace")
#define DLG_CAPTURESAVE_TYPES                       _T("All files (*.*)|*.*")



#define ID_LEFT_EXIT 12345

#endif // _WT_MENUDEFS__
