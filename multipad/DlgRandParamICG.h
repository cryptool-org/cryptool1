#if !defined(AFX_DLGRANDPARAMICG_H__9267A190_7C16_11D5_A850_00025532117A__INCLUDED_)
#define AFX_DLGRANDPARAMICG_H__9267A190_7C16_11D5_A850_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRandParamICG.h : Header-Datei
//

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
	CEdit	m_Param_aCtrl;
	long	m_Param_a;
	long	m_Param_b;
	long	m_Param_N;
	//}}AFX_DATA

	void Set( long a, long b, long N )
	{ m_Param_a = a; m_Param_b = b; m_Param_N = N; }
	long Get_a() { return m_Param_a; }
	long Get_b() { return m_Param_b; }
	long Get_N() { return m_Param_N; }

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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRANDPARAMICG_H__9267A190_7C16_11D5_A850_00025532117A__INCLUDED_
