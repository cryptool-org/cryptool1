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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DlgSignVerif.h
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////

#ifndef AFX_DLGSIGNVERIF_H__EDF96D97_EF51_11D3_8797_00C04F795E36__INCLUDED_
#define AFX_DLGSIGNVERIF_H__EDF96D97_EF51_11D3_8797_00C04F795E36__INCLUDED_

// DlgSignVerif.h : Header-Datei
//

#include "s_ecFp.h"
#include "KeyFileHandling.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgVerifySignature 

class CDlgVerifySignature : public CDialog
{
// Konstruktion
public:
	CDlgVerifySignature(CWnd* pParent = NULL);   // Standardkonstruktor
	CDlgVerifySignature(char* sig_id, char* hash_id, CString sig_key,  CWnd* pParent = NULL);
	CDlgVerifySignature::~CDlgVerifySignature(); // Destruktor

	EcDomParam_ac_ptr DomParamAc; // The Domain Parameter (affine coordinates) of the selected elliptic Curve
	EcDomParam_pc_ptr DomParamPc; // The Domain Parameter (projective coordinates) of the selected elliptic Curve

	char *sigAlg;
	char *hashAlg;

	bool use_affine_coord;// TRUE:affine coordinates;FALSE:projective coordinate

	CString signKey;
	
	CString UserKeyId;
	CString Name;
	CString Firstname;
	CString KeyType;
	CString KeyInfo;
	CString CreatTime;

// Dialogfelddaten
	//{{AFX_DATA(CDlgVerifySignature)
	enum { IDD = IDD_VERIFY_SIGNATURE };
	CButton	m_CheckSteps;
	CButton	m_pcRadioButton;
	CButton	m_acRadioButton;
	CEdit	m_CtrlSigAlg;
	CEdit	m_CtrlHashAlg;
	CButton	m_CheckRSA;
	CButton	m_CheckEC;
	CButton	m_CheckDSA;
	CListCtrl	m_listview;
	CButton	m_nrRadioButton;
	CButton	m_ecdsaRadioButton;
	CButton	m_sha1RadioButton;
	CButton	m_ripemdRadioButton;
	int		m_SigVerfahren;
	int		m_HashFunktion;
	CString	m_EditSigAlg;
	CString	m_EditHashAlg;
	int		m_sel_coord;
	BOOL	m_ShowDuration;
	BOOL	m_ShowSteps;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgVerifySignature)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	int m_lastSelectedRow;
	int sortBy;
	unsigned nKeylistType;

	void InitAsymKeyListBox(unsigned nLocalKeylistType);
	int GetSpecifRow(UINT mask);
	int FindRow( CString pattern);
	void UpdateRowSel(int row);
	void FreeEcMemory();

	CSortAsymKeyList sortedAsymKeyList;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgVerifySignature)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnCheckDsaKey();
	afx_msg void OnCheckEcKey();
	afx_msg void OnCheckRsaKey();
	afx_msg void OnKeydownList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonSearchKey();
	afx_msg void OnRadioECDSA();
	afx_msg void OnRadioECNR();
	afx_msg void OnRadioSHA1();
	afx_msg void OnRadioRIPEMD();
	afx_msg void OnRadioAffineCoord();
	afx_msg void OnRadioProjectCoord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSIGNVERIF_H__EDF96D97_EF51_11D3_8797_00C04F795E36__INCLUDED_
