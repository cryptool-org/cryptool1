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
#ifndef AFX_HILLEINGABEGROSS_H__EB1BC795_A3CB_11D3_877D_00C04F795E36__INCLUDED_
#define AFX_HILLEINGABEGROSS_H__EB1BC795_A3CB_11D3_877D_00C04F795E36__INCLUDED_

// HillEingabeGross.h : Header-Datei
//

#include "HillEncryption.h"
#include "Cryptography.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHill10x10 

class CDlgKeyHill10x10 : public CDialog
{
	CBitmapButton m_Paste;
// Konstruktion
public:
	int		m_decrypt;
	CSquareMatrixModN * mat;
	void UpdateFeld (CEdit*feld);
	void MatrixEinlesen(CSquareMatrixModN& mat, int dim);
	void MatrixAnzeigen(CSquareMatrixModN& mat);
	bool NaechsterEintrag(int& i, int& j) ;
	int AlleFelderKorrekt(int);
	void AnzeigeDimensionSetzen(int);
	int dim;
	int Display(CHillEncryption *);
	CHiEdit* m_pFelder[HILL_MAX_DIM_GROSS][HILL_MAX_DIM_GROSS];
	CDlgKeyHill10x10(CHillEncryption *hillkl, CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgKeyHill10x10();

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHill10x10)
	enum { IDD = IDD_KEY_HILL_10X10 };
	BOOL	m_Verbose;
	CEdit	m_FeldUnsichtbar;
	class CHiEdit	m_Feld11;
	class CHiEdit	m_Feld12;
	class CHiEdit	m_Feld13;
	class CHiEdit	m_Feld14;
	class CHiEdit	m_Feld15;
	class CHiEdit	m_Feld16;
	class CHiEdit	m_Feld17;
	class CHiEdit	m_Feld18;
	class CHiEdit	m_Feld19;
	class CHiEdit	m_Feld110;
	class CHiEdit	m_Feld21;
	class CHiEdit	m_Feld22;
	class CHiEdit	m_Feld23;
	class CHiEdit	m_Feld24;
	class CHiEdit	m_Feld25;
	class CHiEdit	m_Feld26;
	class CHiEdit	m_Feld27;
	class CHiEdit	m_Feld28;
	class CHiEdit	m_Feld29;
	class CHiEdit	m_Feld210;
	class CHiEdit	m_Feld31;
	class CHiEdit	m_Feld32;
	class CHiEdit	m_Feld33;
	class CHiEdit	m_Feld34;
	class CHiEdit	m_Feld35;
	class CHiEdit	m_Feld36;
	class CHiEdit	m_Feld37;
	class CHiEdit	m_Feld38;
	class CHiEdit	m_Feld39;
	class CHiEdit	m_Feld310;
	class CHiEdit	m_Feld41;
	class CHiEdit	m_Feld42;
	class CHiEdit	m_Feld43;
	class CHiEdit	m_Feld44;
	class CHiEdit	m_Feld45;
	class CHiEdit	m_Feld46;
	class CHiEdit	m_Feld47;
	class CHiEdit	m_Feld48;
	class CHiEdit	m_Feld49;
	class CHiEdit	m_Feld410;
	class CHiEdit	m_Feld51;
	class CHiEdit	m_Feld52;
	class CHiEdit	m_Feld53;
	class CHiEdit	m_Feld54;
	class CHiEdit	m_Feld55;
	class CHiEdit	m_Feld56;
	class CHiEdit	m_Feld57;
	class CHiEdit	m_Feld58;
	class CHiEdit	m_Feld59;
	class CHiEdit	m_Feld510;
	class CHiEdit	m_Feld61;
	class CHiEdit	m_Feld62;
	class CHiEdit	m_Feld63;
	class CHiEdit	m_Feld64;
	class CHiEdit	m_Feld65;
	class CHiEdit	m_Feld66;
	class CHiEdit	m_Feld67;
	class CHiEdit	m_Feld68;
	class CHiEdit	m_Feld69;
	class CHiEdit	m_Feld610;
	class CHiEdit	m_Feld71;
	class CHiEdit	m_Feld72;
	class CHiEdit	m_Feld73;
	class CHiEdit	m_Feld74;
	class CHiEdit	m_Feld75;
	class CHiEdit	m_Feld76;
	class CHiEdit	m_Feld77;
	class CHiEdit	m_Feld78;
	class CHiEdit	m_Feld79;
	class CHiEdit	m_Feld710;
	class CHiEdit	m_Feld81;
	class CHiEdit	m_Feld82;
	class CHiEdit	m_Feld83;
	class CHiEdit	m_Feld84;
	class CHiEdit	m_Feld85;
	class CHiEdit	m_Feld86;
	class CHiEdit	m_Feld87;
	class CHiEdit	m_Feld88;
	class CHiEdit	m_Feld89;
	class CHiEdit	m_Feld810;
	class CHiEdit	m_Feld91;
	class CHiEdit	m_Feld92;
	class CHiEdit	m_Feld93;
	class CHiEdit	m_Feld94;
	class CHiEdit	m_Feld95;
	class CHiEdit	m_Feld96;
	class CHiEdit	m_Feld97;
	class CHiEdit	m_Feld98;
	class CHiEdit	m_Feld99;
	class CHiEdit	m_Feld910;
	class CHiEdit	m_Feld101;
	class CHiEdit	m_Feld102;
	class CHiEdit	m_Feld103;
	class CHiEdit	m_Feld104;
	class CHiEdit	m_Feld105;
	class CHiEdit	m_Feld106;
	class CHiEdit	m_Feld107;
	class CHiEdit	m_Feld108;
	class CHiEdit	m_Feld109;
	class CHiEdit	m_Feld1010;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHill10x10)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CFont cf;
	CHillEncryption *hillklasse;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHill10x10)
	virtual void OnOK();
	virtual void OnDecrypt();
	afx_msg void OnPasteKey();
	virtual BOOL OnInitDialog();
	afx_msg void OnDimension1();
	afx_msg void OnDimension2();
	afx_msg void OnDimension3();
	afx_msg void OnDimension4();
	afx_msg void OnDimension5();
	afx_msg void OnDimension6();
	afx_msg void OnDimension7();
	afx_msg void OnDimension8();
	afx_msg void OnDimension9();
	afx_msg void OnDimension10();
	afx_msg	void OnUpdateMat11();
	afx_msg	void OnUpdateMat12();
	afx_msg	void OnUpdateMat13();
	afx_msg	void OnUpdateMat14();
	afx_msg	void OnUpdateMat15();
	afx_msg	void OnUpdateMat16();
	afx_msg	void OnUpdateMat17();
	afx_msg	void OnUpdateMat18();
	afx_msg	void OnUpdateMat19();
	afx_msg	void OnUpdateMat110();
	afx_msg	void OnUpdateMat21();
	afx_msg	void OnUpdateMat22();
	afx_msg	void OnUpdateMat23();
	afx_msg	void OnUpdateMat24();
	afx_msg	void OnUpdateMat25();
	afx_msg	void OnUpdateMat26();
	afx_msg	void OnUpdateMat27();
	afx_msg	void OnUpdateMat28();
	afx_msg	void OnUpdateMat29();
	afx_msg	void OnUpdateMat210();
	afx_msg	void OnUpdateMat31();
	afx_msg	void OnUpdateMat32();
	afx_msg	void OnUpdateMat33();
	afx_msg	void OnUpdateMat34();
	afx_msg	void OnUpdateMat35();
	afx_msg	void OnUpdateMat36();
	afx_msg	void OnUpdateMat37();
	afx_msg	void OnUpdateMat38();
	afx_msg	void OnUpdateMat39();
	afx_msg	void OnUpdateMat310();
	afx_msg	void OnUpdateMat41();
	afx_msg	void OnUpdateMat42();
	afx_msg	void OnUpdateMat43();
	afx_msg	void OnUpdateMat44();
	afx_msg	void OnUpdateMat45();
	afx_msg	void OnUpdateMat46();
	afx_msg	void OnUpdateMat47();
	afx_msg	void OnUpdateMat48();
	afx_msg	void OnUpdateMat49();
	afx_msg	void OnUpdateMat410();
	afx_msg	void OnUpdateMat51();
	afx_msg	void OnUpdateMat52();
	afx_msg	void OnUpdateMat53();
	afx_msg	void OnUpdateMat54();
	afx_msg	void OnUpdateMat55();
	afx_msg	void OnUpdateMat56();
	afx_msg	void OnUpdateMat57();
	afx_msg	void OnUpdateMat58();
	afx_msg	void OnUpdateMat59();
	afx_msg	void OnUpdateMat510();
	afx_msg	void OnUpdateMat61();
	afx_msg	void OnUpdateMat62();
	afx_msg	void OnUpdateMat63();
	afx_msg	void OnUpdateMat64();
	afx_msg	void OnUpdateMat65();
	afx_msg	void OnUpdateMat66();
	afx_msg	void OnUpdateMat67();
	afx_msg	void OnUpdateMat68();
	afx_msg	void OnUpdateMat69();
	afx_msg	void OnUpdateMat610();
	afx_msg	void OnUpdateMat71();
	afx_msg	void OnUpdateMat72();
	afx_msg	void OnUpdateMat73();
	afx_msg	void OnUpdateMat74();
	afx_msg	void OnUpdateMat75();
	afx_msg	void OnUpdateMat76();
	afx_msg	void OnUpdateMat77();
	afx_msg	void OnUpdateMat78();
	afx_msg	void OnUpdateMat79();
	afx_msg	void OnUpdateMat710();
	afx_msg	void OnUpdateMat81();
	afx_msg	void OnUpdateMat82();
	afx_msg	void OnUpdateMat83();
	afx_msg	void OnUpdateMat84();
	afx_msg	void OnUpdateMat85();
	afx_msg	void OnUpdateMat86();
	afx_msg	void OnUpdateMat87();
	afx_msg	void OnUpdateMat88();
	afx_msg	void OnUpdateMat89();
	afx_msg	void OnUpdateMat810();
	afx_msg	void OnUpdateMat91();
	afx_msg	void OnUpdateMat92();
	afx_msg	void OnUpdateMat93();
	afx_msg	void OnUpdateMat94();
	afx_msg	void OnUpdateMat95();
	afx_msg	void OnUpdateMat96();
	afx_msg	void OnUpdateMat97();
	afx_msg	void OnUpdateMat98();
	afx_msg	void OnUpdateMat99();
	afx_msg	void OnUpdateMat910();
	afx_msg	void OnUpdateMat101();
	afx_msg	void OnUpdateMat102();
	afx_msg	void OnUpdateMat103();
	afx_msg	void OnUpdateMat104();
	afx_msg	void OnUpdateMat105();
	afx_msg	void OnUpdateMat106();
	afx_msg	void OnUpdateMat107();
	afx_msg	void OnUpdateMat108();
	afx_msg	void OnUpdateMat109();
	afx_msg	void OnUpdateMat1010();
	afx_msg void OnZufaelligerSchluessel();
	afx_msg void OnKleinereSchluessel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_HILLEINGABEGROSS_H__EB1BC795_A3CB_11D3_877D_00C04F795E36__INCLUDED_
