//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// CrypTool.cpp : Defines the class behaviors for the Multipad application.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "CrypToolApp.h"
#include "CryptDoc.h"
#include "CPlotDocument.h"
#include "PlotView.h"
#include "BlockView.h"
#include "HexView.h"
#include "Cryptography.h"
#include "CryptDocTemplate.h"
#include "DlgOptionsAnalysis.h"
// #include "ECsecude.h"
#include <locale.h>
#include "DlgAbout.h"

#include "AsymmetricEncryption.h" // für KeyGen() in OnCRYPTKeyGen()
#include "DlgKeyAsym.h" // für OnShowKeys()

#include "DlgRSADemo.h"
#include "RandomAnalysisTools.h"
#include "DlgPrimesGeneratorDemo.h"
#include "DlgFactorisationDemo.h"
#include "DlgKeyFromPassword.h"
#include "DlgRandomGenerator.h"
#include "DlgTipsAndTricks.h"
#include "DlgHybridEncryptionDemo.h"
#include "DlgOptionsStartoptions.h"

// globale Variablen fuer Zugriff auf Stringtable
// Deklariert in CrypTool.h
char pc_str[STR_LAENGE_STRING_TABLE];
char pc_str1[STR_LAENGE_STRING_TABLE];

// Globale Variablen fuer Zugriff auf Initialisierunsdatei
char *initializing_file="EC-Param.ini"; // This is the filename of the file, which contains the initializing values for assymmetric key generation
char *initializing_file_2="TEST-Param.ini";

// Globale Variablen fuer wichtige Pfade und Dateien
char *Pfad; // Verzeichnis in dem CrypTool zur Laufzeit liegt
char *PseVerzeichnis; // PSE-Verzeichnis von CrypTool =Pfad+"/PSE";
char *CaPseVerzeichnis; // =Pfad+"/PSE/PSECA";
char *CaPseDatei; // =Pfad+"/PSE/PSECA/pseca";

// globale Variable, die angibt, ob der Dialog für kleine oder große Schlüssel
// und welche Dimension bei Hill Verfahren geöffnet werden soll
// Werte: siehe CrypTool.h
int iHillSchluesselFensterGroesse;
int iHillSchluesselDim;

// globale Variable, in der immer die Fenster Handle des aktive Fensters steht
HWND hWndAktivesFenster;
 

CCrypToolApp NEAR theApp;


BEGIN_MESSAGE_MAP(CCrypToolApp, CWinApp)
	//{{AFX_MSG_MAP(CCrypToolApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_OPTIONS_ANALYSIS, OnOptionsAnalysis)
	ON_COMMAND(ID_WINDOW_CLOSE_ALL, OnWindowCloseAll)
	ON_COMMAND(ID_OPTTEXT, OnOpttext)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_KeyGen, OnUpdateNeedSecudeTicket)
	ON_COMMAND(ID_SHOW_ALL_EC_KEYS, OnShowKeys)
	ON_COMMAND(ID_CRYPT_KeyGen, OnKeyGen)
	ON_COMMAND(ID_EINZELVERFAHREN_TUTORIAL_PRIMZAHLENGENERIEREN, OnEinzelverfahrenTutorialPrimzahlengenerieren)
	ON_COMMAND(ID_EINZELVERFAHREN_TUTORIAL_RSAALGORITHMUS, OnEinzelverfahrenTutorialRsaalgorithmus)
	ON_COMMAND(ID_EINZELVERFAHREN_TUTORIALFRKLEINEZAHLEN_FAKTORISIERENIFP, OnEinzelverfahrenTutorialfrkleinezahlenFaktorisieren)
	ON_COMMAND(ID_EINZELVERFAHREN_SCHLUESSELGENERIEREN, OnEinzelverfahrenSchluesselgenerieren)
	ON_COMMAND(ID_ZUFALL_GENERATOREN, OnGenRandomData)
	ON_COMMAND(ID_HASH_OFAFILE, OnHashOfAFile)
	ON_COMMAND(ID_EINZELVERFAHREN_SIGN, OnEinzelverfahrenTutorialSignaturerzeugung)
	ON_COMMAND(ID_VERENTSCHLSSELN_HYBRIDVERFAHREN_HYBRIDVERSCHLSSELUNG, OnVerentschlsselnHybridverfahrenHybridverschlsselung)
	ON_UPDATE_COMMAND_UI(ID_SHOW_ALL_EC_KEYS, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_KeyGen, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_VERENTSCHLSSELN_HYBRIDVERFAHREN_HYBRIDVERSCHLSSELUNG, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_VERENTSCHLSSELN_HYBRIDVERFAHREN_HYBRIDENTSCHLSSELUNG, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_HASH_OFAFILE, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_EINZELVERFAHREN_SIGN, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_EINZELVERFAHREN_SCHLUESSELGENERIEREN, OnUpdateNeedSecudeTicket)
	ON_COMMAND(ID_OPTIONS_STARTOPTIONS, OnOptionsStartoptions)
	//}}AFX_MSG_MAP

	//ON_COMMAND(ID_VERENTSCHLSSELN_HYBRIDVERFAHREN_HYBRIDVERSCHLSSELUNG, OnVerentschlsselnHybridverfahrenHybridverschlsselung)
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)     // file commands...
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
// BEGINN Fuer Hilfe-Funktionalitaet eingefuegt
	// Globale Hilfebefehle
	ON_COMMAND(ID_HELP_FINDER, CWinApp::OnHelpFinder)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CWinApp::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CWinApp::OnHelpFinder)

