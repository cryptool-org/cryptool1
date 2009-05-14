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

#ifndef _DLGPASSWORDQUALITYMETER_
#define _DLGPASSWORDQUALITYMETER_


// CDlgPasswordQualityMeter-Dialogfeld

#include "PictureEx.h"
#include "afxwin.h"

class CDlgPasswordQualityMeter : public CDialog
{
public:
	CDlgPasswordQualityMeter(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgPasswordQualityMeter();

// Dialogfelddaten
	enum { IDD = IDD_PASSWORDQUALITYMETER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	virtual void EditPasswordChanged();
	virtual void UpdateUserInterface();

	DECLARE_MESSAGE_MAP()

private:
	CPictureEx controlPictureQuality;

private:
	CString password;
	BOOL showPassword;
	
	unsigned int intQualityKeePass;
	unsigned int intQualityMozilla;
	unsigned int intQualityPGP;
	unsigned int intQualityCrypTool;
	
	CString stringQualityKeePass;
	CString stringQualityMozilla;
	CString stringQualityPGP;
	CString stringQualityCrypTool;

	CProgressCtrl controlQualityKeePass;
	CProgressCtrl controlQualityMozilla;
	CProgressCtrl controlQualityPGP;
	CProgressCtrl controlQualityCrypTool;

	CString passwordResistance;
	BOOL displayedDictionaryNotFoundMessage;

public:
	afx_msg void OnBnClickedCheckShowpassword();
	afx_msg void OnBnClickedConfigurePasswordGuidelines();
	CEdit passwordEditCtrl;
	CEdit passwordLengthEditCtrl;
	int passwordLength;

	// this initializes the dialog with a password
	void setPassword(const CString &_password);
};

#endif