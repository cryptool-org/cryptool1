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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef _AUTOMATEDPERM_ANALYSIS_H
#define _AUTOMATEDPERM_ANALYSIS_H

#include "afxwin.h"
#include "resource.h"
#include "automated_permanalysis.h"

// CDlgAutomatedPermAnalysis dialog

class CDlgAutomatedPermAnalysis : public CDialog
{
	DECLARE_DYNAMIC(CDlgAutomatedPermAnalysis)
private:
	HWND hWndEditReference;

	automated_permanalysis permanalysis;
	char *fn_source;
	char *fn_reference;
	__int64 source_filesize;

	void OpenFile(const char *fileName);
	void SaveFile();

	LRESULT ScinMSG(UINT Msg, WPARAM wParam=0, LPARAM lParam=0) {
		return FromHandle(hWndEditReference)->SendMessage(Msg, wParam, lParam);
	}

	void setRefCaption();
	void setViewOptions();

public:
	CDlgAutomatedPermAnalysis(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAutomatedPermAnalysis();

// Dialog Data
	enum { IDD = IDD_AUTOMATED_PERM_ANALYSIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	void check_dir(int &rowByRow, int &colByCol, int isRowByRow);
public:
	virtual BOOL OnInitDialog();
	int setSourceFilename(const char *filename);
	afx_msg void OnBnClickedLoadFile();
	int m_refTextType;
	int m_chk_inRowbyRow;
	int m_chk_permRowbyRow;
	int m_chk_outRowbyRow;
	int m_chk_inColbyCol;
	int m_chk_permColbyCol;
	int m_chk_outColbyCol;
	int m_DataType;
	CString m_editRangeFrom;
	CString m_editRangeTo;
	CEdit   m_ctrlRefernceHeader;
	afx_msg void OnBnClickedCompute();
	afx_msg void OnBnClickedinRowByRow();
	afx_msg void OnBnClickedinColByCol();
	afx_msg void OnBnClickedPermRowByRow();
	afx_msg void OnBnClickedPermColByCol();
	afx_msg void OnBnClickedOutRowByRow();
	afx_msg void OnBnClickedOutColByCol();
	afx_msg void OnBnClickedRadioSourceIsCiphertext();
	afx_msg void OnBnClickedRadioSourceIsPlaintext();
	afx_msg void OnBnClickedRadioText();
	afx_msg void OnBnClickedRadioBinary();
	afx_msg void OnBnClickedTextOptions();
};


#endif