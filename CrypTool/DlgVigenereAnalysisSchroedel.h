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

#ifndef _DLGVIGENEREANALYSISSCHROEDEL_
#define _DLGVIGENEREANALYSISSCHROEDEL_

#if _MSC_VER > 1000
#pragma once
#endif

// CDlgVigenereAnalysisSchroedel dialog

class CDlgVigenereAnalysisSchroedel : public CDialog
{
	DECLARE_DYNAMIC(CDlgVigenereAnalysisSchroedel)

public:
	CDlgVigenereAnalysisSchroedel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgVigenereAnalysisSchroedel();

// Dialog Data
	enum { IDD = IDD_VIGENERE_ANALYSIS_SCHROEDEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

#endif