//////////////////////////////////////////////////////////////////
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "commdlg.h"
#include "multipad.h"
#include "fileutil.h"
#include "CryptDoc.h"
#include "dia1.h"
#include "hexdialog.h"
#include "crypt.h"
#include "HillEingabe.h"
#include "HillEingabeGross.h"
#include "hill.h"
#include "DlgFortschritt.h"
#include "DlgMono.h"
#include "secure.h"
#include "DlgSubstAna.h"
#include "Dlg_SubstResult.h"
#include <iostream.h>
#include <stdio.h>
#include "ChrTools.h"
#include "MyDocument.h"
#include "playfair.h"
#include "Dlg_PlayfairKey.h"
#include "DialogPlayfair.h"
#include "zzahlanalyse.h"
#include "Dlg_homophone.h"
#include "AnalyseNGram.h"
#include "DlgGenRandomData.h"

#include <fstream.h>

char *Eingabedatei;
int *MaxPermu[26];
float Fortschritt=20.0;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void solve (int Tiefe, int DMax, int *Permu[26], int Perm[], int score, char *PatSet[100][50], char *Cipher[100][100], int *MaxScore, int *MaxPermu[26], float Delta);
int SucheLeer (int Start, int Laenge, SymbolArray& text);
bool match (char *current, char *common);

void MakeNewName(char *dest, unsigned int len, const char *format, const char *old)
{
    if(strlen(format)+strlen(old)<len)
        sprintf(dest,format,old);
    else
        sprintf(dest,format,"...");
}

void MakeNewName3(char *dest, unsigned int len, const char *format, const char *alg, const char *old, const char *key)
{
    if(strlen(format)+strlen(alg)+strlen(old)+strlen(key)<len)
        sprintf(dest,format,alg,old,key);
    else {
	    if(strlen(format)+strlen(alg)+3+strlen(key)<len)
	        sprintf(dest,format,alg,"...",key);
		else
	        sprintf(dest,format,alg,"...","...");
	}
}

void FreePar(CryptPar *par)
{
	if(!(par->flags & CRYPT_FREE_MEM)) return;

	if(par->infile) free((void *) par->infile);
	if(par->OldTitle) free((void *) par->OldTitle);
	if(par->key) free(par->key);
}

void CaesarAsc(const char *infile, const char *OldTitle)
{
    char outfile[128], title[128], line[256];
    CMyDocument *NewDoc;

    dia1 KeyDialog(-1);

	SymbolArray text(AppConv);
	{
		CWaitCursor WCursor;
		text.Read(infile);

		if(text.GetSize() < 1) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str,1);
			AfxMessageBox (line);
			return;
		}
		WCursor.Restore();
// == title of modal window: 
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_INPUT_CAESAR,pc_str,STR_LAENGE_STRING_TABLE);
		KeyDialog.SetAlternativeWindowText(pc_str);
// ===================================
		if(KeyDialog.Display()!=IDOK) return;
		WCursor.Restore();
	    if (KeyDialog.GetLen()==0) return;

		SymbolArray Key(AppConv);
	    Key.ReadString(KeyDialog.GetData());
		Key += 1;
   
		GetTmpName(outfile,"cry",".tmp");

	    if(KeyDialog.m_Decrypt)
		    text -= Key;
	    else
		    text += Key;
	    text.Write(outfile);

		Reformat(infile, outfile, FALSE);
	}

    NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.GetData());
    remove(outfile);
    if(NewDoc) {
	    if(KeyDialog.m_Decrypt)
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		else
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_CAESAR,pc_str,STR_LAENGE_STRING_TABLE);
        MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,KeyDialog.GetData());
        NewDoc->SetTitle(title);
    }

	theApp.DoWaitCursor(0);
}


void VigenereAsc(const char *infile, const char *OldTitle)
{
    char outfile[128], title[128], line[256];
	CMyDocument *NewDoc;

    dia1 KeyDialog(MAX_VIGENERE);

	SymbolArray text(AppConv);
	{
		CWaitCursor WCursor;
		text.Read(infile);

		if(text.GetSize() < 1) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str,1);
			AfxMessageBox (line);
			return;
		}

// == title of modal window: 
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_INPUT_VIGENERE,pc_str,STR_LAENGE_STRING_TABLE);
		KeyDialog.SetAlternativeWindowText(pc_str);
// ===================================
		if(KeyDialog.Display()!=IDOK) return;
		WCursor.Restore();
	    if(KeyDialog.GetLen()==0) return;

		theApp.DoWaitCursor(1);

		GetTmpName(outfile,"cry",".tmp");

		SymbolArray Key(AppConv);
	    Key.ReadString(KeyDialog.GetData());

	    if(KeyDialog.m_Decrypt)
		    text -= Key;
		else
			text += Key;
		text.Write(outfile);
		Reformat(infile, outfile, FALSE);
	}
	NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.GetData());
	remove(outfile);
	if(NewDoc) {
		if(KeyDialog.m_Decrypt)
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		else
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_VIGENERE,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,KeyDialog.GetData());
		NewDoc->SetTitle(title);
    }

	theApp.DoWaitCursor(0);

}

