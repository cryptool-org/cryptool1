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

// MFC-ZahlenHai.h : Hauptheaderdatei für die MFC-ZahlenHai-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error 'stdafx.h' muss vor dieser Datei in PCH eingeschlossen werden.
#endif

#include "resource.h"		// Hauptsymbole


// CMFCZahlenHaiApp:
// Siehe MFC-ZahlenHai.cpp für die Implementierung dieser Klasse
//

// forward declaration
class CMFCZahlenHaiDlg;

class CMFCZahlenHaiApp : public CWinApp
{
public:
	CMFCZahlenHaiApp();

// Überschreibungen
	public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()

protected:
	// flomar, 05/01/2012: used for clean accelerator handling
	CMFCZahlenHaiDlg *dlg;
	HACCEL accelerator;
	BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
};

extern CMFCZahlenHaiApp theApp;
