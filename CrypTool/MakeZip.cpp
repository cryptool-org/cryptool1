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