void XorBin(const char *infile, const char *OldTitle)
{
    char outfile[128], title[128], *buffer, line[256];
    CMyDocument *NewDoc;
	int i;

    hexdialog KeyDialog(MAX_VIGENERE);

	SymbolArray text(IdConv);
	{
		CWaitCursor WCursor;
		text.Read(infile);
	}
	if(text.GetSize() < 1) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}

	if(KeyDialog.Display()!=IDOK) return;
    if (KeyDialog.GetLen()==0) return;

	theApp.DoWaitCursor(1);

    GetTmpName(outfile,"cry",".tmp");

	SymbolArray Key(IdConv,KeyDialog.GetLen());
	buffer = KeyDialog.GetData();
	for(i=KeyDialog.GetLen()-1;i>=0;i--) Key[i]=buffer[i];

    text ^= Key;
    text.Write(outfile);

    NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.m_einstr);
    remove(outfile);
    if(NewDoc) {
	    if(KeyDialog.m_Decrypt)
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		else
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_XOR,pc_str,STR_LAENGE_STRING_TABLE);
        MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,KeyDialog.m_einstr);
        NewDoc->SetTitle(title);
    }

	theApp.DoWaitCursor(0);

}

void AddBin(const char *infile, const char *OldTitle)
{
    char outfile[128], title[128], *buffer, line[256];
    CMyDocument *NewDoc;
	int i;

    hexdialog KeyDialog(MAX_VIGENERE);

	SymbolArray text(IdConv);
	{
		CWaitCursor WCursor;
		text.Read(infile);
	}
	if(text.GetSize() < 1) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}

	if(KeyDialog.Display()!=IDOK) return;
    if (KeyDialog.GetLen()==0) return;

	theApp.DoWaitCursor(1);

    GetTmpName(outfile,"cry",".tmp");

	SymbolArray Key(IdConv,KeyDialog.GetLen());
	buffer = KeyDialog.GetData();
	for(i=KeyDialog.GetLen()-1;i>=0;i--) Key[i]=buffer[i];

    if(KeyDialog.m_Decrypt)
        text -= Key;
    else
        text += Key;
    text.Write(outfile);

    NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.m_einstr);
    remove(outfile);
    if(NewDoc) {
	    if(KeyDialog.m_Decrypt)
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		else
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADD,pc_str,STR_LAENGE_STRING_TABLE);
        MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,KeyDialog.m_einstr);
        NewDoc->SetTitle(title);
    }

	theApp.DoWaitCursor(0);

}

void VernamBin(const char *infile, const char *OldTitle)
{
	OPENFILENAME ofn;
	char fname[257], line[256], ftitle[128];
    char outfile[128], title[128];
    CMyDocument *NewDoc;

	SymbolArray text(IdConv);
	{
		CWaitCursor WCursor;
		text.Read(infile);
	}
	if(text.GetSize() < 1) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}

	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_VERNAM_KEYFILE,pc_str,STR_LAENGE_STRING_TABLE);
	ofn.lpstrTitle = pc_str;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	ofn.lpstrFile = fname;
	fname[0] = 0;
	ofn.nMaxFile = sizeof(fname)-1;
	ofn.lpstrFileTitle = ftitle;
	ftitle[0] = 0;
	ofn.nMaxFileTitle = sizeof(ftitle)-1;
	if(!GetOpenFileName(&ofn)) return;
	if(fname[0]==0) return;

	theApp.DoWaitCursor(1);

    GetTmpName(outfile,"cry",".tmp");

	SymbolArray Key(IdConv);
	{
		CWaitCursor WCursor;
		Key.Read(fname);

	    text ^= Key;

		text.Write(outfile);
	}
/*	Reformat(infile, outfile);*/

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

	theApp.DoWaitCursor(0);
}


void PlayfairBin(const char *infile, const char *OldTitle)
{
    char outfile[128],preform[128],title[128];
    CMyDocument *NewDoc;
	int n;

	n=strlen(infile);
	if (strncmp(OldTitle+n-4,".asc",4)&&theApp.TextOptions.m_Format)
		GetTmpName(outfile,"cry",".txt");
	else
		GetTmpName(outfile,"cry",".asc");

	class CDlg_PlayfairKey KeyDialog(infile,outfile,theApp.TextOptions.m_Format,theApp.TextOptions.m_ConvertCase);

	if(KeyDialog.Display()!=IDOK) return;

	if (KeyDialog.m_preformat&&!KeyDialog.m_Dec)
	{
		GetTmpName(outfile,"cry",".asc");
		GetTmpName(preform,"cry",".asc");
		KeyDialog.m_Alg->ApplyPlayfairPreformat(KeyDialog.m_Dec,preform,outfile);
		char tmpStr[128];
		for (int i=0; i<KeyDialog.m_text.GetLength(); i++ )
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
			if(KeyDialog.m_Dec)
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
		KeyDialog.m_Alg->ApplyPlayfairToInput(KeyDialog.m_Dec);
		
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.GetData());
		remove(outfile);
		if(NewDoc) {
			if(KeyDialog.m_Dec)
				LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			else
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_PLAYFAIR,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,KeyDialog.GetData());
			NewDoc->SetTitle(title);
		}
	}
	theApp.DoWaitCursor(0);
}


