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

// DlgAutoSubstitutionAnalysis.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "DlgAutoSubstitutionAnalysis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAutoSubstitutionAnalysis 


CDlgAutoSubstitutionAnalysis::CDlgAutoSubstitutionAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAutoSubstitutionAnalysis::IDD, pParent)
{
	LoadString(AfxGetInstanceHandle(), IDS_MONO_SUBST_AUTO_STAT_ANALYSIS_IS_RUNNING, pc_str, STR_LAENGE_STRING_TABLE);

	m_space_in_alphabet = false;
	m_manual_analysis = false;
	m_threadFinished = false;
	m_threadFailed = false;
	m_guiFinished = false;
	m_changed = false;

	//{{AFX_DATA_INIT(CDlgAutoSubstitutionAnalysis)
	m_language_info = _T("");
	m_key = _T("");
	m_text = _T(pc_str);
	m_ref_file = _T(theApp.TextOptions.getReferenceFile());
	m_character_number = _T("0");
	//}}AFX_DATA_INIT
}


void CDlgAutoSubstitutionAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAutoSubstitutionAnalysis)
	DDX_Text(pDX, IDC_SUBST_LANGINFO, m_language_info);
	DDX_Text(pDX, IDC_SUBST_KEY, m_key);
	DDX_Text(pDX, IDC_SUBST_TEXT, m_text);
	DDX_Text(pDX, IDC_SUBST_REFFILE, m_ref_file);
	DDX_Text(pDX, IDC_SUBST_CHINFO, m_character_number);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAutoSubstitutionAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgAutoSubstitutionAnalysis)
	ON_BN_CLICKED(ID_SUBST_Cancel, OnSUBSTCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_COPY, OnKeyCopy)
	ON_BN_CLICKED(IDC_MANUAL, OnManualAnalysis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************************************************
 Data exchange routines
****************************************************/

void CDlgAutoSubstitutionAnalysis::setText(char *text)
{
	CSingleLock sl(&sync);
	sl.Lock();
	m_changed = true;
	m_text.Format(_T("%s"), text);
	if (sl.IsLocked())
		sl.Unlock();
}

CString CDlgAutoSubstitutionAnalysis::getText()
{
	CString ret;
	CSingleLock sl(&sync);
	sl.Lock();
	ret = m_text;
	if (sl.IsLocked())
		sl.Unlock();

	return ret;
}

void CDlgAutoSubstitutionAnalysis::setLanguageInfo(char *text)
{
	CSingleLock sl(&sync);
	sl.Lock();
	m_changed = true;
	m_language_info = _T(text);
	if (sl.IsLocked())
		sl.Unlock();
}

void CDlgAutoSubstitutionAnalysis::setKey(char *text)
{
	CSingleLock sl(&sync);
	sl.Lock();
	m_changed = true;
	m_key = _T(text);
	if (sl.IsLocked())
		sl.Unlock();
}

CString CDlgAutoSubstitutionAnalysis::getKey()
{
	CString ret;
	CSingleLock sl(&sync);
	sl.Lock();
	ret = m_key;
	if (sl.IsLocked())
		sl.Unlock();

	return ret;
}

void CDlgAutoSubstitutionAnalysis::setCharacterNumber(char *text)
{
	CString ret;
	CSingleLock sl(&sync);
	sl.Lock();
	m_changed = true;
	m_character_number = _T(text);
	if (sl.IsLocked())
		sl.Unlock();
}

void CDlgAutoSubstitutionAnalysis::setSpaceInAlphabet(bool value)
{
	CString ret;
	CSingleLock sl(&sync);
	sl.Lock();
	m_space_in_alphabet = value;
	if (sl.IsLocked())
		sl.Unlock();
}

void CDlgAutoSubstitutionAnalysis::setThreadFinished(bool value)
{
	CSingleLock sl(&sync);
	sl.Lock();
	m_threadFinished = value;
	if (sl.IsLocked())
		sl.Unlock();
}

bool CDlgAutoSubstitutionAnalysis::getThreadFinished()
{
	bool ret;

	CSingleLock sl(&sync);
	sl.Lock();
	ret = m_threadFinished;
	if (sl.IsLocked())
		sl.Unlock();

	return ret;
}
	
void CDlgAutoSubstitutionAnalysis::setGuiFinished(bool value)
{
	CSingleLock sl(&sync);
	sl.Lock();
	m_guiFinished = value;
	if (sl.IsLocked())
		sl.Unlock();
}

bool CDlgAutoSubstitutionAnalysis::getGuiFinished()
{
	bool ret;
	CSingleLock sl(&sync);
	sl.Lock();
	ret = m_guiFinished;
	if (sl.IsLocked())
		sl.Unlock();

	return ret;
}

void CDlgAutoSubstitutionAnalysis::setThreadFailed(bool value)
{
	CSingleLock sl(&sync);
	sl.Lock();
	m_threadFailed = value;
	if (sl.IsLocked())
		sl.Unlock();
}

bool CDlgAutoSubstitutionAnalysis::getThreadFailed()
{
	bool ret;
	CSingleLock sl(&sync);
	sl.Lock();
	ret = m_threadFailed;
	if (sl.IsLocked())
		sl.Unlock();

	return ret;
}


bool CDlgAutoSubstitutionAnalysis::getManualAnalysis()
{
	bool ret;
	CSingleLock sl(&sync);
	sl.Lock();
	ret = m_manual_analysis;
	if (sl.IsLocked())
		sl.Unlock();

	return ret;
}


/***************************************************
 Event handling routines
****************************************************/

BOOL CDlgAutoSubstitutionAnalysis::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_timerDisplay =  SetTimer(13,300,NULL);
	return FALSE;
}

