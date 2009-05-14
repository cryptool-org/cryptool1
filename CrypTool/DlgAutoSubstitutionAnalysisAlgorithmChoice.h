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

#if !defined(AFX_DLGAUTOSUBSTITUTIONANALYSISALGORITHMCHOICE_H__E3313072_2465_4FED_9212_C6BD31E26227__INCLUDED_)
#define AFX_DLGAUTOSUBSTITUTIONANALYSISALGORITHMCHOICE_H__E3313072_2465_4FED_9212_C6BD31E26227__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAutoSubstitutionAnalysisAlgorithmChoice.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAutoSubstitutionAnalysisAlgorithmChoice 

class CDlgAutoSubstitutionAnalysisAlgorithmChoice : public CDialog
{
// Konstruktion
public:
	CDlgAutoSubstitutionAnalysisAlgorithmChoice(CWnd* pParent = NULL);   // Standardkonstruktor

	int m_algChoice;

// Dialogfelddaten
	//{{AFX_DATA(CDlgAutoSubstitutionAnalysisAlgorithmChoice)
	enum { IDD = IDD_AUTO_SUBSTITUTION_ANALYSIS_ALGORITHM_CHOICE };
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgAutoSubstitutionAnalysisAlgorithmChoice)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgAutoSubstitutionAnalysisAlgorithmChoice)
	afx_msg void OnAlgDigram();
	afx_msg void OnAlgWord();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGAUTOSUBSTITUTIONANALYSISALGORITHMCHOICE_H__E3313072_2465_4FED_9212_C6BD31E26227__INCLUDED_