void PlayfairAnalyse(const char *infile, const char *OldTitle)
{
    char outfile[128], title[128];
    CMyDocument *NewDoc;

	GetTmpName(outfile,"cry",".tmp");

	class CDialogPlayfair KeyDialog(infile,outfile,theApp.TextOptions.m_Format,theApp.TextOptions.m_ConvertCase);

	if(KeyDialog.Display()!=IDOK) return;

	KeyDialog.m_Alg->ApplyPlayfairToInput(KeyDialog.m_Dec);

	NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.GetData());
	remove(outfile);
	if(NewDoc) {
		if(KeyDialog.m_Dec)
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		else
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_PLAYFAIR,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,KeyDialog.GetData());
		NewDoc->SetTitle(title);
    }

	theApp.DoWaitCursor(0);
}


void Hill(const char *infile, const char *OldTitle)
{
	// Es muss mindestens ein Zeichen im Alphabet zu verschlüsseln sein
	if (theApp.TextOptions.m_alphabet.GetLength() == 0)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_ON_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (pc_str);
		return;
	}

	// Die Hillklasse wird zur Ueberpruefung der erlaubten Zeichen benoetigt
	hill *hillklasse;
	hillklasse = new hill(theApp.TextOptions.m_alphabet.GetBuffer(0));

    char outfile[128], title[128], line[256];
    CMyDocument *NewDoc;

	// Überprüfung, ob Eingabedatei mindestens ein Zeichen enthält. 
	CFile datei(infile, CFile::modeRead);

	long infile_zeichen_anz = 0;
	char c;
	while(datei.Read(&c,1))
	{
		// Falls Gross-/Kleinschreibung ignoriert werden soll,
		// muessen auch die Kleinbuchstaben mitgezaehlt werden.
		if ( hillklasse->ist_erlaubtes_zeichen(c) ||
			 ( (theApp.TextOptions.m_IgnoreCase) && (MyIsLower(c)) && 
			   (hillklasse->ist_erlaubtes_zeichen(MyToUpper(c))) ) )
		{
			infile_zeichen_anz++;
		}
	}
	datei.Close();

	if (! infile_zeichen_anz)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}

	// Fenster am Bildschirm anzeigen, falls abgebrochen, nichts mehr machen.

	bool bRcWeiter = false; // true, wenn der Dialog nicht mit Klick zum Wechsel
							// in Fenster mit groesseren bzw. kleineren Schluesseln
							// beendet worden ist. 
							// false, wenn mit OK oder Abbrechen beendet
	int iLocalRc;

    CHillEingabe* hillein = NULL;
    CHillEingabeGross* hilleingross = NULL;

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
			hillklasse = new hill(theApp.TextOptions.m_alphabet.GetBuffer(0));

			hillein = new CHillEingabe(hillklasse);
			iLocalRc = hillein->Display(hillklasse);

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
				delete hillklasse;
				hillklasse = NULL;
			}
		}
		else // iHillSchluesselFensterGroesse = HILL_SCHLUESSEL_GROSS
		{
			hillklasse = new hill(theApp.TextOptions.m_alphabet.GetBuffer(0));

			hilleingross = new CHillEingabeGross(hillklasse);
			iLocalRc = hilleingross->Display(hillklasse);

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
				delete hillklasse;
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
		ASSERT (hillklasse != NULL);
		delete hillklasse;

		return;
	}

	theApp.DoWaitCursor(1);

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
	if(theApp.TextOptions.m_IgnoreCase)
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

	// Werte in die Klasse hill einlesen
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
		else if	( (theApp.TextOptions.m_IgnoreCase) && (MyIsLower(csEingabeDatei[i])) && 
				   (hillklasse->ist_erlaubtes_zeichen(MyToUpper(csEingabeDatei[i]))) )
		{
			str[str_laenge++] = MyToUpper(csEingabeDatei[i]);
		}
	}
	str[str_laenge] = '\0';
	free(csEingabeDatei);

	// Variable zur Ausgabe des Schlüssels in der Titelleiste
	char schluessel[(HILL_MAX_DIM_GROSS+1)*HILL_MAX_DIM_GROSS+1];
	
	int i_m_decrypt;
	square_matrix *matrix;

	if (iHillSchluesselFensterGroesse == HILL_SCHLUESSEL_GROSS)
	{
		i_m_decrypt = hilleingross->m_decrypt;
		matrix = new square_matrix(hilleingross->mat->get_dim(),hillklasse->get_modul());
		(*matrix) = (*(hilleingross->mat));
	}
	else
	{
		i_m_decrypt = hillein->m_decrypt;
		matrix = new square_matrix(hillein->mat->get_dim(),hillklasse->get_modul());
		(*matrix) = (*(hillein->mat));
	}

	if (i_m_decrypt) // Entschluesseln
	{
		// Zuerst Matrix invertieren
		// Die Eingabe einer nicht invertierbaren Matrix wird abgelehnt 
		// (in der Eingabe: Hilleingabe.cpp, Funktion: CHillEingabe::OnOK()) !
		square_matrix inv_mat(matrix->get_dim(),hillklasse->get_modul());
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
	GetTmpName(outfile,"cry",".tmp");
    ofstream out(outfile);
	out << str;
	out.close();
	delete[] str;

	// Ver- bzw. Entschluesselte Daten aus Hill-Klasse auslesen und in neuem Fenster anzeigen
    // und danach die temporaere Datei wieder loeschen
	Reformat(infile, outfile, FALSE);
	NewDoc = theApp.OpenDocumentFileNoMRU(outfile,schluessel,SCHLUESSEL_QUADRATISCH);
    remove(outfile);

	if(NewDoc)
	{
	    if(i_m_decrypt)
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		else
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HILL,pc_str,STR_LAENGE_STRING_TABLE);
        MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,schluessel);
        NewDoc->SetTitle(title);
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
	ASSERT (hillklasse != NULL);
	delete hillklasse;

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
	
	theApp.DoWaitCursor(0);
}


