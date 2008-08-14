#ifndef _WT_PACKET_H__
#define _WT_PACKET_H__

#include "Globals.h"
#include "FastDelegate.h"
#include "WtObject.h"
#include "CaptureLibraryDefs.h"
#include "Poco/Timestamp.h"

namespace wt {
namespace core {

typedef uint32_t PacketHeaderHnd;
typedef std::vector<PacketHeaderHnd> PktHeadersVec;

class CPacket : public wt::framework::CWtObject {

public:
    CPacket();
    CPacket(wt::core::capturelibrary::CapturedPkt* pkt);
    virtual ~CPacket();

    virtual uint32_t GetClassId() {return m_classId; }

    static wt::framework::CWtObject* Create();

    virtual void GetInheritedTypes(wt::framework::WtoTypeIdsVec& typeIdVec);

    uint32_t GetPacketLength() {return m_pktLen;}

    uint32_t GetCapturedDataLength() {return m_capLen;}

    std::string GetTimeStamp(){return m_pktTimeStamp;}

    std::string GetTimeStampRelToFirst(){return m_relToFirst;}

    std::string GetTimeStampRelToPrevious(){return m_relToPrevious;}

    std::string GetSrcAddr() {return m_srcStr;}

    std::string GetDstAddr() {return m_dstStr;}

    std::string GetProtocol(){return m_protoStr;}

    std::string GetInfoText() {return m_pktInfoStr;}

    virtual std::string GetIndexAsString();

	void SetStringValues(uint16_t colId, std::string& val);

    virtual bool Init(wt::core::capturelibrary::CapturedPkt* pkt);

    virtual void SetPacketIndex(uint32_t idx) {m_pktIndex = idx;}

    Poco::Timestamp& GetPacketTimeStamp() { return m_ts; }

	std::vector<uint8_t> m_pktData;

protected:
	static uint32_t m_classId;

	virtual bool ValidatePacket() = 0;
	virtual bool ParsePacket() = 0;

	//virtual void SetStringValues(uint16_t colId, std::string& val);
private:

	uint32_t m_pktLen;
	uint32_t m_capLen;
	uint32_t m_pktIndex;

	std::string m_pktTimeStamp;
	std::string m_relToFirst;
	std::string m_relToPrevious;
	std::string m_srcStr;
	std::string m_dstStr;
	std::string m_protoStr;
	std::string m_pktInfoStr;

	Poco::Timestamp m_ts;
	uint32_t m_protocol;

	//Delegates

	void CreateReadableTimeStamp();
	virtual void CreatePacketInfoText() = 0;

};
}
}

#endif // _WT_PACKET_H__
