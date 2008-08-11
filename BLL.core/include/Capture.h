#ifndef _WT_CAPTURE_H__
#define _WT_CAPTURE_H__

#include "Globals.h"
#include "WtObject.h"
#include "WtObjectDefs.h"

#include "Poco/Timestamp.h"


typedef std::map<uint32_t, WtoHandle> PacketIndexMap;


namespace wt {
namespace core {

class CCapture: public wt::framework::CWtObject
{
public:
	CCapture(std::string& name);
	virtual ~CCapture();

    std::string GetCaptureName() {return m_name;}

protected:
    virtual void Init();

    virtual uint32_t GetDataLinkType() {return 0;}

	void AddPacketToMap(WtoHandle pHnd);

private:

	CCapture();

	static uint32_t 	m_classId;

    std::string 		m_name;
    Poco::Timestamp 	m_startTime;

    PacketIndexMap 		m_pkts;

};
}
}
#endif /*CAPTURE_H_*/
