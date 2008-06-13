#ifndef _WT_IPV4ADDRESS_H__
#define _WT_IPV4ADDRESS_H__

#include "Poco/Net/IPAddress.h"

namespace wt {
namespace framework {
namespace types {

#define IPV4_ADDR_LENGTH 4

class CIpv4Address : public Poco::Net::IPAddress {

public:
	CIpv4Address(){};
	~CIpv4Address(){};

private:
	uint8_t m_Addr[IPV4_ADDR_LENGTH];
};

} //common
} // framework
} // wt
#endif /*_WT_IPV4ADDRESS_H__*/
