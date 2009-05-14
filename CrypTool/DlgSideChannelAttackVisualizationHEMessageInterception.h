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

#if !defined(AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEMESSAGEINTERCEPTION_H__AA2A44F1_D5CD_41BE_852E_E7A3B2A50819__INCLUDED_)
#define AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEMESSAGEINTERCEPTION_H__AA2A44F1_D5CD_41BE_852E_E7A3B2A50819__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSideChannelAttackVisualizationHEMessageInterception.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSideChannelAttackVisualizationHEMessageInterception 

class CDlgSideChannelAttackVisualizationHEMessageInterception : public CDialog
{
// Konstruktion
public:
	CDlgSideChannelAttackVisualizationHEMessageInterception(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSideChannelAttackVisualizationHEMessageInterception)
	enum { IDD = IDD_SIDECHANNELATTACKVISUALIZATION_HE_MESSAGEINTERCEPTION };
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgSideChannelAttackVisualizationHEMessageInterception)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSideChannelAttackVisualizationHEMessageInterception)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEMESSAGEINTERCEPTION_H__AA2A44F1_D5CD_41BE_852E_E7A3B2A50819__INCLUDED_
