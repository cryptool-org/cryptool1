#if !defined(AFX_DLGOPTIONSSTARTOPTIONS_H__D396F181_AB59_11D6_9DC9_000629718A52__INCLUDED_)
#define AFX_DLGOPTIONSSTARTOPTIONS_H__D396F181_AB59_11D6_9DC9_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsStartoptions.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsStartoptions 

class CDlgOptionsStartoptions : public CDialog
{
// Konstruktion
public:
	CDlgOptionsStartoptions(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgOptionsStartoptions)
	enum { IDD = IDD_STARTOPTIONS };
	BOOL	m_how_to_start;
	BOOL	m_sample_text_file;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgOptionsStartoptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgOptionsStartoptions)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGOPTIONSSTARTOPTIONS_H__D396F181_AB59_11D6_9DC9_000629718A52__INCLUDED_
