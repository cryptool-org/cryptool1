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


// DlgEntropyInfo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgEntropyInfo.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgEntropyInfo 


CDlgEntropyInfo::CDlgEntropyInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEntropyInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEntropyInfo)
	m_alphabet_info = _T("");
	m_entropy_info = _T("");
	//}}AFX_DATA_INIT
}


void CDlgEntropyInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEntropyInfo)
	DDX_Control(pDX, IDC_ENTROPY_INFO, m_ctrl_entropy_info);
	DDX_Control(pDX, IDC_ALPHABET_INFO, m_ctrl_alphabet_info);
	DDX_Text(pDX, IDC_ALPHABET_INFO, m_alphabet_info);
	DDX_Text(pDX, IDC_ENTROPY_INFO, m_entropy_info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEntropyInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgEntropyInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgEntropyInfo 

BOOL CDlgEntropyInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString title;
	title.Format(IDS_ENTROPY_TITLE,m_oldtitle);
	SetWindowText((LPCTSTR)title);

	LOGFONT logFont;
	CFont   m_font;
	logFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	m_font.CreateFontIndirect( &logFont ); // Font initialisieren
	m_ctrl_entropy_info.SetFont(&m_font);

	UpdateData();
	if ( i_countAlphabet < 256 )
	{
		if (i_characters < i_countAlphabet)
			m_alphabet_info.Format(IDS_ENTROPY_ALPHABET_INFO,i_characters, i_countAlphabet);
		else
			m_alphabet_info.Format(IDS_ENTROPY_ALPHABET_MAX_INFO, i_countAlphabet);
	}
	else
	{
		if (i_characters < i_countAlphabet)
			m_alphabet_info.Format(IDS_BINARY_ENTROPY_ALPHABET_INFO,i_characters, i_countAlphabet);
		else
			m_alphabet_info.Format(IDS_BINARY_ENTROPY_ALPHABET_MAX_INFO, i_countAlphabet);
		
	}
	
	char str_d_entropy[20], str_d_maxEntropy[20];
	double_fmt(d_entropy, str_d_entropy, 2);
	double_fmt(d_maxEntropy, str_d_maxEntropy, 2);
	m_entropy_info.Format(IDS_ENTROPY_INFO,str_d_entropy, str_d_maxEntropy);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
