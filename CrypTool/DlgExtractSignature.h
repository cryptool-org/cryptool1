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
