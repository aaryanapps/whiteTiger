#ifndef _WT_CENTRALCAPTUREMANAGER_H__
#define _WT_CENTRALCAPTUREMANAGER_H__

#include "Globals.h"
#include "Poco/Thread.h"
#include "TraceOptions.h"

class CCapture;

typedef struct CaptureInfo {

    uint32_t _id;
    uint32_t _capHnd;
    Poco::Thread *_th;
} CaptureInfo;

typedef  std::map<uint32_t, CaptureInfo> Id2CapMap;

class CCentralCaptureManager
{
public:
    CCentralCaptureManager();
    ~CCentralCaptureManager();

    static CCentralCaptureManager& Instance();

    uint32_t StartCapture(const char* devName);
    
    uint32_t StartBoundCapture(uint32_t capHnd);
        
    bool StopCapture(uint32_t capId);
    
    bool SaveCapture(uint32_t capId);

    uint32_t OpenSavedCapture(const char* fName);
    
    uint32_t OpenEmptyCapture();
    
    CCapture *GetCapture(uint32_t capId);
    
private:

    uint32_t GetNextCaptureId();

    Id2CapMap m_Captures;

};

#endif // _WT_CENTRALCAPTUREMANAGER_H__
