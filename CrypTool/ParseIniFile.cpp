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
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "CrypToolApp.h"

#include "ParseIniFile.h"
#include "DialogeMessage.h"
#include "s_ecconv.h"
#include "arithmet.h"

extern char *Pfad; // Pfad contains the path of the directory there the mainprogram is executed
extern char *initializing_file; // This string contains the name of the initializing file. (see CrypTool.cpp)
extern char pc_str[STR_LAENGE_STRING_TABLE]; // from CrypTool.cpp
extern char pc_str1[STR_LAENGE_STRING_TABLE]; // from CrypTool.cpp


int CParseIniFile::GetEcIDList(CStringList& ecIDlist)
{
	keyword_prefix1 = "\\begin{";
	keyword_prefix2 = "\\end{";
	keyword_prefix3 = "\\info{";
	keyword_suffix = "}";

	inputfile = (CString) Pfad + initializing_file; // this is the full path of the location of initializing_file

	//Message(IDS_STRING_XXX,MB_ICONINFORMATION, inputfile);

	if (!IniDataFile.Open(inputfile, CFile::modeRead)){
		// file opening (read-only mode) error
		Message(IDS_STRING_ERR_EC_FILE_NOT_FOUND, MB_ICONINFORMATION, inputfile);
		return -1; // error: couldn't open inputfile
	}

	IniDataFile.SeekToBegin(); // Start at beginnig of file
	while (IniDataFile.ReadString(Line)){
		if (Line.Find("\\begin{CURVE_ID_LIST}") > -1){
			while (IniDataFile.ReadString(Line) && (Line.Find("\\end{CURVE_ID_LIST}")== -1)){
				ecIDlist.AddTail( Line );
				//Message(IDS_STRING_XXX,MB_ICONINFORMATION, Line );
			}
		}
	}
	IniDataFile.Close(); // close inputfile
	return 0;
}

int CParseIniFile::GetPreSelEcID(CString& curveID)
{
	keyword_prefix1 = "\\begin{";
	keyword_prefix2 = "\\end{";
	keyword_prefix3 = "\\info{";
	keyword_suffix = "}";

	inputfile = (CString) Pfad + initializing_file; // this is the full path of the location of initializing_file

	if (!IniDataFile.Open(inputfile, CFile::modeRead)){
		// file opening (read-only mode) error
		Message(IDS_STRING_ERR_EC_FILE_NOT_FOUND, MB_ICONSTOP, inputfile);
		return -1; // error: couldn't open inputfile
	}

	IniDataFile.SeekToBegin(); // Start at beginnig of file
	while (IniDataFile.ReadString(Line)){
		if (Line.Find("\\begin{SELECT_DEFAULT_CURVE_ID}") > -1){
			while (IniDataFile.ReadString(Line) && (Line.Find("\\end{SELECT_DEFAULT_CURVE_ID}")== -1)){
				// Read from file 'inputfile' the choice for the preselection of the curve id
				curveID = Line;
			}
		}
	}
	IniDataFile.Close(); // close inputfile
	return 0;
}
 

int CParseIniFile::GetEcDomParam(CString curveID, EcDomParam_ac_ptr ecParam)
{
	int error=0;

	keyword_prefix1 = "\\begin{";
	keyword_prefix2 = "\\end{";
	keyword_prefix3 = "\\info{";
	keyword_suffix = "}";

	inputfile = (CString) Pfad + initializing_file; // this is the full path of the location of initializing_file

	L_NUMBER G_compressed[MAXLGTH];

	start_block = keyword_prefix1 + curveID + keyword_suffix;
	end_block = keyword_prefix2 + curveID + keyword_suffix;

	if (!IniDataFile.Open(inputfile, CFile::modeRead)){
		// file opening (read-only mode) error
		Message(IDS_STRING_ERR_EC_FILE_NOT_FOUND, MB_ICONSTOP, inputfile);
		return -1; // error: couldn't open inputfile
	}
	IniDataFile.SeekToBegin(); // Start searching at beginnig of file
	while (IniDataFile.ReadString(Line)){
		if (Line.Find(start_block) > -1){
			while (IniDataFile.ReadString(Line) && (Line.Find(end_block)== -1)){
				/* So wandelt man CString Objekte in char* Strings um:
					CString theString( "This is a test" );
					LPTSTR lpsz = new TCHAR[theString.GetLength()+1];
					_tcscpy(lpsz, theString);
					//... ändern Sie lpsz nach Belieben
				*/
				if (Line.Find("a=")>-1){
					error += string_to_ln(((LPCTSTR)Line) + 2, ecParam->E->a); 
				}
				
				if (Line.Find("b=")>-1){
					error += string_to_ln(((LPCTSTR)Line) + 2, ecParam->E->b);
				}
				if (Line.Find("p=")>-1){
					error += string_to_ln(((LPCTSTR)Line) + 2, ecParam->E->p);
				}
				if (Line.Find("G=")>-1){
					error += string_to_ln(((LPCTSTR)Line) + 2, G_compressed);
				}
				if (Line.Find("k=")>-1){
					error += string_to_ln(((LPCTSTR)Line) + 2, ecParam->k);
				}
				if (Line.Find("r=")>-1){
					error += string_to_ln(((LPCTSTR)Line) + 2, ecParam->r);
				}
			}
		}
	}
	IniDataFile.Close(); // close inputfile

	if (error > 0){
		// error: curve E could not been initialized with parameters 
		Message(IDS_STRING_ERR_EC_FILE_READING,MB_ICONERROR, inputfile);
		return -1; // error
	}
	else ecFp_X9_decompress_point_ac(ecParam->G,ecParam->E,G_compressed);

	return 0;
}
