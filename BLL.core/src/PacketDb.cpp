#include "StdAfx.h"

#include "PacketDb.h"
#include "Packet.h"
#include "PcapDefs.h"
#include "PacketFactory.h"
#include "WtObjectDb.h"
#include "RelationManager.h"

CPacketDb::CPacketDb()
{
	
}

CPacketDb::~CPacketDb()
{
	
}

CPacketDb& CPacketDb::Instance()
{
	static CPacketDb _pd;
	return _pd;
}

WtoHandle CPacketDb::AddNewPacket(WtoHandle parentCap,
								  uint32_t DataLink,
								  const pcapPktHdr *pkt, 
								  const uint8_t* pktData)
{
	CPacketFactory pf;
	CPacket *newPkt = pf.Create(DataLink);

	if (!newPkt)
	{
		/*TODO: Log Error. May be out of memeory ?, Unsupported LinkType*/
		return PACKETHND_NULL;
	}	

	WtoHandle wHnd = CWtObjectDb::Instance().AddObject((CWtObject *)newPkt);
	if (wHnd == WTOBJECT_HND_NULL)
	{
		if (newPkt)
		{
			delete newPkt;
		}
		return PACKETHND_NULL;
	}

	newPkt->SetWtoHandle(wHnd);
	wt::framework::CRelationManager *rm = wt::framework::CRelationManager::Instance();
	rm->AddRelation(parentCap, wHnd, RelationType(ParentChild()));
	
	newPkt->Init(wHnd, pkt, pktData);
	m_pktDb.insert(std::make_pair(wHnd, newPkt));
	
	return wHnd;
}

CPacket* CPacketDb::GetPacket(PcapHandle pHnd)
{
	PacketDb::iterator pit = m_pktDb.find(pHnd);
	
	if (pit == m_pktDb.end())
	{
		return NULL;
	}
	
	return pit->second;
}

///////// Private helpers


