//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "multipad.h"
#include "fileutil.h"
#include "CryptDoc.h"
#include "crypt.h"
#include "automatic.h"
#include "TextEingabeHillAngriff.h"
#include "HillSchluesselAusgabe.h"
#include "HillSchluesselAusgabeGross.h"
#include "hill.h"
#include "DialogLaenge.h"
#include "DialogLaengeBin.h"
#include "DialogVienereKey.h"
#include "DialoKeyCaesar.h"
#include "DialogKeyHex.h"
#include "ChrTools.h"
#include "MyDocument.h"

#include <iostream.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char *Pfad; // Directory Path of the main programm

void CaesarAuto(const char *infile, const char *OldTitle)
{
	char name[256], name2[256], line[256], key[256];
	CFile f;
	CMyDocument *NewDoc;

	FILE *fi;
	int i;
	
	fi = fopen(infile,"rb");
	fseek(fi,0,SEEK_END);
	i = ftell(fi);
	fclose(fi);
	if(i < 1) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING41544,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}

	if (theApp.Options.m_CHist) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING41471,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41472,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(line,"%s%s",Pfad,pc_str);
		HistogramASCII(line,pc_str1);
		HistogramASCII(infile, OldTitle);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41473,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41474,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str, pc_str1, MB_OK);
	}
	
	theApp.DoWaitCursor(1);
	
	SymbolArray text(AppConv);
    text.Read(infile);
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Henrik Koy November 2000 
	// Automatische Analyse wird abgebrochen, wenn weinger als 2 Zeichen 
	// für die Analyse zur Verfügung stehen
	if (text.GetSize() <= 1)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41544,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,2);
		AfxMessageBox (line);
		return;	
	}
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	
	SymbolArray deutsch(AppConv);
	LoadString(AfxGetInstanceHandle(),IDS_STRING41471,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line,"%s%s",Pfad,pc_str);
	deutsch.Read(line);
	deutsch+=1;
	
	NGram t(text);
	NGram d(deutsch);
	
	DCorrelation c(d,t);
	
	if (theApp.Options.m_CKorr) {
		// Ausgabe der Korrelation zwischen deutschem Text und dem Chiffrat
		GetTmpName(name,"cry",".plt");
		
		LoadString(AfxGetInstanceHandle(),IDS_STRING41475,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName(line,sizeof(line),pc_str,OldTitle);
		
		c.Show(OStream(name)<< OStream::Title(0) << OStream::Description(0) << OStream::Summary(0));
		
		// get the tmp name without file extension
		strcpy(name2, name);
		name2[strlen(name)-4] = 0x0;
		
		if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) ) {
			CArchive ar( &f, CArchive::store);
			CString s1 = line;
			LoadString(AfxGetInstanceHandle(),IDS_STRING41476,pc_str,STR_LAENGE_STRING_TABLE);
			CString s2 = pc_str;
			LoadString(AfxGetInstanceHandle(),IDS_STRING41476,pc_str,STR_LAENGE_STRING_TABLE);
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
		LoadString(AfxGetInstanceHandle(),IDS_STRING41478,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41474,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str, pc_str1, MB_OK);
	}
	
	int shift=c.FindPeak();
	
	if(theApp.Options.m_CKey) {
		CDialoKeyCaesar dia;
		
		dia.m_string = theApp.TextOptions.m_alphabet[shift];
		if(IDCANCEL == dia.DoModal()) return;
		if(dia.m_string.GetLength() == 1) shift = theApp.TextOptions.m_alphabet.Find(dia.m_string[0]);
		else shift = 0;
	}
	text-=shift;
	text-=1;
	GetTmpName(name,"cry",".tmp");
	text.Write(name);
	ForceReformat(infile,name, FALSE);
	CString csKey = theApp.TextOptions.m_alphabet[shift];
    NewDoc = theApp.OpenDocumentFileNoMRU(name, csKey);
    remove(name);
	if(NewDoc) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING41480,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(key,pc_str,theApp.TextOptions.m_alphabet[shift]);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41481,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName2(line,sizeof(line),pc_str,key,OldTitle);
		NewDoc->SetTitle(line);
    }
	theApp.DoWaitCursor(0);
	
}