// ENDE
END_MESSAGE_MAP()

BOOL CCrypToolApp::InitInstance()
{
//	_tsetlocale(LC_ALL, _T(""));

	char buffer[1024], *p;
	int n;

	//Initialisierung der globalen Variablen
	m_HexFormat = RegisterClipboardFormat("HexFormat");
	iHillSchluesselFensterGroesse = HILL_SCHLUESSEL_KLEIN;
	iHillSchluesselDim = 2;

	hWndAktivesFenster = 0;

	KeyOpenDocumentFile.Empty();
	KeyTypeOpenDocumentFile = SCHLUESSEL_INIT;

	// CaPseDatei, CaPseVerzeichnis und Pfad (alle drei char *)
	// Es soll zunächst der (komplette) Pfad der Anwendung herausgefunden werden.
	// Hierzu muß unterschieden werden, ob die Anwendung von der Kommandozeile oder
	// aus dem Explorer (oder einer ähnlichen Anwendung) heraus aufgerufen wird.
	
	CString Pfad2=GetCommandLine();
	
	// AfxMessageBox (Pfad2);

	if (Pfad2.Find("\\")==-1){  // Es liegt noch kein kompletter Pfad vor
		// Pfad2.Find(":\\") wurde geändert in Pfad2.Find("\\"), da bei Programmaufrufen
		// über das Netz ein falscher Pfad angegeben wurde.
		// Setze den Pfad aus GetCommandLine() und GetCurrentDirectory zusammen
		char* Pfad3=(char*)malloc(100);
		GetCurrentDirectory(99,Pfad3);
		CString Pfad4=(CString)Pfad3;
	
		// AfxMessageBox (Pfad3);

		free (Pfad3);
		// Setze den Pfad zusammen
		Pfad2=Pfad4+"\\"+Pfad2;

		// AfxMessageBox (Pfad2);

		// Schneide das führende Hochkomma (") weg
		Pfad2=Pfad2.Left(Pfad2.ReverseFind(92)+1);

		// AfxMessageBox (Pfad2);

	}
	else{						// GetCommandLine hat bereits den kompletten Pfad geliefert
		// Schneide den Anwendungsnamen weg (nur der Pfad interessiert uns)
		Pfad2=Pfad2.Left(Pfad2.ReverseFind(92)+1);

		// AfxMessageBox (Pfad2);

		// Schneide das führende Hochkomma (") weg
		Pfad2.SetAt(0,' ');
		Pfad2.TrimLeft();
	
		// AfxMessageBox (Pfad2);

	}

	// Umwandeln der Baskslashes in Slashes
	for (int i=0;i<Pfad2.GetLength();i++){
		if (Pfad2[i]==92){
			Pfad2.SetAt(i,47);}
	}

	// AfxMessageBox (Pfad2);
	
	//Die beiden folgenden Zeilen müssen für die endgültige Toolkit-Version (andere
	//Verzeichnisstruktur) herausgenommen werden!!!
	//Pfad2=Pfad2.Left(Pfad2.ReverseFind(92));
	//Pfad2=Pfad2.Left(Pfad2.ReverseFind(92));

	//Kopieren des Inhalts von CString Pfad2 nach char *Pfad
	LPTSTR help1 = new TCHAR[Pfad2.GetLength()+1];
	_tcscpy(help1, Pfad2);
	Pfad=help1;
	
	CString PseV, CaPseD, CaPseV;
	PseV  =Pfad2+"PSE";
	CaPseD=Pfad2+"PSE/PSECA/pseca";
	CaPseV=Pfad2+"PSE/PSECA";
		
	LPTSTR help2 = new TCHAR[CaPseD.GetLength()+1];
	_tcscpy(help2, CaPseD);
	CaPseDatei=help2;

	LPTSTR help3 = new TCHAR[CaPseV.GetLength()+1];
	_tcscpy(help3, CaPseV);
	CaPseVerzeichnis=help3;

	LPTSTR help4 = new TCHAR[PseV.GetLength()+1];
	_tcscpy(help4, PseV);
	PseVerzeichnis=help4;

	//Ende der Initialiserung der globalen Variablen

	Enable3dControls();
	/* Einstellen der Länge der MRU-Liste */
	LoadStdProfileSettings(10);
    MRU_Flag = TRUE;

	AddDocTemplate(new CCryptDocTemplate(IDR_TEXTTYPE,
		RUNTIME_CLASS(CCryptDoc), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CAppEditView)));
	AddDocTemplate(new CCryptDocTemplate(IDR_ASCTYPE,
		RUNTIME_CLASS(CAscDoc), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CBlockView)));
	AddDocTemplate(new CCryptDocTemplate(IDR_PLOTTYPE,
		RUNTIME_CLASS(CPlotDocument), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CPlotView)));
	AddDocTemplate(new CCryptDocTemplate(IDR_HEXTYPE,
		RUNTIME_CLASS(CHexDoc), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CHexView)));

	m_pMainWnd = new CMainFrame;
	m_MainWnd = m_pMainWnd;
	((CFrameWnd*)m_pMainWnd)->LoadFrame(IDR_MAINFRAME);
	m_pMainWnd->ShowWindow(m_nCmdShow);

	// enable file manager drag/drop and DDE Execute open
	m_pMainWnd->DragAcceptFiles();
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;// nothing s'gonna happen at application startup
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Am Anfang ist noch kein Fenster geöffnet, die Hilfe soll mit "Wie Sie starten geöffnet werden"
	//::WinHelp(0, AfxGetApp()->m_pszHelpFilePath, HELP_COMMAND, (DWORD)"JumpId(starten)");
	// WinHelp(ID_WIE_SIE_STARTEN+0x10000);

	// initialize the application dependent Converter
	AppConv.SetAlphabet(TextOptions.m_alphabet.GetBuffer(257), TextOptions.m_IgnoreCase);

	SecudeStatus = SecudeLib.OpenSecudeLib(); // secude und Ticket verfuegbar ?
	if(SecudeStatus!=2) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ON_SECUDE_DLL,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(NULL,pc_str,pc_str1,MB_ICONWARNING|MB_OK);
	}

	// Secude ptr fuer EC-Lib setzen
