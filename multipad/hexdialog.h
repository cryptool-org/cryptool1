//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
#ifndef HEXDIALOG_H
#define HEXDIALOG_H

#include "dia1.h"
#include "HexEdit1.h"

#define MAX_ANZ_HEX_BLOECKE MAX_VIGENERE
// hexdialog.h : Header-Datei
//
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld hexdialog 

class hexdialog : public dia1
{
    int i_maxlen;
// Konstruktion
public:
	hexdialog(int maxlen, CWnd* pParent = NULL);   // Standardkonstruktor

	virtual char * GetData( void );
	virtual int GetLen( void );
	virtual int Display();

// Dialogfelddaten
	//{{AFX_DATA(hexdialog)
	enum { IDD = IDD_DIALOG_KEY_INPUT };
	CHexEdit	m_einfeld;
	CString	m_einstr;
	CString	m_static_text;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(hexdialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(hexdialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // HEXDIALOG_H