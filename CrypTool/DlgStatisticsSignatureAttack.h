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

#if !defined(AFX_DLGSTATISTICSSIGNATUREATTACK_H__51A32281_D11F_11D6_9DED_000629718A52__INCLUDED_)
#define AFX_DLGSTATISTICSSIGNATUREATTACK_H__51A32281_D11F_11D6_9DED_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStatisticsSignatureAttack.h : Header-Datei
//
#include "ResultsOfSignatureAttack.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgStatisticsSignatureAttack 

class CDlgStatisticsSignatureAttack : public CDialog
{
// Konstruktion
public:
	bool GetPrintStatistics() const;
	void PrintStatistics();
	void SetData(ResultsOfSignatureAttack *ResSigAtt,
	const int ModifiedBytesHarmless, const int ModifiedBytesDangerous);
	CDlgStatisticsSignatureAttack(CWnd* pParent = NULL);   // Standardkonstruktor
	/*CDlgStatisticsSignatureAttack(CWnd* pParent = NULL, ResultsOfSignatureAttack *ResSigAtt = NULL);*/

// Dialogfelddaten
	//{{AFX_DATA(CDlgStatisticsSignatureAttack)
	enum { IDD = IDD_STATISTICS_SIGNATURE_ATTACK };
	CStatic	m_control_dangerous;
	CStatic	m_control_harmless;
	CListCtrl	m_control_ListOfRuns;
	CString	m_ExpectedSteps;
	CString	m_ExpectedTime;
	CString	m_TotalSteps;
	CString	m_EffectiveTime;
	CString	m_HashOperationsPerformed;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgStatisticsSignatureAttack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgStatisticsSignatureAttack)
	virtual BOOL OnInitDialog();
	afx_msg void OnPrintStatistics();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_PrintStatistics;
	ResultsOfSignatureAttack *m_ResSigAtt;
	int m_ModifiedBytesHarmless;
	int m_ModifiedBytesDangerous;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSTATISTICSSIGNATUREATTACK_H__51A32281_D11F_11D6_9DED_000629718A52__INCLUDED_
