#include "StdAfx.h"

#include "TcpHeader.h"
#include "Globals.h"
#include "net/HeaderTypes.h"
#include "CommonPacketUtils.h"
#include "WtLogger.h"
#include "CoreConsts.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"
#include "PacketHeaderFactory.h"

using namespace wt::core;

uint32_t CTcpHeader::m_classId = REGISTER_CREATOR(CTcpHeader_Class_Id, CTcpHeader::Create);
uint32_t CTcpHeader::m_hdrType = REGISTER_HDRTYPE(WT_TCP,
												  WT_SELF_HEADER,
												  CTcpHeader_Class_Id) ;

std::string CTcpHeader::m_hdrTypeInStr = WT_TCP_STR;
uint32_t 	CTcpHeader::m_hdrLen = WT_TCP_HDRLEN ;

DEFINE_STATIC_LOGGER("core.TcpHeader", devLogger)

CTcpHeader::CTcpHeader() :
						m_hdr(NULL),
						m_sPort(0),
						m_dPort(0),
						m_seq(0),
						m_ack(0),
						m_win(0),
						m_flag(0),
						m_bSyn(false),
						m_bAck(false),
						m_bFin(false),
						m_bRst(false),
						m_bPsh(false),
						m_bUrg(false),
						m_bEce(false),
						m_bCwr(false)
{
	AddAsDerivedClassId(CTcpHeader_Class_Id);
}

wt::framework::CWtObject* CTcpHeader::Create()
{
	return new CTcpHeader();
}

CTcpHeader::~CTcpHeader()
{

}

bool CTcpHeader::Init(uint32_t hdrOffset, const uint8_t* pktData)
{


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
	return m_hdrTypeInStr;
}

std::string CTcpHeader::GetInfoString()
{
	std::stringstream ss;

	ss << m_sPort << " > ";
	ss << m_dPort << " " ;
	ss << GetTcpFlagString() << " ";
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

	if (m_flag & TH_ACK)
	{
		m_bAck = true;
	}

	if (m_flag & TH_SYN)
	{
		m_bSyn = true;
	}

	if (m_flag & TH_CWR)
	{
		m_bCwr = true;
	}

	if (m_flag & TH_ECE)
	{
		m_bEce = true;
	}

	if (m_flag & TH_URG)
	{
		m_bUrg = true;
	}

	if (m_flag & TH_PUSH)
	{
		m_bPsh = true;
	}

	if (m_flag & TH_RST)
	{
		m_bRst = true;
	}

	if (m_flag & TH_FIN)
	{
		m_bFin = true;
	}

	LOG_DEBUG( devLogger(), "Completed Parsing TCP Header") ;
	return true;
}

uint32_t CTcpHeader::HeaderToCreateNext()
{
	//TODO: Create the appropriate Data class e.g Http, Https, Telnet, Ftp, etc.
	return WT_UNKWN;
}


/////// Private Methods;


std::string CTcpHeader::GetTcpFlagString()
{
	std::stringstream flg;

	flg << "[" ;

	if (m_bSyn)
	{
		flg << "SYN";
	}

	if (m_bAck && m_bSyn)
		flg << "," ;

	if (m_bAck)
		flg << "ACK";

	if (m_bAck && !m_bSyn)
	{

		if (m_bCwr)
		{
			flg << " CWR";
		}

		if (m_bEce)
		{
			flg << " ECE";
		}

		if (m_bUrg)
		{
			flg << " URG";
		}

		if (m_bPsh)
		{
			flg << " PUSH";
		}

		if (m_bRst)
		{
			flg << " RST";
		}

		if (m_bFin)
		{
			flg << " FIN";
		}

	}

	flg << "]";

	return flg.str();
}
