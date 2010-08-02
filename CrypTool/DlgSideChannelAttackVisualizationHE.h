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

#if !defined(AFX_DLGSIDECHANNELATTACKVISUALIZATIONHE_H__998CA727_553E_497C_A839_A042B3538D85__INCLUDED_)
#define AFX_DLGSIDECHANNELATTACKVISUALIZATIONHE_H__998CA727_553E_497C_A839_A042B3538D85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSideChannelAttackVisualizationHE.h : Header-Datei
//

// sub-dialogues
#include "DlgSideChannelAttackVisualizationHEIntroduction.h"
#include "DlgSideChannelAttackVisualizationHEPreparations.h"
#include "DlgSideChannelAttackVisualizationHEMessagetransmission.h"
#include "DlgSideChannelAttackVisualizationHEMessageinterception.h"
#include "DlgSideChannelAttackVisualizationHEAttackcycle.h"
#include "DlgSideChannelAttackVisualizationHEReport.h"
#include "DlgSideChannelAttackVisualizationHEPSEPINPrompt.h"
#include "DlgHybridEncryptionDemo.h"	// Hinzugef�gt von der Klassenansicht

#include "DlgSideChannelAttackVisualizationHEFinished.h"

#include "DlgSideChannelAttackVisualizationHEAlice.h"
#include "DlgSideChannelAttackVisualizationHEBob.h"
#include "DlgSideChannelAttackVisualizationHETrudy.h"

// Seitenkanalangriff(e)
#include "SideChannelAttack.h"
#include "SideChannelAttackButtonControl.h"

// f�r animierte GIFs
#include "PictureEx.h"


// * INIT MODES *
#define SCA_MODE_VALID_FILE					1
#define SCA_MODE_INVALID_FILE				2
#define SCA_MODE_NO_FILE					4

// * LIGHT MODES *
#define SCA_LIGHTS_NORMAL					1
#define SCA_LIGHTS_GREEN					2
#define SCA_LIGHTS_RED						4

// * ABARROW MODES *
#define SCA_ABARROW_NORMAL					1
#define SCA_ABARROW_TRANSMISSION			2
#define SCA_ABARROW_INTERCEPTION			4
#define SCA_ABARROW_FAILURE					8
#define SCA_ABARROW_SUCCESS					16
#define SCA_ABARROW_TRANSMISSION_TRUDYBOB	32

// * TIMER EVENTS *
#define SCA_TIMEREVENT_AB_TRANSMISSION		512
#define SCA_TIMEREVENT_TB_TRANSMISSION		1024

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSideChannelAttackVisualizationHE 

class CDlgSideChannelAttackVisualizationHE : public CDialog
{
	void startAttackCycle();
	void cancelAttackCycle();

	HybridEncryptedFileInfo hi;
	bool isHybridEncryptedFileDeclared;
	CString certFilename;
	SCACertificateInformation certInfo;
	// Pfad zur Input-Datei, d.h. Pfad zu der Datei, die beim �ffnen des
	// Dialogs aktiv war (ContentName)
	CString initFile;
	//
	CString initFileTitle;
	// Pfad zur Output-Datei, d.h. Pfad zu der HYBRIDVERSCHL�SSELTEN DATEI, die
	// beim Ausf�hren des Dialogs erzeugt worden ist. F�r sp�tere Verwendung n�tig.
	CString targetFile;
	// Initialisierungsmodus
	int initMode;
	// War ein Fenster aktiv, als der Dialog ge�ffnet wurde?
	bool isFileDeclared;

	// SCA
	SCA_Server *scaServer;
	SCA_Client *scaClient;
	SCA_Attacker *scaAttacker;

	// aktueller Status der Visualisierung
	int currentStep;
	// Update der grafischen Oberfl�che
	void updateGUI(int);

	// Button-Abh�ngigkeiten
	BitmapButtonControl *pButtonControl;

public:
	void setHybridEncryptedFileInfo(HybridEncryptedFileInfo&);

	bool isDocumentHybridEncrypted(const char*);
	void setEncryptedFile(const char*);
	void setInitFileTitle(const char*);

	// SCA
	SCA_Server *getSCAServer() { return scaServer; };
	SCA_Client *getSCAClient() { return scaClient; };
	SCA_Attacker *getSCAAttacker() { return scaAttacker; };

   c_scaBigNumberSettings scaBigNumberSettings; // FIXME HK: Ensure enough memory for Big numbers

// Konstruktion
public:
	void setLights(int);
	void setABArrow(int);
	~CDlgSideChannelAttackVisualizationHE();
	void CreateErrorMessage(SCA_Error&);
	CDlgSideChannelAttackVisualizationHE(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSideChannelAttackVisualizationHE)
	enum { IDD = IDD_SIDECHANNELATTACKVISUALIZATION_HE };
	CButton	m_AttackControl;
	CButton	m_ControlButtonAllSteps;
	CButton	m_ControlButtonNextStep;
	CProgressCtrl	m_ControlAttackProgress;
	CPictureEx	m_ControlABArrow;
	CPictureEx	m_ControlLights;
	BOOL	m_bShowInfoDialogues;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgSideChannelAttackVisualizationHE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSideChannelAttackVisualizationHE)
	afx_msg void OnIntroduction();
	afx_msg void OnPreparations();
	afx_msg void OnMessagetransmission();
	afx_msg void OnMessageinterception();
	afx_msg void OnAttackcycle();
	afx_msg void OnReport();
	afx_msg void OnAlice();
	afx_msg void OnBob();
	afx_msg void OnTrudy();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonNextsinglestep();
	afx_msg void OnButtonAllremainingsteps();
	afx_msg void OnMessagereception();
	afx_msg void OnCheckDisablehelp();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CBrush m_greybrush;
	COLORREF m_greycolor;
	CBrush m_blackbrush;
	COLORREF m_blackcolor;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGSIDECHANNELATTACKVISUALIZATIONHE_H__998CA727_553E_497C_A839_A042B3538D85__INCLUDED_
