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

// DlgOptionsStartoptions.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"

#include "DlgOptionsStartoptions.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsStartoptions 


CDlgOptionsStartoptions::CDlgOptionsStartoptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsStartoptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsStartoptions)
	m_how_to_start = FALSE;
	m_sample_text_file = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsStartoptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsStartoptions)
	DDX_Check(pDX, IDC_CHECK1, m_how_to_start);
	DDX_Check(pDX, IDC_CHECK2, m_sample_text_file);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsStartoptions, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsStartoptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgOptionsStartoptions 

BOOL CDlgOptionsStartoptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS_OPTIONS, "StartingOptions" ) == ERROR_SUCCESS )
	{
		unsigned long u_how_to_start = 1, u_flagSampleTextFile = 0;
		CT_READ_REGISTRY_DEFAULT(u_how_to_start, "NoTipps", u_how_to_start);
		CT_READ_REGISTRY_DEFAULT(u_flagSampleTextFile, "SampleTextFile", u_flagSampleTextFile);

		UpdateData(true);
		m_how_to_start = (u_how_to_start) ? 0 : 1;
		m_sample_text_file = u_flagSampleTextFile;	
		UpdateData(false);

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgOptionsStartoptions::OnOK() 
{
	UpdateData(true);
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS_OPTIONS, "StartingOptions" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(!m_how_to_start), "NoTipps");
		CT_WRITE_REGISTRY(unsigned long(m_sample_text_file), "SampleTextFile");

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

	CDialog::OnOK();
}
