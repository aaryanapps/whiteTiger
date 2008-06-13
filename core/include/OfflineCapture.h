#ifndef _WT_OFFLINEFILECAPTURE_H__
#define _WT_OFFLINEFILECAPTURE_H__

#include "Capture.h"
#include "Globals.h"
#include "PcapDefs.h"

class CPacket;
class COfflineCapture : public CCapture
{
public:
	COfflineCapture();
	COfflineCapture(std::string& name);
    ~COfflineCapture();

    virtual void run();

    void Init();

    void OnPacket(const void* pSender, PcapHandle& data);

	void SetPcapHandle(PcapHandle pHnd) {m_pcapHnd = pHnd;}
	PcapHandle GetPcapHandle() {return m_pcapHnd;}

	uint32_t GetTypeId() {return m_typeId; }
	uint32_t GetDataLinkType() { return m_dataLink; }
	
    /* prototype of the packet handler */
    static void OnNewPacket(u_char *param, 
    						   const struct pcap_pkthdr *header, 
    						   const u_char *pkt_data);
	
private:
    std::string m_name;
    uint32_t 	m_typeId;
    
    newPktCallBack m_pktCb;
    std::string m_fileLoc;
    PcapHandle m_pcapHnd;
    uint32_t m_dataLink;

    void NotifyNewPacket(WtoHandle pHnd);
    
};

#endif // _WT_OFFLINEFILECAPTURE_H__
