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

#include "stdafx.h"
#include "CrypToolApp.h"
#include "SecretSharingLog.h"

#define BREAK	"\n\n"

SecretSharingLog::SecretSharingLog(CString partyLimit_set,
								   CString primeLimit_set,
								   CString secret_set,
								   CString participants_set,
								   CString threshold_set,
								   CString polynom_random,
								   CString prime_random,
								   long *parameter_random,
								   Big *shares_calc,
								   bool *isSelected_set,
								   Big *numerator_calc,
								   Big *denominator_calc,
								   Big result_calc,
								   bool prime_set,
								   bool coeff_set)
{
	this->PartyLimit = partyLimit_set;
	this->PrimeLimit = primeLimit_set;
	this->Secret = secret_set;
	this->Participants = participants_set;
	this->Threshold = threshold_set;
	this->Polynomial = polynom_random;
	this->Prime = prime_random;
	this->Parameter = parameter_random;
	this->Shares = shares_calc;
	this->IsSelected = isSelected_set;
	this->Numerator = numerator_calc;
	this->Denominator = denominator_calc;
	this->Result = result_calc;
	this->LogText = "";
	//je nach Belegung ändert sich der Text 
	this->primeFlag = prime_set; 
	this->coeffFlag = coeff_set; 

	CString tmp;
	
	// add a heading for the log file
	tmp.LoadString(IDS_SECRETSHARINGSHAMIR_LOG_HEADING);
	this->LogText += tmp;
	this->LogText += BREAK;

	// create the log file content...
	tmp.LoadString(IDS_STRING_LOGSS_1);
	this->LogText += tmp;
	this->LogText += BREAK;
	this->LogText += "S: ";
	this->LogText += this->Secret;
	this->LogText += "\n";
	this->LogText += "l = Max(n): ";
	this->LogText += this->PartyLimit;
	this->LogText += "\n";
	this->LogText += "n: ";
	this->LogText += this->Participants;
	this->LogText += "\n";
	this->LogText += "Max(p): ";
	this->LogText += this->PrimeLimit;
	this->LogText += "\n";
	this->LogText += "t: ";
	this->LogText += this->Threshold;
	this->LogText += BREAK;

	if(primeFlag == false)
	{
		tmp.LoadString(IDS_STRING_LOGSS_2A);
	}
	else
	{
		tmp.LoadString(IDS_STRING_LOGSS_2B);
	}
	this->LogText += tmp;
	this->LogText += BREAK;
	this->LogText += "p: ";
	this->LogText += this->Prime;
	this->LogText += BREAK;

	if(coeffFlag == false)
	{
		tmp.LoadString(IDS_STRING_LOGSS_3A);
	}
	else
	{
		tmp.LoadString(IDS_STRING_LOGSS_3B);
	}
	this->LogText += tmp;
	this->LogText += BREAK;
	this->LogText += "f(x): ";
	this->LogText += this->Polynomial;
	this->LogText += BREAK;

	tmp.LoadString(IDS_STRING_LOGSS_4);
	this->LogText += tmp;
	this->LogText += BREAK;
	int n = atoi((char*)Participants.c_str());
	int i;
	for (i = 0; i < n; i++)
	{
		CString a;
		a.Format("%d", i+1);
		this->LogText += a;
		this->LogText += ": ";
		a.Format("%d", Parameter[i]);
		this->LogText += a;
		this->LogText += "\n";
	}
	this->LogText += "\n";

	tmp.LoadString(IDS_STRING_LOGSS_5);
	this->LogText += tmp;
	this->LogText += BREAK;
	for (i = 0; i < n; i++)
	{
		CString a;
		a.Format("%d", i+1);
		this->LogText += a;
		this->LogText += ": ";
		pc_str << this->Shares[i];
		std::string y = pc_str;
		this->LogText += y;
		this->LogText += "\n";
	}
	this->LogText += "\n";

	int s = 0;
	tmp.LoadString(IDS_STRING_LOGSS_6);
	this->LogText += tmp;
	this->LogText += BREAK;
	for (i = 0; i<n; i++)
	{
		if (this->IsSelected[i] == true)
		{
			s++;
			CString a;
			a.Format("%d", i+1);
			this->LogText += a;
			this->LogText += ", ";
		}
	}
	this->LogText += BREAK;

	tmp.LoadString(IDS_STRING_LOGSS_7);
	this->LogText += tmp;
	this->LogText += BREAK;
	for (i = 0; i<n; i++)
	{
		if (this->IsSelected[i] == true)
		{
			CString a;
			a.Format("%d", i+1);
			this->LogText += a;
			this->LogText += ": ";
			a.Format("%d", Parameter[i]);
			this->LogText += a;
			this->LogText += " / ";
			pc_str << this->Shares[i];
			std::string y = pc_str;
			this->LogText += y;
			this->LogText += "\n";
		}
	}
	this->LogText += "\n";

	tmp.Format(IDS_STRING_LOGSS_8, s);
	this->LogText += tmp;
	this->LogText += BREAK;
	CString a;
	BigToCString(Result, a, 10);
	this->LogText += a;
}

std::string SecretSharingLog::GetLogText()
{
	return this->LogText;
}
