#ifndef AFX_SCHLUESSELAUSGABELINEAR_H__5AA7B9F0_DACD_11D3_8791_00C04F795E36__INCLUDED_
#define AFX_SCHLUESSELAUSGABELINEAR_H__5AA7B9F0_DACD_11D3_8791_00C04F795E36__INCLUDED_

// SchluesselAusgabeLinear.h : Header-Datei
//


#include "KeyRepository.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSchluesselAusgabeLinear 

class CSchluesselAusgabeLinear : public CDialog
{
// Konstruktion
public:
	CString Key;
	char strTitle[KEYDATA_HASHSTRING_LENGTH+1];
//	void SetAlternativeWindowText(LPCTSTR s_title);
	CSchluesselAusgabeLinear(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CSchluesselAusgabeLinear)
	enum { IDD = IDD_DIALOG_SCHLUESSEL_AUSGABE_LINEAR };
	CEdit	m_CtrlKey;
	CString	m_Key;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSchluesselAusgabeLinear)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

private:
//    char s_alternativeWindowText[127];

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSchluesselAusgabeLinear)
	afx_msg void OnCopyKey();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_SCHLUESSELAUSGABELINEAR_H__5AA7B9F0_DACD_11D3_8791_00C04F795E36__INCLUDED_
