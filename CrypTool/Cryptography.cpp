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
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "commdlg.h"
#include "CrypToolApp.h"
#include "CryptDoc.h"
#include "DlgKey.h"
#include "DlgShowKey.h"
#include "DlgKeyHex.h"
#include "Cryptography.h"
#include "DlgKeyHill5x5.h"
#include "DlgKeyHill10x10.h"
#include "HillEncryption.h"
#include "DlgShowProgress.h"
#include "DlgKeySubstitution.h"
// #include "secure.h"
#include "DlgOptionsSubstitutionAnalysis.h"
#include "DlgManualSubstAnalysis.h"
#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif
#include <stdio.h>
#include "ChrTools.h"
#include "AppDocument.h"
#include "PlayfairAnalysis.h"
#include "DlgKeyPlayfair.h"
#include "DlgPlayfairAnalysis.h"
#include "RandomAnalysisTools.h"
#include "DlgKeyHomophone.h"
#include "DlgNGramAnalysis.h"
#include "DlgRandomGenerator.h"
#include "DlgPeriodicityAnalysis.h"
#include "DlgKeyPermutation.h"
#include "DlgKeyPermutationInfo.h"
#include "DlgSelectHashFunction.h"
#include "SecudeCryptography.h"
#include "DlgHashDemo.h"
#include "DlgSignatureDemo.h"
#include "DlgEntropyInfo.h"
#include "Mac.h"
// #include "DlgMac.h"
#include "DlgHMAC.h"
#include "DlgMonSubst.h"

#include "DialogeMessage.h"
#include "MakeNewName.h"
#include "CrypToolTools.h"

#include "ScintillaDoc.h"
#include "ScintillaView.h"
#include "DlgKeyHexFixedLen.h"
#include "DlgBruteForceAES.h" 
#include "ListResults.h"
#include "bruteforceheap.h"

#include <fstream>

#define MAX_LAENGE_STRTEXT 16000

char *Eingabedatei;
int *MaxPermu[26];
float Fortschritt=20.0;

#pragma warning(disable : 4996)


#if 0
///////////////////////////////////////////////////////////////////////
// FIXME


int symEncProviderSecude::onErrCleanUp()
{
	int decryptionError = 0;
	struct ErrStack *err;
	err = theApp.SecudeLib.th_remove_last_error();
	if ( err->e_number == 1792 ) decryptionError = 0;
	else                         decryptionError = err->e_number;
	if(err->e_text) theApp.SecudeLib.aux_free(err->e_text);
	if(err->e_proc) theApp.SecudeLib.aux_free(err->e_proc);
	if(err->e_addr)
	{
		switch (err->e_addrtype)
		{
		case int_n:
			break;
		case OctetString_n:
			theApp.SecudeLib.aux_free_OctetString((OctetString **) &(err->e_addr));
			break;
		case BitString_n:
			theApp.SecudeLib.aux_free_BitString((BitString **) &(err->e_addr));
			break;
		case AlgId_n:
			//					theApp.SecudeLib.aux_free_AlgId((AlgId **) &(err->e_addr));
			break;
		case KeyInfo_n:
			theApp.SecudeLib.aux_free_KeyInfo((KeyInfo **) &(err->e_addr));
			break;
		case ObjId_n:
			theApp.SecudeLib.aux_free_ObjId((ObjId **) &(err->e_addr));
			break;
		case KeyBits_n:
			theApp.SecudeLib.aux_free_KeyBits((KeyBits **) &(err->e_addr));
			break;
		case PSEToc_n:
			theApp.SecudeLib.aux_free_PSEToc((PSEToc **) &(err->e_addr));
			break;
		}
	}
	theApp.SecudeLib.aux_free(err);
	return decryptionError;
}



int	symEncProviderSecude::set_key(const char *key, int keylength)
{

	return 0;
}

int	symEncProviderSecude::encrypt()
{
	// ASSERT()
	if (theApp.SecudeLib.sec_encrypt_all (&in, &out, &keyinfo)==-1)
		return onErrCleanUp()
	else
		return 0;
}

int	symEncProviderSecude::decrypt()
{
	// ASSERT()
	if (theApp.SecudeLib.sec_decrypt_all (&in, &out, &keyinfo)==-1)
		return onErrCleanUp()
	else
		return 0;
}

symEncProviderCrypTool::symEncProviderCrypTool()
{


}



#endif

//////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void solve (int Tiefe, int DMax, int *Permu[26], int Perm[], int score, char *PatSet[100][50], char *Cipher[100][100], int *MaxScore, int *MaxPermu[26], float Delta);
int SucheLeer (int Start, int Laenge, SymbolArray& text);
bool match (char *current, char *common);

/* local functions */
void FreePar(CryptPar *par)
{
	if(!(par->flags & CRYPT_FREE_MEM)) return;

	if(par->infile) free((void *) par->infile);
	if(par->OldTitle) free((void *) par->OldTitle);
	if(par->key) free(par->key);
}

void SetDialogTitle( CDlgKey &Dialog, int IDS_STRING_ID )
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
	Dialog.SetAlternativeWindowText(pc_str);
}

void SetDialogTitle( CDlgKeyHex &Dialog, int IDS_STRING_ID )
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
	Dialog.SetAlternativeWindowText(pc_str);
}

// ========================================================================
/*MKraft: hier Kaskaden-bool übergeben*/
void CaesarAsc(const char *infile, const char *OldTitle)
{
    char outfile[1024];
    CDlgKey KeyDialog(-1);
	SymbolArray text(AppConv);

// == load INPUT
	if ( !CheckAlphabet() ) return;
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) return;
	SetDialogTitle( KeyDialog, IDS_STRING_KEY_INPUT_CAESAR );

// == KeyDialog
	if(KeyDialog.Display()!=IDOK) return;
	SymbolArray Key(AppConv);
	Key.ReadString(KeyDialog.GetData());
	Key += 1;

/* MKraft
*	hier Kaskaden-bool abfragen */
// == Encryption / Decryption
	SHOW_HOUR_GLASS
	GetTmpName(outfile,"cry",".txt");
	if(KeyDialog.m_Decrypt)
		text -= Key;
	else
		text += Key;
	text.Write(outfile);
	Reformat(infile, outfile, FALSE);

// == Open the new document
	OpenNewDoc( outfile, KeyDialog.GetData(), OldTitle, IDS_STRING_CAESAR, KeyDialog.m_Decrypt );

	HIDE_HOUR_GLASS
}

void VigenereAsc(const char *infile, const char *OldTitle)
{
    char outfile[1024];
    CDlgKey KeyDialog(MAX_VIGENERE);
	SymbolArray text(AppConv);

// == load INPUT
	if ( !CheckAlphabet() ) return;
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) return;
	SetDialogTitle( KeyDialog, IDS_STRING_KEY_INPUT_VIGENERE );

// == KeyDialog
	if(KeyDialog.Display()!=IDOK) return;

// == Encryption / Decryption
	SHOW_HOUR_GLASS
	GetTmpName(outfile,"cry",".txt");
	SymbolArray Key(AppConv);
	Key.ReadString(KeyDialog.GetData());
	if(KeyDialog.m_Decrypt)
		text -= Key;
	else
		text += Key;
	text.Write(outfile);
	Reformat(infile, outfile, FALSE);
	
// == Open the new document
	OpenNewDoc( outfile, KeyDialog.GetData(), OldTitle, IDS_STRING_VIGENERE, KeyDialog.m_Decrypt );

	HIDE_HOUR_GLASS
}

void XorBin(const char *infile, const char *OldTitle)
{
    char outfile[1024], *buffer;
    CDlgKeyHex KeyDialog(MAX_VIGENERE);
	SymbolArray text(IdConv);
	
// == load INPUT
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) return;
	SetDialogTitle( KeyDialog, IDS_STRING_KEY_INPUT_XOR );

// == KeyDialog
	if(KeyDialog.Display()!=IDOK) return;

// == Encryption / Decryption
	SHOW_HOUR_GLASS
    GetTmpName(outfile,"cry",".tmp");
	SymbolArray Key(IdConv,KeyDialog.GetLen());
	buffer = KeyDialog.GetData();
	for(int i=KeyDialog.GetLen()-1;i>=0;i--) Key[i]=buffer[i];
    text ^= Key;
    text.Write(outfile);

// == Open the new document
	OpenNewDoc( outfile, KeyDialog.m_einstr, OldTitle, IDS_STRING_XOR, KeyDialog.m_Decrypt );

	HIDE_HOUR_GLASS
}

void AddBin(const char *infile, const char *OldTitle)
{
    char outfile[1024], *buffer;
    CDlgKeyHex KeyDialog(MAX_VIGENERE);
	SymbolArray text(IdConv);
	
// == load INPUT
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) return;
	SetDialogTitle( KeyDialog, IDS_STRING_KEY_INPUT_ADD );

// == KeyDialog
	if(KeyDialog.Display()!=IDOK) return;

// == Encryption / Decryption
	SHOW_HOUR_GLASS
    GetTmpName(outfile,"cry",".tmp");
	SymbolArray Key(IdConv,KeyDialog.GetLen());
	buffer = KeyDialog.GetData();
	for(int i=KeyDialog.GetLen()-1;i>=0;i--) Key[i]=buffer[i];
    if(KeyDialog.m_Decrypt)
        text -= Key;
    else
        text += Key;
    text.Write(outfile);

// == Open the new document
	OpenNewDoc( outfile, KeyDialog.m_einstr, OldTitle, IDS_STRING_ADD, KeyDialog.m_Decrypt );

	HIDE_HOUR_GLASS
}

void VernamBin(const char *infile, const char *OldTitle)
{
	char fname[1024], line[1024], ftitle[1024];
    char outfile[1024], title[1024];
    CAppDocument *NewDoc;
	SymbolArray text(IdConv);

// == load INPUT
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) return;
	
// == load KEY
	{
		// Initialisierung des File-Dialogs:
		CString sFileFilter;
		CString sDefName("*.txt");
		CString sTitle;
		DWORD   dwFlags(OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST);
		sFileFilter.LoadString(IDS_OPEN_DOCUMENT_FILTER);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_VERNAM_KEYFILE,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy(title, OldTitle);
		if ( strlen(title) > 32 )
		{
			strcpy(title+29, "...");
		}
		sprintf(line, pc_str, title);
		sTitle = line;
		// sTitle.LoadString(IDS_STRING_VERNAM_KEYFILE);
		CFileDialog* doc;
		doc = new CFileDialog(TRUE, NULL, sDefName, dwFlags, sFileFilter);
		doc->m_ofn.lpstrTitle = sTitle;

		if(doc->DoModal()==IDOK)// Aufruf des File-Dialogs
		{			
			strcpy(ftitle, LPCTSTR (doc->GetFileName()));
			strcpy(fname, LPCTSTR (doc->GetPathName()));
			delete doc;
		}
		else
		{
			delete doc;
			return;
		}
	}

// == Encryption / Decryption
	SHOW_HOUR_GLASS
    GetTmpName(outfile,"cry",".tmp");
	SymbolArray Key(IdConv);
	Key.Read( fname );
	/* if the key size is zero, notify the user and DON'T ENCRYPT/DECRYPT anything */
	if(Key.GetSize() == 0) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_INVALID_VERNAM_KEY,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str, MB_ICONINFORMATION);
	}
	/* else: encrypt/decrypt */
	else {
		int a = Key.GetSize();
		int b = text.GetSize();

		if(Key.GetSize() < text.GetSize()) {
			/* notify the user if the key is shorter than the text that is to be encrypted */
			LoadString(AfxGetInstanceHandle(),IDS_STRING_SHORT_VERNAM_KEY,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str, MB_ICONINFORMATION);
		}
		/* do the actual encryption */
		text ^= Key;
	}
	text.Write(outfile);

// == Open the new document
	CString csKey = "Datei ";
	csKey += fname;
    NewDoc = theApp.OpenDocumentFileNoMRU(outfile,csKey);
    remove(outfile);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_VERNAM_ENCRYPTION_OF,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line,pc_str,ftitle);
    if(NewDoc) {
        MakeNewName(title,sizeof(title),line,OldTitle);
        NewDoc->SetTitle(title);
    }
	HIDE_HOUR_GLASS
}


void PlayfairBin(const char *infile, const char *OldTitle)
{
 	char outfile[128],preform[128],title[128];
    CAppDocument *NewDoc;

	// Überprüfen, ob die Eingabedatei mindestens zwei gültige Zeichen enthält,
	// d.h. Zeichen, die im entsprechenden Alphabet vorkommen.
	FILE *stream;
	long infile_zeichen_anz = 0;
	int ch;
	char c;

	// Das Lesen der Datei wurde wegen Geschwindigkeitsvorteilen nachträglich nicht
	// mehr durch MFC implementiert. Um durch die Codeänderung keinen Absturz zu verursachen,
	// wird die Prüfung _NUR_ bei erfolgreicher Dateiöffnung durchgeführt.
	if( (stream = fopen(infile, "rb" )) )
	{
		ch = fgetc(stream);	
		
		// Bis zum Erreichen des Dateiendes (EOF) wird die gesamte Datei durchsucht
		// und jedes Zeichen einzeln auf Gültigkeit überprüft.
		int i;
		for(i=0; feof( stream ) == 0; i++ )
		{
			c = (char)ch;

			if( ( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')  ) )
			{
				infile_zeichen_anz++;
				
				// An dieser Stelle ist das Gültigkeitskriterium erreicht,
				// die for-Schleife wird demnach abgebrochen.
				if ( infile_zeichen_anz >= 2 ) break;
			}

			ch = fgetc( stream );
		
		}
	
		fclose( stream );
	
	}
	
	if (infile_zeichen_anz < 2)
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 2);
		return;
	}
	
	int n=strlen(infile);
	if ( strncmp(OldTitle+n-4,".txt",4) && theApp.TextOptions.getKeepCharactersNotPresentInAlphabetUnchanged() )
		GetTmpName(outfile,"cry",".txt");
	else
		GetTmpName(outfile,"cry",".txt");

	class CDlgKeyPlayfair KeyDialog(infile,outfile,theApp.TextOptions.getKeepCharactersNotPresentInAlphabetUnchanged(),theApp.TextOptions.getKeepUpperLowerCaseInformation());

	if(KeyDialog.Display()!=IDOK) return;

	if (KeyDialog.m_preformat&&!KeyDialog.getDec())
	{
		GetTmpName(outfile,"cry",".txt");
		GetTmpName(preform,"cry",".txt");
		KeyDialog.m_Alg->ApplyPlayfairPreformat(KeyDialog.getDec(),preform,outfile);
		char tmpStr[128];

		int i;
		for (i=0; i<KeyDialog.m_text.GetLength(); i++ )
			tmpStr[i] = KeyDialog.m_text.GetAt(i);
		tmpStr[i]=0;
		NewDoc = theApp.OpenDocumentFileNoMRU(preform, tmpStr /* KeyDialog.GetData()*/ );
		remove(preform);
		if(NewDoc)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PLAYFAIR_PREFORMAT,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName(title,sizeof(title),pc_str,OldTitle);
			NewDoc->SetTitle(title);
			NewDoc->SetData(2);
		}

		NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.GetData());
		remove(outfile);
		if(NewDoc)
		{
			if(KeyDialog.getDec())
				LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			else
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_PLAYFAIR,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,KeyDialog.GetData());
			NewDoc->SetTitle(title);
			NewDoc->SetData(2);
	    }
	}
	else
	{
		KeyDialog.m_Alg->ApplyPlayfairToInput(KeyDialog.getDec());
		OpenNewDoc( outfile, KeyDialog.GetData(), OldTitle, IDS_PLAYFAIR, KeyDialog.getDec() );
	}
	HIDE_HOUR_GLASS
}

void PlayfairAnalyse(const char *infile, const char *OldTitle)
{
	char outfile[128];
	GetTmpName(outfile,"cry",".tmp");
	class CDlgPlayfairAnalysis KeyDialog(infile,outfile,theApp.TextOptions.getKeepCharactersNotPresentInAlphabetUnchanged(),theApp.TextOptions.getKeepUpperLowerCaseInformation());

	if(KeyDialog.Display()!=IDOK) return;

	KeyDialog.getAlg()->ApplyPlayfairToInput(KeyDialog.getDec());
	OpenNewDoc( outfile, KeyDialog.GetData(), OldTitle, IDS_PLAYFAIR, KeyDialog.getDec() );
	HIDE_HOUR_GLASS
}


