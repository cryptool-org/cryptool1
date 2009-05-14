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

#if !defined(AFX_DLGDIFFIEHELLMANVISUALIZATION_H__CE0FF917_D502_11D6_A88B_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANVISUALIZATION_H__CE0FF917_D502_11D6_A88B_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanVisualization.h : Header-Datei
//

#include "DiffieHellmanParty.h"
#include "DiffieHellmanButtonControl.h"
#include "DiffieHellmanLogFile.h"
// für animierte GIF-Pfeile
#include "PictureEx.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanVisualization 

class CDlgDiffieHellmanVisualization : public CDialog
{
// Konstruktion
public:
	void UpdateGUI(int);
	bool CheckInternalStatus();
	void CreateErrorMessage(DHError&);
	CDlgDiffieHellmanVisualization(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgDiffieHellmanVisualization();
	
// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanVisualization)
	enum { IDD = IDD_DIFFIEHELLMANVISUALIZATION };
	CString	m_Generator;
	CString	m_Prime;
	CString	m_SecretAlice;
	CString	m_SecretBob;
	CString	m_SharedKeyAlice;
	CString	m_SharedKeyBob;
	CString	m_SessionKeyAlice;
	CString	m_SessionKeyBob;
	BOOL m_bShowInfoDialogues;
	BOOL m_bShowIntroDialog;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanVisualization)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
private:
	BitmapButtonControl *pButtonControl;
	DiffieHellmanParty *Alice;
	DiffieHellmanParty *Bob;
	// Zeiger auf eine Logdatei; ihr werden am Ende des Verfahrens die ermittelten
	// Parameter übergeben.
	DiffieHellmanLogFile *pDiffieHellmanLogFile;

	// Für die GIF-Animation(en) im Dialog:
	CPictureEx m_AnimGif;
	bool m_bAnimatedGIFLoaded;
	bool m_bStaticGIFLoaded;

	// ToolTip-Control für Schlüsselanzeige
	CToolTipCtrl *pToolTipKey;

public:

	// Für die GIF-Animation(en) im Dialog
	void ShowAnimatedGIF();
	void ShowStaticGIF(unsigned long gifIDR);


protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanVisualization)
	afx_msg void OnSetPublicParameters();
	afx_msg void OnSetsecrets();
	virtual BOOL OnInitDialog();
	afx_msg void OnCreatesharedkey();
	afx_msg void OnExchangesharedkeys();
	afx_msg void OnGeneratefinalkey();
	afx_msg void OnButtonalice1();
	afx_msg void OnButtonbob1();
	afx_msg void OnButtonalice2();
	afx_msg void OnButtonbob2();
	afx_msg void OnButtonalice3();
	afx_msg void OnButtonbob3();
	afx_msg void OnCheckDisablehelp();
	afx_msg void OnCheckDisableIntroDialog();
	afx_msg void OnKey();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CBrush m_greybrush;
	COLORREF m_greycolor;
	CBrush m_blackbrush;
	COLORREF m_blackcolor;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANVISUALIZATION_H__CE0FF917_D502_11D6_A88B_00025532117A__INCLUDED_