void CDlgAutoSubstitutionAnalysis::OnSUBSTCancel() 
{
	CSingleLock sl(&sync);
	sl.Lock();
	m_guiFinished = true;
	if (sl.IsLocked())
		sl.Unlock();
	CDialog::OnCancel();
}

void CDlgAutoSubstitutionAnalysis::OnOK() 
{
	CSingleLock sl(&sync);
	sl.Lock();
	m_guiFinished = true;
	if (sl.IsLocked())
		sl.Unlock();
	CDialog::OnOK();
}

void CDlgAutoSubstitutionAnalysis::OnTimer(UINT nIDEvent) 
{
	CSingleLock sl(&sync);
	sl.Lock();
	if (m_changed)
	{
		UpdateData(FALSE);
		UpdateWindow();
		m_changed = false;
	}
	if (sl.IsLocked())
		sl.Unlock();
	
	CWnd::OnTimer(nIDEvent);
}

void CDlgAutoSubstitutionAnalysis::OnKeyCopy() 
{
	// Test whether the clipboard can be opened
	if (OpenClipboard())
	{
		// Empty the Clipboard
		EmptyClipboard();

		// Allocate the global memory for data
		HGLOBAL hClipboardData;
		hClipboardData = GlobalAlloc(GMEM_DDESHARE, m_key.GetLength()+1);
		char * pchData;
		pchData = (char*)GlobalLock(hClipboardData);

		// copy data to the global memory.
		strcpy(pchData, LPCSTR(m_key));

		// Unlock the memory but don't call GlobalFree
		GlobalUnlock(hClipboardData);
			  
		// Set the Clipboard data
		SetClipboardData(CF_TEXT,hClipboardData);

		// Close the Clipboard
		CloseClipboard();
	}	
}

void CDlgAutoSubstitutionAnalysis::OnManualAnalysis() 
{
	if (m_space_in_alphabet)
	{
		LoadString(AfxGetInstanceHandle(), IDS_MONO_SUBST_AUTO_MANUAL_ANALYSIS_NOT_POSS, pc_str, STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
	}
	else
	{
		CSingleLock sl(&sync);
		sl.Lock();
		m_guiFinished = true;
		m_manual_analysis = true;
		if (sl.IsLocked())
			sl.Unlock();
		CDialog::OnOK();
	}
}
