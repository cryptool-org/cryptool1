#ifndef AFX_DLGKOLLISION_H__780E0543_4329_11D3_876A_00C04F795E36__INCLUDED_
#define AFX_DLGKOLLISION_H__780E0543_4329_11D3_876A_00C04F795E36__INCLUDED_

// DlgKollision.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKollision 

class CDlgKollision : public CDialog
{
// Konstruktion
public:
	CDlgKollision(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKollision)
	enum { IDD = IDD_KOLLISION };
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgKollision)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKollision)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGKOLLISION_H__780E0543_4329_11D3_876A_00C04F795E36__INCLUDED_
#endif // AFX_DLGKOLLISION_H__780E0543_4329_11D3_876A_00C04F795E36__INCLUDED_
#endif // AFX_DLGKOLLISION_H__780E0543_4329_11D3_876A_00C04F795E36__INCLUDED_
