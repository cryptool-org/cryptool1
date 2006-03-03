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

// DlgFindAndReplace.cpp

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgFindAndReplace.h"

// global vector for previously used FIND terms
std::vector<CString> termsFind;
// global vector for previously used REPLACE terms
std::vector<CString> termsReplace;

IMPLEMENT_DYNAMIC(CDlgFindAndReplace, CDialog)
CDlgFindAndReplace::CDlgFindAndReplace(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFindAndReplace::IDD, pParent)
	, textFind(_T(""))
	, textReplace(_T(""))
	, checkCaseSensitive(FALSE)
	, checkFindBackwards(FALSE)
	, checkRegularExpressions(FALSE)
	, created(FALSE)
{
}

CDlgFindAndReplace::~CDlgFindAndReplace()
{
}

void CDlgFindAndReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_FIND, textFind);
	DDX_CBString(pDX, IDC_COMBO_REPLACE, textReplace);
	DDX_Check(pDX, IDC_CHECK_CASE_SENSITIVE, checkCaseSensitive);
	DDX_Check(pDX, IDC_CHECK_FIND_BACKWARDS, checkFindBackwards);
	DDX_Check(pDX, IDC_CHECK_REGULAR_EXPRESSIONS, checkRegularExpressions);
	DDX_Control(pDX, IDC_COMBO_FIND, comboBoxControlFind);
	DDX_Control(pDX, IDC_COMBO_REPLACE, comboBoxControlReplace);
}


BEGIN_MESSAGE_MAP(CDlgFindAndReplace, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_REPLACE, OnBnClickedButtonReplace)
	ON_BN_CLICKED(IDC_BUTTON_REPLACE_ALL, OnBnClickedButtonReplaceAll)
END_MESSAGE_MAP()


// CDlgFindAndReplace message handlers

void CDlgFindAndReplace::OnBnClickedButtonFind()
{
	UpdateData(true);
	// store find term
	addFindTerm(textFind);

	// TODO: **FIND**
}

void CDlgFindAndReplace::OnBnClickedButtonReplace()
{
	UpdateData(true);
	// store find and replace terms
	addFindTerm(textFind);
	addReplaceTerm(textReplace);

	// TODO: **FIND AND REPLACE**
}

void CDlgFindAndReplace::OnBnClickedButtonReplaceAll()
{
	UpdateData(true);
	// store find and replace terms
	addFindTerm(textFind);
	addReplaceTerm(textReplace);

	// TODO: **FIND AND REPLACE ALL**
}

// add FIND term to vector (no doubled entries)
void CDlgFindAndReplace::addFindTerm(CString _term)
{
	// look for existing entries...
	for(unsigned int i=0; i<termsFind.size(); i++)
		if(termsFind[i] == _term) return;
	// ...or insert new one
	termsFind.push_back(_term);
}

// add REPLACE term to vector (no doubled entries)
void CDlgFindAndReplace::addReplaceTerm(CString _term)
{
	// look for existing entries...
	for(unsigned int i=0; i<termsReplace.size(); i++)
		if(termsReplace[i] == _term) return;
	// ...or insert new one
	termsReplace.push_back(_term);
}

BOOL CDlgFindAndReplace::OnInitDialog()
{
	CDialog::OnInitDialog();

	insertOldFindAndReplaceTerms();

	return TRUE;
}

void CDlgFindAndReplace::insertOldFindAndReplaceTerms()
{
	// remove former entries in both boxes
	comboBoxControlFind.ResetContent();
	comboBoxControlReplace.ResetContent();

	// insert former FIND terms into combo box...
	for(unsigned int i=0; i<termsFind.size(); i++)
		comboBoxControlFind.InsertString(-1, termsFind[i]);
	// insert former REPLACE terms into combo box...
	for(unsigned int j=0; j<termsReplace.size(); j++)
		comboBoxControlReplace.InsertString(-1, termsReplace[j]);

	// select the last FIND term in the combox box
	if(termsFind.size() > 0) comboBoxControlFind.SelectString(-1, termsFind[termsFind.size()-1]);
    // select the last REPLACE term in the combo box
	if(termsReplace.size() > 0) comboBoxControlReplace.SelectString(-1, termsReplace[termsReplace.size()-1]);
}

void CDlgFindAndReplace::show()
{
	if(!created)
	{
		Create(IDD_FIND_AND_REPLACE);
		created = true;
	}

	insertOldFindAndReplaceTerms();

	ShowWindow(SW_SHOW);
}

void CDlgFindAndReplace::OnCancel() 
{
	ShowWindow(SW_HIDE);
}