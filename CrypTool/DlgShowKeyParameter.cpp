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


// DLG_param.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowKeyParameter.h"
#include "DlgHybridEncryptionDemo.h"
#include "s_ecconv.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKeyParameter 


CDlgShowKeyParameter::CDlgShowKeyParameter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowKeyParameter::IDD, pParent)
{
	m_entries=0;
	//{{AFX_DATA_INIT(CDlgShowKeyParameter)
	m_radio = 1;
	m_titel = _T("");
	//}}AFX_DATA_INIT
	disableOkButton = false;
}


void CDlgShowKeyParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowKeyParameter)
	DDX_Control(pDX, IDOK, m_ctrlOK);
	DDX_Control(pDX, IDC_LIST, m_listctrl);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Text(pDX, IDC_TITEL, m_titel);
	DDV_MaxChars(pDX, m_titel, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowKeyParameter, CDialog)
	//{{AFX_MSG_MAP(CDlgShowKeyParameter)
	ON_BN_CLICKED(IDC_RADIO1, OnUpdate)
	ON_BN_CLICKED(IDC_RADIO2, OnUpdate)
	ON_BN_CLICKED(IDC_RADIO3, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowKeyParameter 

void CDlgShowKeyParameter::OnUpdate() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateListBox();
}

void CDlgShowKeyParameter::addentry(char *bez,L_NUMBER *num)
{
	strcpy(m_data[m_entries].titel,bez);
	memcpy(m_data[m_entries].data,num,MAXLGTH*sizeof(L_NUMBER));
	m_entries++;
}

void CDlgShowKeyParameter::settitel(char *a)
{
	m_titel=a;
}

void CDlgShowKeyParameter::UpdateListBox()
{
	int i;
	
	UpdateData(TRUE);
	for (i=0;i<m_entries;i++)
	{
		char *a;

		switch (m_radio)
		{
		case 0:
			ln_to_string(m_data[i].data,&a,8);
			break;
		case 1:
			ln_to_string(m_data[i].data,&a,10);
			break;
		case 2:
			ln_to_string(m_data[i].data,&a,16);
			break;
		}
		m_listctrl.SetItemText(i,1,a);
		free(a);
	}
	UpdateData(FALSE);
}

BOOL CDlgShowKeyParameter::OnInitDialog() 
{
	int i;
	CDialog::OnInitDialog();

	m_listctrl.DeleteAllItems();
	LoadString(AfxGetInstanceHandle(),IDS_STRING_VARIABLE,pc_str,STR_LAENGE_STRING_TABLE);
	m_listctrl.InsertColumn(0,pc_str,LVCFMT_RIGHT,50,0);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_VALUE,pc_str,STR_LAENGE_STRING_TABLE);
	m_listctrl.InsertColumn(1,pc_str,LVCFMT_LEFT,375,1);

	//disableOKButton wird in CDlgHybridEncryptionDemo auf true gesetzt.
	//dieser Abschnitt modifiziert den Dialog für die Anzeige bei der
	//Hybridverschlüsselung
    if(disableOkButton)
	{
		CDlgHybridEncryptionDemo dlg;
		m_ctrlOK.ShowWindow(false);
		SetWindowText(m_Title);
	}

	for (i=0;i<m_entries;i++)
		m_listctrl.InsertItem(i,m_data[i].titel);
	disableOkButton = false;
	UpdateListBox();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
} 