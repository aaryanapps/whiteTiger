/*
 * CaptureLibraryAdapter.cpp
 *
 *  Created on: Jul 26, 2008
 *      Author: saumil
 */

#include "StdAfx.h"

#include "CaptureLibraryInterface.h"
#include "WtLogger.h"
#include "pcap.h"

using namespace wt::core::capturelibrary;

DEFINE_STATIC_LOGGER("framework.capturelibrary.CaptureLibraryAdapter", devLogger)

CCaptureLibraryAdapter::CCaptureLibraryAdapter(std::string &adpName):
												_strAdapter(adpName),
												_pPcapDesc(NULL)
{
	//Query Pcap and check the adapter name.



}

CCaptureLibraryAdapter::~CCaptureLibraryAdapter()
{
	//Close pcap_desc if open
}


/* prototype of the packet handler */
void CCaptureLibraryAdapter::OnNewPacket(u_char *param,
						const struct pcap_pkthdr *header,
						const u_char *pkt_data)
{
	/*Received a new packet. Give it to those subscribed for
	 * notification
	 * */


}

bool CCaptureLibraryAdapter::InitInterface()
{
    char Errbuf[PCAP_ERRBUF_SIZE];

    _pPcapDesc = pcap_open_live (_strAdapter.c_str(), 65535, 0, 0, Errbuf);

    if (_pPcapDesc == NULL)
    {
    	std::stringstream ss;
    	ss 	<< "Could not initialize Adapter: "
    		<< this->_strAdapter ;

    	LOG_ERROR( devLogger() , ss.str() );
    	return false;
    }

    return true;
}

int32_t CCaptureLibraryAdapter::Capture()
{
	if(_pPcapDesc == NULL)
	{
		return -1;
	}
	std::stringstream ss;
	ss 	<< "Starting Capture on Adapter: "
		<< this->_strAdapter ;
	LOG_DEBUG( devLogger() , ss.str() );

	uint8_t *uData = (uint8_t *) (this);
	int32_t ret = pcap_loop(_pPcapDesc,-1, &CCaptureLibraryAdapter::OnNewPacket,
							 uData);
	return ret;
}


bool CCaptureLibraryAdapter::RegisterNewPacketNotification(NewPktDelegate dl)
{
	/*Add the Delegate in the List*/
	return false;
}
