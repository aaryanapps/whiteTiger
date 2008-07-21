#include "StdAfx.h"

#include "Packet.h"
#include "Globals.h"
#include "PcapDefs.h"
#include "PacketHeaderDb.h"
#include "PacketDb.h"
#include <sstream>
#include "net/HeaderTypes.h"
#include "WtLogger.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Capture.h"
#include "CommonPacketUtils.h"
#include "AppConsts.h"

DEFINE_STATIC_LOGGER("bll.Packet", devLogger);

CPacket::CPacket() :
					m_typeId(CPacket_Class_Id)
{
	//m_newPktHdr = fastdelegate::MakeDelegate(this, &CPacket::OnNewPacketHeader);
}


CPacket::~CPacket()
{
	
}

CPacket::CPacket(uint32_t hnd, const pcapPktHdr *pkt, 
							  const char* pktData) :
							m_pktHnd(hnd), 
							m_pktLen(pkt->len), m_capLen(pkt->len),
							m_tm(pkt->ts)
{
	m_pktData.reserve(pkt->len);
	
	/* Store the binary Data*/
	for (uint32_t i = 0; i < pkt->len ; ++i)
	{
		m_pktData.push_back(i);
	}

}

bool CPacket::Init(uint32_t hnd,
				   const pcapPktHdr *pkt, 
	  			   const uint8_t* pktData)
{
	m_pktHnd = hnd;
	m_capLen = pkt->caplen;
	m_pktLen = pkt->len;
	m_tm	 = pkt->ts;
	
	m_pktData.reserve(pkt->len);
	
	uint8_t *data = const_cast<uint8_t*> (pktData);
	/* Store the binary Data*/
	for (uint32_t i = 0; i < pkt->len ; ++i)
	{
		m_pktData.push_back(*data);
		++data;
	}

	Poco::Timestamp tmp(CCommonPacketUtils::ConvertTimeValToU64(m_tm));
	m_ts = tmp ;
	
	/*Covert TimeStamp to String*/
	CreateReadableTimeStamp();

	//TODO: Initialize all the str vars
	m_pktInfoStr = "Info Message from CPacket!!";
	
	/* TODO: Solve the error comming from here.
	CPacketDb& pd = CPacketDb::Instance();
	pd.RegisterNewPacketHeaderNotification(m_pktHnd, m_newPktHdr);	
	*/
	return true;
}


//////// Private helpers

void CPacket::CreateReadableTimeStamp()
{
    struct tm *ltime;
    char timestr[16];
    time_t local_tv_sec;

    Poco::Timestamp cts(m_ts);
    int64_t diff(0L);
    
    CCapture * pCap = dynamic_cast<CCapture*>(GetParent());
    
    if (!pCap)
    {
    	LOG_ERROR(devLogger() , "No Parent Capture for packet")
    }
    else
    {
    	Poco::Timestamp fts(0L);
    	std::stringstream ss;

    	CPacket* fPkt = dynamic_cast<CPacket *> (pCap->GetFirstPacket());
    	if (fPkt)
    	{
    		if (this == fPkt)
    		{
    			fts = 0L;
    			cts = 0L;
    		}
    		else
    		{
    			fts = fPkt->GetPacketTimeStamp();
    		}
    	}
    	else
    	{
    		cts = 0L;
    	}

    	diff = cts - fts;
    	m_relToFirst = CCommonPacketUtils::ConvertMicroSecToSecString(diff);

    	ss << "Microsecond diff: " << m_relToFirst; 	
    	LOG_DEBUG(devLogger() , ss.str())
    }
    
    /* convert the timestamp to readable format */
    local_tv_sec = m_tm.tv_sec;
    ltime=localtime(&local_tv_sec);
    strftime( timestr, sizeof timestr, "%H:%M:%S", ltime);
  
    std::stringstream s;

    s.setf(std::ios::right);
    s.width(6);
    s.fill('0');
    s << m_tm.tv_usec ;
    s.unsetf(std::ios::right);
    m_pktTimeStamp = timestr;
    m_pktTimeStamp += "." ;
    m_pktTimeStamp += s.str();
    m_pktTimeStamp += " " ;
    
    /* Bug in Poco Lib: %H or %h does not return the hour
    m_pktTimeStamp = Poco::DateTimeFormatter::format(m_ts,std::string("%h:%M:%S.%i"));
    */

    Poco::DateTime dt(m_ts);
    
    std::stringstream ss ;
    ss << dt.hour() << ":";
    ss << dt.minute() << ":";
    ss << dt.second() << ".";
    ss.setf(std::ios::right);
    ss.width(3);
    ss.fill('0');
    ss << dt.millisecond() ;
    ss.width(3);
    ss.fill('0');
    ss << dt.microsecond() ;
    
    m_pktTimeStamp = ss.str();
    //m_pktTimeStamp = Poco::DateTimeFormatter::format(dt,std::string("%h:%M:%S.%i"));
}

bool CPacket::ValidatePacket()
{
	return true;
}

//TODO: Change this to template and general function
void CPacket::SetStringValues(uint16_t colId, std::string& val)
{
	switch (colId)
	{
	case Column_SrcAddr_String:
		m_srcStr = val;
		break;
	case Column_DstAddr_String:
		m_dstStr = val;
		break;
	case Column_Protocol_String:
		m_protoStr = val;
		break;
	case Column_Info_String:
		m_pktInfoStr = val;
		break;
	default:
		return;
	}
}


std::string CPacket::GetIndexAsString()
{
	std::stringstream s;
	s << m_pktIndex;
	return s.str();
}

/*	timeval m_tm;
void CPacket::OnNewPacketHeader(uint32_t hdrHnd)
{
    ValueCompareFunctor<PacketHeaderHnd> functor(hdrHnd) ;
    PktHeadersVec::iterator pit = std::find_if(m_hdrs.begin(), m_hdrs.end(), functor) ;
	
	if (pit == m_hdrs.end())
	{
		m_hdrs.push_back(hdrHnd);
	}
	else
	{
		//Print debug, error message
	}

	//Check for SRC Capable. DST Capable, Protocol Capable, TextInfo Capable
	
}
*/
