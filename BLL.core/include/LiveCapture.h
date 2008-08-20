#ifndef _WT_LIVECAPTURE_H__
#define _WT_LIVECAPTURE_H__

#include "Globals.h"
#include "CaptureType.h"
#include "BllCoreExport.h"

namespace wt {
namespace core {

class CORE_EXPORT CLiveCapture : public CCaptureType
{
public:
    CLiveCapture();
    CLiveCapture(std::string& name);
    ~CLiveCapture();

	virtual uint32_t 	GetClassId() {return m_classId; }

	static wt::framework::CWtObject* Create();

	/*Call back function to be called when there is a new packet*/
	void 				OnNewPacket(wt::framework::WtoHandle pkt, void *data);


protected:
    virtual void Init();


private:

	static uint32_t m_classId; /*Unique class Id in the system*/

    void 			NotifyNewPacket(wt::framework::WtoHandle pHnd);

    /*Register for new packet notification*/
	bool			RegisterNewPacketNotification();
};
}
}

#endif // _WT_LIVECAPTURE_H__
