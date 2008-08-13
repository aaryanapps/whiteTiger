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

using namespace wt::core;

//uint32_t CCaptureFile::m_classId = 0x00000264 ;
uint32_t CCaptureFile::m_classId = REGISTER_CREATOR(CArpHeader_Class_Id, CCaptureFile::Create);

//DEFINE_STATIC_LOGGER("core.CaptureFile", devLogger)

std::string CCaptureFile::m_defFile = "Untitled1" ;

CCaptureFile::CCaptureFile(std::string& fname) :
					m_fileName(fname)
{

}

CCaptureFile::CCaptureFile() :
				m_fileName(CCaptureFile::m_defFile)
{

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


void CCaptureFile::ParseFile()
{

}

