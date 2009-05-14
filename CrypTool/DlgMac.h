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

#pragma once
#include "stdafx.h"
#include <string>
#include "afxwin.h"

// CDlgMac-Dialogfeld

class CDlgMac : public CDialog
{
public:
	CDlgMac(CWnd* pParent = NULL);
	//virtual ~CDlgMac();

	CString strText;

    void String2Octets(OctetString *osTarget,const char* Source, const int Length);
	void SetMac(CString input);
	CString CalculateMac(CString tmpStr);
	CString CDlgMac::MacToHex(OctetString *hash);

// Dialogfelddaten
	//{{AFX_DATA(CDlgMac)
		enum { IDD = IDD_MAC };
		int m_alg;
		int m_position;
		CEdit m_text;	
		CEdit m_mac;
		CEdit m_ctrl_key;
		CString m_key;
		CString m_str_mac;
		CString m_secondkey;
		CEdit m_ctrl_secondkey;
		CButton m_create_mac;	
		CFont m_font;
	//}}AFX_DATA

protected:
	// DDX/DDV-Unterstützung
	virtual void DoDataExchange(CDataExchange* pDX);

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgMac)
		virtual BOOL OnInitDialog();
		afx_msg void OnBUTTONSecondKey();
		afx_msg void OnEditText();
		afx_msg void OnEditKey();
		afx_msg void OnBUTTONFront();
		afx_msg void OnBUTTONBack();
		afx_msg void OnBUTTONBoth();
		afx_msg void OnBUTTONDouble();
		afx_msg void OnEditSecondKey();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBUTTONHashFunction();
};
