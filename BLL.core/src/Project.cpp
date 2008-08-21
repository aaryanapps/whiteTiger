/*
 * Project.cpp
 *
 *  Created on: Aug 14, 2008
 *      Author: smehta
 */

#include "StdAfx.h"
#include "Project.h"
#include "WtDataStore.h"
#include "CoreConsts.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"

using namespace wt::core;
using namespace wt::framework;

uint32_t CProject::m_classId = REGISTER_CREATOR(CProject_Class_Id, CProject::Create);


CProject::CProject()
{
	AddAsDerivedClassId(CProject_Class_Id);
}

CProject::~CProject()
{

}


CProject& CProject::Instance()
{
	static CProject* prj = NULL;

	if (NULL == prj)
	{
		CWtDataStore &ds = CWtDataStore::Instance();
		WtoHandle prjHnd = ds.CreateObject(CProject::m_classId);

		prj = dynamic_cast<CProject*> (ds.GetObjectFromHnd(prjHnd));
		return *prj;

	}

	return *prj;
}

CWtObject* CProject::Create()
{
	return new CProject();
}
