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

#if !defined(AFX_DLGKEYPERMUTATIONINFO_H__2EDC8EC3_A835_11D6_9DC4_000629718A52__INCLUDED_)
#define AFX_DLGKEYPERMUTATIONINFO_H__2EDC8EC3_A835_11D6_9DC4_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKeyPermutationInfo.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyPermutationInfo 

class CDlgKeyPermutationInfo : public CDialog
{
// Konstruktion
public:
	CString m_dialogue_title;
	CString m_button_title;
	CDlgKeyPermutationInfo(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyPermutationInfo)
	enum { IDD = IDD_KEY_PERMUTATION_INFO };
	CButton	m_button_control;
	CString	m_Inverse1;
	CString	m_Permutation1;
	CString	m_Permutation2;
	CString	m_Inverse2;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyPermutationInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyPermutationInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBack();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGKEYPERMUTATIONINFO_H__2EDC8EC3_A835_11D6_9DC4_000629718A52__INCLUDED_
