#ifndef _WT_MACADDRESS_H__
#define _WT_MACADDRESS_H__

#include "BllFrameworkExport.h"
//#include "Globals.h"
#include "DataTypes.h"

namespace wt {
namespace framework {
namespace types {

#define MAC_ADDR_LENGTH 6

class FRAMEWORK_EXPORT CMacAddress {

public:
	CMacAddress();
	~CMacAddress();
	CMacAddress(const char* data);
	CMacAddress(uint8_t* data);
	
	void CopyFrom(const char* data);
	void CopyFrom(uint8_t* data);
	void ToString(std::string& out);
	std::string ToString();
	uint8_t * c_str();
	
private:
	uint8_t m_Addr[MAC_ADDR_LENGTH];
};

} // types
} // framework
} // wt
#endif /*_WT_MACADDRESS_H__*/
