/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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


#if !defined(AFX_HYBRIDENCR_H__EB90CA93_1BA0_11D6_AB88_0006291976BD__INCLUDED_)
#define AFX_HYBRIDENCR_H__EB90CA93_1BA0_11D6_AB88_0006291976BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HybridEncr.h : Header-Datei
//
#include "s_prng.h"
#include "DlgRSAEncryption.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHybridEncryptionDemo 
#define MAX_LEN_EDIT 30000
#define KEY_LEN 16
#define DIR_ENCRYPT 0 

#define INFO_TEXT_COLUMNS 20 // Abh�ngig von der Fensterbreite in den Ressourcen !!!!!!
                             // Beim Editieren der Ressoucen bitte Gr��e anpassen

class CDlgHybridEncryptionDemo : public CDialog
{
// Konstruktion
public:
	bool DateiOeffnen(const CString &DateiPfadName);
	int m_ButtonStatus[11];					// Zustand des Buttons (deaktiviert / aktiviert, aber noch nicht
											// gedr�ckt / aktiviert und schon gedr�ckt)
	bool m_ActionPerformed[11];				// Button wurde gedr�ckt? (TRUE = ja / FALSE = nein)
	bool m_setMatrix[11][11];
	CString m_strBuffEditEncKeyAsym;
	CString m_strBuffEditEncDoc;
	CString Edit;
	int m_iDocSize;
	bool m_bAuswahlDat;
	CDlgRSAEncryption rsaDlg;
	char SymKey[KEY_LEN];
	OctetString* EncSymKey;
	int m_iDocSizeForEnc;
	CFont m_font;
	CString m_strSymKey;
	CString m_strPathSelDoc; // if not empty on DoModal, this file is opened
	CString	m_strBuffTitle;
	CString UserKeyId;

	OctetString *PlainText;
	OctetString *CipherText;
	
	CDlgHybridEncryptionDemo(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgHybridEncryptionDemo();
	void ShowButtons();
	void EnDisButtons();
	void SetCondition(int button,bool state);
	void ResetDependent(int button);
	void RSAEncrypt();
	

// Dialogfelddaten
	//{{AFX_DATA(CDlgHybridEncryptionDemo)
	enum { IDD = IDD_HYBRID_ENCRYPTION_DEMO };
	CStatic	m_ctrlBG;
	CString	m_strEdit;
	CString	m_strTitle;
	//}}AFX_DATA

	CBitmapButton m_ctrlBmpRaute1;
	CBitmapButton m_ctrlBmpRaute2;
	CBitmapButton m_ctrlBmpRaute3;
	CBitmapButton m_ctrlBmpRaute4;
	CBitmapButton m_ctrlBmpRaute5;
	CBitmapButton m_ctrlBmpSechseck1;
	CBitmapButton m_ctrlBmpSechseck2;
	CBitmapButton m_ctrlBmpSechseck3;
	CBitmapButton m_ctrlBmpRechteck1;
	CBitmapButton m_ctrlBmpRechteck2;
	CBitmapButton m_ctrlBmpOval1;
	CBitmapButton m_ctrlBmpOval2;

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgHybridEncryptionDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CWnd *m_hFocus;		// Zeiger auf CWnd

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgHybridEncryptionDemo)
	afx_msg void OnButtonGetDocument();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonEncKeyAsym();
	afx_msg void OnButtonEncDocumentSym();
	afx_msg void OnButtonGenSymKey();
	afx_msg void OnButtonGetAsymKey();
	afx_msg void OnButtonShowSymKey();
	afx_msg void OnButtonShowAsymKey();
	afx_msg void OnButtonShowDocument();
	afx_msg void OnButtonShowEncDocument();
	afx_msg void OnButtonShowEncSymKey();
	afx_msg void OnButtonDatenausgabe();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	enum ButtonStatus {inactive /* = 0*/, active_not_pressed /* = 1*/, active_pressed /* = 2*/};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_HYBRIDENCR_H__EB90CA93_1BA0_11D6_AB88_0006291976BD__INCLUDED_
