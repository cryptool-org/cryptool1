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

#if !defined(AFX_DLGAUTOSUBSTITUTIONANALYSIS_H__A13B5A0D_B962_45C6_8D5D_375F1E86BAC7__INCLUDED_)
#define AFX_DLGAUTOSUBSTITUTIONANALYSIS_H__A13B5A0D_B962_45C6_8D5D_375F1E86BAC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAutoSubstitutionAnalysis.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAutoSubstitutionAnalysis 

class CDlgAutoSubstitutionAnalysis : public CDialog
{
// Konstruktion
public:
	CDlgAutoSubstitutionAnalysis(CWnd* pParent = NULL);   // Standardkonstruktor

	void CDlgAutoSubstitutionAnalysis::setText(char *text);
	CString CDlgAutoSubstitutionAnalysis::getText();
	void CDlgAutoSubstitutionAnalysis::setLanguageInfo(char *text);
	void CDlgAutoSubstitutionAnalysis::setKey(char *text);
	CString CDlgAutoSubstitutionAnalysis::getKey();
	void CDlgAutoSubstitutionAnalysis::setCharacterNumber(char *text);
	void CDlgAutoSubstitutionAnalysis::setSpaceInAlphabet(bool value);

	void CDlgAutoSubstitutionAnalysis::setThreadFinished(bool value);
	bool CDlgAutoSubstitutionAnalysis::getThreadFinished();
	void CDlgAutoSubstitutionAnalysis::setGuiFinished(bool value);
	bool CDlgAutoSubstitutionAnalysis::getGuiFinished();
	void CDlgAutoSubstitutionAnalysis::setThreadFailed(bool value);
	bool CDlgAutoSubstitutionAnalysis::getThreadFailed();
	bool CDlgAutoSubstitutionAnalysis::getManualAnalysis();


// Dialogfelddaten
	//{{AFX_DATA(CDlgAutoSubstitutionAnalysis)
	enum { IDD = IDD_AUTO_SUBSTITUTION_ANALYSIS };
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgAutoSubstitutionAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CCriticalSection	sync;

	bool	m_threadFinished;
	bool	m_threadFailed;
	bool	m_guiFinished;
	bool	m_changed;
	bool	m_manual_analysis;
	bool	m_space_in_alphabet;

	int		m_timerDisplay;
	CString	m_language_info;
	CString	m_key;
	CString	m_text;
	CString	m_ref_file;
	CString	m_character_number;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgAutoSubstitutionAnalysis)
	afx_msg void OnSUBSTCancel();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyCopy();
	afx_msg void OnManualAnalysis();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGAUTOSUBSTITUTIONANALYSIS_H__A13B5A0D_B962_45C6_8D5D_375F1E86BAC7__INCLUDED_
