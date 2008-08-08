#ifndef _WT_CAPTURELIBRARYINTERFACE_H__
#define _WT_CAPTURELIBRARYINTERFACE_H__

#include "BllFrameworkExport.h"

#include "DataTypes.h"
#include "WtObjectDefs.h"
#include "FastDelegate.h"

#include "CaptureLibraryDefs.h"

#include "Poco/Delegate.h"

namespace wt {
namespace core {
namespace capturelibrary {

class FRAMEWORK_EXPORT CCaptureLibraryInterface {
public:
	static 		CCaptureLibraryInterface& Instance();

	/*Get the List of Adapters*/
	void 		GetAdaptersList(adapterVec& adVec) ;

	/*Start Capture on the Adapter*/
	bool 		StartCapture(std::string& adpName);

	/*Stop Capture on the Adapter*/
	bool 		StopCapture(std::string& adpName, uint32_t regId = 0);

	/*Return true is adapter is Capturing Packets*/
	bool 		IsAdapterCapturing(std::string& adpName);

	/* Register for notification when new packet is captured
	 * Returns a registrationId. This id is used in future to
	 * unregister the notification
	 */
	uint32_t	RegisterNewPacketNotification(std::string& adpName,
				NewPktDelegateInfo& pktDelInfo);

	/* UnRegister for previously registered notification.
	 * If there is no registration found, it returns false
	 */
	bool		UnRegisterNewPacketNotification(std::string& adpName, uint32_t regId);

	/*Parse the given file Name*/
	WtoHandle	ParseFile(std::string& fname);

private:
	CCaptureLibraryInterface();
	~CCaptureLibraryInterface();

	bool 			IsAdapterOpen(std::string& adpName);

	bool 			OpenCaptureLibraryAdapter(std::string& adpName);

	CCaptureLibraryAdapter*	GetCaptureLibraryAdp(std::string& adpName);

	Poco::Thread* 	CreateThreadForAdp(std::string& adpName);

	Poco::Thread* 	GetThreadForAdp(std::string& adpName);

	bool 			StartCaptureInThread(std::string& adpName);

	ActiveAdapters 			_mActAdapters;

};

}
}
}


#endif /*CAPTURELIBRARYINTERFACE_H_*/
