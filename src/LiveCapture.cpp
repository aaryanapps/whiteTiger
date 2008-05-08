
#include "LiveCapture.h"
#include "PcapHandler.h"
#include "pcap.h"
#include "Packet.h"
#include "PcapUtils.h"
#include "PacketDb.h"
#include "Globals.h"
#include "WtLogger.h"

DEFINE_STATIC_LOGGER("bll.LiveCapture", devLogger);

CLiveCapture::CLiveCapture() :
							  m_typeId(CLiveCapture_Class_Id)
{
}

CLiveCapture::CLiveCapture(std::string& name) :
	CCapture(name), m_typeId(CLiveCapture_Class_Id), m_pcapHnd(0)
{

}


CLiveCapture::~CLiveCapture()
{

}

void CLiveCapture::run()
{
	Init();
    
    CPcapHandler& ph = CPcapHandler::Instance();

    pcap_t *cDesc = ph.GetPcapDesc(m_pcapHnd);
    uint8_t *uData = (uint8_t *) (this);

    pcap_loop(cDesc,-1, &CLiveCapture::OnNewPacket, uData);


}

void CLiveCapture::Init()
{
	m_dataLink = CPcapUtils::GetDataLinkType(m_pcapHnd);
}


/* Callback function invoked by libpcap for every incoming packet */
void CLiveCapture::OnNewPacket(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{	
	CLiveCapture *self = (CLiveCapture *) (param);

    CPacketDb& pdb = CPacketDb::Instance();
    WtoHandle pktHnd = pdb.AddNewPacket(self->GetWtoHandle(),
    									self->GetDataLinkType(),
										header, pkt_data);


    CPacket* pkt = pdb.GetPacket(pktHnd);
    if (pkt)
    {
    	std::stringstream ss;
    	ss << pkt->GetTimeStamp() 
    			  << ", Length: " <<
					pkt->GetPacketLength();
    	
    	LOG_ERROR( devLogger() , ss.str() );
		
    }
    else
    {
    	/* Could not create the Packet
    	 * Various Reasons: no memory, unsupported datalink, etc
    	 */
    }
    
    self->AddPacketToMap(pktHnd);
    self->NotifyNewPacket(pktHnd);

}

void CLiveCapture::NotifyNewPacket(WtoHandle pHnd)
{
    NewNetworkPacket.notifyAsync(this, pHnd);
}
