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
