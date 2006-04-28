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

class CMFCZahlenHaiApp : public CWinApp
{
public:
	CMFCZahlenHaiApp();

// Überschreibungen
	public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CMFCZahlenHaiApp theApp;