#define DoOneFn(a,b,c,d) ECSecudeLib.##c = SecudeLib.##c;
#define DoOneData(a,b) ECSecudeLib.##b = SecudeLib.##b;
	DoECAll
#undef DoOneFn
#undef DoOneData

	// nach AES-Selfextractor suchen

	n = SearchPath(NULL,"AESTool.exe", NULL, 1023, buffer, &p);
	if(n>0) {
		m_Selfextract_EXE = (char *) malloc(n+2);
		strcpy(m_Selfextract_EXE, buffer);
	}
	else
		m_Selfextract_EXE = NULL;

	// korrektes Helpfile laden
	CString HlpTmp;
	free((void*)m_pszHelpFilePath);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HELPNAME,pc_str,STR_LAENGE_STRING_TABLE);
	HlpTmp = Pfad;
	HlpTmp += pc_str;
	m_pszHelpFilePath=_tcsdup(HlpTmp);


	// Tipps & Tricks anzeigen
	CDlgTipsAndTricks Tipps;
	Tipps.m_DoNotShowThisAgain = GetProfileInt("Settings","NoTipps",FALSE);
	if(FALSE == Tipps.m_DoNotShowThisAgain)
	{
		Tipps.DoModal();
		WriteProfileInt("Settings", "NoTipps", Tipps.m_DoNotShowThisAgain);
	}

	if(1 == GetProfileInt("Settings", "SampleTextFile", 1))
	{
		FILE *f;
		CString filename = Pfad, help;

		help.LoadString(IDS_STRING_SAMPLE_FILE);
		filename = filename + help;
		if(f = fopen(filename, "r"))	// öffnet die Beispiel-Datei, sofern sie gefunden wurde
		{
			fclose(f);
			OpenDocumentFileNoMRU(filename, "", SCHLUESSEL_LINEAR);
		}
		WriteProfileInt("Settings", "SampleTextFile", 1);
	}
	
	// Enable RichEdit Windows...
	AfxEnableControlContainer();
	return TRUE;
}

