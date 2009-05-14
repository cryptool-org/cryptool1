/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

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