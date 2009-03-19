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
#include "CrypToolApp.h"
#include "FileTools.h"
#include "CryptDoc.h"
#include "Cryptography.h"
#include "AutomaticAnalysis.h"
#include "DlgHillAnalysis.h"
#include "DlgShowKeyHill5x5.h"
#include "DlgShowKeyHill10x10.h"
#include "HillEncryption.h"
#include "DlgKeyLength.h"
#include "DialogLaengeBin.h"
#include "DlgKeyVigenere.h"
#include "DlgCaesarAnalysis.h"
#include "DlgKeyHexAnalysis.h"
#include "ChrTools.h"
#include "AppDocument.h"
#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif
#include <stdio.h>
#include "DialogeMessage.h"
#include "FileTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char *Pfad; // Directory Path of the main programm

// ========================================================================================
// Automatic Caesar "ciphertext-only" analysis
void CaesarAuto(const char *infile, const char *OldTitle)
{
	char name[1024], name2[256], line[256], key[256];
	CFile f;
	CAppDocument *NewDoc;

	FILE *fi;
	int i;
	
// == Caesar analysis doesent make sence if the ciphertext has length 0
	fi = fopen(infile,"rb");
	fseek(fi,0,SEEK_END);
	i = ftell(fi);
	fclose(fi);
	if(i < 1) {
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		return;
	}

// == in the first step, the histograms of the ciphertext and the reference text will be displayed
	if (theApp.Options.m_CHist) {
		HistogramASCII(theApp.TextOptions.getReferenceFile(), theApp.TextOptions.getTitle());
		HistogramASCII(infile, OldTitle);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_CMP_CIPHER_REFERENCE,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line, pc_str, theApp.TextOptions.getTitle());
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_CAESAR,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(line, pc_str1, MB_OK);
	}
	
	SHOW_HOUR_GLASS
	
	SymbolArray text(AppConv);
    text.Read(infile);
// == additional condition: if the sieved ciphertext length is below 2 ... exit the procedure
	if (text.GetSize() < 2)
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 2);
		return;	
	}
	
// == compare the ciphertext and the reference text
	SymbolArray reference(AppConv);
	
	if ( 1 > filesize(theApp.TextOptions.getReferenceFile().GetBuffer(0)) )
	{
		Message(IDS_ERRON_OPEN_REFERENCE_FILE, MB_ICONEXCLAMATION);
		return;
	}
	reference.Read(theApp.TextOptions.getReferenceFile());
	reference+=1;
	
	NGram t(text);
	NGram d(reference);
	
	DCorrelation c(d,t);
	
	if (theApp.Options.m_CKorr) {
	// == plot the correlation between the ciphertext and the reference text
		GetTmpName(name,"cry",".plt");
		
		LoadString(AfxGetInstanceHandle(),IDS_STRING_CORRELATION,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName2(line,sizeof(line),pc_str,theApp.TextOptions.getTitle(), OldTitle);
		
		c.Show(OStream(name)<< OStream::Title(0) << OStream::Description(0) << OStream::Summary(0));
		
		// == get the tmp name without file extension
		strcpy(name2, name);
		name2[strlen(name)-4] = 0x0;
		
		if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) ) {
			CArchive ar( &f, CArchive::store);
			CString s1 = line;
			LoadString(AfxGetInstanceHandle(),IDS_STRING_SHIFT,pc_str,STR_LAENGE_STRING_TABLE);
			CString s2 = pc_str;
			LoadString(AfxGetInstanceHandle(),IDS_STRING_TITLE_CORRELATION,pc_str,STR_LAENGE_STRING_TABLE);
			CString s3 = pc_str;
			
			// headline <<  x_label << y_label
			ar << s1 << s2 << s3;
			
			// CONTINUOUS  X_CHAR  Y_CHAR
			ar << (int)0 << (char)0x40 << (char)0x30;
			ar.Close(); f.Close();
			
		}

		NewDoc = theApp.OpenDocumentFileNoMRU(name);		
		remove(name); remove(name2);    // delete temporary files		
		if(NewDoc) {
			NewDoc->SetTitle(line);
		}
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_SUPERIMPOSITIONS,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_CAESAR,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str, pc_str1, MB_OK);
	}

// == seek for the assumed decryption key 
	int shift=c.FindPeak();
	
