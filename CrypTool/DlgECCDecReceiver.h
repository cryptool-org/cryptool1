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

// ECCDecReceiver.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgECCDecReceiver

#include "KeyFileHandling.h"

class CDlgECCDecReceiver : public CDialog
{
// Konstruktion
public:
	bool disableButtons;
	CDlgECCDecReceiver(CWnd* pParent = NULL);   // Standardkonstruktor

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
	//{{AFX_DATA(CDlgECCDecReceiver)
	enum { IDD = IDD_ECCDECRECEIVER };
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
	//{{AFX_VIRTUAL(CDlgECCDecReceiver)
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
	//{{AFX_MSG(CDlgECCDecReceiver)
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