void EntropyASCII(const char *infile, const char *OldTitle)
{
    char line[256];

    SymbolArray text(AppConv);
	{
		CWaitCursor WCursor;
		text.Read(infile);
	}
	if(text.GetSize() < 2) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,2);
		AfxMessageBox (line);
		return;
	}

	{
		CWaitCursor WCursor;
	    NGram distr(text);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ENTROPY_OF,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,distr.Entropie());
	}

	LoadString(AfxGetInstanceHandle(),IDS_STRING_TITLE_ENTROPY,pc_str,STR_LAENGE_STRING_TABLE);
    theApp.m_MainWnd->MessageBox(line, pc_str, MB_OK);
}


void EntropyBin(const char *infile, const char *OldTitle)
{
    char line[256];

    SymbolArray text(IdConv);
	{
		CWaitCursor WCursor;
		text.Read(infile);
	}
	if(text.GetSize() < 2) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,2);
		AfxMessageBox (line);
		return;
	}

	{
		CWaitCursor WCursor;
	    NGram distr(text);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ENTROPY_OF,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,distr.Entropie());
	}

	theApp.DoWaitCursor(0);

	LoadString(AfxGetInstanceHandle(),IDS_STRING_TITLE_ENTROPY,pc_str,STR_LAENGE_STRING_TABLE);
    theApp.m_MainWnd->MessageBox(line, pc_str, MB_OK);
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
		theApp.DoWaitCursor(-1);

	class zzahlanalyse analyse((char *)par->infile);
	analyse.WriteAnalyse(outfile,par->OldTitle);

	if((par->flags & CRYPT_DO_PROGRESS ) && (theApp.fs.m_canceled == 0)) {
		while(theApp.fs.Set(100)!=100) Sleep(100);
		theApp.fs.cancel();
	}

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(-1);

	par->flags |= CRYPT_DONE;
	FreePar(par);

	return 0;
}


// === PERIODENANALYSE
// September 2000 - Peter Gruber Entwurf
// Oktober 2000 - Henrik Koy Fehlerbeseitigung
// Januar 2001 - Thomas Gauweiler: Fehlerbeseitigung & linearer Algorithmus
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
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(-1);

	{
		// Initialisierung des Fortschrittbalkens
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PERIOD_ANALYSIS_D,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);

		// Thomas' Variante
		// eigentliche Periodenanalyse
		class zzahlanalyse analyse((char *)par->infile);
		int isPeriode = analyse.FindPeriod();

		// Vollständigkeit des Fortschrittbalkens anzeigen
		theApp.fs.Set(100,pc_str);
	
		// Ausgabe der Periodenlänge
		if (isPeriode > 0)
		{

			LoadString(AfxGetInstanceHandle(),IDS_STRING_PERIOD_FOUND,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1,"Periodenanzahl = %d", analyse.cnt_periodResults);
				int xx = AfxMessageBox(pc_str1, MB_OK | MB_ICONINFORMATION);
			for (int i=0; i<analyse.cnt_periodResults; i++) {
				sprintf(pc_str1,"%d: Länge = %d Offset = %d Wdh = %d", i, analyse.periodResults[i].length, analyse.periodResults[i].offset+1, analyse.periodResults[i].repeated);
				int x = AfxMessageBox(pc_str1, MB_OK | MB_ICONINFORMATION);
			}
/*			for (int i=0; i<analyse.cnt_periodResults; i++) {
				sprintf(pc_str1,pc_str, analyse.periodResults[i].length, analyse.periodResults[i].offset+1);
				strcpy (pc_str, pc_str1);
			}
			int x = AfxMessageBox(pc_str1, MB_OK | MB_ICONINFORMATION);
*/
		}

		// Keine Periode gefunden
		if (isPeriode == 0)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_NO_PERIOD_FOUND,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str);
		}

		// Zu analysierende Textdatei zu kurz
		if (isPeriode < 0)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_PERIOD_ANALYSIS_TEXTLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str);
		}

/* Hendriks Variante
        // Henrik Koy Oktober 2000
	    // neu Defnition der Schnittstelle für Periodenanalyse:
		// i_periodenLaenge: länge der gefundenen Periode
		// i_periodenOffset: Start der Periode im Dokument
		// eigentliche Periodenanalyse
		class zzahlanalyse analyse((char *)par->infile);
		int i_periodenOffset;
		int i_periodenLaenge = analyse.FindPeriod( i_periodenOffset );

		// Ausgabe der Periodenlänge
		if (i_periodenLaenge > 0)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PERIOD_FOUND,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(pc_str1,pc_str, i_periodenLaenge, i_periodenOffset+1);
			int x = AfxMessageBox(pc_str1, MB_OK | MB_ICONINFORMATION);
		}

		// Keine Periode gefunden
		if (i_periodenLaenge == 0)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_NO_PERIOD_FOUND,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str);
		}

		// Zu analysierende Textdatei zu kurz
		if (i_periodenLaenge < 0)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_PERIOD_ANALYSIS_TEXTLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str);
		}
*/

	
	}

	if((par->flags & CRYPT_DO_PROGRESS ) && (theApp.fs.m_canceled == 0)) {
		while(theApp.fs.Set(100)!=100) Sleep(100);
		theApp.fs.cancel();
	}

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(-1);

	par->flags |= CRYPT_DONE;
	FreePar(par);

	return 0;
}

