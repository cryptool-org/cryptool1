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

#include "process.h"

#include "stdafx.h"
#include <stdlib.h>


#include "CrypToolApp.h"
#include "CryptDoc.h"
#include "CPlotDocument.h"
#include "PlotView.h"
#include "OpenGLDoc.h"
#include "OpenGLView.h"
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
#include "DlgSignatureAttack.h"
#include "DlgSigAttModificDemo.h"
#include "DlgDiffieHellmanVisualization.h"
#include "DialogeMessage.h"
#include "DlgSideChannelAttackVisualizationHE.h"
#include "ChallengeResponseDlg.h"
#include "DlgPasswordQualityMeter.h"
#include "DlgPasswordEntropy.h"
#include "HexEditCtrlDoc.h"
#include "HexEditCtrlView.h"
#include "ScintillaWnd.h"
#include "ScintillaDoc.h"
#include "ScintillaView.h"
#include "DlgCrtAstronomy.h"
#include "DlgCrtTransformation.h"
#include "DlgCrtSecretSharing.h"
#include "DlgSecretSharingSetup.h"
#include "DlgPrimeTest.h"

#include "HillEncryption.h"

// #if !defined(_MSC_VER) || _MSC_VER <= 1200
#include "RSABloemerMayDlg.h"
#include "RSAStereotypedMSGDlg.h"
#include "RSAFactorHintDlg.h"
#include ".\cryptoolapp.h"
#include "CrypToolTools.h"
// #endif

#pragma warning(disable : 4996)

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
CString sHillGlobalKey[HILL_MAX_DIM_GROSS][HILL_MAX_DIM_GROSS];
int iHillMultiplicationType = 0;  //0: (matrix)*(column vector) 1:(row vector)*(matrix)
bool bHexEnabled = false;
bool bGlobVerbose = false;

CString sNotInFileChars;
int iClearTextAlphCharCount;
int iClearTextNotAlphCharCount;

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
	ON_COMMAND(ID_OPTIONS_STARTOPTIONS, OnOptionsStartoptions)
	ON_COMMAND(ID_HILFE_INDEX, OnHilfeIndex)
	ON_COMMAND(ID_HILFE_STARTSEITE, OnHilfeStartseite)
	ON_COMMAND(ID_HILFE_SZENARIEN, OnHilfeSzenarien)
	ON_COMMAND(ID_SIGNATUR_ATTACK, OnSignaturAttack)
	ON_COMMAND(ID_EINZELVERFAHREN_DIFFIEHELLMANDEMO, OnEinzelverfahrenDiffiehellmandemo)
	ON_COMMAND(ID_SIGATTMODIFICDEMO, OnSigattmodificdemo)
	ON_COMMAND(ID_LOAD_README, OnLoadReadme)
	ON_COMMAND(ID_SCRIPT, OnScript)
	ON_COMMAND(ID_HELP_PRESENTATION, OnPresentation)
	ON_COMMAND(ID_EINZELVERFAHREN_SIDECHANNELATTACK_ON_HYBRIDENCRYPTION, OnEinzelverfahrenSidechannelattackOnHybridencryption)
	ON_COMMAND(ID_PASSWORDQUALITYMETER, OnPasswordQualityMeter)
	ON_COMMAND(ID_PASSWORDENTROPY, OnPasswordEntropy)
	ON_COMMAND(ID_CHALLENGE_RESPONSE, OnChallengeResponse)
	ON_COMMAND(ID_RSA_FACTORHINT, OnRsaFactorhint)
	ON_COMMAND(ID_RSA_STEREOTYPED, OnRsaStereotyped)
	ON_COMMAND(ID_RSA_BLOEMERMAY, OnRsaBloemermay)
	ON_COMMAND(ID_HELP_ANIMAL_CAESAR, OnAnimalCaesar)
	ON_COMMAND(ID_HELP_ANIMAL_VIGENERE, OnAnimalVigenere)
	ON_COMMAND(ID_HELP_ANIMAL_NIHILIST, OnAnimalNihilist)
	ON_COMMAND(ID_HELP_ANIMAL_DES, OnAnimalDes)
	ON_COMMAND(ID_INDIV_CRT_PLANET, OnIndivCrtPlanet)
	ON_COMMAND(ID_INDIV_CRT_DEMO, OnIndivCrtDemo)
	ON_COMMAND(ID_INDIV_CRT_SECRETSHARING, OnIndivCrtSecretsharing)
	ON_COMMAND(ID_NUMBERSHARK, OnNumberShark)
	ON_UPDATE_COMMAND_UI(ID_NUMBERSHARK, OnUpdateNumberShark)
	ON_UPDATE_COMMAND_UI(ID_SHOW_ALL_EC_KEYS, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_KeyGen, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_VERENTSCHLSSELN_HYBRIDVERFAHREN_HYBRIDVERSCHLSSELUNG, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_VERENTSCHLSSELN_HYBRIDVERFAHREN_HYBRIDENTSCHLSSELUNG, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_HASH_OFAFILE, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_EINZELVERFAHREN_SIGN, OnUpdateNeedSecudeTicket)
	ON_UPDATE_COMMAND_UI(ID_EINZELVERFAHREN_SCHLUESSELGENERIEREN, OnUpdateNeedSecudeTicket)
	ON_COMMAND(ID_INDIVIDUAL_PROCEDURES_SECRETSHARING, OnIndividualProceduresSecretsharing)
	//}}AFX_MSG_MAP

	//ON_COMMAND(ID_VERENTSCHLSSELN_HYBRIDVERFAHREN_HYBRIDVERSCHLSSELUNG, OnVerentschlsselnHybridverfahrenHybridverschlsselung)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)			     // file commands...
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
// BEGINN Fuer Hilfe-Funktionalitaet eingefuegt
	// Globale Hilfebefehle
	ON_COMMAND(ID_HELP_FINDER, CWinApp::OnHelpFinder)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CWinApp::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CWinApp::OnHelpFinder)

