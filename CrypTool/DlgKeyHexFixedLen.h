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


#if !defined(AFX_DLGKEYHEXFIXEDLEN_H__F8863501_0F96_11D7_B75D_005056C00001__INCLUDED_)
#define AFX_DLGKEYHEXFIXEDLEN_H__F8863501_0F96_11D7_B75D_005056C00001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKeyHexFixedLen.h : Header-Datei
//
#include "HexEdit.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHexFixedLen 

class CDlgKeyHexFixedLen : public CDialog
{
// Konstruktion
public:
	virtual CString GetKeyFormatted();
	virtual bool ModeIsDecrypt();
	virtual int GetKeyByteLength();
	virtual char * GetKeyBytes();
	virtual void Init(CString title, int keylenmin, int keylenmax, int keylenstep, int parity_check = 0);
	CDlgKeyHexFixedLen(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHexFixedLen)
	enum { IDD = IDD_KEY_HEX_FIXED_LEN };
	CHexEdit	m_key_ctl;
	CComboBox	m_key_len_ctl;
	int		m_key_len_index;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHexFixedLen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CBitmapButton m_paste_key;
	CString m_title; // must be set via Init(...) on InitDialog
	int m_keylenmin, m_keylenmax, m_keylenstep; // must be set via Init(...) on InitDialog
	CFont m_font; // font for m_key_ctl
	bool m_modeisdecrypt; // available after DoModal has finished
	CString m_key_formatted; // available after DoModal has finished
	int m_parity_check;
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHexFixedLen)
	afx_msg void OnChangeKeyLen();
	virtual BOOL OnInitDialog();
	afx_msg void OnEncrypt();
	afx_msg void OnDecrypt();
	afx_msg void OnPasteKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGKEYHEXFIXEDLEN_H__F8863501_0F96_11D7_B75D_005056C00001__INCLUDED_