void CCrypToolApp::OnAppAbout()
{
	// Aenderung Jens Liebehenschel, 18.02.00
	// Beim Doppelklick kam nicht mehr das Fenster mit den Namen der Autoren.
	// Die Nachricht wird nur bei Ansprechen über die Klasse CDlgAbout behandelt.
//	CDialog(IDD_ABOUT).DoModal();
	CDlgAbout klasse;
	klasse.DoModal();
	// Ende der Aenderung
}

IMPLEMENT_DYNCREATE(CMainFrame, CMDIFrameWnd)
BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_OPTIONS_PLOT, OnOptionsPlot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT buttons[] =
{
	ID_FILE_NEW, ID_FILE_OPEN, ID_FILE_SAVE, ID_SEPARATOR,
	ID_EDIT_CUT, ID_EDIT_COPY, ID_EDIT_PASTE, ID_SEPARATOR,
	ID_FILE_PRINT, ID_APP_ABOUT
};

static UINT indicators[] =
{
	ID_SEPARATOR, ID_INDICATOR_CAPS, ID_INDICATOR_NUM, ID_INDICATOR_SCRL
};

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	((m_ToolBar.Create(this) &&
// Die folgende Zeile ist neu, dafuer mussten die beiden naechsten Zeilen raus
		m_ToolBar.LoadToolBar(IDR_MAINFRAME) &&
//		m_ToolBar.LoadBitmap(IDR_MAINFRAME) &&
//		m_ToolBar.SetButtons(buttons, sizeof(buttons)/sizeof(UINT)) &&
		m_StatusBar.Create(this) &&
		m_StatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	  ? 0 : -1);

	// Kopiert aus einem vom Application Wizard erzeugten MDI-Projekt
	// BEGINN
	// ZU ERLEDIGEN: Entfernen, wenn Sie keine QuickInfos oder variable Symbolleiste wünschen
	m_ToolBar.SetBarStyle(m_ToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// ZU ERLEDIGEN: Löschen Sie diese drei Zeilen, wenn Sie nicht wollen, dass die Symbolleiste
	//  andockbar ist.
	m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBar);
	// ENDE

	return CMDIFrameWnd::OnCreate(lpCreateStruct);
}

