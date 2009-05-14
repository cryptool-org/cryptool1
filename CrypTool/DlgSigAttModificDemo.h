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

#if !defined(AFX_DLGSIGATTMODIFICDEMO_H__ABE40D51_3900_11D7_9E4E_000629718A52__INCLUDED_)
#define AFX_DLGSIGATTMODIFICDEMO_H__ABE40D51_3900_11D7_9E4E_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSigAttModificDemo.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSigAttModificDemo 

class CDlgSigAttModificDemo : public CDialog
{
// Konstruktion
public:
	void SetData(char *Path, const CString &Title);
	CDlgSigAttModificDemo(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSigAttModificDemo)
	enum { IDD = IDD_SIGATTMODIFICDEMO };
	CComboBox	m_control_run;
	CButton	m_control_method;
	CButton	m_control_unprintable;
	CButton	m_control_printable;
	CButton	m_control_double;
	CButton	m_control_eol;
	CEdit	m_control_hashvalue;
	CString	m_hashvalue;
	int		m_sigbit;
	int		m_method;
	int		m_printable;
	int		m_parity;
	CString	m_run;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSigAttModificDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSigAttModificDemo)
	afx_msg void OnModify();
	afx_msg void OnAttachment();
	afx_msg void OnMethod();
	afx_msg void OnPrintable();
	afx_msg void OnUnprintable();
	afx_msg void OnUpdateHashvalue();
	afx_msg void OnUpdateSigbit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CalculateParity();
	int HexCharToInt(const char C) const;

	CString m_Path;
	CString m_Title;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSIGATTMODIFICDEMO_H__ABE40D51_3900_11D7_9E4E_000629718A52__INCLUDED_
