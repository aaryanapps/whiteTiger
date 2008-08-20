/*
 * CaptureType.h
 *
 *  Created on: Aug 8, 2008
 *      Author: saumil
 */

#ifndef _WT_CAPTURETYPE_H_
#define _WT_CAPTURETYPE_H_

#include "Globals.h"
#include "BllCoreExport.h"
#include "WtObject.h"
#include "WtObjectDefs.h"

typedef std::map<uint32_t, wt::framework::WtoHandle> PacketIndexMap;


namespace wt {
namespace core {

class  CORE_EXPORT  CCaptureType: public wt::framework::CWtObject
{
public:
	CCaptureType();
	virtual ~CCaptureType();

	/*Returns the packet at requested index*/
	virtual CWtObject* 	GetPacketAt(uint32_t index) ;

	/*Get range of packets*/
	virtual void 		GetPackets(uint32_t startIdx,
								   uint32_t endIdx,
								   wt::framework::WtoVec& wtv) ;

	/*Returns the last packet*/
	virtual CWtObject* 	GetLastPacket() ;

	/*Returns the first packet object*/
	virtual CWtObject* 	GetFirstPacket() ;

    /*Returns the Class Id*/
	virtual uint32_t 	GetClassId() {return m_classId; }

	static wt::framework::CWtObject* Create();

protected:
    virtual void Init();

private:
	static uint32_t 	m_classId;


};
}
}


#endif /* _WT_CAPTURETYPE_H_ */
