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
#ifndef AFX_DLGSUBSTANA_H__A504DEF7_F0A2_11D2_8D5B_00C04F795E36__INCLUDED_
#define AFX_DLGSUBSTANA_H__A504DEF7_F0A2_11D2_8D5B_00C04F795E36__INCLUDED_

// DlgSubstAna.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsSubstitutionAnalysis 

class CDlgOptionsSubstitutionAnalysis : public CDialog
{
// Konstruktion
public:
	CDlgOptionsSubstitutionAnalysis(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgOptionsSubstitutionAnalysis)
	enum { IDD = IDD_OPTIONS_SUBSTITUTION_ANALYSIS };
		
	CButton m_controlRadioAnalysisAutomatic;
	CButton m_controlRadioAnalysisManual;
	CButton m_controlRadioAnalysisAutomaticGerman;
	CButton m_controlRadioAnalysisAutomaticEnglish;
	CEdit m_controlEditAnalysisAutomaticWordlistGerman;
	CEdit m_controlEditAnalysisAutomaticWordlistEnglish;
	CStatic m_controlStaticAnalysisAutomaticOption1;
	CButton m_controlCheckAnalysisAutomaticOption1;
	CStatic m_controlStaticAnalysisAutomaticOption2;
	CButton m_controlCheckAnalysisAutomaticOption2;
	CButton m_buttonSelectWordlistGerman;
	CButton m_buttonSelectWordlistEnglish;
	CButton m_controlCheckAnalysisManualOption1;

	CString m_editWordlistGerman;
	CString m_editWordlistEnglish;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgOptionsSubstitutionAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgOptionsSubstitutionAnalysis)
	virtual BOOL OnInitDialog();

	afx_msg void OnRadioAnalysisAutomatic();
	afx_msg void OnRadioAnalysisManual();
	afx_msg void OnRadioAnalysisAutomaticGerman();
	afx_msg void OnRadioAnalysisAutomaticEnglish();
	afx_msg void OnButtonSelectWordlistGerman();
	afx_msg void OnButtonSelectWordlistEnglish();
	afx_msg void OnCheckAnalysisAutomaticOption1();
	afx_msg void OnCheckAnalysisAutomaticOption2();
	afx_msg void OnCheckAnalysisManualOption1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	// are we in automatic or manual mode?
	bool analysisModeAutomatic;
	// boolen values for AUTOMATIC options
	bool analysisAutomaticGerman;
	bool analysisAutomaticOption1;
	bool analysisAutomaticOption2;
	// boolean values for MANUAL options
	bool analysisManualOption1;
protected:
	// internal function for GUI updates
	void updateButtons();

public:
	// varios access function
	bool isAnalysisAutomatic() { return analysisModeAutomatic; }
	bool isAnalysisManual() { return !analysisModeAutomatic; }
	bool isAnalysisAutomaticGerman() { return analysisModeAutomatic && analysisAutomaticGerman; }
	bool isAnalysisAutomaticEnglish() { return analysisModeAutomatic && !analysisAutomaticGerman; }
	bool isAnalysisAutomaticOption1() { return analysisModeAutomatic && analysisAutomaticOption1; }
	bool isAnalysisAutomaticOption2() { return analysisModeAutomatic && analysisAutomaticOption2; }
	bool isAnalysisManualOption1() { return !analysisModeAutomatic && analysisManualOption1; }
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSUBSTANA_H__A504DEF7_F0A2_11D2_8D5B_00C04F795E36__INCLUDED_
