#include "StdAfx.h"

#include "CommandManager.h"

using namespace wt::framework;

CCommandManager::CCommandManager()
{

}

CCommandManager::~CCommandManager()
{

}

CCommandManager& CCommandManager::Instance()
{
	static CCommandManager tm;
	return tm;
}