void Hill(const char *infile, const char *OldTitle)
{
	// Es muss mindestens ein Zeichen im Alphabet zu verschlüsseln sein
	if ( !CheckAlphabet( 2 ) ) return;

	// Die Hillklasse wird zur Ueberpruefung der erlaubten Zeichen benoetigt
	CHillEncryption *hillklasse;
	hillklasse = new CHillEncryption(theApp.TextOptions.getAlphabet().GetBuffer(0));

    char outfile[128];

	// Überprüfung, ob Eingabedatei mindestens ein Zeichen enthält. 
	CFile datei(infile, CFile::modeRead);

	sNotInFileChars = ""; //clear because of not wrong counting past userinput

	iClearTextAlphCharCount = 0;
	iClearTextNotAlphCharCount = 0;

	long infile_zeichen_anz = 0;
	char c;
	while(datei.Read(&c,1))
	{
		// Falls Gross-/Kleinschreibung ignoriert werden soll,
		// muessen auch die Kleinbuchstaben mitgezaehlt werden.
		if ( hillklasse->ist_erlaubtes_zeichen(c) ||
			 ( (theApp.TextOptions.getIgnoreCase()) && (MyIsLower(c)) && 
			   (hillklasse->ist_erlaubtes_zeichen(MyToUpper(c))) ) )
		{
			infile_zeichen_anz++;
		}
		else
		{
			iClearTextNotAlphCharCount++;

			if(sNotInFileChars.GetLength() < 3) //to show only first 3 chars in hill details
				sNotInFileChars += (CString)c; //if not exists in alph

		}
		iClearTextAlphCharCount++;
	}
	datei.Close();


	if (! infile_zeichen_anz)
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		return;
	}

	// Fenster am Bildschirm anzeigen, falls abgebrochen, nichts mehr machen.

	bool bRcWeiter = false; // true, wenn der Dialog nicht mit Klick zum Wechsel
							// in Fenster mit groesseren bzw. kleineren Schluesseln
							// beendet worden ist. 
							// false, wenn mit OK oder Abbrechen beendet
	int iLocalRc;

    CDlgKeyHill5x5* hillein = NULL;
    CDlgKeyHill10x10* hilleingross = NULL;

	delete hillklasse;
	hillklasse = NULL;

	// Fenter jetzt anzeigen 
	// Es kann beliebig oft vom Fenster mit Schluesseln bis Dimension 5 x 5 zum 
	// Fenster mit Schluesseln mit Dimension bis 10 x 10 gewechselt werden.
	// Ein Wechsel der Dimension wird an der Variablen iHillSchluesselFensterGroesse
	// erkannt. Wenn sie nicht mehr den gleichen Wert wie vor dem Anzeigen des
	// Fensters hat, so muss das entsprechende andere Fenster angezeigt werden.
	// Die Klassen fuer die Dialoge und die Klasse fuer das Hill-Verfahren
	// werden immer neu angelegt und nach Benutzung wirde freigegeben. 
	// Wenn ok betaetigt worden ist, werden die Klassen noch gebraucht und 
	// erst am Ende der Funktion freigegeben.

	// Falls beim letzten Aufruf das Fenster für grosse Schluessel angezeigt worden ist,
	// dort aber ein kleiner Schluessel (<= 5 x 5) eingegeben worden ist,
	// dann oeffnen wir wieder das Fenster fuer kleine Schluessel
	if (iHillSchluesselDim <= HILL_MAX_DIM)
	{
		iHillSchluesselFensterGroesse = HILL_SCHLUESSEL_KLEIN;
	}

	while (! bRcWeiter)
	{
		ASSERT ( (iHillSchluesselFensterGroesse == HILL_SCHLUESSEL_KLEIN) ||
				 (iHillSchluesselFensterGroesse == HILL_SCHLUESSEL_GROSS) );

		if (iHillSchluesselFensterGroesse == HILL_SCHLUESSEL_KLEIN)
		{
			hillein = new CDlgKeyHill5x5();
			hillklasse = hillein->getHillKlasse();
			iLocalRc = hillein->Display();

			// Falls nicht auf "Groessere Schluessel" geklickt wurde
			if (iHillSchluesselFensterGroesse == HILL_SCHLUESSEL_KLEIN)
			{
				bRcWeiter = true;
			}
			else
			{
				// Die Maske Groessere Schluessel muss geoeffnet werden
				delete hillein;
				hillein = NULL;
				hillklasse = NULL;
			}
		}
		else // iHillSchluesselFensterGroesse = HILL_SCHLUESSEL_GROSS
		{
			hilleingross = new CDlgKeyHill10x10();
			hillklasse = hilleingross->getHillKlasse();
			iLocalRc = hilleingross->Display();

			// Falls nicht auf "Kleinere Schluessel" geklickt wurde
			if (iHillSchluesselFensterGroesse == HILL_SCHLUESSEL_GROSS)
			{
				bRcWeiter = true;
			}
			else
			{
				// Die Maske Kleinere Schluessel muss geoeffnet werden
				delete hilleingross;
				hilleingross = NULL;
				hillklasse = NULL;
			}
		}
	}

	// Wurde der Dialog abgebrochen -> Vor der Rueckkehr speicher freigeben
	if(iLocalRc != IDOK)
	{
		if (iHillSchluesselFensterGroesse == HILL_SCHLUESSEL_GROSS)
		{
			ASSERT (hilleingross != NULL);
			delete hilleingross;
		}
		else
		{
			ASSERT (hillein != NULL);
			delete hillein;
		}

		return;
	}

	SHOW_HOUR_GLASS

	// Falls nicht abgebrochen, ist eine invertierbare Matrix 
	// als Schluessel eingegeben worden -> Verschluesseln bzw. Entschluesseln


	// Mit der Aenderung, dass es moeglich ist, das Format bei den klassischen 
	// Verfahren beizubehalten (siehe Funktionen Reformat bzw. ForceReformat), 
	// ergab sich das Problem, dass beim Hill-Verfahren eventuell am Ende mit dem 
	// Fuellzeichen aufgefuellt werden muss, damit die Laenge des Textes durch die
	// Dimension des Schluessels ohne Rest teilbar ist. Dieses wurde aber in der 
	// Funktion Force Reformat nicht beruecksichtigt, so dass der letzte Block - 
	// falls aufgefuellt wurde - nicht korrekt entschluesselt wird und der Angriff
	// auch nicht funktioniert. 
	// Daher wurde die Eingabedatei mit dem Fuellzeichen zu einem Vielfachen der 
	// Dimension der Schluesselmatrix aufgefuellt.
	// BEGINN der Aenderung 
	FILE *fp;
	long i;
	int iAnz = 0, iNeueX = 0, iDateiLaenge;
	char *csEingabeDatei;

	// Dateilaenge ermitteln und Dateiinhalt in Feld einlesen
	fp = fopen(infile,"r+b");

	fseek(fp, 0, SEEK_END);
	iDateiLaenge = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	csEingabeDatei = (char *) malloc(iDateiLaenge+1);
	fread(csEingabeDatei, 1, iDateiLaenge, fp);

	// Falls Gross-/Kleinschreibung ignoriert werden soll:
	// Es werden alle Kleinbuchstaben in Grossbuchstaben umgewandelt
	if(theApp.TextOptions.getIgnoreCase())
	{
		MyToUpper(csEingabeDatei);
	}

	// Die Anzahl der erlaubten Zeichen in der Eingabe zaehlen:
	for (i=0; i<iDateiLaenge; i++)
	{
		// Kleinbuchstaben wurden schon zu Grossbuchstaben konvertiert, sofern erforderlich;
		// deshalb muss dies hier nicht mehr beruecksichtigt werden.
		if ( hillklasse->ist_erlaubtes_zeichen(csEingabeDatei[i]) )
		{
			iAnz++;
		}
	}

	free(csEingabeDatei);

	// Anzahl der aufzufuellenden Zeichen berechnen und sofern ein Auffuellen erforderlich ist,
	// die entsprechende Anzahl (iNeueX) Zeichen ans Dateiende schreiben.

	int iDimension;

	if (iHillSchluesselFensterGroesse == HILL_SCHLUESSEL_GROSS)
	{
		iDimension = hilleingross->dim;
	}
	else
	{
		iDimension = hillein->dim;
	}

	if ((iAnz % iDimension) != 0)
	{
		// iNeueX = kleinste Anzahl der aufzufuellenden Zeichen, damit die Laenge der Daten
		//         ein Vielfaches der Schluesseldimension ist.
		// Aenderung:
		// Es wird nicht mit 'X' aufgefuellt, sondern mit dem ASCII-maessig kleinsten 
		// Zeichen in den zu beruecksichtigenden Zeichen.
		iNeueX = (iDimension-(iAnz%iDimension));
	
		csEingabeDatei = (char *) malloc(iNeueX);
		for (i=0; i<iNeueX; i++)
		{
			csEingabeDatei[i] = hillklasse->get_fuellzeichen();
		}

		fseek(fp, 0, SEEK_END);
		fwrite(csEingabeDatei, 1, iNeueX, fp);
		
		free(csEingabeDatei);
	}
	// ENDE der Aenderung

	// Werte in die Klasse CHillEncryption einlesen
	hillklasse->set_dim(iDimension);

	// aus dem Text nur Buchstaben uebernehmen und in Grossbuchstaben konvertieren
	// den konvertierten Text ueber eine Datei in einen String einlesen
	char *str;
	str = new char[iDateiLaenge+iNeueX+1];
	long str_laenge = 0;

	fseek(fp, 0, SEEK_SET);
	csEingabeDatei = (char *) malloc(iDateiLaenge+iNeueX+1);
	fread(csEingabeDatei, 1, iDateiLaenge, fp);
	fclose(fp);

	// Die erlaubten Zeichen aus der Eingabe uebernehmen:
	for (i=0; i<iDateiLaenge+iNeueX; i++)
	{
		// Falls Gross-/Kleinschreibung ignoriert werden soll,
		// muessen die Kleinbuchstaben in Grossbuchstaben konvertiert werden.
		if ( hillklasse->ist_erlaubtes_zeichen(csEingabeDatei[i]) )
		{
			str[str_laenge++] = csEingabeDatei[i];
		}
		else if	( (theApp.TextOptions.getIgnoreCase()) && (MyIsLower(csEingabeDatei[i])) && 
				   (hillklasse->ist_erlaubtes_zeichen(MyToUpper(csEingabeDatei[i]))) )
		{
			str[str_laenge++] = MyToUpper(csEingabeDatei[i]);
		}
	}
	str[str_laenge] = '\0';
	free(csEingabeDatei);

	// Variable zur Ausgabe des Schlüssels in der Titelleiste
	char schluessel[(HILL_MAX_DIM_GROSS+1)*HILL_MAX_DIM_GROSS+1];
	
	int  i_m_decrypt;
	BOOL i_m_Verbose;
	CSquareMatrixModN *matrix;

	if (iHillSchluesselFensterGroesse == HILL_SCHLUESSEL_GROSS)
	{
		i_m_decrypt = hilleingross->m_decrypt;
		i_m_Verbose = hilleingross->m_Verbose;
		matrix = new CSquareMatrixModN(hilleingross->mat->get_dim(),hillklasse->get_modul());
		(*matrix) = (*(hilleingross->mat));
	}
	else
	{
		i_m_decrypt = hillein->m_decrypt;
		i_m_Verbose = hillein->m_Verbose;
		matrix = new CSquareMatrixModN(hillein->mat->get_dim(),hillklasse->get_modul());
		(*matrix) = (*(hillein->mat));
	}

	if (i_m_decrypt) // Entschluesseln
	{
		// Zuerst Matrix invertieren
		// Die Eingabe einer nicht invertierbaren Matrix wird abgelehnt 
		// (in der Eingabe: Hilleingabe.cpp, Funktion: CDlgKeyHill5x5::OnOK()) !
		CSquareMatrixModN inv_mat(matrix->get_dim(),hillklasse->get_modul());
		BOOL b = matrix->invert(&inv_mat);
		ASSERT(b);

		// Schlüssel zur Ausgabe in der Titelleiste speichern
		for (i=0; i<iDimension; i++)
		{
			for (int j=0; j<iDimension; j++)
			{
				schluessel[i*(iDimension+1)+j] = hillklasse->my_int_to_char((*matrix)(i,j));
			}
			schluessel[i*(iDimension+1)+iDimension] = ' ';
		}
		schluessel[(iDimension+1)*iDimension-1] = '\0';

		hillklasse->set_dec_mat(inv_mat);
		hillklasse->set_ciphertext(str);
		delete[] str;

		hillklasse->entschluesseln();
		
		str = new char[hillklasse->get_laenge_plain()+1];
		hillklasse->get_plaintext(str);
	}
	else // Verschluesseln
	{
		// Schlüssel zur Ausgabe in der Titelleiste speichern
		for (i=0; i<iDimension; i++)
		{
			for (int j=0; j<iDimension; j++)
			{
				schluessel[i*(iDimension+1)+j] = hillklasse->my_int_to_char((*matrix)(i,j));
			}
			schluessel[i*(iDimension+1)+iDimension] = ' ';
		}
		schluessel[(iDimension+1)*iDimension-1] = '\0';

		hillklasse->set_enc_mat(*matrix);
		hillklasse->set_plaintext(str);
		delete[] str;

		hillklasse->verschluesseln();

		str = new char[hillklasse->get_laenge_cipher()+1];
		hillklasse->get_ciphertext(str);
	}
	
	// Ver- bzw. Entschluesselten Text in temporaere Datei schreiben
	GetTmpName(outfile,"cry",".txt");
    ofstream out(outfile);
	out << str;
	out.close();
	delete[] str;

	// Ver- bzw. Entschluesselte Daten aus Hill-Klasse auslesen und in neuem Fenster anzeigen
    // und danach die temporaere Datei wieder loeschen
	Reformat(infile, outfile, FALSE);
	OpenNewDoc( outfile, schluessel, OldTitle, IDS_STRING_HILL, i_m_decrypt, SCHLUESSEL_QUADRATISCH );

	if ( i_m_Verbose )
	{
		GetTmpName(outfile,"cry",".txt");
		ofstream verboseOut(outfile);
		CString out;
		hillklasse->OutputHillmatrix(out);
		verboseOut << out.GetBuffer(0);
		verboseOut.close();


		CAppDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
		remove(outfile);
		if (NewDoc) {
			char title[128]; 
			// LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_ANALYSIS_OF,pc_str,STR_LAENGE_STRING_TABLE);
			GetNewDocTitle(schluessel, OldTitle, IDS_STRING_HILL_DETAILS, title, 128, i_m_decrypt, SCHLUESSEL_QUADRATISCH );
			NewDoc->SetTitle(title);
			CView* CView_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive()->GetActiveView();
			((CScintillaView*)CView_hilf)->OnViewFontCourier10();
		}
	}


	delete matrix;

	if (iHillSchluesselFensterGroesse == HILL_SCHLUESSEL_GROSS)
	{
		ASSERT (hilleingross != NULL);
		delete hilleingross;
	}
	else
	{
		ASSERT (hillein != NULL);
		delete hillein;
	}

	// Nun muessen die in die Eingabedatei geschriebenen Zeichen wieder entfernt werden,
	// da sonst bei Verschluesselung der gleichen Datei mit Schluesseln verschiedener 
	// Dimensionen immer wieder aufgefuellt wird und damit am Ende immer mehr Fuellzeichen
	// stehen. Dies fuehrt auch zu Problemen bei der Analyse einer vorher verschluesselten 
	// Datei, da beide Texte Fuellzeichen enthalten und somit der Schluessel zwar gefunden
	// werden kann, jedoch bei Entsachluesseln des / der letzten Bloecke ein Fehler auftritt
	// und somit der Schluessel wegen eines Widerspruches als nicht gefunden erkannt wird.
	csEingabeDatei = (char *) malloc(iDateiLaenge+iNeueX+1);
	fp = fopen(infile,"r+b");
	fread(csEingabeDatei, 1, iDateiLaenge+iNeueX, fp);
	fp = freopen(infile,"wb",fp);
	fwrite(csEingabeDatei, 1, iDateiLaenge, fp);
	fclose(fp);
	free(csEingabeDatei);
	
	HIDE_HOUR_GLASS
}


void Entropy( const char* infile, SymbolArray &text, const char* oldtitle)
{
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) return;
	int nalph = text.GetModulus();
	int nsymbol = 0;

	SHOW_HOUR_GLASS

	NGram distr(text);
	for (int i = 0; i < nalph; i++) 
		if (distr[i])
			nsymbol++;

	CDlgEntropyInfo entropyInfo;
	entropyInfo.SetParameter( oldtitle, nalph, nsymbol, log2(nalph), distr.Entropie());
	entropyInfo.DoModal();	

	HIDE_HOUR_GLASS
}

void EntropyASCII(const char *infile, const char *OldTitle)
{
    SymbolArray text(AppConv);
	Entropy( infile, text, OldTitle );
}

void EntropyBin(const char *infile, const char *OldTitle)
{
    SymbolArray text(IdConv);
	Entropy( infile, text, OldTitle );
}


int deltas[]={1,2,5,10,20,25,50,100,200,250,500,1000};

UINT Vitanycorr(PVOID p)
{
	CryptPar *par;
	char outfile[128];

	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_PROGRESS) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYZE_VITANY,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Display(pc_str);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_END_ANALYZE_VITANY,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	class CRandomAnalysisTools analyse((char *)par->infile);
	analyse.WriteAnalyse(outfile,par->OldTitle);

	if((par->flags & CRYPT_DO_PROGRESS ) && (theApp.fs.m_canceled == 0)) {
		while(theApp.fs.Set(100)!=100) Sleep(100);
		theApp.fs.cancel();
	}

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	par->flags |= CRYPT_DONE;
	FreePar(par);

	return 0;
}


// === PERIODENANALYSE
// September 2000 - Peter Gruber Entwurf
// Oktober 2000 - Henrik Koy Fehlerbeseitigung
// Januar 2001 - Thomas Gauweiler: Fehlerbeseitigung & linearer Algorithmus
// Juni 2001 - Thomas Gauweiler: neue Ausgabe mit Speichern in Datei
// 
UINT Periode(PVOID p)
{
	CryptPar *par;

	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_PROGRESS) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PERIOD_ANALYSIS,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Display(pc_str);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PERIOD_ANALYSIS_D,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	CDlgPeriodicityAnalysis POutp;
	POutp.OldTitle = strdup(par->OldTitle);
	class CRandomAnalysisTools analyse((char *)par->infile);
	int isPeriode;
	OPENFILENAME ofn;
	// Ausgabe der Periodenlänge
	char fname[257], ftitle[128], fboxtitle[128];

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS

	// Initialisierung des Fortschrittbalkens
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PERIOD_ANALYSIS_D,pc_str,STR_LAENGE_STRING_TABLE);
	theApp.fs.Set(0,pc_str);

	// Thomas' Variante
	// eigentliche Periodenanalyse
	isPeriode = analyse.FindPeriod();

	// Vollständigkeit des Fortschrittbalkens anzeigen
	theApp.fs.Set(100,pc_str);

	if((par->flags & CRYPT_DO_PROGRESS ) && (theApp.fs.m_canceled == 0)) {
		while(theApp.fs.Set(100)!=100) Sleep(100);
		theApp.fs.cancel();
	}
	while(theApp.fs.m_displayed) Sleep(10);

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	par->flags |= CRYPT_DONE;

	FreePar(par);
	p = NULL;


	// prepare the fileselectorbox dialog
	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = AfxGetMainWnd()->m_hWnd;
	ofn.hInstance = AfxGetInstanceHandle();
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_FSBDTITLE,pc_str,STR_LAENGE_STRING_TABLE);
	ofn.lpstrTitle = fboxtitle;	fboxtitle[0] = '\0';
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_FSBDTITLE,fboxtitle,128);
	ofn.Flags = OFN_HIDEREADONLY;
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_FILENAME,pc_str,STR_LAENGE_STRING_TABLE);
	ofn.lpstrFile = fname;	strcpy(fname, pc_str);
	ofn.nMaxFile = sizeof(fname)-1;
	ofn.lpstrFileTitle = ftitle;	ftitle[0] = '\0';
	ofn.nMaxFileTitle = sizeof(ftitle);

	POutp.zahlenanalyse = &analyse;
	if ( isPeriode > 0 )
	{
		POutp.DoModal();
	}


