#ifndef WT_COMMONPACKETUTILS_H__
#define WT_COMMONPACKETUTILS_H__

#include "Globals.h"
#include "PcapDefs.h"

#define WT_USEC                1000000L

class CCommonPacketUtils {
public:
	
	uint32_t SuperFastHash (const char * data, int len);
	
	static uint32_t GetHeaderLength(uint32_t);
	static uint32_t GetNetworkToHostOrder(uint32_t var);
	static uint16_t GetNetworkToHostOrder(uint16_t var);
	static std::string GetIpFromU32(uint32_t ip);
	static std::string GetIpFromNetU32(uint32_t netIp);
	static uint32_t GetU32(uint8_t* data);
	static uint16_t GetU16(uint8_t* data);
	static std::string GetHexFromU8(const uint8_t *data, uint32_t len);

	static int64_t ConvertTimeValToU64(timeval& tv);
	static std::string ConvertMicroSecToSecString(int64_t);
private:
	
};


#endif /*WT_COMMONPACKETUTILS_H__*/