// == the user may change the proposed decryption key via the dialog
	if(theApp.Options.m_CKey) {
		CDlgCaesarAnalysis dia;
		
		dia.m_string = theApp.TextOptions.getAlphabet()[shift];
		if(IDCANCEL == dia.DoModal()) return;
		if(dia.m_string.GetLength() == 1) shift = theApp.TextOptions.getAlphabet().Find(dia.m_string[0]);
		else shift = 0;
	}

// == decrypt the ciphertext
	text-=shift;
	text-=1;
	GetTmpName(name,"cry",".tmp");
	text.Write(name);
	ForceReformat(infile,name, FALSE);
	// CString csKey = theApp.TextOptions.getAlphabet()[shift];
	CString csKey = theApp.TextOptions.getAlphabet().Mid(shift, 1);

    NewDoc = theApp.OpenDocumentFileNoMRU(name, csKey);
    remove(name);
	if(NewDoc) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KEY,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(key,pc_str,theApp.TextOptions.getAlphabet()[shift]);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOMATIC_CAESAR_ANALYSE_OF,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName2(line,sizeof(line),pc_str,key,OldTitle);
		NewDoc->SetTitle(line);
    }
	HIDE_HOUR_GLASS
}

// ======================================================================================
// Automatic Vigenere "ciphertext-only" analysis
UINT VigenereAuto(PVOID p)
{
	char name[256], name2[256], line[256], line2[256], key[256];
	CFile f;
	CryptPar *par;
	CDlgOptionsAnalysis Opt;
	int av, mx, s, periode, r;
	CryptPar para;
	
// == auto-correlation analysis for the ciphertext
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS
	
	if(par->flags | CRYPT_DO_PROGRESS) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOCORRELATION_COMPLETE,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	
	Opt.m_VKey  = theApp.Options.m_VKey;
	Opt.m_VKorr = theApp.Options.m_VKorr;
	Opt.m_VLen  = theApp.Options.m_VLen;
	Opt.m_VBase = theApp.Options.m_VBase;
	
	SymbolArray text(AppConv);
    text.Read(par->infile);
	// ## if the ciphertext-length is less than 4, abort procedure (added code Nov 2000)
	if (text.GetSize() <= 3)
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 4);
		return 0;	
	}
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

	SCorrelation c(text,min(text.GetSize(), 200));	// Auto-correlation restricted to 1..200 
	
	memset(&para,0,sizeof(para));
	para.infile = par->infile;
	para.OldTitle = par->OldTitle;
	para.result = &c;
	if (Opt.m_VKorr) 
		para.flags=(CRYPT_DISPLAY_BG | (par->flags & CRYPT_DO_PROGRESS));
	else
		para.flags= (par->flags & CRYPT_DO_PROGRESS);
	if(c.GetSize()<2)
		para.flags&=!CRYPT_DISPLAY_BG;
	// == execute and plot the autocorrelation

    r = Autocorr(&para);	
	while(theApp.fs.m_displayed) Sleep(100);
	if(r) return r;
	/* removed information dialog according to BE's remarks, 02/07/07
	if (Opt.m_VKorr) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PROCEED,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_VIGENERE,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str, pc_str1, MB_OK);
	}*/
	
// == compute the assumed key-length
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS
	
	av = (int) c.GetAverage(1);
	mx = (int) c.GetMax(1);
	s = (av + mx) / 2;
	for(periode=1;periode<c.GetSize();periode++) if(c[periode]>s) break;
	
// == Diplay (and edit) the assumed Key-Length
	if(Opt.m_VLen) {
		CDlgKeyLength dia;
		dia.m_laenge = periode;
		if(IDCANCEL == dia.DoModal()) {
			if(par->flags & CRYPT_DO_WAIT_CURSOR)
				HIDE_HOUR_GLASS
			return r;
		}
		periode = dia.m_laenge;
	}

	SymbolArray reference(AppConv);
	// bug: CrypTool terminated when no valid reference file was given (e.g. empty string)
	// solution: tell user to specify valid reference file and return
	if(theApp.TextOptions.getReferenceFile().GetLength() <= 0)
	{
		LoadString(AfxGetInstanceHandle(),IDS_ERRON_OPEN_REFERENCE_FILE,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str, MB_ICONINFORMATION);
		return -1;
	}
	reference.Read(theApp.TextOptions.getReferenceFile());
	reference += 1;
	NGram d(reference);

