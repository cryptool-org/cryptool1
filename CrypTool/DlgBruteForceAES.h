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
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Dialogfeld CDlgBruteForceAES 

#if !defined(AFX_AESSUCHE_H__D6167951_518F_11D4_A04D_002035F23D41__INCLUDED_)
#define AFX_AESSUCHE_H__D6167951_518F_11D4_A04D_002035F23D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgBruteForceAES 

class CDlgBruteForceAES : public CDialog, public CProgressModel
{
// Konstruktion
public:
	CDlgBruteForceAES(CWnd* pParent = NULL);   // Standardkonstruktor

	char m_data[256/8*2+1];
	int m_mask[256/8*2+1];
	int m_state; // -1: initially, 1: after first Step, 0: after last Step
	int m_len;
	int m_text_len;
	int m_parity_check;
	CString m_alg;
	int Display(char *titel,int keylenmin,int keylenmax, int keylenstep, int _parity_check = 0);
	int GetLen();
	int GetBinlen();
	int GetSearchBitLen();
	char *GetData();
	void GetDataInt(char *);
	int Step(); // set next key if not finished, otherwise return false
	virtual double getProgress(); // 0.0 <= result <= 1.0

// Dialogfelddaten
	//{{AFX_DATA(CDlgBruteForceAES)
	enum { IDD = IDD_BRUTEFORCE };
	CComboBox	m_keylen_ctl;
	CHexEdit m_text_ctl;
	int		m_keylenindex;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgBruteForceAES)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	char m_hexinc['F'];
	int m_keylenmin, m_keylenmax, m_keylenstep; // see CryptPar
	CFont m_font; // font for m_text_ctl
	CString m_text; // m_text_ctl content
	void UpdateDataMask();
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgBruteForceAES)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeKeyLen();
	virtual void OnOK();
	afx_msg void OnSetfocusHexEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_AESSUCHE_H__D6167951_518F_11D4_A04D_002035F23D41__INCLUDED_
