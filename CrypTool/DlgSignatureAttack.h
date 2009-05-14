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

#if !defined(AFX_DLGSIGNATUREATTACK_H__A1F6ED91_B4D2_11D6_9DD2_000629718A52__INCLUDED_)
#define AFX_DLGSIGNATUREATTACK_H__A1F6ED91_B4D2_11D6_9DD2_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSignatureAttack.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignatureAttack 

class CDlgSignatureAttack : public CDialog
{
// Konstruktion
public:
	
	CDlgSignatureAttack(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSignatureAttack)
	enum { IDD = IDD_SIGNATURE_ATTACK };
	CEdit	m_control_file_harmless;
	CEdit	m_control_file_dangerous;
	CButton	m_control_compute;
	CString	m_file_harmless;
	CString	m_file_dangerous;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSignatureAttack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSignatureAttack)
	afx_msg void OnOptions();
	afx_msg void OnBrowseOriginal();
	afx_msg void OnBrowseFake();
	afx_msg void OnCompute();
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateFileFake();
	afx_msg void OnUpdateFileOriginal();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GenerateMessageText(int Errorcode, UINT MessageBoxStyle = MB_ICONEXCLAMATION);
	void BrowseDocument(CString &);
	void batchAttack();
	bool AreValidPaths();

	/* this function checks whether the values for harmless and dangerous file entered by the user 
	comply with what was defined at compile time; if one of the file names differ, the button for 
	using the default messages (as defined at compile time) is activated */
	void activateOrDeactivateUseDefaultMessagesButton();

public:
	afx_msg void OnBnClickedButtonUsedefaultmessages();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSIGNATUREATTACK_H__A1F6ED91_B4D2_11D6_9DD2_000629718A52__INCLUDED_
