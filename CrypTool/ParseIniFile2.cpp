/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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
