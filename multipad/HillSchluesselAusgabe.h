//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
#ifndef AFX_HILLSCHLUESSELAUSGABE_H__2270633D_8B55_11D2_8D35_00C04F795E36__INCLUDED_
#define AFX_HILLSCHLUESSELAUSGABE_H__2270633D_8B55_11D2_8D35_00C04F795E36__INCLUDED_

#include "hill.h"

// HillSchluesselAusgabe.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CHillSchluesselAusgabe 

class CHillSchluesselAusgabe : public CDialog
{
// Konstruktion
	int keyDimension;
public:
	void SchluesselAnzeigen (CString Key);
	void MatrixAnzeigen(square_matrix& mat, int dim, hill& hillklasse);
	CString* m_pFelder[HILL_MAX_DIM][HILL_MAX_DIM];
	CEdit* m_pControlFelder[HILL_MAX_DIM][HILL_MAX_DIM];
	CHillSchluesselAusgabe(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CHillSchluesselAusgabe)
	enum { IDD = IDD_DIALOG_SCHLUESSEL_HILL_ANGRIFF };
	CEdit	m_FeldUnsichtbar;
	CString	m_Feld11;
	CString	m_Feld12;
	CString	m_Feld13;
	CString	m_Feld14;
	CString	m_Feld15;
	CString	m_Feld21;
	CString	m_Feld22;
	CString	m_Feld23;
	CString	m_Feld24;
	CString	m_Feld25;
	CString	m_Feld31;
	CString	m_Feld32;
	CString	m_Feld33;
	CString	m_Feld34;
	CString	m_Feld35;
	CString	m_Feld41;
	CString	m_Feld42;
	CString	m_Feld43;
	CString	m_Feld44;
	CString	m_Feld45;
	CString	m_Feld51;
	CString	m_Feld52;
	CString	m_Feld53;
	CString	m_Feld54;
	CString	m_Feld55;
	CEdit	m_ControlFeld11;
	CEdit	m_ControlFeld12;
	CEdit	m_ControlFeld13;
	CEdit	m_ControlFeld14;
	CEdit	m_ControlFeld15;
	CEdit	m_ControlFeld21;
	CEdit	m_ControlFeld22;
	CEdit	m_ControlFeld23;
	CEdit	m_ControlFeld24;
	CEdit	m_ControlFeld25;
	CEdit	m_ControlFeld31;
	CEdit	m_ControlFeld32;
	CEdit	m_ControlFeld33;
	CEdit	m_ControlFeld34;
	CEdit	m_ControlFeld35;
	CEdit	m_ControlFeld41;
	CEdit	m_ControlFeld42;
	CEdit	m_ControlFeld43;
	CEdit	m_ControlFeld44;
	CEdit	m_ControlFeld45;
	CEdit	m_ControlFeld51;
	CEdit	m_ControlFeld52;
	CEdit	m_ControlFeld53;
	CEdit	m_ControlFeld54;
	CEdit	m_ControlFeld55;
	CButton	m_InvertKnopf;
	int		m_decrypt;
	//}}AFX_DATA

	int		decrypt_vorher;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CHillSchluesselAusgabe)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CFont cf;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CHillSchluesselAusgabe)
	afx_msg void OnDecrypt();
	virtual BOOL OnInitDialog();
	afx_msg void OnVerschluesseln();
	afx_msg void OnEntschluesseln();
	afx_msg void OnKopieren();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_HILLSCHLUESSELAUSGABE_H__2270633D_8B55_11D2_8D35_00C04F795E36__INCLUDED_
