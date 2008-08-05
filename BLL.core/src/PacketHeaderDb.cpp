#include "StdAfx.h"

#include "PacketHeaderDb.h"
#include "PacketHeader.h"
#include "PacketHeaderFactory.h"
#include "PacketDb.h"
#include "WtObjectDb.h"
#include "RelationManager.h"

using namespace wt::core;
using namespace wt::framework;

CPacketHeaderDb::CPacketHeaderDb()
{

}

CPacketHeaderDb::~CPacketHeaderDb()
{

}

CPacketHeaderDb& CPacketHeaderDb::Instance()
{
	static CPacketHeaderDb _pd;
	return _pd;
}


WtoHandle CPacketHeaderDb::AddNewHeader(WtoHandle parentPkt,
										uint32_t hdrType,
										const uint32_t hdrOffset,
										const uint8_t* pktData)
{
	CPacketHeaderFactory pf;
	CPacketHeader *newHdr = pf.Create(hdrType);

	if (!newHdr)
	{
		/*TODO: Log Error. May be out of memeory ?*/
		return PACKETHDRHND_NULL;
	}

	WtoHandle wHnd = CWtObjectDb::Instance().AddObject((CWtObject *)newHdr);
	if (wHnd == WTOBJECT_HND_NULL)
	{
		if (newHdr)
			delete newHdr;
		return PACKETHDRHND_NULL;
	}

	newHdr->SetWtoHandle(wHnd);

	//TODO: Add validation around Init
	newHdr->Init(wHnd, hdrOffset, pktData);
	m_hdrDb.insert(std::make_pair(wHnd, newHdr));

	wt::framework::CRelationManager *rm = wt::framework::CRelationManager::Instance();
	rm->AddRelation(parentPkt, wHnd, RelationType(ParentChild()));

	return wHnd;
}

CPacketHeader* CPacketHeaderDb::GetHeader(WtoHandle pHnd)
{
	PacketHdrDb::iterator pit = m_hdrDb.find(pHnd);

	if (pit == m_hdrDb.end())
	{
		return NULL;
	}

	return pit->second;
}

///////// Private helpers


