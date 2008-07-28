#ifndef _WT_NETWORKINTERFACEADAPTERMANAGER_H__
#define _WT_NETWORKINTERFACEADAPTERMANAGER_H__

#include "BllFrameworkExport.h"

#include "DataTypes.h"
#include "Poco/Delegate.h"
#include "WtObjectDefs.h"

namespace wt {
namespace framework {
namespace networkintf {

class CNetworkInterfaceAdapter;

typedef std::map<std::string , CNetworkInterfaceAdapter*> activeAdapters;
typedef std::vector<std::string> adapterVec;


class FRAMEWORK_EXPORT CNetworkInterfaceAdapterManager {
public:
	static 	CNetworkInterfaceAdapterManager& Instance();
	
	void 	GetAdaptersList(adapterVec& adVec) ;
	
	bool 	StartCapture(std::string& adpName, 
			Poco::Delegate<CWtObject, WtoHandle>&);
	
	bool 	IsAdapterCapturing(std::string& adpName);
	
	bool	RegisterNewPacketNotification(std::string& adpName, 
			Poco::Delegate<CWtObject, WtoHandle>&);
	
private:
	CNetworkInterfaceAdapterManager();
	~CNetworkInterfaceAdapterManager();

	activeAdapters 			_mActAdapters;
	
};

}
}
}


#endif /*NETWORKINTERFACEADAPTERMANAGER_H_*/
