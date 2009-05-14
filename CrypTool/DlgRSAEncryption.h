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
