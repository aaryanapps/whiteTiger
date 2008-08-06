/*
 * CaptureLibraryDefs.h
 *
 *  Created on: Aug 6, 2008
 *      Author: saumil
 */

#ifndef _WT_CAPTURELIBRARYDEFS_H_
#define _WT_CAPTURELIBRARYDEFS_H_

#include "WtObjectDefs.h"

namespace Poco {
	class Thread;
}

namespace wt {
namespace core {
namespace capturelibrary {
	class CCaptureLibraryAdapter;
}
}
}

typedef std::vector<std::string> adapterVec;
typedef fastdelegate::FastDelegate2<WtoHandle, void*> NewPktDelegate;

typedef struct {
	wt::core::capturelibrary::CCaptureLibraryAdapter* _capLibAdp;
	Poco::Thread* _pThread;
} AdapterInfo;

typedef struct {
	NewPktDelegate 	_newpktDel;
	void*			_data;
} NewPktDelegateInfo;

typedef std::vector<NewPktDelegateInfo> NewPktDelegateVec;

typedef std::map<std::string , AdapterInfo> ActiveAdapters;



#endif /* _WT_CAPTURELIBRARYDEFS_H_ */