// ENDE
	ON_COMMAND(ID_PRIMENUMBER_TEST, OnPrimenumberTest)
	ON_COMMAND(ID_AES_SELFEXTRACT, OnAesSelfextract)
	ON_COMMAND(ID_INDIV_POINTADDITIONONELLIPTICCURVES, OnIndivPointadditiononellipticcurves)
	ON_COMMAND(ID_FLASH_AESDEMO, OnFlashAesdemo)
	ON_COMMAND(ID_FLASH_RIJNDAEL_INSPECTOR, OnFlashRijndaelInspector)
	ON_COMMAND(ID_FLASH_ENIGMADEMO, OnFlashEnigmademo)
	ON_COMMAND(ID_INTERACTIVE_NUMBER_THEORY, OnInteractiveNumberTheory)
	ON_COMMAND(ID_PROTOKOL_SMIME, &CCrypToolApp::OnProtokolSMIME)
END_MESSAGE_MAP()



int copy_files(const char *from, const char *to)
{
	WIN32_FIND_DATA FileData; 
	HANDLE hSearch; 

	char szTargetPath[MAX_PATH];
	char szSourcePath[MAX_PATH];
	lstrcpy(szSourcePath, from);
	lstrcat(szSourcePath, "\\*.*");

	BOOL fFinished = FALSE; 
	 
	hSearch = FindFirstFile(szSourcePath, &FileData); 
	if (hSearch == INVALID_HANDLE_VALUE) 
		fFinished = TRUE;
	 
	while (!fFinished) 
	{ 
		lstrcpy(szTargetPath, to);
		lstrcat(szTargetPath, "\\");
		lstrcat(szTargetPath, FileData.cFileName); 

		lstrcpy(szSourcePath, from);
		lstrcat(szSourcePath, "\\");
		lstrcat(szSourcePath, FileData.cFileName); 

		if (CopyFile(szSourcePath, szTargetPath, FALSE))
			SetFileAttributes(szTargetPath, FILE_ATTRIBUTE_NORMAL); 

		if (!FindNextFile(hSearch, &FileData)) 
		{
			if (GetLastError() == ERROR_NO_MORE_FILES) 
			{ 
				fFinished = TRUE; 
			} 
			else
				break;
		}
	} 
	 
	FindClose(hSearch);
	return fFinished;
}

int check_files(const char *path)
{
	WIN32_FIND_DATA FileData; 
	HANDLE hSearch; 

	char szPath[MAX_PATH];
	lstrcpy(szPath, path);
	lstrcat(szPath, "\\*.*");

	BOOL fFinished = FALSE; 
	int error      = 0;
	 
	hSearch = FindFirstFile(szPath, &FileData); 
	if (hSearch == INVALID_HANDLE_VALUE) 
		fFinished = TRUE;
	 
	while (!fFinished) 
	{ 
		lstrcpy(szPath, path);
		lstrcat(szPath, "\\");
		lstrcat(szPath, FileData.cFileName); 

		if ( FILE_ATTRIBUTE_READONLY & GetFileAttributes(szPath) )
			error++;

		if (!FindNextFile(hSearch, &FileData)) 
		{
			if (GetLastError() == ERROR_NO_MORE_FILES) 
			{ 
				fFinished = TRUE; 
			} 
			else
				break;
		}
	} 
	 
	FindClose(hSearch);
	return error;
}




// PSE Handling
const int pse_filestruct_valid                      = 0;
const int pse_filestruct_corrupted                  = IDS_PSE_FILESTRUCT_CORRUPTED;
const int pse_filestruct_does_not_exist             = 2;
const int pse_filestruct_could_not_create_directory = IDS_PSE_FILESTRUCT_COULD_NOT_CREATE_DIRECTORY;
const int pse_filestruct_could_not_copy_pse         = IDS_PSE_FILESTRUCT_COULD_NOT_COPY_PSE;
const int pse_filestruct_no_application_data_path   = IDS_PSE_FILESTRUCT_NO_APPLICATION_DATA_PATH;
const int pse_filestruct_orig_corrupted             = IDS_PSE_FILESTRUCT_ORIG_CORRUPTED;
const int pse_filestruct_try_to_rewrite_user_pse    = IDS_PSE_FILESTRUCT_TRY_TO_REWRITE_PSE;

const char pse_folder[]     = "PSE";
const char pse_ca_folder[]  = "PSE\\PSECA";
const char pse_ca_keyfile[] = "PSE\\PSECA\\capse.cse";

int check_keystore_path( const char *key_store_path );
int copy_keystore_path( const char *path_from, const char *path_to );

int check_keystore_path( const char *key_store_path )
{
	CString PseV, CaPseD, CaPseV;
	PseV  = key_store_path + CString(pse_folder);
	CaPseD= key_store_path + CString(pse_ca_keyfile);
	CaPseV= key_store_path + CString(pse_ca_folder);
	if ( FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes( key_store_path ) )
	{ 
		if ( !( ( INVALID_FILE_ATTRIBUTES != GetFileAttributes( PseV ) ) &&  
				( INVALID_FILE_ATTRIBUTES != GetFileAttributes( CaPseD ) ) &&
				( INVALID_FILE_ATTRIBUTES != GetFileAttributes( CaPseV ) ) ) )
			return pse_filestruct_corrupted;
		else
			return pse_filestruct_valid;
	}
	else
		return pse_filestruct_does_not_exist;
}

