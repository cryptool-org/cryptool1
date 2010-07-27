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

#if !defined(AFX_DLG_HOMOPHONE_H__C0728083_FD9D_11D4_80F2_000629C93170__INCLUDED_)
#define AFX_DLG_HOMOPHONE_H__C0728083_FD9D_11D4_80F2_000629C93170__INCLUDED_

#include "HomophoneEncryption.h"	// Hinzugefügt von der Klassenansicht
#include "KeyParameterHomophone.h"	// Hinzugefügt von der Klassenansicht
#include "afxwin.h"
#include "ToolTipButton.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define range		256
#define upper_range 4096


// Dlg_homophone.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHomophone 

class CDlgKeyHomophone : public CDialog
{
// Konstruktion
public:
	int GetSpecificRow(UINT mask);
	int m_lastSelectedRow;
	void UpdateSelectedRow(int newRow);
	BOOL DeactivateDecryptionButton;
	void LoadListBox();
	bool Get_crypt();
	int Display();
	CDlgKeyHomophone(CWnd* pParent = NULL);   // Standardkonstruktor
	CHomophoneEncryption HB;
	CKeyParameterHomophone TA;
	char c_SourceFile[1024];
	CString m_AlphabetBackup;
// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHomophone)
	enum { IDD = IDD_KEY_HOMOPHONE };
	CEdit	m_EditNoOfHomophonesCtrl;
	CEdit	m_NoOfHomophonesCtrl;
	CButton	m_ButtonDecryption;
	CEdit	m_BitlengthCtrl;
	CEdit	m_KeyCtrl;
	CListCtrl	m_listview;
	CEdit       m_dummyCtrl;
	CString	m_KeyCStr;
	int		m_BaseHomophones;
	int     m_InputType;
	int		m_Bitlength;
	int		m_NoOfHomophones;
	int		m_EditNoOfHomophones;
	CString	m_RowHomophonesList;
	CString	m_HomophonesList;
	CButton m_ctrlEncodeUmlauts;
	int		m_encodeUmlauts;
	CButton m_ctrlEncryptFormatCharacters;
	//}}AFX_DATA
	int m_crypt;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHomophone)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CFont m_Font;
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHomophone)
	afx_msg void OnErzeugen();
	virtual BOOL OnInitDialog();
	afx_msg void OnLoadKey();
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	afx_msg void OnHex();
	afx_msg void OnDecimal();
	afx_msg void OnActualizeNoOfHomophones();
	afx_msg void OnSelectList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkSelect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReturnSelect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelectEncryptFormatCharacters();
	afx_msg void OnBnClickedRadioTextInput();
	afx_msg void OnBnClickedRadioBinaryInput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CToolTipButton m_Paste;
	void Init_ListBox();
	BOOL InputTypeIsChanged;
public:
	afx_msg void OnBnClickedButtonTextoptions();
	CButton m_ctrlTextOptions;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_HOMOPHONE_H__C0728083_FD9D_11D4_80F2_000629C93170__INCLUDED_
