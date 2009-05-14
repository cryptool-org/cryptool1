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
