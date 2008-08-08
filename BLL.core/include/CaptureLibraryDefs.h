/*
 * CaptureLibraryDefs.h
 *
 *  Created on: Aug 6, 2008
 *      Author: saumil
 */

#ifndef _WT_CAPTURELIBRARYDEFS_H_
#define _WT_CAPTURELIBRARYDEFS_H_

#include "WtObjectDefs.h"
#include "FastDelegate.h"

namespace Poco {
	class Thread;
}

namespace wt {
namespace core {
namespace capturelibrary {
	class CCaptureLibraryAdapter;


struct PktTimeStamp {
	uint32_t _sec;
	uint32_t _usec;
};

typedef struct {

	PktTimeStamp _ts;
	uint32_t 	_capLen;
	uint32_t 	_len;
	std::vector<uint8_t> _pktData;

	void clear() {
		_ts._sec = 0;
		_ts._usec = 0;
		_capLen = 0;
		_len = 0;
		_pktData.clear();
	}
} CapturedPkt;


typedef std::vector<std::string> adapterVec;
typedef fastdelegate::FastDelegate2<CapturedPkt*, void*> NewPktDelegate;

//typedef fastdelegate::FastDelegate2<WtoHandle, void*> FileParsingCompleteDel;

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

}
}
}

#endif /* _WT_CAPTURELIBRARYDEFS_H_ */
