
#include "net/MacAddress.h"
#include "Globals.h"

using namespace wt::framework::types;

CMacAddress::CMacAddress()
{
	
}

CMacAddress::~CMacAddress()
{
	
}

CMacAddress::CMacAddress(const char* data)
{
	memcpy(&m_Addr[0], data, 6*(sizeof(int8_t)));
}

CMacAddress::CMacAddress(uint8_t* data)
{
	memcpy(&m_Addr[0], data, 6*(sizeof(int8_t)));
}


void CMacAddress::CopyFrom(const char* data)
{
	memcpy(m_Addr, data, 6*sizeof(int8_t));
}

void CMacAddress::CopyFrom(uint8_t* data)
{
	memcpy(m_Addr, data, 6*sizeof(uint8_t));
}

void CMacAddress::ToString(std::string& out)
{
    char address[] = "xx:xx:xx:xx:xx:xx";
    sprintf(address, "%02x:%02x:%02x:%02x:%02x:%02x",
	    m_Addr[0], m_Addr[1], m_Addr[2],
	    m_Addr[3], m_Addr[4], m_Addr[5]);
    out = address;
}

std::string CMacAddress::ToString()
{
    std::string s;
    ToString(s);
    std::transform(s.begin(), s.end(), s.begin(),
                 (int(*)(int)) std::toupper);
    return s;
}

uint8_t * CMacAddress::c_str()
{
	return &m_Addr[0];
}
