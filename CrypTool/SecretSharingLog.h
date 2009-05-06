#ifndef _SECRETSHARINGLOG_
#define _SECRETSHARINGLOG_

#include <string>


class SecretSharingLog
{
public:
	SecretSharingLog(CString, CString, CString, CString, CString, CString, CString, long*, Big*, bool*, Big*, Big*, Big, bool, bool);
	std::string GetLogText();

protected:

private:
	std::string PartyLimit;
	std::string PrimeLimit;
	std::string Secret;
	std::string Participants;
	std::string Threshold;
	std::string Polynomial;
	std::string Prime;
	long *Parameter;
	Big *Shares;
	bool *IsSelected;
	Big *Numerator;
	Big *Denominator;
	Big Result;
	bool primeFlag;
	bool coeffFlag;

	std::string LogText;
};

#endif
