//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "commdlg.h"
#include "multipad.h"
#include "CryptDoc.h"
#include "fileutil.h"
#include "crypt.h"
#include "dozip.h"
#include "zip\zipup.h"
#include "zip\zunzip.h"
#include "zip\zip.h"
#include "MyDocument.h"

const char MagicZipNumber[4] = "CTZ";

void dozip(const char *infile, const char *OldTitle)
{
	char outfile[128], title[256];
    CMyDocument *NewDoc;
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
		LoadString(AfxGetInstanceHandle(),IDS_STRING41566,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1,pc_str,(LaengeVorher-LaengeNachher)*100/LaengeVorher);
		AfxMessageBox(pc_str1, MB_ICONINFORMATION);
	}
	fclose(fi);
	fclose(fo);

	if(res) {
		remove(outfile);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41522,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(err_txt,pc_str,MB_OK);
		return;
	}

    NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
    remove(outfile);
    if(NewDoc) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING41523,pc_str,STR_LAENGE_STRING_TABLE);
        MakeNewName(title,sizeof(title),pc_str,OldTitle);
        NewDoc->SetTitle(title);
    }
}

void dounzip(const char *infile, const char *OldTitle)
{
	char outfile[128], title[256];
    CMyDocument *NewDoc;
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
			LoadString(AfxGetInstanceHandle(),IDS_STRING41546,pc_str,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING41524,pc_str1,STR_LAENGE_STRING_TABLE);
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
		LoadString(AfxGetInstanceHandle(),IDS_STRING41524,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41522,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK);
		return;
	}

    NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
    remove(outfile);
    if(NewDoc) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING41525,pc_str,STR_LAENGE_STRING_TABLE);
        MakeNewName(title,sizeof(title),pc_str,OldTitle);
        NewDoc->SetTitle(title);
    }
} 