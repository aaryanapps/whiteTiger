#include "StdAfx.h"

#include <iostream>
#include "Project.h"
#include "WtDataStore.h"
#include "CoreConsts.h"
#include "Capture.h"
#include "CaptureType.h"
#include "LiveCapture.h"
#include "CaptureFile.h"

#include "CaptureLibraryDefs.h"
#include "CaptureLibraryInterface.h"
#include "NetworkInterfaceAdapter.h"


using namespace wt::framework;
using namespace wt::core;
using namespace wt::core::capturelibrary;

void SystemTest()
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

	std::cout << "5 Live Captures Created!! " << std::endl;

	std::cout << "Capture 1 created: " << ds.AddObject(CCapture_Class_Id, &prj) << std::endl;
	std::cout << "Capture 2 created: " << ds.AddObject(CCapture_Class_Id, &prj) << std::endl;
	std::cout << "Capture 3 created: " << ds.AddObject(CCapture_Class_Id, &prj) << std::endl;

	std::cout << "3 Captures Created!! " << std::endl;

	WtoVec wtv;
	prj.GetObjects(wtv,CCaptureType_Class_Id);
	std::cout << "LiveCapture Objects under Project (using base class - CaptureType): " << wtv.size() << std::endl;

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

	return;
}

void LiveCaptureTest()
{

	CProject& prj = CProject::Instance();
	CWtDataStore& ds = CWtDataStore::Instance();

	//Create Capture Object under project
	WtoHandle capHnd = ds.AddObject(CCapture_Class_Id, &prj);
	CCapture* capPtr = dynamic_cast<CCapture*> (ds.GetObjectFromHnd(capHnd));

	//Create NetworkAdapter Object under project
	//TODO: currently, Network interface is created under capture.
	WtoHandle nwHnd = ds.AddObject(CNetworkInterfaceAdapter_Class_Id, capPtr);
	CNetworkInterfaceAdapter* nwPtr = dynamic_cast<CNetworkInterfaceAdapter*> (ds.GetObjectFromHnd(nwHnd));

	//Add relationship between capture and networkadapter.

	//Create Live Capture under Capture Object
	WtoHandle lvcHnd = ds.AddObject(CLiveCapture_Class_Id, &prj);
	CLiveCapture* lvcPtr = dynamic_cast<CLiveCapture*> (ds.GetObjectFromHnd(lvcHnd));

	//Get List of Available Adapters
	CCaptureLibraryInterface &cif = CCaptureLibraryInterface::Instance();

	adapterVec aVec;

	cif.GetAdaptersList(aVec);
	if (aVec.empty())
	{
		std::cout << "No Adapters found for capturing" << std::endl;
	}
	else
	{
		adapterVec::const_iterator ait = aVec.begin();

		for(;ait != aVec.end(); ++ait)
		{
			std::cout << "Adapter : " << *ait << std::endl;
		}
	}
	//Open desired Adapter for capture.

	std::string s("eth0");
	cif.OpenCaptureLibraryAdapter(s);

	/*Set the Adapter Name*/
	nwPtr->SetAdapterName(s);

	//Start Capture using CaptureLibraryInterface
	nwPtr->StartCapture();

	std::cout << "Capture Status: " << nwPtr->GetCaptureStatus() << std::endl;

	uint32_t testi;
	std::cin >> testi;


}


int main(int argc, const char* argv[])
{

//	SystemTest();

	//LiveCaptureTest();


	CProject& prj = CProject::Instance();
	CWtDataStore& ds = CWtDataStore::Instance();

	//Create Capture Object under project
	WtoHandle capHnd = ds.AddObject(CCapture_Class_Id, &prj);
	CCapture* capPtr = dynamic_cast<CCapture*> (ds.GetObjectFromHnd(capHnd));

	//Create CaptureFile under Capture Object
	WtoHandle capFlHnd = ds.AddObject(CCaptureFile_Class_Id, capPtr);
	CCaptureFile* capFlPtr = dynamic_cast<CCaptureFile*> (ds.GetObjectFromHnd(capFlHnd));

	std::string fname("output.pcap");

	/*Set the Adapter Name*/
	capFlPtr->SetFileName(fname);

	/*Parse the file*/
	capFlPtr->ParseFile();


	WtoVec wtv;
	capPtr->GetObjects(wtv,CPacket_Class_Id);
	std::cout << "Total Packets under Capture: " << wtv.size() << std::endl;

	WtoVec::const_iterator wit;

	uint32_t pktCnt = 0;

	for (wit = wtv.begin(); wit != wtv.end(); ++wit)
	{
		pktCnt++;
		CWtObject* wto = ds.GetObjectFromHnd((*wit)->GetWtoHandle());
		WtoVec phdr;
		wto->GetObjects(phdr,CPacketHeader_Class_Id);
		std::cout << "	--------Packet #: " << pktCnt << " , Total Headers under packet: " << phdr.size() << std::endl;

	}


	std::cout << "Core.Test compiled and run successfully!!" << std::endl;

	return 0;

}
