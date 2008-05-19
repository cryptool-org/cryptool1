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

#ifndef _DLGFINDANDREPLACE_H_
#define _DLGFINDANDREPLACE_H_

// DlgFindAndReplace.h

#include "HexEdit.h"

#include <vector>

// global vector for previously used FIND terms
extern std::vector<CString> termsFind;
// global vector for previously used REPLACE terms
extern std::vector<CString> termsReplace;

class CDlgFindAndReplace : public CDialog
{
	DECLARE_DYNAMIC(CDlgFindAndReplace)

public:
	CDlgFindAndReplace(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgFindAndReplace();

	// bring dialog window to foreground (make it visible)
	void show();

	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedButtonReplace();
	afx_msg void OnBnClickedButtonReplaceAll();
	afx_msg void OnBnClickedRadioTextMode();
	afx_msg void OnBnClickedRadioHexMode();

	CString textFind;
	CString textReplace;
	CString textFindHex;
	CString textReplaceHex;

// Dialog Data
	enum { IDD = IDD_FIND_AND_REPLACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()

private:
	// handles to our Scintilla windows
	HWND handleScintillaWindowFind;
	HWND handleScintillaWindowReplace;

	// hex edit fields for hex mode
	CHexEdit hexEditControlFind;
	CHexEdit hexEditControlReplace;

	// radio button for text mode
	CButton radioButtonControlText;
	// radio button for hex mode
	CButton radioButtonControlHex;

	void updateMode();

	BOOL checkCaseSensitive;
	BOOL checkFindBackwards;
	BOOL checkRegularExpressions;

	// has dialog window already been created? (MODELESS dialog!)
	bool created;
	// overridden OnCancel (MODELESS dialog!)
	virtual void OnCancel();

	void OnBnClickedButtonFind(bool replace, bool all);
	void DoFindReplace(bool replace, bool all);
	void DoFindReplaceScintilla(CWnd *pWindow, bool replace, bool all);
	void DoFindReplaceHexEdit(CWnd *pWindow, bool replace, bool all);
};

#endif
