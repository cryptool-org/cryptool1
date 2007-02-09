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


#ifndef AFX_RSAENC_H__9BB28A41_A60A_11D2_8881_00C04F795E28__INCLUDED_
#define AFX_RSAENC_H__9BB28A41_A60A_11D2_8881_00C04F795E28__INCLUDED_

// RsaEnc.h : Header-Datei
//
#include "KeyFileHandling.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRSAEncryption 

class CDlgRSAEncryption : public CDialog
{
// Konstruktion
public:
	bool disableButtons;
	bool encryptButtonVisible;
	CDlgRSAEncryption(CWnd* pParent = NULL);   // Standardkonstruktor

	CString Name;
	CString Firstname;
	CString CreatTime;
	
	// formerly protected
	CString KeyType;
	CString KeyInfo;

	CString UserKeyId; //roger???
	CString oldTitle;

// Dialogfelddaten
	//{{AFX_DATA(CDlgRSAEncryption)
	enum { IDD = IDD_RSA_ENCRYPTION };
	CButton	m_ctrlCancel;
	CButton	m_ctrlTime;
	CButton	m_ctrlOK;
	CListCtrl	m_listview;
	BOOL	m_ShowDuration;
	CStatic m_ctrlHeadlineSelect;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgRSAEncryption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	int m_lastSelectedRow;
	int sortBy;
	unsigned nKeylistType;

//	CString UserKeyId; //Roger???

	void InitAsymKeyListBox(unsigned nLocalKeylistType);
	void UpdateRowSel(int row);
	int GetSpecifRow(UINT mask);

	CSortAsymKeyList sortedAsymKeyList;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRSAEncryption)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_RSAENC_H__9BB28A41_A60A_11D2_8881_00C04F795E28__INCLUDED_
