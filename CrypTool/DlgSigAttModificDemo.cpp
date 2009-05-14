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

// DlgSigAttModificDemo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSigAttModificDemo.h"
#include "FileTools.h"
#include "ModifiedDocumentForHashing.h"
#include "ModifiedDocument_Blanks.h"
#include "ModifiedDocument_Attachments.h"
#include "BitParity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSigAttModificDemo 


CDlgSigAttModificDemo::CDlgSigAttModificDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSigAttModificDemo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSigAttModificDemo)
	m_hashvalue = _T("");
	m_sigbit = 0;
	m_method = 0;
	m_printable = 0;
	m_parity = 0;
	m_run = _T("");
	//}}AFX_DATA_INIT
}


void CDlgSigAttModificDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSigAttModificDemo)
	DDX_Control(pDX, IDC_COMBO1, m_control_run);
	DDX_Control(pDX, IDC_METHOD, m_control_method);
	DDX_Control(pDX, IDC_RADIO4, m_control_unprintable);
	DDX_Control(pDX, IDC_RADIO3, m_control_printable);
	DDX_Control(pDX, IDC_CHECK2, m_control_double);
	DDX_Control(pDX, IDC_CHECK1, m_control_eol);
	DDX_Control(pDX, IDC_HASHVALUE, m_control_hashvalue);
	DDX_Text(pDX, IDC_HASHVALUE, m_hashvalue);
	DDX_Text(pDX, IDC_SIGBIT, m_sigbit);
	DDX_Radio(pDX, IDC_METHOD, m_method);
	DDX_Radio(pDX, IDC_RADIO3, m_printable);
	DDX_Text(pDX, IDC_PARITY, m_parity);
	DDV_MinMaxInt(pDX, m_parity, 0, 1);
	DDX_CBString(pDX, IDC_COMBO1, m_run);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSigAttModificDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgSigAttModificDemo)
	ON_BN_CLICKED(IDOK, OnModify)
	ON_BN_CLICKED(IDC_RADIO2, OnAttachment)
	ON_BN_CLICKED(IDC_METHOD, OnMethod)
	ON_BN_CLICKED(IDC_RADIO3, OnPrintable)
	ON_BN_CLICKED(IDC_RADIO4, OnUnprintable)
	ON_EN_UPDATE(IDC_HASHVALUE, OnUpdateHashvalue)
	ON_EN_UPDATE(IDC_SIGBIT, OnUpdateSigbit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSigAttModificDemo 

void CDlgSigAttModificDemo::OnModify() 
{
	UpdateData(TRUE);

	CAppDocument *NewDocument;
	char outfile[1024];
	CString msg;
	ifstream ifstr_Document;
	ofstream ofstr_Document;
	int ii, DocumentLength, HashValueHexLength, HashValueByteLength, RunNo, temp;
	struct stat stat_object;

	if (FALSE == m_hashvalue.IsEmpty())
	{
		for (ii = 0; ii < m_hashvalue.GetLength(); ii ++)
		{
			if (!(m_hashvalue[ii] >= '0' && m_hashvalue[ii] <= '9'
				|| m_hashvalue[ii] >= 'a' && m_hashvalue[ii] <= 'f'
				|| m_hashvalue[ii] >= 'A' && m_hashvalue[ii] <= 'F'))
			{
				m_hashvalue.Delete(ii, 1);
				return;
			}
		}
	}

	if (0 == m_method && 1 != m_control_eol.GetCheck() && 1 != m_control_double.GetCheck())
	{
		msg.Format(IDS_STRING_SIG_ATT_NO_CHECK);
		MessageBox(msg, "CrypTool", MB_ICONEXCLAMATION | MB_APPLMODAL);
		m_control_eol.SetCheck(1);

		return;
	}

	ifstr_Document.open(m_Path, ios::in | ios::binary);
	if (!ifstr_Document)
	{
		return;
	}
	
	stat((const char *) m_Path, & stat_object);
	if (0 == stat_object.st_size)
	{
		return;
	}
	DocumentLength = stat_object.st_size;

#ifdef _SIG_ATT_SPEED_INCREMENT

	DocumentLength += 2;

#endif

	char *Text= new char[DocumentLength];

	ii = 0;
	while (0 == ifstr_Document.eof())
	{
		ifstr_Document.read(Text + ii, 1);
		ii ++;
	}
	ifstr_Document.close();

	ModifiedDocumentForHashing *m_Document;
	if (!m_method)
	{
		m_Document = new ModifiedDocument_Blanks(Text, DocumentLength, m_sigbit,
			m_control_eol.GetCheck(), m_control_double.GetCheck());
	}
	else
	{
		m_Document = new ModifiedDocument_Attachments(Text, DocumentLength + 2, m_sigbit, m_printable);
	}

	HashValueHexLength = m_hashvalue.GetLength();
	HashValueByteLength = (HashValueHexLength + 1) / 2;	
	char *HashValue = new char[HashValueByteLength];

	for (ii = 0; ii < HashValueHexLength; ii ++)
	{
		if (0 == ii % 2)
		{
			temp = 16 * HexCharToInt(m_hashvalue[ii]);
		}
		else
		{
			temp += HexCharToInt(m_hashvalue[ii]);
			HashValue[(ii - 1) / 2] = temp;
		}
	}

	if (0 != HashValueHexLength % 2)
	{
		HashValue[HashValueByteLength - 1] = 16 * HexCharToInt(m_hashvalue[HashValueHexLength - 1]);
	}


	if (TRUE == m_run.IsEmpty())
	{
		return;
	}

	m_run.Delete(2,1);
	RunNo = atoi(m_run) - 1;
	m_Document->ModifyOriginalDocument(RunNo);
	m_Document->ModifyDocument(HashValue);

	GetTmpName(outfile,"cry",".tmp");
	ofstr_Document.open(outfile, ios::out | ios::binary);
	if (!ofstr_Document)
	{
		return;
	}
	ofstr_Document.write(m_Document->GetDocumentData(), m_Document->GetDocumentLength());
	ofstr_Document.close();
	NewDocument = theApp.OpenDocumentFileNoMRU(outfile);
	
	char title[1024];
	_snprintf(title, sizeof(title) - 1, "Modifikation von <%s>", m_Title);
	NewDocument->SetTitle(title);

	delete m_Document;
	delete []HashValue;
}

void CDlgSigAttModificDemo::OnAttachment() 
{
	m_method = 1;	

	m_control_eol.EnableWindow(FALSE);
	m_control_double.EnableWindow(FALSE);
	m_control_printable.EnableWindow(TRUE);
	m_control_unprintable.EnableWindow(TRUE);
	m_control_run.EnableWindow(TRUE);

	UpdateData(FALSE);
}

void CDlgSigAttModificDemo::OnMethod() 
{
	m_method = 0;

	m_control_eol.EnableWindow(TRUE);
	m_control_double.EnableWindow(TRUE);
	m_control_printable.EnableWindow(FALSE);
	m_control_unprintable.EnableWindow(FALSE);
	m_control_run.EnableWindow(FALSE);
	
	UpdateData(FALSE);	
}

void CDlgSigAttModificDemo::OnPrintable() 
{
	m_printable = 0;	
}

void CDlgSigAttModificDemo::OnUnprintable() 
{
	m_printable = 1;	
}

void CDlgSigAttModificDemo::OnUpdateHashvalue() 
{
	UpdateData(TRUE);
	CalculateParity();
	UpdateData(FALSE);
}

void CDlgSigAttModificDemo::SetData(char *Path, const CString &Title)
{
	m_Path = Path;
	m_Title = Title;
}

int CDlgSigAttModificDemo::HexCharToInt(const char C) const
{
	if (C >= '0' && C <= '9')
	{
		return (C - 48);
	}

	else if (C >= 'A' && C <= 'F')
	{
		return (C - 55);
	}

	else if (C >= 'a' && C <= 'f')
	{
		return (C - 87);
	}

	return 0;
}

void CDlgSigAttModificDemo::OnUpdateSigbit() 
{
	UpdateData(TRUE);
	CalculateParity();
	UpdateData(FALSE);
}

void CDlgSigAttModificDemo::CalculateParity()
{
	char *String;
	int ii, temp, HashValueByteLength, HashValueHexLength;

	HashValueHexLength = m_hashvalue.GetLength();
	HashValueByteLength = (HashValueHexLength + 1) / 2;	

	if (HashValueHexLength * 4 < m_sigbit || 0 == HashValueByteLength)
	{
		return;
	}

	String = new char[HashValueByteLength];

	for (ii = 0; ii < HashValueHexLength; ii ++)
	{
		if (0 == ii % 2)
		{
			temp = 16 * HexCharToInt(m_hashvalue[ii]);
		}
		else
		{
			temp += HexCharToInt(m_hashvalue[ii]);
			String[(ii - 1) / 2] = temp;
		}
	}

	if (0 != HashValueHexLength % 2)
	{
		String[HashValueByteLength - 1] = 16 * HexCharToInt(m_hashvalue[HashValueHexLength - 1]);
	}

	BitParity BP;
	m_parity = BP.GetParity(String, m_sigbit);
}

BOOL CDlgSigAttModificDemo::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_control_eol.EnableWindow(TRUE);
	m_control_eol.SetCheck(1);
	m_control_double.EnableWindow(TRUE);
	m_control_double.SetCheck(1);
	m_control_printable.EnableWindow(FALSE);
	m_control_unprintable.EnableWindow(FALSE);
	m_control_run.EnableWindow(FALSE);
	
	UpdateData(FALSE);
	
	return TRUE;
}
