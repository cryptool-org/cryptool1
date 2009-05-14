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

#if !defined(AFX_DLGKEYTUTORIAL_H__73C6A6D7_05B6_11D6_8A83_000255320F1C__INCLUDED_)
#define AFX_DLGKEYTUTORIAL_H__73C6A6D7_05B6_11D6_8A83_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKeyTutorial.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDemoRSAKeyGeneration 

#include "PSEDemo.h"

class CDlgDemoRSAKeyGeneration : public CDialog
{
// Konstruktion
public:
	CDlgDemoRSAKeyGeneration(CWnd* pParent = NULL);   // Standardkonstruktor

	void InitRSA(CPSEDemo* Cert);

protected:
	//CBitmap m_bmpCheck;
	//CBitmap m_bmpNoCheck;
	CBitmapButton m_ButtonInfo;

private:
	CPSEDemo* m_Cert; // Zertifikat
	CString m_sPrime_p_OLD;
	CString m_sPrime_q_OLD;
	CString m_sKeyPublic_OLD;

// Dialogfelddaten
	//{{AFX_DATA(CDlgDemoRSAKeyGeneration)
	enum { IDD = IDD_DEMO_RSAKEY_GENERATION };
	CStatic	m_BitLengthCtrl;
	CStatic	m_CheckPrimeCtrl;
	CStatic	m_CheckPublicCtrl;
	CEdit	m_KeyPublicCtrl;
	CButton	m_ButtonOKCtrl;
	CString	m_sPrime_p;
	CString	m_sPrime_q;
	CString	m_sKeyPublic;
	CString	m_sKeyPrivate;
	CString	m_sModN;
	CString	m_sPhiN;
	CString	m_sCheckPrime;
	CString	m_sCheckPublic;
	CString	m_sBitLength;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDemoRSAKeyGeneration)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDemoRSAKeyGeneration)
	virtual BOOL OnInitDialog();
	afx_msg void OnGeneratePrime();
	afx_msg void OnUpdateParameter();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGKEYTUTORIAL_H__73C6A6D7_05B6_11D6_8A83_000255320F1C__INCLUDED_