/*
	if ((isPeriode > 0) && (POutp.DoModal()==IDOK) && (GetSaveFileName(&ofn)) && (fname[0]!='\0'))
	{  // Ausgabewerte speichern
		FILE *out;
		out=fopen(fname,"w");

		LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_TITLE,pc_str,STR_LAENGE_STRING_TABLE);
		fprintf(out,pc_str, "");
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_HEADER,pc_str,STR_LAENGE_STRING_TABLE);
		fprintf(out,pc_str);

		int maxtxtlen = (analyse.periodResults[analyse.cnt_periodResults-1].length<PA_MAXPRINTLENGTH) ? analyse.periodResults[analyse.cnt_periodResults-1].length : PA_MAXPRINTLENGTH;
//			for (int i=0; i<analyse.cnt_periodResults; i++) {
		for (int i=analyse.cnt_periodResults-1; i>=0; i--) {
			line[0] = '\0';
			fprintf(out,"%d\t", analyse.cnt_periodResults-i);
			fprintf(out,"%d\t", analyse.periodResults[i].offset+1);
			fprintf(out,"%d\t", analyse.periodResults[i].length);
			fprintf(out,"%d\t\t", analyse.periodResults[i].repeated+1);

			pc_str1[0]='\0';
			char s [PA_MAXPRINTLENGTH*4+10]; s[0]='\0';
			int len = (analyse.periodResults[i].length)<PA_MAXPRINTLENGTH ? analyse.periodResults[i].length : PA_MAXPRINTLENGTH;
			for (int k=0; k<len; k++) {
				s[k] = IsText(analyse.periodResults[i].str[k]) ? analyse.periodResults[i].str[k] : '.';
				sprintf(pc_str1,"%s %02.2X", pc_str1, (unsigned char)analyse.periodResults[i].str[k]);
			}
			s[len]='\0';

			fprintf(out,"%s\t", s);
			for (int j= (maxtxtlen - analyse.periodResults[i].length+7) / 8; j>0; j--) fprintf(out,"\t");
			fprintf(out,"%s\n", pc_str1);
		}
		fclose(out);

	}
*/
	// Keine Periode gefunden
	if (isPeriode == 0)
	{
		Message(IDS_STRING_NO_PERIOD_FOUND, MB_ICONINFORMATION);
	}

	// Zu analysierende Textdatei zu kurz
	if (isPeriode < 0)
	{
		Message(IDS_STRING_ERR_PERIOD_ANALYSIS_TEXTLENGTH, MB_ICONEXCLAMATION);
	}


	return 0;
}



UINT Autocorr(PVOID p)
{
    int i, j, n, r,fsize;
	char line[256], name[128], name2[128];
	CAppDocument *NewDoc = NULL;
	CryptPar *par;
	CFile f;
	FILE *fo;

	r=0;
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS

    SymbolArray text(IdConv);
	if(par->flags & CRYPT_ASCII)
		text.SetConverter((class Converter &) AppConv);

	// FLAG für Fortschrittsanzeiger
	if(par->flags & CRYPT_DO_PROGRESS) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOCORRELATION,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Display(pc_str);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOCORRELATION_COMPLETE,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

   	SCorrelation *tx;
	if(par->result) {
		tx = (SCorrelation *) par->result;
		n = fsize = tx->GetSize();
	}
	else {
		text.Read(par->infile);
		fsize = text.GetSize();
		n =	min(fsize/2,200);

		tx = new SCorrelation(text,n);	// Auto-Korrelation 1..200 betrachten,
	}

	if(fsize < 8) { // Mindestlänge 8 Zeichen
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 8);
		r=1;
		goto cancel;
	}

	if((par->flags & (CRYPT_DISPLAY_BG | CRYPT_DISPLAY_IMMEDIATE)) !=0) {
		GetTmpName(name,"cry",".plt");
		fo = fopen(name,"wt");

		for(i=1;i<n;i++) {
			j = (int) (*tx)[i];
			if(theApp.PlotOptions.m_relativ)
				fprintf(fo,"%f\n",(double)j*100/fsize);   /* relative Übereinstimmung*/
			else
				fprintf(fo,"%d\n",j);
			if(((i%5)==0) && (par->flags & CRYPT_DO_PROGRESS)) {
					theApp.fs.Set((i*100)/n);
					if(theApp.fs.m_canceled) {
						fclose(fo);
						remove(name);
						r=1;
						goto cancel;
					}
			}
		}
		fclose(fo);

		// get the tmp name without file extension
		strcpy(name2, name);
		name2[strlen(name)-4] = 0x0;
	
		LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOCORRELATION_OF,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName(line,sizeof(line),pc_str,par->OldTitle);
	
	
		if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) ) {
			CArchive ar( &f, CArchive::store);
			CString s1 = line;
				LoadString(AfxGetInstanceHandle(),IDS_STRING_SHIFT,pc_str,STR_LAENGE_STRING_TABLE);
			CString s2 = pc_str;
			if (theApp.PlotOptions.m_relativ)
				LoadString(AfxGetInstanceHandle(),IDS_REL_MATCH,pc_str,STR_LAENGE_STRING_TABLE);
			else
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_MATCHING_CHARACTERS,pc_str,STR_LAENGE_STRING_TABLE);
			CString s3 = pc_str;

			ar << s1 << s2 << s3;
	
			// CONTINUOUS  X_CHAR  Y_CHAR
			ar << (int)1 << '0' << '0';
				
			ar.Close(); f.Close();

		}

		if(par->flags & (CRYPT_DISPLAY_BG | CRYPT_DISPLAY_IMMEDIATE)) {
			theApp.ThreadOpenDocumentFileNoMRU(name,line);
		}
	}
	else {
		for(i=1;i<n;i++) {
			j = (int) (*tx)[i];
			if((par->flags & CRYPT_DO_PROGRESS) && (i%5==0)) theApp.fs.Set((i*100)/n);
			if((par->flags & CRYPT_DO_PROGRESS) && (theApp.fs.m_canceled)) goto cancel;
		}
	}


cancel:


	if(!par->result) {
		free(tx);
	}

	if((par->flags & CRYPT_DO_PROGRESS ) && (theApp.fs.m_canceled == 0)) {
		while(theApp.fs.Set(100)!=100) Sleep(100);
		theApp.fs.cancel();
	}

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	par->flags |= CRYPT_DONE;
	FreePar(par);

	return r;
}

UINT FloatingEntropy(PVOID p)
// Berechnung der "gleitenden Entropie" in einem Fenster (Default: 64 Bytes, Max 256)
// Anzeige als Diagramm ähnlich der Autokorrelation
{
    int i, n, r, l;
	char line[256], name[128], name2[128];
	unsigned char buffer[1024], c;
	int num[256], g;
	double ld[257], e;
	CAppDocument *NewDoc = NULL;
	CryptPar *par;
	CFile f;
	FILE *fi, *fo;
	int winsize = 64;

	r=0;
	winsize = 64;
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS

	if(par->flags & CRYPT_DO_PROGRESS) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FLOATING_FREQ,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Display(pc_str);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FLOATING_FREQ_FINISHED,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	n = filesize(par->infile);
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	fi = fopen(par->infile,"rb");
	l = fread(buffer, 1, sizeof(buffer), fi);
	fo = NULL;

	if(l<winsize) {
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, winsize);
		r=1;
		goto cancel;
	}

	// initialisierung von ld
	ld[0]=0.0;
	for(i=min(257,winsize);i>0;i--) {
//		t = ((double)i) / ((double)winsize);  // verwende Logarithmus
//		ld[i] = -t * log(t) / log(2);
		ld[i] = 1;	// zählen der unterschiedlichen Zeichen
	}

	// initiale Befüllung des Arrays num
	for(i=0;i<256;i++) num[i] = 0;
	for(i=0;i<winsize;i++) num[buffer[i]]++;

	// initialisieren der Entropie
	for(e=i=0;i<256;i++) e += ld[num[i]];

	GetTmpName(name,"cry",".plt");
	fo = fopen(name,"wt");

	// ganze Datei abarbeiten
	g = 0;
	do {
		for(i=winsize;i<l;i++) {
			// Entropie in Datei schreiben
			fprintf(fo,"%g\n",e);
			if(((g%5)==0) && (par->flags & CRYPT_DO_PROGRESS)) {
					theApp.fs.Set((g*100)/n);
					if(theApp.fs.m_canceled) {
						fclose(fo);
						remove(name);
						r=1;
						goto cancel;
					}
			}
			// Entropie updaten
			c = buffer[i-winsize];
			e -= ld[num[c]];
			num[c]--;
			e += ld[num[c]];
			c = buffer[i];
			e -= ld[num[c]];
			num[c]++;
			e += ld[num[c]];
			g++;
		}
		memcpy(buffer,buffer+l-winsize,winsize);
		l = winsize + fread(buffer+winsize, 1, sizeof(buffer)-winsize, fi);
	} while(l>winsize);

	fclose(fo);

	// get the tmp name without file extension
	strcpy(name2, name);
	name2[strlen(name)-4] = 0x0;
	
	//////// string name aendern
	LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_FLOATING_FREQ_OF,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName(line,sizeof(line),pc_str,par->OldTitle);
	
	
	if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) ) {
		CArchive ar( &f, CArchive::store);
		CString s1 = line;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FLOATING_ENTROPY_SEQUENCE_POSITION,pc_str,STR_LAENGE_STRING_TABLE);
		CString s2 = pc_str;
		LoadString(AfxGetInstanceHandle(),IDS_FLOATING_FREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
		CString s3 = pc_str;

		ar << s1 << s2 << s3;
	
		// CONTINUOUS  X_CHAR  Y_CHAR
		ar << (int)1 << '0' << '0';
				
		ar.Close(); f.Close();

	}

	if(par->flags & (CRYPT_DISPLAY_BG | CRYPT_DISPLAY_IMMEDIATE)) {
		theApp.ThreadOpenDocumentFileNoMRU(name,line);
	}


cancel:

	fclose(fi);

	if((par->flags & CRYPT_DO_PROGRESS ) && (theApp.fs.m_canceled == 0)) {
		while(theApp.fs.Set(100)!=100) Sleep(100);
		theApp.fs.cancel();
	}

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	par->flags |= CRYPT_DONE;
	FreePar(par);

	return r;
}

void HistogramASCII(const char *infile, const char *OldTitle)
{
    char line[256], name[128], name2[128], numbuff[20];
	CFile f;

	SHOW_HOUR_GLASS

    SymbolArray text(AppConv);

    text.Read(infile);
	if ( !CheckTextSize( text ) ) return;

    NGram distr(text);
	GetTmpName(name,"cry",".plt");

	int len = text.GetSize();
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ASCII_HISTOGRAM_OF,pc_str,STR_LAENGE_STRING_TABLE);
    MakeNewName2(line,sizeof(line),pc_str,_itoa(len, numbuff, 10),OldTitle);

	distr.Show(OStream(name)<< OStream::Title(0) << OStream::Description(0) << OStream::Summary(0) << OStream::Percent());
	// get the tmp name without file extension
	strcpy(name2, name);
	name2[strlen(name)-4] = 0x0;

	if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) ) {
		CArchive ar( &f, CArchive::store);
		CString s1 = line;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_VALUE,pc_str,STR_LAENGE_STRING_TABLE);
		CString s2 = pc_str;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
		CString s3 = pc_str;

		// headline <<  x_label << y_label
		ar << s1 << s2 << s3;
		// CONTINUOUS  X_CHAR  Y_CHAR
		ar << (int)0 << (char)0x40 << (char)0x30;
		ar.Close(); f.Close();
	}

    theApp.ThreadOpenDocumentFileNoMRU(name,line);
	HIDE_HOUR_GLASS
}



void HistogramBin(const char *infile, const char *OldTitle)
{
    char line[256],name[128], name2[128], numbuff[20];
	CFile f;

	SHOW_HOUR_GLASS

    SymbolArray text(IdConv);
    text.Read(infile);
	if ( !CheckTextSize( text ) ) return;

    NGram distr(text);
	GetTmpName(name,"cry",".plt");

	int len = text.GetSize();
	LoadString(AfxGetInstanceHandle(),IDS_STRING_BINARY_HISTOGRAM_OF,pc_str,STR_LAENGE_STRING_TABLE);
    MakeNewName2(line,sizeof(line),pc_str,_itoa(len, numbuff, 10),OldTitle);
	distr.Show(OStream(name)<< OStream::Title(0) << OStream::Description(0) << OStream::Summary(0) << OStream::Percent());

	// get the tmp name without file extension
	strcpy(name2, name);
	name2[strlen(name)-4] = 0x0;

	if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) ) {
		CArchive ar( &f, CArchive::store);
		CString s1 = line;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_VALUE,pc_str,STR_LAENGE_STRING_TABLE);
		CString s2 = pc_str;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
		CString s3 = pc_str;

		// headline <<  x_label << y_label
		ar << s1 << s2 << s3;

		// CONTINUOUS  X_CHAR  Y_CHAR
		ar << (int)0 << '0' << '0';
		ar.Close(); f.Close();
	}

    theApp.ThreadOpenDocumentFileNoMRU(name,line);
	HIDE_HOUR_GLASS
}


int AnalyseMonoManual(const char *infile, const char *OldTitle)
{
	// char *common[135]; // FIXME: not used?! 
	// int Grenze; // FIXME: not used?!
	//Eingabedatei=infile;
	int vore[26], nache[26], i; //  anfang[26], ende[26], j; // FIXME: not used ?!
	for (i=0; i<26; i++){
		nache[i]=0;
		vore[i]=0;
	}

	// Umlaute und Zeilenumbrueche umwandeln
	char outfile2[1024];
	GetTmpName(outfile2,"cry",".txt");
	FILE *stream, *stream2;
		
	int ch;
	if( (stream = fopen( infile, "rt" )) == NULL )
		exit( 0 );
	if( (stream2 = fopen( outfile2, "wt" )) == NULL )
		exit( 0 );

	while ( feof( stream ) == 0 )
	{
		ch = fgetc( stream );
		switch(ch) {
		case (-1):
			break;
		case ('\n'):					// Zeilenumbruch
			fwrite (" \n", 1, 2, stream2);
			break;
		case (252):
			fwrite ("ue", 1, 2, stream2);
			break;
		case (220):
			fwrite ("Ue", 1, 2, stream2);
			break;
		case (246):
			fwrite ("oe", 1, 2, stream2);
			break;
		case (214):
			fwrite ("Oe", 1, 2, stream2);
			break;
		case (228):
			fwrite ("ae", 1, 2, stream2);
			break;
		case (196):
			fwrite ("Ae", 1, 2, stream2);
			break;
		case ('ß'):
			fwrite ("ss", 1, 2, stream2);
			break;
		default:
			fputc (ch, stream2);
			break;
		}
	}
	fclose (stream);
	fclose (stream2);
	
	Eingabedatei=outfile2;
	SymbolArray text(AlphaSpaceConv);
	text.Read(outfile2);
	int Laenge=text.GetSize(); // Länge des eingelesenen Textes
	// int Leerzeichen;		// FIXME: not used (Position des nächsten Leerzeichens)
	int Start=0;			// Merkt sich, wo das letzte Leerezichen gefunden wurde
	char *current=(char*) malloc (50);

	// Initialisieurng vom Permu und MaxPermu
	// Permu speichert die gerade untersuchte Substitution und MaxPermu die Substitution,
	// die bisher das beste Ergebnis brachte.
	int *Permu[26];//,*MaxPermu[26];
	//int *Permu[26];
	for (i=0; i<26; i++){
		Permu[i]=(int*)malloc(sizeof(int));
		*Permu[i]=-1;
		MaxPermu[i]=(int*)malloc(sizeof(int));
		*MaxPermu[i]=-1;
	}

	/* Manuelle Bearbeitung des Textes:
	   Das Nachbearbeitungsfenster wird aufgerufen. Im oberen Teil des Fensters werden
	   jedoch noch keine Zuordnungen vorgenommen (alles mit '*' initialisiert).
	   Der Benutzer kann Zuordnungen eingeben. Die daraus resultierende aktuelle
	   Substitution wird benutzt, um den zu bearbeitenden Ciphertext zu entschlüsseln.
	   Das Resultat wird im unteren Texfenster dargestellt.				*/

	CDlgManualSubstAnalysis Dialogbox;
	if (Dialogbox.DoModal()==IDOK){
		// Entschlüsseln und Ausgabe des Textes
		char outfile[1024], title[1024];
		GetTmpName(outfile,"cry",".txt");

		Laenge=text.GetSize();

		LPTSTR string = new TCHAR[Laenge + 1];
		int len;

		for (len=i=0 ; i<Laenge; i++){
			if (text[i]!=26){
				if (*MaxPermu[text[i]]!=-1){
					string[len++]=(char)(*MaxPermu[text[i]]);
				}
				else {
					string[len++]=(char)text[i]+'a';}
			}
		}
		string[len]=0;

		char *Ausgabe2=string;
		// Kopieren von char *Ausgabe2 in die Datei <outfile> (mit Hilfe der Secude Funktionen)
		OctetString help;
		help.noctets=strlen(Ausgabe2);
		help.octets=Ausgabe2;
		theApp.SecudeLib.aux_OctetString2file(&help,outfile,2);
		delete string;

		ForceReformat(outfile2, outfile, TRUE);

		// Berechnung der (Teil-)Permutation zur Anzeige im Titel
		char schluessel[27];
		for (i=0; i<26;i++)
		{
			schluessel[i] = '*';
		}
		for (i=0; i<26;i++)
		{
			if (*MaxPermu[i] != -1)
			{
				schluessel[(*MaxPermu[i])-'A'] = i+'A';
			}
		}
		schluessel[26]='\0';

		LoadString(AfxGetInstanceHandle(),IDS_STRING_POSSIBLE_PLAINTEXT_OF,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName2(title,sizeof(title),pc_str,schluessel,OldTitle);
		theApp.ThreadOpenDocumentFileNoMRU(outfile, title, schluessel);
		remove(outfile2);	
	}
	// Den allokierten Speicherplatz von current, Permu und MaxPermu freigeben
	free (current);
	for (i=0; i<26; i++){
		free (Permu[i]);
		free (MaxPermu[i]);
	}
	return 0;
}


/* Funktion zur monoalphabetischen Ver- und Entschlüsselung			*/
void Mono(const char *infile, const char *OldTitle){

	// Überprüfung, ob Eingabedatei mindestens ein Zeichen enthält. 
	CFile datei(infile, CFile::modeRead);
	bool laenge_groesser_0 = FALSE;
	char c;
	while(datei.Read(&c,1) && ! laenge_groesser_0)
	{
		if ( (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) )
		{
			laenge_groesser_0 = TRUE;
		}
	}
	datei.Close();
	if (! laenge_groesser_0)
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		return;
	}

// Encryption
	CDlgMonSubst dlgMono;
	if ( IDOK == dlgMono.DoModal() )
	{
		char outfile[1024], title[1024];
		CAppDocument *NewDoc;
		char outfile2[1024];
		GetTmpName(outfile2,"cry",".txt");
		FILE *stream, *stream2;

		// Umlaute und Zeilenumbrueche umwandeln		
		int ch;
		if( (stream = fopen( infile, "rt" )) == NULL )
			exit( 0 );
		if( (stream2 = fopen( outfile2, "wt" )) == NULL )
			exit( 0 );

		while ( feof( stream ) == 0 ){
			ch = fgetc( stream );
			switch(ch) {
			case (-1):
				break;
			case ('\n'):					// Zeilenumbruch
				fwrite (" \n", 1, 2, stream2);
				break;
			case (252):
				fwrite ("ue", 1, 2, stream2);
				break;
			case (220):
				fwrite ("Ue", 1, 2, stream2);
				break;
			case (246):
				fwrite ("oe", 1, 2, stream2);
				break;
			case (214):
				fwrite ("Oe", 1, 2, stream2);
				break;
			case (228):
				fwrite ("ae", 1, 2, stream2);
				break;
			case (196):
				fwrite ("Ae", 1, 2, stream2);
				break;
			case ('ß'):
				fwrite ("ss", 1, 2, stream2);
				break;
			default:
				fputc (ch, stream2);
				break;
			}
		}
		fclose (stream);
		fclose (stream2);


	
		{  // CRYPT
			SymbolArray text(AlphaConv);
			//text.Read(infile);
			text.Read(outfile2);
			GetTmpName(outfile,"cry",".txt");
 			int Laenge=text.GetSize();
			
			int i;
			if (!dlgMono.m_cryptDirection){  // Decryption
				
				//Berechne die inverse Permutation
				char keyinvers[26];
				for (i=0; i<26; i++){
					keyinvers[dlgMono.key[i]-65]=i;}
				
				//Entschlüsselung (=Verschlüsselung mit der inversen Permutation)
				for (i=0 ; i<Laenge; i++){
					if (text[i]!=26){
						text[i]=(keyinvers[text[i]]);}}
			}
			else{   // ENCRYPTION
				for (i=0 ; i<Laenge; i++){
					if (text[i]!=26){
						text[i]=(dlgMono.key[text[i]]-65);}
				}
			}

			//Ausgabe des permutierten Textes
			text.Write(outfile);
		}

		Reformat(outfile2,outfile, TRUE);
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile,dlgMono.key);
		remove(outfile);	
		remove (outfile2);
		if(NewDoc) 
		{
			if(!dlgMono.m_cryptDirection)
				LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			else
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			// LoadString(AfxGetInstanceHandle(),IDS_STRING_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
			// Der eingegebene Schluessel ist zur Ausgabe in der Titelzeile nicht geeignet,
			// da bei der Analyse nur die Permutation gefunden werden kann, 
			// nicht jedoch das Schlüsselwort. 
			// Wegen der Konsistenz wird hier nur die Permutation ausgegeben 
			MakeNewName3(title,sizeof(title),pc_str1, dlgMono.typeOfEncryption ,OldTitle,dlgMono.key);
			NewDoc->SetTitle(title);
		}
	}


}

