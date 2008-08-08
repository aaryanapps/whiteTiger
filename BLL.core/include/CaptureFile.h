/*
 * CaptureFile.h
 *
 *  Created on: Aug 7, 2008
 *      Author: smehta
 */

#ifndef _WT_CAPTUREFILE_H_
#define _WT_CAPTUREFILE_H_

#include "Capture.h"
#include "BllCoreExport.h"

namespace wt {
namespace core {


class CORE_EXPORT CCaptureFile : public CCapture
{
public:
	CCaptureFile(std::string& fname);
    ~CCaptureFile();

    /*Parse the File if it exists*/
    void 				ParseFile();

	virtual uint32_t 	GetClassId() {return m_classId; }

	virtual uint32_t 	GetDataLinkType(){ return m_dataLink; }

	std::string 		GetFileName() { return m_fileName; }

protected:
    virtual void Init();


private:
	CCaptureFile();


	static uint32_t m_classId; /*Unique class Id in the system*/

	uint32_t 		m_dataLink; /*Data link of the capture*/
	std::string 	m_fileName;	/*Name of the file*/


};
}
}

#endif /* _WT_CAPTUREFILE_H_ */
