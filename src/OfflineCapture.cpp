
#include "OfflineCapture.h"
#include "PcapHandler.h"
#include "pcap.h"
#include "Packet.h"
#include "PcapUtils.h"
#include "Globals.h"
#include "CommonPacketUtils.h"
#include "WtLogger.h"

DEFINE_STATIC_LOGGER("bll.OfflineCapture", devLogger);

COfflineCapture::COfflineCapture() :
									m_typeId(COfflineCapture_Class_Id)
{
}

COfflineCapture::COfflineCapture(std::string& name) :
	CCapture(name), m_typeId(COfflineCapture_Class_Id), m_pcapHnd(0)
{

}


COfflineCapture::~COfflineCapture()
{

}

void COfflineCapture::run()
{
	Init();
    
    CPcapHandler& ph = CPcapHandler::Instance();

    pcap_t *cDesc = ph.GetPcapDesc(m_pcapHnd);
    uint8_t *uData = (uint8_t *) (this);
    int len = 0;
    do {
		len = pcap_dispatch(cDesc, 1, &COfflineCapture::OnNewPacket, uData);
	} while (len > 0);

}

void COfflineCapture::Init()
{
	m_dataLink = CPcapUtils::GetDataLinkType(m_pcapHnd);
}


/* Callback function invoked by libpcap for every incoming packet */
void COfflineCapture::OnNewPacket(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{	
	COfflineCapture *self = (COfflineCapture *) (param);
		
	CPacketDb& pdb = CPacketDb::Instance();
    WtoHandle pktHnd = pdb.AddNewPacket(self->GetWtoHandle(),
    									self->GetDataLinkType(),
										header, pkt_data);


    CPacket* pkt = pdb.GetPacket(pktHnd);
    if (!pkt)
    {
    	std::stringstream ss ;
    	ss << "Could not create Packet for file " << self->m_fileLoc ;
    	LOG_ERROR( devLogger(), ss.str()) ;
    }
    
    self->AddPacketToMap(pktHnd);
    self->NotifyNewPacket(pktHnd);

}

void COfflineCapture::NotifyNewPacket(WtoHandle pHnd)
{
    NewNetworkPacket.notifyAsync(this, pHnd);
}