UINT AnaSubst(PVOID p) {
/*  Diese Funktion dient zum Brechen einer monoalphabetischen Substitution.
	Sie arbeitet mit deutschen und englischen Standardtexten.
	Die Leerzeichen müssen im Ciphertext enthalten sein.

	Die Analyse basiert auf einer Liste mit den häufigsten Wörtern der jeweiligen 
	Sprache. Im englischen ist die Wahrscheinlichkeit, daß ein zufällig aus einem
	Standardtext herausgegriffenes Wort in dieser Liste enthalten ust gerade 0,5.

	Die Wörter des Ciphertextes werden (ihrem Muster nach) mit den Wörtern in der 
	Liste verglichen. Bei jeder möglichen Zuordnung ergibt sich daraus eine
	(partielle) Substitution. Durch einen Suchbaum wird diejenige Substitution
	ermittelt, die mit den meisten partiellen Substitutionen verträglich ist.

	Quelle: George W. Hart
		   To Decode Short Cryptograms
		   Communications of the ACM, Sept 1994, Vol 37, No.4
*/
	
	char *common[135];
	CryptPar *par;
	int Grenze;
	//Eingabedatei=infile;
	int vore[26], nache[26], anfang[26], ende[26],i,j;
	for (i=0; i<26; i++){
		nache[i]=0;
		vore[i]=0;
	}

	// Anzeigen des Auswahlfensters für die gewünchte Analysemethode
	CDlgOptionsSubstitutionAnalysis Dialog;

	par = (CryptPar *) p;

	if (Dialog.DoModal()==IDOK){
		/* deutscher Klartext
		   Eine Liste mit den 106 häufigsten Wörtern wird eingelesen
		   Quelle: eigene statistische Auswertungen				*/
		if (Dialog.m_radio1==0){
			Grenze=106;
			common[0]="DIE";common[1]="DER";common[2]="UND";common[3]="IN";common[4]="DAS";
			common[5]="ER";common[6]="DEN";common[7]="ICH";common[8]="ZU";common[9]="SIE";
			common[10]="NICHT";common[11]="MIT";common[12]="SICH";common[13]="ES";common[14]="AUF";
			common[15]="WAR";common[16]="EIN";common[17]="VON";common[18]="DEM";common[19]="IST";
			common[20]="DES";common[21]="IM";common[22]="EINE";common[23]="ABER";common[24]="ALS";
			common[25]="AN";common[26]="HATTE";common[27]="AUCH";common[28]="WIE";common[29]="FUER";
			common[30]="WIR";common[31]="AUS";common[32]="NACH";common[33]="EINEN";common[34]="NOCH";
			common[35]="SO";common[36]="WAS";common[37]="DASS";common[38]="MIR";common[39]="HAT";
			common[40]="NUR";common[41]="UM";common[42]="EINEM";common[43]="DANN";common[44]="MICH";
			common[45]="VOR";common[46]="EINER";common[47]="WENN";common[48]="BEI";common[49]="ZUM";
			common[50]="ODER";common[51]="SEIN";common[52]="DU";common[53]="HABEN";common[54]="IHM";
			common[55]="IHN";common[56]="MAN";common[57]="AM";common[58]="WAREN";common[59]="WIEDER";
			common[60]="SEINE";common[61]="UNS";common[62]="SIND";common[63]="SCHON";common[64]="IMMER";
			common[65]="JA";common[66]="ALLES";common[67]="ETWAS";common[68]="DA";common[69]="DIESE";
			common[70]="DURCH";common[71]="WERDEN";common[72]="JETZT";common[73]="MEINE";common[74]="MEHR";
			common[75]="HIER";common[76]="WURDE";common[77]="HABE";common[78]="DOCH";common[79]="WIRD";
			common[80]="HATTEN";common[81]="DIESER";common[82]="IHR";common[83]="SEINER";common[84]="BIS";
			common[85]="KANN";common[86]="MENSCHEN";common[87]="EINES";common[88]="ZUR";common[89]="EINMAL";
			common[90]="KEINE";common[91]="UNTER";common[92]="IHRE";common[93]="KONNTE";common[94]="JAHRE";
			common[95]="ZEIT";common[96]="MAL";common[97]="FRAU";common[98]="ANDEREN";common[99]="VOM";
			common[100]="KOENNEN";common[101]="ALSO";common[102]="NICHTS";common[103]="IHNEN";common[104]="MANN";
			common[105]="UEBER";
		}
		if (Dialog.m_radio1==1){
			/* englischer Klartext
			   eine Liste mit den 135 häufigsten englischen Wörtern wird eingelesen.
			   Quelle: George W. Hart
			           To Decode Short Cryptograms
					   Communications of the ACM, Sept 1994, Vol 37, No.4			*/
			Grenze=135;
			common[0]="THE";common[1]="OF";common[2]="AND";common[3]="TO";common[4]="A";
			common[5]="IN";common[6]="THAT";common[7]="IS";common[8]="WAS";common[9]="HE";
			common[10]="FOR";common[11]="IT";common[12]="WITH";common[13]="AS";common[14]="HIS";
			common[15]="ON";common[16]="BE";common[17]="AT";common[18]="BY";common[19]="I";
			common[20]="THIS";common[21]="HAD";common[22]="NOT";common[23]="ARE";common[24]="BUT";
			common[25]="FROM";common[26]="OR";common[27]="HAVE";common[28]="AN";common[29]="THEY";
			common[30]="WHICH";common[31]="ONE";common[32]="YOU";common[33]="WERE";common[34]="HER";
			common[35]="ALL";common[36]="SHE";common[37]="THERE";common[38]="WOULD";common[39]="THEIR";
			common[40]="WE";common[41]="HIM";common[42]="BEEN";common[43]="HAS";common[44]="WHEN";
			common[45]="WHO";common[46]="WILL";common[47]="MORE";common[48]="NO";common[49]="IF";
			common[50]="OUT";common[51]="SO";common[52]="SAID";common[53]="WHAT";common[54]="UP";
			common[55]="ITS";common[56]="ABOUT";common[57]="INTO";common[58]="THAN";common[59]="THEM";
			common[60]="CAN";common[61]="ONLY";common[62]="OTHER";common[63]="NEW";common[64]="SOME";
			common[65]="COULD";common[66]="TIME";common[67]="THESE";common[68]="TWO";common[69]="MAY";
			common[70]="THEN";common[71]="DO";common[72]="FIRST";common[73]="ANY";common[74]="MY";
			common[75]="NOW";common[76]="SUCH";common[77]="LIKE";common[78]="OUR";common[79]="OVER";
			common[80]="MAN";common[81]="ME";common[82]="EVEN";common[83]="MOST";common[84]="MADE";
			common[85]="AFTER";common[86]="ALSO";common[87]="DID";common[88]="MANY";common[89]="BEFORE";
			common[90]="MUST";common[91]="THROUGH";common[92]="BACK";common[93]="YEARS";common[94]="WHERE";
			common[95]="MUCH";common[96]="YOUR";common[97]="WAY";common[98]="WELL";common[99]="DOWN";
			common[100]="SHOULD";common[101]="BECAUSE";common[102]="EACH";common[103]="JUST";common[104]="THOSE";
			common[105]="PEOPLE";common[106]="MR";common[107]="HOW";common[108]="TOO";common[109]="LITTLE";
			common[110]="STATE";common[111]="GOOD";common[112]="VERY";common[113]="MAKE";common[114]="WORLD";
			common[115]="STILL";common[116]="OWN";common[117]="SEE";common[118]="MEN";common[119]="WORK";
			common[120]="LONG";common[121]="GET";common[122]="HERE";common[123]="BETWEEN";common[124]="BOTH";
			common[125]="LIFE";common[126]="BEING";common[127]="UNDER";common[128]="NEVER";common[129]="DAY";
			common[130]="SAME";common[131]="ANOTHER";common[132]="KNOW";common[133]="WHILE";common[134]="LAST";}
	}
	else{	// Der Benutzer hat in der Dialogbox "Abbrechen" gedrückt
		return 0;}

	// Manuelle Analyse wurde gewählt.
	// In diesem Fall ist eine Anzeige des Fortschrittsanzeigers nicht nötig,
	// da keine umfangreichen Berechnungen angestellt werden müssen.
	if(Dialog.m_radio1 < 2 && Dialog.m_radio1 >= 0){
		if(par->flags & CRYPT_DO_PROGRESS) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_SUBSTITUTION_ANALYSE,pc_str,STR_LAENGE_STRING_TABLE);
			theApp.fs.Display(pc_str);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_SUBSTITUTION_ANALYSE_COMPLETE,pc_str,STR_LAENGE_STRING_TABLE);
			theApp.fs.Set(0,pc_str);
			Sleep(1);
		}
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			SHOW_HOUR_GLASS
	}

	// Umlaute und Zeilenumbrueche umwandeln
	char outfile2[1024];
	GetTmpName(outfile2,"cry",".txt");
	FILE *stream, *stream2;
		
	int ch;
	if( (stream = fopen( par->infile, "rt" )) == NULL )
		exit( 0 );
	if( (stream2 = fopen( outfile2, "wt" )) == NULL )
		exit( 0 );

	while ( feof( stream ) == 0 )
	{
		ch = fgetc( stream );
		switch(ch) {
		case (-1):
			break;
		case ('\n'):					// Zeilenumbruch
			fwrite (" \n", 1, 2, stream2);
			break;
		case (252):
			fwrite ("ue", 1, 2, stream2);
			break;
		case (220):
			fwrite ("Ue", 1, 2, stream2);
			break;
		case (246):
			fwrite ("oe", 1, 2, stream2);
			break;
		case (214):
			fwrite ("Oe", 1, 2, stream2);
			break;
		case (228):
			fwrite ("ae", 1, 2, stream2);
			break;
		case (196):
			fwrite ("Ae", 1, 2, stream2);
			break;
		case ('ß'):
			fwrite ("ss", 1, 2, stream2);
			break;
		default:
			fputc (ch, stream2);
			break;
		}
	}
	fclose (stream);
	fclose (stream2);
	
	Eingabedatei=outfile2;
	SymbolArray text(AlphaSpaceConv);
	text.Read(outfile2);
	int Laenge=text.GetSize(); // Länge des eingelesenen Textes
	int Leerzeichen;		// Position des nächsten Leerzeichens
	int Start=0;			// Merkt sich, wo das letzte Leerezichen gefunden wurde
	char *current=(char*) malloc (50);

	// Initialisieurng vom Permu und MaxPermu
	// Permu speichert die gerade untersuchte Substitution und MaxPermu die Substitution,
	// die bisher das beste Ergebnis brachte.
	int *Permu[26];//,*MaxPermu[26];
	//int *Permu[26];
	for (i=0; i<26; i++){
		Permu[i]=(int*)malloc(sizeof(int));
		*Permu[i]=-1;
		MaxPermu[i]=(int*)malloc(sizeof(int));
		*MaxPermu[i]=-1;
	}

	/* Manuelle Bearbeitung des Textes:
	   Das Nachbearbeitungsfenster wird aufgerufen. Im oberen Teil des Fensters werden
	   jedoch noch keine Zuordnungen vorgenommen (alles mit '*' initialisiert).
	   Der Benutzer kann Zuordnungen eingeben. Die daraus resultierende aktuelle
	   Substitution wird benutzt, um den zu bearbeitenden Ciphertext zu entschlüsseln.
	   Das Resultat wird im unteren Texfenster dargestellt.				*/

	if (Dialog.m_radio1==2 || Dialog.m_storedKey == 0){
		// Anzeigen des Nachbearbeitungsfensters
		if ( Dialog.m_storedKey == 0 )
		{
			LoadString(AfxGetInstanceHandle(),IDS_ANALYSIS_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
			CString SubstKey;
			if ( PasteKey( pc_str, SubstKey ) )
			{
				for (int i=0; i<26; i++)
				{
					*MaxPermu[i] = SubstKey[i];
				}
			}
		}

		CDlgManualSubstAnalysis Dialogbox;
		if (Dialogbox.DoModal()==IDOK){
			// Entschlüsseln und Ausgabe des Textes
			char outfile[1024], title[1024];
			GetTmpName(outfile,"cry",".txt");

			Laenge=text.GetSize();

			LPTSTR string = new TCHAR[Laenge + 1];
			int len;

			for (len=i=0 ; i<Laenge; i++){
				if (text[i]!=26){
					if (*MaxPermu[text[i]]!=-1){
						string[len++]=(char)(*MaxPermu[text[i]]);
					}
					else {
						string[len++]=(char)text[i]+'a';}
				}
			}
			string[len]=0;

			char *Ausgabe2=string;
			// Kopieren von char *Ausgabe2 in die Datei <outfile> (mit Hilfe der Secude Funktionen)
			OctetString help;
			help.noctets=strlen(Ausgabe2);
			help.octets=Ausgabe2;
			theApp.SecudeLib.aux_OctetString2file(&help,outfile,2);
			delete string;

			ForceReformat(outfile2, outfile, TRUE);

			// Berechnung der (Teil-)Permutation zur Anzeige im Titel
			char schluessel[27];
			for (i=0; i<26;i++)
			{
				schluessel[i] = '*';
			}
			for (i=0; i<26;i++)
			{
				if (*MaxPermu[i] != -1)
				{
					schluessel[(*MaxPermu[i])-'A'] = i+'A';
				}
			}
			schluessel[26]='\0';

			LoadString(AfxGetInstanceHandle(),IDS_STRING_POSSIBLE_PLAINTEXT_OF,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName2(title,sizeof(title),pc_str,schluessel,par->OldTitle);
			theApp.ThreadOpenDocumentFileNoMRU(outfile, title, schluessel);
			remove(outfile2);	
		}
		// Den allokierten Speicherplatz von current, Permu und MaxPermu freigeben
		free (current);
		for (i=0; i<26; i++){
			free (Permu[i]);
			free (MaxPermu[i]);
		}
		return 0;
	}
	
	// Variable Max_Score wird mitübergeben
	int MaxScore=-1;

	int oft=-1;

	bool doppelt=false;


	/* Die Option
	   'e' als häufigstes Zeichen annehmen 
	   wurde angewählt.
	   Das häufigste Zeichen im Text wird bestimmt und die Anfangspermutation wird so gesetzt,
	   daß dieses Zeichen die Verschlüsselung von 'e' darstellt.*/
	if ((Dialog.m_check1)||(Dialog.m_check2)){
		NGram t(text);
		int maxim=0;
		for (/*int*/ i=0; i<26; i++){
			if ((int)t.GetCount(i)>=maxim){
				if ((int)t.GetCount(i)==maxim){
					doppelt=true;}
				else {
					doppelt=false;}
				oft=i;
				maxim=t.GetCount(i);			
			}
		}
		if (doppelt==true){
			Message(IDS_STRING_MSG_FREQ_ANALYSE_NOTE, MB_ICONINFORMATION);
		}
		else{
			*Permu[oft]=69;
		}
	}

	
	/* Ein zweidimensionales Feld Cipher wird erzeugt, in dem die Worte des Ciphertextes 
	   abgelegt werden.
	   Dabei werden Worte, die das selbe Pattern haben in einer Zeile (d.h. identische erste
	   Koordinate) abgelegt.
	   Doppelte Wörter werden ignoriert.
	   Ciphertextworte, für die kein passendes Pattern in common vorkommt, werden auch ignoriert.			*/

	/* In der i-ten Zeile von PatSet werden all die Einträge aus common gespeichert, die vom Pattern her zur
	   i-ten Zeile von Cipher passen																		*/

	char *Cipher [100][100];
	char *PatSet [100][50];
	// Felder Cipher und PatSet initialieren
	for (i=0;i< 100; i++){
		for (j=0;j<100;j++){
			Cipher[i][j]=NULL;}
		for (j=0; j<50; j++){
			PatSet[i][j]=NULL;}
	}

	
	if(par->flags & CRYPT_DO_PROGRESS)    theApp.fs.Set(10);
	int Worte_in_Analyse=0;
	
	while ((Start<Laenge)&&(Worte_in_Analyse<100)){

		if((par->flags & CRYPT_DO_PROGRESS)&&(theApp.fs.m_canceled))   return 0;
		Leerzeichen=SucheLeer(Start, Laenge, text);

		// Es werden Wörter gefunden, die länger als 20 Zeichen sind.
		// D.h. entweder der Text hat gar keine Leerzeichen oder das
		// Wort ist wirklich länger als 20 Zeichen.
		// Wörter, die länger als 20 Zeichen sind, kommen aber in common nicht vor
		// und können mißachtet werden.
		if ((Leerzeichen-Start)>20){
			Start=Leerzeichen+1;
			continue;}
		// Kopiere das letzte Wort (bis zum Blank) nach char *current
		// Gleichzeitig werden die Felder vore[26] und nache[26] mit den 
		// Buchstabenhäufigkeiten vor bzw. nach dem e gepflegt
		for (/*int*/ i=0;i<(Leerzeichen-Start);i++){
			current[i]=(int)text[Start+i]+65;
			if ((i<((Leerzeichen-Start)-1))&&(current[i]==(oft+65))){
				nache[(int)text[Start+i+1]]++;}
			if ((i!=0)&&(current[i]==(oft+65))){
				vore[current[i-1]-65]++;}
		}
		// gehört noch zum Kopiervorgang
		current[Leerzeichen-Start]=0;
		// Pflege der Felder anfang[26] und ende[26]
		anfang[current[0]-65]++;
		ende[current[Leerzeichen-Start-1]-65]++;


		// Suche die Zeile im Feld Cipher, die das selbe Pattern hat wie current
		for (i=0; i<100; i++){
			if (Cipher [i][0]==NULL){   // Pattern kommt in Cipher noch nicht vor
				// Teste, ob es für dieses Ciphertextwort ein passendes Pattern in common gibt
				bool passt=FALSE;
				for (int k=0; k<Grenze; k++){
					if (match(current, common[k])==TRUE){
						passt=TRUE;
						break;}
				}

				// Es gibt kein passendes Pattern für current in der Liste common
				if (passt==FALSE){
					break;}

				// Es gibt ein passendes Pattern
				if (passt==TRUE){

					Worte_in_Analyse++;
					// Lege neuen Eintrag in Cipher an		
					Cipher [i][0]=(char*)malloc(strlen(current)+1);
					// Cipher [i][0] den Wert von current zuweisen
					for (int k=0; k<(int)strlen(current); k++){
						Cipher [i][0][k]=current[k];
					}
					Cipher [i][0][strlen(current)]=0;
					
					// Füge die entsprechenden Patterns nach PatSet hinzu
					int j=0;
					for (int l=0; l<Grenze; l++){
						if (match (current, common[l])==TRUE){
							// Füge common [i] in PatSet ein
							PatSet [i][j]=(char*)malloc(strlen(common[l])+1);
							for (int k=0; k<(int)strlen(common[l]); k++){
								PatSet [i][j][k]=common[l][k];
							}
							PatSet [i][j][strlen(common[l])]=0;
							j++;

						}
					}						
					break;
				}				
			}

			if (match(Cipher [i][0],current)==TRUE){   // Zeile mit passendem Pattern gefunden
				// Schaue, ob das Wort (exakt, nicht das pattern) schon in der Zeile vorhanden ist
				
				for (int j=0; j<100;j++){
					if (Cipher [i][j]==NULL){
						Worte_in_Analyse++;
						// current in die Zeile einfügen
						// current nach Cipher [i][j] kopieren
						Cipher [i][j]=(char*)malloc(strlen(current)+1);
						for (int k=0; k<(int)strlen(current); k++){
							Cipher [i][j][k]=current[k];
						}
						Cipher [i][j][strlen(current)]=0;
						break;
					}
					else {
						// Vergleiche Cipher [i][j] mit current
						bool gleich=TRUE;
						if (strlen(Cipher[i][j])==strlen(current)){
							for (int k=0; k<(int)strlen(current); k++){
								if (Cipher[i][j][k]!=current[k]){
									gleich=FALSE;
								}
							}
						}
						else {gleich=FALSE;}
						if (gleich){

							break;
						}
					}
				}
				break;
			}
		}
		Start=Leerzeichen+1;
	}

	// Setze die Frtschrittsanzeige auf 10%
	if(par->flags & CRYPT_DO_PROGRESS) {
		theApp.fs.Set(15);
	}

	// Bestimmung von DMax, der Anzahl der verschiedenen Patternklassen
	int DMax;
	for (i=0; i<100; i++){
		if (Cipher [i][0]==NULL){
			DMax=i;
			break;
		}
	}

///////////////////////////////////////////////////////////////////////
// Ordnen der Ciphertextklassen
///////////////////////////////////////////////////////////////////////

/*  Finden des Root-Wortes
	Wir suchen die Ciphertextklasse, für die die Anzahl der verschiedenen 
	Buchstaben im Pattern geteilt durch die Größe der Pattern Set maximal ist			

	Das Feld nBuch[100] speichert die Anzahl der verschiedenen Buchstaben der Patterns 
	Das Feld nPatSet die Größe der zugehörigen Pattern Set
	Das Feld Taken merkt sich, ob die entsprechende Ciphertexte Klasse bereits 
	in die Sortierung aufgenommen wurde	Die Reihenfolge wird in Perm[100] gespeichert */
	float max=0;
	int nMax;
	int nBuch[100];
	int nPatSet[100];
	int Perm[100];
	bool taken[100];
	for (i=0; i<100; i++){
		nBuch[i]=0;
		nPatSet[i]=0;
		taken[i]=FALSE;}

	nMax=0;
	if(par->flags & CRYPT_DO_PROGRESS) {
		theApp.fs.Set(16);
	}

	for (i=0; i<DMax; i++){

		if(par->flags & CRYPT_DO_PROGRESS) {
			if(theApp.fs.m_canceled) {
				return 0;
			};
		}

		bool benutzt[26];
		for (j=0; j<26;j++){
			benutzt[j]=FALSE;}
		for (j=0; j<(int)strlen(Cipher[i][0]); j++){
			if (benutzt[(Cipher[i][0][j])-65]==FALSE){
				benutzt[(Cipher[i][0][j])-65]=TRUE;
				nBuch[i]++;
			}
		}

		for (j=0; j<50; j++){
			if (PatSet[i][j]!=NULL){
				nPatSet[i]++;
			}
			else
			{	
				break;
			}
		}

		if (((float)nBuch[i])/((float)nPatSet[i])>max){
			max=((float)nBuch[i])/((float)nPatSet[i]);
			nMax=i;}
	}

	if(par->flags & CRYPT_DO_PROGRESS) {
		theApp.fs.Set(17);
	}
	taken[nMax]=TRUE;
	Perm[0]=nMax;
	Perm[1]=nMax;

	/* Alle anderen Ciphertextklassen werden nach der Länge von nBuch sortiert
	   Dabei kommen die größten Werte für nBuch zuerst (Sinn: dadurch wird das Durchlaufen des
	   Suchbaumes effizienter)				*/
	for (i=1; i<DMax; i++){
		if((par->flags & CRYPT_DO_PROGRESS)&&(theApp.fs.m_canceled))    return 0;

// Bestimme das aktuelle Maximum nMax der nBuch
//	theApp.fs.Set(i);

		nMax=-1;
		int Maximum=-1;
		for (int j=0; j<DMax; j++){
			if (taken[j]==FALSE){
				if (nBuch[j]>Maximum){
					Maximum=nBuch[j];
					nMax=j;
				}
			}
		}
		taken[nMax]=TRUE;

		// Setze Perm[i] auf nMax;
		Perm[i]=nMax;
		Sleep(0);	// 
	}

	if(par->flags & CRYPT_DO_PROGRESS) {
		theApp.fs.Set(18);
	}

	//////////////////////////////////////////////////////////////
	// Ende (Ordnen der Ciphertextklassen)
	//////////////////////////////////////////////////////////////

	// Der Wert Delta gibt an, um wieviel die Fortschrittsanzeige jedesmal hochgesetzt werden
	// soll.
	// Da die Fortschrittsanzeige bei jedem Aufruf der Funktion "solve" bei Suchtiefe 1
	// hochgesetzt wird
	float Delta=40.0;
	nMax=0;
	while (Cipher[Perm[0]][nMax]!=NULL)   nMax++;
	Delta=Delta/((float)nMax+1);
	nMax=0;
	while (Cipher[Perm[1]][nMax]!=NULL)   nMax++;
	Delta=Delta/((float)nMax+1);

	
	// Setzen der Fortschrittsanzeige auf 20%
	if(par->flags & CRYPT_DO_PROGRESS) {
		theApp.fs.Set(20,pc_str);}

	/////////////////////////////////////////////////////////////
	// erweiterte Analyse (für deutsche Klartexte)
	/////////////////////////////////////////////////////////////

	// Bestimme den Buchstaben, der im Chiffrat am häufigsten nach dem e vorkommt.
	// Wir nehmen an, daß dieser Buchstabe entweder auf n oder auf r abgebildet wird
	if ((Dialog.m_check2)&&(doppelt==false)){

		
		// Sortieren der Listen vore[26], nache[26], anfang[26] und ende[26]
		bool benutzt[26];
		int nacheSort[26], voreSort[26], anfangSort[26], endeSort[26];

		//Sortiere nache[26] und lege das Ergebnis in nacheSort[26] ab
		for (i=0; i<26; i++){
			benutzt[i]=false;
		}

		int Maximum=-1, Maximalwert=-1;
		for (i=0; i<26; i++){
			// Finde den nächsthöheren Wert
			// Alle Werte, deren benutzt-Wert auf true steht sind schon vergebe
			for (int j=0; j<26; j++){
				if ((nache[j]>Maximalwert)&&(benutzt[j]==false)){
					Maximalwert=nache[j];
					Maximum=j;
				}
			}
			nacheSort[i]=Maximum;
			benutzt[Maximum]=true;
			Maximalwert=-1;
		}

		//Sortiere vore[26] und lege das Ergebnis in voreSort[26] ab
		for (i=0; i<26; i++){
			benutzt[i]=false;
		}

		Maximum=-1, Maximalwert=-1;
		for (i=0; i<26; i++){
			for (int j=0; j<26; j++){
				if ((vore[j]>Maximalwert)&&(benutzt[j]==false)){
					Maximalwert=nache[j];
					Maximum=j;
				}
			}
			voreSort[i]=Maximum;
			benutzt[Maximum]=true;
			Maximalwert=-1;
		}

		//Sortiere anfang[26] und lege das Ergebnis in anfangSort[26] ab
		for (i=0; i<26; i++){
			benutzt[i]=false;
		}

		Maximum=-1, Maximalwert=-1;
		for (i=0; i<26; i++){
			for (int j=0; j<26; j++){
				if ((anfang[j]>Maximalwert)&&(benutzt[j]==false)){
					Maximalwert=anfang[j];
					Maximum=j;
				}
			}
			anfangSort[i]=Maximum;
			benutzt[Maximum]=true;
			Maximalwert=-1;
		}

		//Sortiere ende[26] und lege das Ergebnis in endeSort[26] ab
		for (i=0; i<26; i++){
			benutzt[i]=false;
		}

		Maximum=-1, Maximalwert=-1;
		for (i=0; i<26; i++){
			for (int j=0; j<26; j++){
				if ((ende[j]>Maximalwert)&&(benutzt[j]==false)){
					Maximalwert=ende[j];
					Maximum=j;
				}
			}
			endeSort[i]=Maximum;
			benutzt[Maximum]=true;
			Maximalwert=-1;
		}



		/* Bestimme das n als den Buchstaben, der in den Listen
		   endeSort[26] und nacheSort[26] "am weitesten oben steht".
		   Unter "am weitesten oben steht" ist zu verstehen, daß die
		   Summe der Indizes minimal ist.						*/

		/* Da es häufig Schwierigkeiten in der Unterscheidung von n und r
		   gab, die weiteren Analysen jedoch auf der Erkennung des n beruhen,
		   wurde die Funktion erweitert.
		   Es werden nun die beiden Minima berechnet.
		   Als das n wird dann der Wert (von beiden) angenommen, 
		   der in allen vier Listen am weitesten oben steht. Der andere Buchstabe
		   wird als Chiffrat des r angenommen.
			 der in der 
		   Liste endeSort[26] am weitesten oben steht		*/


		int Minimum=5000, Minimum2=5000;
		int Punkte=100, Punkte2=100;
		for (i=0; i<26; i++){
			// suche den Buchstaben endeSort[i] in der Liste nacheSort[26]
			for (int j=0; j<26; j++){
				if ((endeSort[i]==nacheSort[j])&&(*Permu[endeSort[i]]==-1)){
					if ((i+j)<Punkte2){	// in Liste
						if ((i+j)<Punkte){	// neues Minimum
							Punkte2=Punkte;
							Minimum2=Minimum;
							Punkte=i+j;
							Minimum=i;
						}
						else {		// neuen 2. Platz
							Punkte2=i+j;
							Minimum2=i;
						}
					}
				}
			}
		}

		// Unterscheide n und r
		// Kann durchaus noch verbessert werden.
		if (Minimum<Minimum2){
			*Permu[endeSort[Minimum]]=78;
			*Permu[endeSort[Minimum2]]=82;
		}
		else{
			*Permu[endeSort[Minimum2]]=78;
			*Permu[endeSort[Minimum]]=82;
		}


		// Erstelle eine Liste mit den häufigsten Buchstaben vor und nach dem n
		int vorn[26], vornSort[26], nachn[26], nachnSort[26];
		for (i=0; i<26; i++){
			vorn[i]=0;
			vornSort[i]=0;
			nachn[26];
			nachnSort[26];
			benutzt[i]=false;
		}
		for (i=0; i<Laenge; i++){
			if (text[i]==13){
				if (i!=0){
					if (text[i-1]!=26){
						vorn[text[i-1]]++;
					}
				}
				if (i<Laenge-1){
					if (text[i+1]!=26){
						nachn[text[i+1]]++;
					}
				}
			}
		}

		// Sortieren der Liste vorn[26]
		Maximum=-1, Maximalwert=-1;
		for (i=0; i<26; i++){
			for (int j=0; j<26; j++){
				if ((vorn[j]>Maximalwert)&&(benutzt[j]==false)){
					Maximalwert=ende[j];
					Maximum=j;
				}
			}
			vornSort[i]=Maximum;
			benutzt[Maximum]=true;
			Maximalwert=-1;
		}

		// Sortieren der Liste nachn[26]
		for (i=0; i<26; i++){
			benutzt[i]=false;
		}
		Maximum=-1, Maximalwert=-1;
		for (i=0; i<26; i++){
			for (int j=0; j<26; j++){
				if ((nachn[j]>Maximalwert)&&(benutzt[j]==false)){
					Maximalwert=ende[j];
					Maximum=j;
				}
			}
			nachnSort[i]=Maximum;
			benutzt[Maximum]=true;
			Maximalwert=-1;
		}


		/* Bestimme das i als den Buchstaben, der in den Listen
		   voreSort[26] und nacheSort[26] und vornSort[26] am "weitesten oben steht".		*/

		Punkte=100;
		for (i=0; i<26; i++){
			// suche den Buchstaben voreSort[i] in der Liste nacheSort[26]
			for (int j=0; j<26; j++){
				if ((voreSort[i]==nacheSort[j])&&(*Permu[voreSort[i]]==-1)){
					for (int k=0; k<26; k++){
						if (voreSort[i]==vornSort[k]){
							if ((i+j+k)<=Punkte){
								Punkte=i+j+k;
								Minimum=i;
							}
						}
					}
				}
			}
		}
		if (*Permu[voreSort[Minimum]]==-1){
			*Permu[voreSort[Minimum]]=73;
		}



		// Mit der eben ermittelten (partiellen) Substitution wird
		// jetzt nach einer Lösung gesucht.
		Fortschritt=20;
		solve (0, DMax, Permu, Perm, 0, PatSet, Cipher, &MaxScore, MaxPermu, Delta);

		
	}

	///////////////////////////////////////////////////////////////////
	// Ende (erweiterte Analyse)
	///////////////////////////////////////////////////////////////////

	else{  // Option "erweiterte Analyse" wurde nicht gewählt

		/* Erster Aufruf von solve:
		   Die einzelnen Parameter bedeuten folgendes:
		   1. Parameter: aktuelle Suchtiefe (Null steht für Wurzel)
		   2. Parameter: Tiefe des Baumes
		   3. Parameter: aktuelle (partielle) Permutation (zu Beginn leer)
		   4. Parameter: Reihenfolge der Ciphertextklassen
		   5. Parameter: aktuelle Punktzahl (zu Beginn Null)
		   6. Parameter: die Ciphertextklassen
		   7. Parameter: die Pattern Sets
		*/
		Fortschritt=20;
		solve (0, DMax, Permu, Perm, 0, PatSet, Cipher, &MaxScore, MaxPermu, Delta);
	}

	// Löschen der Fortschrittsanzeige
	theApp.fs.cancel();
	while(theApp.fs.m_displayed) Sleep(100);
	
	// Anzeigen des Nachbearbeitungsfensters
	CDlgManualSubstAnalysis Dialogbox;
	if (Dialogbox.DoModal()==IDCANCEL){		// "Cancel" angeklickt
		// Belegten Speicherplatz freigeben
		free(current);
		// Den allokierten Platz für die Felder Cipher und PatSet wieder freigeben
		for (i=0; i<100; i++){
			for (j=0; j<100; j++){
				if (Cipher [i][j]!=NULL)   free (Cipher[i][j]);
			}
			for (j=0; j<50; j++){
				if (PatSet [i][j]!=NULL)   free (PatSet[i][j]);
			}
		}
		// Den allokierten Speicherplatz von Permu und MaxPermu freigeben
		for (i=0; i<26; i++){
			free (Permu[i]);
			free (MaxPermu[i]);
		}

		return 0;}
	


	// Entschlüsseln und Ausgabe des Textes
	char outfile[1024], title[1024];
	GetTmpName(outfile,"cry",".txt");

	Laenge=text.GetSize();

	LPTSTR string = new TCHAR[Laenge + 1];
	int len;

	for (len=i=0 ; i<Laenge; i++){
		if (text[i]!=26){
			if (*MaxPermu[text[i]]!=-1){
				string[len++]=(char)(*MaxPermu[text[i]]);
			}
			else {
				string[len++]=(char)text[i]+'a';}
		}
	}
	string[len]=0;


	// Den String string in einem eigenen Textfenster ausgeben
	// Kopieren von string nach char *Ausgabe2
	// Kopieren von Cstring string1 nach Char *string3
//	LPTSTR string = new TCHAR[Ausgabe.GetLength()+1];
//	_tcscpy(string, Ausgabe);		
	char *Ausgabe2=string;
	// Kopieren von char *Ausgabe2 in die Datei <outfile> (mit Hilfe der Secude Funktionen)
	OctetString help;
	help.noctets=strlen(Ausgabe2);
	help.octets=Ausgabe2;
	theApp.SecudeLib.aux_OctetString2file(&help,outfile,2);
	delete string;

	ForceReformat(outfile2, outfile, TRUE);

	// Berechnung der (Teil-)Permutation zur Anzeige im Titel
	char schluessel[27];

	for (i=0; i<26;i++)
	{
		schluessel[i] = '*';
	}
	for (i=0; i<26;i++)
	{
		if (*MaxPermu[i] != -1)
		{
			schluessel[(*MaxPermu[i])-'A'] = i+'A';
		}
	}
	schluessel[26]='\0';

	LoadString(AfxGetInstanceHandle(),IDS_STRING_POSSIBLE_PLAINTEXT_OF,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName2(title,sizeof(title),pc_str,schluessel,par->OldTitle);
	theApp.ThreadOpenDocumentFileNoMRU(outfile, title, schluessel);
//	remove(outfile);	
	remove(outfile2);

	free(current);
	// Den allokierten Platz für die Felder Cipher und PatSet wieder freigeben
	for (i=0; i<100; i++){
		for (j=0; j<100; j++){
			if (Cipher [i][j]!=NULL)   free (Cipher[i][j]);
		}
		for (j=0; j<50; j++){
			if (PatSet [i][j]!=NULL)   free (PatSet[i][j]);
		}
	}


	// Den allokierten Speicherplatz von Permu und MaxPermu freigeben
	for (i=0; i<26; i++){
		free (Permu[i]);
		free (MaxPermu[i]);
	}

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	return 0;
}

int SucheLeer (int Start, int Laenge, SymbolArray& text){
	while (Start<Laenge){
		if (text[Start]==26){
			return Start;
		}
		Start=Start+1;
	}

	// Es kommt kein Leerzeichen im Text mehr vor
	// Bearbeite das letzte Wort
	return (Laenge);
}

/* Überprüft, ob die beiden der Funktion übergebenen Wörter das
   selbe Muster (Pattern) haben.						*/
bool match (char *current, char *common){
	if (strlen(current)!=strlen(common)){
		return FALSE;
	}
	for (int l=1; l<(int)strlen(current); l++){
		for (int j=0; j<l; j++){
			if ((current[l]==current[j])&&(common[l]!=common[j])){
				return FALSE;
			}
			if ((current[l]!=current[j])&&(common[l]==common[j])){
				return FALSE;
			}
		}
	}
	return TRUE;
}

void compare_score (int *Permu[26], int *MaxScore, int score, int *MaxPermu[26]){

	// Vergleiche die übergebene Punktzahl mit der maximalen Punktzahl
	// ist die aktuelle Punktzahl höher, so ist die aktuelle Permutation
	// die im Moment wahrscheinlichste.

	if (score>*MaxScore){
		// Speichere score als neue Maximalpunktzahl
		*MaxScore=score;
		// Kopieren von Permu nach MaxPermu
		for (int i=0; i<26; i++){
			*MaxPermu[i]=*Permu[i];
		}
	}
}


/* Die Funktion konsistent erhält als Eingabe ein (partielle) Permutation Perm sowie
   zwei Strings w und x.
   Die Strings w und x induzieren ebenfalls eine partielle Permutation.
   konsistent überprüft, ob diese beiden Permutationen verträglich sind */
bool konsistent (int *Permu[26], int *PermuNeu[26], char *w, char *x){

	int i;
	for (i=0; i<26; i++){
		*PermuNeu[i]=*Permu[i];}
	for (i=0; i<(int)strlen(w); i++){
		if ((*Permu[w[i]-65]!=-1)&&(*Permu[w[i]-65]!=x[i])){
			return FALSE;}
		for (int j=0; j<26; j++){
			if (*Permu[j]==x[i]){
				if ((w[i]-65)!=j){
					return FALSE;
				}
			}
		}
		*PermuNeu[w[i]-65]=(int)x[i];
	}
	return TRUE;
}

/* Eigentliche Analyse-Funktion
   Wird rekursiv aufgerufen						*/
void solve (int Tiefe, int DMax, int *Permu[26], int Perm[], int score, char *PatSet[100][50], char *Cipher[100][100], int *MaxScore, int *MaxPermu[26], float Delta){
	
	if(theApp.fs.m_canceled)   return;
	if (Tiefe==DMax){
		compare_score(Permu, MaxScore, score, MaxPermu);
	}
	else{
		int i=0;
		int *PermuNeu[26];
		int k;

		for (k=0; k<26; k++){
			PermuNeu[k]=(int*)malloc(sizeof(int));
			*PermuNeu[k]=-1;}
		while (Cipher[Perm[Tiefe]][i]!=NULL){
			if (Tiefe==1){
				// Setze Fortschrittsanzeige neu
				Fortschritt+=Delta;
				theApp.fs.Set((int)Fortschritt);
			}
			int j=0;
			while (PatSet[Perm[Tiefe]][j]!=NULL){
				
				if (konsistent (Permu, PermuNeu, Cipher[Perm[Tiefe]][i], PatSet[Perm[Tiefe]][j])==TRUE){
					solve (Tiefe+1, DMax, PermuNeu, Perm, score+1,PatSet, Cipher, MaxScore, MaxPermu, Delta);
				}
				j++;
			}
			i++;
		}
		if (Tiefe==1){
			// Setze Fortschrittsanzeige neu
			Fortschritt+=Delta;
			theApp.fs.Set((int)Fortschritt);
		}
		if (score==0){
			Fortschritt+=(float)(40.0/(float)DMax);
			theApp.fs.Set((int)Fortschritt);
		}
		solve (Tiefe+1, DMax, Permu, Perm, score, PatSet, Cipher, MaxScore, MaxPermu, Delta);
		// Den allokierten Speicherplatz von PermuNeu freigeben
		for (k=0; k<26; k++){
			free (PermuNeu[k]);
		}
	}
}


// =====================================================================================
// Homophone encryption:
// 
// Jan Blumenstein & Henrik Koy (March 2001)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//
// -------------------------------------------------------------------------------------

void HomophoneAsc(const char *infile, const char *OldTitle)
{
	if ( !CheckAlphabet() ) return;
	SymbolArray text(AppConv);
	text.Read(infile);
	if ( !CheckTextSize( text ) ) return;
	
	char inbuffer[buffsize+3];
	CDlgKeyHomophone DH;
	// DH.DeactivateDecryptionButton = TRUE;
	for (int i=0; ; i++ ) {
		DH.c_SourceFile[i] = infile[i];
		if (infile[i] == 0) break;
	}

	ifstream in(infile, ios::binary | ios::in);	
	in.read(inbuffer,buffsize);

	CAppDocument *NewDoc;

	if(IDOK!=DH.DoModal()) 
	{
		theApp.TextOptions.getAlphabet() = DH.m_AlphabetBackup;
		in.close();
		return;
	}
	theApp.TextOptions.getAlphabet() = DH.m_AlphabetBackup;

// Routine zur Homophonen Verschlüsselung
	char outbuffer[17000];
	long outbuffsize;
	char outfile[1024],title[1024];
	int value;
	GetTmpName(outfile,"cry",".hex");
	ofstream out(outfile, ios::binary | ios::out );

	unsigned char	* p_value = (unsigned char*)&value;
    char		      residuum = 0;
	unsigned char     offsetResiduum = 0;
	int               bitLength = DH.HB.LogKeySize( 2 );

	if(true==DH.Get_crypt())			// Verschlüsselung
	{
		while(in.gcount())
		{
			outbuffsize=0;
			char buff = 0;
			bool umlautFlag = FALSE;
			for (int i=0;i<in.gcount(); )
			{		
				if ( DH.HB.GetKeyType() == HOM_ENC_TXT )
				{
					if ( DH.m_encodeUmlauts && buff == 0 )
					{
						switch ( (char)inbuffer[i] ) {
						case 'ä': inbuffer[i] = 'a'; buff = 'e'; umlautFlag = true;
							break;
						case 'ö': inbuffer[i] = 'o'; buff = 'e'; umlautFlag = true;
							break;
						case 'ü': inbuffer[i] = 'u'; buff = 'e'; umlautFlag = true;
							break;
						case 'ß': inbuffer[i] = 's'; buff = 's'; umlautFlag = true;
							break;
						case 'Ä': inbuffer[i] = 'A'; buff = 'e'; umlautFlag = true;
							break;
						case 'Ö': inbuffer[i] = 'O'; buff = 'e'; umlautFlag = true;
							break;
						case 'Ü': inbuffer[i] = 'U'; buff = 'e'; umlautFlag = true;
							break;
						}					
						value=DH.HB.Encrypt((unsigned char)inbuffer[i]);					
					}

					if ( !buff )
					{	
						value=DH.HB.Encrypt((unsigned char)inbuffer[i]);
						i++;
					}
					else if ( umlautFlag ) 
					{
						umlautFlag = false;
					}
					else
					{
						value=DH.HB.Encrypt((unsigned char)buff);
						buff = 0;
						i++;
					}
				}
				else
				{
					value = DH.HB.Encrypt((unsigned char)inbuffer[i++]);
				}

				if ( value >= 0 )
				{
					value <<= offsetResiduum;
					value |= residuum;
					offsetResiduum += bitLength;

					int j;
					for (j=0; offsetResiduum >= 8; j++ )
					{
						outbuffer[outbuffsize]= p_value[j];
						outbuffsize++;
						offsetResiduum -= 8;
					}
					if ( offsetResiduum ) 
					{
						residuum = p_value[j];
					}
					else
					{
						residuum = 0;
					}
				}
			}

			out.write(outbuffer,outbuffsize);
			in.read(inbuffer,buffsize);
		}
		if ( residuum ) 
			out << residuum; 
	}
	else								// Entschlüsselung
	{
		DH.HB.Make_dec_table();
		value = 0;
		unsigned char offsetResiduumPrev = 0;
		int j = 0;

		while(in.gcount())
		{
			outbuffsize=0;
			for (int i=0;i<in.gcount();)
			{
				p_value[j] = inbuffer[i];
				i++; j++; offsetResiduum += 8;
				while ( offsetResiduum >= bitLength )
				{
					value = (value << offsetResiduumPrev) + residuum;
					int val = value % (1 << bitLength);
					outbuffer[outbuffsize]=DH.HB.Decrypt( val );
					outbuffsize++;
					offsetResiduum -= bitLength;
					residuum = value >> bitLength;

					value = j = 0;
					offsetResiduumPrev = offsetResiduum;
				}
			}
			out.write(outbuffer,outbuffsize);
			in.read((char *)inbuffer,buffsize);
		}
	}

	in.close();
 	out.close();

	NewDoc = theApp.OpenDocumentFileNoMRU(outfile,DH.HB.GetKeyStr());
	remove(outfile);
	if(NewDoc) 
	{
		if(true==DH.Get_crypt())
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		}
		else
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		}
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HOMOPHONE,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,"");
		NewDoc->SetTitle(title);
	}

	HIDE_HOUR_GLASS
} // end Hompohone Asc

