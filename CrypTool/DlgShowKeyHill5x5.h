/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
#ifndef AFX_HILLSCHLUESSELAUSGABE_H__2270633D_8B55_11D2_8D35_00C04F795E36__INCLUDED_
#define AFX_HILLSCHLUESSELAUSGABE_H__2270633D_8B55_11D2_8D35_00C04F795E36__INCLUDED_

#include "HillEncryption.h"

// HillSchluesselAusgabe.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKeyHill5x5 

class CDlgShowKeyHill5x5 : public CDialog
{
// Konstruktion
	int keyDimension;
public:
	void SchluesselAnzeigen (CString Key);
	void MatrixAnzeigen(CSquareMatrixModN& mat, int dim, CHillEncryption& hillklasse);
	CString* m_pFelder[HILL_MAX_DIM][HILL_MAX_DIM];
	CString* m_pAlphFelder[HILL_MAX_DIM][HILL_MAX_DIM];
	CEdit* m_pControlFelder[HILL_MAX_DIM][HILL_MAX_DIM];
	CEdit* m_pControlAlphFelder[HILL_MAX_DIM][HILL_MAX_DIM];
	CDlgShowKeyHill5x5(CWnd* pParent = NULL);   // Standardkonstruktor

	CString getAlphCode(CString alphChar);

// Dialogfelddaten
	//{{AFX_DATA(CDlgShowKeyHill5x5)
	enum { IDD = IDD_SHOW_KEY_HILL5x5 };
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

	CString	m_AlphFeld36;
	CString	m_AlphFeld37;
	CString	m_AlphFeld38;
	CString	m_AlphFeld40;
	CString	m_AlphFeld46;
	CString	m_AlphFeld47;
	CString	m_AlphFeld48;
	CString	m_AlphFeld49;
	CString	m_AlphFeld50;
	CString	m_AlphFeld111;
	CString	m_AlphFeld57;
	CString	m_AlphFeld58;
	CString	m_AlphFeld59;
	CString	m_AlphFeld56;
	CString	m_AlphFeld115;
	CString	m_AlphFeld60;
	CString	m_AlphFeld61;
	CString	m_AlphFeld62;
	CString	m_AlphFeld116;
	CString	m_AlphFeld117;
	CString	m_AlphFeld63;
	CString	m_AlphFeld64;
	CString	m_AlphFeld69;
	CString	m_AlphFeld65;
	CString	m_AlphFeld66;


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

	CEdit	m_ControlAlphFeld36;
	CEdit	m_ControlAlphFeld37;
	CEdit	m_ControlAlphFeld38;
	CEdit	m_ControlAlphFeld40;
	CEdit	m_ControlAlphFeld46;
	CEdit	m_ControlAlphFeld47;
	CEdit	m_ControlAlphFeld48;
	CEdit	m_ControlAlphFeld49;
	CEdit	m_ControlAlphFeld50;
	CEdit	m_ControlAlphFeld111;
	CEdit	m_ControlAlphFeld57;
	CEdit	m_ControlAlphFeld58;
	CEdit	m_ControlAlphFeld59;
	CEdit	m_ControlAlphFeld56;
	CEdit	m_ControlAlphFeld115;
	CEdit	m_ControlAlphFeld60;
	CEdit	m_ControlAlphFeld61;
	CEdit	m_ControlAlphFeld62;
	CEdit	m_ControlAlphFeld116;
	CEdit	m_ControlAlphFeld117;
	CEdit	m_ControlAlphFeld63;
	CEdit	m_ControlAlphFeld64;
	CEdit	m_ControlAlphFeld69;
	CEdit	m_ControlAlphFeld65;
	CEdit	m_ControlAlphFeld66;

	CButton	m_InvertKnopf;
	int		m_decrypt;
	//}}AFX_DATA

	int		decrypt_vorher;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgShowKeyHill5x5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CFont cf;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowKeyHill5x5)
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
