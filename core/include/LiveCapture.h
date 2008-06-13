#ifndef _WT_LIVECAPTURE_H__
#define _WT_LIVECAPTURE_H__

#include "TraceOptions.h"
#include "Poco/Runnable.h"
#include "Globals.h"
#include "PcapDefs.h"
#include "Capture.h"
#include "PacketDb.h"

class CPacket;
class CLiveCapture : public CCapture
{
public:
    CLiveCapture();
    CLiveCapture(std::string& name);
    ~CLiveCapture();

	void SetPcapHandle(PcapHandle pHnd) {m_pcapHnd = pHnd;}
	PcapHandle GetPcapHandle() {return m_pcapHnd;}

	virtual void run();
	
	virtual uint32_t GetTypeId() {return m_typeId; }
	
    /* prototype of the packet handler */
    static void OnNewPacket(u_char *param, 
    						   const struct pcap_pkthdr *header, 
    						   const u_char *pkt_data);

	virtual uint32_t GetDataLinkType(){return m_dataLink;}
	
	
protected:
    virtual void Init();
	
private:
    uint32_t 	m_typeId;
	uint32_t m_dataLink;
    PcapHandle m_pcapHnd;
    
    void NotifyNewPacket(WtoHandle pHnd);
    
};

#endif // _WT_LIVECAPTURE_H__