int copy_keystore_path( const char *path_from, const char *path_to )
{
	int error = check_keystore_path(path_from);
	if ( error != pse_filestruct_valid )
	{
		if ( error = pse_filestruct_corrupted )
			error = pse_filestruct_orig_corrupted;
		return error;
	}

	CString PseV, CaPseV, PseV_from, CaPseV_from;
	PseV  = path_to + CString(pse_folder);
	CaPseV= path_to + CString(pse_ca_folder);

	DWORD a1, a2, a3;
	a1 = GetFileAttributes(path_to);
	a2 = GetFileAttributes(PseV);
	a3 = GetFileAttributes(CaPseV);

	// IF NOT ( (DIR does not exists but can be created) OR (DIR exists) ) ...
	if ( !((((INVALID_FILE_ATTRIBUTES == a1) && CreateDirectory(path_to, NULL)) || (FILE_ATTRIBUTE_DIRECTORY & a1)) &&
	       (((INVALID_FILE_ATTRIBUTES == a2) && CreateDirectory(PseV, NULL))    || (FILE_ATTRIBUTE_DIRECTORY & a2)) &&
	       (((INVALID_FILE_ATTRIBUTES == a3) && CreateDirectory(CaPseV, NULL))  || (FILE_ATTRIBUTE_DIRECTORY & a3))) )
		return pse_filestruct_could_not_create_directory;

	PseV_from   = path_from + CString(pse_folder);
	CaPseV_from = path_from + CString(pse_ca_folder);
	if ( !(copy_files(PseV_from, PseV) && copy_files(CaPseV_from, CaPseV) ) )
		return pse_filestruct_could_not_copy_pse;	
	return pse_filestruct_valid;
}



