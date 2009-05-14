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
#include "afxwin.h"


// CDlgSecretSharingOptions-Dialogfeld

class CDlgSecretSharingOptions : public CDialog
{

public:
	CString m_limit;
	CString m_prime;

	CDlgSecretSharingOptions(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgSecretSharingOptions();

// Dialogfelddaten
	//{{AFX_DATA(CDlgSecretSharingOptions)
	enum { IDD = IDD_SECRETSHARING_OPTIONS };
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSecretSharingOptions)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSecretSharingOptions)
	afx_msg void OnButtonOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
