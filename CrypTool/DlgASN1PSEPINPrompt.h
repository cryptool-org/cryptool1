#if !defined(AFX_DLGASN1PSEPINPROMPT_H__106FAD25_B8E7_11D6_A87F_00025532117A__INCLUDED_)
#define AFX_DLGASN1PSEPINPROMPT_H__106FAD25_B8E7_11D6_A87F_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgASN1PSEPINPrompt.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgASN1PSEPINPrompt 

class CDlgASN1PSEPINPrompt : public CDialog
{
// Konstruktion
public:
	CDlgASN1PSEPINPrompt(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgASN1PSEPINPrompt)
	enum { IDD = IDD_ASN1_PSE_PIN_PROMPT };
	CString	m_PIN;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgASN1PSEPINPrompt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgASN1PSEPINPrompt)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGASN1PSEPINPROMPT_H__106FAD25_B8E7_11D6_A87F_00025532117A__INCLUDED_
