#if !defined(AFX_DLGGENRANDOMDATA_H__87703501_3308_11D5_92F3_00B0D0161C45__INCLUDED_)
#define AFX_DLGGENRANDOMDATA_H__87703501_3308_11D5_92F3_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGenRandomData.h : Header-Datei
//
#include "HexEdit1.h"
#include "CryptologyUsingMiracl.h"
#include "DlgRandParameter_x2_mod_N.h"
#include "DlgRandomParameterLCG.h"
#include "DlgRandParamICG.h"
#include "DlgFortschritt.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgGenRandomData 

typedef struct
{
	int		m_SelGenerator;
	long	m_DataSize;
	CString m_seed;

	// x^2 (mod N) Generator
	x2modN_generator rnd_x2modN;
	DlgRandParameter_x2_mod_N DRPXN;

	// LCG Generator
	LinearCongruenceGenerator DLCG;
	DlgRandomParameterLCG DRP_LCG;

	// EICG Generator
	InverseCongruenceGenerator DICG;
	DlgRandParamICG DRP_ICG;

} RandPar;

class DlgGenRandomData : public CDialog
{
// Konstruktion
public:


// ============================================
	//char outfile[128];

	DlgGenRandomData(CWnd* pParent = NULL);   // Standardkonstruktor
	

	//friend UINT GenRandomDataThread( PVOID pParam ); // Thread-Version

// Dialogfelddaten
	//{{AFX_DATA(DlgGenRandomData)
	enum { IDD = IDD_DIALOG_GEN_RANDOMDATA };
	CHexEdit	m_seed_ctrl;
	int		m_SelGenerator;
	CString m_seed;
	long	m_DataSize;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(DlgGenRandomData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	RandPar* m_pPara;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(DlgGenRandomData)
	afx_msg void OnSelGenParam();
	afx_msg void OnGenRandomData();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGGENRANDOMDATA_H__87703501_3308_11D5_92F3_00B0D0161C45__INCLUDED_
