#if !defined(AFX_DLGGENRANDOMDATA_H__87703501_3308_11D5_92F3_00B0D0161C45__INCLUDED_)
#define AFX_DLGGENRANDOMDATA_H__87703501_3308_11D5_92F3_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGenRandomData.h : Header-Datei
//
#include "HexEdit.h"
#include "IntegerArithmetic.h"
#include "DlgX2ModNRandomParamater.h"
#include "DlgLCGRandomParameter.h"
#include "DlgICGRandomParamater.h"
#include "DlgShowProgress.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRandomGenerator 

typedef struct
{
	int		m_SelGenerator;
	long	m_DataSize;
	CString m_seed;

	// x^2 (mod N) Generator
	CX2ModNGenerator rnd_x2modN;
	CDlgX2ModNRandomParamater DRPXN;

	// LCG Generator
	LinearCongruenceGenerator DLCG;
	CDlgLCGRandomParameter DRP_LCG;

	// EICG Generator
	InverseCongruenceGenerator DICG;
	CDlgICGRandomParamater DRP_ICG;

} RandPar;

class CDlgRandomGenerator : public CDialog
{
// Konstruktion
public:


// ============================================
	//char outfile[128];

	CDlgRandomGenerator(CWnd* pParent = NULL);   // Standardkonstruktor
	

	//friend UINT GenRandomDataThread( PVOID pParam ); // Thread-Version

// Dialogfelddaten
	//{{AFX_DATA(CDlgRandomGenerator)
	enum { IDD = IDD_RANDOM_GENERATOR };
	CButton	m_CtrlSecudeGenerator;
	CHexEdit	m_seed_ctrl;
	int		m_SelGenerator;
	CString m_seed;
	long	m_DataSize;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgRandomGenerator)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	RandPar* m_pPara;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRandomGenerator)
	afx_msg void OnSelGenParam();
	afx_msg void OnGenRandomData();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGGENRANDOMDATA_H__87703501_3308_11D5_92F3_00B0D0161C45__INCLUDED_
