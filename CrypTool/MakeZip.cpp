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
#include "stdafx.h"
#include "commdlg.h"
#include "CrypToolApp.h"
#include "CryptDoc.h"
#include "FileTools.h"
#include "Cryptography.h"
#include "MakeZip.h"
#include "zip\zipup.h"
#include "zip\zunzip.h"
#include "zip\zip.h"
#include "AppDocument.h"

const char MagicZipNumber[4] = "CTZ";

void dozip(const char *infile, const char *OldTitle)
{
	char outfile[CRYPTOOL_PATH_LENGTH], title[256];
    CAppDocument *NewDoc;
	FILE *fi, *fo;
	int res;

    GetTmpName(outfile,"cry",".hex");

	fi = fopen(infile,"rb");
	fo = fopen(outfile,"wb");
	fwrite( MagicZipNumber, sizeof(char), 3, fo ); 
	try{
		res = zipup(fi,fo);
	}
	catch(...)
	{
		res=1;
	}
	// Laengen der Dateien bestimmen und so den Komprimierungsgrad ermitteln.
	// Komprimierungsgrad wie bei WinZip angeben: um ..% komprimiert
	long LaengeVorher,
		 LaengeNachher;
	fseek(fi, 0, SEEK_END);
	LaengeVorher = ftell(fi);
	fseek(fo, 0, SEEK_END);
	LaengeNachher = ftell(fo);
	if (LaengeVorher > 0)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KOMPRESSION_FACTOR,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1,pc_str,(LaengeVorher-LaengeNachher)*100/LaengeVorher);
		AfxMessageBox(pc_str1, MB_ICONINFORMATION);
	}
	fclose(fi);
	fclose(fo);

	if(res) {
		remove(outfile);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ZIP,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(err_txt,pc_str,MB_OK);
		return;
	}

    NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
    remove(outfile);
    if(NewDoc) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_ZIP_COMPRESSION_OF,pc_str,STR_LAENGE_STRING_TABLE);
        MakeNewName(title,sizeof(title),pc_str,OldTitle);
        NewDoc->SetTitle(title);
    }
}

void dounzip(const char *infile, const char *OldTitle)
{
	char outfile[CRYPTOOL_PATH_LENGTH], title[256];
    CAppDocument *NewDoc;
	FILE *fi, *fo;
	int res;

    GetTmpName(outfile,"cry",".tmp");

	fi = fopen(infile,"rb");
	{	// Henrik Koy 21. Nov 2000
		// Magic Number Test
		char _MNumber[8];
		int numread = fread(_MNumber, sizeof(char), 3, fi);
		if ( numread < 3 || strncmp( _MNumber, MagicZipNumber, 3) )
		{
			remove(outfile);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_NO_ZIP_FILE,pc_str,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ZIP_FILE,pc_str1,STR_LAENGE_STRING_TABLE);
			theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONEXCLAMATION);
			fclose(fi);
			return;
		}
	}


	fo = fopen(outfile,"wb");
	try{
		res = unzip(fi,fo);
	}
	catch(...)
	{
		res=1;
	}
	fclose(fi);
	fclose(fo);

	if(res) {
		remove(outfile);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ZIP_FILE,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ZIP,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK);
		return;
	}

    NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
    remove(outfile);
    if(NewDoc) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_ZIP_DECOMPRESSION_OF,pc_str,STR_LAENGE_STRING_TABLE);
        MakeNewName(title,sizeof(title),pc_str,OldTitle);
        NewDoc->SetTitle(title);
    }
} 