// ======================================================================================


#if 0
void HomophoneHex(const char *infile, const char *OldTitle)
{
	CWaitCursor WCursor;

	if ( !CheckAlphabet() ) return;
    SymbolArray text(IdConv);
	text.Read(infile);
	if ( !CheckTextSize( text ) ) return;

	WCursor.Restore();	
	unsigned char inbuffer[buffsize];

	CDlgKeyHomophone DH;
	for (int i=0; ; i++ ) {
		DH.c_SourceFile[i] = infile[i];
		if (infile[i] == 0) break;
	}

	ifstream in(infile, ios::binary | ios::in );	
	in.read((char *)inbuffer,buffsize);

	CAppDocument *NewDoc;

	if(IDOK!=DH.DoModal()) 
	{
		theApp.TextOptions.getAlphabet() = DH.m_AlphabetBackup;
		in.close();
		return;
	}
	theApp.TextOptions.getAlphabet() = DH.m_AlphabetBackup;

// Routine zur Homophonen Verschlüsselung
	char outbuffer[4096];
	long outbuffsize;
	char outfile[1024],title[1024];
	int value;
	GetTmpName(outfile,"cry",".hex");
	ofstream out(outfile, ios::binary | ios::out );

	unsigned char	* p_value = (unsigned char*)&value;
    char		      residuum = 0;
	unsigned char     offsetResiduum = 0;
	int               bitLength = DH.HB.LogKeySize( 2 );

	if(true==DH.Get_crypt())			// Verschlüsselung
	{


		while(in.gcount())
		{
			outbuffsize=0;
			for(int i=0;i<in.gcount();i++)
			{
				value=DH.HB.Encrypt((unsigned char)inbuffer[i]);
				if(value>=0)
				{
					outbuffer[outbuffsize]=value;
					outbuffsize++;				
				}
			}
			out.write(outbuffer,outbuffsize);
			in.read((char *)inbuffer,buffsize);
		}
	}
	else								// Entschlüsselung
	{
		DH.HB.Make_dec_table();

		while(in.gcount())
		{
			outbuffsize=0;
			for (int i=0;i<in.gcount();)
			{
				value = 0;
				unsigned char offsetResiduumPrev = offsetResiduum;
				for ( int j=0; offsetResiduum < bitLength; )
				{
					p_value[j] = inbuffer[i];
					i++; j++; offsetResiduum += 8;
				}
				value = (value << offsetResiduumPrev) + residuum;
				int val = value % (1 << bitLength);
				outbuffer[outbuffsize]=DH.HB.Decrypt( val );
				outbuffsize++;
				offsetResiduum -= bitLength;
				residuum = value >> bitLength;
			}
			out.write(outbuffer,outbuffsize);
			in.read((char *)inbuffer,buffsize);
		}
	}
	in.close();
 	out.close();

	NewDoc = theApp.OpenDocumentFileNoMRU(outfile,DH.HB.GetKeyStr());
	remove(outfile);
	if(NewDoc) 
	{
		if(true==DH.Get_crypt())
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		}
		else
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		}
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HOMOPHONE,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,"");
		NewDoc->SetTitle(title);
	}

	HIDE_HOUR_GLASS
} // end Hompohone Hex
#endif


