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
#ifndef AFX_HILLSCHLUESSELAUSGABEGROSS_H__EB1BC793_A3CB_11D3_877D_00C04F795E36__INCLUDED_
#define AFX_HILLSCHLUESSELAUSGABEGROSS_H__EB1BC793_A3CB_11D3_877D_00C04F795E36__INCLUDED_

#include "HillEncryption.h"

// HillSchluesselAusgabeGross.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKeyHill10x10 

class CDlgShowKeyHill10x10 : public CDialog
{
// Konstruktion
public:
	void SchluesselAnzeigen (CString Key);
	void MatrixAnzeigen(CSquareMatrixModN& mat, int dim, CHillEncryption& hillklasse);
	CString* m_pFelder[HILL_MAX_DIM_GROSS][HILL_MAX_DIM_GROSS];
	CEdit* m_pControlFelder[HILL_MAX_DIM_GROSS][HILL_MAX_DIM_GROSS];
	CDlgShowKeyHill10x10(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgShowKeyHill10x10)
	enum { IDD = IDD_SHOW_KEY_HILL10x10 };
	CEdit	m_FeldUnsichtbar;
	CString	m_Feld11;
	CString	m_Feld12;
	CString	m_Feld13;
	CString	m_Feld14;
	CString	m_Feld15;
	CString	m_Feld16;
	CString	m_Feld17;
	CString	m_Feld18;
	CString	m_Feld19;
	CString	m_Feld110;
	CString	m_Feld21;
	CString	m_Feld22;
	CString	m_Feld23;
	CString	m_Feld24;
	CString	m_Feld25;
	CString	m_Feld26;
	CString	m_Feld27;
	CString	m_Feld28;
	CString	m_Feld29;
	CString	m_Feld210;
	CString	m_Feld31;
	CString	m_Feld32;
	CString	m_Feld33;
	CString	m_Feld34;
	CString	m_Feld35;
	CString	m_Feld36;
	CString	m_Feld37;
	CString	m_Feld38;
	CString	m_Feld39;
	CString	m_Feld310;
	CString	m_Feld41;
	CString	m_Feld42;
	CString	m_Feld43;
	CString	m_Feld44;
	CString	m_Feld45;
	CString	m_Feld46;
	CString	m_Feld47;
	CString	m_Feld48;
	CString	m_Feld49;
	CString	m_Feld410;
	CString	m_Feld51;
	CString	m_Feld52;
	CString	m_Feld53;
	CString	m_Feld54;
	CString	m_Feld55;
	CString	m_Feld56;
	CString	m_Feld57;
	CString	m_Feld58;
	CString	m_Feld59;
	CString	m_Feld510;
	CString	m_Feld61;
	CString	m_Feld62;
	CString	m_Feld63;
	CString	m_Feld64;
	CString	m_Feld65;
	CString	m_Feld66;
	CString	m_Feld67;
	CString	m_Feld68;
	CString	m_Feld69;
	CString	m_Feld610;
	CString	m_Feld71;
	CString	m_Feld72;
	CString	m_Feld73;
	CString	m_Feld74;
	CString	m_Feld75;
	CString	m_Feld76;
	CString	m_Feld77;
	CString	m_Feld78;
	CString	m_Feld79;
	CString	m_Feld710;
	CString	m_Feld81;
	CString	m_Feld82;
	CString	m_Feld83;
	CString	m_Feld84;
	CString	m_Feld85;
	CString	m_Feld86;
	CString	m_Feld87;
	CString	m_Feld88;
	CString	m_Feld89;
	CString	m_Feld810;
	CString	m_Feld91;
	CString	m_Feld92;
	CString	m_Feld93;
	CString	m_Feld94;
	CString	m_Feld95;
	CString	m_Feld96;
	CString	m_Feld97;
	CString	m_Feld98;
	CString	m_Feld99;
	CString	m_Feld910;
	CString	m_Feld101;
	CString	m_Feld102;
	CString	m_Feld103;
	CString	m_Feld104;
	CString	m_Feld105;
	CString	m_Feld106;
	CString	m_Feld107;
	CString	m_Feld108;
	CString	m_Feld109;
	CString	m_Feld1010;
	CEdit	m_ControlFeld11;
	CEdit	m_ControlFeld12;
	CEdit	m_ControlFeld13;
	CEdit	m_ControlFeld14;
	CEdit	m_ControlFeld15;
	CEdit	m_ControlFeld16;
	CEdit	m_ControlFeld17;
	CEdit	m_ControlFeld18;
	CEdit	m_ControlFeld19;
	CEdit	m_ControlFeld110;
	CEdit	m_ControlFeld21;
	CEdit	m_ControlFeld22;
	CEdit	m_ControlFeld23;
	CEdit	m_ControlFeld24;
	CEdit	m_ControlFeld25;
	CEdit	m_ControlFeld26;
	CEdit	m_ControlFeld27;
	CEdit	m_ControlFeld28;
	CEdit	m_ControlFeld29;
	CEdit	m_ControlFeld210;
	CEdit	m_ControlFeld31;
	CEdit	m_ControlFeld32;
	CEdit	m_ControlFeld33;
	CEdit	m_ControlFeld34;
	CEdit	m_ControlFeld35;
	CEdit	m_ControlFeld36;
	CEdit	m_ControlFeld37;
	CEdit	m_ControlFeld38;
	CEdit	m_ControlFeld39;
	CEdit	m_ControlFeld310;
	CEdit	m_ControlFeld41;
	CEdit	m_ControlFeld42;
	CEdit	m_ControlFeld43;
	CEdit	m_ControlFeld44;
	CEdit	m_ControlFeld45;
	CEdit	m_ControlFeld46;
	CEdit	m_ControlFeld47;
	CEdit	m_ControlFeld48;
	CEdit	m_ControlFeld49;
	CEdit	m_ControlFeld410;
	CEdit	m_ControlFeld51;
	CEdit	m_ControlFeld52;
	CEdit	m_ControlFeld53;
	CEdit	m_ControlFeld54;
	CEdit	m_ControlFeld55;
	CEdit	m_ControlFeld56;
	CEdit	m_ControlFeld57;
	CEdit	m_ControlFeld58;
	CEdit	m_ControlFeld59;
	CEdit	m_ControlFeld510;
	CEdit	m_ControlFeld61;
	CEdit	m_ControlFeld62;
	CEdit	m_ControlFeld63;
	CEdit	m_ControlFeld64;
	CEdit	m_ControlFeld65;
	CEdit	m_ControlFeld66;
	CEdit	m_ControlFeld67;
	CEdit	m_ControlFeld68;
	CEdit	m_ControlFeld69;
	CEdit	m_ControlFeld610;
	CEdit	m_ControlFeld71;
	CEdit	m_ControlFeld72;
	CEdit	m_ControlFeld73;
	CEdit	m_ControlFeld74;
	CEdit	m_ControlFeld75;
	CEdit	m_ControlFeld76;
	CEdit	m_ControlFeld77;
	CEdit	m_ControlFeld78;
	CEdit	m_ControlFeld79;
	CEdit	m_ControlFeld710;
	CEdit	m_ControlFeld81;
	CEdit	m_ControlFeld82;
	CEdit	m_ControlFeld83;
	CEdit	m_ControlFeld84;
	CEdit	m_ControlFeld85;
	CEdit	m_ControlFeld86;
	CEdit	m_ControlFeld87;
	CEdit	m_ControlFeld88;
	CEdit	m_ControlFeld89;
	CEdit	m_ControlFeld810;
	CEdit	m_ControlFeld91;
	CEdit	m_ControlFeld92;
	CEdit	m_ControlFeld93;
	CEdit	m_ControlFeld94;
	CEdit	m_ControlFeld95;
	CEdit	m_ControlFeld96;
	CEdit	m_ControlFeld97;
	CEdit	m_ControlFeld98;
	CEdit	m_ControlFeld99;
	CEdit	m_ControlFeld910;
	CEdit	m_ControlFeld101;
	CEdit	m_ControlFeld102;
	CEdit	m_ControlFeld103;
	CEdit	m_ControlFeld104;
	CEdit	m_ControlFeld105;
	CEdit	m_ControlFeld106;
	CEdit	m_ControlFeld107;
	CEdit	m_ControlFeld108;
	CEdit	m_ControlFeld109;
	CEdit	m_ControlFeld1010;
	CButton	m_InvertKnopf;
	int		m_decrypt;
	//}}AFX_DATA

	int		decrypt_vorher;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgShowKeyHill10x10)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CFont cf;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowKeyHill10x10)
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

#endif // AFX_HILLSCHLUESSELAUSGABEGROSS_H__EB1BC793_A3CB_11D3_877D_00C04F795E36__INCLUDED_
