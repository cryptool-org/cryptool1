//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef DIALOGKEYHEX_H
#define DIALOGKEYHEX_H

#include "DlgKeyVigenere.h"
#include "HexEdit.h"

#define MAX_ANZ_HEX_BLOECKE MAX_VIGENERE
// DialogKeyHex.h : Header-Datei
//
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHex 

class CDlgKeyHexAnalysis : public CDlgKeyVigenereAnalyisis
{
// Konstruktion
public:
	CDlgKeyHexAnalysis(CWnd* pParent = NULL);   // Standardkonstruktor

	virtual char * GetData( void );
	virtual int GetLen( void );
	virtual int GetHexData(LPTSTR v, int len); // copy m_einstr, removing non-hex chars
	virtual int Display(char *, int);
	virtual int Display(CString);
	int len;

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHexAnalysis)
	enum { IDD = IDD_KEY_ANALYSIS };
	CHexEdit	m_einfeld;
	CString	m_einstr;
	CString	m_static_text;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHexAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CFont m_font; // font for key display
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHexAnalysis)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // DIALOGKEYHEX_H
