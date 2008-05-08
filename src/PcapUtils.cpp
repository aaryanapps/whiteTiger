
#include "PcapUtils.h"
#include "pcap.h"
#include "PcapHandler.h"

CPcapUtils::CPcapUtils()
{
}

CPcapUtils::~CPcapUtils()
{
}


bool CPcapUtils::GetAdapterList(pcap_if_t** ifs, char* err)
{
/*
    if (ifs != NULL)
    {
        pcap_freealldevs(ifs);
    }
*/
    // Retrieve the interfaces list
    if (pcap_findalldevs(ifs, err) == -1)
        return false;

    if (ifs == NULL)
    {
        return false;
    }
    return true;
}

uint32_t CPcapUtils::GetDataLinkType (PcapHandle pHnd)
{
    
    CPcapHandler& ph = CPcapHandler::Instance();

    pcap_t *p = ph.GetPcapDesc(pHnd);
    //TODO: Think/Add of error notificaiton
    if (p)
    {
        return pcap_datalink(p);
    }
    else
    {
        return DLT_EN10MB;
    }
}



