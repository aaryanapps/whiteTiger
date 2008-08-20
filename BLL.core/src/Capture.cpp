#include "StdAfx.h"

#include "Capture.h"
#include "WtLogger.h"
#include "CoreConsts.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"

using Poco::Timestamp;
using namespace wt::core;
using namespace wt::framework;

uint32_t CCapture::m_classId = REGISTER_CREATOR(CCapture_Class_Id, CCapture::Create);

DEFINE_STATIC_LOGGER("core.Capture", devLogger)

CCapture::CCapture()
{
	AddAsDerivedClassId(CCapture_Class_Id);
	Init();
}

CCapture::~CCapture()
{
}

CCapture::CCapture(std::string& name) :
					m_name(name)
{
	AddAsDerivedClassId(CCapture_Class_Id);
	Init();
}

CWtObject* CCapture::Create()
{
	return new CCapture();
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

