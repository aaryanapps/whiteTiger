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

	/*Return true is adapter is Capturing Packets*/
	bool 		IsAdapterCapturing(std::string& adpName);

	/*Register for notification when new packet is captured
	 * Returns a registrationId. This id is used in future to
	 * unregister the notification
	 * */
	uint32_t	RegisterNewPacketNotification(std::string& adpName,
				NewPktDelegateInfo* pktDelInfo);



private:
	CCaptureLibraryInterface();
	~CCaptureLibraryInterface();

	bool AdapterExists(std::string& adpName);

	bool CreateCaptureLibraryAdapter(std::string& adpName);

	CCaptureLibraryAdapter*	GetCaptureLibraryAdp(std::string& adpName);

	Poco::Thread* CreateThreadForAdp(std::string& adpName);

	Poco::Thread* GetThreadForAdp(std::string& adpName);

	bool StartCaptureInThread(std::string& adpName);

	ActiveAdapters 			_mActAdapters;

};

}
}
}


#endif /*CAPTURELIBRARYINTERFACE_H_*/
