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
#ifndef AFX_PINCODEDIALOG_H__F1360882_35D6_11D3_8D69_00C04F795E36__INCLUDED_
#define AFX_PINCODEDIALOG_H__F1360882_35D6_11D3_8D69_00C04F795E36__INCLUDED_

// PinCodeDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgPINAccess 

class CDlgPINAccess : public CDialog
{
// Konstruktion
public:
	CDlgPINAccess(int modus, CString keyinfo, CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgPINAccess)
	enum { IDD = IDD_PIN_ACCESS };
	CEdit	m_InfoBoxCtrl;
	CEdit	m_ModusInfoBoxCtrl;
	CEdit	m_PinEditControl;
	CString	m_PinCode;
	CString	m_InfoBox;
	CString	m_ModusInfoBox;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgPINAccess)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CString UserKeyId;
	int Modus;
	CFont m_Font;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgPINAccess)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_PINCODEDIALOG_H__F1360882_35D6_11D3_8D69_00C04F795E36__INCLUDED_
