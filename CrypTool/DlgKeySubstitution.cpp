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

//////////////////////////////////////////////////////////////////
// Programmiert von Christian Tobias
//////////////////////////////////////////////////////////////////
// Diese Quellcode-Datei enthält alle Funktionalitäten für
// die Dialogbox zur Auswahl der Analyseart bei
// monoalphabetischer Substitution.
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeySubstitution.h"
#include "Cryptography.h"
#include "KeyRepository.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define INIT_STRING ""

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeySubstitution 


CDlgKeySubstitution::CDlgKeySubstitution(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeySubstitution::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeySubstitution)
	m_edit = _T("");
	//}}AFX_DATA_INIT
}


void CDlgKeySubstitution::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeySubstitution)
	DDX_Control(pDX, IDC_EDIT1, m_edit2);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeySubstitution, CDialog)
	//{{AFX_MSG_MAP(CDlgKeySubstitution)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeySubstitution 

void CDlgKeySubstitution::OnDecrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_check = 1;
	OnOK();
}

void CDlgKeySubstitution::OnEncrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_check = 0;
	OnOK();
}



void CDlgKeySubstitution::OnChangeEdit1() 
{
	// TODO: Wenn es sich hierbei um ein RICHEDIT-Steuerelement handelt, sendet es
	// diese Benachrichtigung nur, wenn die Funktion CDialog::OnInitDialog()
	// überschrieben wird, um die EM_SETEVENTMASK-Nachricht an das Steuerelement
	// mit dem ENM_CHANGE-Attribut ORed in die Maske lParam zu senden.
	
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
		
	UpdateData(TRUE);

	int selStart;
	int selEnd;
	m_edit2.GetSel(selStart, selEnd);
	for (int i=0 ;i<m_edit.GetLength(); i++)
	{
		if ((m_edit[i]<'A')||(m_edit[i]>'Z'))
		{
				//Entfernen des fehlerhaften Zeichens.
				//Der Cursor wird anschließend an die Stelle gesetzt, an der das
				//fehlerhafte Zeichen stand.
				m_edit.Delete(i);
				selStart = selEnd = i;
				i--;		
		}
	}	

	UpdateData(FALSE);
	m_edit2.SetSel(selStart, selEnd);
}

BOOL CDlgKeySubstitution::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString Title;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
	Title = pc_str;
	VERIFY(m_Paste.AutoLoad(IDC_BUTTON2,this));
	if ( IsKeyEmpty( Title ))
	{
		m_Paste.EnableWindow(TRUE);
	}
	else
	{
		m_Paste.EnableWindow(FALSE);
	}

	// add tool tip to the paste button
	CString buttonPasteText;
	buttonPasteText.LoadString(IDS_STRING_PASTE_KEY_FROM_KEY_STORE);
	m_Paste.SetToolTipText(&buttonPasteText);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgKeySubstitution::OnPasteKey() 
{
	UpdateData(TRUE);

	CString Title;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
	PasteKey(pc_str,m_edit);
	UpdateData(FALSE);	
}