// == evaluate assumed key using the Caesar analysis for the partitioned ciphertext
	if (Opt.m_VBase) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_STANDARD_REF_TEXT,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_GERMAN,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(line,"%s%s",Pfad,pc_str);	
		HistogramASCII(line, pc_str1);
	}
	
	// == Einzelne Caesars Brechen	
	int i;
	for (i=0; i<periode;i++) {
		SymbolArray s=text.Extract(i,periode);
		if (Opt.m_VBase) { // 
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_ON_CAESAR,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line2,pc_str,i+1);
			MakeNewName(line,sizeof(line),line2,par->OldTitle);
			GetTmpName(name,"cry",".tmp");
			text.Write(name);
			HistogramASCII(name,line);
			remove(name);
		}
		NGram ng(s);
		DCorrelation c(d,ng);
		
		int shift=c.FindPeak();
		
		key[i] = theApp.TextOptions.getAlphabet()[(shift+1) % c.GetSize()];
		if (Opt.m_VBase) {
			// Ausgabe der Korrelation zwischen deutschem Text und dem Chiffrat
			GetTmpName(name,"cry",".plt");
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_CORRELATION_CAESAR_REFERENCE,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str,i+1, theApp.TextOptions.getTitle());
			
			c.Show(OStream(name)<< OStream::Title(0) << OStream::Description(0) << OStream::Summary(0));
			
			// get the tmp name without file extension
			strcpy(name2, name);
			name2[strlen(name)-4] = 0x0;
			
			if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) ) {
				CArchive ar( &f, CArchive::store);
				CString s1 = line;
				LoadString(AfxGetInstanceHandle(),IDS_STRING_SHIFT,pc_str,STR_LAENGE_STRING_TABLE);
				CString s2 = pc_str;
				LoadString(AfxGetInstanceHandle(),IDS_STRING_TITLE_CORRELATION,pc_str,STR_LAENGE_STRING_TABLE);
				CString s3 = pc_str;
				
				// headline <<  x_label << y_label
				ar << s1 << s2 << s3;
				//				ar.Flush();
				//				f.Flush();
				
				// CONTINUOUS  X_CHAR  Y_CHAR
				ar << (int)0 << (char)0x40 << (char)0x30;
				ar.Close(); f.Close();
				
			}
			
			theApp.ThreadOpenDocumentFileNoMRU(name,line);
			
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASCERTAINED_KEY_CHARACTER,pc_str,STR_LAENGE_STRING_TABLE);
			// ## NEW CODE (Mai 01) '+1' insered: caused by difference Caesar <--> Vigenere-Caesar 
			unsigned char CaesarKey = (theApp.TextOptions.getAlphabet()[shift]+1 - 'A') % 26;
			CaesarKey += 'A';		
			sprintf(line,pc_str,i+1, CaesarKey ); 
			// ## END NEW CODE
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_VIGENERE,pc_str,STR_LAENGE_STRING_TABLE);
			if(IDCANCEL==theApp.m_MainWnd->MessageBox(line,pc_str,MB_OKCANCEL)) Opt.m_VBase = FALSE;
		}
		
	}
	key[i]=0;

// == display the ascertained key
	SymbolArray KeyArray(AppConv);
	if(Opt.m_VKey) {
		CDlgKeyVigenereAnalyisis dia;
		dia.m_Str = key;
		if(IDCANCEL == dia.DoModal()) return 0;
		strcpy(key,dia.m_Str);
	}
	periode = strlen(key); // check for iterated key
	for(i=1;i<periode;i++) {
		if(periode%i == 0) {
			if(!memcmp(key,key+i,periode-i)) { // iterated key found
				key[i]=0;
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_ON_CONVERT_KEY,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str,key);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_VIGENERE,pc_str,STR_LAENGE_STRING_TABLE);
				theApp.m_MainWnd->MessageBox(line,pc_str,MB_OK);
			}
		}
	}

// == decrypt the ciphertext
	KeyArray.ReadString(key);
	text -= KeyArray;
	GetTmpName(name,"cry",".tmp");
	text.Write(name);
	ForceReformat(par->infile,name, FALSE);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOMATIC_VIGENERE_ANALYSE_OF,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName2(line,sizeof(line),pc_str,key,par->OldTitle);
    theApp.ThreadOpenDocumentFileNoMRU(name,line,key);
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS
	
	return 0;
}

