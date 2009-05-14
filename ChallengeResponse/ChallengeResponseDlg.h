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

// ChallengeResponseDlg.h : header file
//

#if !defined(AFX_CHALLENGERESPONSEDLG_H__FEB697A7_667E_11D6_9FD1_BDBD5AAECF56__INCLUDED_)
#define AFX_CHALLENGERESPONSEDLG_H__FEB697A7_667E_11D6_9FD1_BDBD5AAECF56__INCLUDED_

#include "Computer.h"	// Added by ClassView
#include "Wire.h"	// Added by ClassView
#include "Scenario.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CChallengeResponseDlg dialog

class CChallengeResponseDlg : public CDialog
{
// Construction
	
public:
	CString helpKey;
	CString msg;
	bool authenticateAttacker;
	void checkAttackerCanMask();
	void startProtocol(bool authenticateAttacker);
	void ChangeMode(int mode);	
	CScenario scenario;
	CChallengeResponseDlg(CWnd* pParent = NULL);	// standard constructor

	//Inserted
	HINSTANCE m_hInstance;  //Variable für Anwendungsinstanz
	//Inserted End

// Dialog Data
	//{{AFX_DATA(CChallengeResponseDlg)
	enum { IDD = IDD_CHALLENGERESPONSE_DIALOG };
	CButton	c_attackerMasked;
	CButton	m_authenticateClient;
	CString	m_modeText;
	int		m_mode;
	int		m_action;
	BOOL	m_attackerMasked;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChallengeResponseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChallengeResponseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnExitButton();
	afx_msg void OnModeRadioButtons();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChangeAction();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAuthenticateClientButton();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAuthenticateAttackerButton();
	afx_msg void OnCheckMask();
	afx_msg void OnScenarioHelpButton();
	afx_msg void OnResetButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HCURSOR hCstandard,hCmark;
	void ChangeScenario();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHALLENGERESPONSEDLG_H__FEB697A7_667E_11D6_9FD1_BDBD5AAECF56__INCLUDED_)
