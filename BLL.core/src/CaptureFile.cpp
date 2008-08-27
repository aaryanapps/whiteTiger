/*
 * CaptureFile.cpp
 *
 *  Created on: Aug 7, 2008
 *      Author: smehta
 */

#include "StdAfx.h"

#include "CaptureFile.h"
#include "Globals.h"
#include "WtLogger.h"
#include "CoreConsts.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"
#include "FastDelegate.h"
#include "CaptureLibraryInterface.h"
#include "CaptureLibraryDefs.h"
#include "PacketParser.h"

using namespace wt::core;
using namespace wt::core::capturelibrary;

DEFINE_STATIC_LOGGER("core.CaptureFile", devLogger)

uint32_t CCaptureFile::m_classId = REGISTER_CREATOR(CCaptureFile_Class_Id, CCaptureFile::Create);

std::string CCaptureFile::m_defFile = "Untitled1" ;

CCaptureFile::CCaptureFile(std::string& fname) :
					m_fileName(fname)
{
	AddAsDerivedClassId(CCaptureFile_Class_Id);
	m_dNewPkt = fastdelegate::MakeDelegate(this, &CCaptureFile::OnNewPacket);
}

CCaptureFile::CCaptureFile() :
				m_fileName(CCaptureFile::m_defFile)
{
	AddAsDerivedClassId(CCaptureFile_Class_Id);
	m_dNewPkt = fastdelegate::MakeDelegate(this, &CCaptureFile::OnNewPacket);
}

wt::framework::CWtObject* CCaptureFile::Create()
{
	return new CCaptureFile();
}


CCaptureFile::~CCaptureFile()
{

}

std::string& CCaptureFile::GetDefaultFileName()
{
	static uint32_t m_fileno = 1;
	std::stringstream ss;
	ss << "Untitled" << m_fileno;
	m_defFile = ss.str();
	m_fileno++;
	return m_defFile;
}

void CCaptureFile::Init()
{

}

void CCaptureFile::ParseFile()
{

	CCaptureLibraryInterface& cli = CCaptureLibraryInterface::Instance();

	wt::core::capturelibrary::NewPktDelegateInfo del;
	del._newpktDel = m_dNewPkt;
	del._data = NULL;

	bool ret = cli.ParsePcapFile(m_fileName, del);

	if ( !ret )
    {
    	LOG_ERROR( devLogger() , "Error occured when starting Capture on Adapter: " );
    }

}


void CCaptureFile::OnNewPacket(CapturedPkt* pkt, void* data)
{
	LOG_DEBUG(devLogger(), "Received new packet notification");

	//TODO: Addlogic to process new packet notification
	/* Call the Protocol dissector
	 * Parse the packet. Create header objects as required.
	 */

	CPacketParser &pp = CPacketParser::Instance();
	pp.ParsePacket(GetParent(), pkt, 1);


	return;
}
