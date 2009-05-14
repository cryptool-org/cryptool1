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

#if !defined(AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEPREPARATIONS_H__B0302F79_94ED_424B_90BF_A85DA006AC34__INCLUDED_)
#define AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEPREPARATIONS_H__B0302F79_94ED_424B_90BF_A85DA006AC34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSideChannelAttackVisualizationHEPreparations.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSideChannelAttackVisualizationHEPreparations 

// wegen init-Modes
#include "DlgSideChannelAttackVisualizationHE.h"
// wegen CertStruktur
#include "DlgHybridEncryptionDemo.h"


class CDlgSideChannelAttackVisualizationHEPreparations : public CDialog
{
	bool useExistingHybEncFile;

// Konstruktion
public:
	bool isExistingHybEncFileUsed() { return useExistingHybEncFile; };
	CString getOriginalSessionKey();
	SCACertificateInformation getCertInfo();
	CString getFinalHybEncFile();
	void setInitFile(CString);
	void setInitFileTitle(CString);
	void setInitMode(int);
	CDlgSideChannelAttackVisualizationHEPreparations(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSideChannelAttackVisualizationHEPreparations)
	enum { IDD = IDD_SIDECHANNELATTACKVISUALIZATION_HE_PREPARATIONS };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSideChannelAttackVisualizationHEPreparations)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSideChannelAttackVisualizationHEPreparations)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString originalSessionKey;
	CString certFilename;
	SCACertificateInformation scaCertInfo;
	CString finalHybEncFile;
	CString initFile;
	CString initFileTitle;
	int initMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEPREPARATIONS_H__B0302F79_94ED_424B_90BF_A85DA006AC34__INCLUDED_
