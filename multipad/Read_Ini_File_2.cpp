//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000 
// Modifiziert von Matej Matejicek 2001
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "multipad.h"
#include "crypt.h"
#include "Read_Ini_File_2.h"

extern char *Pfad; // Pfad contains the path of the directory there the mainprogram is executed
extern char *initializing_file_2; // This string contains the name of the initializing file. (see multipad.cpp)
extern char pc_str[STR_LAENGE_STRING_TABLE]; // from multipad.cpp
extern char pc_str1[STR_LAENGE_STRING_TABLE]; // from multipad.cpp


int CReadIniFile2::GetAlphaList(CStringList& AlphaList)
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

int CReadIniFile2::GetDefaultAlpha(CString& alpha)
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
 

double CReadIniFile2::GetAlphaParam(CString alpha, UINT def_id)
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
