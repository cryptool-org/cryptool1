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

#if !defined(AFX_DLGHMAC_H__8CFA9814_3E86_445A_8C71_A60FD455A1CE__INCLUDED_)
#define AFX_DLGHMAC_H__8CFA9814_3E86_445A_8C71_A60FD455A1CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHMAC.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHMAC 

class CDlgHMAC : public CDialog
{
// Konstruktion
	void hash(char *data, int data_len, char *digest, int &len);
	void hash(CString &data, char *digest, int &len);
	CString hex_dump( const char *data, int len );
	void keyEmpty(int IDS);

public:
	void SetMac(CString input);
	void SetOuterHash();
	CString CalculateMac(CString tmpStr);
	CString strText;

	CDlgHMAC(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgHMAC)
	enum { IDD = IDD_HMAC };
	CEdit	m_ctrl_secondkey;
	CEdit	m_ctrl_key;
	CEdit	m_mac;
	CEdit	m_text;
	int		m_alg;
	int		m_position;
	CString	m_key;
	CString	m_secondkey;
	CString	m_str_mac;
	CString m_originalMessage;
	CString m_outerHash;
	//}}AFX_DATA

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgHMAC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgHMAC)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONSecondKey();
	afx_msg void OnEditText();
	afx_msg void OnEditKey();
	afx_msg void OnEditOriginalMessage();
	afx_msg void OnBUTTONFront();
	afx_msg void OnBUTTONBack();
	afx_msg void OnBUTTONBoth();
	afx_msg void OnBUTTONDouble();
	afx_msg void OnEditSecondKey();
	afx_msg void OnBUTTONHashFunction();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// this function is used for the live-update functionality of this dialog; as soon as a dialog 
	// control is ivoked that changes a variable, use this function to both re-calculate the MAC and 
	// update the user interface accordingly
	void calculateMACAndUpdateGUI();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGHMAC_H__8CFA9814_3E86_445A_8C71_A60FD455A1CE__INCLUDED_