BOOL CCrypToolApp::InitInstance()
{
//	_tsetlocale(LC_ALL, _T(""));

	char buffer[1024], *p;
	int n;

	#if !defined(_MSC_VER) || _MSC_VER <= 1200  
// HTML Help for VC++ 6.0
// ...
	#else
	EnableHtmlHelp( );
	#endif


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
	
	Pfad2.Replace("/","\\"); //change Slashes to ensure Vista compatibility
	
	_tcscpy(help1, Pfad2);

	
	Pfad=help1;

// Old Path Settings for KeyStore
	CString PseV, CaPseD, CaPseV;
	PseV   = Pfad2 + CString(pse_folder);
	CaPseD = Pfad2 + CString(pse_ca_keyfile);
	CaPseV = Pfad2 + CString(pse_ca_folder);
		
	LPTSTR help2 = new TCHAR[CaPseD.GetLength()+1];
	_tcscpy(help2, CaPseD);
	CaPseDatei=help2;

	LPTSTR help3 = new TCHAR[CaPseV.GetLength()+1];
	_tcscpy(help3, CaPseV);
	CaPseVerzeichnis=help3;

	LPTSTR help4 = new TCHAR[PseV.GetLength()+1];
	_tcscpy(help4, PseV);
	PseVerzeichnis=help4;

	if ( ERROR_SUCCESS == CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "UserKeyStore") )
	{
		char key_store_path[1024];
		unsigned long  str_len = 1024;
		int error = 0;

		unsigned long use_local_pse;
		CT_READ_REGISTRY_DEFAULT(use_local_pse, "UseUserKeyStore", 1);

		if ( use_local_pse )
		{
			if ( !CT_READ_REGISTRY(key_store_path, "Path", str_len) )
			{
				char* app_data_env;
				app_data_env = getenv("APPDATA");
				if ( app_data_env )
				{
					strcpy(key_store_path, app_data_env);
					strcat(key_store_path, "\\CrypTool\\");
					if ( pse_filestruct_valid != check_keystore_path( key_store_path ) )
						error = copy_keystore_path( Pfad2, key_store_path );
					if ( !error )
						CT_WRITE_REGISTRY(key_store_path, "Path");
				}
				else
					error = pse_filestruct_no_application_data_path;
			}
			else
			{
				if ( pse_filestruct_valid != check_keystore_path( key_store_path ) )
					error = pse_filestruct_try_to_rewrite_user_pse;
			}

			// Try to rewrite PSE to local KEYSTORE
			if ( error == pse_filestruct_try_to_rewrite_user_pse )
			{
				char error_caption[128];
				char error_message_template[1024];
				char error_message[2048];
				LoadString(AfxGetInstanceHandle(),IDS_ERROR_LOAD_LOCAL_PSE_CAPTION,error_caption,STR_LAENGE_STRING_TABLE);
				LoadString(AfxGetInstanceHandle(),error,error_message_template,STR_LAENGE_STRING_TABLE);
				error = pse_filestruct_does_not_exist;
				sprintf(error_message, error_message_template, key_store_path);
				if ( IDOK == MessageBox(NULL,error_message,error_caption,MB_ICONWARNING|MB_OKCANCEL) )
					error = copy_keystore_path( Pfad2, key_store_path );
			}

			if ( !error )
			{
				PseV  = key_store_path + CString(pse_folder);
				CaPseD= key_store_path + CString(pse_ca_keyfile);
				CaPseV= key_store_path + CString(pse_ca_folder);

				delete []CaPseDatei;
				LPTSTR help2 = new TCHAR[CaPseD.GetLength()+1];
				_tcscpy(help2, CaPseD);
				CaPseDatei=help2;

				delete []CaPseVerzeichnis;
				LPTSTR help3 = new TCHAR[CaPseV.GetLength()+1];
				_tcscpy(help3, CaPseV);
				CaPseVerzeichnis=help3;

				delete []PseVerzeichnis;
				LPTSTR help4 = new TCHAR[PseV.GetLength()+1];
				_tcscpy(help4, PseV);
				PseVerzeichnis=help4;
			}
			else if ( error != pse_filestruct_does_not_exist )  // pse_filestruct_does_not_exist is already handled
			{
				char error_caption[128];
				char error_message_template[1024];
				char error_message[2048];
				LoadString(AfxGetInstanceHandle(),IDS_ERROR_LOAD_LOCAL_PSE_CAPTION,error_caption,STR_LAENGE_STRING_TABLE);
				LoadString(AfxGetInstanceHandle(),error,error_message_template,STR_LAENGE_STRING_TABLE);

				switch ( error )
				{
					case IDS_PSE_FILESTRUCT_CORRUPTED:
					case IDS_PSE_FILESTRUCT_COULD_NOT_CREATE_DIRECTORY:
					case IDS_PSE_FILESTRUCT_COULD_NOT_COPY_PSE:
						sprintf(error_message, error_message_template, key_store_path);
						break;
					case IDS_PSE_FILESTRUCT_ORIG_CORRUPTED:
						sprintf(error_message, Pfad2, key_store_path);
						break;
					default:
						strcpy(error_message, error_message_template);
						break;
				}
				MessageBox(NULL,error_message,error_caption,MB_ICONWARNING|MB_OK);
			}
		}
	}


	if ( check_files(CaPseVerzeichnis) || check_files(PseVerzeichnis) )
	{
		char error_caption[128];
		char error_message_template[1024];
		char error_message[2048];
		LoadString(AfxGetInstanceHandle(),IDS_ERROR_LOAD_LOCAL_PSE_CAPTION,error_caption,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_PSE_FILES_READONLY,error_message_template,STR_LAENGE_STRING_TABLE);
		sprintf(error_message, error_message_template, PseVerzeichnis);
		MessageBox(NULL,error_message,error_caption,MB_ICONWARNING|MB_OK);
	}
	//Ende der Initialiserung der globalen Variablen

	SetRegistryKey("HKEY_CURRENT_USER\\Software\\CrypTool\\Most Recently Used Files"); // No .Ini File#
	/* Einstellen der Länge der MRU-Liste */
	LoadStdProfileSettings(10);
    MRU_Flag = TRUE;

	AddDocTemplate(new CCryptDocTemplate(IDR_TEXTTYPE,
		RUNTIME_CLASS(CScintillaDoc), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CScintillaView))); // FIXME OnShowKey etc.
	AddDocTemplate(new CCryptDocTemplate(IDR_PLOTTYPE,
		RUNTIME_CLASS(CPlotDocument), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CPlotView)));
	AddDocTemplate(new CCryptDocTemplate(IDR_HEXTYPE,
		RUNTIME_CLASS(CHexEditCtrlDoc), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CHexEditCtrlView)));
	AddDocTemplate(new CCryptDocTemplate(IDR_OPENGLTYPE,
		RUNTIME_CLASS(COpenGLDoc), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(COpenGLView)));

	// load Scintilla DLL
	ScintillaLib = CScintillaWnd::LoadScintillaDll();
	if(!ScintillaLib) { // secude und Ticket verfuegbar ?
		LPVOID lpMsgBuf;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf,0,NULL);
		// Write to stderr
		LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
		CString msg;
		msg.Format(_T("%s:%s\n"), (LPCSTR)STR_LEXERDLL, (LPCTSTR)lpMsgBuf);
		MessageBox(NULL,(LPCTSTR)msg,pc_str1,MB_ICONWARNING|MB_OK);
		// Free the buffer.
		LocalFree( lpMsgBuf );
		exit(0);
	}

#if 0
	// try to get version from lexer dll
	if (m_hDll != NULL)
	{
		TCHAR szFilename[256];
		::GetModuleFileName(m_hDll, szFilename, 256);
		CFileVersion ver;
		ver.Open (szFilename);
		m_strVersionScintilla = ver.GetFixedFileVersion();
		m_strProductScintilla = ver.QueryValue (_T("ProductName"));
		m_strFileScintilla = szFilename;
		ver.Close();
	}
#endif

	m_pMainWnd = new CMainFrame;
	m_MainWnd = m_pMainWnd;
	((CFrameWnd*)m_pMainWnd)->LoadFrame(IDR_MAINFRAME);

	// enable file manager drag/drop and DDE Execute open
	m_pMainWnd->DragAcceptFiles();
	// EnableShellOpen();  // EVIL !!!
	// RegisterShellFileTypes(TRUE); // EVIL !!!

	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;// nothing s'gonna happen at application startup
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line

	if (!ProcessShellCommand(cmdInfo))
	{
		return FALSE;
	}


	// Am Anfang ist noch kein Fenster geöffnet, die Hilfe soll mit "Wie Sie starten geöffnet werden"
	//::WinHelp(0, AfxGetApp()->m_pszHelpFilePath, HELP_COMMAND, (DWORD)"JumpId(starten)");
	// WinHelp(ID_WIE_SIE_STARTEN+0x10000);

	// initialize the application dependent Converter
	AppConv.SetAlphabet(TextOptions.refAlphabet().GetBuffer(257), TextOptions.getIgnoreCase());


	SecudeStatus = SecudeLib.GetStatus();
	if(SecudeStatus!=2) { // secude und Ticket verfuegbar ?
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

	// nach Zahlenhai suchen
	CString numberSharkExe;
	numberSharkExe.LoadString(IDS_NUMBERSHARK_EXE);
	n = SearchPath(NULL,numberSharkExe, NULL, 1023, buffer, &p);
	if(n>0) {
		m_NumberShark_Selfextract_EXE = (char *) malloc(n+2);
		strcpy(m_NumberShark_Selfextract_EXE, buffer);
	}
	else
		m_NumberShark_Selfextract_EXE = NULL;


	// korrektes Helpfile laden
	CString HlpTmp;
	free((void*)m_pszHelpFilePath);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HELPNAME,pc_str,STR_LAENGE_STRING_TABLE);
	HlpTmp = Pfad;
	HlpTmp += pc_str;
	m_pszHelpFilePath=_tcsdup(HlpTmp);


