/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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
#ifndef AFX_HILLEINGABE_H__218034DD_7572_11D2_8D2B_00C04F795E36__INCLUDED_
#define AFX_HILLEINGABE_H__218034DD_7572_11D2_8D2B_00C04F795E36__INCLUDED_

// HillEingabe.h : Header-Datei
//

#include "HillEncryption.h"
#include "Cryptography.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHill5x5 

class CHiEdit : public CEdit
{
protected:
	//{{AFX_MSG(CHiEdit)
	afx_msg void OnLButtonUp(UINT, CPoint);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
};

class CDlgKeyHill5x5 : public CDialog
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
	class CHiEdit* m_pFelder[HILL_MAX_DIM][HILL_MAX_DIM];
	CDlgKeyHill5x5(CHillEncryption *hillkl, CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgKeyHill5x5();

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHill5x5)
	enum { IDD = IDD_KEY_HILL5X5 };
	BOOL	m_Verbose;
	CEdit	m_FeldUnsichtbar;
	class CHiEdit	m_Feld11;
	class CHiEdit	m_Feld12;
	class CHiEdit	m_Feld13;
	class CHiEdit	m_Feld14;
	class CHiEdit	m_Feld15;
	class CHiEdit	m_Feld21;
	class CHiEdit	m_Feld22;
	class CHiEdit	m_Feld23;
	class CHiEdit	m_Feld24;
	class CHiEdit	m_Feld25;
	class CHiEdit	m_Feld31;
	class CHiEdit	m_Feld32;
	class CHiEdit	m_Feld33;
	class CHiEdit	m_Feld34;
	class CHiEdit	m_Feld35;
	class CHiEdit	m_Feld41;
	class CHiEdit	m_Feld42;
	class CHiEdit	m_Feld43;
	class CHiEdit	m_Feld44;
	class CHiEdit	m_Feld45;
	class CHiEdit	m_Feld51;
	class CHiEdit	m_Feld52;
	class CHiEdit	m_Feld53;
	class CHiEdit	m_Feld54;
	class CHiEdit	m_Feld55;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHill5x5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CFont cf;
	CHillEncryption *hillklasse;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHill5x5)
	virtual void OnOK();
	virtual void OnDecrypt();
	virtual BOOL OnInitDialog();
	afx_msg void OnPasteKey();
	afx_msg void OnDimension1();
	afx_msg void OnDimension2();
	afx_msg void OnDimension3();
	afx_msg void OnDimension4();
	afx_msg void OnDimension5();
	afx_msg void OnUpdateMat11();
	afx_msg void OnUpdateMat12();
	afx_msg void OnUpdateMat13();
	afx_msg void OnUpdateMat14();
	afx_msg void OnUpdateMat15();
	afx_msg void OnUpdateMat21();
	afx_msg void OnUpdateMat22();
	afx_msg void OnUpdateMat23();
	afx_msg void OnUpdateMat24();
	afx_msg void OnUpdateMat25();
	afx_msg void OnUpdateMat31();
	afx_msg void OnUpdateMat32();
	afx_msg void OnUpdateMat33();
	afx_msg void OnUpdateMat34();
	afx_msg void OnUpdateMat35();
	afx_msg void OnUpdateMat41();
	afx_msg void OnUpdateMat42();
	afx_msg void OnUpdateMat43();
	afx_msg void OnUpdateMat44();
	afx_msg void OnUpdateMat45();
	afx_msg void OnUpdateMat51();
	afx_msg void OnUpdateMat52();
	afx_msg void OnUpdateMat53();
	afx_msg void OnUpdateMat54();
	afx_msg void OnUpdateMat55();
	afx_msg void OnZufaelligerSchluessel();
	afx_msg void OnGroessereSchluessel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_HILLEINGABE_H__218034DD_7572_11D2_8D2B_00C04F795E36__INCLUDED_
