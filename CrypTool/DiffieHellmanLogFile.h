// DiffieHellmanLogFile.h

#ifndef _DIFFIEHELLMANLOGFILE_
#define _DIFFIEHELLMANLOGFILE_

#include <string>

class DiffieHellmanLogFile
{
private:
	std::string Generator;
	std::string PrimeModule;
	std::string SecretAlice;
	std::string SecretBob;
	std::string SharedKeyAlice;
	std::string SharedKeyBob;
	std::string SessionKeyAlice;
	std::string SessionKeyBob;

	std::string LogText;

protected:

public:
	DiffieHellmanLogFile(std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);

	std::string GetLogText();

	void MakeUpText(std::string&, int);
};

#endif