// ================================================================================================
// "Known-plaintext" analysis for Hill-ciphers
void HillPlain(const char *infile, const char *OldTitle)
{
	// Hill Klasse anlegen und Daten in Hill-Klasse fuellen
	CHillEncryption hillklasse((const char*)theApp.TextOptions.getAlphabet());
	
	// Überprüfung, ob Eingabedatei mindestens ein Zeichen enthält. 
	CFile datei(infile, CFile::modeRead);
	long infile_zeichen_anz = 0;
	char c;
	while(datei.Read(&c,1))
	{
		// Falls Gross-/Kleinschreibung ignoriert werden soll,
		// muessen auch die Kleinbuchstaben mitgezaehlt werden.
		if ( hillklasse.ist_erlaubtes_zeichen(c) ||
			( (theApp.TextOptions.getIgnoreCase()) && (MyIsLower(c)) && 
			(hillklasse.ist_erlaubtes_zeichen(MyToUpper(c))) ) )
		{
			infile_zeichen_anz++;
		}
	}
	datei.Close();
	
	if (! infile_zeichen_anz)
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		return;
	}
	// jetzt hat die Eingabedatei auf jeden Fall mehr als ein zu verschlüsselndes Zeichen
	
	// Eingabe des Klartextes bzw. verschluesselten Textes 
	CDlgHillAnaylsis EingabeDialog;	
	
	if (EingabeDialog.DoModal() == IDOK)
	{
		SHOW_HOUR_GLASS
		
		// Falls Gross-/Kleinschreibung ignoriert werden soll:
		// Es werden alle Kleinbuchstaben in Grossbuchstaben umgewandelt
		if(theApp.TextOptions.getIgnoreCase())
		{
			MyToUpper(EingabeDialog.m_EingabeFeld);
		}
		
		int laenge = EingabeDialog.m_EingabeFeld.GetLength();
		
		char *str;
		str = new char[laenge+1];
		// wir legen vielleicht einiges zuviel an Speicher an 
		// (falls viele nicht zu verschluesselnde Zeichen in der Datei vorhanden sind)
		long laenge_str = 0;
		
		int i;
		for (i=0; i<laenge; i++)
		{
			// Kleinbuchstaben wurden schon zu Grossbuchstaben konvertiert, sofern erforderlich;
			// deshalb muss dies hier nicht mehr beruecksichtigt werden.
			if ( hillklasse.ist_erlaubtes_zeichen(EingabeDialog.m_EingabeFeld[i]) )
			{
				str[laenge_str++] = EingabeDialog.m_EingabeFeld[i];
			}
		}
		str[laenge_str] = '\0';
		
		// Hat auch die andere Datei mindestens ein zu verschlüsselndes Zeichen ?
		if (!laenge_str)
		{
			Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		}
		else
		{
			// aus dem Text nur die erlaubten Zeichen uebernehmen und den Text in einen String einlesen
			// infile hat infile_zeichen_anz erlaubte Zeichen
			CFile datei(infile, CFile::modeRead);
			
			char *anderer_str;
			// wir legen vielleicht einiges zuviel an Speicher an
			// (falls viele nicht zu verschluesselnde Zeichen in der Datei vorhanden sind)
			anderer_str = new char[infile_zeichen_anz+1];
			long laenge_anderer_str = 0;
			
			char c;
			while(datei.Read(&c,1))
			{
				if ( hillklasse.ist_erlaubtes_zeichen(c) )
				{
					anderer_str[laenge_anderer_str++] = c;
				}
				// Falls Gross-/Kleinschreibung ignoriert werden soll:
				// Es werden alle Kleinbuchstaben in Grossbuchstaben umgewandelt
				else if ( (theApp.TextOptions.getIgnoreCase()) && MyIsLower(c) && 
					hillklasse.ist_erlaubtes_zeichen(MyToUpper(c)) )
				{
					anderer_str[laenge_anderer_str++] = MyToUpper(c);
				}
			}
			anderer_str[laenge_anderer_str] = '\0';
			datei.Close();
			
			// In das Eingabefeld fuer den Text koennen zwar ueber die Zwischenablage  
			// grosse Dokumente eingegeben werden, aber sie werden nur bis zu einer 
			// gewissen Groesse ins Feld uebernommen.
			// Daher kann es vorkommen, dass der Schluessel gefunden wird, jedoch
			// nicht komplett ueberprueft werden kann. -> Returncode aus der Hillklasse
			
			if (EingabeDialog.m_Klartext == 0)
			{
				// Es wurde ein Klartext eingegeben, also ist der 
				// Text im Fenster der verschluesselte
				hillklasse.set_plaintext(str);
				hillklasse.set_ciphertext(anderer_str);
			}
			else
			{
				// Es wurde ein Klartext eingegeben, also ist der 
				// Text im Fenster der verschluesselte
				hillklasse.set_plaintext(anderer_str);
				hillklasse.set_ciphertext(str);
			}
			
			delete[] str;
			delete[] anderer_str;
			
			
			// Plaintext-Angriff durchfuehren
			CSquareMatrixModN *mat;
			
			int hill_rc;
			int hill_rc_dims[HILL_MAX_DIM_GROSS];

			hill_rc = hillklasse.angriff(EingabeDialog.von, EingabeDialog.bis, &mat, hill_rc_dims);
			
			// Rueckgabewerte siehe hill.h
			if (hill_rc == HILL_OK || hill_rc == HILL_OK_LAENGE_UNTERSCHIEDLICH)	
			{
				if (mat->get_dim() <= 5)
				{
					// Inhalt von mat anzeigen
					CDlgShowKeyHill5x5 AusgabeFenster;
					
					// War einer der Texte kuerzer ?
					if (hill_rc == HILL_OK_LAENGE_UNTERSCHIEDLICH)
					{
						Message(IDS_STRING_MSG_DATALENGTH_MISMATCH,MB_ICONINFORMATION);
					}
					
					// Jetzt muessen die Werte der Matrix in den Variablen der
					// Klasse gespeichert werden.
					AusgabeFenster.MatrixAnzeigen(*mat, mat->get_dim(), hillklasse);
					
					// Es wird immer der Schluessel zum Verschluesseln angezeigt
					AusgabeFenster.m_decrypt = FALSE;
					
					// Fenster anzeigen
					AusgabeFenster.DoModal();
				}
				else
				{
					// Inhalt von mat anzeigen
					CDlgShowKeyHill10x10 AusgabeFenster;
					
					// War einer der Texte kuerzer ?
					if (hill_rc == HILL_OK_LAENGE_UNTERSCHIEDLICH)
					{
						Message(IDS_STRING_MSG_DATALENGTH_MISMATCH,MB_ICONINFORMATION);
					}
					
					// Jetzt muessen die Werte der Matrix in den Variablen der
					// Klasse gespeichert werden.
					AusgabeFenster.MatrixAnzeigen(*mat, mat->get_dim(), hillklasse);
					
					// Es wird immer der Schluessel zum Verschluesseln angezeigt
					AusgabeFenster.m_decrypt = FALSE;
					
					// Fenster anzeigen
					AusgabeFenster.DoModal();
				}
				
				delete mat;
			}
			else if (hill_rc == HILL_NICHT_OK_NICHT_GEFUNDEN)
			{
				Message(IDS_STRING_MSG_KEY_NOT_FOUND_SHORT_TEXT, MB_ICONSTOP);
			}
			else if (hill_rc == HILL_NICHT_OK_WIDERSPRUCH)
			{
				Message(IDS_STRING_MSG_KEY_NOT_FOUND_CONFLICT, MB_ICONSTOP);
			}
			else if (hill_rc == HILL_UNDEF)
			{
				// Es gibt mindestens einmal HILL_NICHT_OK_NICHT_GEFUNDEN
				// und einmal HILL_NICHT_OK_WIDERSPRUCH. Daher die Ergebnisse
				// fuer alle Dimensionen ausgeben.
				CString cstr; // Ausgabefeld aufbauen
				CString nicht_gefunden, 
					widerspruch,
					zahl;
				
				for (i=EingabeDialog.von; i<=EingabeDialog.bis; i++)
				{
					zahl.Format("%d", i);
					
					if (hill_rc_dims[i-1] == HILL_NICHT_OK_NICHT_GEFUNDEN)
					{
						if (! nicht_gefunden.IsEmpty())
						{
							nicht_gefunden += ", ";
						}
						nicht_gefunden += zahl; 
					}
					else if (hill_rc_dims[i-1] == HILL_NICHT_OK_WIDERSPRUCH)
					{
						if (! widerspruch.IsEmpty())
						{
							widerspruch += ", ";
						}
						widerspruch += zahl; 
					}
				}
				
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KEY_NOT_FOUND_CONFLICT_2,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1,pc_str,widerspruch.GetBuffer(0));
				cstr += pc_str1;
				cstr += "\n";
				
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KEY_NOT_FOUND_2,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1,pc_str,nicht_gefunden.GetBuffer(0));
				cstr += pc_str1;
				
				AfxMessageBox(cstr.GetBuffer(0), MB_ICONSTOP);
			}
			else // Das darf nicht passieren, wir geben aus: Der Schluessel wurde nicht gefunden
			{
				Message(IDS_STRING_MSG_KEY_NOT_FOUND, MB_ICONSTOP);
			}
		}
		
		HIDE_HOUR_GLASS
	}
}



