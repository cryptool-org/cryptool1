#if !defined(AFX_RSA_KLEIN_H__573CD3B1_3338_11D5_88C9_00062919F268__INCLUDED_)
#define AFX_RSA_KLEIN_H__573CD3B1_3338_11D5_88C9_00062919F268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSA_KLEIN.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld RSA_KLEIN 

class RSA_KLEIN : public CDialog
{
// Konstruktion
public:
	RSA_KLEIN(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(RSA_KLEIN)
	enum { IDD = IDD_DIALOG_RSA_KLEIN };
	CString	m_eingabe_p;
	CString	m_eingabe_q;
	CString	m_oeffentliche_parameter_pq;
	CString	m_geheime_parameter;
	CString	m_oeffentliche_schluessel_e;
	CString	m_oeffentliche_schluessel_d;
	CString	m_edit7;
	CString	m_edit8;
	CString	m_edit9;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(RSA_KLEIN)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(RSA_KLEIN)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_RSA_KLEIN_H__573CD3B1_3338_11D5_88C9_00062919F268__INCLUDED_
