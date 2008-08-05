#ifndef _WT_CAPTURELIBRARYINTERFACE_H__
#define _WT_CAPTURELIBRARYINTERFACE_H__

#include "BllFrameworkExport.h"

#include "DataTypes.h"
#include "Poco/Delegate.h"
#include "WtObjectDefs.h"

namespace wt {
namespace framework {
namespace capturelibrary {

class CNetworkInterfaceAdapter;

typedef std::map<std::string , CNetworkInterfaceAdapter*> activeAdapters;
typedef std::vector<std::string> adapterVec;


class FRAMEWORK_EXPORT CCaptureLibraryInterface {
public:
	static 	CCaptureLibraryInterface& Instance();

	void 	GetAdaptersList(adapterVec& adVec) ;

	bool 	StartCapture(std::string& adpName,
			Poco::Delegate<CWtObject, WtoHandle>&);

	bool 	IsAdapterCapturing(std::string& adpName);

	bool	RegisterNewPacketNotification(std::string& adpName,
			Poco::Delegate<CWtObject, WtoHandle>&);

private:
	CCaptureLibraryInterface();
	~CCaptureLibraryInterface();

	activeAdapters 			_mActAdapters;

};

}
}
}


#endif /*CAPTURELIBRARYINTERFACE_H_*/
