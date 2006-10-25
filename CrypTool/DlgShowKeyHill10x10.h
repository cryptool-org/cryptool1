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
	CString* m_pAlphFelder[HILL_MAX_DIM_GROSS][HILL_MAX_DIM_GROSS];

	CEdit* m_pControlFelder[HILL_MAX_DIM_GROSS][HILL_MAX_DIM_GROSS];
	CEdit* m_pControlAlphFelder[HILL_MAX_DIM_GROSS][HILL_MAX_DIM_GROSS];

	CDlgShowKeyHill10x10(CWnd* pParent = NULL);   // Standardkonstruktor

	CString getAlphCode(CString alphChar);

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

	CString m_AlphFeld40;
	CString m_AlphFeld50;
	CString m_AlphFeld20;
	CString m_AlphFeld90;
	CString m_AlphFeld100;
	CString m_AlphFeld117;
	CString m_AlphFeld118;
	CString m_AlphFeld119;
	CString m_AlphFeld60;
	CString m_AlphFeld125;
	CString m_AlphFeld127;
	CString m_AlphFeld213;
	CString m_AlphFeld214;
	CString m_AlphFeld215;
	CString m_AlphFeld70;
	CString m_AlphFeld216;
	CString m_AlphFeld217;
	CString m_AlphFeld218;
	CString m_AlphFeld80;
	CString m_AlphFeld219;
	CString m_AlphFeld220;
	CString m_AlphFeld134;
	CString m_AlphFeld135;
	CString m_AlphFeld136;
	CString m_AlphFeld137;
	CString m_AlphFeld138;
	CString m_AlphFeld139;
	CString m_AlphFeld211;
	CString m_AlphFeld140;
	CString m_AlphFeld312;
	CString m_AlphFeld142;
	CString m_AlphFeld221;
	CString m_AlphFeld222;
	CString m_AlphFeld223;
	CString m_AlphFeld144;
	CString m_AlphFeld145;
	CString m_AlphFeld146;
	CString m_AlphFeld147;
	CString m_AlphFeld148;
	CString m_AlphFeld412;
	CString m_AlphFeld149;
	CString m_AlphFeld150;
	CString m_AlphFeld113;
	CString m_AlphFeld151;
	CString m_AlphFeld152;
	CString m_AlphFeld153;
	CString m_AlphFeld154;
	CString m_AlphFeld155;
	CString m_AlphFeld156;
	CString m_AlphFeld512;
	CString m_AlphFeld224;
	CString m_AlphFeld158;
	CString m_AlphFeld159;
	CString m_AlphFeld160;
	CString m_AlphFeld161;
	CString m_AlphFeld162;
	CString m_AlphFeld163;
	CString m_AlphFeld164;
	CString m_AlphFeld174;
	CString m_AlphFeld612;
	CString m_AlphFeld225;
	CString m_AlphFeld226;
	CString m_AlphFeld166;
	CString m_AlphFeld167;
	CString m_AlphFeld168;
	CString m_AlphFeld169;
	CString m_AlphFeld170;
	CString m_AlphFeld171;
	CString m_AlphFeld172;
	CString m_AlphFeld712;
	CString m_AlphFeld227;
	CString m_AlphFeld175;
	CString m_AlphFeld176;
	CString m_AlphFeld177;
	CString m_AlphFeld178;
	CString m_AlphFeld179;
	CString m_AlphFeld180;
	CString m_AlphFeld191;
	CString m_AlphFeld181;
	CString m_AlphFeld812;
	CString m_AlphFeld183;
	CString m_AlphFeld228;
	CString m_AlphFeld184;
	CString m_AlphFeld185;
	CString m_AlphFeld186;
	CString m_AlphFeld187;
	CString m_AlphFeld188;
	CString m_AlphFeld189;
	CString m_AlphFeld190;
	CString m_AlphFeld912;
	CString m_AlphFeld229;
	CString m_AlphFeld193;
	CString m_AlphFeld194;
	CString m_AlphFeld195;
	CString m_AlphFeld196;
	CString m_AlphFeld197;
	CString m_AlphFeld198;
	CString m_AlphFeld199;
	CString m_AlphFeld200;
	CString m_AlphFeld1012;


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

	CEdit m_ControlAlphFeld40;
	CEdit m_ControlAlphFeld50;
	CEdit m_ControlAlphFeld20;
	CEdit m_ControlAlphFeld90;
	CEdit m_ControlAlphFeld100;
	CEdit m_ControlAlphFeld117;
	CEdit m_ControlAlphFeld118;
	CEdit m_ControlAlphFeld119;
	CEdit m_ControlAlphFeld60;
	CEdit m_ControlAlphFeld125;
	CEdit m_ControlAlphFeld127;
	CEdit m_ControlAlphFeld213;
	CEdit m_ControlAlphFeld214;
	CEdit m_ControlAlphFeld215;
	CEdit m_ControlAlphFeld70;
	CEdit m_ControlAlphFeld216;
	CEdit m_ControlAlphFeld217;
	CEdit m_ControlAlphFeld218;
	CEdit m_ControlAlphFeld80;
	CEdit m_ControlAlphFeld219;
	CEdit m_ControlAlphFeld220;
	CEdit m_ControlAlphFeld134;
	CEdit m_ControlAlphFeld135;
	CEdit m_ControlAlphFeld136;
	CEdit m_ControlAlphFeld137;
	CEdit m_ControlAlphFeld138;
	CEdit m_ControlAlphFeld139;
	CEdit m_ControlAlphFeld211;
	CEdit m_ControlAlphFeld140;
	CEdit m_ControlAlphFeld312;
	CEdit m_ControlAlphFeld142;
	CEdit m_ControlAlphFeld221;
	CEdit m_ControlAlphFeld222;
	CEdit m_ControlAlphFeld223;
	CEdit m_ControlAlphFeld144;
	CEdit m_ControlAlphFeld145;
	CEdit m_ControlAlphFeld146;
	CEdit m_ControlAlphFeld147;
	CEdit m_ControlAlphFeld148;
	CEdit m_ControlAlphFeld412;
	CEdit m_ControlAlphFeld149;
	CEdit m_ControlAlphFeld150;
	CEdit m_ControlAlphFeld113;
	CEdit m_ControlAlphFeld151;
	CEdit m_ControlAlphFeld152;
	CEdit m_ControlAlphFeld153;
	CEdit m_ControlAlphFeld154;
	CEdit m_ControlAlphFeld155;
	CEdit m_ControlAlphFeld156;
	CEdit m_ControlAlphFeld512;
	CEdit m_ControlAlphFeld224;
	CEdit m_ControlAlphFeld158;
	CEdit m_ControlAlphFeld159;
	CEdit m_ControlAlphFeld160;
	CEdit m_ControlAlphFeld161;
	CEdit m_ControlAlphFeld162;
	CEdit m_ControlAlphFeld163;
	CEdit m_ControlAlphFeld164;
	CEdit m_ControlAlphFeld174;
	CEdit m_ControlAlphFeld612;
	CEdit m_ControlAlphFeld225;
	CEdit m_ControlAlphFeld226;
	CEdit m_ControlAlphFeld166;
	CEdit m_ControlAlphFeld167;
	CEdit m_ControlAlphFeld168;
	CEdit m_ControlAlphFeld169;
	CEdit m_ControlAlphFeld170;
	CEdit m_ControlAlphFeld171;
	CEdit m_ControlAlphFeld172;
	CEdit m_ControlAlphFeld712;
	CEdit m_ControlAlphFeld227;
	CEdit m_ControlAlphFeld175;
	CEdit m_ControlAlphFeld176;
	CEdit m_ControlAlphFeld177;
	CEdit m_ControlAlphFeld178;
	CEdit m_ControlAlphFeld179;
	CEdit m_ControlAlphFeld180;
	CEdit m_ControlAlphFeld191;
	CEdit m_ControlAlphFeld181;
	CEdit m_ControlAlphFeld812;
	CEdit m_ControlAlphFeld183;
	CEdit m_ControlAlphFeld228;
	CEdit m_ControlAlphFeld184;
	CEdit m_ControlAlphFeld185;
	CEdit m_ControlAlphFeld186;
	CEdit m_ControlAlphFeld187;
	CEdit m_ControlAlphFeld188;
	CEdit m_ControlAlphFeld189;
	CEdit m_ControlAlphFeld190;
	CEdit m_ControlAlphFeld912;
	CEdit m_ControlAlphFeld229;
	CEdit m_ControlAlphFeld193;
	CEdit m_ControlAlphFeld194;
	CEdit m_ControlAlphFeld195;
	CEdit m_ControlAlphFeld196;
	CEdit m_ControlAlphFeld197;
	CEdit m_ControlAlphFeld198;
	CEdit m_ControlAlphFeld199;
	CEdit m_ControlAlphFeld200;
	CEdit m_ControlAlphFeld1012;


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