///////////////// LOCAL REGISTRY SETTINGS

	if (ERROR_FILE_NOT_FOUND == CT_OPEN_REGISTRY_SETTINGS(KEY_READ, IDS_REGISTRY_SETTINGS))
	{
		HKEY hKey;
		char registryPath[1024];
		LoadString(AfxGetInstanceHandle(),IDS_REGISTRY_SETTINGS,registryPath,STR_LAENGE_STRING_TABLE);

		RegCreateKeyEx(HKEY_CURRENT_USER,registryPath, 0, NULL, REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS | KEY_WRITE | KEY_READ, NULL, &hKey, NULL);
		CT_OPEN_REGISTRY_SETTINGS(KEY_WRITE, IDS_REGISTRY_SETTINGS);
		CT_CLOSE_REGISTRY();
	}

	if ( ERROR_SUCCESS == CT_OPEN_REGISTRY_SETTINGS(KEY_READ, IDS_REGISTRY_SETTINGS, "Options") )
		CT_CLOSE_REGISTRY();

	CDlgTipsAndTricks Tipps; 
	unsigned long u_doNotshowAgain    = (unsigned long)FALSE;
	unsigned long flagOpenSampleFile  = (unsigned long)TRUE;

	if (ERROR_SUCCESS == CT_OPEN_REGISTRY_SETTINGS	(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "SignatureAttack"))
	{
		
		LoadString(AfxGetInstanceHandle(),IDS_SIGATT_HARMLESS,pc_str,STR_LAENGE_STRING_TABLE);
		CT_WRITE_REGISTRY(CString(Pfad)+CString(pc_str), "HarmlessFile" );
		LoadString(AfxGetInstanceHandle(),IDS_SIGATT_DANGEROUS,pc_str,STR_LAENGE_STRING_TABLE);
		CT_WRITE_REGISTRY(CString(Pfad)+CString(pc_str), "DangerousFile" );

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

	if (ERROR_SUCCESS == CT_OPEN_REGISTRY_SETTINGS	(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS_OPTIONS, "StartingOptions"))
	{
		if ( CT_READ_REGISTRY_DEFAULT(u_doNotshowAgain, "NoTipps", u_doNotshowAgain) )
			Tipps.m_DoNotShowThisAgain = u_doNotshowAgain;
		CT_READ_REGISTRY_DEFAULT(flagOpenSampleFile, "SampleTextFile", flagOpenSampleFile);
		

		if (FALSE == Tipps.m_DoNotShowThisAgain)
		{
			Tipps.DoModal();
			CT_WRITE_REGISTRY(Tipps.m_DoNotShowThisAgain, "NoTipps");
		}

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}


///////////////// LOCAL REGISTRY SETTINGS
	// OPEN SAMPLE FILE
	if(flagOpenSampleFile)
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
	ID_SEPARATOR, ID_INDICATOR_LINE, ID_INDICATOR_OVR, ID_INDICATOR_CAPS, ID_INDICATOR_NUM, ID_INDICATOR_SCRL
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
CAppDocument * CCrypToolApp::OpenDocumentFileNoMRU(const char *name, CString Key, int KeyType, int fontSize, CString fontFace)
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
	// set font size and font face
	doc->fontSize = fontSize;
	doc->fontFace = fontFace;

    MRU_Flag = oldflag;
    return doc;
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
	if(m_NumberShark_Selfextract_EXE) free(m_NumberShark_Selfextract_EXE);
	if (ScintillaLib) FreeLibrary(ScintillaLib);
	return CWinApp::ExitInstance();
//	m_pRecentFileList->WriteList();
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
	// enable the generation of sets of prime numbers
	DPG.enableGenerateASetOfPrimeNumbersFunctionality();
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


#if !defined(_MSC_VER) || _MSC_VER <= 1200		
// HTML Help for VC++ 6.0
void CCrypToolApp::WinHelp( DWORD dwData, UINT nCmd)
#else											
// HTML Help for VC++ .NET
void CCrypToolApp::WinHelpInternal( DWORD_PTR dwData, UINT nCmd)
#endif
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
		TCHAR formstr[] = "%s"; 
		TCHAR cmd[sizeof(formstr) + sizeof(alinkid)];
		_snprintf(cmd,sizeof(cmd),formstr,alinkid);
		cmd[sizeof(cmd)-1] = '\0';

		
		callHtmlHelp(HH_DISPLAY_TOPIC, NULL);


		LoadString(AfxGetInstanceHandle(),IDS_ALINK_ERROR_MESSAGE,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_ALINK_ERROR_MESSAGE_TITLE,pc_str1,STR_LAENGE_STRING_TABLE);

		HH_AKLINK link;		// structure needed to call an Alink
		link.cbStruct =     sizeof(HH_AKLINK) ;
		link.fReserved =    FALSE ;
		link.pszKeywords =  cmd ; 
		link.pszUrl =       NULL; 
		link.pszMsgText =   pc_str ; 
		link.pszMsgTitle =  pc_str1 ; 
		link.pszWindow =    NULL;
		link.fIndexOnFail = FALSE ;

		callHtmlHelp(HH_ALINK_LOOKUP, (DWORD) &link);


	} else
	{	
		// creating the path to the help
		CString html_help_path = CString(m_pszHelpFilePath) + CString(">MainWindow");
		
		// calling the help by turning an ID over to the htmlhelp
		switch (nCmd)
		{
			case HELP_CONTEXT:	
				callHtmlHelp(HH_HELP_CONTEXT, dwData);
			break;
			case HELP_FINDER:
				callHtmlHelp(HH_DISPLAY_TOPIC, NULL);
			break;	
		}
		// Error in case help is not found
		LoadString(AfxGetInstanceHandle(),IDS_HELP_ERROR,pc_str,STR_LAENGE_STRING_TABLE);
		CString help_error_message = CString (pc_str) + CString(m_pszHelpFilePath);
		// if (hwnd == NULL) AfxMessageBox(help_error_message, MB_ICONINFORMATION, 0);
	}	

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