// ========================================================================================================================
// "Ciphertext-only" analysis for XOR-encryptions
UINT XorAuto(PVOID p)
{
	char name[256], line[256], line2[256], MaxChar;
	unsigned char key[256];
	CFile f;
	CryptPar *par;
	int j, shift, av, mx, periode, s, r, k;
	double m;
	CDlgOptionsAnalysis Opt;
	CryptPar para;
	
// == auto-correlation analysis for the ciphertext
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS
	r=0;
	
	Opt.m_VKey = theApp.Options.m_VKey;
	Opt.m_VKorr = theApp.Options.m_VKorr;
	Opt.m_VLen = theApp.Options.m_VLen;
	Opt.m_VBase = theApp.Options.m_VBase;
	
	SymbolArray text(IdConv);
    text.Read(par->infile);
	SCorrelation c(text,min(text.GetSize(),200));	// Auto-Korrelation 1..200 betrachten,
// == additional condition: if the sieved ciphertext length is below 2 ... exit the procedure
	if (c.GetSize() <= 1)
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 2);
		return 0;	
	}
	
	memset(&para,0,sizeof(para));
	para.infile = par->infile;
	para.OldTitle = par->OldTitle;
	para.result = &c;
	if (Opt.m_VKorr) 
		para.flags=(CRYPT_DISPLAY_BG | (par->flags & CRYPT_DO_PROGRESS));
	else
		para.flags= (par->flags & CRYPT_DO_PROGRESS);
	if(c.GetSize()<2)
		para.flags&=!CRYPT_DISPLAY_BG;
    r = Autocorr(&para);
	while(theApp.fs.m_displayed) Sleep(100);
	if(r) return r;
	/* removed information dialog according to BE's remarks, 02/07/07
	if (Opt.m_VKorr) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PROCEED,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_XOR,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str, pc_str1, MB_OK);
	}*/
	
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS
	
	av = (int) c.GetAverage();
	mx = (int) c.GetMax(1);
	s = (av + mx) / 2;
	for(periode=1;periode<c.GetSize()/*200*/;periode++) if(c[periode]>s) break;

