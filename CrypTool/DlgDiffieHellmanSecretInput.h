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

#if !defined(AFX_DLGDIFFIEHELLMANSECRETINPUT_H__5F417B9F_EFB8_11D6_A8A3_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANSECRETINPUT_H__5F417B9F_EFB8_11D6_A8A3_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanSecretInput.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanSecretInput 

class CDlgDiffieHellmanSecretInput : public CDialog
{
private:
	Big m_Prime;
	std::string m_Party;
	bool m_SecretExceedsPrime;

// Konstruktion
public:
	CDlgDiffieHellmanSecretInput(CWnd* pParent = NULL);			// Standardkonstruktor
	CDlgDiffieHellmanSecretInput(std::string,Big&,CWnd* pParent = NULL);				// Zusätzlicher Konstruktor
	CDlgDiffieHellmanSecretInput(std::string,std::string,Big&,CWnd* pParent = NULL);	// Zusätzlicher Konstruktor
	bool SecretExceedsPrime() { return m_SecretExceedsPrime; }
// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanSecretInput)
	enum { IDD = IDD_DIFFIEHELLMAN_SECRETINPUT };
	CButton	m_CtrlOKButton;
	CButton	m_ButtonGenSec;
	CEdit	m_SecretControl;
	CString	m_Secret;
	CString	m_PartyHeader;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanSecretInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanSecretInput)
	virtual void OnOK();
	afx_msg void OnGenerateSecret();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANSECRETINPUT_H__5F417B9F_EFB8_11D6_A8A3_00025532117A__INCLUDED_