void CCrypToolApp::OnHilfeIndex() 
{
	callHtmlHelp(HH_HELP_CONTEXT, ID_HILFE_INDEX+0x10000);
}

void CCrypToolApp::OnHilfeStartseite() 
{
	callHtmlHelp(HH_HELP_CONTEXT, ID_WIE_SIE_STARTEN+0x10000);
}

void CCrypToolApp::OnHilfeSzenarien() 
{
	callHtmlHelp(HH_HELP_CONTEXT, ID_HILFE_SZENARIEN+0x10000);
}

void CCrypToolApp::OnSignaturAttack() 
{
	CDlgSignatureAttack DlgSA;
	DlgSA.DoModal();
}

void CCrypToolApp::OnEinzelverfahrenDiffiehellmandemo() 
{
	CDlgDiffieHellmanVisualization dlg;
	dlg.DoModal();	
}

void CCrypToolApp::OnSigattmodificdemo() 
{
	CDlgSigAttModificDemo SAMD;
	SAMD.DoModal();
}

void CCrypToolApp::OnLoadReadme() 
{
	callHtmlHelp(HH_HELP_CONTEXT, ID_LOAD_README+0x10000);
}

void CCrypToolApp::OnScript() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	char readmePath[1024];
	LoadString(AfxGetInstanceHandle(),IDS_SCRIPTPATH,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(readmePath, pc_str, Pfad);

	//HINSTANCE hInst = ShellExecute(0, "open", readmePath, NULL, 0, SW_SHOW ); // does not work for BE - .NET 3.0 issue?
	HINSTANCE hInst = ShellExecute(0, NULL, readmePath, NULL, 0, SW_SHOW );

	if ( reinterpret_cast<int>(hInst) <= 32 )
		Message(IDS_ERROPEN_SCRIPT, MB_ICONSTOP);
}

void CCrypToolApp::OnPresentation()
{
	LoadString(AfxGetInstanceHandle(),IDS_PATH_PRESENTATION,pc_str,STR_LAENGE_STRING_TABLE);
	int lengthPresentationPath = strlen(pc_str) + strlen(Pfad) + 1;
	char *presentationPath = new char[lengthPresentationPath];
	memset(presentationPath, 0, lengthPresentationPath);
	sprintf(presentationPath, pc_str, Pfad);
	HINSTANCE hInst = ShellExecute(0, NULL, presentationPath, NULL, 0, SW_SHOW);
	delete []presentationPath;
	if(reinterpret_cast<int>(hInst) <= 32)
		Message(IDS_ERROR_OPENING_PRESENTATION, MB_ICONSTOP);
}

// Den Dialog "Visualisierung eines Seitenkanalangriffs auf das
// Hybridverschlüsselungsverfahren" erstellen und anzeigen
void CCrypToolApp::OnEinzelverfahrenSidechannelattackOnHybridencryption() 
{
	CDlgSideChannelAttackVisualizationHE dlg;
	dlg.DoModal();
}

void CCrypToolApp::OnPasswordQualityMeter()
{
	CDlgPasswordQualityMeter dlg;
	dlg.DoModal();
}

void CCrypToolApp::OnPasswordEntropy()
{
	CDlgPasswordEntropy dlg;
	dlg.DoModal();
}

void CCrypToolApp::OnChallengeResponse() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CChallengeResponseDlg dlg;

	
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}	
}


// #if !defined(_MSC_VER) || _MSC_VER <= 1200

void CCrypToolApp::OnRsaFactorhint() 
{
	CRSAFactorHintDlg RSAFHDlg;
	RSAFHDlg.DoModal();
}

void CCrypToolApp::OnRsaStereotyped() 
{
	CRSAStereotypedMSGDlg RSASMDlg;
	RSASMDlg.DoModal();
}

void CCrypToolApp::OnRsaBloemermay() 
{
	CRSABloemerMayDlg RSABMDlg;
	RSABMDlg.DoModal();
}
// #endif