// == Display (edit) the assumed key-length and enter the assumed most frequent plaintext-character
	if(Opt.m_VLen) {
		CDlgBinKeyLength dia;
		dia.m_laenge = periode;
		// set dialog title
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_XOR,pc_str1,STR_LAENGE_STRING_TABLE);
		dia.m_title = pc_str1;
		if(IDCANCEL == dia.DoModal()) {
			if(par->flags & CRYPT_DO_WAIT_CURSOR)
				HIDE_HOUR_GLASS
			return r;
		}
		periode = dia.m_laenge;
		MaxChar = dia.m_c;
	}
	
// == Partition the ciphertext and evaluete the assumed XOR-Key
	int i;
	for (i=0; i<periode;i++) {
		SymbolArray s=text.Extract(i,periode);
		if (Opt.m_VBase) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_XOR_MSG_OF,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line2,pc_str,i+1);
			MakeNewName(line,sizeof(line),line2,par->OldTitle);
			GetTmpName(name,"cry",".txt");
			text.Write(name);
			HistogramBin(name,line);
			remove(name);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PROCEED,pc_str,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_XOR,pc_str1,STR_LAENGE_STRING_TABLE);
			if(IDCANCEL==theApp.m_MainWnd->MessageBox(pc_str, pc_str1, MB_OKCANCEL)) Opt.m_VBase = FALSE;
		}
		NGram ng(s);
		m=0;
		for(j=255;j>=0;j--)
			if (ng[j]>m) {
				m=ng[j];
				shift=j;
			}
		key[i] = shift ^ MaxChar;
	}

