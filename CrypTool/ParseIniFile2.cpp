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
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "CrypToolApp.h"
#include "DialogeMessage.h"
#include "ParseIniFile2.h"

extern char *Pfad; // Pfad contains the path of the directory there the mainprogram is executed
extern char *initializing_file_2; // This string contains the name of the initializing file. (see CrypTool.cpp)
extern char pc_str[STR_LAENGE_STRING_TABLE]; // from CrypTool.cpp
extern char pc_str1[STR_LAENGE_STRING_TABLE]; // from CrypTool.cpp


int CParseIniFile2::GetAlphaList(CStringList& AlphaList)
{
	keyword_prefix1 = "\\begin{";
	keyword_prefix2 = "\\end{";
	keyword_prefix3 = "\\info{";
	keyword_suffix = "}";

	inputfile = (CString) Pfad + initializing_file_2; // this is the full path of the location of initializing_file

	//Message(IDS_STRING_XXX,MB_ICONINFORMATION, inputfile );

	if (!IniDataFile.Open(inputfile, CFile::modeRead)){
		// file opening (read-only mode) error
		Message(IDS_STRING_ERR_TESTS_INIFILE_NOT_FOUND, MB_ICONINFORMATION, inputfile);
		return -1; // error: couldn't open inputfile
	}

	IniDataFile.SeekToBegin(); // Start at beginnig of file
	while (IniDataFile.ReadString(Line)){
		if (Line.Find("\\begin{ALPHA_LIST}") > -1){
			while (IniDataFile.ReadString(Line) && (Line.Find("\\end{ALPHA_LIST}")== -1)){
				AlphaList.AddTail( Line );
				// Message(IDS_STRING_XXX,MB_ICONINFORMATION, Line );
			}
		}
	}
	IniDataFile.Close(); // close inputfile
	return 0;
}

int CParseIniFile2::GetDefaultAlpha(CString& alpha)
{
	keyword_prefix1 = "\\begin{";
	keyword_prefix2 = "\\end{";
	keyword_prefix3 = "\\info{";
	keyword_suffix = "}";

	inputfile = (CString) Pfad + initializing_file_2; // this is the full path of the location of initializing_file

	if (!IniDataFile.Open(inputfile, CFile::modeRead)){
		// file opening (read-only mode) error
		Message(IDS_STRING_ERR_TESTS_INIFILE_NOT_FOUND,MB_ICONSTOP, inputfile);
		return -1; // error: couldn't open inputfile
	}

	IniDataFile.SeekToBegin(); // Start at beginnig of file
	while (IniDataFile.ReadString(Line)){
		if (Line.Find("\\begin{SELECT_DEFAULT_ALPHA}") > -1){
			while (IniDataFile.ReadString(Line) && (Line.Find("\\end{SELECT_DEFAULT_ALPHA}")== -1)){
				// Read from file 'inputfile' the choice for the preselection of the curve id
				alpha = Line;
			}
		}
	}
	IniDataFile.Close(); // close inputfile
	return 0;
}
 

double CParseIniFile2::GetAlphaParam(CString alpha, UINT def_id)
{
	int error=0;

	keyword_prefix1 = "\\begin{";
	keyword_prefix2 = "\\end{";
	keyword_prefix3 = "\\info{";
	keyword_suffix = "}";

	inputfile = (CString) Pfad + initializing_file_2; // this is the full path of the location of initializing_file

	start_block = keyword_prefix1 + alpha + keyword_suffix;
	end_block = keyword_prefix2 + alpha + keyword_suffix;

	if (!IniDataFile.Open(inputfile, CFile::modeRead)){
		// file opening (read-only mode) error
		Message(IDS_STRING_ERR_TESTS_INIFILE_NOT_FOUND,MB_ICONSTOP,inputfile);
		return -1.0; // error: couldn't open inputfile
	}
	IniDataFile.SeekToBegin(); // Start searching at begining of file
	while (IniDataFile.ReadString(Line)){
		if (Line.Find(start_block) > -1){
			for (UINT i=0; i <= (def_id+1);i++)
			{
				if ((IniDataFile.ReadString(Line)) && (Line.Find(end_block)== -1) && (def_id==i))
				{
					LPTSTR lpsz = new TCHAR[Line.GetLength()+1];
					_tcscpy(lpsz, Line);
					return strtod(lpsz, NULL);
				}
			}
		}
	}

	IniDataFile.Close(); // close inputfile

	return 0;
}
