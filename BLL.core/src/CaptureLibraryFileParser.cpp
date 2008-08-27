/*
 * CaptureLibraryFileParser.cpp
 *
 *  Created on: Aug 26, 2008
 *      Author: saumil
 */

#include "StdAfx.h"
#include "CaptureLibraryFileParser.h"
#include "CaptureLibraryAdapter.h"
#include "WtLogger.h"

using namespace wt::core::capturelibrary;

DEFINE_STATIC_LOGGER("core.capturelibrary.CaptureLibraryFileParser", devLogger)

CCaptureLibraryFileParser::CCaptureLibraryFileParser(std::string& fileName) :
	CCaptureLibraryAdapter(fileName), _strFileName(fileName)
{

}

CCaptureLibraryFileParser::~CCaptureLibraryFileParser()
{

}

void CCaptureLibraryFileParser::ParsePcapFile()
{
	CCaptureLibraryAdapter::StartCapture();
	return;
}

pcap_t* CCaptureLibraryFileParser::Init()
{
    char Errbuf[PCAP_ERRBUF_SIZE];

    pcap_t* _pcapDesc = pcap_open_offline (_strFileName.c_str(), Errbuf);

    if (_pcapDesc == NULL)
    {
    	std::stringstream ss;
    	ss 	<< "Could not initialize file to parse: "
    	    << _strFileName ;

    	LOG_ERROR( devLogger() , ss.str() );
    	return _pcapDesc;
    }

    return _pcapDesc;
}
