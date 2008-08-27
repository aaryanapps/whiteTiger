/*
 * CaptureLibraryFileParser.h
 *
 *  Created on: Aug 26, 2008
 *      Author: saumil
 */

#ifndef _WT_CAPTURELIBRARYFILEPARSER_H_
#define _WT_CAPTURELIBRARYFILEPARSER_H_

#include "CaptureLibraryAdapter.h"
#include "pcap.h"

namespace wt {
namespace core {
namespace capturelibrary {

class CCaptureLibraryFileParser : public CCaptureLibraryAdapter {

public:
	CCaptureLibraryFileParser(std::string& fileName);
	~CCaptureLibraryFileParser();

	/*Parse the file*/
	void 	ParsePcapFile();

protected:
	/*Init the pcap desc.*/
	virtual pcap_t* Init();

private:

	std::string _strFileName; 			/* Name of File*/

};

}
}
}
#endif /* _WT_CAPTURELIBRARYFILEPARSER_H_ */
