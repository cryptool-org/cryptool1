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
	int		BitlengthF1;
	int		BitlengthF2;
	struct  DFItem *next;
};


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFactorisationList 

class CDlgFactorisationList : public CDialog
{
// Konstruktion
	struct DFItem *List;
public:
	~CDlgFactorisationList();
	char outfile[256];
	bool b_SaveFactorList;
	void ClearFactDetail();
	void InsertFactDetail( CString & Num, CString &Factor1, 
		                   CString &Factor2, CString &Method, CString &Time, int PrimeMask,
						   int BitlengthF1, int BitlengthF2);
	void Init_ListBox();
	CDlgFactorisationList(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgFactorisationList)
	enum { IDD = IDD_FACTORISATION_LIST };
	CListCtrl	m_FactorisationDetails;
	CString	m_orignNumber;
	CString	m_factorisedNumber;
	CString	m_Factor1isPrime;
	CString	m_Factor2isPrime;
	CString	m_factor2;
	CString	m_factor1;
	//}}AFX_DATA

	CString m_benoetigte_zeit_global;
	CString m_Factorisation;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgFactorisationList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgFactorisationList)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkSelect(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDETAILSFACTORISATION_H__C7183AE5_1AE6_11D6_ACFC_000255321174__INCLUDED_
