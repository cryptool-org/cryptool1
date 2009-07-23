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
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef _AUTOMATEDPERM_ANALYSIS_H
#define _AUTOMATEDPERM_ANALYSIS_H

#include "afxwin.h"
#include "resource.h"
#include "automated_permanalysis.h"
#include "afxcmn.h"
#include "assert.h"

// CDlgAutomatedPermAnalysis dialog

class CDlgAutomatedPermAnalysis : public CDialog
{
	DECLARE_DYNAMIC(CDlgAutomatedPermAnalysis)

private:
	HWND hWndEditPlain;
	HWND hWndEditCipher;
	int  m_edTab;

	automated_permanalysis permanalysis;
	char *fn_activeDocument;
	char *fn_plaintext;
	char *fn_ciphertext;
	__int64 s_activeDocument, s_plaintext, s_ciphertext;


	void OpenFile(const char *fileName);
	void SaveFile();
	void setViewOptions();
	void initSCEdit();
	int setSourceFilename(const char *filename, char *&fn, __int64 &sz);

	LRESULT ScinMSG(UINT Msg, WPARAM wParam=0, LPARAM lParam=0) {
		assert(m_edTab < 2 );
		return FromHandle( !( m_edTab ) ? hWndEditPlain : hWndEditCipher )->SendMessage(Msg, wParam, lParam);
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	void check_dir(int &rowByRow, int &colByCol, int isRowByRow);

public:
	CDlgAutomatedPermAnalysis(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAutomatedPermAnalysis();

// Dialog Data
	enum { IDD = IDD_AUTOMATED_PERM_ANALYSIS };

	virtual BOOL OnInitDialog();
	int setSourceFilename(const char *filename) 
	{ return setSourceFilename(filename, fn_activeDocument, s_activeDocument); }
	int m_chk_inRowbyRow;
	int m_chk_permRowbyRow;
	int m_chk_outRowbyRow;
	int m_chk_inColbyCol;
	int m_chk_permColbyCol;
	int m_chk_outColbyCol;
	int m_DataType;
	CString m_editRangeFrom;
	CString m_editRangeTo;

	afx_msg void OnBnClickedLoadFile();
	afx_msg void OnBnClickedCompute();
	afx_msg void OnBnClickedinRowByRow();
	afx_msg void OnBnClickedinColByCol();
	afx_msg void OnBnClickedPermRowByRow();
	afx_msg void OnBnClickedPermColByCol();
	afx_msg void OnBnClickedOutRowByRow();
	afx_msg void OnBnClickedOutColByCol();
	afx_msg void OnBnClickedRadioText();
	afx_msg void OnBnClickedRadioBinary();
	afx_msg void OnBnClickedTextOptions();
	CTabCtrl m_TC_textspace;
	afx_msg void OnTcnSelchangeTabEditor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedLoadActiveDocument();
	CButton m_ctrl_LoadActiveDocument;
	afx_msg void OnBnClickedClose();
};


#endif