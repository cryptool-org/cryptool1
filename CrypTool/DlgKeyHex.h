//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
#ifndef HEXDIALOG_H
#define HEXDIALOG_H

#include "DlgKey.h"
#include "HexEdit.h"

#define MAX_ANZ_HEX_BLOECKE MAX_VIGENERE

// hexdialog.h : Header-Datei
//
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHex 

class CDlgKeyHex : public CDlgKey
{
    int i_maxlen;
// Konstruktion
public:
	CDlgKeyHex(int maxlen, CWnd* pParent = NULL);   // Standardkonstruktor
	virtual char * GetData( void );
	virtual int GetLen( void );
	virtual int Display();

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHex)
	enum { IDD = IDD_KEY };
	CHexEdit	m_einfeld;
	CString		m_einstr;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHex)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHex)
	afx_msg void OnUpdateKey();
	afx_msg void OnPasteHexKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // HEXDIALOG_H
