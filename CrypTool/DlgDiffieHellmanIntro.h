#if !defined(AFX_DLGDIFFIEHELLMANINTRO_H__7090642D_02A2_11D7_A8B4_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANINTRO_H__7090642D_02A2_11D7_A8B4_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanIntro.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanIntro 

class CDlgDiffieHellmanIntro : public CDialog
{
// Konstruktion
public:
	CDlgDiffieHellmanIntro(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanIntro)
	enum { IDD = IDD_DIFFIEHELLMAN_INTRO };
	BOOL	m_Check_NoShow;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanIntro)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanIntro)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANINTRO_H__7090642D_02A2_11D7_A8B4_00025532117A__INCLUDED_
