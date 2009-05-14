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

#if !defined(AFX_DLGSIDECHANNELATTACKVISUALIZATIONHETRUDY_H__EE3B5F11_61DC_460C_A8AA_47BD9DCD0C62__INCLUDED_)
#define AFX_DLGSIDECHANNELATTACKVISUALIZATIONHETRUDY_H__EE3B5F11_61DC_460C_A8AA_47BD9DCD0C62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSideChannelAttackVisualizationHETrudy.h : Header-Datei
//

#include "DlgSideChannelAttackVisualizationHE.h"
#include "SideChannelAttack.h"
#include "PictureEx.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSideChannelAttackVisualizationHETrudy 

class CDlgSideChannelAttackVisualizationHETrudy : public CDialog
{
// Konstruktion
public:
	void updateDisplay();
	CDlgSideChannelAttackVisualizationHETrudy(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSideChannelAttackVisualizationHETrudy)
	enum { IDD = IDD_SIDECHANNELATTACKVISUALIZATION_HE_TRUDY };
	CListBox	m_ControlTasks;
	CListCtrl	m_ListModifiedSessionKeys;
	CString	m_DeterminedSessionKey;
	CString	m_InterceptedEncryptedSessionKey;
	CString	m_ComputedMessage;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSideChannelAttackVisualizationHETrudy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSideChannelAttackVisualizationHETrudy)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CWnd* parent;
	int significantBits;
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSIDECHANNELATTACKVISUALIZATIONHETRUDY_H__EE3B5F11_61DC_460C_A8AA_47BD9DCD0C62__INCLUDED_
