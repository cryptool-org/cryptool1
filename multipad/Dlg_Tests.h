#if !defined(AFX_DLG_TESTS_H__2330231D_80B3_11D5_A856_00025532117A__INCLUDED_)
#define AFX_DLG_TESTS_H__2330231D_80B3_11D5_A856_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Tests.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Dlg_Tests_Freq 

class Dlg_Tests_Freq : public CDialog
{
// Konstruktion
public:
	Dlg_Tests_Freq(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Dlg_Tests_Freq)
	enum { IDD = IDD_DIALOG_FREQTEST };
	CStatic	m_Bitmap_Ctrl2;
	CStatic	m_Bitmap_Ctrl;
	CString	m_Ergebnis;
	const char *infile;
	const char *oldTitle;
	//}}AFX_DATA

	void init(const char *, const char *);
	const char * Get_infile() { return infile; }
	const char * Get_oldTitle() { return oldTitle; }
// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Dlg_Tests_Freq)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Dlg_Tests_Freq)
	afx_msg void OnButtonFreqtest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_TESTS_H__2330231D_80B3_11D5_A856_00025532117A__INCLUDED_
