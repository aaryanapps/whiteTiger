#include "StdAfx.h"

#include "TcpHeader.h"
#include "Globals.h"
#include "net/HeaderTypes.h"
#include "PacketHeaderDb.h"
#include "PcapDefs.h"
#include "CommonPacketUtils.h"
#include "WtLogger.h"
#include "CoreConsts.h"

using namespace wt::core;

//DEFINE_STATIC_LOGGER("bll.TcpHeader", devLogger);

CTcpHeader::CTcpHeader() :
						  m_typeId(CTcpHeader_Class_Id)
{

}

CTcpHeader::~CTcpHeader()
{

}

bool CTcpHeader::Init(uint32_t hnd, uint32_t hdrOffset, const uint8_t* pktData)
{
	m_hdrType = WT_TCP_HDR;
	m_hdrTypeInStr = WT_TCP_STR;
	m_hdrLen = WT_TCP_HDRLEN ;

	if (!pktData)
	{
		/*No Data*/
		return false;
	}

	//TODO: Get the parent Packet instance and check the captured length to header length.

	uint8_t* data = const_cast<uint8_t*> (pktData + hdrOffset);
	m_hdr = (tcp_hdr *)	data;

	if (!m_hdr)
		return false;

	if (!ValidateHeader())
		return false;

	if (!ParseHeader())
		return false;

	return true;
}

bool CTcpHeader::IsStringCapable(uint16_t colId)
{
	switch (colId)
	{
	case Column_SrcAddr_String:
		return false;
	case Column_DstAddr_String:
		return false;
	case Column_Protocol_String:
		return true;
	case Column_Info_String:
		return true;
	default:
		return false;
	}

	return false;
}

std::string CTcpHeader::GetSrcAddrString()
{
	std::stringstream s;
	s << "";
	return s.str();
}

std::string CTcpHeader::GetDstAddrString()
{
	std::stringstream s;
	s << "";
	return s.str();
}

std::string CTcpHeader::GetProtocolString()
{
	std::string s(WT_TCP_STR);
	return s;
}

std::string CTcpHeader::GetInfoString()
{
	std::stringstream ss;

	ss << m_sPort << " > ";
	ss << m_dPort << " " ;
	ss << GetTcpFlag() << " ";
	ss << "Seq=" << m_seq << " ";
	ss << "Ack=" << m_ack << " ";
	ss << "Win=" << m_win << " ";

	return ss.str();
}

bool CTcpHeader::ValidateHeader()
{
	return true;
}

bool CTcpHeader::ParseHeader()
{
	m_sPort = CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->th_sport);
	m_dPort = CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->th_dport);
	m_seq 	= CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->th_seq);
	m_ack	= CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->th_ack);
	m_flag	= m_hdr->th_flags ;
	m_win	= CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->th_win);

	//TODO: Create the appropriate Data class e.g Http, Https, Telnet, Ftp, etc.

	return true;
}

uint32_t CTcpHeader::HeaderToCreateNext()
{
	return WT_UNKWN;
}


/////// Private Methods;





std::string CTcpHeader::GetTcpFlag()
{
	std::stringstream flg;

	bool isAck = false;
	bool isSyn = false;

	flg << "[" ;

	if (m_flag & TH_ACK)
	{
		isAck = true;
	}

	if (m_flag & TH_SYN)
	{
		isSyn = true;
		flg << "SYN";
	}

	if (isAck && isSyn)
		flg << "," ;

	if (isAck)
		flg << "ACK";

	if (isAck && !isSyn)
	{

		if (m_flag & TH_CWR)
		{
			flg << "CWR";
		}

		if (m_flag & TH_ECE)
		{
			flg << "ECE";
		}

		if (m_flag & TH_URG)
		{
			flg << "URG";
		}

		if (m_flag & TH_PUSH)
		{
			flg << "PUSH";
		}

		if (m_flag & TH_RST)
		{
			flg << "RST";
		}

		if (m_flag & TH_FIN)
		{
			flg << "FIN";
		}

	}

	flg << "]";

	return flg.str();
}