// == display the ascertained XOR-key
	key[i]=0;
	if(Opt.m_VKey) {
		CDlgKeyHexAnalysis dia;
		
		CString title;
		title.LoadString(IDS_STRING_ANALYSE_XOR);		
		if(IDCANCEL == dia.Display((LPCTSTR)title,(char *) key,periode,false)) {
			if(par->flags & CRYPT_DO_WAIT_CURSOR)
				HIDE_HOUR_GLASS
			return r;
		}
		
		periode = dia.GetLen();
		memcpy(key,dia.GetData(),periode);
	}
	for(i=1;i<periode;i++) { // check for repeated keys
		if(periode%i == 0) {
			if(!memcmp(key,key+i,periode-i)) { // iterated key found
				periode = i;
				for(i=0;i<periode;i++) sprintf(line2+(i*3)," %02.2X", key[i]);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_ON_CONVERT_KEY,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str,line2+1);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_XOR,pc_str,STR_LAENGE_STRING_TABLE);
				theApp.m_MainWnd->MessageBox(line,pc_str,MB_OK);
			}
		}
	}

// == Decrypt the ciphertext 
	for(i=0;i<periode;i++) sprintf(line2+(i*3)," %02.2X", key[i]);
	SymbolArray KeyArray(IdConv,periode);
	for(k=0;k<periode;k++) KeyArray[k]=key[k];
	text ^= KeyArray;
	
	GetTmpName(name,"cry",".tmp");
	text.Write(name);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOMATIC_XOR_ANALYSE_OF,pc_str,STR_LAENGE_STRING_TABLE);
	// line2+1: die +1 wegen des ersten zusätzlichen Leereichens, das in den String
	// line2 am Anfang eingefügt worden ist, aber nicht mit ausgegeben werden soll 
	MakeNewName2(line,sizeof(line),pc_str,line2+1,par->OldTitle);
    theApp.ThreadOpenDocumentFileNoMRU(name,line, line2+1);
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS
	
	return r;
}


// ========================================================================================================================
// "Ciphertext-only" analysis for ADD-encryptions
UINT AddAuto(PVOID p)
{
	char name[256], line[256], line2[256], MaxChar;
	unsigned char key[256];
	CFile f;
	CryptPar *par;
	int j, shift, av, mx, periode, s, r;
	double m;
	CDlgOptionsAnalysis Opt;
	CryptPar para;


// == auto-correlation analysis for the ciphertext
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS
	r=0;
	
	Opt.m_VKey = theApp.Options.m_VKey;
	Opt.m_VKorr = theApp.Options.m_VKorr;
	Opt.m_VLen = theApp.Options.m_VLen;
	Opt.m_VBase = theApp.Options.m_VBase;
	
	SymbolArray text(IdConv);
    text.Read(par->infile);
	SCorrelation c(text,min(text.GetSize(),200));	// Auto-Korrelation 1..200 betrachten,
// == additional condition: if the sieved ciphertext length is below 2 ... exit the procedure
	if (c.GetSize() <= 1)
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 2);
		return 0;	
	}
	
	memset(&para,0,sizeof(para));
	para.infile = par->infile;
	para.OldTitle = par->OldTitle;
	para.result = &c;
	if (Opt.m_VKorr) 
		para.flags=(CRYPT_DISPLAY_BG | (par->flags & CRYPT_DO_PROGRESS));
	else
		para.flags= (par->flags & CRYPT_DO_PROGRESS);
	if(c.GetSize()<2)
		para.flags&=!CRYPT_DISPLAY_BG;
    r = Autocorr(&para);
	while(theApp.fs.m_displayed) Sleep(100);
	if(r) return r;
	
	/* removed information dialog according to BE's remarks, 02/07/07
	if (Opt.m_VKorr) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PROCEED,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_ADD,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str, pc_str1, MB_OK);
	}*/
	
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS
	
	av = (int) c.GetAverage();
	mx = (int) c.GetMax(1);
	s = (av + mx) / 2;
	// ~~~~~~~~~ Henrik Koy 20. Nov 2000 
	// Bug: 200 ==> Überlauf! wurde entfernt 
	for(periode=1;periode<c.GetSize();periode++) if(c[periode]>s) break;

