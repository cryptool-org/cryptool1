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

#if !defined(AFX_DLGCERTTUTORIAL_H__73C6A6D9_05B6_11D6_8A83_000255320F1C__INCLUDED_)
#define AFX_DLGCERTTUTORIAL_H__73C6A6D9_05B6_11D6_8A83_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCertTutorial.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCertificateGeneration 

#include "PSEDemo.h"

class CDlgCertificateGeneration : public CDialog
{
// Konstruktion
	void OnChangeCertData();

public:
	CDlgCertificateGeneration(CWnd* pParent = NULL);   // Standardkonstruktor
	BOOL m_PSEIsExtern;

	void InitRSA(CPSEDemo* Cert);
protected:
	CPSEDemo* m_Cert;
private:
	time_t m_lTime;

// Dialogfelddaten
	//{{AFX_DATA(CDlgCertificateGeneration)
	enum { IDD = IDD_CERTIFICATE_GENERATION };
	CEdit	m_CtrlPINv;
	CEdit	m_CtrlPIN;
	CEdit	m_CtrlFirstName;
	CEdit	m_CtrlName;
	CEdit	m_CtrlKeyID;
	CButton	m_CtrlOK;
	CString	m_sDName;
	CString	m_sFirstName;
	CString	m_sKeyID;
	CString	m_sName;
	CString	m_sUserID;
	CString	m_sBitLength;
	CString	m_sPIN;
	CString	m_sPINv;
	CString	m_sKeyPublic;
	CString	m_sModN;
	//}}AFX_DATA
	

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgCertificateGeneration)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgCertificateGeneration)
	virtual BOOL OnInitDialog();
	afx_msg void OnPseImport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChangeEdit();
	virtual void OnOK();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGCERTTUTORIAL_H__73C6A6D9_05B6_11D6_8A83_000255320F1C__INCLUDED_
