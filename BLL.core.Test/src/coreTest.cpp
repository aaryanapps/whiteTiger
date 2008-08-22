#include "StdAfx.h"

#include <iostream>
#include "Project.h"
#include "WtDataStore.h"
#include "CoreConsts.h"
#include "CaptureType.h"
#include "LiveCapture.h"

using namespace wt::framework;
using namespace wt::core;

int main(int argc, const char* argv[])
{

	CProject& prj = CProject::Instance();
	CWtDataStore& ds = CWtDataStore::Instance();

	WtoHandle wtHnd0 = ds.AddObject(CLiveCapture_Class_Id, &prj);
	WtoHandle wtHnd1 = ds.AddObject(CLiveCapture_Class_Id, &prj);
	WtoHandle wtHnd2 = ds.AddObject(CLiveCapture_Class_Id, &prj);
	WtoHandle wtHnd3 = ds.AddObject(CLiveCapture_Class_Id, &prj);
	WtoHandle wtHnd4 = ds.AddObject(CLiveCapture_Class_Id, &prj);

	std::cout << "Live Capture 1 Created: " << wtHnd0 << std::endl;
	std::cout << "Live Capture 2 Created: " << wtHnd1 << std::endl;
	std::cout << "Live Capture 3 Created: " << wtHnd2 << std::endl;
	std::cout << "Live Capture 4 Created: " << wtHnd3 << std::endl;
	std::cout << "Live Capture 5 Created: " << wtHnd4 << std::endl;

	std::cout << "5 Live Capture Created!! " << std::endl;


	WtoVec wtv;
	prj.GetObjects(wtv,CLiveCapture_Class_Id);
	std::cout << "LiveCapture Objects under Project: " << wtv.size() << std::endl;

	WtoVec::const_iterator wit;

	for (wit = wtv.begin(); wit != wtv.end(); ++wit)
	{
		//Handle to base WtObject.
		CWtObject* wto = ds.GetObjectFromHnd((*wit)->GetWtoHandle());
		std::cout << "LiveCapture Object under Project: " << (*wit)->GetWtoHandle() << std::endl;
		std::cout << "Live Capture Parent: " << wto->GetParent()->GetWtoHandle() << std::endl;

	}

	//Handle to base WtObject.
	CWtObject* wto = ds.GetObjectFromHnd(wtHnd0);

	//Handle to CaptureType capture.
	CCaptureType* _ptrCaptype = dynamic_cast<CCaptureType*> (ds.GetObjectFromHnd(wtHnd0));
	std::cout << "Base CaptureType ClassId: " << _ptrCaptype->GetClassId() << std::endl;


	//Handle to live capture.
	CLiveCapture* lvcap = dynamic_cast<CLiveCapture*> (ds.GetObjectFromHnd(wtHnd0));
	std::cout << "Live Capture ClassId: " << lvcap->GetClassId() << std::endl;

	std::cout << "Capture IsInstanceOf (Negative, should be false): " << wto->IsInstanceOf(CCapture_Class_Id) << std::endl;
	std::cout << "Base CaptureType IsInstanceOf: " << wto->IsInstanceOf(CCaptureType_Class_Id) << std::endl;
	std::cout << "Live Capture IsInstanceOf: " << wto->IsInstanceOf(CLiveCapture_Class_Id) << std::endl;


	std::cout << "Core.Test compiled and run successfully!!" << std::endl;

	return 0;

}
