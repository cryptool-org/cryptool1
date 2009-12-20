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

// TextAnalyse.h: Schnittstelle für die Klasse TextAnalyse.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTANALYSE_H__83C7F3B3_0C82_11D5_8102_000629C93170__INCLUDED_)
#define AFX_TEXTANALYSE_H__83C7F3B3_0C82_11D5_8102_000629C93170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define range		256
#define buffsize	4096
#define HOM_ENC_BIN 1
#define HOM_ENC_TXT 0

class CKeyParameterHomophone  
{
public:
	bool Analyse(int _keyType = HOM_ENC_TXT);
	bool Analyse( const char * f_toAnalyse, int _keyType = HOM_ENC_TXT );
	double freq[range];
	long count[range];
	CKeyParameterHomophone();
	virtual ~CKeyParameterHomophone();

private:
	int  keyType;
	bool Checksum();
	void Correct_count_table();
	void Make_freq_table();
	long total_count;
	void Init(int _keyType);
};

#endif // !defined(AFX_TEXTANALYSE_H__83C7F3B3_0C82_11D5_8102_000629C93170__INCLUDED_)
