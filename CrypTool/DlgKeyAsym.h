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
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security

#ifndef AFX_DlgAsymKeys_H__F1360881_35D6_11D3_8D69_00C04F795E36__INCLUDED_
#define AFX_DlgAsymKeys_H__F1360881_35D6_11D3_8D69_00C04F795E36__INCLUDED_

// DlgAsymKeys.h : Header-Datei
//

#include "KeyFileHandling.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyAsym 

class CDlgKeyAsym : public CDialog
{
// Konstruktion
public:
	bool AreThereRSAKeys();
	CDlgKeyAsym(CWnd* pParent = NULL);   // Standardkonstruktor
	//~CDlgKeyAsym(); // Destruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyAsym)
	enum { IDD = IDD_KEY_ASYM };
	CButton	m_RemoveItem;
	CButton	m_CheckEC;
	CButton	m_CheckDSA;
	CButton	m_CheckRSA;
	CButton	m_show_cert_button;
	CButton	m_export_cert_button;
	CListCtrl	m_listview;
	CButton	m_secret_param_button;
	CButton	m_pub_param_button;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyAsym)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementierung
protected:

	int m_lastSelectedRow;
	int sortBy;
	unsigned nKeylistType;

	// diese Strings werden in CDlgKeyAsym::OnClickList3() mit Werten belegt
	CString Name;
	CString Firstname;
	CString KeyType;
	CString KeyInfo;
	CString CreatTimeUTC; 
	CString CreatTime;

	CString UserKeyId;

	void InitAsymKeyListBox(unsigned nLocalKeylistType);
	void UpdateRowSel(int row);
	int GetSpecifRow(UINT mask);
	int FindRow( CString pattern);

	CSortAsymKeyList sortedAsymKeyList;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyAsym)
	afx_msg void OnShowPubParamButton();
	afx_msg void OnShowAllParamButton();
	afx_msg void OnDeleteEntryButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonShowCert();
	afx_msg void OnButtonExportCert();
	afx_msg void OnColumnclickList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckRsaKey();
	afx_msg void OnCheckDsaKey();
	afx_msg void OnCheckEcKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DlgAsymKeys_H__F1360881_35D6_11D3_8D69_00C04F795E36__INCLUDED_
