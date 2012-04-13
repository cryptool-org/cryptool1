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
#ifndef AFX_OPTIONSDIALOG_H__CF6277BD_7D2F_11D2_887F_00C04F795E28__INCLUDED_
#define AFX_OPTIONSDIALOG_H__CF6277BD_7D2F_11D2_887F_00C04F795E28__INCLUDED_

// OptionsDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsAnalysis 

class CDlgOptionsAnalysis : public CDialog
{
// Konstruktion
public:
	CDlgOptionsAnalysis(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgOptionsAnalysis)
	enum { IDD = IDD_OPTIONS_ANALYSIS };
	BOOL	m_CKey;
	BOOL	m_CKorr;
	BOOL	m_CHist;
	BOOL	m_VKey;
	BOOL	m_VLen;
	BOOL	m_VKorr;
	BOOL	m_VBase;
	long	m_BFEntropyWindow;
	BOOL  m_VigenereAnalysisSchroedelExtensiveLogging;
	CString m_VigenereAnalysisSchroedelDictionaryFile;
	CString m_VigenereAnalysisSchroedelDigramsFile;
	CString m_VigenereAnalysisSchroedelTrigramsFile;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgOptionsAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual BOOL OnInitDialog();

	afx_msg void OnOK();

	CEdit controlEditDictionaryFile;
	CEdit controlEditDigramsFile;
	CEdit controlEditTrigramsFile;

	afx_msg void OnButtonSearchDictionaryFile();
	afx_msg void OnButtonSearchDigramsFile();
	afx_msg void OnButtonSearchTrigramsFile();

	afx_msg void OnBnClickedButtonRestoreStandard();

	CString chooseFileThroughDialog(const CString title, const CString defaultFile);

	void readSettingsVigenereAnalysisSchroedel();
	void writeSettingsVigenereAnalysisSchroedel();

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgOptionsAnalysis)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int i_alphabetOptions;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_OPTIONSDIALOG_H__CF6277BD_7D2F_11D2_887F_00C04F795E28__INCLUDED_
