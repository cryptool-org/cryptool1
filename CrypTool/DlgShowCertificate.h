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
// Programmiert von Bartol Filipovic, 2000

#ifndef AFX_DIALOGCERT_H__B1DF5657_F6FB_11D2_888E_00C04F795E28__INCLUDED_
#define AFX_DIALOGCERT_H__B1DF5657_F6FB_11D2_888E_00C04F795E28__INCLUDED_

// DialogCert.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowCertificate 

class CDlgShowCertificate : public CDialog
{
// Konstruktion
public:
	CDlgShowCertificate(CWnd* pParent = NULL);   // Standardkonstruktor
	CDlgShowCertificate(CString CertIn, CWnd* pParent = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CDlgShowCertificate)
	enum { IDD = IDD_SHOW_CERTIFICATE };
	CEdit	m_dummyCtrl;
	CEdit	m_CertEditCtrl;
	CString	m_CertEdit;
	CString	m_dummy;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgShowCertificate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CString Cert;
	CFont m_Font;
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowCertificate)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOGCERT_H__B1DF5657_F6FB_11D2_888E_00C04F795E28__INCLUDED_
