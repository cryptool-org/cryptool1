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

	LPTSTR str_a, str_b, str_p, str_G, str_k, str_r;

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
					str_a = new TCHAR[Line.GetLength()+1];
					_tcscpy(str_a, Line);
					
					//AfxMessageBox(&str_a[2],MB_ICONINFORMATION, 0 );

					error += string_to_ln(&str_a[2], ecParam->E->a); 
					// &str_a[2] means ignore the first two characters (i.e. ignore 'a=')
				}
				
				if (Line.Find("b=")>-1){
					str_b = new TCHAR[Line.GetLength()+1];
					_tcscpy(str_b, Line);
					error += string_to_ln(&str_b[2], ecParam->E->b);
					// &str_b[2] means ignore the first two characters (i.e. ignore 'b=')
				}
				if (Line.Find("p=")>-1){
					str_p = new TCHAR[Line.GetLength()+1];
					_tcscpy(str_p, Line);
					error += string_to_ln(&str_p[2], ecParam->E->p);
					// &str_p[2] means ignore the first two characters (i.e. ignore 'p=')
				}
				if (Line.Find("G=")>-1){
					str_G = new TCHAR[Line.GetLength()+1];
					_tcscpy(str_G, Line);
					error += string_to_ln(&str_G[2], G_compressed);
					// &str_G[2] means ignore the first two characters (i.e. ignore 'G=')
				}
				if (Line.Find("k=")>-1){
					str_k = new TCHAR[Line.GetLength()+1];
					_tcscpy(str_k, Line);
					error += string_to_ln(&str_k[2], ecParam->k);
					// &str_k[2] means ignore the first two characters (i.e. ignore 'k=')
				}
				if (Line.Find("r=")>-1){
					str_r = new TCHAR[Line.GetLength()+1];
					_tcscpy(str_r, Line);

					//AfxMessageBox(&str_r[2],MB_ICONINFORMATION, 0 );

					error += string_to_ln(&str_r[2], ecParam->r);
					// &str_r[2]means ignore the first two characters (i.e. ignore 'r=')
				}
			}
		}
	}
	IniDataFile.Close(); // close inputfile

	// sprintf(pc_str, "\n str_a = %s \n",&str_a[2]);
	// AfxMessageBox (pc_str);

	if (error > 0){
		// error: curve E could not been initialized with parameters str_a, str_b, str_p
		Message(IDS_STRING_ERR_EC_FILE_READING,MB_ICONERROR, inputfile);
		return -1; // error
	}
	else ecFp_X9_decompress_point_ac(ecParam->G,ecParam->E,G_compressed);

	return 0;
}