UINT VigenereAuto(PVOID p)
{
	char name[256], name2[256], line[256], line2[256], key[256];
	CFile f;
	CryptPar *par;
	OptionsDialog Opt;
	int av, mx, s, periode, r;
	CryptPar para;
	
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(1);
	
	if(par->flags | CRYPT_DO_PROGRESS) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING41482,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	
	Opt.m_VKey = theApp.Options.m_VKey;
	Opt.m_VKorr = theApp.Options.m_VKorr;
	Opt.m_VLen = theApp.Options.m_VLen;
	Opt.m_VBase = theApp.Options.m_VBase;
	
	SymbolArray text(AppConv);
    text.Read(par->infile);
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Henrik Koy November 2000 
	// Automatische Analyse wird abgebrochen, wenn weinger als 2 Zeichen 
	// für die Analyse zur Verfügung stehen
	if (text.GetSize() <= 3)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41544,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,4);
		AfxMessageBox (line);
		return 0;	
	}
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	


	SCorrelation c(text,min(text.GetSize()/* /2 */,200));	// Auto-Korrelation 1..200 betrachten,*/
	
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
	if(r) return r;
	if (Opt.m_VKorr) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41483,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41484,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str, pc_str1, MB_OK);
	}
	
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(1);
	
	av = (int) c.GetAverage(1);
	mx = (int) c.GetMax(1);
	s = (av + mx) / 2;
	for(periode=1;periode<c.GetSize();periode++) if(c[periode]>s) break;
	
// ==========================================================================
// 2. Jan. 2001: Henrik Koy
// Anpassen der automatischen Vigenere Analyse auf Mehrsprachigkeit
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if(Opt.m_VLen) {
		CDialogLaenge dia;
		dia.m_laenge = periode;
		if(IDCANCEL == dia.DoModal()) {
			if(par->flags & CRYPT_DO_WAIT_CURSOR)
				theApp.DoWaitCursor(-1);
			return r;
		}
		periode = dia.m_laenge;
	
		switch ( dia.m_Sprache ) {
		case(0):  // german
			LoadString(AfxGetInstanceHandle(),IDS_STRING41471,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,"%s%s",Pfad,pc_str);
			break;
		case(1):  // english
			LoadString(AfxGetInstanceHandle(),IDS_STRING41479,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,"%s%s",Pfad,pc_str);
			break;
		default: // is german
			LoadString(AfxGetInstanceHandle(),IDS_STRING41471,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,"%s%s",Pfad,pc_str);
		}
	}

	SymbolArray language(AppConv);
	language.Read(line);
	language += 1;
	NGram d(language);