IMPLEMENT_DYNCREATE(CPadDoc, CAppDocument)
BEGIN_MESSAGE_MAP(CPadDoc, CAppDocument)
	//{{AFX_MSG_MAP(CPadDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPadDoc::Serialize(CArchive& ar)
{
	((CAppEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////

void CCrypToolApp::AddToRecentFileList(LPCTSTR lpszPathName)
{
    if(MRU_Flag) CWinApp::AddToRecentFileList(lpszPathName);
}

// Ein neues Dokument (CAppDocument) wird geoeffnet und die Informationen
// Window Handle des Vaterfanster, Schluessel und Type des Schluessels
// in diesem Dokuemnt gespeichert.
// Ausserdem wird dieses neue Dokument nicht in die Recent-Liste aufgenommen.
// Parameter: Dateiname der zu oeffnenden Datei
//				schluessel (vorbelegt mit "")
//				Type des Schluessels (vorbelegt mit SCHLUESSEL_LINEAR)
CAppDocument * CCrypToolApp::OpenDocumentFileNoMRU(const char *name, CString Key, int KeyType)
{
    BOOL oldflag;
    CAppDocument *doc;

    oldflag = MRU_Flag;
    MRU_Flag = FALSE;

	// Vor dem Öffnen des neuen Dokuments die WindowHandle 
	// und den View des aktiven Fensters merken.
	HWND HWND_hilf = hWndAktivesFenster; // global
	CWnd* CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();

    doc = (CAppDocument*)OpenDocumentFile(name);

	doc->SetModifiedFlag(FALSE);
	doc->hWndVaterFenster = HWND_hilf;
	doc->CWndVaterFenster = CWnd_hilf;
	doc->csSchluessel = Key;
	doc->iSchluesselTyp = KeyType;
	doc->ClearPathName();

    MRU_Flag = oldflag;
    return doc;
}

BOOL CCrypToolApp::WriteProfileDouble( LPCTSTR lpszSection, LPCTSTR lpszEntry, double Value )
{
	char line[128];
	sprintf(line,"%g",Value);
	return WriteProfileString(lpszSection, lpszEntry, line);
}

void CCrypToolApp::OnOptionsAnalysis() 
{
	Options.DoModal();
}

void CCrypToolApp::OnWindowCloseAll() 
{
	SaveAllModified();
	CloseAllDocuments(FALSE);	
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	char line[128];
	CAppDocument *NewDoc = NULL;
	int n;
/*	static int state=0;*/

	if(nIDEvent == 42) {
		switch(theApp.OpenBGFlag) {
		case(0):
			break;
		case(1):
			break;
		case(2):
			NewDoc = theApp.OpenDocumentFileNoMRU(theApp.OpenPath, theApp.KeyOpenDocumentFile, 
												theApp.KeyTypeOpenDocumentFile);
			theApp.KeyOpenDocumentFile.Empty();
			theApp.KeyTypeOpenDocumentFile = SCHLUESSEL_INIT;
			if(NewDoc) {
				NewDoc->SetTitle(theApp.OpenTitle);
				theApp.DoWaitCursor(0);
			}
			remove(theApp.OpenPath);
			strcpy(line,theApp.OpenPath);
			n=strlen(line);
			if((n>4) && (0==strcmp(line+n-4,".plt"))) {
				line[n-4]=0;
				remove(line);
			}
			theApp.OpenBGFlag=-1;
			break;
		default:
			theApp.OpenBGFlag=-1;
			KillTimer(42);
			break;
		}
	}
	if(nIDEvent == 44) {
		theApp.fs.DoModal();
		theApp.DoWaitCursor(0);
	}
	
	CMDIFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnOptionsPlot() 
{
	int t1,t2;

	t1 = theApp.PlotOptions.m_bar_width;
	t2 = theApp.PlotOptions.m_curve;
	if(theApp.PlotOptions.DoModal() != IDOK) {
		theApp.PlotOptions.m_bar_width = t1;
		theApp.PlotOptions.m_curve = t2;
	}
}

void CCrypToolApp::ThreadOpenDocumentFileNoMRU(const char * name, const char * title, char *Key, int KeyType)
{
	int i;

	for(i=0;((i<50)&&(OpenBGFlag==2));i++) Sleep(100);
	OpenBGFlag=2;
	strncpy(OpenTitle, title, sizeof(OpenTitle)-1);
	OpenTitle[sizeof(OpenTitle)-1]=0;
	strncpy(theApp.OpenPath, name, sizeof(OpenPath)-1);
	OpenPath[sizeof(OpenPath)-1]=0;
	KeyOpenDocumentFile = Key;
	KeyTypeOpenDocumentFile = KeyType;
	m_MainWnd->SendMessage(WM_TIMER,42,NULL);
}

void CCrypToolApp::OnOpttext() 
{
	TextOptions.DoModal();
}



int CCrypToolApp::ExitInstance()
{
	if(CaPseDatei) free(CaPseDatei);
	if(CaPseVerzeichnis) free(CaPseVerzeichnis);
	if(Pfad) free(Pfad);
	if(PseVerzeichnis) free(PseVerzeichnis);
	if(m_Selfextract_EXE) free(m_Selfextract_EXE);
//	m_pRecentFileList->WriteList();
	return CWinApp::ExitInstance();
}

void CCrypToolApp::OnUpdateNeedSecudeTicket(CCmdUI* pCmdUI) 
{
    if(theApp.SecudeStatus == 2) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);	
	if (pCmdUI->m_nID == ID_VERENTSCHLSSELN_HYBRIDVERFAHREN_HYBRIDENTSCHLSSELUNG )
		pCmdUI->Enable(FALSE);
}

void CCrypToolApp::OnShowKeys() 
{
	// UpdateContent();
	CDlgKeyAsym TocDialog;
	TocDialog.DoModal();
}

void CCrypToolApp::OnKeyGen() 
{
	KeyGen();
}

void CCrypToolApp::OnEinzelverfahrenTutorialPrimzahlengenerieren() 
{
	CDlgPrimesGeneratorDemo DPG;
	DPG.m_hide_button_accept = true;
	DPG.DoModal();
}

void CCrypToolApp::OnEinzelverfahrenTutorialRsaalgorithmus() 
{
	CDlgRSADemo objekt;
	objekt.DoModal();
}

void CCrypToolApp::OnEinzelverfahrenTutorialfrkleinezahlenFaktorisieren() 
{
	CDlgFactorisationDemo FAKT;
	AfxInitRichEdit();
        FAKT.DoModal();
/*
	if ( FAKT.DetailsFactorisation.b_SaveFactorList )
	{
		CAppDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU( FAKT.DetailsFactorisation.outfile);
		remove(FAKT.DetailsFactorisation.outfile);
		LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HL_OUTPUT,
				pc_str,STR_LAENGE_STRING_TABLE);
		char line[256];
		CString tmp = FAKT.DetailsFactorisation.m_orignNumber;
		if ( tmp.GetLength() < 20 )
		{
			sprintf( line, pc_str, tmp.GetBuffer(0) );
		}
		else
		{
			CString tmp2 = tmp.Left(9) + "..." + tmp.Right(8);
			sprintf( line, pc_str, tmp2.GetBuffer(0) );
		}
		NewDoc->SetTitle(line);
	}
*/
}

void CCrypToolApp::OnEinzelverfahrenSchluesselgenerieren() 
{
	CDlgKeyFromPassword SG;
	SG.DoModal();
}


void CCrypToolApp::OnGenRandomData()
{
	CDlgRandomGenerator DGR;
	DGR.DoModal();
}


void CCrypToolApp::OnHashOfAFile() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	HashOfAFile();	
}


void CCrypToolApp::OnEinzelverfahrenTutorialSignaturerzeugung() 
{
	CDlgSignatureDemo DST;
	DST.DoModal();
}


void CCrypToolApp::WinHelp( DWORD dwData, UINT nCmd)
{
	if (m_menuItemWithSubMenuSelected && !m_menuItemStack.empty()) {

		TCHAR alinkid[255] = ""; //255 is the maximum for alinks
		deque<menuitem>::iterator it;
		// calculate a unique id for current menu item (alinkid) from stack
		for (it = m_menuItemStack.begin(); it != m_menuItemStack.end(); it++) {
			TCHAR mi[sizeof alinkid] = "";
			GetMenuString((*it).hmenu,(*it).index,mi,sizeof(mi)-1,MF_BYPOSITION);
			mi[sizeof mi - 1] = '\0';
			int i = 0, j = 0;
			TCHAR c;
			// remove from mi
			// - everything except alphanumerics
			// - \t and everything following
			while ((c = mi[j++]) && c != '\t')  //isalnum liefert auch true beim Umlaute
				if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
					mi[i++] = c;
				//else don't copy c, don't increment i
			mi[i] = '\0';
			int len = strlen(alinkid);
			if (len > 0 && len < sizeof(alinkid))
				alinkid[len++] = '_';
			strncpy(alinkid+len,mi,sizeof(alinkid)-len);
			alinkid[sizeof(alinkid) - 1] = '\0';
		}
		// perpare help macro string
		TCHAR formstr[] = "AL(\"%s\",1)"; // AL = ALink = jump to A footnote; 1 means: jump to topic if match was unique
		TCHAR cmd[sizeof(formstr) + sizeof(alinkid)];
		_snprintf(cmd,sizeof(cmd),formstr,alinkid);
		cmd[sizeof(cmd)-1] = '\0';
		// WinHelp displays an error popup if we try to jump via ALink to a page that is already displayed.
		// As we cannot find out which page is currently displayed (controlled by user),
		// we make sure that another page is displayed.  
		CWinApp::WinHelp(ID_WIE_SIE_STARTEN+0x10000);
		// invoke help macro: jump to the key word derived from m_CurrentPopupMenu
		CWinApp::WinHelp((DWORD)cmd,HELP_COMMAND);
	} else
		CWinApp::WinHelp(dwData,nCmd);
}

void CCrypToolApp::updateMenuItemStack(HMENU hmenu,INT index) { 
	// update the stack of open menus with a new one
	if (!m_menuItemStack.empty()) {
		menuitem top = m_menuItemStack.back();
		HMENU submenu = GetSubMenu(top.hmenu,top.index);
		if (hmenu != submenu) {
			//pop from stack until hmenu found our empty
			while (!m_menuItemStack.empty() && hmenu != m_menuItemStack.back().hmenu)
				m_menuItemStack.pop_back();
			if (!m_menuItemStack.empty()) // found hmenu on stack
				m_menuItemStack.pop_back(); // remove it so that it is repaced by a new entry with correct index
		}
	}
	menuitem mi = { hmenu, index };
	m_menuItemStack.push_back(mi);
}


BOOL CCrypToolApp::ProcessMessageFilter(int code, LPMSG lpMsg)
{
	if ( code == MSGF_MENU && lpMsg->message == WM_MENUSELECT) {
		HMENU hmenu = (HMENU)lpMsg->lParam;
		UINT flags = (UINT)HIWORD(lpMsg->wParam); 
		UINT item = (UINT)LOWORD(lpMsg->wParam);
		m_menuItemWithSubMenuSelected = 0;
		if (flags & MF_POPUP && !(flags == 0xFFFF && hmenu == 0 /*menu closed*/)) {
			updateMenuItemStack(hmenu,item);
			m_menuItemWithSubMenuSelected = 1;
		}
	}
	return CWinThread::ProcessMessageFilter(code,lpMsg);
}

void CCrypToolApp::OnVerentschlsselnHybridverfahrenHybridverschlsselung() 
{
	CDlgHybridEncryptionDemo hyb;
	hyb.DoModal();
}

void CCrypToolApp::OnOptionsStartoptions() 
{
	CDlgOptionsStartoptions oso;
	oso.DoModal();
}
