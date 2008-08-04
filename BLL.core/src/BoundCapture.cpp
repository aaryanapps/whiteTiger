#include "StdAfx.h"

#include "BoundCapture.h"
//#include "NetworkInterfaceAdapterManager.h"
#include "Packet.h"
#include "PacketDb.h"
#include "FastDelegate.h"
#include <iostream>
#include "WtLogger.h"
#include "CoreConsts.h"

//using namespace wt::framework::networkintf;
using namespace wt::core;


CBoundCapture::CBoundCapture() :
	m_name("Default Capture"), m_typeId(CBoundCapture_Class_Id)
{
}

CBoundCapture::CBoundCapture(uint32_t id, uint32_t capHnd, std::string& name) :
    m_name(name), m_typeId(CBoundCapture_Class_Id)
{

}


CBoundCapture::~CBoundCapture()
{

}

void CBoundCapture::run()
{
	//CNetworkInterfaceAdapterManager& ph = CNetworkInterfaceAdapterManager::Instance();

    //Register delegate for new packet.

	/* TODO: Refactor Comment
	Poco::Delegate<CWtObject, WtoHandle> dl((CWtObject*))this, &CBoundCapture::OnPacket);
    ph.RegisterNewPacketNotification(GetWtoHandle(), dl);
	*/
}

void CBoundCapture::OnPacket(const void* pSender, WtoHandle& data)
{
	static uint32_t _pktIndex = 0;

	CBoundCapture *self = (CBoundCapture *) (pSender);
	++_pktIndex ;
	self->AddPacketToMap(data);
	std::cout << "Received New Packet, PacketHandle " << data << std::endl;



}