// ================ DAS WARS ====================================================

	if (Opt.m_VBase) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING41471,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41472,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(line,"%s%s",Pfad,pc_str);	
		HistogramASCII(line, pc_str1);
	}
	
	// Einzelne Caesars Brechen	
	for (int i=0; i<periode;i++) {
		SymbolArray s=text.Extract(i,periode);
		if (Opt.m_VBase) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING41486,pc_str,STR_LAENGE_STRING_TABLE);
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
		//		s-=shift;
		//		text.Put(s,i,periode);
		
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Henrik Koy 21.11.00 
		// modulo c.GetSize() (Alphabet Größe) Rechnen! (um ein Arrayüberlauf zu verhindern).
		key[i] = theApp.TextOptions.m_alphabet[(shift+1) % c.GetSize()];
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if (Opt.m_VBase) {
			// Ausgabe der Korrelation zwischen deutschem Text und dem Chiffrat
			GetTmpName(name,"cry",".plt");
			LoadString(AfxGetInstanceHandle(),IDS_STRING41487,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str,i+1);
			
			c.Show(OStream(name)<< OStream::Title(0) << OStream::Description(0) << OStream::Summary(0));
			
			// get the tmp name without file extension
			strcpy(name2, name);
			name2[strlen(name)-4] = 0x0;
			
			if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) ) {
				CArchive ar( &f, CArchive::store);
				CString s1 = line;
				LoadString(AfxGetInstanceHandle(),IDS_STRING41476,pc_str,STR_LAENGE_STRING_TABLE);
				CString s2 = pc_str;
				LoadString(AfxGetInstanceHandle(),IDS_STRING41477,pc_str,STR_LAENGE_STRING_TABLE);
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
			
			LoadString(AfxGetInstanceHandle(),IDS_STRING41488,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str,i+1,theApp.TextOptions.m_alphabet[shift]);
			LoadString(AfxGetInstanceHandle(),IDS_STRING41484,pc_str,STR_LAENGE_STRING_TABLE);
			if(IDCANCEL==theApp.m_MainWnd->MessageBox(line,pc_str,MB_OKCANCEL)) Opt.m_VBase = FALSE;
		}
		
	}
	key[i]=0;
	SymbolArray KeyArray(AppConv);
	if(Opt.m_VKey) {
		CDialogVienereKey dia;
		
		dia.m_Str = key;
		if(IDCANCEL == dia.DoModal()) return 0;
		strcpy(key,dia.m_Str);
		
		//		LoadString(AfxGetInstanceHandle(),IDS_STRING41535,pc_str,STR_LAENGE_STRING_TABLE);
		//		sprintf(line,pc_str,key);
		//		LoadString(AfxGetInstanceHandle(),IDS_STRING41484,pc_str,STR_LAENGE_STRING_TABLE);
		//		theApp.m_MainWnd->MessageBox(line,pc_str,MB_OK);
	}
	periode = strlen(key); // check for iterated key
	for(i=1;i<periode;i++) {
		if(periode%i == 0) {
			if(!memcmp(key,key+i,periode-i)) { // iterated key found
				key[i]=0;
				LoadString(AfxGetInstanceHandle(),IDS_STRING41548,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str,key);
				LoadString(AfxGetInstanceHandle(),IDS_STRING41484,pc_str,STR_LAENGE_STRING_TABLE);
				theApp.m_MainWnd->MessageBox(line,pc_str,MB_OK);
			}
		}
	}
	KeyArray.ReadString(key);
	text -= KeyArray;
	// und ausgeben
	GetTmpName(name,"cry",".tmp");
	text.Write(name);
	ForceReformat(par->infile,name, FALSE);
	LoadString(AfxGetInstanceHandle(),IDS_STRING41489,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName2(line,sizeof(line),pc_str,key,par->OldTitle);
    theApp.ThreadOpenDocumentFileNoMRU(name,line,key);
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(1);
	
	return 0;
}

