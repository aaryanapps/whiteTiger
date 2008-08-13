#ifndef _WT_TCPHEADER_H__
#define _WT_TCPHEADER_H__

#include "Globals.h"
#include "PacketHeader.h"
#include "net/tcp.h"

namespace wt {
namespace core {


class CTcpHeader : public CPacketHeader {

public:
	CTcpHeader();
	CTcpHeader(uint32_t hnd,  uint32_t len, const uint8_t* hdrData);
    virtual ~CTcpHeader();

    std::string GetHeaderAbbrName()
    {
    	std::string s("Tcp");
    	return s;
    }

    /*Returns the Class Id*/
	virtual uint32_t 	GetClassId() {return m_classId; }

	static wt::framework::CWtObject* Create();

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
    	typeIdVec.push_back(CTcpHeader::m_classId);
    	return;
    }

protected:
	static uint32_t m_classId;

	virtual bool ValidateHeader();
	virtual bool ParseHeader();

private:

	uint32_t m_hdrLen;
	std::string m_hdrTypeInStr;
	uint32_t m_hdrType;

	tcp_hdr		*m_hdr;
	std::string m_infoStr;

	uint16_t 	m_sPort;
	uint16_t 	m_dPort;
	uint32_t 	m_seq;
	uint32_t 	m_ack;
	uint16_t	m_win;
	uint8_t		m_flag;

	std::string GetTcpFlag();

};
}
}

#endif // _WT_PACKETHEADER_H__
