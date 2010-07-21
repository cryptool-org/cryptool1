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

//////////////////////////////////////////////////////////////////
#ifndef AFX_TEXTEINGABEHILLANGRIFF_H__154D9E9D_8504_11D2_8D33_00C04F795E36__INCLUDED_
#define AFX_TEXTEINGABEHILLANGRIFF_H__154D9E9D_8504_11D2_8D33_00C04F795E36__INCLUDED_
#include "afxwin.h"
#include "afxcmn.h"
#include "assert.h"

// TextEingabeHillAngriff.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHillAnaylsis 

class CDlgHillAnaylsis : public CDialog
{
	HWND hWndEditPlain;
	HWND hWndEditCipher;
	int  m_edTab;
	long m_sel_tab1, m_sel_tab2;

	LRESULT ScinMSG(UINT Msg, WPARAM wParam=0, LPARAM lParam=0) {
		assert(m_edTab < 2 );
		return FromHandle( !( m_edTab ) ? hWndEditPlain : hWndEditCipher )->SendMessage(Msg, wParam, lParam);
	}
	void OpenFile(const char *fileName);
	void SaveFile();
	void setViewOptions();
	void initSCEdit();
	int  setSourceFilename(const char *filename, char *&fn, __int64 &sz);

public:
	int bis;
	int von;

	char *fn_activeDocument;
	char *fn_plaintext;
	char *fn_ciphertext;
	__int64 s_activeDocument, s_plaintext, s_ciphertext;


	CDlgHillAnaylsis(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgHillAnaylsis();

// Dialogfelddaten
	enum { IDD = IDD_HILL_ANALYSIS };

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDimVon();
	afx_msg void OnSelchangeDimBis();

public:
	CComboBox	m_DimensionVon;
	CComboBox	m_DimensionBis;
	CTabCtrl m_TC_textspace;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	int setSourceFilename(const char *filename) 
	{ return setSourceFilename(filename, fn_activeDocument, s_activeDocument); }
	afx_msg void OnBnClickedSearchKey();
	afx_msg void OnBnClickedCancel();
//	int m_multDir;
//	int m_ofs;
	afx_msg void OnBnClickedTextOptions();
	afx_msg void OnCbnSelendokFileSelect();
	CComboBox m_ctrlFileSelect;
	int m_check_VM;
	int m_check_MV;
	afx_msg void OnBnClickedCheckVM();
	afx_msg void OnBnClickedCheckMV();
};


#endif // AFX_TEXTEINGABEHILLANGRIFF_H__154D9E9D_8504_11D2_8D33_00C04F795E36__INCLUDED_