UINT Autocorr(PVOID p)
{
    int i, j, n, r,fsize;
	char line[256], name[128], name2[128];
	CMyDocument *NewDoc = NULL;
	CryptPar *par;
	CFile f;
	FILE *fo;

	r=0;
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(1);

    SymbolArray text(IdConv);
	if(par->flags & CRYPT_ASCII)
		text.SetConverter((class Converter &) AppConv);

	if(par->flags & CRYPT_DO_PROGRESS) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOCORRELATION,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Display(pc_str);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOCORRELATION_COMPLETE,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(-1);

   	SCorrelation *tx;
	if(par->result) {
		tx = (SCorrelation *) par->result;
		n = tx->GetSize();
	}
	else {
		text.Read(par->infile);
		n = min(text.GetSize()/2,200);
		tx = new SCorrelation(text,n);	// Auto-Korrelation 1..200 betrachten,
	}

	fsize=text.GetSize();
	if(n<1) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,2);
		AfxMessageBox (line);
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
		theApp.DoWaitCursor(-1);

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
	CMyDocument *NewDoc = NULL;
	CryptPar *par;
	CFile f;
	FILE *fi, *fo;
	int winsize = 64;

	r=0;
	winsize = 64;
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(1);

	if(par->flags & CRYPT_DO_PROGRESS) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FLOATING_FREQ,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Display(pc_str);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FLOATING_FREQ_FINISHED,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	n = filesize(par->infile);
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(0);

	fi = fopen(par->infile,"rb");
	l = fread(buffer, 1, sizeof(buffer), fi);
	fo = NULL;

	if(l<winsize) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,winsize);
		AfxMessageBox (line);
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
		LoadString(AfxGetInstanceHandle(),IDS_STRING_TITLE_ENTROPY,pc_str,STR_LAENGE_STRING_TABLE);
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
		theApp.DoWaitCursor(-1);

	par->flags |= CRYPT_DONE;
	FreePar(par);

	return r;
}

void HistogramASCII(const char *infile, const char *OldTitle)
{
    char line[256], name[128], name2[128], numbuff[20];
	CFile f;
	int len;

	theApp.DoWaitCursor(1);

    SymbolArray text(AppConv);

    text.Read(infile);
	len = text.GetSize();
	if(len < 1) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}

    NGram distr(text);
	GetTmpName(name,"cry",".plt");

	LoadString(AfxGetInstanceHandle(),IDS_STRING_ASCII_HISTOGRAM_OF,pc_str,STR_LAENGE_STRING_TABLE);
    MakeNewName2(line,sizeof(line),pc_str,_itoa(len, numbuff, 10),OldTitle);

	distr.Show(OStream(name)<< OStream::Title(0) << OStream::Description(0) << OStream::Summary(0) << OStream::Percent());
//	distr.Show(PlotStream()<<OStream::PlotTitle(line));

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
		/*sprintf(buffer,"%d\n %d\n %d\n %d\n %d\n ", 1, 0, 0); 		
		
		ar<<buffer;
		*/
		ar.Close(); f.Close();

	}

    theApp.ThreadOpenDocumentFileNoMRU(name,line);

//    remove(name2);    // delete temporary files

/*    if(NewDoc) {
        NewDoc->SetTitle(line);
    }*/

	theApp.DoWaitCursor(0);

}



void HistogramBin(const char *infile, const char *OldTitle)
{
    char line[256],name[128], name2[128], numbuff[20];
	CFile f;
	int len;

	theApp.DoWaitCursor(1);

    SymbolArray text(IdConv);
    text.Read(infile);
	len = text.GetSize();
	if(len < 1) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}

    NGram distr(text);
	GetTmpName(name,"cry",".plt");
	LoadString(AfxGetInstanceHandle(),IDS_STRING_BINARY_HISTOGRAM_OF,pc_str,STR_LAENGE_STRING_TABLE);
    MakeNewName2(line,sizeof(line),pc_str,_itoa(len, numbuff, 10),OldTitle);
	distr.Show(OStream(name)<< OStream::Title(0) << OStream::Description(0) << OStream::Summary(0) << OStream::Percent());
