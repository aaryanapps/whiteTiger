/*s
 * CaptureLibraryAdapter.h
 *
 *  Created on: Jul 26, 2008
 *      Author: saumil
 */

#ifndef _WT_CAPTURELIBRARYADAPTER_H_
#define _WT_CAPTURELIBRARYADAPTER_H_

#include "pcap.h"
#include "Globals.h"
#include "FastDelegate.h"
#include "CaptureLibraryDefs.h"

#include "Poco/Runnable.h"

namespace wt {
namespace core {
namespace capturelibrary {


class CCaptureLibraryAdapter: public Poco::Runnable {
public:
	CCaptureLibraryAdapter(std::string& adpName);
	~CCaptureLibraryAdapter();

    /* prototype of the packet handler in pcap library*/
    static void OnNewPacket(u_char *param,
    						const struct pcap_pkthdr *header,
    						const u_char *pkt_data);

    /*Main Entry point in the Runnable. */
	void 	run();

	/*Initialize the Interface (pcap_open_live)*/
    bool 	InitInterface();

    /*Allow Others to register for receive notification
     * When there is new packet captured */
    bool 	RegisterNewPacketNotification(uint32_t regId,
										  NewPktDelegateInfo* pktDelInfo);

    bool	UnRegisterNewPacketNotification(uint32_t regId);

    /*Return true if packets are captured*/
    bool 	IsCaptureRunning();

    /*Start capture on the interface*/
    void 	StartCapture();

private:

	std::string _strAdapter; 		/* Name of Adapter*/
	pcap_t*		_pPcapDesc; 		/*Pcap descriptor*/

};

}
}
}

#endif /* CAPTURELIBRARYADAPTER_H_ */
