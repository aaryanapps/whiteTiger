/*
 * CaptureType.cpp
 *
 *  Created on: Aug 8, 2008
 *      Author: saumil
 */

#include "StdAfx.h"
#include "CaptureType.h"
#include "WtObject.h"

using namespace wt::core;
using namespace wt::framework;

uint32_t CCaptureType::m_classId = 0x00000232 ;

//DEFINE_STATIC_LOGGER("core.CaptureType", devLogger)

CCaptureType::CCaptureType()
{

}

CCaptureType::~CCaptureType()
{

}

/*Returns the packet at requested index*/
CWtObject* CCaptureType::GetPacketAt(uint32_t index)
{
	CWtObject* wo = NULL;
	return wo;
}

/*Get range of packets*/
void CCaptureType::GetPackets(uint32_t startIdx,
							  uint32_t endIdx,
							  WtoVec& wtv)
{
	return;
}

/*Returns the last packet*/
CWtObject* CCaptureType::GetLastPacket()
{
	return NULL;
}

/*Returns the first packet object*/
CWtObject* CCaptureType::GetFirstPacket()
{
	return NULL;
}

void CCaptureType::Init()
{

}