//	distr.Show(PlotStream()<<OStream::PlotTitle(line));

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
//    remove(name2);

	theApp.DoWaitCursor(0);

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
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	    char line[256];
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}

	// Dialogbox zur Schlüsseleingabe anzeigen
	CDlgMono Mono1;
	if (Mono1.DoModal()==IDOK){
		/* Herleitung des (eigentlichen) Schlüssels aus dem eingegebenen Schlüsselwort:
		   Doppelte Buchstaben im Schlüsselwort werden nicht berücksichtigt.
		   Ansonsten wird das a auf den ersten Buchstaben des Schlüsselwortes abgebildet,
		   das b auf den zweiten,...
		   Danach werden alle Buchstaben, die nicht im Schlüsselwort vorkommen in
		   umgekehrter Reihenfolge den restlichen Buchstaben des Alphabetes zugeordnet.	*/

		// Die +1 ist für \0 (wegen der Ausgabe in der Titelleiste notwendig)
		char key[26+1];
		key[26] = '\0';

		bool schonda[26];//Ist der i-te Buchstabe bereits im Schlüsselwort aufgetreten??
		for (int i=0; i<=25; i++){
			key[i]=' ';
			schonda[i]=FALSE;}
		int lang=Mono1.m_edit.GetLength();
		int Nummer=0;
		for (int j=0; j<=(lang-1); j++){
			if ((Mono1.m_edit[j]>='A')&&(Mono1.m_edit[j]<='Z')){
				if (schonda[Mono1.m_edit[j]-65]==FALSE){
					key[Nummer]=Mono1.m_edit[j];
					Nummer++;
					schonda[Mono1.m_edit[j]-65]=TRUE;
				}
			}
		}
		
		//Die verbleibenden Schlüsselbuchstaben vergeben
		for (i=25; i>=0; i--){
			if (schonda[i]==FALSE){
				key[Nummer]=i+65;
				Nummer++;
			}
		}

		//Ausgabe der Permutation:
		LoadString(AfxGetInstanceHandle(),IDS_STRING_YOUR_KEYWORD,pc_str,STR_LAENGE_STRING_TABLE);
		CString Permu=pc_str;
		Permu+=Mono1.m_edit;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
		Permu+=pc_str;
		Permu+="ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
		for (i=0; i<=25; i++){
			Permu=Permu+(char)(key[i]);
		}
		AfxMessageBox (Permu);

		
		char outfile[128], title[128];
		CMyDocument *NewDoc;

		// Umlaute und Zeilenumbrueche umwandeln
		char outfile2[128];
		GetTmpName(outfile2,"cry",".tmp");
		FILE *stream, *stream2;
		
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
		
		// Sollen Leerzeichen im  Chiffretexttext erhalten bleiben???
/****************** Die Formatierung des Textes wird jetzt ueber eine globale Option gesetzt. Damit bleinben
alle Formatierunginformationen erhalten
		const Converter *Conv;
		if (Mono1.m_check==FALSE){ //Encrypt gewählt
			if (Mono1.m_check2==FALSE){
				Conv=&AlphaConv;
			}
			else {
				Conv=&AlphaSpaceConv;
			}
		}
		else { //decrypt gewählt
			Conv=&AlphaSpaceConv;
		}
		SymbolArray text(*Conv);
*************************/
		SymbolArray text(AlphaConv);

		//text.Read(infile);
		text.Read(outfile2);
		GetTmpName(outfile,"cry",".tmp");
		
		
		if (Mono1.m_check==TRUE){
			int Laenge=text.GetSize();
			
			//Berechne die inverse Permutation
			char keyinvers[26];
			for (i=0; i<26; i++){
				keyinvers[key[i]-65]=i;}
			
			//Entschlüsselung (=Verschlüsselung mit der inversen Permutation)
			for (i=0 ; i<Laenge; i++){
				if (text[i]!=26){
					text[i]=(keyinvers[text[i]]);}}
		}
		else{
			int Laenge=text.GetSize();
			for (i=0 ; i<Laenge; i++){
				if (text[i]!=26){
					text[i]=(key[text[i]]-65);}
			}
		}

		//Ausgabe des permutierten Textes
		text.Write(outfile);
		Reformat(outfile2,outfile, TRUE);
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile,key);
		remove(outfile);	
		remove (outfile2);
		if(NewDoc) 
		{
/* Ohne Ausgabe des Schlüssels in der Titelleiste:
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MONOALPHABETIC_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName(title,sizeof(title),pc_str,OldTitle);
			NewDoc->SetTitle(title);
*/
			if(Mono1.m_check)
				LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			else
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
			// Der eingegebene Schluessel ist zur Ausgabe in der Titelzeile nicht geeignet,
			// da bei der Analyse nur die Permutation gefunden werden kann, 
			// nicht jedoch das Schlüsselwort. 
			// Wegen der Konsistenz wird hier nur die Permutation ausgegeben 
			//MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,Mono1.m_edit);
			MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,key);
			NewDoc->SetTitle(title);
		}
	}
}

