#if !defined(AFX_DLGRANDPARAMICG_H__9267A190_7C16_11D5_A850_00025532117A__INCLUDED_)
#define AFX_DLGRANDPARAMICG_H__9267A190_7C16_11D5_A850_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRandParamICG.h : Header-Datei
//

#include "KeyEdit.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgRandParamICG 

class DlgRandParamICG : public CDialog
{
// Konstruktion
public:
	DlgRandParamICG(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(DlgRandParamICG)
	enum { IDD = IDD_RANDOM_PARAMETER_ICG };
	CStatic	m_StaticGPA;
	CKeyEdit	m_PrimLang_Ctrl;
	CKeyEdit	m_Param_NCtrl;
	CKeyEdit	m_Param_bCtrl;
	CKeyEdit	m_Param_aCtrl;
	CString	m_Param_a;
	CString	m_Param_b;
	CString	m_Param_N;
	UINT	m_PrimLang;
	//}}AFX_DATA

	void Set( CString a, CString b, CString N )
	{ m_Param_a = a; m_Param_b = b; m_Param_N = N; }
	void SetPrimLang ( UINT Laenge ) { m_PrimLang = Laenge; }
	CString Get_a() { return m_Param_a; }
	CString Get_b() { return m_Param_b; }
	CString Get_N() { return m_Param_N; }

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(DlgRandParamICG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(DlgRandParamICG)
	afx_msg void OnStaticGp_a();
	afx_msg void OnPrimbutton();
	afx_msg void OnStaticGpc();
	afx_msg void OnStaticGpp();
	afx_msg void OnStaticGpl();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRANDPARAMICG_H__9267A190_7C16_11D5_A850_00025532117A__INCLUDED_