void CCrypToolApp::execAnimalVisualization(int animalPathID, int animalFileID, int animalExecutableID, int animalLocaleID)
{
	CString animalPath, animalFile, animalExecutable, animalLocale;
	LoadString(AfxGetInstanceHandle(),animalPathID,pc_str,STR_LAENGE_STRING_TABLE);
	animalPath = CString(Pfad) + CString(pc_str);
	
	LoadString(AfxGetInstanceHandle(),animalExecutableID,pc_str,STR_LAENGE_STRING_TABLE);
	animalExecutable = pc_str;
	
	LoadString(AfxGetInstanceHandle(),animalFileID,pc_str,STR_LAENGE_STRING_TABLE);
	animalFile = pc_str;
	
	LoadString(AfxGetInstanceHandle(),animalLocaleID,pc_str,STR_LAENGE_STRING_TABLE);
	animalLocale = pc_str;

	animalFile = animalLocale + CString(" ") + CString("\"") + animalPath + animalFile +CString("\"");

	animalPath.Replace("/","\\");

	HINSTANCE hInst=ShellExecute(NULL,NULL,animalExecutable,animalFile,animalPath,SW_HIDE );
	
	if ( reinterpret_cast<int>(hInst) <= 32 )
		Message(IDS_ERROPEN_ANIM, MB_ICONSTOP);
}

void CCrypToolApp::OnAnimalCaesar() 
{
	execAnimalVisualization(IDS_ANIMAL_PATH, IDS_ANIMAL_FILE_CAESAR, IDS_ANIMAL_EXECUTABLE, IDS_ANIMAL_FILE_LOCALE);
}

void CCrypToolApp::OnAnimalVigenere() 
{
	execAnimalVisualization(IDS_ANIMAL_PATH, IDS_ANIMAL_FILE_VIGENERE, IDS_ANIMAL_EXECUTABLE, IDS_ANIMAL_FILE_LOCALE);
}

void CCrypToolApp::OnAnimalNihilist() 
{
	execAnimalVisualization(IDS_ANIMAL_PATH, IDS_ANIMAL_FILE_NIHILIST, IDS_ANIMAL_EXECUTABLE, IDS_ANIMAL_FILE_LOCALE);
}

void CCrypToolApp::OnAnimalDes() 
{
	execAnimalVisualization(IDS_ANIMAL_PATH, IDS_ANIMAL_FILE_DES, IDS_ANIMAL_EXECUTABLE, IDS_ANIMAL_FILE_LOCALE);
}

void CCrypToolApp::OnIndivCrtPlanet() 
{
	CDlgCrtAstronomy ddlg;
	ddlg.DoModal();
}

void CCrypToolApp::OnIndivCrtDemo() 
{
	CDlgCrtTransformation dialg;
	dialg.DoModal();
}

void CCrypToolApp::OnIndivCrtSecretsharing() 
{
	CDlgCrtSecretSharing dialg;
	dialg.DoModal();
}

void CCrypToolApp::OnNumberShark() 
{
	// zahlenhai aufrufen
	CString str_m_NumberShark_Selfextract_EXE_Quoted = CString("\"") + CString(theApp.m_NumberShark_Selfextract_EXE) + CString("\"");
	_spawnl(_P_NOWAIT, theApp.m_NumberShark_Selfextract_EXE, str_m_NumberShark_Selfextract_EXE_Quoted, NULL);
	// FIXME: Interpret return value of _spawnl
}

void CCrypToolApp::OnUpdateNumberShark(CCmdUI* pCmdUI) 
{
	if(theApp.m_NumberShark_Selfextract_EXE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

BOOL CCrypToolApp::OnDDECommand(LPTSTR lpszCommand)
{
	// TODO: Add your specialized code here and/or call the base class
	if ( CWinApp::OnDDECommand(lpszCommand) )
		return TRUE;

	// AfxMessageBox ("MUST BE FIXED !!");
	return FALSE;
}


void CCrypToolApp::callHtmlHelp(UINT uCommand, DWORD dwData)
{
#if !defined(_MSC_VER) || _MSC_VER <= 1200 // HTML Help for VC++ 6.0
// creating the path to the help
		CString html_help_path = CString(m_pszHelpFilePath) + CString(">MainWindow");
		
		// to ensure that the help window is created before an Alink is looked up, this command is called 
		HWND hwnd = ::HtmlHelp(
				AfxGetMainWnd()->m_hWnd, /* GetDesktopWindow(), We Consider the global handle is the better choice ? */
				html_help_path,
				uCommand,
				dwData) ;
		// Error in case help is not found 
		LoadString(AfxGetInstanceHandle(),IDS_HELP_ERROR,pc_str,STR_LAENGE_STRING_TABLE);
		CString help_error_message = CString (pc_str) + CString(m_pszHelpFilePath);
		if (hwnd == NULL) AfxMessageBox(help_error_message, MB_ICONINFORMATION, 0);
#else
#if 0
	HH_WINTYPE *phhwt = NULL;
	CString html_help_path = CString(m_pszHelpFilePath) + CString(">MainWindow");
	HWND hwnd = ::HtmlHelp(AfxGetMainWnd()->m_hWnd,html_help_path,HH_GET_WIN_TYPE,(DWORD)&phhwt);
	if (phhwt) {
		HH_WINTYPE hhwt;

		// Copy the returned structure
		// NOTE: DO NOT MODIFY THE RETURNED STRUCTURE!!
		memcpy(&hhwt,phhwt,min(long(sizeof(hhwt)),long(phhwt->cbStruct)));

		// Reset members to enable notification messages
		hhwt.cbStruct = sizeof(hhwt);
		hhwt.fsValidMembers = HHWIN_PARAM_PROPERTIES;
		hhwt.fsWinProperties |= HHWIN_PROP_NODEF_EXSTYLES | HHWIN_PROP_NODEF_STYLES; //  | HHWIN_PROP_NOTITLEBAR;

		// Set it
		::HtmlHelp(NULL,NULL,HH_SET_WIN_TYPE,(DWORD)&hhwt);
	}

	// Display the return value
#endif
	HtmlHelp(dwData, uCommand);
#endif
}

void CCrypToolApp::OnIndividualProceduresSecretsharing() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CDlgSecretSharingSetup demoSetup;
	demoSetup.DoModal();
}

void CCrypToolApp::OnPrimenumberTest()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
	CDlgPrimeTest dialg;
	dialg.DoModal();
}

