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


// CDlgSecretSharingParameter-Dialogfeld

class CDlgSecretSharingParameter : public CDialog
{
public:
	CString m_secret;
	CString m_participants;
	CString m_threshold;
	CString m_myPrime;
	CString m_myCoeff;
	GeneratePrimes P;

	long *setupCoeff;

	CDlgSecretSharingParameter(CWnd* pParent = NULL);   // Standardkonstruktor
	CDlgSecretSharingParameter(CString kPara, CString nPara, CString tPara, CString pPara, long* coeffPara, long limitPara, int limitParties, bool flagPara, CWnd* pParent = NULL);
	virtual ~CDlgSecretSharingParameter();
	void CheckEdit(CString &m_edit,int & sels, int & sele);

// Dialogfelddaten
	//{{AFX_DATA(CDlgSecretSharingSetup)
	enum { IDD = IDD_SECRETSHARING_PARAMETER };
	CButton m_ctrlButtonOK;
	CEdit m_ctrl_myPrime;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSecretSharingParameter)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSecretSharingParameter)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGenerateNew();
	afx_msg void OnButtonClickedOk();
	afx_msg void OnEnUpdateEditMyprime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()		

private:
	int t, oldPrime;
	long limit;
	int parties;
	bool isNew;
public:
	afx_msg void OnUpdateEditMycoeff();
};
