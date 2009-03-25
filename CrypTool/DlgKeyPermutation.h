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


#if !defined(AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_)
#define AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogPermutation.h : Header-Datei
//
#include "AscEdit.h"
#include "Cryptography.h"
#include "DlgKeyPermutationInfo.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyPermutation 

// #define MAX_PERM_LENGTH <Innerhalb der Datei AscEdit.h defniert>

#define INV_TOKEN "INV, "
#define PARAM_TOKEN "PARAMETER: "

class CDlgKeyPermutation : public CDialog
{
	CBitmapButton m_Paste;
	// Konstruktion
public:
	int MakePermInt(CString *Pin, int p[], int pinv[]);
	CString makeASCII( CString &line);
	int PrintPerm(char *dest, int *perm, int len);
	int m_Dec;
	int MakePerm(CString *Pin, int p[MAX_PERM_LENGTH], int pinv[MAX_PERM_LENGTH]);
	int m_P1[MAX_PERM_LENGTH];
	int m_P1inv[MAX_PERM_LENGTH];
	int m_P1len;
	int m_P2[MAX_PERM_LENGTH];
	int m_P2inv[MAX_PERM_LENGTH];
	int m_P2len;
	CDlgKeyPermutation(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyPermutation)
	enum { IDD = IDD_KEY_PERMUTATION };
	CButton	 m_Decrypt;
	CButton	 m_Encrypt;
	CButton  chk_showPermutations;
	CAscEdit m_CPerm2;
	CAscEdit m_CPerm1;
	CString  m_Perm1;
	CString	 m_Perm2;
	CString	 m_P1out;
	CString	 m_P2out;
	int		 m_P1InSeq;
	int		 m_P1OutSeq;
	int		 m_P2InSeq;
	int		 m_P2OutSeq;
	int		 m_P1Perm;
	int		 m_P2Perm;
	int		 m_DataType;
	BOOL	 m_Invert;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyPermutation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyPermutation)
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	afx_msg void OnPasteKey();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	// Required because of BACK-Button from CDlgKeyPermutationInfo !!!
public:
	int ShowPermutations();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_
