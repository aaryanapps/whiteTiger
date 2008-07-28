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

class Poco::Thread;
//class wt::framework::capturelibrary::CCaptureLibraryInterface;

namespace wt {
namespace framework {
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

    bool RegisterOnNewPacket(Poco::Delegate<CWtObject, WtoHandle>& dl);

    /* prototype of the packet handler */
    static void OnNewPacket(u_char *param,
    						const struct pcap_pkthdr *header,
    						const u_char *pkt_data);

    virtual void run();

	bool InitAdapter();

	bool StartCapture();


private:
	CNetworkInterfaceAdapter(){};

	void NotifyNewPacket(WtoHandle pHnd);

	bool CreateThread();

	std::string  	_strAdapName;
	Poco::Thread*	_pThread;
	Poco::BasicEvent<WtoHandle> NewNetworkPacket;
	CaptureState	_captureStatus;
	wt::framework::capturelibrary::CCaptureLibraryInterface*	_capLibInt;
};

}
}
}

#endif //_WT_NETWORKINTERFACEADAPTER_H__
