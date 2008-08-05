#ifndef _WT_PACKETHEADER_H__
#define _WT_PACKETHEADER_H__

#include "Globals.h"
#include "WtObject.h"

namespace wt {
namespace core {

class CPacketHeader : public wt::framework::CWtObject {

public:
	CPacketHeader();
    CPacketHeader(uint32_t hnd,  uint32_t len, const uint8_t* hdrData);
    virtual ~CPacketHeader();

    virtual uint32_t GetTypeId() {return m_typeId; }

    virtual std::string GetHeaderAbbrName() = 0;
    virtual uint32_t GetHeaderLength() = 0;
    virtual bool Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData);

	virtual uint32_t HeaderToCreateNext() = 0;

    virtual std::string GetSrcAddrString() = 0;
    virtual std::string GetDstAddrString() = 0;
    virtual std::string GetProtocolString() = 0;
    virtual std::string GetInfoString() = 0;

    virtual bool IsStringCapable(uint16_t colId) = 0;

protected:
	virtual bool ValidateHeader() = 0;
	virtual bool ParseHeader() = 0;

private:
	uint32_t 	m_hdrHnd;
    uint32_t 	m_typeId;

	uint32_t m_hdrLen;
	std::string m_hdrTypeInStr;
	uint8_t *m_hdrData;
	uint32_t m_hdrType;

	virtual bool CreateHeaders(){return false;};

};
}
}

#endif // _WT_PACKETHEADER_H__
