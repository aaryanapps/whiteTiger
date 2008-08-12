#include "StdAfx.h"

#include "Capture.h"
#include "PacketDb.h"
#include "WtLogger.h"
#include "CoreConsts.h"

using Poco::Timestamp;
using namespace wt::core;
using namespace wt::framework;

uint32_t CCapture::m_classId = 0x00000200 ;

DEFINE_STATIC_LOGGER("core.Capture", devLogger)

CCapture::CCapture()
{
	Init();
}

CCapture::~CCapture()
{
}

CCapture::CCapture(std::string& name) :
					m_name(name)
{
	Init();
}

void CCapture::Init()
{
	//Set the Start of this capture
	m_startTime.update();
}

void CCapture::AddPacketToMap(WtoHandle pHnd)
{
	static uint32_t _pktIndex = 0;
	++_pktIndex ;
	m_pkts.insert(std::make_pair(_pktIndex,pHnd));

	std::stringstream ss ;
	ss << "Packet Hnd:" << pHnd ;
	ss << " Packet No: " << _pktIndex ;

	LOG_DEBUG( devLogger(), ss.str()) ;

}

void CCapture::GetInheritedTypes(WtoTypeIdsVec& typeIdVec)
{
	typeIdVec.push_back(CCapture::m_classId);
	return;
}
