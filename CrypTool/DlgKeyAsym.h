/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

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

public:
	void setKeyID(CString &userKeyId) { UserKeyId = userKeyId; }

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DlgAsymKeys_H__F1360881_35D6_11D3_8D69_00C04F795E36__INCLUDED_
