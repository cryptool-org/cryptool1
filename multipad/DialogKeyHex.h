//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef DIALOGKEYHEX_H
#define DIALOGKEYHEX_H

#include "DialogVienereKey.h"
#include "HexEdit1.h"

#define MAX_ANZ_HEX_BLOECKE MAX_VIGENERE
// DialogKeyHex.h : Header-Datei
//
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld hexdialog 

class CDialogKeyHex : public CDialogVienereKey
{
// Konstruktion
public:
	CDialogKeyHex(CWnd* pParent = NULL);   // Standardkonstruktor

	virtual char * GetData( void );
	virtual int GetLen( void );
	virtual int Display(char *, int);
	virtual int Display(CString);
	int len;

// Dialogfelddaten
	//{{AFX_DATA(CDialogKeyHex)
	enum { IDD = IDD_DIALOG_KEY_VIGENERE };
	CHexEdit	m_einfeld;
	CString	m_einstr;
	CString	m_static_text;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDialogKeyHex)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogKeyHex)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // DIALOGKEYHEX_H
