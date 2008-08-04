#ifndef _WT_BOUNDCAPTURE_H__
#define _WT_BOUNDCAPTURE_H__

#include "Capture.h"
#include "Globals.h"
#include "PcapDefs.h"

class CPacket;

namespace wt {
namespace core {

class CBoundCapture : public CCapture
{
public:
    CBoundCapture();
    CBoundCapture(uint32_t id, uint32_t capId, std::string& name);
    ~CBoundCapture();

    virtual uint32_t GetTypeId() {return m_typeId; }

    virtual void run();

    void OnPacket(const void* pSender, WtoHandle& data);

private:

    std::string m_name;
    uint32_t 	m_typeId;
    newPktCallBack m_pktCb;

    /* void OnNewPacket(pkt p); */
    PacketIndexMap m_pkts;

};
}
}
#endif // _WT_BOUNDCAPTURE_H__
