#ifndef _WT_NETWORKINTERFACEADAPTER_H__
#define _WT_NETWORKINTERFACEADAPTER_H__

#include "BllFrameworkExport.h"

#include "Poco/Runnable.h"
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"
//#include "Poco/Thread.h"

#include "WtObjectDefs.h"
#include "WtObject.h"
#include "CaptureLibraryInterface.h"
#include "FastDelegate.h"

class Poco::Thread;

namespace wt {
namespace core {
namespace networkintf {

typedef enum CaptureStateEnum {
	CAPTURE_IDLE = 1,
	CAPTURE_BEING_STARTED,
	CAPTURE_RUNNING,
	CAPTURE_PAUSED,
	CAPTURE_BEING_STOPPED,
	CAPTURE_STOPPED
} CaptureState;

class FRAMEWORK_EXPORT CNetworkInterfaceAdapter : public Poco::Runnable {

public:

	CNetworkInterfaceAdapter(std::string& adpName);
	~CNetworkInterfaceAdapter();

    bool RegisterOnNewPacket(Poco::Delegate<wt::framework::CWtObject, WtoHandle>& dl);

    /* prototype of the packet handler */
    static void OnNewPacket(u_char *param,
    						const struct pcap_pkthdr *header,
    						const u_char *pkt_data);

    virtual void run();

	bool InitAdapter();

	bool StartCapture();

	void OnNewPacket(uint32_t pktHnd, void* data);

	WtoHandle GetLastPacket();

	WtoHandle GetFirstPacket();

private:
	CNetworkInterfaceAdapter(){};

	void NotifyNewPacket(WtoHandle pHnd);

	bool CreateThread();

	std::string  	_strAdapName;
	Poco::Thread*	_pThread;
	Poco::BasicEvent<WtoHandle> NewPacket;
	CaptureState	_captureStatus;

	wt::core::capturelibrary::CCaptureLibraryInterface*	_capLibInt;
	wt::core::capturelibrary::NewPktDelegate	_dNewPkt;

};

}
}
}

#endif //_WT_NETWORKINTERFACEADAPTER_H__
