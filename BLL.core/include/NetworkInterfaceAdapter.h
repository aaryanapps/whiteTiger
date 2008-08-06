#ifndef _WT_NETWORKINTERFACEADAPTER_H__
#define _WT_NETWORKINTERFACEADAPTER_H__

#include "BllFrameworkExport.h"

#include "WtObjectDefs.h"
#include "WtObject.h"
#include "CaptureLibraryInterface.h"
#include "FastDelegate.h"

//Poco
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"



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

class FRAMEWORK_EXPORT CNetworkInterfaceAdapter : public wt::framework::CWtObject {

public:

	CNetworkInterfaceAdapter(std::string& adpName);
	~CNetworkInterfaceAdapter();

    bool RegisterOnNewPacket(Poco::Delegate<wt::framework::CWtObject, WtoHandle>& dl);

    /* prototype of the packet handler */
    static void OnNewPacket(u_char *param,
    						const struct pcap_pkthdr *header,
    						const u_char *pkt_data);

	bool StartCapture();

	void OnNewPacket(WtoHandle pktHnd, void* data);

	WtoHandle GetLastPacket();

	WtoHandle GetFirstPacket();

	void 		SetCaptureStatus(CaptureState status) {_captureStatus = status;}
	CaptureState GetCaptureStatus() { return _captureStatus;}

private:
	/*Default ctor*/
	CNetworkInterfaceAdapter(){};

	void NotifyNewPacket(WtoHandle pHnd);

	/*Initialize the Adaptor for Capture*/
	bool InitAdapter();


	bool CreateThread();

	std::string  	_strAdapName;			/*Adapter Name*/
	Poco::BasicEvent<WtoHandle> NewPacket;
	CaptureState	_captureStatus;			/*Capture Status*/

	wt::core::capturelibrary::NewPktDelegate	_dNewPkt;

};

}
}
}

#endif //_WT_NETWORKINTERFACEADAPTER_H__
