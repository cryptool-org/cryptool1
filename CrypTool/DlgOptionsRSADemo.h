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

#if !defined(AFX_DLGRSAWITHSMALLPRIMESOPTIONS_H__98A64261_5414_11D5_9319_00B0D0161C45__INCLUDED_)
#define AFX_DLGRSAWITHSMALLPRIMESOPTIONS_H__98A64261_5414_11D5_9319_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRSAwithSmallPrimesOptions.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsRSADemo 

class CDlgOptionsRSADemo : public CDialog
{
// Konstruktion
public:
	void MsgAnzahlZeichen();
	void ReInitBlockLength(BOOL setMaxBlockLength = FALSE);
	void MsgBlockLength();
	bool CompareModulAlphabetSize(CString N_str);
	CDlgOptionsRSADemo(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgOptionsRSADemo)
	enum { IDD = IDD_OPTIONS_RSA_DEMO };
	CButton	m_RSAVariantCtrl;
	CButton m_CodingControl;
	CEdit	m_BlockLengthCtrl;
	CEdit	m_alphabetControl;
	CString	m_alphabet;
	int		m_numberBasis;
	int		m_TextOptions;
	int     m_RSAVariant;
	UINT	m_BlockLength;
	int     m_Bitlength;
	CString	m_MaxBlockLength;
	int		m_codingMethod;
	CString	m_AnzahlZeichen;
	//}}AFX_DATA
	double m_log2N;
	CString RSA_Modul;
	int Anzahl_Zeichen;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgOptionsRSADemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgOptionsRSADemo)
	afx_msg void OnSelectRSA();
	afx_msg void OnSelectDialougeOfSisters();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeAlphabet();
	afx_msg void OnSelectASCII();
	afx_msg void OnSelectAlphabet();
	virtual void OnOK();
	afx_msg void OnCodingNumberSystem();
	afx_msg void OnCodingBAdic();
	afx_msg void OnBase10();
	afx_msg void OnBase2();
	afx_msg void OnBase8();
	afx_msg void OnBase16();
	virtual void OnCancel();
	afx_msg void OnChangeEdit3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int GetBlockLength();

	CString s_alphabet;
	int     s_numberBasis;
	int     s_TextOptions;
	int     s_RSAVariant;
	int     s_BlockLength;
	CString s_MaxBlockLength;
	int     s_codingMethod;
	CString s_AnzahlZeichen;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRSAWITHSMALLPRIMESOPTIONS_H__98A64261_5414_11D5_9319_00B0D0161C45__INCLUDED_
