#ifndef _WT_NETWORKINTERFACEADAPTER_H__
#define _WT_NETWORKINTERFACEADAPTER_H__

#include "BllCoreExport.h"

#include "WtObjectDefs.h"
#include "WtObject.h"
#include "CaptureLibraryDefs.h"

//Poco
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"

using namespace wt::framework;

class Poco::Thread;

namespace wt {
namespace core {

typedef enum CaptureStateEnum {
	CAPTURE_IDLE = 1,
	CAPTURE_BEING_STARTED,
	CAPTURE_RUNNING,
	CAPTURE_PAUSED,
	CAPTURE_BEING_STOPPED,
	CAPTURE_STOPPED
} CaptureState;

class CORE_EXPORT CNetworkInterfaceAdapter : public wt::framework::CWtObject {

public:

	CNetworkInterfaceAdapter(std::string& adpName);
	~CNetworkInterfaceAdapter();

    bool RegisterOnNewPacket(Poco::Delegate<wt::framework::CWtObject, WtoHandle>& dl);

	bool StartCapture();

	void OnNewPacket(wt::core::capturelibrary::CapturedPkt* pkt, void* data);

	WtoHandle GetLastPacket();

	WtoHandle GetFirstPacket();

	//Getters/Setters

	void 		SetCaptureStatus(CaptureState status) {_captureStatus = status;}

	CaptureState GetCaptureStatus() { return _captureStatus;}

private:
	/*Default ctor*/
	CNetworkInterfaceAdapter(){};

	void NotifyNewPacket(WtoHandle pHnd);


	std::string  	_strAdapName;			/*Adapter Name*/
	Poco::BasicEvent<WtoHandle> NewPacket;
	CaptureState	_captureStatus;			/*Capture Status*/

	wt::core::capturelibrary::NewPktDelegate	_dNewPkt;

};

}
}

#endif //_WT_NETWORKINTERFACEADAPTER_H__