// Plaintextangriff fuer Hill Cipher
void HillPlain(const char *infile, const char *OldTitle)
{
	// Hill Klasse anlegen und Daten in Hill-Klasse fuellen
	hill hillklasse(theApp.TextOptions.m_alphabet.GetBuffer(0));
	
	// Überprüfung, ob Eingabedatei mindestens ein Zeichen enthält. 
	CFile datei(infile, CFile::modeRead);
	long infile_zeichen_anz = 0;
	char c;
	while(datei.Read(&c,1))
	{
		// Falls Gross-/Kleinschreibung ignoriert werden soll,
		// muessen auch die Kleinbuchstaben mitgezaehlt werden.
		if ( hillklasse.ist_erlaubtes_zeichen(c) ||
			( (theApp.TextOptions.m_IgnoreCase) && (MyIsLower(c)) && 
			(hillklasse.ist_erlaubtes_zeichen(MyToUpper(c))) ) )
		{
			infile_zeichen_anz++;
		}
	}
	datei.Close();
	
	if (! infile_zeichen_anz)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41544,pc_str,STR_LAENGE_STRING_TABLE);
		char line[256];
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}
	// jetzt hat die Eingabedatei auf jeden Fall mehr als ein zu verschlüsselndes Zeichen
	
	// Eingabe des Klartextes bzw. verschluesselten Textes 
	CTextEingabeHillAngriff EingabeDialog;	
	
	if (EingabeDialog.DoModal() == IDOK)
	{
		theApp.DoWaitCursor(1);
		
		// Falls Gross-/Kleinschreibung ignoriert werden soll:
		// Es werden alle Kleinbuchstaben in Grossbuchstaben umgewandelt
		if(theApp.TextOptions.m_IgnoreCase)
		{
			MyToUpper(EingabeDialog.m_EingabeFeld);
		}
		
		int laenge = EingabeDialog.m_EingabeFeld.GetLength();
		
		char *str;
		str = new char[laenge+1];
		// wir legen vielleicht einiges zuviel an Speicher an 
		// (falls viele nicht zu verschluesselnde Zeichen in der Datei vorhanden sind)
		long laenge_str = 0;
		
		for (int i=0; i<laenge; i++)
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
		if (! laenge_str)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING41544,pc_str,STR_LAENGE_STRING_TABLE);
			char line[256];
			sprintf(line,pc_str,1);
			AfxMessageBox (line);
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
				else if ( (theApp.TextOptions.m_IgnoreCase) && MyIsLower(c) && 
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
			square_matrix *mat;
			
			int hill_rc;
			int hill_rc_dims[HILL_MAX_DIM_GROSS];
			
			hill_rc = hillklasse.angriff(EingabeDialog.von, EingabeDialog.bis, &mat, hill_rc_dims);
			
			// Rueckgabewerte siehe hill.h
			if (hill_rc == HILL_OK || hill_rc == HILL_OK_LAENGE_UNTERSCHIEDLICH)	
			{
				if (mat->get_dim() <= 5)
				{
					// Inhalt von mat anzeigen
					CHillSchluesselAusgabe AusgabeFenster;
					
					// War einer der Texte kuerzer ?
					if (hill_rc == HILL_OK_LAENGE_UNTERSCHIEDLICH)
					{
						LoadString(AfxGetInstanceHandle(),IDS_STRING41563,pc_str,STR_LAENGE_STRING_TABLE);
						AfxMessageBox(pc_str,MB_ICONINFORMATION);
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
					CHillSchluesselAusgabeGross AusgabeFenster;
					
					// War einer der Texte kuerzer ?
					if (hill_rc == HILL_OK_LAENGE_UNTERSCHIEDLICH)
					{
						LoadString(AfxGetInstanceHandle(),IDS_STRING41563,pc_str,STR_LAENGE_STRING_TABLE);
						AfxMessageBox(pc_str,MB_ICONINFORMATION);
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
				LoadString(AfxGetInstanceHandle(),IDS_STRING41561,pc_str,STR_LAENGE_STRING_TABLE);
				AfxMessageBox(pc_str, MB_ICONSTOP);
			}
			else if (hill_rc == HILL_NICHT_OK_WIDERSPRUCH)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING41562,pc_str,STR_LAENGE_STRING_TABLE);
				AfxMessageBox(pc_str, MB_ICONSTOP);
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
				
				LoadString(AfxGetInstanceHandle(),IDS_STRING41565,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1,pc_str,widerspruch.GetBuffer(0));
				cstr += pc_str1;
				cstr += "\n";
				
				LoadString(AfxGetInstanceHandle(),IDS_STRING41564,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1,pc_str,nicht_gefunden.GetBuffer(0));
				cstr += pc_str1;
				
				AfxMessageBox(cstr.GetBuffer(0), MB_ICONSTOP);
			}
			else // Das darf nicht passieren, wir geben aus: Der Schluessel wurde nicht gefunden
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING41490,pc_str,STR_LAENGE_STRING_TABLE);
				AfxMessageBox(pc_str, MB_ICONSTOP);
			}
		}
		
		theApp.DoWaitCursor(0);
	}
}

