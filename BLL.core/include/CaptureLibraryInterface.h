/*
 * CaptureLibraryInterface.h
 *
 *  Created on: Jul 26, 2008
 *      Author: saumil
 */

#ifndef _WT_CAPTURELIBRARYINTERFACE_H_
#define _WT_CAPTURELIBRARYINTERFACE_H_

#include "pcap.h"
#include "Globals.h"
#include "FastDelegate.h"

namespace wt {
namespace framework {
namespace capturelibrary {

typedef fastdelegate::FastDelegate2<uint32_t, void*> NewPktDelegate;

class CCaptureLibraryInterface {
public:
	CCaptureLibraryInterface(std::string& adpName);
	~CCaptureLibraryInterface();

    /* prototype of the packet handler */
    static void OnNewPacket(u_char *param,
    						const struct pcap_pkthdr *header,
    						const u_char *pkt_data);


    bool 	InitInterface();

    bool 	RegisterNewPacketNotification();
    
    int32_t Capture();

private:

	std::string _strAdapter;
	pcap_t*		_pPcapDesc;

};

}
}
}

#endif /* CAPTURELIBRARYINTERFACE_H_ */
