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

#ifndef AFX_DLGSIGNEXTRACT_H__9FCAFEFF_FF13_11D3_879C_00C04F795E36__INCLUDED_
#define AFX_DLGSIGNEXTRACT_H__9FCAFEFF_FF13_11D3_879C_00C04F795E36__INCLUDED_

// DlgSignExtract.h : Header-Datei
//
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic, 2000
//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgExtractSignature 

class CDlgExtractSignature : public CDialog
{
// Konstruktion
public:
	// CDlgExtractSignature(CWnd* pParent = NULL);   // Standardkonstruktor
	CDlgExtractSignature(char* infile_name, const char *title, CWnd* pParent = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CDlgExtractSignature)
	enum { IDD = IDD_EXTRACT_SIGNATURE };
	CEdit	m_TextAlgCtrl;
	CEdit	m_TextKeyCtrl;
	CEdit	m_TextSignerCtrl;
	CEdit	m_DefEditCtrl;
	CEdit	m_TextMsgCtrl;
	CEdit	m_TextSigCtrl;
	CEdit	m_MessageCtrl;
	CEdit	m_SignatureCtrl;
	CButton	m_RadioHexadezimal;
	CButton	m_RadioDezimal;
	CButton	m_RadioOktal;
	CButton	m_RadioOctets;
	int		m_sigButtonGroup;
	CString	m_KeyInfo;
	CString	m_Signature;
	CString	m_SignatureLength;
	CString	m_Message;
	CString	m_MessageLength;
	CString	m_InfoAboutSigner;
	CString	m_SigHashAlg;
	CString	m_TextSig;
	CString	m_TextMsg;
	CString	m_TextSigner;
	CString	m_TextKey;
	CString	m_TextAlg;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgExtractSignature)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	char *inFileName;
	const char *doctitle;
	int hexdumpCols;
	int base;

	L_NUMBER c[MAXLGTH]; // only correct initialized then verifiying EC signatures
	L_NUMBER d[MAXLGTH]; // only correct initialized then verifiying EC signatures
	Signature Signatur; // only correct initialized then verifiying RSA or DSA signatures
	OctetString message; // signed message, enthält später die signierte Nachricht

	int SignatureType;

	CFont Font;
	CFont Font2;

	int UpdateSigEditBox();

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgExtractSignature)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRadioOctets();
	afx_msg void OnRadioOktal();
	afx_msg void OnRadioDezimal();
	afx_msg void OnRadioHexadezimal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedExtractSignatureVerify();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSIGNEXTRACT_H__9FCAFEFF_FF13_11D3_879C_00C04F795E36__INCLUDED_