// =====================================================================================
// NGram Analyse:
// 
// Henrik Koy (March 2001)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//
// -------------------------------------------------------------------------------------

void NGramAsc(const char *infile, const char *OldTitle)
{
	SHOW_HOUR_GLASS

    char      * buffer;
	CFile f( infile, CFile::modeRead );
	unsigned long fLen = (unsigned long)((f.GetLength() < 1048576) ? f.GetLength() : 1048576);  //  2^20 bytes restriction restriction
	buffer = new char[fLen+1];
	f.Read( (void *)buffer, fLen );	
	CDlgNGramAnaylsis DiaNGram;
	DiaNGram.LoadText(buffer, fLen, OldTitle, 0);

    DiaNGram.DoModal();

    if ( DiaNGram.b_saveNGramList() )
	{
		CAppDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU(DiaNGram.outfile);
		remove(DiaNGram.outfile);
		if (NewDoc) {
			char title[128], method[20]; 
			switch ( DiaNGram.m_N_NGram )  {
			case 0: LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_HISTOGRAM,pc_str,STR_LAENGE_STRING_TABLE);
				strcpy( method, pc_str );
				break;
			case 1: LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_DIGRAM,pc_str,STR_LAENGE_STRING_TABLE);
				strcpy( method, pc_str );
				break;
			case 2: LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_TRIGRAM,pc_str,STR_LAENGE_STRING_TABLE);
				strcpy( method, pc_str );
				break;
			case 3:  LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_NGRAM,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf( method, pc_str, DiaNGram.m_NrNGram );
				break;
			}
			LoadString(AfxGetInstanceHandle(),IDS_TITLE_NGRAMANALYSIS,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName2(title,sizeof(title),pc_str,OldTitle,method);
			NewDoc->SetTitle(title);
		}
	}

	HIDE_HOUR_GLASS
}

void NGramBin(const char *infile, const char *OldTitle)
{
	SHOW_HOUR_GLASS

    char      * buffer;	
	CFile f( infile, CFile::modeRead );
	unsigned long fLen = (unsigned long)((f.GetLength() < 1048576) ? f.GetLength() : 1048576);  // 2^18 bytes restriction
	buffer = new char[fLen+1];
	f.Read( (void *)buffer, fLen );

	CDlgNGramAnaylsis DiaNGram;
	DiaNGram.LoadText(buffer, fLen, OldTitle, 1);

	DiaNGram.DoModal();

    if ( DiaNGram.b_saveNGramList() )
	{
		CAppDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU(DiaNGram.outfile);
		remove(DiaNGram.outfile);
		if (NewDoc) {
			char title[128], method[20]; 
			switch ( DiaNGram.m_N_NGram )  {
			case 0: LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_HISTOGRAM,pc_str,STR_LAENGE_STRING_TABLE);
				strcpy( method, pc_str );
				break;
			case 1: LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_DIGRAM,pc_str,STR_LAENGE_STRING_TABLE);
				strcpy( method, pc_str );
				break;
			case 2: LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_TRIGRAM,pc_str,STR_LAENGE_STRING_TABLE);
				strcpy( method, pc_str );
				break;
			case 3:  LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_NGRAM,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf( method, pc_str, DiaNGram.m_NrNGram );
				break;
			}
			LoadString(AfxGetInstanceHandle(),IDS_TITLE_NGRAMANALYSIS,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName2(title,sizeof(title),pc_str,OldTitle,method);
			NewDoc->SetTitle(title);
		}
	}

	HIDE_HOUR_GLASS
}

// =============================================================
// == permutation cryptology 
// == Peer Wichmann July 2001
void DoPerm(char *dest, char *src, int len, int *p, int plen, int Zin, int Zout)
{		
	int i, k, pt;
	int Zeilenzahl, LetzteZLen;
	int pres[MAX_PERM_LENGTH], sstart[MAX_PERM_LENGTH], slen[MAX_PERM_LENGTH];

	Zeilenzahl = len / plen;
	LetzteZLen = len % plen;
	for(i=0;i<LetzteZLen;i++) slen[i] = Zeilenzahl+1;
	for(i=LetzteZLen;i<plen;i++) slen[i] = Zeilenzahl;
	sstart[0]=0;
	for(i=1;i<plen;i++) sstart[i] = sstart[i-1] + slen[i-1];

	memcpy(pres, p, plen * sizeof(int));
	for(i=k=0;i<plen;i++)
		if(pres[k] >= LetzteZLen)
			memcpy(pres+k, pres+k+1, sizeof(int) * (plen - i));
		else
			k++;


	if(Zin == 0) // zeilenweise einlesen
		if(Zout == 1) // zeilenweise einlesen, spaltenweise auslesen
			for(pt=i=0;i<plen;i++)
				for(k=p[i];k<len;k+=plen)
					dest[pt++]=src[k];
		else {//zeilenweise einlesen, zeilenweise auslesen
			for(pt=i=0;i<Zeilenzahl;i++,pt+=plen) // ganze Zeilen
				for(k=0;k<plen;k++)
					dest[pt+p[k]]=src[pt+k];
			for(i=0;i<LetzteZLen;i++) // letzte Zeile
				dest[pt+pres[i]]=src[pt+i];
		}
	else	// spaltenweise einlesen
		if(Zout == 1) // spaltenweise einlesen, spaltenweise auslesen
			for(pt=i=0;i<plen;i++) {
				memcpy(dest+pt, src+sstart[p[i]], slen[p[i]]);
				pt += slen[p[i]];
			}
		else {//spaltenweise einlesen, zeilenweise auslesen 
			for(pt=i=0;i<Zeilenzahl;i++)
				for(k=0;k<plen;k++)
					dest[pt++]=src[sstart[p[k]]+i];
			for(i=0; i<LetzteZLen; i++) // letzte Zeile
				dest[pt++]=src[sstart[pres[i]]+Zeilenzahl];
		}
}

