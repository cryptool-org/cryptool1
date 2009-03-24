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
