#if !defined(AFX_DLGRANDOMPARAMETERLCG_H__B38FEE81_37E8_11D5_92F9_00B0D0161C45__INCLUDED_)
#define AFX_DLGRANDOMPARAMETERLCG_H__B38FEE81_37E8_11D5_92F9_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRandomParameterLCG.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgRandomParameterLCG 

class DlgRandomParameterLCG : public CDialog
{
// Konstruktion
public:
	DlgRandomParameterLCG(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(DlgRandomParameterLCG)
	enum { IDD = IDD_RANDOM_PARAMETER_LCG };
	long	m_LinParam_a;
	long	m_LinParam_b;
	long	m_Modul_N;
	//}}AFX_DATA

	void Set( long a, long b, long N )
	{ m_LinParam_a = a; m_LinParam_b = b; m_Modul_N = N; }
	long Get_a() { return m_LinParam_a; }
	long Get_b() { return m_LinParam_b; }
	long Get_N() { return m_Modul_N; }

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(DlgRandomParameterLCG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(DlgRandomParameterLCG)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRANDOMPARAMETERLCG_H__B38FEE81_37E8_11D5_92F9_00B0D0161C45__INCLUDED_
