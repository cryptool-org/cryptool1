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

#ifndef AFX_TEXTOPTIONS_H__85C21241_18D7_11D3_8D64_00C04F795E36__INCLUDED_
#define AFX_TEXTOPTIONS_H__85C21241_18D7_11D3_8D64_00C04F795E36__INCLUDED_



// TextOptions.h : Header-Datei
//


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgTextOptions 


class CDlgTextOptions : public CDialog
{
// Konstruktion

public:
	CString m_StrTitle;
	int m_IgnoreCase;
	CDlgTextOptions(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgTextOptions)
	enum { IDD = IDD_TEXT_OPTIONS };
	CEdit	m_CtrlRefFile;
	CButton	m_CaseControl;
	CEdit	m_alphacontrol;
	BOOL	m_Format;
	CString	m_alphabet;
	BOOL	m_Case;
	BOOL	m_LeerVal;
	int		m_GrossVal;
	int		m_KleinVal;
	int		m_SatzVal;
	int		m_ZahlVal;
	BOOL	m_ConvertCase;
	CString	m_trenn;
	BOOL	m_addx;
	CString	m_StrRefFile;
	CStatic	m_InformationAlphabetSize;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgTextOptions)

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL



// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgTextOptions)
	afx_msg void OnUpdateEdit1();
	afx_msg void OnUpdateEdit2();
	afx_msg void OnButton1();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnCheck2();
	virtual void OnOK();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	afx_msg void OnButtonTextoptionenSucheReferenzdatei();
	afx_msg void OnUpdateEditTextoptionenReferenzdatei();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateHeaderAlphabet();
	int UpdateTags();
	CString OldAlphabet;
	BOOL	OldFormat;
	BOOL	OldCase;
public:
	afx_msg void OnBnClickedOk();
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.


#endif // AFX_TEXTOPTIONS_H__85C21241_18D7_11D3_8D64_00C04F795E36__INCLUDED_