UINT AnaSubst(PVOID p) {

	/* Diese Funktion dient zum Brechen einer monoalphabetischen Substitution.
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
	CDlgSubstAna Dialog;

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
	if(Dialog.m_check3==(int)false){
		if(par->flags & CRYPT_DO_PROGRESS) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_SUBSTITUTION_ANALYSE,pc_str,STR_LAENGE_STRING_TABLE);
			theApp.fs.Display(pc_str);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_SUBSTITUTION_ANALYSE_COMPLETE,pc_str,STR_LAENGE_STRING_TABLE);
			theApp.fs.Set(0,pc_str);
			Sleep(1);
		}
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			theApp.DoWaitCursor(1);
	}


	// Umlaute und Zeilenumbrueche umwandeln
	char outfile2[128];
	GetTmpName(outfile2,"cry",".tmp");
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

	if (Dialog.m_check3==(int)true){
		// Anzeigen des Nachbearbeitungsfensters
		CDlg_SubstResult Dialogbox;
		if (Dialogbox.DoModal()==IDOK){
			// Entschlüsseln und Ausgabe des Textes
			char outfile[128], title[128];
			GetTmpName(outfile,"cry",".tmp");

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
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_FREQ_ANALYSE_NOTE,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (pc_str);}
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
		for (int j=0;j<100;j++){
			Cipher[i][j]=NULL;}
		for (j=0; j<50; j++){
			PatSet[i][j]=NULL;}
	}

	
	if(par->flags & CRYPT_DO_PROGRESS)    theApp.fs.Set(10);
	int Worte_in_Analyse=0;
	
	while ((Start<Laenge)&&(Worte_in_Analyse<100)){

		if((par->flags & CRYPT_DO_PROGRESS)&&(theApp.fs.m_canceled))   return 0;

// Sleep(1000);
		Leerzeichen=SucheLeer(Start, Laenge, text);
// Sleep(1000);

		// Es werden Wörter gefunden, die länger als 20 Zeichen sind.
		// D.h. entweder der Text hat gar keine Leerzeichen oder das
		// Wort ist wirklich länger als 20 Zeichen.
		// Wörter, die länger als 20 Zeichen sind, kommen aber in common nicht vor
		// und können mißachtet werden.
		if ((Leerzeichen-Start)>20){
			Start=Leerzeichen+1;
			continue;}
// Sleep(1000);
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

	/* Finden des Root-Wortes
	   Wir suchen die Ciphertextklasse, für die die Anzahl der verschiedenen Buchstaben im Pattern geteilt
	   durch die Größe der Pattern Set maximal ist			
	
	   Das Feld nBuch[100] speichert die Anzahl der verschiedenen Buchstaben der Patterns
	   Das Feld nPatSet die Größe der zugehörigen Pattern Set
	   Das Feld Taken merkt sich, ob die entsprechende Ciphertexte Klasse bereits in die Sortierung aufgenommen wurde
	   Die Reihenfolge wird in Perm[100] gespeichert			*/
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
			else{
				break;}
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
//	Sleep(1000);

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

// Wenn die folgenden Zeilen auskommentiert werden, bitte auf die Strings über die Stringtable zugreifen
// VON HIER
		// Testweise Ausgabe der sortierten Listen
		/*CString help="anfangSort: ";
		for (i=0; i<26; i++){
			help+=(char)(anfangSort[i]+65);
		}
		AfxMessageBox (help);

		help="endeSort: ";
		for (i=0; i<26; i++){
			help+=(char)(endeSort[i]+65);
		}
		AfxMessageBox (help);

		help="voreSort: ";
		for (i=0; i<26; i++){
			help+=(char)(voreSort[i]+65);
		}
		AfxMessageBox (help);

		help="nacheSort: ";
		for (i=0; i<26; i++){
			help+=(char)(nacheSort[i]+65);
		}
		AfxMessageBox (help);*/


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
// BIS HIER


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

// Wenn die folgenden Zeilen auskommentiert werden, bitte auf die Strings über die Stringtable zugreifen
// VON HIER
		// Testausgabe
		/*CString help2="n ist: ";
		help2+=(char)(endeSort[Minimum]+65);
		AfxMessageBox (help2);
		help2="Oder n ist: ";
		help2+=(char)(endeSort[Minimum2]+65);
		AfxMessageBox (help2);*/
// BIS HIER
		
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

// Wenn die folgenden Zeilen auskommentiert werden, bitte auf die Strings über die Stringtable zugreifen
// VON HIER
		// Testweise Ausgabe der ersten drei Einträge von vorn[26] und nachn[26]
		/*help="vornSort: ";
		for (i=0; i<26; i++){
			help+=(char)(vornSort[i]+65);
		}
		AfxMessageBox (help);

		help="nachnSort: ";
		for (i=0; i<26; i++){
			help+=(char)(nachnSort[i]+65);
		}
		AfxMessageBox (help);*/
// BIS HIER


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
	CDlg_SubstResult Dialogbox;
	if (Dialogbox.DoModal()==IDCANCEL){		// "Cancel" angeklickt
		// Belegten Speicherplatz freigeben
		free(current);
		// Den allokierten Platz für die Felder Cipher und PatSet wieder freigeben
		for (i=0; i<100; i++){
			for (int j=0; j<100; j++){
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
	char outfile[128], title[128];
	GetTmpName(outfile,"cry",".tmp");

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
		for (int j=0; j<100; j++){
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
		theApp.DoWaitCursor(-1);

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

	
	for (int i=0; i<26; i++){
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
		for (int k=0; k<26; k++){
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
	char line[100];
	CWaitCursor WCursor;

// first precondition:
// the alphabet for encryption must NOT be empty
	if(TRUE==theApp.TextOptions.m_alphabet.IsEmpty())
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_TEXT_OPTIONS,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);		
		return;				// wenn das Alphabet in Textoptionen kein Zeichen enthält, brich ab
	}

// second precondition:
// the text for encryption must NOT be empty
	SymbolArray text(AppConv);
	text.Read(infile);
	if(0==text.GetSize())
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox(line);		
		return;				// wenn der Text kein Zeichen aus dem Alphabet in Textoptionen enthält, brich ab
	}
	

	WCursor.Restore();	
	char inbuffer[buffsize];

	Dlg_homophone DH;
	DH.DeactivateDecryptionButton = TRUE;
	for (int i=0; ; i++ ) {
		DH.c_SourceFile[i] = infile[i];
		if (infile[i] == 0) break;
	}

	ifstream in(infile);	
	in.read(inbuffer,buffsize);

	CMyDocument *NewDoc;

	if(IDOK!=DH.DoModal()) 
	{
		in.close();
		return;
	}
// Routine zur Homophonen Verschlüsselung
	char outbuffer[17000];
	long outbuffsize;
	char outfile[128],title[128];
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
			for (int i=0;i<in.gcount();i++)
			{
				value=DH.HB.Encrypt((unsigned char)inbuffer[i]);
				if ( value >= 0 )
				{
					value <<= offsetResiduum;
					value |= residuum;
					offsetResiduum += bitLength;
					for (int i=0; offsetResiduum >= 8; i++ )
					{
						outbuffer[outbuffsize]= p_value[i];
						outbuffsize++;
						offsetResiduum -= 8;
					}
					if ( offsetResiduum ) 
					{
						residuum = p_value[i];
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

/*
	else								// Entschlüsselung
	{
		DH.HB.Make_dec_table();
		while(in.gcount())
		{
			outbuffsize=0;
			for(int i=0;i<in.gcount();i++)
			{
				outbuffer[outbuffsize]=DH.HB.Decrypt(inbuffer[i]);
				outbuffsize++;
			}
			out.write(outbuffer,outbuffsize);
			in.read(inbuffer,buffsize);
		}
	}
*/

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

	theApp.DoWaitCursor(0);
} // end Hompohone Asc

// ======================================================================================

void HomophoneHex(const char *infile, const char *OldTitle)
{
	char line[100];
	CWaitCursor WCursor;

// first precondition:
// the alphabet for encryption must NOT be empty
	if(TRUE==theApp.TextOptions.m_alphabet.IsEmpty())
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_TEXT_OPTIONS,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox(line);		
		return;				// wenn das Alphabet in Textoptionen kein Zeichen enthält, brich ab
	}

// second precondition:
// the text for encryption must NOT be empty
    SymbolArray text(IdConv);
	text.Read(infile);
	if(0==text.GetSize())
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox(line);		
		return;				// wenn der Text kein Zeichen aus dem Alphabet in Textoptionen enthält, brich ab
	}
	

	WCursor.Restore();	
	unsigned char inbuffer[buffsize];

	Dlg_homophone DH;
	for (int i=0; ; i++ ) {
		DH.c_SourceFile[i] = infile[i];
		if (infile[i] == 0) break;
	}

	ifstream in(infile, ios::binary | ios::in );	
	in.read(inbuffer,buffsize);

	CMyDocument *NewDoc;

	if(IDOK!=DH.DoModal()) 
	{
		in.close();
		return;
	}
// Routine zur Homophonen Verschlüsselung
	char outbuffer[4096];
	long outbuffsize;
	char outfile[128],title[128];
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
			in.read(inbuffer,buffsize);
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
			in.read(inbuffer,buffsize);
		}
	}
/*
	{
		DH.HB.Make_dec_table();

		
		while(in.gcount())
		{
			outbuffsize=0;
			for(int i=0;i<in.gcount();i++)
			{
				outbuffer[outbuffsize]=DH.HB.Decrypt(inbuffer[i]);
				outbuffsize++;
			}
			out.write(outbuffer,outbuffsize);
			in.read(inbuffer,buffsize);
		}
	}
*/
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

	theApp.DoWaitCursor(0);
} // end Hompohone Hex


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
    char line[256];
	CFile f;
	int len;

	theApp.DoWaitCursor(1);

    SymbolArray text(AppConv);

    text.Read(infile);
	len = text.GetSize();
	if(len < 1) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}

	AnalyseNGram DiaNGram;
	DiaNGram.LoadText(text, 0);
    DiaNGram.DoModal();

    if ( DiaNGram.b_saveNGramList() )
	{
		CMyDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU(DiaNGram.outfile);
		remove(DiaNGram.outfile);
		if(NewDoc) {
/*
			if(KeyDialog.m_Decrypt)
				LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			else
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_CAESAR,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,KeyDialog.GetData());
			NewDoc->SetTitle(title);
*/
			NewDoc->SetTitle("N-Gramm Analyse von");
		}
	}


	theApp.DoWaitCursor(0);
}

void NGramBin(const char *infile, const char *OldTitle)
{
    char line[256];
	CFile f;
	int len;

	theApp.DoWaitCursor(1);

    SymbolArray text(IdConv);

    text.Read(infile);
	len = text.GetSize();
	if(len < 1) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}

	AnalyseNGram DiaNGram;
	DiaNGram.LoadText(text, 1);

	DiaNGram.DoModal();
    if ( DiaNGram.b_saveNGramList() )
	{
		CMyDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU(DiaNGram.outfile);
		remove(DiaNGram.outfile);
		if(NewDoc) {
/*
			if(KeyDialog.m_Decrypt)
				LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			else
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_CAESAR,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,KeyDialog.GetData());
			NewDoc->SetTitle(title);
*/
			NewDoc->SetTitle("N-Gramm Analyse von X ");
		}
	}

	theApp.DoWaitCursor(0);
}