UINT XorAuto(PVOID p)
{
	char name[256], line[256], line2[256], MaxChar;
	unsigned char key[256];
	CFile f;
	CryptPar *par;
	int j, shift, av, mx, periode, s, r, k;
	double m;
	OptionsDialog Opt;
	CryptPar para;
	
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(1);
	r=0;
	
	Opt.m_VKey = theApp.Options.m_VKey;
	Opt.m_VKorr = theApp.Options.m_VKorr;
	Opt.m_VLen = theApp.Options.m_VLen;
	Opt.m_VBase = theApp.Options.m_VBase;
	
	SymbolArray text(IdConv);
    text.Read(par->infile);
	SCorrelation c(text,min(text.GetSize(),200));	// Auto-Korrelation 1..200 betrachten,
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Henrik Koy November 2000 
	// Automatische Analyse wird abgebrochen, wenn weinger als 3 Zeichen 
	// für die Analyse zur Verfügung stehen
	if (c.GetSize() <= 1)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41544,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,2);
		AfxMessageBox (line);
		return 0;	
	}
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	
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
	if(r) return r;
	if (Opt.m_VKorr) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41483,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41491,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str, pc_str1, MB_OK);
	}
	
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(1);
	
	av = (int) c.GetAverage();
	mx = (int) c.GetMax(1);
	s = (av + mx) / 2;
	for(periode=1;periode<c.GetSize()/*200*/;periode++) if(c[periode]>s) break;
	
	if(Opt.m_VLen) {
		CDialogLaengeBin dia;
		dia.m_laenge = periode;
		if(IDCANCEL == dia.DoModal()) {
			if(par->flags & CRYPT_DO_WAIT_CURSOR)
				theApp.DoWaitCursor(-1);
			return r;
		}
		periode = dia.m_laenge;
		MaxChar = dia.m_c;
	}
	
	// Einzelne XORs Brechen	
	for (int i=0; i<periode;i++) {
		SymbolArray s=text.Extract(i,periode);
		if (Opt.m_VBase) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING41492,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line2,pc_str,i+1);
			MakeNewName(line,sizeof(line),line2,par->OldTitle);
			GetTmpName(name,"cry",".asc");
			text.Write(name);
			HistogramBin(name,line);
			remove(name);
			LoadString(AfxGetInstanceHandle(),IDS_STRING41483,pc_str,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING41491,pc_str1,STR_LAENGE_STRING_TABLE);
			if(IDCANCEL==theApp.m_MainWnd->MessageBox(pc_str, pc_str1, MB_OKCANCEL)) Opt.m_VBase = FALSE;
		}
		NGram ng(s);
		m=0;
		for(j=255;j>=0;j--)
			if (ng[j]>m) {
				m=ng[j];
				shift=j;
			}
			//		s^=MaxChar^shift;
			//		text.Put(s,i,periode);
			
			key[i] = shift ^ MaxChar;
			
	}
	key[i]=0;
	if(Opt.m_VKey) {
		CDialogKeyHex dia;
		
		if(IDCANCEL == dia.Display((char *) key,periode)) {
			if(par->flags & CRYPT_DO_WAIT_CURSOR)
				theApp.DoWaitCursor(-1);
			return r;
		}
		
		periode = dia.GetLen();
		memcpy(key,dia.GetData(),periode);
		//		LoadString(AfxGetInstanceHandle(),IDS_STRING41493,pc_str,STR_LAENGE_STRING_TABLE);
		//		sprintf(line,pc_str,line2+1);
		//		LoadString(AfxGetInstanceHandle(),IDS_STRING41491,pc_str,STR_LAENGE_STRING_TABLE);
		//		theApp.m_MainWnd->MessageBox(line,pc_str,MB_OK);
	}
	for(i=1;i<periode;i++) { // check for repeated keys
		if(periode%i == 0) {
			if(!memcmp(key,key+i,periode-i)) { // iterated key found
				periode = i;
				for(i=0;i<periode;i++) sprintf(line2+(i*3)," %02.2X", key[i]);
				LoadString(AfxGetInstanceHandle(),IDS_STRING41548,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str,line2+1);
				LoadString(AfxGetInstanceHandle(),IDS_STRING41491,pc_str,STR_LAENGE_STRING_TABLE);
				theApp.m_MainWnd->MessageBox(line,pc_str,MB_OK);
			}
		}
	}
	// und ausgeben
	for(i=0;i<periode;i++) sprintf(line2+(i*3)," %02.2X", key[i]);
	SymbolArray KeyArray(IdConv,periode);
	for(k=0;k<periode;k++) KeyArray[k]=key[k];
	text ^= KeyArray;
	
	GetTmpName(name,"cry",".tmp");
	text.Write(name);
	LoadString(AfxGetInstanceHandle(),IDS_STRING41494,pc_str,STR_LAENGE_STRING_TABLE);
	// line2+1: die +1 wegen des ersten zusätzlichen Leereichens, das in den String
	// line2 am Anfang eingefügt worden ist, aber nicht mit ausgegeben werden soll 
	MakeNewName2(line,sizeof(line),pc_str,line2+1,par->OldTitle);
    theApp.ThreadOpenDocumentFileNoMRU(name,line, line2+1);
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(0);
	
	return r;
}

