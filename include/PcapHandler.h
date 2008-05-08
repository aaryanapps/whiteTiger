#ifndef _WT_PCAPHANDLER_H__
#define _WT_PCAPHANDLER_H__

#include "Globals.h"
#include "Poco/Thread.h"
#include "PcapDefs.h"
#include "Poco/Delegate.h"
#include "PacketDb.h"
#include "WtObjectDb.h"

using namespace Poco;

class CLiveCapture;
class CBoundCapture;

#define INVALID_LV_CAP_ID 0

typedef struct LiveCaptureDetails {
    Thread   *_th;
    pcap_t   *_capDesc;
    PcapHandle  _pcapHnd;
    WtoHandle _lvCap;
    std::string _devName;

} LiveCaptureDetails;

typedef std::map<std::string, WtoHandle> dev2IdMap;
typedef std::map<WtoHandle, LiveCaptureDetails> CaptureDetailsMap;

class CPcapHandler {

public:

    static CPcapHandler& Instance();

    WtoHandle StartLiveCapture(std::string& devName);

    bool StopLiveCapture(uint32_t devId);
    
    WtoHandle ParseOfflineFile(std::string& fname);

    pcap_t* GetCaptureDesc(uint32_t devId);
	
	pcap_t* GetPcapDesc(PcapHandle pHnd);
    
    void CleanUp(uint32_t devId);

    bool RegisterNewPacketNotification(WtoHandle capId, Delegate<CBoundCapture, PacketHandle>&);

private:
    CPcapHandler();
    ~CPcapHandler();
    
    bool IsCaptureRunning(std::string& devName);

    uint32_t GetCaptureIdFromString(std::string& devName);
    std::string GetCaptureStringFromId(uint32_t devId);

    uint32_t GetNextCaptureId(std::string& devName);

    uint32_t CreateLiveCapture(std::string& dev);
    bool CreateLiveCaptureEnv(WtoHandle devId);
    bool PrepareLiveCaptureInterface(WtoHandle dev);
    bool StartLiveCapture(uint32_t dev);
    
    void RemoveLiveCapture(std::string& dev);
    void RemoveLiveCapture(uint32_t devId);

	uint32_t GetNextPcapHnd();

    dev2IdMap m_actCaptures;
    CaptureDetailsMap m_capDetails;
    PcapHnd2DescMap m_pcapHnds;

};

#endif //_WT_PCAPHANDLER_H__
