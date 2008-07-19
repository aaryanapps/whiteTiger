#ifndef _WT_TCPHEADER_H__
#define _WT_TCPHEADER_H__

#include "Globals.h"
#include "PacketHeader.h"
#include "net/tcp.h"

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
    virtual uint32_t GetTypeId() {return m_typeId; }
    
    uint32_t GetHeaderLength() {return m_hdrLen;}
    virtual bool Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData);
    
	virtual uint32_t HeaderToCreateNext();

    virtual std::string GetSrcAddrString();
    virtual std::string GetDstAddrString();
    virtual std::string GetProtocolString();
    virtual std::string GetInfoString();	

    virtual bool IsStringCapable(uint16_t colId);
    
protected:
	virtual bool ValidateHeader();
	virtual bool ParseHeader();
	
private:
	uint32_t 	m_typeId;
	
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
#endif // _WT_PACKETHEADER_H__
