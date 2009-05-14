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

#if !defined(AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEREPORT_H__FEC28F94_9F75_4F87_ACD8_C61588479ADF__INCLUDED_)
#define AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEREPORT_H__FEC28F94_9F75_4F87_ACD8_C61588479ADF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSideChannelAttackVisualizationHEReport.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSideChannelAttackVisualizationHEReport 

class CDlgSideChannelAttackVisualizationHEReport : public CDialog
{
// Konstruktion
public:
	CDlgSideChannelAttackVisualizationHEReport(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSideChannelAttackVisualizationHEReport)
	enum { IDD = IDD_SIDECHANNELATTACKVISUALIZATION_HE_REPORT };
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgSideChannelAttackVisualizationHEReport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSideChannelAttackVisualizationHEReport)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEREPORT_H__FEC28F94_9F75_4F87_ACD8_C61588479ADF__INCLUDED_
