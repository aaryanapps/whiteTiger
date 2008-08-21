#include "StdAfx.h"

#include <iostream>
#include "Project.h"
#include "WtDataStore.h"
#include "CoreConsts.h"

using namespace wt::framework;
using namespace wt::core;

int main(int argc, const char* argv[])
{

	CProject& prj = CProject::Instance();
	CWtDataStore& ds = CWtDataStore::Instance();

	WtoHandle wtHnd = ds.AddObject(CLiveCapture_Class_Id, &prj);

	std::cout << "Live Capture Created: " << wtHnd << std::endl;

	std::cout << "Core.Test compiled and run successfully!!" << std::endl;

	return 0;

}
