/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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
#include "afxwin.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRandomGenerator 

typedef struct
{
	int		m_SelGenerator;
	long	m_DataSize;
	CString m_seed;
	int     m_PrintInternalStates;

	// X^2 (mod N) Generator
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
	int     m_PrintInternalStates;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgRandomGenerator)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
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

public:
	afx_msg void OnBnClickedRadio1();
	CButton m_ctrlSetInternalStates;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGGENRANDOMDATA_H__87703501_3308_11D5_92F3_00B0D0161C45__INCLUDED_
