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


#if !defined(AFX_DLGHYBRIDDECRYPTIONDEMO_H__634A1871_40B8_11D6_AD1A_000255321174__INCLUDED_)
#define AFX_DLGHYBRIDDECRYPTIONDEMO_H__634A1871_40B8_11D6_AD1A_000255321174__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHybridDecryptionDemo.h : Header-Datei
//
#define MAX_LEN_EDIT 30000
#define KEY_LEN 16
#define DIR_ENCRYPT 0 

#include "s_prng.h"
#include "DlgRSADecryption.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHybridDecryptionDemo 

class CDlgHybridDecryptionDemo : public CDialog
{
// Konstruktion
public:
	bool zugross;
	CString sModN, sPhiN, sKeyPublic, sKeyPrivate, sOutput;
	OctetString message;
	CString EncSessionKey;
	OctetString OctetEncSessionKey;
	CString DecSessionKey;
	CString SymAlg;
	CString AsymAlg;
	CString UserKeyId;
	CString UserKeyId_Datei;
	CString SymAlg_Datei;
	CString AsymAlg_Datei;
	CString EncSessionKey_Datei;
	CString m_CertificateData;
	void RsaDec();
	char SymKey[KEY_LEN];
	bool m_iIsGenAsymKey;
	CString PinCode;
	CDlgRSADecryption RsaDialog1;
	int UpdateDataDisplay();
	CFont m_font;
	int m_gc;
	bool m_bAuswahlDat;
	CString	m_strTitle1;
	char* m_strEdit1;
	CString m_strPathnameTxt;
	CDlgHybridDecryptionDemo(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgHybridDecryptionDemo();
// Dialogfelddaten
	//{{AFX_DATA(CDlgHybridDecryptionDemo)
	enum { IDD = IDD_HYBRID_DECRYPTION_DEMO };
	CEdit	m_DisplayDataCtrl;
	CEdit	m_StepCtrl;
	CEdit	m_TextSignStepsCtrl;
	CButton	m_FlushDecDataCtrl;
	CButton	m_ContinueButtonCtrl;
	CString	m_TextSignSteps;
	CString	m_Step;
	CString	m_DisplayData;
	CButton m_ShowCertificate;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgHybridDecryptionDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void SetHeadLine( CString &mHeader, int IDS_STRING_ID, int base = 0 );	
	CPSEDemo* m_Cert;			// Zeiger auf CPSEDemo
	int nFirstVisibleLine;
	int step;
	CFont m_Font;
	CFont m_Font2;
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgHybridDecryptionDemo)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonContinue();
	afx_msg void OnButtonShowCertificate();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGHYBRIDDECRYPTIONDEMO_H__634A1871_40B8_11D6_AD1A_000255321174__INCLUDED_
