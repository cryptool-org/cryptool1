/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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
// Programmiert von Bartol Filipovic 1999-2000
//////////////////////////////////////////////////////////////////


#ifndef AFX_DLGSIGN_H__A55D2FEB_B45F_11D2_8D43_00C04F795E36__INCLUDED_
#define AFX_DLGSIGN_H__A55D2FEB_B45F_11D2_8D43_00C04F795E36__INCLUDED_

// DlgSign.h : Header-Datei
//

#include "s_ecFp.h"
#include "KeyFileHandling.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignature 

class CDlgSignature : public CDialog
{
// Konstruktion
public:
	CDlgSignature(CWnd* pParent = NULL);   // Standardkonstruktor

	CDlgSignature::~CDlgSignature();

// Dialogfelddaten
	//{{AFX_DATA(CDlgSignature)
	enum { IDD = IDD_SIGNATURE };
	CButton	m_CheckSteps;
	CButton	m_pcRadio;
	CButton	m_acRadio;
	CButton	m_RadioECNR;
	CButton	m_RadioECDSA;
	CButton	m_RadioDSA;
	CButton	m_RadioRSA;
	CButton	m_CheckRSA;
	CButton	m_CheckDSA;
	CButton	m_CheckEC;
	CListCtrl	m_listview;
	CButton	m_ctrl11;
	CButton	m_ctrl15;
	CButton	m_ctrl14;
	CButton	m_ctrl13;
	CButton	m_ctrl12;
	CEdit	m_ctrl1;
	CString	m_edit;
	int		m_radio;
	int		m_SignAlg;
	int		m_EcPointRepresModus;
	BOOL	m_ShowDuration;
	BOOL	m_ShowSteps;
	//}}AFX_DATA

	EcDomParam_ac_ptr DomParamAc; // The Domain Parameter (affine coordinates) of the selected elliptic Curve
	EcDomParam_pc_ptr DomParamPc; // The Domain Parameter (projective coordinates) of the selected elliptic Curve

	bool use_affine_coord;// TRUE:affine coordinates;FALSE:projective coordinate

	CString UserKeyId;

	CString Name;
	CString Firstname;
	CString KeyType;

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgSignature)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	int m_lastSelectedRow;
	int sortBy;
	unsigned nKeylistType;

	CString KeyInfo;
	CString CreatTime;

	void InitAsymKeyListBox(unsigned nLocalKeylistType);
	int FindRow( CString pattern);
	int GetSpecifRow(UINT mask);
	void EnableAllRadioButtons();
	void UpdateRowSel(int row);
	void FreeEcMemory();

	CSortAsymKeyList sortedAsymKeyList;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSignature)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckDsaKeys();
	afx_msg void OnCheckEcKeys();
	afx_msg void OnCheckRsaKeys();
	afx_msg void OnRadioRSA();
	afx_msg void OnRadioDSA();
	afx_msg void OnRadioECDSA();
	afx_msg void OnRadioECNR();
	afx_msg void OnRadioAffinCoord();
	afx_msg void OnRadioProjectCoord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSIGN_H__A55D2FEB_B45F_11D2_8D43_00C04F795E36__INCLUDED_