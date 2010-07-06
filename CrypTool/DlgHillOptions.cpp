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

// DlgHillOptions.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgHillOptions.h"
#include ".\dlghilloptions.h"
#include "CrypToolTools.h"

// DlgHillOptions dialog
void DlgHillOptions::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_EDIT2, m_ownCharForPadding);
}

BEGIN_MESSAGE_MAP(DlgHillOptions, CDialog)
	ON_BN_CLICKED(IDOK,        OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1,  OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2,  OnBnClickedRadio2)
	ON_EN_CHANGE (IDC_EDIT2,   OnEnChangeEdit2)
   ON_BN_CLICKED(IDC_RADIO3, &DlgHillOptions::OnBnClickedOffset0)
   ON_BN_CLICKED(IDC_RADIO4, &DlgHillOptions::OnBnClickedOffset1)
END_MESSAGE_MAP()



IMPLEMENT_DYNAMIC(DlgHillOptions, CDialog)
DlgHillOptions::DlgHillOptions(CWnd* pParent /*=NULL*/)
	: CDialog(DlgHillOptions::IDD, pParent)
	, m_ownCharForPadding(_T(""))
   , m_offset(0)
{
}

DlgHillOptions::~DlgHillOptions()
{
}

void DlgHillOptions::readRegistry()
{
	m_offset             = 0;
	useFirstCharFromAlph = 1;

   if(CT_OPEN_REGISTRY_SETTINGS(KEY_READ, IDS_REGISTRY_SETTINGS, "Hill") == ERROR_SUCCESS)
	{
		CT_READ_REGISTRY_DEFAULT(m_offset, "OrdChrOffset", 0);
		CT_READ_REGISTRY_DEFAULT(useFirstCharFromAlph, "PaddingDefaultChr", 1);

      if ( theApp.TextOptions.getAlphabet().GetLength() )
      {
	      unsigned long u_length = 2; 
	      char cFirstCharFromAlph[3];
	      CT_READ_REGISTRY_DEFAULT(cFirstCharFromAlph,"PaddingOwnChr",theApp.TextOptions.getAlphabet().Mid(0,1).GetBuffer(), u_length);
	      m_ownCharForPadding = cFirstCharFromAlph;
      }
		else
		{
			m_ownCharForPadding = _T("A");
		}
		CT_CLOSE_REGISTRY();
	}

   if ( m_ownCharForPadding.GetLength() != 1 )
      m_ownCharForPadding = theApp.TextOptions.getAlphabet().Mid(0,1);
}

void DlgHillOptions::writeRegistry()
{
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "Hill" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(m_offset), "OrdChrOffset");
		CT_WRITE_REGISTRY(unsigned long(useFirstCharFromAlph), "PaddingDefaultChr");
		CT_WRITE_REGISTRY(m_ownCharForPadding,"PaddingOwnChr");
		CT_CLOSE_REGISTRY();
	}
}

BOOL DlgHillOptions::OnInitDialog()
{
   readRegistry();
   UpdateData(FALSE);
	CheckRadioButton( IDC_RADIO3, IDC_RADIO4, ( m_offset ) ? IDC_RADIO4 : IDC_RADIO3 );
   GetDlgItem( IDC_EDIT1 )->SetWindowTextA( theApp.TextOptions.getAlphabet().Mid(0,1) );

	if(useFirstCharFromAlph == 1)
	{
		CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	}
	if(useFirstCharFromAlph == 0)
	{
		CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	}

	return TRUE;
}

void DlgHillOptions::OnBnClickedOk()
{
   if ( !m_ownCharForPadding.GetLength() )
   {
      // FIXME HK --> NOTIFICATION
      m_ownCharForPadding = theApp.TextOptions.getAlphabet().Mid(0,1);
   }
   writeRegistry();
   OnOK();
}

void DlgHillOptions::OnBnClickedRadio1()
{
   useFirstCharFromAlph = 1;
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
}

void DlgHillOptions::OnBnClickedRadio2()
{
	useFirstCharFromAlph = 0;
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->SetFocus();
}

void DlgHillOptions::OnEnChangeEdit2()
{
   int found = 0;
	UpdateData( TRUE );

   if ( m_ownCharForPadding.GetLength() > 1 )
      m_ownCharForPadding.Delete(1, m_ownCharForPadding.GetLength() - 1);
   char c = MyToUpper(m_ownCharForPadding[0]);
   for ( int i = 0; i<theApp.TextOptions.getAlphabet().GetLength(); i++)
      if ( c == theApp.TextOptions.getAlphabet()[i] )
      {
         found++;
         break;
      }
   if ( !found )
      m_ownCharForPadding = _T("");
   else
      m_ownCharForPadding = CString( c );

   UpdateData( FALSE );
}


void DlgHillOptions::OnBnClickedOffset0()
{
   m_offset = 0;
}

void DlgHillOptions::OnBnClickedOffset1()
{
   m_offset = 1;
}
