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


#if !defined(AFX_DLGSIGNTUTORIAL_H__C8A91DA0_040A_11D6_8A81_000255320F1C__INCLUDED_)
#define AFX_DLGSIGNTUTORIAL_H__C8A91DA0_040A_11D6_8A81_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSignTutorial.h : Header-Datei
//
#include "PSEDemo.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignatureDemo 

class CDlgSignatureDemo : public CDialog
{
// Konstruktion
public:
	CDlgSignatureDemo(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgSignatureDemo();

	// Funktionen
	BOOL InitDocument(const char *infile, const char* OldTitle);

protected:
	// Variablen
	CString			m_sPathName;	// Pfadname des Dokuments
	CString			m_sFileName;	// Titel des Dokuments
	CString			m_sFileNameNew; // Titel des signierten Dokuments
	int				m_nCols;		// Spaltenzahl des Displays
	CFont			m_Font1;	
	BOOL			m_bUpdateHsh;
	BOOL			m_bUpdateEnc;
	BOOL			m_bUpdateSgn;
	BOOL			m_bUpdateCrt;
	BOOL			m_bPSEIsExtern;
	OctetString 	m_osHash;
	OctetString		m_osHashDER;
	OctetString		m_osHashEnc;
	OctetString		m_SignText;		// OctetString

	// Zeiger	
	OctetString*    m_Message;		// Zeiger auf OctetString
	CPSEDemo*		m_Cert;			// Zeiger auf CPSEDemo
	CAppDocument*	m_NewDoc;		// Zeiger auf CAppDocument
	CWnd*			m_hFocus;		// Zeiger auf CWnd

	// Buttons
	CBitmapButton m_ButtonSelectDoc;
	CBitmapButton m_ButtonSelectHashAlg;
	CBitmapButton m_ButtonSelectKey;
	CBitmapButton m_ButtonSelectCert;

	CBitmapButton m_ButtonInfoDoc;
	CBitmapButton m_ButtonInfoHashAlg;
	CBitmapButton m_ButtonInfoKey;
	CBitmapButton m_ButtonInfoCert;

	CBitmapButton m_ButtonCompute;
	CBitmapButton m_ButtonEncrypt;
	CBitmapButton m_ButtonCombine;

	CBitmapButton m_ButtonInfoHash;
	CBitmapButton m_ButtonInfoHashEnc;
	CBitmapButton m_ButtonInfoSign;

	CBitmapButton m_ButtonCancel;
	CBitmapButton m_ButtonOK;

// Dialogfelddaten
	//{{AFX_DATA(CDlgSignatureDemo)
	enum { IDD = IDD_SIGNATURE_DEMO };
	CStatic	m_DisplayContentCtrl;
	CEdit	m_DisplayInfoCtrl;
	CString	m_DisplayInfo;
	CString	m_DisplayContent;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSignatureDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void EnableButtons();
	void ClearInfo();

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSignatureDemo)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectDocument();
	afx_msg void OnInfoDocument();
	afx_msg void OnSelectKey();
	afx_msg void OnInfoKey();
	afx_msg void OnSelectHashAlg();
	afx_msg void OnCompute();
	afx_msg void OnInfoHash();
	afx_msg void OnEncrypt();
	afx_msg void OnInfoHashEnc();
	afx_msg void OnSelectCert();
	afx_msg void OnInfoAlg();
	afx_msg void OnCombine();
	virtual void OnOK();
	afx_msg void OnInfoCert();
	afx_msg void OnInfoSign();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSIGNTUTORIAL_H__C8A91DA0_040A_11D6_8A81_000255320F1C__INCLUDED_
