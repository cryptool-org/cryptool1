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

#ifndef AFX_SCHLUESSELAUSGABELINEAR_H__5AA7B9F0_DACD_11D3_8791_00C04F795E36__INCLUDED_
#define AFX_SCHLUESSELAUSGABELINEAR_H__5AA7B9F0_DACD_11D3_8791_00C04F795E36__INCLUDED_

// SchluesselAusgabeLinear.h : Header-Datei
//


#include "KeyRepository.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKey 

class CDlgShowKey : public CDialog
{
// Konstruktion
public:
	CString Key;
	char strTitle[KEYDATA_HASHSTRING_LENGTH+1];
//	void SetAlternativeWindowText(LPCTSTR s_title);
	CDlgShowKey(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgShowKey)
	enum { IDD = IDD_SHOW_KEY };
	CEdit	m_CtrlKey;
	CString	m_Key;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgShowKey)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

private:
//    char s_alternativeWindowText[127];

protected:
	CFont m_font; // font for key display
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowKey)
	afx_msg void OnCopyKey();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_SCHLUESSELAUSGABELINEAR_H__5AA7B9F0_DACD_11D3_8791_00C04F795E36__INCLUDED_
