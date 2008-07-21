#include "StdAfx.h"

#include "TaskManager.h"

using namespace wt::framework;

CTaskManager::CTaskManager()
{
	
}

CTaskManager::~CTaskManager()
{
	
}

CTaskManager& CTaskManager::Instance()
{
	static CTaskManager tm;
	return tm;
}

