bin_PROGRAMS = whitetiger

# set the include path found by configure
INCLUDES = -I$(top_srcdir)/include $(all_includes) -I$(HOME)/opt/include \
	-I/usr/include/wx-2.8 -I/usr/lib/wx/include/gtk2-unicode-release-2.8

# the library search path.
whitetiger_LDFLAGS = $(all_libraries) 
AM_CXXFLAGS = -pthread
whitetiger_LDADD = -lPocoFoundationd -lPocoNet -lPocoUtil -lPocoXML -lpcapnav \
	-lwx_baseu-2.8 -lwx_baseu_net-2.8 -lwx_baseu_xml-2.8 -lwx_gtk2u_adv-2.8 \
	-lwx_gtk2u_aui-2.8 -lwx_gtk2u_core-2.8 -lwx_gtk2u_html-2.8 -lwx_gtk2u_qa-2.8 \
	-lwx_gtk2u_xrc-2.8
whitetiger_SOURCES = Capture.cpp CentralCaptureManager.cpp LiveCapture.cpp \
	MainFrame.cpp PcapHandler.cpp PcapUtils.cpp PktHeader.cpp SelectAdapterDialog.cpp \
	TraceListPane.cpp TraceManager.cpp TraceOptions.cpp whitetiger.cpp
