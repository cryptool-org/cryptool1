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


// DlgAdfgvxIntro-Dialogfeld

class DlgAdfgvxIntro : public CDialog
{
	DECLARE_DYNAMIC(DlgAdfgvxIntro)

public:
	DlgAdfgvxIntro(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~DlgAdfgvxIntro();

// Dialogfelddaten
	enum { IDD = IDD_ADFGVX_INTRO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung

	DECLARE_MESSAGE_MAP()
private:
	BOOL noIntro;
public:
	afx_msg void OnBnClickedCheck1();
};
