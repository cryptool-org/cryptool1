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