void DoInvPerm(char *dest, char *src, int len, int *p, int plen, int Zin, int Zout)
{
	int i, k, pt;
	int Zeilenzahl, LetzteZLen;
	int pres[MAX_PERM_LENGTH], sstart[MAX_PERM_LENGTH], slen[MAX_PERM_LENGTH];

	Zeilenzahl = len / plen;
	LetzteZLen = len % plen;
	for(i=0;i<LetzteZLen;i++) slen[i] = Zeilenzahl+1;
	for(i=LetzteZLen;i<plen;i++) slen[i] = Zeilenzahl;
	sstart[0]=0;
	for(i=1;i<plen;i++) sstart[i] = sstart[i-1] + slen[i-1];

	memcpy(pres, p, plen * sizeof(int));
	for(i=k=0;i<plen;i++)
		if(pres[k] >= LetzteZLen)
			memcpy(pres+k, pres+k+1, sizeof(int) * (plen - i));
		else
			k++;


	if(Zin == 0) // zeilenweise einlesen
		if(Zout == 1) // zeilenweise einlesen, spaltenweise auslesen
			for(pt=i=0;i<plen;i++)
				for(k=p[i];k<len;k+=plen)
					dest[k]=src[pt++];
		else {//zeilenweise einlesen, zeilenweise auslesen
			for(pt=i=0;i<Zeilenzahl;i++,pt+=plen) // ganze Zeilen
				for(k=0;k<plen;k++)
					dest[pt+k]=src[pt+p[k]];
			for(i=0;i<LetzteZLen;i++) // letzte Zeile
				dest[pt+i]=src[pt+pres[i]];
		}
	else	// spaltenweise einlesen
		if(Zout == 1) // spaltenweise einlesen, spaltenweise auslesen
			for(pt=i=0;i<plen;i++) {
				memcpy(dest+sstart[p[i]], src+pt, slen[p[i]]);
				pt += slen[p[i]];
			}
		else {//spaltenweise einlesen, zeilenweise auslesen // TBD
			for(pt=i=0;i<Zeilenzahl;i++)
				for(k=0;k<plen;k++)
					dest[sstart[p[k]]+i]=src[pt++];
			for(i=0; i<LetzteZLen; i++) // letzte Zeile
				dest[sstart[pres[i]]+Zeilenzahl]=src[pt++];
		}
}

void PermutationAsc(const char *infile, const char *OldTitle)
{
    char outfile[1024], key[1024], title[1024];
	CFile datei(infile, CFile::modeRead);
	bool laenge_groesser_0 = FALSE;
	char c;
	char *b1=NULL, *b2=NULL, *b3, *CPlayfairAlphabet;
	unsigned long l1, l2, i, ignoreCase;;

	ASSERT(datei.GetLength() < ULONG_MAX);
	l1 = (unsigned long)datei.GetLength();
	b1 = (char *) malloc(l1+1);
	l1 = datei.Read(b1, l1);
	datei.Close();
	b1[l1]=0;
	CPlayfairAlphabet = theApp.TextOptions.getAlphabet().GetBuffer(0);
	ignoreCase = theApp.TextOptions.getIgnoreCase();
	for(l2=i=0;i<l1;i++) {
		c = b1[i];
		if(ignoreCase && 'a'<=c && c<='z')
			c += 'A' - 'a';
		if(strchr(CPlayfairAlphabet, c))
			b1[l2++] = c;
	}
	theApp.TextOptions.getAlphabet().ReleaseBuffer();
	b1[l2]=0;
	if(l2<1) {
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		free(b1);
		return;
	}
			
	// Dialogbox zur Schlüsseleingabe anzeigen
	CDlgKeyPermutation Perm;

    if (Perm.DoModal()==IDOK)
	{
		b2 = (char *) malloc(l2+1);

		if(Perm.m_Dec) 
		{
			if(Perm.m_P2len)
			{
				if ( !Perm.m_Invert )
				{
					DoInvPerm(b2, b1, l2, Perm.m_P2inv, Perm.m_P2len, Perm.m_P2InSeq ^ Perm.m_P2Perm  ^ 1, Perm.m_P2OutSeq ^ Perm.m_P2Perm  ^ 1);
					DoInvPerm(b1, b2, l2, Perm.m_P1inv, Perm.m_P1len, Perm.m_P1InSeq ^ Perm.m_P1Perm  ^ 1, Perm.m_P1OutSeq ^ Perm.m_P1Perm  ^ 1);
					b3 = b1;
				}
				else
				{
					DoInvPerm(b2, b1, l2, Perm.m_P2, Perm.m_P2len, Perm.m_P2InSeq ^ Perm.m_P2Perm  ^ 1, Perm.m_P2OutSeq ^ Perm.m_P2Perm  ^ 1);
					DoInvPerm(b1, b2, l2, Perm.m_P1, Perm.m_P1len, Perm.m_P1InSeq ^ Perm.m_P1Perm  ^ 1, Perm.m_P1OutSeq ^ Perm.m_P1Perm  ^ 1);
					b3 = b1;
				}
			}
			else
			{
				if ( !Perm.m_Invert )
				{
					DoInvPerm(b2, b1, l2, Perm.m_P1inv, Perm.m_P1len, Perm.m_P1InSeq ^ Perm.m_P1Perm  ^ 1, Perm.m_P1OutSeq ^ Perm.m_P1Perm  ^ 1);
					b3 = b2;
				}
				else
				{
					DoInvPerm(b2, b1, l2, Perm.m_P1, Perm.m_P1len, Perm.m_P1InSeq ^ Perm.m_P1Perm  ^ 1, Perm.m_P1OutSeq ^ Perm.m_P1Perm  ^ 1);
					b3 = b2;
				}
			}
		}
		else // Perm Dec == FALSE
		{
			if ( !Perm.m_Invert )
				DoPerm(b2, b1, l2, Perm.m_P1inv, Perm.m_P1len, Perm.m_P1InSeq ^ Perm.m_P1Perm  ^ 1, Perm.m_P1OutSeq ^ Perm.m_P1Perm  ^ 1);
			else
				DoPerm(b2, b1, l2, Perm.m_P1, Perm.m_P1len, Perm.m_P1InSeq ^ Perm.m_P1Perm  ^ 1, Perm.m_P1OutSeq ^ Perm.m_P1Perm  ^ 1);

			if(Perm.m_P2len)
			{
				b3 = b1;
				if ( !Perm.m_Invert )
					DoPerm(b1, b2, l2, Perm.m_P2inv, Perm.m_P2len, Perm.m_P2InSeq ^ Perm.m_P2Perm  ^ 1, Perm.m_P2OutSeq ^ Perm.m_P2Perm  ^ 1);
				else
					DoPerm(b1, b2, l2, Perm.m_P2, Perm.m_P2len, Perm.m_P2InSeq ^ Perm.m_P2Perm  ^ 1, Perm.m_P2OutSeq ^ Perm.m_P2Perm  ^ 1);
			}
			else b3 = b2;
		}


		GetTmpName(outfile,"cry",".tmp");
		
		CFile outf(outfile,CFile::modeWrite | CFile::modeCreate);
		outf.Write(b3,l2);
		outf.Close();
		Reformat(infile,outfile, FALSE);

		char *Invert = new char[];
		(Perm.m_Invert) ? Invert= INV_TOKEN : Invert="";

		if(Perm.m_P2len)
			sprintf(key,"%s;%s %s%s%i,%i,%i,%i,%i,%i", Perm.m_Perm1, Perm.m_Perm2, PARAM_TOKEN, Invert,
					Perm.m_P1InSeq, Perm.m_P1Perm, Perm.m_P1OutSeq,
					Perm.m_P2InSeq, Perm.m_P2Perm, Perm.m_P2OutSeq);
		else
			sprintf(key,"%s %s%s%i,%i,%i,%i,%i,%i", Perm.m_Perm1, PARAM_TOKEN, Invert,
					Perm.m_P1InSeq, Perm.m_P1Perm, Perm.m_P1OutSeq,
					Perm.m_P2InSeq, Perm.m_P2Perm, Perm.m_P2OutSeq);
		CAppDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile,key);
		remove(outfile);	
		if(NewDoc) 
		{
			if(Perm.m_Dec)
				LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			else
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,key);
			NewDoc->SetTitle(title);
		}
	}

	if(b1) free(b1);
	if(b2) free(b2);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Hashwert einer Datei berechnen, ohne dass die Datei selbst in den Dialog geöffnet werden 
// muß. (Henrik Koy: Maerz. 2002)

void HashOfAFile()
{
	char fname[257], ftitle[128];
 
// == load INPUT
	{		
		// Initialisierung des File-Dialogs:
		CString sFileFilter;
		CString sDefName("*.*");
		CString sTitle;
		DWORD   dwFlags(OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST);
		sFileFilter.LoadString(IDS_OPEN_DOCUMENT_FILTER);
		sTitle.LoadString(IDS_OPENHASHOFAFILE);
		CFileDialog* doc;
		doc = new CFileDialog(TRUE, NULL, sDefName, dwFlags, sFileFilter);
		doc->m_ofn.lpstrTitle = sTitle;

		if(doc->DoModal()==IDOK)// Aufruf des File-Dialogs
		{			
			strcpy(ftitle, LPCTSTR (doc->GetFileName()));
			strcpy(fname, LPCTSTR (doc->GetPathName()));
			delete doc;
		}
		else
		{
			delete doc;
			return;
		}
	}
	CDlgSelectHashFunction Dlg;
	if ( Dlg.DoModal() == IDOK )
	{
		hash(fname, ftitle, Dlg.m_selectedHashFunction+1 );
	}
}


//####################################
//Myriam Zeuner, Projekt Hashdemo

void Hashdemo(const char *infile,const char *OldTitle)
{
	long FileSize;
	{
		struct stat *obj;
		obj = new (struct stat);
		int result = stat((const char*)infile,obj);
		FileSize = obj->st_size;
		delete obj;
		if ( result != 0 )
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_Hashdemo_FileNotFound,pc_str,100);
			AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
			return;
		}
	}
	if ( FileSize > 16000 )
	{
		CString msg;
		msg.Format(IDS_STRING_Hashdemo_DateilaengeZuLang,MAX_LAENGE_STRTEXT);
		AfxMessageBox((LPCTSTR)msg,MB_ICONEXCLAMATION,IDD_HASH_DEMO + 0x20000UL - 0x30000);	
		FileSize = 16000;
	}

	CDlgHashDemo HashDlg;
	if ( 0 == HashDlg.loadData(infile, OldTitle, FileSize) )
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_Hashdemo_KeineWerteGefunden,pc_str,100);
		AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
		return;
	}


	AfxInitRichEdit(); // GRRMPF
	HashDlg.DoModal();
	// Die Instanz der Klasse (Der Dialog) wird modal aufgerufen

}

//crypt.cpp
void SignatureTutorial(const char *infile, const char* OldTitle)
{
	if(CDlgSignatureDemo* SigDemo = new CDlgSignatureDemo)
	{
		SigDemo->InitDocument( infile, OldTitle );
		SigDemo->DoModal();
		delete SigDemo;
	}
}


//Christine Stötzel, September 2004
//Message Authentication Code
void CreateMac(const char *infile, const char *OldTitle)
{
	long FileSize;
	{
		struct stat *obj;	
		obj = new (struct stat);
		//obj speichert Statusinformationen über infile
		int result = stat((const char*)infile, obj);
		//FileSize = Größe der Datei in Bytes
		FileSize = obj->st_size;
		delete obj;
		//wenn ein Fehler zurückgegeben wurde
		if ( result != 0 )
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_Hashdemo_FileNotFound,pc_str,100);
			AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
			return;
		}
	}
	if ( FileSize > 16000 )
	{
		LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_ZuLang, pc_str, 120);
		AfxMessageBox(pc_str, MB_ICONEXCLAMATION|MB_OK);	
		FileSize = 16000;
	}
	
	OctetString *TextFile;
	TextFile = new OctetString;
	//noctets enthält die Anzahl der Bytes, octets ist ein Feld er entsprechenden Größe
	TextFile->noctets = FileSize;
	TextFile->octets  = new char [FileSize+1];
	//die aktuelle Datei kann zum Lesen geöffnet werden
	CFile text(infile, CFile::modeRead);
	//liest Daten aus der verknüpften Datei in einen Puffer
	text.Read((void *)TextFile->octets, FileSize);
	text.Close();
	//Endekennung für das letzte Element
	TextFile->octets[FileSize] = '\0';
	if (strlen(TextFile->octets) == 0)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_Hashdemo_KeineWerteGefunden,pc_str,100);
		AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
		return;
	}
	CDlgHMAC macdlg;
	//das file wird im CString strText des Dialogs gespeichert
	macdlg.strText = CString((char*)TextFile->octets);
	macdlg.DoModal();
	delete []TextFile->octets;
	delete TextFile;
}

BOOL Rot13CaesarAsc(SymbolArray & text, const char *infile)
{
// == load INPUT
	if ( !CheckAlphabet() ) 
	{
		return FALSE;
	}
	LoadText( infile, text );
	if ( !CheckTextSize( text ) )
	{
		return FALSE;
	}
	return TRUE;
}

void Rot13CaesarAscFinish(SymbolArray & text, const char * infile, char * sKey, BOOL bDecrypt, const char *OldTitle, UINT type, bool keyOffsetZero)
{
	char outfile[1024];
	SymbolArray Key(AppConv);
	
	// make sure only the first character of the key is actually used as Caesar key,
	// because using the whole key including the key offset part leads to some weird behaviour
	Key.ReadString(sKey, 1);

	// handle key offset (whether A=0 or A=1)
	if(!keyOffsetZero)
		Key += 1;

// == Encryption / Decryption
	SHOW_HOUR_GLASS
	GetTmpName(outfile,"cry",".txt");
	if (bDecrypt)
	{
		text -= Key;
	}
	else
	{
		text += Key;
	}
	text.Write(outfile);
	Reformat(infile, outfile, FALSE);

// == Open the new document
	OpenNewDoc(outfile, sKey, OldTitle, type, bDecrypt);

	HIDE_HOUR_GLASS
}

void SymmetricEncryption(int AlgId, cryptProvider provider, 
						 const char* infile, const char *OldTitle,
						 int fixed_keylength)
{
	CString Title, AlgString;
	AlgString.LoadString(AlgId);
	int errorCode = 0;
	char keybuffhex[256/4+1];
	unsigned char keybuffbin[256/8];

	Title.Format(IDS_STRING_KEYINPUT_SYMMETRIC, AlgString);
    CDlgKeyHexFixedLen KeyDialog;

	if ( !fixed_keylength ) switch (AlgId)
	{
		case IDS_CRYPT_MARS:
		case IDS_CRYPT_RC6:
		case IDS_CRYPT_RIJNDAEL:
		case IDS_CRYPT_SERPENT:
		case IDS_CRYPT_TWOFISH:
			KeyDialog.Init(Title,128,256,64);
			break;
		case IDS_CRYPT_DESL:
		case IDS_CRYPT_DES_CBC:
		case IDS_CRYPT_DES_ECB:
			KeyDialog.Init(Title,64,64,64,CRYPT_PARITY_DES);
			break;
		case IDS_CRYPT_TRIPLE_DES_CBC:
		case IDS_CRYPT_TRIPLE_DES_ECB:
			KeyDialog.Init(Title,128,128,128,CRYPT_PARITY_DES);
			break;
		case IDS_CRYPT_DESX:
		case IDS_CRYPT_DESXL:
			KeyDialog.Init(Title,192,192,192,CRYPT_PARITY_DESX);
			break;
		case IDS_CRYPT_IDEA:
			KeyDialog.Init(Title,128,128,128);
			break;
		case IDS_CRYPT_RC2:
		case IDS_CRYPT_RC4:
			KeyDialog.Init(Title,8,128,8);
			break;
		default:
			ASSERT(0);
	}
	else
		KeyDialog.Init(Title,fixed_keylength,fixed_keylength,1);

	if (KeyDialog.DoModal() != IDOK) 
		return;

	unsigned char *key = (unsigned char *) KeyDialog.GetKeyBytes();
	int            keylen = KeyDialog.GetKeyByteLength();
	ASSERT(keylen <= sizeof keybuffbin);
	for(int i=0;i<keylen; i++) keybuffbin[i] = key[i];
	
	ASSERT(2*keylen + 1 <= sizeof keybuffhex);
	for(int i=0; i<keylen; i++) 
		sprintf(keybuffhex+2*i,"%02.2X",keybuffbin[i]);

	char outfile[CRYPTOOL_PATH_LENGTH];
    GetTmpName(outfile,"cry",".tmp");

	try {
		if ( KeyDialog.ModeIsDecrypt() )
		{
			errorCode = sym_decrypt(AlgId, provider, keybuffhex, keylen<<3,infile, outfile);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		}
		else
		{
			errorCode = sym_encrypt(AlgId, provider, keybuffhex, keylen<<3,infile, outfile);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		}
		char title[128];
		CAppDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.GetKeyFormatted());
		remove(outfile);
		if(NewDoc) {
			MakeNewName3(title,sizeof(title),pc_str1,AlgString,OldTitle,KeyDialog.GetKeyFormatted());
			NewDoc->SetTitle(title);
		}
	}
	catch ( CString errStr ) {
		if ( provider == SECUDE_PROVIDER )
		{
			errStr.AppendChar('\n');
			errStr.Append(theApp.SecudeLib.LASTTEXT);
		}
		AfxMessageBox(errStr, MB_ICONSTOP);
	}
}


UINT SymmetricBruteForce(PVOID p)
{
// 
	int windowlen = theApp.Options.m_BFEntropyWindow;
	int r = 0, skip_parity = 0;


	CryptPar *par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS

//  get file size
	FILE *fi = fopen(par->infile,"rb");
	fseek(fi,0,SEEK_END);
	int datalen = ftell(fi);
	fclose(fi);
	
	if(datalen < 1) 
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			HIDE_HOUR_GLASS
		par->flags |= CRYPT_DONE;
		FreePar(par);
		return r;
	}
	if(datalen > windowlen)     
		datalen=windowlen;

//	load brute force pattern
	algorithm_info *info = (algorithm_info*)par->key;
	CString AlgTitle;
	AlgTitle.LoadString(info->AlgId);

	CDlgBruteForceAES KeyDialog;

