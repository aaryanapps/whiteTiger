/*
 * CaptureFileParser.h
 *
 *  Created on: Aug 7, 2008
 *      Author: smehta
 */

#ifndef _WT_CAPTUREFILEPARSER_H_
#define _WT_CAPTUREFILEPARSER_H_

#include "BllCoreExport.h"
#include "Globals.h"

namespace wt {
namespace core {

typedef enum {

	FILE_UNKNWN = 1,
	FILE_PCAP

} CaptureFileFormat;

class CORE_EXPORT CCaptureFileParser
{
public:
	CCaptureFileParser();
    ~CCaptureFileParser();

    /*Parse the File if it exists*/
    static void ParseFile(std::string& fname, CaptureFileFormat fileFormat);

    /*Directly parse Pcap File*/
    static void ParsePcapFile(std::string& fname);


private:


};
}
}


#endif /* _WT_CAPTUREFILEPARSER_H_ */
