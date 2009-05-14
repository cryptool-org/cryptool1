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
#include "IntegerArithmetic.h"
#include "afxcmn.h"
#include "SecretSharingLog.h"


// CDlgSecretSharingSetup-Dialogfeld

class CDlgSecretSharingSetup : public CDialog
{
public:
	CString m_secret;
	CString m_threshold;
	CString m_polynom;
	CString m_participants;
	CString m_values;
	CString m_modulus;
	BOOL m_show_intro;

	CString primeLimit;
	CString partyLimit;
	GeneratePrimes P;

	CDlgSecretSharingSetup(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgSecretSharingSetup();
	void GeneratePoly(long *co);
	Big CalculateShare(long *co, long par);
	bool CheckEdit(CString &m_edit,int & sels, int & sele);
	void RevealSecret(int sel);
	void ReduceFrac(int pos);

// Dialogfelddaten
	//{{AFX_DATA(CDlgSecretSharingSetup)
	enum { IDD = IDD_SECRETSHARING_SETUP };
	CButton m_ctrl_ButtonPolynom;
	CButton m_ctrl_ButtonUpdate;
	CListCtrl m_list_shares;
	CEdit m_ctrl_secret;
	CEdit m_ctrl_threshold;
	CButton m_ctrl_ButtonOK;
	CEdit m_ctrl_participants;
	CButton m_ctrl_ButtonOptions;
	CButton m_ctrl_ButtonParameter;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSecretSharingSetup)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSecretSharingSetup)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGenerate();
	afx_msg void OnButtonUpdate();
	afx_msg void OnButtonOk();
	afx_msg void OnUpdateEditThreshold();
	afx_msg void OnUpdateEditSecret();
	afx_msg void OnUpdateEditParticipants();
	afx_msg void OnButtonOpt();
	afx_msg void OnButtonChange();
	afx_msg void OnButtonClickedCheckShowintro();
	afx_msg void OnButtonExample();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int g, n, t, s;
	int maxParties;
	long maxPrime;
	long *coeff;
	long *parameter;
	Big *shares, *numerator, *denominator, result;	
	bool *isSelected;
	bool primeFlag, coeffFlag;

	SecretSharingLog *logFile;	
public:
	afx_msg void OnNMClickListShares(NMHDR *pNMHDR, LRESULT *pResult);
};

