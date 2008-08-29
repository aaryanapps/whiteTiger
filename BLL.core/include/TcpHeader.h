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

    virtual bool Init(uint32_t hdrOffset, const uint8_t* pktData);

	virtual uint32_t HeaderToCreateNext();

    virtual std::string GetSrcAddrString() ;
    virtual std::string GetDstAddrString() ;
    virtual std::string GetProtocolString();
    virtual std::string GetInfoString() ;

    virtual bool IsStringCapable(uint16_t colId);

    bool IsFin() const {return m_bFin;}
    bool IsSyn() const {return m_bSyn;}
    bool IsRst() const {return m_bRst;}
    bool IsPsh() const {return m_bPsh;}
    bool IsAck() const {return m_bAck;}
    bool IsUrg() const {return m_bUrg;}
    bool IsEce() const {return m_bEce;}
    bool IsCwr() const {return m_bCwr;}


protected:
	static uint32_t m_classId;

	static uint32_t m_hdrType;

	virtual bool ValidateHeader();
	virtual bool ParseHeader();

private:

	static uint32_t m_hdrLen;
	static std::string m_hdrTypeInStr;

	tcp_hdr		*m_hdr;
	std::string m_infoStr;

	uint16_t 	m_sPort;
	uint16_t 	m_dPort;
	uint32_t 	m_seq;
	uint32_t 	m_ack;
	uint16_t	m_win;
	uint8_t		m_flag;

	bool 		m_bSyn;
	bool		m_bAck;
	bool 		m_bFin;
	bool 		m_bRst;
	bool 		m_bPsh;
	bool 		m_bUrg;
	bool 		m_bEce;
	bool 		m_bCwr;

	std::string GetTcpFlagString();

};
}
}

#endif // _WT_PACKETHEADER_H__
