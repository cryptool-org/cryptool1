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
// Programmiert von Bartol Filipovic 1999-2000
//////////////////////////////////////////////////////////////////

#ifndef AFX_RSADEC_H__11C1DEFD_F5DB_11D3_8798_00C04F795E36__INCLUDED_
#define AFX_RSADEC_H__11C1DEFD_F5DB_11D3_8798_00C04F795E36__INCLUDED_

// RsaDec.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRSADecryption 

#include "KeyFileHandling.h"

class CDlgRSADecryption : public CDialog
{
// Konstruktion
public:
	bool disableButtons;
	CDlgRSADecryption(CWnd* pParent = NULL);   // Standardkonstruktor

	CString UserKeyId;
	CString KeyType;
	CString KeyInfo;
	CString Name;
	CString Firstname;
	CString CreatTime;

	CString m_sDialogText;
	CString m_sCancelText;
	CString m_sOKText;
	BOOL	m_bHideDuration;

// Dialogfelddaten
	//{{AFX_DATA(CDlgRSADecryption)
	enum { IDD = IDD_RSA_DECRYPTION };
	CButton	m_OKCtrl;
	CButton	m_CancelCtrl;
	CButton	m_ShowDurationCtrl;
	CListCtrl	m_listview;
	CEdit	m_PinCodeEditctrl;
	CString	m_PinCode;
	BOOL	m_ShowDuration;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgRSADecryption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementierung
protected:

	int FindRow( CString pattern);
	int m_lastSelectedRow;
	int sortBy;
	unsigned nKeylistType;

	void InitAsymKeyListBox(unsigned nLocalKeylistType);
	void UpdateRowSel(int row);
	int GetSpecifRow(UINT mask);

	CSortAsymKeyList sortedAsymKeyList;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRSADecryption)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_RSADEC_H__11C1DEFD_F5DB_11D3_8798_00C04F795E36__INCLUDED_
