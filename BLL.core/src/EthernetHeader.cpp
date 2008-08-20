#include "StdAfx.h"

//#include <netinet/in.h>		/* ntohs() */

#include "net/ether_types.h"
#include "net/ether.h"

#include "Globals.h"
#include "CoreConsts.h"
#include "EthernetHeader.h"
#include "net/HeaderTypes.h"
#include "CommonPacketUtils.h"
#include "WtObject.h"
#include "WtObjectRegistrar.h"
#include "PacketHeaderFactory.h"

using namespace wt::core;

//uint32_t CEthernetHeader::m_classId = CEthernetHeader_Class_Id ;
uint32_t CEthernetHeader::m_classId = REGISTER_CREATOR(CEthernetHeader_Class_Id, CEthernetHeader::Create);
uint32_t CEthernetHeader::m_hdrType = REGISTER_HDRTYPE(WT_ETH,CEthernetHeader_Class_Id) ;


CEthernetHeader::CEthernetHeader() :
									m_hdrLen(0)
{
	AddAsDerivedClassId(CEthernetHeader_Class_Id);
}

CEthernetHeader::~CEthernetHeader()
{

}

CEthernetHeader::CEthernetHeader(uint32_t hdrOffset, const uint8_t* pktData)
{
	AddAsDerivedClassId(CEthernetHeader_Class_Id);
	Init(hdrOffset, pktData);
}

wt::framework::CWtObject* CEthernetHeader::Create()
{
	return new CEthernetHeader();
}

bool CEthernetHeader::Init(uint32_t hdrOffset, const uint8_t* pktData)
{
	m_hdrTypeInStr = WT_ETH_STR;
	m_hdrLen = WT_ETH_HDRLEN ;

	if (!pktData)
	{
		/*No Data*/
		return false;
	}

	//TODO: Get the parent Packet instance and check the captured length to header length.

	m_hdrData = pktData + hdrOffset;
	m_hdr = (struct ether_hdr *) pktData;

	if (!m_hdr)
		return false;

	if (!ValidateHeader())
		return false;

	if (!ParseHeader())
		return false;

	return true;
}

bool CEthernetHeader::ValidateHeader()
{
	return true;
}

bool CEthernetHeader::ParseHeader()
{
	m_srcMac.CopyFrom(&(m_hdr->ether_shost[0]));
	m_dstMac.CopyFrom(&(m_hdr->ether_dhost[0]));

	return true;
}

uint32_t CEthernetHeader::HeaderToCreateNext()
{
	return CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->ether_type);
}

std::string CEthernetHeader::GetInfoString()
{
	std::stringstream ss;
	ss << "Ethernet II - Next Hdr: " ;
	ss << CCommonPacketUtils::GetNetworkToHostOrder(m_hdr->ether_type);
	return ss.str();
}

bool CEthernetHeader::IsStringCapable(uint16_t colId)
{
	switch (colId)
	{
	case Column_SrcAddr_String:
		return true;
	case Column_DstAddr_String:
		return true;
	case Column_Protocol_String:
		return true;
	case Column_Info_String:
		return true;
	default:
		return false;
	}

	return false;
}
