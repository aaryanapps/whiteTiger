#ifndef _WT_UDPHEADER_H__
#define _WT_UDPHEADER_H__

#include "Globals.h"
#include "PacketHeader.h"
#include "net/udp.h"

namespace wt {
namespace core {


class CUdpHeader : public CPacketHeader {

public:
	CUdpHeader();
	CUdpHeader(uint32_t hnd,  uint32_t len, const uint8_t* hdrData);
    virtual ~CUdpHeader();

    std::string GetHeaderAbbrName()
    {
    	std::string s("Udp");
    	return s;
    }
    virtual uint32_t GetTypeId() {return m_typeId; }

    uint32_t GetHeaderLength() {return m_hdrLen;}
    virtual bool Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData);

	virtual uint32_t HeaderToCreateNext();

    virtual std::string GetSrcAddrString();
    virtual std::string GetDstAddrString();
    virtual std::string GetProtocolString();
    virtual std::string GetInfoString();

    virtual bool IsStringCapable(uint16_t colId);

    virtual void GetInheritedTypes(wt::framework::WtoTypeIdsVec& typeIdVec)
    {
    	CPacketHeader::GetInheritedTypes(typeIdVec);
    	typeIdVec.push_back(CUdpHeader::m_classId);
    	return;
    }

protected:
	static uint32_t m_classId;
	virtual bool ValidateHeader();
	virtual bool ParseHeader();

private:
	uint32_t 	m_typeId;

	uint32_t m_hdrLen;
	std::string m_hdrTypeInStr;
	uint32_t m_hdrType;

	udp_hdr		*m_hdr;
	std::string m_infoStr;

	uint16_t 	m_sPort;
	uint16_t 	m_dPort;
	uint16_t	m_len;
	uint16_t	m_chksum;

	//std::string GetTcpFlag();

};
}
}

#endif // _WT_PACKETHEADER_H__
