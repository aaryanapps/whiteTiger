
#include "BoundCapture.h"
#include "PcapHandler.h"
#include "Packet.h"
#include "PacketDb.h"
#include "FastDelegate.h"
#include <iostream>
#include "WtLogger.h"


CBoundCapture::CBoundCapture() :
	m_name("Default Capture"), m_typeId(CBoundCapture_Class_Id)
{
}

CBoundCapture::CBoundCapture(uint32_t id, uint32_t capHnd, std::string& name) :
    m_name(name), m_typeId(CBoundCapture_Class_Id)
{
    //m_pktCb = fastdelegate::MakeDelegate(this, &CBoundCapture::OnNewPacket);
}


CBoundCapture::~CBoundCapture()
{

}

void CBoundCapture::run()
{
    CPcapHandler& ph = CPcapHandler::Instance();

    //Register delegate for new packet.
    Poco::Delegate<CWtObject, WtoHandle> dl((CWtObject*))this, &CBoundCapture::OnPacket);
    ph.RegisterNewPacketNotification(GetWtoHandle(), dl);

}

void CBoundCapture::OnPacket(const void* pSender, WtoHandle& data)
{
	static uint32_t _pktIndex = 0;
	
	CBoundCapture *self = (CBoundCapture *) (pSender);
	++_pktIndex ;
	self->AddPacketToMap(data);
	std::cout << "Received New Packet, PacketHandle " << data << std::endl;

	

}

