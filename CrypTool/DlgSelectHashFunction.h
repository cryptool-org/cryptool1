#if !defined(AFX_SELCTAHASHFUNCTION_H__F4D10A11_197E_11D6_9392_00B0D0161C45__INCLUDED_)
#define AFX_SELCTAHASHFUNCTION_H__F4D10A11_197E_11D6_9392_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelctAHashfunction.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelectHashFunction 

class CDlgSelectHashFunction : public CDialog
{
// Konstruktion
public:
	CDlgSelectHashFunction(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSelectHashFunction)
	enum { IDD = IDD_SELECT_HASHFUNCTION };
	int		m_selectedHashFunction;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgSelectHashFunction)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSelectHashFunction)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_SELCTAHASHFUNCTION_H__F4D10A11_197E_11D6_9392_00B0D0161C45__INCLUDED_
