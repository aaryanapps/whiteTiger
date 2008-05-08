#ifndef _WT_PCAPUTILS_H__
#define _WT_PCAPUTILS_H__

#include "PcapDefs.h"
#include "pcap.h"

class CPcapUtils {

public:
    CPcapUtils();
    ~CPcapUtils();

    static bool GetAdapterList(pcap_if_t** ifs, char* err);

    static uint32_t GetDataLinkType (PcapHandle pHnd);

};

#endif //_WT_PCAPUTILS_H__
