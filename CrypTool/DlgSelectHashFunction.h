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

#if !defined(AFX_SELCTAHASHFUNCTION_H__F4D10A11_197E_11D6_9392_00B0D0161C45__INCLUDED_)
#define AFX_SELCTAHASHFUNCTION_H__F4D10A11_197E_11D6_9392_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelctAHashfunction.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelectHashFunction 

class CDlgSelectHashFunction : public CDialog
{
// Konstruktion
public:
	CDlgSelectHashFunction(CWnd* pParent = NULL);   // Standardkonstruktor

	bool    m_deactivateMD4;
	bool    m_deactivateSHA2;
	int		m_selectedHashFunction;
	CString m_sHashAlg;
// Dialogfelddaten
	//{{AFX_DATA(CDlgSelectHashFunction)
	enum { IDD = IDD_SELECT_HASHFUNCTION };
	CButton	m_selectedHashFunctionMD4Ctrl;
	int		m_selectedHashFunctionMD2;
	int		m_selectedHashFunctionMD4;
	int		m_selectedHashFunctionMD5;
	int		m_selectedHashFunctionSHA;
	int		m_selectedHashFunctionSHA_1;
	int		m_selectedHashFunctionSHA_256;
	int		m_selectedHashFunctionSHA_512;
	int		m_selectedHashFunctionRIPEMD_160;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSelectHashFunction)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSelectHashFunction)
	afx_msg void OnSelectedMD2();
	afx_msg void OnSelectedMD4();
	afx_msg void OnSelectedMD5();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectSHA();
	afx_msg void OnSelectedSHA_1();
	afx_msg void OnSelectedSHA_256();
	afx_msg void OnSelectedSHA_512();
	afx_msg void OnSelectedRIPEMD_160();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SELCTAHASHFUNCTION_H__F4D10A11_197E_11D6_9392_00B0D0161C45__INCLUDED_
