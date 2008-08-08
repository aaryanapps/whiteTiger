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

using namespace wt::core;

//DEFINE_STATIC_LOGGER("core.CaptureFile", devLogger)

uint32_t CCaptureFile::m_classId = 0x00000264 ;


CCaptureFile::CCaptureFile(std::string& fname) :
							m_fileName(fname)
{

}

CCaptureFile::CCaptureFile()
{

}

CCaptureFile::~CCaptureFile()
{

}



void CCaptureFile::ParseFile()
{

}

