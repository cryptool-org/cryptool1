#if !defined(AFX_DLGDETAILSFACTORISATION_H__C7183AE5_1AE6_11D6_ACFC_000255321174__INCLUDED_)
#define AFX_DLGDETAILSFACTORISATION_H__C7183AE5_1AE6_11D6_ACFC_000255321174__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDetailsFactorisation.h : Header-Datei
//


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDetailsFactorisation 

struct DFItem {
	CString Num;
	CString Factor1;
	CString Factor2;
	CString Method;
	CString Time;
	int     PrimeMask;
	struct  DFItem *next;
};


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgDetailsFactorisation 

class DlgDetailsFactorisation : public CDialog
{
// Konstruktion
	struct DFItem *List;
public:
	void ClearFactDetail();
	void InsertFactDetail( CString & Num, CString &Factor1, 
		                   CString &Factor2, CString &Method, CString &Time, int PrimeMask);
	void Init_ListBox();
	DlgDetailsFactorisation(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(DlgDetailsFactorisation)
	enum { IDD = IDD_DIALOG_FACTORISATION_DETAILS };
	CListCtrl	m_FactorisationDetails;
	CString	m_orignNumber;
	CString	m_factorisedNumber;
	CString	m_Factor1isPrime;
	CString	m_Factor2isPrime;
	CString	m_factor2;
	CString	m_factor1;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(DlgDetailsFactorisation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(DlgDetailsFactorisation)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkSelect(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDETAILSFACTORISATION_H__C7183AE5_1AE6_11D6_ACFC_000255321174__INCLUDED_
