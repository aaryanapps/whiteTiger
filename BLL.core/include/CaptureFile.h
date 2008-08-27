/*
 * CaptureFile.h
 *
 *  Created on: Aug 7, 2008
 *      Author: smehta
 */

#ifndef _WT_CAPTUREFILE_H_
#define _WT_CAPTUREFILE_H_

#include "CaptureType.h"
#include "BllCoreExport.h"
#include "CaptureLibraryDefs.h"

namespace wt {
namespace core {


class CORE_EXPORT CCaptureFile : public CCaptureType
{
public:
	CCaptureFile(std::string& fname);
    virtual ~CCaptureFile();

    /*Parse the File if it exists*/
    void 				ParseFile();

    /*Returns the Class Id*/
	virtual uint32_t 	GetClassId() {return m_classId; }

	/*Get the next default filename.*/
	static std::string&	GetDefaultFileName();

	void 		OnNewPacket(wt::core::capturelibrary::CapturedPkt* pkt, void* data);

	//Getters,Setters
	uint32_t 	GetDataLinkType(){ return m_dataLink; }

	void 		SetDataLinkType(uint32_t dtType){ m_dataLink = dtType; }

	/*Get the filename*/
	std::string 		GetFileName() { return m_fileName; }

	/*Set the filename*/
	void 		 		SetFileName(std::string& fname) { m_fileName = fname; }


	static wt::framework::CWtObject* Create();

protected:
    virtual void Init();

private:
	CCaptureFile();


	static uint32_t 	m_classId; 	/*Unique class Id in the system*/
	static std::string 	m_defFile; /*Number representing the default file #*/

	uint32_t 		m_dataLink; /*Data link of the capture*/

	std::string 	m_fileName;	/*Name of the file*/

	wt::core::capturelibrary::NewPktDelegate	m_dNewPkt;


};
}
}

#endif /* _WT_CAPTUREFILE_H_ */
