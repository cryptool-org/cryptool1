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


// DlgAdfgvxStringBox-Dialogfeld

class DlgAdfgvxStringBox : public CDialog
{
	DECLARE_DYNAMIC(DlgAdfgvxStringBox)

public:
	DlgAdfgvxStringBox(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~DlgAdfgvxStringBox();

// Dialogfelddaten
	enum { IDD = IDD_ADFGVX_STRINGBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CString GetInput();
	afx_msg void OnBnClickedOk();
	afx_msg void OnOk();

private:
	CString input;
	void DlgAdfgvxStringBox::OnOK();
	BOOL DlgAdfgvxStringBox::OnInitDialog();
};
