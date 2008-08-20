#include "StdAfx.h"

#include "Packet.h"
#include "Globals.h"
#include <sstream>
#include "net/HeaderTypes.h"
#include "WtLogger.h"

#include "Poco/Timestamp.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"

#include "Capture.h"
#include "CaptureType.h"
#include "CaptureLibraryDefs.h"
#include "CommonPacketUtils.h"
#include "CoreConsts.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"

using namespace wt::core;
using namespace wt::framework;

//uint32_t CPacket::m_classId = 0x00000100 ;
uint32_t CPacket::m_classId = REGISTER_CREATOR(CPacket_Class_Id, CPacket::Create);


DEFINE_STATIC_LOGGER("core.Packet", devLogger)

CPacket::CPacket()
{
	AddAsDerivedClassId(CPacket_Class_Id);
	//m_newPktHdr = fastdelegate::MakeDelegate(this, &CPacket::OnNewPacketHeader);
}

CWtObject* CPacket::Create()
{
	return NULL;
}

CPacket::~CPacket()
{

}

CPacket::CPacket(wt::core::capturelibrary::CapturedPkt* pkt)
{
	Init(pkt);
}

bool CPacket::Init(wt::core::capturelibrary::CapturedPkt* pkt)
{
	m_capLen = pkt->_capLen;
	m_pktLen = pkt->_len;

	Poco::Timestamp tmp(CCommonPacketUtils::ConvertTimeValToU64(pkt->_ts._sec, pkt->_ts._usec));
	m_ts = tmp ;

	m_pktData.reserve(pkt->_capLen);

	m_pktData.assign(pkt->_pktData.begin(), pkt->_pktData.begin());

	/*Covert TimeStamp to String*/
	CreateReadableTimeStamp();

	//TODO: Initialize all the str vars
	m_pktInfoStr = "Info Message from CPacket!!";

	return true;
}


//////// Private helpers

void CPacket::CreateReadableTimeStamp()
{
/*
	struct tm *ltime;
    char timestr[16];
    time_t local_tv_sec;
*/
    Poco::Timestamp cts(m_ts);
    //int64_t diff(0L);

    CCapture * pCap = dynamic_cast<CCapture*>(GetParent());

    if (!pCap)
    {
    	LOG_ERROR(devLogger() , "No Parent Capture for packet")
    }
    else
    {
    	Poco::Timestamp fts(0L);
    	std::stringstream ss;
/* TODO:Uncomment this logic
		CCaptureType* cCaptype = dynamic_cast<CPacket *> (pCap->GetObject());
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
*/
    }


    /* convert the timestamp to readable format */
/*
    local_tv_sec = m_ts.epochTime();
    //uint64_t local_tv_usec = m_ts.epochMicroseconds();
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
*/
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
