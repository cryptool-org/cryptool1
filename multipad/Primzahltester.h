#if !defined(AFX_PRIMZAHLTESTER_H__E58B0B61_9DAF_11D4_807B_000629C93170__INCLUDED_)
#define AFX_PRIMZAHLTESTER_H__E58B0B61_9DAF_11D4_807B_000629C93170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Primzahltester.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Primzahltester 

class Primzahltester : public CDialog
{
// Konstruktion
public:
	Primzahltester(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Primzahltester)
	enum { IDD = IDD_DIALOG_PRIMZAHLTESTER };
	CString	m_eingabe;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Primzahltester)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Primzahltester)
	afx_msg void OnButtonTesten();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PRIMZAHLTESTER_H__E58B0B61_9DAF_11D4_807B_000629C93170__INCLUDED_
#endif // AFX_PRIMZAHLTESTER_H__E58B0B61_9DAF_11D4_807B_000629C93170__INCLUDED_
#endif // AFX_PRIMZAHLTESTER_H__E58B0B61_9DAF_11D4_807B_000629C93170__INCLUDED_
