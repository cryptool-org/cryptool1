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

#if !defined(AFX_COLOREDLISTCTRL_H__86FEBE8E_F6FA_429F_B740_76F1769C81C6__INCLUDED_)
#define AFX_COLOREDLISTCTRL_H__86FEBE8E_F6FA_429F_B740_76F1769C81C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColoredListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColoredListCtrl window

class CColoredListCtrl : public CListCtrl
{
// Construction
public:
	CColoredListCtrl();

// Attributes
public:
	COLORREF m_colRow1;
	COLORREF m_colRow2;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColoredListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColoredListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColoredListCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);	
	//}}AFX_MSG
	afx_msg void CColoredListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOREDLISTCTRL_H__86FEBE8E_F6FA_429F_B740_76F1769C81C6__INCLUDED_)
