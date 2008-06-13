#ifndef _WT_IPV6ADDRESS_H__
#define _WT_IPV6ADDRESS_H__

#include "Poco/Net/IPAddress.h"

namespace wt {
namespace framework {
namespace types {

#define IPV6_ADDR_LENGTH 16

class CIpv6Address : public Poco::Net::IPAddress {

public:
	CIpv6Address(){};
	~CIp64Address(){};

private:
	uint8_t m_Addr[IPV6_ADDR_LENGTH];
};

} // types
} // framework
} // wt
#endif /*_WT_IPV6ADDRESS_H__*/

