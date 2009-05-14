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
#define DIR_ENCRYPT 0 

#define INFO_TEXT_COLUMNS 20 // Abhängig von der Fensterbreite in den Ressourcen !!!!!!
                             // Beim Editieren der Ressoucen bitte Größe anpassen


// Falls der SCA-Modus aktiviert ist, werden in folgender Struktur Informationen
// über das ausgewählte Zertifikat/RSA-Schlüsselpaar abgelegt:
struct SCACertificateInformation
{
	CString firstname;
	CString lastname;
	CString keytype;
	CString time;
	CString keyid;
};

class CDlgHybridEncryptionDemo : public CDialog
{
// Konstruktion
public:

	SCACertificateInformation getCertInfo();
	CString getSCAFile();
	void activateSCABehaviour();
	
	bool DateiOeffnen(const CString &DateiPfadName);
	int m_ButtonStatus[11];					// Zustand des Buttons (deaktiviert / aktiviert, aber noch nicht
											// gedrückt / aktiviert und schon gedrückt)
	bool m_ActionPerformed[11];				// Button wurde gedrückt? (TRUE = ja / FALSE = nein)
	bool m_setMatrix[11][11];
	CString m_strBuffEditEncKeyAsym;
	CString m_strBuffEditEncDoc;
	CString Edit;
	int m_iDocSize;
	bool m_bAuswahlDat;
	CDlgRSAEncryption rsaDlg;
	char *SymKey;
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

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgHybridEncryptionDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
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

	SCACertificateInformation scaCertInfo;
	
	CString scaFile;
	bool isSCABehaviourActivated;
	
	enum ButtonStatus {inactive /* = 0*/, active_not_pressed /* = 1*/, active_pressed /* = 2*/};
	// Default-Einstellung für die Länge des symmetrischen Schlüssels; wird
	// im Konstruktor initialisiert (Lesen aus .ini-Datei)
	int symKeyByteLength;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_HYBRIDENCR_H__EB90CA93_1BA0_11D6_AB88_0006291976BD__INCLUDED_
