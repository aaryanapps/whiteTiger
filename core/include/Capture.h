#ifndef _WT_CAPTURE_H__
#define _WT_CAPTURE_H__

#include "Globals.h"
#include "Poco/Runnable.h"
#include "Poco/BasicEvent.h"
#include "Poco/Timestamp.h"
#include "PcapDefs.h"
#include "WtObject.h"
#include "WtObjectDefs.h"

typedef std::map<uint32_t, WtoHandle> PacketIndexMap;
class CPacket;
class CCapture: public Poco::Runnable, public CWtObject
{
public:
	CCapture();
	CCapture(std::string& name);
	virtual ~CCapture();
	
	virtual void run() = 0;

	virtual uint32_t GetTypeId() {return m_typeId; }
    //Events
    Poco::BasicEvent<PcapHandle> NewNetworkPacket;

    //Poco::Timestamp& GetStartTimeStamp();
    
    void SetCaptureName(std::string& name) {m_name = name;}
    std::string GetCaptureName() {return m_name;}

	virtual CPacket* GetPacketAt(uint32_t index) ;
	
	CPacket* GetLastPacket() ;
	CPacket* GetFirstPacket() ;
		
protected:
    virtual void Init();
	virtual uint32_t GetDataLinkType() {return 0;}
    void AddPacketToMap(WtoHandle pHnd);
    
private:
    std::string 		m_name;
    uint32_t 			m_typeId;
    Poco::Timestamp 	m_startTime;
    
    PacketIndexMap m_pkts;
    
};

#endif /*CAPTURE_H_*/
