#ifndef _WT_NETWORKINTERFACEADAPTER_H__
#define _WT_NETWORKINTERFACEADAPTER_H__

#include "pcap.h"
#include "Poco/Runnable.h"
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"
#include "Poco/Thread.h"
#include "WtObjectDefs.h"

namespace wt {
namespace framework {
namespace networkintf {

class CNetworkInterfaceAdapter : public Poco::Runnable {

public:
	
	CNetworkInterfaceAdapter(std::string&);
	~CNetworkInterfaceAdapter();

    bool RegisterOnNewPacket(Poco::Delegate<CWtObject, WtoHandle>&);

    /* prototype of the packet handler */
    static void OnNewPacket(u_char *param, 
    						const struct pcap_pkthdr *header, 
    						const u_char *pkt_data);
    
    virtual void run();
    
	bool InitAdapter();
    
private:
	CNetworkInterfaceAdapter(){};
	void NotifyNewPacket(WtoHandle pHnd);
	bool CreateThread();
	
	pcap_t*			_pPcapDesc;
	std::string  	_strAdapName;
	Poco::Thread*	_pThread;
	Poco::BasicEvent<WtoHandle> NewNetworkPacket;	

};

}
}
}

#endif //_WT_NETWORKINTERFACEADAPTER_H__
