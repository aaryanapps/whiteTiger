#ifndef _WT_MACADDRESS_H__
#define _WT_MACADDRESS_H__

#include "Globals.h"
//#include ""

#define MAC_ADDR_LENGTH 6

class CMacAddress {

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

#endif /*_WT_MACADDRESS_H__*/
