#ifndef AFX_SCHLUESSELAUSGABELINEAR_H__5AA7B9F0_DACD_11D3_8791_00C04F795E36__INCLUDED_
#define AFX_SCHLUESSELAUSGABELINEAR_H__5AA7B9F0_DACD_11D3_8791_00C04F795E36__INCLUDED_

// SchluesselAusgabeLinear.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSchluesselAusgabeLinear 

class CSchluesselAusgabeLinear : public CDialog
{
// Konstruktion
public:
	CSchluesselAusgabeLinear(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CSchluesselAusgabeLinear)
	enum { IDD = IDD_DIALOG_SCHLUESSEL_AUSGABE_LINEAR };
	CString	m_Key;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CSchluesselAusgabeLinear)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSchluesselAusgabeLinear)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_SCHLUESSELAUSGABELINEAR_H__5AA7B9F0_DACD_11D3_8791_00C04F795E36__INCLUDED_
