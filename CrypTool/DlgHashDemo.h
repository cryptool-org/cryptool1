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

#if !defined(AFX_HASHDEMO_H__06BADA81_9DFF_11D5_AB3E_0006291976BD__INCLUDED_)
#define AFX_HASHDEMO_H__06BADA81_9DFF_11D5_AB3E_0006291976BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Hashdemo.h : Header-Datei
//

#define MAX_LAENGE_STRTEXT 16000

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHashDemo 

class CDlgHashDemo : public CDialog
{
// Konstruktion
	CString	m_strHashDiffRE;
	CString m_strNewHashBin;
	CString m_strOrigHashBin;
	CString m_strTitle;
	OctetString m_hash, m_newHash; 
	OctetString m_dataOrig; 
	CString m_strText; // initial content of m_ctrlText;  

	// Texte für Auswahl der Hashfunktionen
	CString m_strHashFunctionMD2;
	CString m_strHashFunctionMD4;
	CString m_strHashFunctionMD5;
	CString m_strHashFunctionSHA;
	CString m_strHashFunctionSHA1;
	CString m_strHashFunctionSHA256;
	CString m_strHashFunctionSHA512;
	CString m_strHashFunctionRIPEMD160;

public:
	unsigned long loadData( const char *infile, const char *title, unsigned long filesize, unsigned long max_filesize = MAX_LAENGE_STRTEXT );
	CDlgHashDemo(CWnd* pParent = NULL);   // Standardkonstruktor
    ~CDlgHashDemo();

protected:
// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgHashDemo)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Dialogfelddaten
	//{{AFX_DATA(CDlgHashDemo)
	enum { IDD = IDD_HASH_DEMO };
	CComboBox	m_comboCtrlSelectHashFunction;
	CEdit	m_ctrlText;
	CRichEditCtrl	m_ctrlHashDiff;
	CFont   m_font;
	int		m_rb_DarstHW;
	CString	m_strOrigHash; // display original hash in hex
	CString	m_strNewHash;
	//}}AFX_DATA
	

// Implementierung
private:
	void SetRed();
	void SetHashDiff(OctetString &hash1,OctetString &hash2);
	void showDiffNewHashBin(OctetString &hash);
	void showDiffOrigHashBin(OctetString &hash);
	void ComputeHash(OctetString *data, OctetString *hashValue);

	void getNextBlock(CString &dispByte, unsigned char inByte, unsigned short numberBase, char seperator = '\0');
	void showHashBin(OctetString &hash);
	void showHashHex(OctetString &hash);
	void showHashDec(OctetString &hash);
	void showNewHashHex(OctetString &hash);
	void showNewHashDec(OctetString &hash);
	void showNewHashBin(OctetString &hash);
	

protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgHashDemo)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioBin();
	afx_msg void OnRadioDec();
	afx_msg void OnRadioHex();
	afx_msg void OnChangeEditText();
	afx_msg void OnSelendokComboSelectHashFunction();
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_HASHDEMO_H__06BADA81_9DFF_11D5_AB3E_0006291976BD__INCLUDED_
