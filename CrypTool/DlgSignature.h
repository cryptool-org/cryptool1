/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

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

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSignature)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
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
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSIGN_H__A55D2FEB_B45F_11D2_8D43_00C04F795E36__INCLUDED_