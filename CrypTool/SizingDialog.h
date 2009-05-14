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

////////////////////////////////////////////////////////////////////////////
// SizingDialog.h
//
// Copyright 2005 Xia Xiongjun( ÏÄÐÛ¾ü ), All Rights Reserved.
//
// E-mail: xj-14@163.com
//
// This source file may be copyed, modified, redistributed  by any means
// PROVIDING that this notice and the authors name and all copyright notices
// remain intact, and PROVIDING it is NOT sold for profit without the authors
// expressed written consent. The author accepts no liability for any 
// damage/loss of business that this product may cause.
//
////////////////////////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////////////////////
// class CCtrlInfo

class CCtrlInfo
{
// XR: Constructor and destructor
public:
	CCtrlInfo(LPCRECT rcInit = NULL,
		double dRateLeft = 0.0,  double dRateRight    = 0.0, 
		double dRateTop  = 0.0,  double dRateBottom   = 0.0);
	virtual ~CCtrlInfo(void);

// XR: Operations
public:
	BOOL Modify(const CWnd* pCtrl, const CWnd* pParent, 
		LPCTSTR lpszString, char chSpr = '+');
	BOOL Modify(LPCRECT rcInit,
		double dRateLeft = 0.0,  double dRateRight    = 0.0, 
		double dRateTop  = 0.0,  double dRateBottom   = 0.0);

// XR: Data
public:
	CRect  m_rcInit;
	double m_dRateLeft;
	double m_dRateRight;
	double m_dRateTop;
	double m_dRateBottom;

// XR: Implementations
protected:
	BOOL ExtractOptions(LPCTSTR lpszSection, 
		const CWnd* pCtrl = NULL, const CWnd* pParent = NULL);
	void GetCoefficientAndWord(LPCTSTR lpszSection,
		CString& strWord, double& dCoef) const;
};

////////////////////////////////////////////////////////////////////////////
// CSizingDialog dialog

#include "afxcoll.h"	// XR: For CMapPtrToPtr

#define DT_STRING 0
#define DT_NUMBER 1

class CSizingDialog : public CDialog
{
	DECLARE_DYNAMIC(CSizingDialog)

// XR: Constructor and destructor
public:
	explicit CSizingDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);	// constructor													
	virtual ~CSizingDialog();

// XR: Operations
protected:
	void AddResizaleCtrl(UINT nID, LPCTSTR lpszString = NULL);
	void AddResizaleCtrl(UINT nID,
		double dRateLeft, double dRateRight, 
		double dRateTop, double dRateBottom);

	void AddResizaleCtrlRange(UINT nIDStart, UINT nIDEnd, 
		LPCTSTR lpszString = NULL);
	void ModifyResizaleCtrlRange(UINT nIDStart, UINT nIDEnd, 
		LPCTSTR lpszString = NULL);
	void AddResizaleCtrlRange(UINT nIDStart, UINT nIDEnd, 
		double dRateLeft, double dRateRight, 
		double dRateTop, double dRateBottom);

	void AddResizaleCtrlArray(UINT nIDStart, UINT nIDEnd,
		double dSelfGain = 0.0, double dBorderIntervalRate = 1.0, BOOL bHori = TRUE);
	
// XR: Implementations
private:
	void AddCtrl(UINT nID, int nDataType, LPCVOID lpData);
	void AddCtrlRange(UINT nIDStart, UINT nIDEnd, int nDataType, LPCVOID lpData);
	void RearrangeID(UINT& nReIDS, UINT& nReIDE, 
		HWND& hCtrlS, HWND& hCtrlE, int& nNum) const;
	void ResizeControls();

	// XR: Save and Restore Window Position Functions
    void SaveWindowPosition();
    void RestoreWindowPosition();

public:
	void InvalidateCtrlBorder(
		LPCRECT lpRectOld, LPCRECT lpRectNew, BOOL bErase = TRUE);

// XR: Implementations
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
//	afx_msg UINT OnNcHitTest(CPoint point);
	DECLARE_MESSAGE_MAP()

// Data
private:
	CMapPtrToPtr m_mapPtToInfo;
	CRect m_rcInit;
public:
	afx_msg void OnClose();
};
