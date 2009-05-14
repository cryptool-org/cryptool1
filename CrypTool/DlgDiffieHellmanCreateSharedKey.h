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

#if !defined(AFX_DLGDIFFIEHELLMANCREATESHAREDKEY_H__33449F32_E641_11D6_A898_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANCREATESHAREDKEY_H__33449F32_E641_11D6_A898_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanCreateSharedKey.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanCreateSharedKey 

class CDlgDiffieHellmanCreateSharedKey : public CDialog
{
// Konstruktion
public:
	CDlgDiffieHellmanCreateSharedKey(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanCreateSharedKey)
	enum { IDD = IDD_DIFFIEHELLMAN_CREATESHAREDKEY };
	CStatic	m_HeadingControl;
	CString	m_HeadingText;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanCreateSharedKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanCreateSharedKey)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANCREATESHAREDKEY_H__33449F32_E641_11D6_A898_00025532117A__INCLUDED_