//	Skip parity bits during enumeration (i.e. DES variants)
	if ( info->AlgId == IDS_CRYPT_DES_CBC ||
		 info->AlgId == IDS_CRYPT_DES_ECB ||
		 info->AlgId == IDS_CRYPT_TRIPLE_DES_CBC ||
		 info->AlgId == IDS_CRYPT_TRIPLE_DES_ECB ||
		 info->AlgId == IDS_CRYPT_DESL )
		skip_parity = CRYPT_PARITY_DES;
	else if ( info->AlgId == IDS_CRYPT_DESX || info->AlgId == IDS_CRYPT_DESXL )
		skip_parity = CRYPT_PARITY_DESX;
	else
		skip_parity = CRYPT_PARITY_NONE;

	if(KeyDialog.Display(AlgTitle.GetBuffer(),par->keylenmin,par->keylenmax,par->keylenstep,skip_parity)!=IDOK)
	{
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			HIDE_HOUR_GLASS
		par->flags |= CRYPT_DONE;
		FreePar(par);
		return r;
	}

//	initialize brute force
	int key_bitlength = KeyDialog.GetBinlen();

	// load ciphertext 
	sym_brute *brute;
	{
		char *cipher;
		cipher = (char*)malloc(datalen);
		fi = fopen(par->infile,"rb");
		int inputSize = fread(cipher,1,datalen,fi);
		fclose(fi);
		// initialise ...
		brute = init_sym_brute(info->AlgId, info->provider, key_bitlength, cipher, datalen);
		free(cipher);
	}

//  start progress dialog
	CString title;
	title.Format(IDS_STRING_ANALYSE_ON,AlgTitle);
	if(par->flags & CRYPT_DO_PROGRESS)
	{
		CString message;
		message.Format(IDS_STRING_MSG_SEARCHING_COMPLETE,KeyDialog.GetSearchBitLen());
		theApp.fs.setModelTitleFormat(&KeyDialog,title,message);
		theApp.fs.Display();
	}

//  Build alphabet set
	int alphaSet[256];
	for (int i=0; i<256; i++)
	{
		switch ( theApp.Options.i_alphabetOptions ) {
			case 0: alphaSet[i] = 1;
				break;
			case 1: alphaSet[i] = ( i >= 32 ) ? 1 : 0;
				break;
			case 2: alphaSet[i] = ( 0 <= theApp.TextOptions.getAlphabet().Find((char)i) ) ? 1 : 0;
				break;
		}
		if ( i == (int)'\0' || i == (int)'\n' || i == (int)'\r' || i == (int)'\t' )
			alphaSet[i] = 1;
	}

//	precomputations for fast entropy calculation
	double entr;
	double *xlogx = new double[datalen + 1];
	if (!xlogx) return 0;
	xlogx[0] = 0.0;
	int i;
	for (i = 1; i <= datalen; i++) 
		xlogx[i] = -1.0 * i * log(i/double(datalen))/log(2.0);


//  brute force
#define BRUTEFORCE_HEAPSIZE 50
	CBruteForceHeap candidates;
	candidates.init( key_bitlength/8, datalen, BRUTEFORCE_HEAPSIZE);

	int pos=0;
	int distr[256];
	theApp.fs.startClock();

	while (KeyDialog.Step())    // next key
	{           
		if(par->flags & CRYPT_DO_PROGRESS)
		{
			if(theApp.fs.m_canceled)
			{
				// theApp.fs.cancel();
				break;
			}
		}

 		char *plain = brute->decrypt(KeyDialog.GetData());

		if ( theApp.Options.i_alphabetOptions )
		{
			BOOL decryptionResult_invalid = FALSE;
			for (int i=0; i<brute->decrypted_bytes; i++)
				if (!alphaSet[(int)plain[i]])
				{
					decryptionResult_invalid = TRUE;
					break;
				}
			if ( decryptionResult_invalid )
				continue;
		}

		//	compute entropy
		memset(distr,0,sizeof(distr));
		for(i=0;i<brute->decrypted_bytes;i++)
			distr[(unsigned char) plain[i]]++;
		entr = 0.0;
		i = 0; 
		while (i<256) {
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
		}
		entr /= (double)datalen;

		if ( candidates.check_add( entr ) )
			candidates.add_candidate( entr, KeyDialog.GetData(), plain, brute->decrypted_bytes );
	}

	if(par->flags & CRYPT_DO_PROGRESS) theApp.fs.cancel();
	WaitForSingleObject( theApp.fs.pEvent.m_hObject, INFINITE );
	//theApp.fs.m_displayed = false;

	if ( !candidates.heapsize )
	{
		Message(IDS_STRING_NO_VALID_KEYS_FOUND, MB_ICONINFORMATION);
	}
	else
	{
		candidates.sort();
		CListResults dlgResults;
		dlgResults.LoadList( candidates.list, candidates.heapsize );
		// TODO load list
		if ( IDOK == dlgResults.DoModal() )
		{
			char outfile[CRYPTOOL_PATH_LENGTH];
			char line[CRYPTOOL_PATH_LENGTH];
			GetTmpName(outfile,"cry",".tmp");
			try {
				sym_decrypt(info->AlgId, info->provider, dlgResults.get_keyhex(), key_bitlength, par->infile, outfile);
				
				LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOMATIC_ANALYSE,pc_str,STR_LAENGE_STRING_TABLE);
				MakeNewName3(line,sizeof(line),pc_str, AlgTitle, par->OldTitle, dlgResults.get_keyhex());
				theApp.ThreadOpenDocumentFileNoMRU(outfile,line,dlgResults.get_keyhex());
			}
			catch ( CString errStr ) {
				if ( info->provider == SECUDE_PROVIDER )
				{
					errStr.AppendChar('\n');
					errStr.Append(theApp.SecudeLib.LASTTEXT);
				}
				AfxMessageBox(errStr, MB_ICONSTOP);
			}
		}
	}

	delete brute;

	par->flags |= CRYPT_DONE;
	FreePar(par);

	return r;
}

//
// TODO due to lack of time: make sure dynamically allocated memory is freed 
//
// Rail Fence encryption (part of the simple transpositions dialog)
// RETURN VALUES:		1 (success), -1 (invalid key), -2 (invalid file handle)
int RailFenceEncryption(const char *infile, const char *oldTitle, int key, int offset, bool encrypt) {
	// create a handle for the input file
	std::ifstream fileInput;
	fileInput.open(infile);
	if(!fileInput) return -2;

	// store the contents of the file in bufferString
	std::string bufferString;
	char buffer[4096 + 1];
	memset(buffer, 0, 4096 + 1);
	do {
		memset(buffer, 0, 4096 + 1);
		fileInput.read(buffer, 4096);
		bufferString.append(buffer);
	}
	while(!fileInput.eof());
	fileInput.close();

	// ignore non-alphabet characters
	CString bufferStringValid;
	for(unsigned int i=0; i<bufferString.length(); i++) {
		if(theApp.TextOptions.getAlphabet().Find(bufferString[i]) != -1) {
			bufferStringValid.AppendChar(bufferString[i]);
		}
	}
	bufferString = bufferStringValid;

	// IMPORTANT: the key is invalid if it is "1" or >= the length of the clear text
	if(key <= 1 || key >= (int)bufferString.length()) {
		return -1;
	}

	// *** BEGIN ENCRYPTION/DECRYPTION PROCESS ***
	int textLength = bufferString.length();
	char *clearText = new char[textLength + offset + 1];
	memset(clearText, 0, textLength + offset + 1);
	char *cipherText = new char[textLength + offset + 1];
	memset(cipherText, 0, textLength + offset + 1);

	// ******************
	// *** ENCRYPTION ***
	// ******************
	if(encrypt) {
		// the period of the encryption
		int n = 2 * key - 2; 
		if(offset > 0) offset = (offset % n);
		if(offset < 0) offset = (offset % n) + n;
		// get the clear text and respect leading zeros (thus, the offset variable)
		memcpy(clearText + offset, bufferString.c_str(), textLength);
		// now, process all characters of the clear text
		int charactersProcessed = 0;
		for(int d=0; d<=n/2; d++) {
			for(int j=0; j<textLength+offset; j++) {
				if(j%n == d || j%n == n-d) {
					cipherText[charactersProcessed++] = clearText[j];
				}	
			}
		}
		// remove zeros
		char *cipherTextTemp = new char[textLength + 1];
		memset(cipherTextTemp, 0, textLength + 1);
		for(int i=0; i<textLength+offset; i++) {
			if(cipherText[i] != 0) {
				strncat(cipherTextTemp, cipherText + i, 1);
			}
		}
		// store the result in "cipherText"
		memset(cipherText, 0, textLength + 1);
		memcpy(cipherText, cipherTextTemp, textLength);
	}
	// ******************
	// *** DECRYPTION ***
	// ******************
	else {
		// the period of the encryption
		int n = 2 * key - 2;
		offset = (offset % n);
		if(offset < 0) offset = (offset + n);
		// get the cipher text
		memcpy(cipherText, bufferString.c_str(), textLength);
		// process all characters of the cipher text
		int *charactersInRow = new int[key];
		memset(charactersInRow, 0, key * 4);
		int currentRow = 0;
		memset(charactersInRow, 0, 3);
		std::string *rows = new std::string[key];
		// flatten out the cipher text
		for(int index=offset; index<textLength+offset; index++) {
			// determine which row we're in (zero-based, from top down)
			int localOffset = index % n;
			// is it going up or down the fence?
			if(localOffset < key) { // *down*
				currentRow = localOffset;
			}
			else {									// *up*
				currentRow = (key - 1);
				int steps = localOffset - (key - 1);
				currentRow -= steps;
			}	
			charactersInRow[currentRow]++;
		}
		// now, assemble each row
		int charactersProcessed = 0;
		for(int i=0; i<key; i++) {
			char *temp = new char[textLength + 1];
			memset(temp, 0, textLength + 1);
			memcpy(temp, cipherText + charactersProcessed, charactersInRow[i]);
			rows[i].append(temp);
			charactersProcessed += charactersInRow[i];
		}
		// transform flattened out cipher text into clear text
		int *charactersInRowProcessed = new int[key];
		memset(charactersInRowProcessed, 0, key * 4);
		charactersProcessed = 0;
		for(int index=offset; index<textLength+offset; index++) {
			// determine which row we're in (zero-based, from top down)
			int localOffset = index % n;
			// is it going up or down the fence?
			if(localOffset < key) { // *down*
				currentRow = localOffset;
			}
			else {									// *up*
				currentRow = (key - 1);
				int steps = localOffset - (key - 1);
				currentRow -= steps;
			}	
			// construct the clear text character by character
			clearText[charactersProcessed++] = rows[currentRow].c_str()[charactersInRowProcessed[currentRow]++];
		}
		// this is ugly, but we're working on "cipherText" in the lines below; thus we copy from 
		// "clearText" to "cipherText" although we were actually decrypting here
		memset(cipherText, 0, textLength + 1);
		memcpy(cipherText, clearText, strlen(clearText));
	}

	std::string cipherTextString = cipherText;
	delete clearText;
	delete cipherText;
	// *** END ENCRYPTION/DECRYPTION PROCESS ***

	// create a name for the outfile
	char outfile[4096];
	GetTmpName(outfile, "cry", ".txt");

	// create a file handle for the output file
	std::ofstream fileOutput;
	fileOutput.open(outfile, ios::out);
	if(!fileOutput) return -2;

	// write the output file
	fileOutput.write(cipherTextString.c_str(), cipherTextString.length());
	fileOutput.close();

	// key as string including offset
	CString stringKeyAndOffset;
	char stringKey[4096 + 1];
	char stringOffset[4096 + 1];
	memset(stringKey, 0, 4096 + 1);
	memset(stringOffset, 0, 4096 + 1);
	itoa(key, stringKey, 10);
	itoa(offset, stringOffset, 10);
	stringKeyAndOffset.Append(stringKey);
	stringKeyAndOffset.Append(", KEY OFFSET: ");
	stringKeyAndOffset.Append(stringOffset);

	// open the new document
	CDocument *document = theApp.OpenDocumentFileNoMRU(outfile, stringKeyAndOffset);
	if(document) {
		char title[4096];
		memset(title, 0, 4096);
		// set the document title depending on whether we have an encryption or a decryption
		if(encrypt) LoadString(AfxGetInstanceHandle(), IDS_STRING_RAIL_FENCE_ENCRYPTION_OF, pc_str, STR_LAENGE_STRING_TABLE);
		else LoadString(AfxGetInstanceHandle(), IDS_STRING_RAIL_FENCE_DECRYPTION_OF, pc_str, STR_LAENGE_STRING_TABLE);
		// now add the old title and the key into the new title
		sprintf(title, pc_str, oldTitle, stringKeyAndOffset);
		// set the new document title
		document->SetTitle(title);
	}

	return 1;
}

//
// TODO due to lack of time: make sure dynamically allocated memory is freed 
//
// Scytale encryption (part of the simple transpositions dialog)
// RETURN VALUES:		1 (success), -1 (invalid key), -2 (invalid file handle)
int ScytaleEncryption(const char *infile, const char *oldTitle, int key, int offset, bool encrypt) {
	// create a handle for the input file
	std::ifstream fileInput;
	fileInput.open(infile);
	if(!fileInput) return -2;

	// store the contents of the file in bufferString
	std::string bufferString;
	char buffer[4096 + 1];
	memset(buffer, 0, 4096 + 1);
	do {
		memset(buffer, 0, 4096 + 1);
		fileInput.read(buffer, 4096);
		bufferString.append(buffer);
	}
	while(!fileInput.eof());
	fileInput.close();

	// ignore non-alphabet characters
	CString bufferStringValid;
	for(unsigned int i=0; i<bufferString.length(); i++) {
		if(theApp.TextOptions.getAlphabet().Find(bufferString[i]) != -1) {
			bufferStringValid.AppendChar(bufferString[i]);
		}
	}
	bufferString = bufferStringValid;

	// IMPORTANT: the key is invalid if it is "1" or >= the length of the clear text
	if(key <= 1 || key >= (int)bufferString.length()) {
		return -1;
	}

	// *** BEGIN ENCRYPTION/DECRYPTION PROCESS ***
	int textLength = bufferString.length();
	char *clearText = new char[textLength + offset + 1];
	memset(clearText, 0, textLength + offset + 1);
	memcpy(clearText, bufferString.c_str(), textLength);
	char *cipherText = new char[textLength + offset + 1];
	memset(cipherText, 0, textLength + offset + 1);

	// we need this check to make sure too big offsets don't mess up the encryption; thus, 
	// by convention, offsets bigger than the text length are reduced modulo the text length
	if(offset > textLength) offset = textLength;

	// we need to know how many columns ("windings") we have on our Scytale
	int numberOfColumns = (textLength + offset) / key;
	if((textLength + offset) % key) numberOfColumns++;

	// in the context of the Scytale encryption "the offset" indicates which winding 
	// we're starting to write on (0 = the first winding, 1 = the second winding...)
	offset = offset % numberOfColumns;

	// ENCRYPTION
	if(encrypt) {

		int charactersProcessed = 0;

		// declare a vector of rows (size: key)
		char **rows = new char*[key];
		for(int row=0; row<key; row++) {
			rows[row] = new char[numberOfColumns + 1];
			memset(rows[row], 0, numberOfColumns + 1);
		}
		int *charactersInRowProcessed = new int[key];
		memset(charactersInRowProcessed, 0, 4 * key);

		// fill the rows
		for(int index=0; index<textLength+offset; index++) {
			int row = index / numberOfColumns;
			if(offset > index) memset(rows[row] + charactersInRowProcessed[row]++, 0, 1);
			else memcpy(rows[row] + charactersInRowProcessed[row]++, clearText + charactersProcessed++, 1);
		}
		
		// create the ciphertext
		charactersProcessed = 0;
		for(int column=0; column<numberOfColumns; column++) {
			for(int row=0; row<key; row++) {
				// ignore zero bytes
				if(rows[row][column] == 0) continue;
				memcpy(cipherText + charactersProcessed++, rows[row] + column, 1);
			}
		}

	}
	// DECRYPTION
	else {
		
		int charactersProcessed = 0;

		// declare a vector of rows (size: key)
		char **rows = new char*[key];
		for(int row=0; row<key; row++) {
			rows[row] = new char[numberOfColumns + 1];
			memset(rows[row], 0, numberOfColumns + 1);
		}
		int *charactersInRowProcessed = new int[key];
		memset(charactersInRowProcessed, 0, 4 * key);

		// fill the rows
		charactersProcessed = 0;
		for(int column=0; column<numberOfColumns; column++) {
			for(int row=0; row<key; row++) {
				// ignore zero bytes
				if(offset > column && row == 0) continue;
				// make sure we end rows correctly (that is, not copy too much)
				if(row*numberOfColumns + column - offset >= textLength) continue;
				memcpy(rows[row] + charactersInRowProcessed[row]++, clearText + charactersProcessed++, 1); 
			}
		}	

		// create the clear text
		charactersProcessed = 0;
		for(int row=0; row<key; row++) {
			memcpy(cipherText + charactersProcessed, rows[row], strlen(rows[row]));
			charactersProcessed += strlen(rows[row]);
		}

		// flomar, 03/10/2009
		// again, it's ugly that we're storing the result in cipherText instead of clearText 
		// although we're executing a decryption; this will be fixed when there's more time

	}

	std::string cipherTextString = cipherText;
	delete clearText;
	delete cipherText;
	// *** END ENCRYPTION/DECRYPTION PROCESS ***

	// create a name for the outfile
	char outfile[4096];
	GetTmpName(outfile, "cry", ".txt");

	// create a file handle for the output file
	std::ofstream fileOutput;
	fileOutput.open(outfile, ios::out);
	if(!fileOutput) return -2;

	// write the output file
	fileOutput.write(cipherTextString.c_str(), cipherTextString.length());
	fileOutput.close();

	// key as string including offset
	CString stringKeyAndOffset;
	char stringKey[4096 + 1];
	char stringOffset[4096 + 1];
	memset(stringKey, 0, 4096 + 1);
	memset(stringOffset, 0, 4096 + 1);
	itoa(key, stringKey, 10);
	itoa(offset, stringOffset, 10);
	stringKeyAndOffset.Append(stringKey);
	stringKeyAndOffset.Append(", KEY OFFSET: ");
	stringKeyAndOffset.Append(stringOffset);

	// open the new document
	CDocument *document = theApp.OpenDocumentFileNoMRU(outfile, stringKeyAndOffset);
	if(document) {
		char title[4096];
		memset(title, 0, 4096);
		// set the document title depending on whether we have an encryption or a decryption
		if(encrypt) LoadString(AfxGetInstanceHandle(), IDS_STRING_SCYTALE_ENCRYPTION_OF, pc_str, STR_LAENGE_STRING_TABLE);
		else LoadString(AfxGetInstanceHandle(), IDS_STRING_SCYTALE_DECRYPTION_OF, pc_str, STR_LAENGE_STRING_TABLE);
		// now add the old title and the key into the new title
		sprintf(title, pc_str, oldTitle, stringKeyAndOffset);
		// set the new document title
		document->SetTitle(title);
	}

	return 1;
}