#if !defined(AFX_DLGRSAWITHSMALLPRIMESOPTIONS_H__98A64261_5414_11D5_9319_00B0D0161C45__INCLUDED_)
#define AFX_DLGRSAWITHSMALLPRIMESOPTIONS_H__98A64261_5414_11D5_9319_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRSAwithSmallPrimesOptions.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRSAwithSmallPrimesOptions 

class CDlgRSAwithSmallPrimesOptions : public CDialog
{
// Konstruktion
public:
	CDlgRSAwithSmallPrimesOptions(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgRSAwithSmallPrimesOptions)
	enum { IDD = IDD_RSA_WITH_SMALL_PRIMES_OPTIONS };
	CEdit	m_alphabetControl;
	BOOL	m_alphabetOptionExample;
	CString	m_alphabet;
	int		m_inputOption;
	int		m_numberBasis;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgRSAwithSmallPrimesOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRSAwithSmallPrimesOptions)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRSAWITHSMALLPRIMESOPTIONS_H__98A64261_5414_11D5_9319_00B0D0161C45__INCLUDED_
