/*
 * PacketHeaderFactory.cpp
 *
 *  Created on: Aug 13, 2008
 *      Author: smehta
 */

#include "StdAfx.h"
#include "PacketHeaderFactory.h"
#include "WtLogger.h"

using namespace wt::core;

CPacketHeaderFactory::CPacketHeaderFactory()
{

}

CPacketHeaderFactory::~CPacketHeaderFactory()
{

}

CPacketHeaderFactory& CPacketHeaderFactory::Instance()
{
    static CPacketHeaderFactory _phf;
	return _phf;
}

uint32_t CPacketHeaderFactory::RegisterHeader(uint32_t hdrType, uint32_t hdrClassId)
{
	HdrType2IdMap* hMap = GetHeaderMap();
	HdrType2IdMap::const_iterator hit = hMap->find(hdrType);

	if (hit == hMap->end())
	{
		hMap->insert(std::make_pair(hdrType, hdrClassId));
		return hdrType;
	}
	else
	{
		return WT_UNKWN;
	}

}

HdrType2IdMap* CPacketHeaderFactory::GetHeaderMap()
{
	static HdrType2IdMap _mHdrMap;
	return &_mHdrMap;
}

uint32_t CPacketHeaderFactory::GetClassIdForHdrType(uint32_t hdrType)
{
	HdrType2IdMap* hMap = GetHeaderMap();
	HdrType2IdMap::const_iterator hit = hMap->find(hdrType);

	if (hit == hMap->end())
	{
		return WT_UNKWN;
	}
	else
	{
		return hit->second;
	}

}
