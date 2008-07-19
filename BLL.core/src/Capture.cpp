#include "Capture.h"
#include "PacketDb.h"
#include "WtLogger.h"
#include "AppConsts.h"

using Poco::Timestamp;

DEFINE_STATIC_LOGGER("bll.Capture", devLogger);

CCapture::CCapture() :
					  m_typeId(CCapture_Class_Id)
{
	Init();
}

CCapture::~CCapture()
{
}

CCapture::CCapture(std::string& name) :
					m_name(name),
					m_typeId(CCapture_Class_Id)
{
	Init();
}

void CCapture::Init()
{	
	//Set the Start of this capture
	m_startTime.update();
}
/*
Timestamp& CCapture::GetStartTimeStamp()
{
	return m_startTime;
}
*/

CPacket* CCapture::GetLastPacket()
{
	uint32_t sz = m_pkts.size();
	CPacket* pkt = GetPacketAt(sz - 1);	
	return pkt ;
}

CPacket* CCapture::GetFirstPacket()
{
	uint32_t sz = m_pkts.size();
	if (sz != 0)
	{
		CPacket* pkt = GetPacketAt(1);	
		return pkt ;
	}
	
	return NULL;
}


CPacket* CCapture::GetPacketAt(uint32_t index)
{
	PacketIndexMap::iterator pit = m_pkts.find(index);
	if (pit == m_pkts.end())
	{
		/* 
		 * Return the default handle which returns null values to display
		 */
		return NULL;
	}
	
	return CPacketDb::Instance().GetPacket(pit->second);
}

void CCapture::AddPacketToMap(WtoHandle pHnd)
{
	static uint32_t _pktIndex = 0;
	++_pktIndex ;
	m_pkts.insert(std::make_pair(_pktIndex,pHnd));

	std::stringstream ss ;
	ss << "Packet Hnd:" << pHnd ;
	ss << " Packet No: " << _pktIndex ;
    
	LOG_DEBUG( devLogger(), ss.str()) ;
	
}