void CCrypToolApp::OnAesSelfextract()
{
	CString str_m_Selfextract_EXE_Quoted = CString("\"") + CString(theApp.m_Selfextract_EXE) + CString("\"");
//	int intptr_t = _spawnl(_P_NOWAIT, strmod, strmod, NULL, NULL);
	int intptr_t = _spawnl(_P_NOWAIT, theApp.m_Selfextract_EXE, str_m_Selfextract_EXE_Quoted, NULL, NULL);
	// FIXME: Interpret return value of _spawnl
}

void CCrypToolApp::OnIndivPointadditiononellipticcurves()
{
	CString ECCPath, ECCFile, ECCExecutable;
	HINSTANCE hInst;


	LoadString(AfxGetInstanceHandle(),IDS_ECCDemo_EXECUTABLE,pc_str,STR_LAENGE_STRING_TABLE);
	ECCExecutable = pc_str; //IDS_ECCDemo_EXECUTABLE     java.exe

	LoadString(AfxGetInstanceHandle(),IDS_ECCDemo_FILE,pc_str,STR_LAENGE_STRING_TABLE);
	ECCFile = pc_str; // ECCDemo.jar

	hInst=ShellExecute(NULL,NULL, ECCExecutable, ECCFile, Pfad, SW_HIDE);

	if ( reinterpret_cast<int>(hInst) <= 32 ) Message(IDS_ERROPEN_ECCDemo, MB_ICONSTOP);
}

void CCrypToolApp::OnFlashAesdemo()
{
	CString AESDemoExecStr;
	AESDemoExecStr.LoadString(IDS_AESDEMO_EXEC_STR);

  	
	HINSTANCE hInst = ShellExecute(NULL,NULL, AESDemoExecStr, " ", Pfad, SW_SHOW);
	if ( reinterpret_cast<int>(hInst) <= 32 ) {
		// display error message stating where the desired executable is expected
		CString message;
		message.Format(IDS_ERROR_OPEN_FLASHAESDEMO, Pfad);
		AfxMessageBox(message, MB_ICONSTOP);
	}
}

void CCrypToolApp::OnFlashRijndaelInspector()
{
	CString RijndaelInspectorExecStr;
	RijndaelInspectorExecStr.LoadString(IDS_RIJNDAEL_INSPECTOR_EXEC_STR);


	HINSTANCE hInst = ShellExecute(NULL,NULL, RijndaelInspectorExecStr, " ", Pfad, SW_SHOW);
	if ( reinterpret_cast<int>(hInst) <= 32 ) {
		// display error message stating where the desired executable is expected
		CString message;
		message.Format(IDS_ERROR_OPEN_RIJNDAELINSPECTOR, Pfad);
		AfxMessageBox(message, MB_ICONSTOP);
	}
}

void CCrypToolApp::OnInteractiveNumberTheory()
{
	CString InteractiveNTExecStr;
	InteractiveNTExecStr.LoadString(IDS_INTERACTIVE_NUMBER_THEORY_EXEC);


	HINSTANCE hInst = ShellExecute(NULL,NULL, InteractiveNTExecStr, " ", Pfad, SW_SHOW);
	if ( reinterpret_cast<int>(hInst) <= 32 ) {
		// display error message stating where the desired executable is expected
		CString message;
		message.Format(IDS_ERROPEN_INTERACTIVE_NUMBER_THEORY, Pfad);
		AfxMessageBox(message, MB_ICONSTOP);
	}
}

void CCrypToolApp::OnFlashEnigmademo()
{
	CString EnigmaFlashExecStr;
	EnigmaFlashExecStr.LoadString(IDS_ENIGMA_FLASH);


	HINSTANCE hInst = ShellExecute(NULL,NULL, EnigmaFlashExecStr, " ", Pfad, SW_SHOW);
	if ( reinterpret_cast<int>(hInst) <= 32 ) {
		// display error message stating where the desired executable is expected
		CString message;
		message.Format(IDS_ERROPEN_ENIGMA_FLASH, Pfad);
		AfxMessageBox(message, MB_ICONSTOP);
	}
}

void CCrypToolApp::OnProtokolSMIME()
{
	CString smimeParamStr, smimeDemoExecStr;
	smimeParamStr.LoadString(IDS_SMIMEDEMO_PARAM);
	smimeDemoExecStr.LoadString (IDS_SMIMEDEMO_EXE);

	HINSTANCE hInst = ShellExecute(NULL,NULL, smimeDemoExecStr, smimeParamStr, Pfad, SW_SHOW);
	if ( reinterpret_cast<int>(hInst) <= 32 ) {
		// display error message stating where the desired executable is expected
		CString message;
		message.Format(IDS_ERROPEN_SMIMEDEMO, Pfad);
		AfxMessageBox(message, MB_ICONSTOP);
	}
}
