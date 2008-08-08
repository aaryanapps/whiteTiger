#ifndef _WT_LIVECAPTURE_H__
#define _WT_LIVECAPTURE_H__

#include "Globals.h"
#include "Capture.h"
#include "BllCoreExport.h"

namespace wt {
namespace core {

class CORE_EXPORT CLiveCapture : public CCapture
{
public:
    CLiveCapture();
    CLiveCapture(std::string& name);
    ~CLiveCapture();

	virtual uint32_t 	GetClassId() {return m_classId; }

	virtual uint32_t 	GetDataLinkType();


	bool 				RegisterNewPacketNotification();

	void 				OnNewPacket(WtoHandle pkt, void *data);


protected:
    virtual void Init();


private:

	static uint32_t m_classId; /*Unique class Id in the system*/

	uint32_t 		m_dataLink; /*Data link of the capture*/

    void 			NotifyNewPacket(WtoHandle pHnd);

};
}
}

#endif // _WT_LIVECAPTURE_H__
