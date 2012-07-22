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

// MFC-ZahlenHai.cpp : Definiert das Klassenverhalten f�r die Anwendung.
//

#include "stdafx.h"
#include "MFC-ZahlenHai.h"
#include "MFC-ZahlenHaiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCZahlenHaiApp

BEGIN_MESSAGE_MAP(CMFCZahlenHaiApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCZahlenHaiApp-Erstellung

CMFCZahlenHaiApp::CMFCZahlenHaiApp()
{
	// TODO: Hier Code zur Konstruktion einf�gen
	// Alle wichtigen Initialisierungen in InitInstance positionieren
}


// Das einzige CMFCZahlenHaiApp-Objekt

CMFCZahlenHaiApp theApp;


// CMFCZahlenHaiApp Initialisierung

BOOL CMFCZahlenHaiApp::InitInstance()
{
	CWinApp::InitInstance();

	AfxEnableControlContainer();
	AfxInitRichEdit();

	// initialize our accelerator object
	accelerator = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));

	// Standardinitialisierung
	// Wenn Sie diese Features nicht verwenden und die Gr��e
	// der ausf�hrbaren Datei verringern m�chten, entfernen Sie
	// die nicht erforderlichen Initialisierungsroutinen.
	// �ndern Sie den Registrierungsschl�ssel unter dem Ihre Einstellungen gespeichert sind.
	// TODO: �ndern Sie diese Zeichenfolge entsprechend,
	// z.B. zum Namen Ihrer Firma oder Organisation.
	SetRegistryKey(_T("Vom lokalen Anwendungs-Assistenten generierte Anwendungen"));

	dlg = 0;
	dlg = new CMFCZahlenHaiDlg;
	m_pMainWnd = dlg;
	INT_PTR nResponse = dlg->DoModal();
	if (nResponse == IDOK)
	{
		// TODO: F�gen Sie hier Code ein, um das Schlie�en des
		//  Dialogfelds �ber OK zu steuern
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: F�gen Sie hier Code ein, um das Schlie�en des
		//  Dialogfelds �ber "Abbrechen" zu steuern
	}

	delete dlg;

	// Da das Dialogfeld geschlossen wurde, FALSE zur�ckliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}

BOOL CMFCZahlenHaiApp::ProcessMessageFilter(int code, LPMSG lpMsg)
{
	// try to let the accelerator handle the message
	if(accelerator) {
		if (::TranslateAccelerator(m_pMainWnd->m_hWnd, accelerator, lpMsg)) {
			if(lpMsg->message == 260) {
				// SHIFT+ALT+C
				if(lpMsg->wParam == 67) {
					dlg->OnBnClickedButtonSwitchStyle();
					return(TRUE);
				}
				// SHIFT+ALT+L
				if(lpMsg->wParam == 76) {
					dlg->OnBnClickedButtonLoad();
					return(TRUE);
				}
				// SHIFT+ALT+S
				if(lpMsg->wParam == 83) {
					dlg->OnBnClickedButtonSave();
					return(TRUE);
				}
			}
    }
	}
	// otherwise use the default implementation
	return CWinApp::ProcessMessageFilter(code, lpMsg);
}

