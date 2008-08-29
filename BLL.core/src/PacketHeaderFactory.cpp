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

uint32_t CPacketHeaderFactory::RegisterHeader(uint32_t hdrType,
											  uint32_t nextHdrType,
											  uint32_t hdrClassId)
{

	if (!IsHdrTypeRegistered(hdrType))
	{
		HdrType2NxtHdrMap* hMap = GetHeaderMap();
		HdrType2IdMap nxtHdrMap;
		nxtHdrMap.insert(std::make_pair(nextHdrType, hdrClassId));
		hMap->insert(std::make_pair(hdrType, nxtHdrMap));
		return hdrType;
	}
	else
	{
		if (!IsNextHdrTypeRegistered(hdrType, nextHdrType))
		{
			HdrType2NxtHdrMap* hMap = GetHeaderMap();
			HdrType2NxtHdrMap::const_iterator hit = hMap->find(hdrType);
			if (hit != hMap->end())
			{
				HdrType2IdMap nxtHdrMap = hit->second ;
				nxtHdrMap.insert(std::make_pair(nextHdrType, hdrClassId));
				return hdrType;
			}
			else
			{
				//Should not reach here.
				return WT_UNKWN;
			}
		}
		else
		{
			//Should not reach here as it is already registered.
			return WT_UNKWN;
		}
	}
}

HdrType2NxtHdrMap* CPacketHeaderFactory::GetHeaderMap()
{
	static HdrType2NxtHdrMap _mHdrMap;
	return &_mHdrMap;
}

uint32_t CPacketHeaderFactory::GetClassIdForHdrType(uint32_t hdrType, uint32_t nextHdrType)
{
	HdrType2NxtHdrMap* hMap = GetHeaderMap();
	HdrType2NxtHdrMap::const_iterator hit = hMap->find(hdrType);

	if (hit == hMap->end())
	{
		return WT_UNKWN;
	}
	else
	{
		HdrType2IdMap::const_iterator nhit = hit->second.find(nextHdrType);

		if (nhit != hit->second.end())
		{
			return nhit->second;
		}
		else
		{
			return WT_UNKWN;
		}
	}
}


bool CPacketHeaderFactory::IsHdrTypeRegistered(uint32_t hdrType)
{
	HdrType2NxtHdrMap* hMap = GetHeaderMap();
	HdrType2NxtHdrMap::const_iterator hit = hMap->find(hdrType);

	if (hit == hMap->end())
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool CPacketHeaderFactory::IsNextHdrTypeRegistered(uint32_t hdrType, uint32_t nextHdrType)
{
	HdrType2NxtHdrMap* hMap = GetHeaderMap();
	HdrType2NxtHdrMap::const_iterator hit = hMap->find(hdrType);

	if (hit == hMap->end())
	{
		return false;
	}
	else
	{
		HdrType2IdMap::const_iterator nhit = hit->second.find(nextHdrType);

		if (nhit != hit->second.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