UINT AddAuto(PVOID p)
{
	char name[256], line[256], line2[256], MaxChar;
	unsigned char key[256];
	CFile f;
	CryptPar *par;
	int j, shift, av, mx, periode, s, r;
	double m;
	OptionsDialog Opt;
	CryptPar para;


	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(1);
	r=0;
	
	Opt.m_VKey = theApp.Options.m_VKey;
	Opt.m_VKorr = theApp.Options.m_VKorr;
	Opt.m_VLen = theApp.Options.m_VLen;
	Opt.m_VBase = theApp.Options.m_VBase;
	
	SymbolArray text(IdConv);
    text.Read(par->infile);
	SCorrelation c(text,min(text.GetSize(),200));	// Auto-Korrelation 1..200 betrachten,
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Henrik Koy November 2000 
	// Automatische Analyse wird abgebrochen, wenn weinger als 3 Zeichen 
	// für die Analyse zur Verfügung stehen
	if (c.GetSize() <= 1)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41544,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,2);
		AfxMessageBox (line);
		return 0;	
	}
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	
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
	if(r) return r;
	if (Opt.m_VKorr) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41483,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41495,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str, pc_str1, MB_OK);
	}
	
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(1);
	
	av = (int) c.GetAverage();
	mx = (int) c.GetMax(1);
	s = (av + mx) / 2;
	// ~~~~~~~~~ Henrik Koy 20. Nov 2000 
	// Bug: 200 ==> Überlauf! wurde entfernt 
	for(periode=1;periode<c.GetSize()/*200*/;periode++) if(c[periode]>s) break;
	
	if(Opt.m_VLen) {
		CDialogLaengeBin dia;
		dia.m_laenge = periode;
		if(IDCANCEL == dia.DoModal()) {
			if(par->flags & CRYPT_DO_WAIT_CURSOR)
				theApp.DoWaitCursor(-1);
			return r;
		}
		periode = dia.m_laenge;
		MaxChar = dia.m_c;
	}
	
	
	// Einzelne Adds Brechen	
	for (int i=0; i<periode;i++) {
		SymbolArray s=text.Extract(i,periode);
		if (Opt.m_VBase) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING41496,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line2,pc_str,i+1);
			MakeNewName(line,sizeof(line),line2,par->OldTitle);
			GetTmpName(name,"cry",".asc");
			text.Write(name);
			HistogramBin(name,line);
			remove(name);
			LoadString(AfxGetInstanceHandle(),IDS_STRING41483,pc_str,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING41495,pc_str1,STR_LAENGE_STRING_TABLE);
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
	key[periode]=0;
	if(Opt.m_VKey) {
		CDialogKeyHex dia;
		
		if(IDCANCEL == dia.Display((char *) key,periode)) {
			if(par->flags & CRYPT_DO_WAIT_CURSOR)
				theApp.DoWaitCursor(-1);
			return r;
		}
		
		periode = dia.GetLen();
		memcpy(key,dia.GetData(),periode);
		
		//		LoadString(AfxGetInstanceHandle(),IDS_STRING41493,pc_str,STR_LAENGE_STRING_TABLE);
		//		sprintf(line,pc_str,line2+1);
		//		LoadString(AfxGetInstanceHandle(),IDS_STRING41495,pc_str,STR_LAENGE_STRING_TABLE);
		//		theApp.m_MainWnd->MessageBox(line,pc_str,MB_OK);
	}
	for(i=1;i<periode;i++) { // check for repeated keys
		if(periode%i == 0) {
			if(!memcmp(key,key+i,periode-i)) { // iterated key found
				periode = i;
				for(i=0;i<periode;i++) sprintf(line2+(i*3)," %02.2X", key[i]);
				LoadString(AfxGetInstanceHandle(),IDS_STRING41548,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str,line2+1);
				LoadString(AfxGetInstanceHandle(),IDS_STRING41495,pc_str,STR_LAENGE_STRING_TABLE);
				theApp.m_MainWnd->MessageBox(line,pc_str,MB_OK);
			}
		}
	}
	// und ausgeben
	for(i=0;i<periode;i++) sprintf(line2+(i*3)," %02.2X", key[i]);
	SymbolArray KeyArray(IdConv,periode);
	for(i=0;i<periode;i++) KeyArray[i]=key[i];
	// Entschlüsseln
	text -= KeyArray;
	
	GetTmpName(name,"cry",".tmp");
	text.Write(name);
	LoadString(AfxGetInstanceHandle(),IDS_STRING41497,pc_str,STR_LAENGE_STRING_TABLE);
	// line2+1: die +1 wegen des ersten zusätzlichen Leereichens, das in den String
	// line2 am Anfang eingefügt worden ist, aber nicht mit ausgegeben werden soll 
	MakeNewName2(line,sizeof(line),pc_str,line2+1,par->OldTitle);
    theApp.ThreadOpenDocumentFileNoMRU(name,line, line2+1);
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(0);
	
	return r;
}
