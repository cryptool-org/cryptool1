// MFC-ZahlenHai.h : Hauptheaderdatei f�r die MFC-ZahlenHai-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error 'stdafx.h' muss vor dieser Datei in PCH eingeschlossen werden.
#endif

#include "resource.h"		// Hauptsymbole


// CMFCZahlenHaiApp:
// Siehe MFC-ZahlenHai.cpp f�r die Implementierung dieser Klasse
//

class CMFCZahlenHaiApp : public CWinApp
{
public:
	CMFCZahlenHaiApp();

// �berschreibungen
	public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CMFCZahlenHaiApp theApp;