// == Display (edit) the assumed key-length and enter the assumed most frequent plaintext-character
	if(Opt.m_VLen) {
		CDlgBinKeyLength dia;
		dia.m_laenge = periode;
		// set dialog title
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_ADD,pc_str1,STR_LAENGE_STRING_TABLE);
        dia.m_title = pc_str1;
		if(IDCANCEL == dia.DoModal()) {
			if(par->flags & CRYPT_DO_WAIT_CURSOR)
				HIDE_HOUR_GLASS
			return r;
		}
		periode = dia.m_laenge;
		MaxChar = dia.m_c;
	}
	
	
// == Partition the ciphertext and evaluate the assumed ADD-Key
	int i;
	for (i=0; i<periode;i++) {
		SymbolArray s=text.Extract(i,periode);
		if (Opt.m_VBase) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADD_MSG_OF,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line2,pc_str,i+1);
			MakeNewName(line,sizeof(line),line2,par->OldTitle);
			GetTmpName(name,"cry",".txt");
			text.Write(name);
			HistogramBin(name,line);
			remove(name);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PROCEED,pc_str,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_ADD,pc_str1,STR_LAENGE_STRING_TABLE);
			if(IDCANCEL==theApp.m_MainWnd->MessageBox(pc_str, pc_str1, MB_OKCANCEL)) Opt.m_VBase = FALSE;
		}
		NGram ng(s);
		// Maximum m suchen und Position j bestimmen
		m=0;
		for(j=255;j>=0;j--)
			if (ng[j]>m) {
				m=ng[j];
				shift=j;
			}
			//		s+=MaxChar-shift;
			//		text.Put(s,i,periode);
			
			//		key[i] = shift-MaxChar;
			key[i] = (shift+256-MaxChar) % 256;
			
	}

	//	key[i]=0;
// == display the ascertained XOR-key
	key[periode]=0;
	if(Opt.m_VKey) {
		CDlgKeyHexAnalysis dia;
		
		CString title;
		title.LoadString(IDS_STRING_ANALYSE_ADD);
		if(IDCANCEL == dia.Display((LPCTSTR)title,(char *) key,periode,false)) {
			if(par->flags & CRYPT_DO_WAIT_CURSOR)
				HIDE_HOUR_GLASS
			return r;
		}
		
		periode = dia.GetLen();
		memcpy(key,dia.GetData(),periode);
	}
	for(i=1;i<periode;i++) { // check for repeated keys
		if(periode%i == 0) {
			if(!memcmp(key,key+i,periode-i)) { // iterated key found
				periode = i;
				for(i=0;i<periode;i++) sprintf(line2+(i*3)," %02.2X", key[i]);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_ON_CONVERT_KEY,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str,line2+1);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_ADD,pc_str,STR_LAENGE_STRING_TABLE);
				theApp.m_MainWnd->MessageBox(line,pc_str,MB_OK);
			}
		}
	}

// == Decrypt the ciphertext 	
	for(i=0;i<periode;i++) sprintf(line2+(i*3)," %02.2X", key[i]);
	SymbolArray KeyArray(IdConv,periode);
	for(i=0;i<periode;i++) KeyArray[i]=key[i];
	// Entschlüsseln
	text -= KeyArray;
	
	GetTmpName(name,"cry",".tmp");
	text.Write(name);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOMATIC_ADD_ANALYSE_OF,pc_str,STR_LAENGE_STRING_TABLE);
	// line2+1: die +1 wegen des ersten zusätzlichen Leereichens, das in den String
	// line2 am Anfang eingefügt worden ist, aber nicht mit ausgegeben werden soll 
	MakeNewName2(line,sizeof(line),pc_str,line2+1,par->OldTitle);
    theApp.ThreadOpenDocumentFileNoMRU(name,line, line2+1);
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS
	
	return r;
}
