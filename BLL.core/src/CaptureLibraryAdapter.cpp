/*
 * CaptureLibraryAdapter.cpp
 *
 *  Created on: Jul 26, 2008
 *      Author: saumil
 */

#include "StdAfx.h"

#include "CaptureLibraryAdapter.h"
#include "CaptureLibraryInterface.h"
#include "CaptureLibraryDefs.h"

#include "WtLogger.h"

#include "pcap.h"

using namespace wt::core::capturelibrary;

DEFINE_STATIC_LOGGER("core.capturelibrary.CaptureLibraryAdapter", devLogger)

CCaptureLibraryAdapter::CCaptureLibraryAdapter(std::string &adpName):
												_strAdapter(adpName)
{


}

CCaptureLibraryAdapter::~CCaptureLibraryAdapter()
{
	// Close all pcap_desc if open, This can never happen as
	// the class is singleton.

}


/* prototype of the packet handler */
void CCaptureLibraryAdapter::OnNewPacket(u_char *param,
						const struct pcap_pkthdr *header,
						const u_char *pkt_data)
{
	/* Received a new packet.
	 * Generate the struct
	 * Give it to those subscribed for notification
	 */

	CCaptureLibraryAdapter *capAdp = reinterpret_cast<CCaptureLibraryAdapter*> (param);

	CapturedPkt cp;
	cp._ts._sec = header->ts.tv_sec;
	cp._ts._usec = header->ts.tv_usec;
	cp._capLen 	= header->caplen;
	cp._len		= header->len;
	cp._pktData.assign(pkt_data, pkt_data + header->caplen);

	capAdp->SendNotifications(cp);

}

void CCaptureLibraryAdapter::SendNotifications(CapturedPkt& pkt)
{
	LOG_DEBUG(devLogger(), "Sending New Pkt Notification")

	NewPktDelegateMap::const_iterator dit = _mNewPktDels.begin();

	while(dit != _mNewPktDels.end())
	{
		(dit->second._newpktDel)(&pkt,dit->second._data);
		++dit;
	}

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

bool CCaptureLibraryAdapter::IsCaptureRunning()
{
	return false;
}

void CCaptureLibraryAdapter::StartCapture()
{
	//Initialize Adapter if required.
    if (_pPcapDesc == NULL)
    {
    	InitInterface();
    }
	return;
}

void CCaptureLibraryAdapter::StopCapture()
{
	if (IsCaptureRunning())
	{
		pcap_breakloop(_pPcapDesc);
	}
}


void CCaptureLibraryAdapter::run()
{
	if(_pPcapDesc == NULL)
	{
		LOG_ERROR(devLogger(), "Null desc. Should not happen!")
		return;
	}

	std::stringstream ss;
	ss 	<< "In run: Starting Capture on Adapter: "
		<< this->_strAdapter ;

	LOG_DEBUG( devLogger() , ss.str() );

	u_char* Data = (u_char*)(this);

	int32_t ret = pcap_loop(_pPcapDesc,-1, &CCaptureLibraryAdapter::OnNewPacket,
							 Data);

	if ( -1 == ret)
	{
		LOG_ERROR(devLogger(), "Error occured after capture stopped!")
	}
}

bool CCaptureLibraryAdapter::RegisterNewPacketNotification(uint32_t regId,
												NewPktDelegateInfo& pktDelInfo)
{
	//Save the info in map. The regId is used to unregister.

	NewPktDelegateMap::const_iterator it = _mNewPktDels.find(regId);

	if (it == _mNewPktDels.end())
	{
		_mNewPktDels.insert(std::make_pair(regId, pktDelInfo));
		return true;
	}
	else
	{
		LOG_ERROR(devLogger(), "Registration Id already registered")
		return false;
	}

}

bool CCaptureLibraryAdapter::UnRegisterNewPacketNotification(uint32_t regId)
{
	//Delete the info from map. The regId is used to unregister.

	NewPktDelegateMap::const_iterator it = _mNewPktDels.find(regId);

	if (it != _mNewPktDels.end())
	{
		LOG_DEBUG(devLogger(), "Registration Id found, deleting it")
		_mNewPktDels.erase(regId);
		return true;
	}
	else
	{
		LOG_DEBUG(devLogger(), "Registration Id not found")
		return false;
	}

	return false;
}

uint32_t CCaptureLibraryAdapter::GetDataLinkType()
{
	return pcap_datalink(_pPcapDesc);
}
