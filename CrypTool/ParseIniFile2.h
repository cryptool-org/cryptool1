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

//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Modifiziert von Matej Matejicek 2001
// Nur für die Cryptool Datei "TEST-Param.ini"
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////

#include <afxtempl.h>

class CParseIniFile2 : public CStdioFile
{

public:
	typedef CList <CString,CString&> CStringList; // A List which will contain CString entries

private:
	CString keyword_prefix1;
	CString keyword_prefix2;
	CString keyword_prefix3;
	CString keyword_suffix;
	CString keyword;
	CString start_block;
	CString end_block;
	CString Line;
	CString inputfile;

	CStdioFile IniDataFile; //"TEST-Param.ini" Datei

public:
	// Methoden
	int GetAlphaList(CStringList& AlphaList);			//Alpha-Liste
	int GetDefaultAlpha(CString& curveID);				//Default-Alpha
	double GetAlphaParam(CString alpha, UINT def_id);	//Parameter von Alpha, def_id ist 
														//die Freiheitsgrad v
};
