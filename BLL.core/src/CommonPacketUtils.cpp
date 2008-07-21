#include "StdAfx.h"

#include "CommonPacketUtils.h"
#include "net/HeaderTypes.h"
#include "Globals.h"
#ifdef WIN32
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include <netinet/in.h>
#endif

#include <iomanip>
using namespace std;

///////
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

uint32_t CCommonPacketUtils::SuperFastHash (const char * data, int len) {
uint32_t hash = len, tmp;
int rem;

    if (len <= 0 || data == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (;len > 0; len--) {
        hash  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        data  += 2*sizeof (uint16_t);
        hash  += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
        case 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= data[sizeof (uint16_t)] << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += *data;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}
///////

uint32_t CCommonPacketUtils::GetHeaderLength(uint32_t hdr)
{
	//TODO Change this to map, Added quickly for proto
	switch(hdr)
	{
	case WT_ETH:
		return WT_ETH_HDRLEN;
	case WT_ARP:
		return WT_ARP_HDRLEN;
	case WT_IP:
		return WT_IP_HDRLEN;
	case WT_IPV6:
		return WT_IPV6_HDRLEN;
	default:
		return WT_UNKWN_HDRLEN;
	}
	
}
int64_t CCommonPacketUtils::ConvertTimeValToU64(timeval& tv)
{
	int64_t sec, usec;
	sec  = (int64_t)tv.tv_sec;
	usec = (int64_t)tv.tv_usec;
	return ((WT_USEC * sec) + usec);	
}

std::string CCommonPacketUtils::ConvertMicroSecToSecString(int64_t usec)
{
	uint64_t sec = usec / 1000000 ;
	uint64_t msec = usec % 1000000 ;
	std::stringstream s;

    s.setf(std::ios::right);
    s << sec ;
    s << "." ;
    s.width(6);
    s.fill('0');
    s << msec ;

    return s.str();
}


/*
 * This method is implemented so the caller can identify what the input is
 * Only for readability
 */
std::string CCommonPacketUtils::GetIpFromNetU32(uint32_t netIp)
{
	uint32_t ip = GetNetworkToHostOrder(netIp);
	return GetIpFromU32(ip);
}

std::string CCommonPacketUtils::GetIpFromU32(uint32_t ip)
{

	std::stringstream s;
//	s << static_cast<uint32_t> (ip&0xff) << ".";
//	s << static_cast<uint32_t> ((ip>>8)&0xff)  << "." ;
//	s << static_cast<uint32_t> ((ip>>16)&0xff) << "." ;	
//	s << static_cast<uint32_t> ((ip>>24)&0xff) ;
	s << static_cast<uint32_t> ((ip>>24)&0xff) << "." ;
	s << static_cast<uint32_t> ((ip>>16)&0xff) << "." ;
	s << static_cast<uint32_t> ((ip>>8)&0xff)  << "." ;
	s << static_cast<uint32_t> (ip&0xff) ;
	
	return s.str();	
}

std::string CCommonPacketUtils::GetHexFromU8(const uint8_t *data, uint32_t len)
{
	std::ostringstream ss;
	ss.setf ( ios::hex, ios::basefield );
	uint8_t * _data = const_cast<uint8_t *> (data);
	for (uint32_t i = 0; i < len; ++i)
	{
		//ss << std::setbase(16) << std::setw(2) << std::setfill('0') << *_data;
		ss << std::setw(2) << std::setfill('0') << (int) *_data ;
		++_data;
	}
	
	return ss.str();
}

#if	__BYTE_ORDER == __LITTLE_ENDIAN

uint32_t CCommonPacketUtils::GetNetworkToHostOrder(uint32_t var)
{
	return ntohl(var);
}

uint16_t CCommonPacketUtils::GetNetworkToHostOrder(uint16_t var)
{
	return ntohs(var);
}


uint32_t CCommonPacketUtils::GetU32(uint8_t* data)
{
	uint32_t u32 = (uint32_t)(*(data + 3) << 24 | *(data + 2) << 16 | *(data + 1) << 8 | *(data + 0));
	return u32;
}


uint16_t CCommonPacketUtils::GetU16(uint8_t* data)
{
	uint16_t u16 = (uint16_t)(*(data + 1) << 8 | *(data + 0));
	return u16;
}


#elif	__BYTE_ORDER == __BIG_ENDIAN
uint32_t CCommonPacketUtils::GetNetworkToHostOrder(uint32_t var)
{
	return var;
}

uint16_t CCommonPacketUtils::GetNetworkToHostOrder(uint16_t var)
{
	return var;
}

uint32_t CCommonPacketUtils::GetU32(uint8_t* data)
{
	uint32_t u32 = (uint32_t)(*(data + 0) << 24 | *(data + 1) << 16 | *(data + 2) << 8 | *(data + 3));
	return u32;
}

uint16_t CCommonPacketUtils::GetU16(uint8_t* data)
{
	uint16_t u16 = (uint16_t)(*(data + 0) << 8 | *(data + 1));
	return u16;
}


std::string CCommonPacketUtils::GetIpFromU32(uint32_t ip)
{
	std::stringstream s;
	
	s << static_cast<uint32_t> ((ip>>24)&0xff) << "." ;
	s << static_cast<uint32_t> ((ip>>16)&0xff) << "." ;
	s << static_cast<uint32_t> ((ip>>8)&0xff)  << "." ;
	s << static_cast<uint32_t> (ip&0xff) ;

	return s.str();	
}

#else
#error	"Please #define __BYTE_ORDER"
#endif
