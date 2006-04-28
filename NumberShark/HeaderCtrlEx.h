// HeaderCtrlEx.h : main header file for the HEADERCTRLEX application
//

#if !defined(AFX_HEADERCTRLEX_H__B35F5F4A_C93C_445E_8591_9466397169C5__INCLUDED_)
#define AFX_HEADERCTRLEX_H__B35F5F4A_C93C_445E_8591_9466397169C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExApp:
// See HeaderCtrlEx.cpp for the implementation of this class
//

class CHeaderCtrlExApp : public CWinApp
{
public:
	CHeaderCtrlExApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderCtrlExApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHeaderCtrlExApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEADERCTRLEX_H__B35F5F4A_C93C_445E_8591_9466397169C5__INCLUDED_)
