#ifndef _WT_ARPHEADERIMPL_H__
#define _WT_ARPHEADERIMPL_H__

class CArpHeaderImpl {
	
public:
	CArpHeaderImpl(){};
	virtual ~CArpHeaderImpl(){};
	
	virtual std::string GetHeaderAbbrName() = 0;
	virtual std::string GetInfoString() = 0;
	virtual std::string GetProtocolString() = 0;
	
	virtual bool ValidateHeader() = 0;
	virtual bool ParseHeader() = 0;
private:
	
};

#endif /*ARPHEADERIMPL_H_*/
