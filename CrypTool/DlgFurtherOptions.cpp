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


// DlgFurtherOptions.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgFurtherOptions.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFurtherOptions 


CDlgFurtherOptions::CDlgFurtherOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFurtherOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFurtherOptions)
	m_ShowIntroDialogue = FALSE;
	m_SCAKeyword = _T("");
	m_primeNumberSeparator = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFurtherOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFurtherOptions)
	DDX_Check(pDX, IDC_CHECK1, m_ShowIntroDialogue);
	DDX_Text(pDX, IDC_EDIT_SCAKEYWORD, m_SCAKeyword);
	DDX_Text(pDX, IDC_EDIT_PRIME_NUMBER_SEPARATOR, m_primeNumberSeparator);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFurtherOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgFurtherOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgFurtherOptions 

BOOL CDlgFurtherOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_READ, IDS_REGISTRY_SETTINGS, "DifieHellman" ) == ERROR_SUCCESS )
	{
		unsigned long u_Intro = (unsigned long)TRUE;
	
		CT_READ_REGISTRY(u_Intro, "ShowIntro");

		UpdateData();
		m_ShowIntroDialogue = u_Intro;
		UpdateData(FALSE);

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_READ, IDS_REGISTRY_SETTINGS, "SideChannelAttack" ) == ERROR_SUCCESS )
	{
		unsigned long u_length = 1024;
		char c_SCA_keyWord[1025] = "Alice";

		CT_READ_REGISTRY(c_SCA_keyWord, "Keyword", u_length);

		UpdateData();
		m_SCAKeyword = c_SCA_keyWord;
		UpdateData(FALSE);

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

	if(CT_OPEN_REGISTRY_SETTINGS(KEY_READ, IDS_REGISTRY_SETTINGS, "PrimeNumberGeneration") == ERROR_SUCCESS)
	{
		unsigned long u_length = 1024;
		char c_primeNumberSeparator[1025] = " ";

		CT_READ_REGISTRY(c_primeNumberSeparator, "Separator", u_length);

		UpdateData();
		m_primeNumberSeparator = c_primeNumberSeparator;
		UpdateData(FALSE);

		CT_CLOSE_REGISTRY();
	}
	else
	{

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CDlgFurtherOptions::OnOK() 
{
	UpdateData(true);


	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "DifieHellman" ) == ERROR_SUCCESS )
	{

		CT_WRITE_REGISTRY((unsigned long)m_ShowIntroDialogue, "ShowIntro");
		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

		if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "SideChannelAttack" ) == ERROR_SUCCESS )
	{

		if (m_SCAKeyword == "") 
			m_SCAKeyword = CString("Alice");	
		CT_WRITE_REGISTRY(m_SCAKeyword, "Keyword");
		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

	if(CT_OPEN_REGISTRY_SETTINGS(KEY_WRITE, IDS_REGISTRY_SETTINGS, "PrimeNumberGeneration") == ERROR_SUCCESS)
	{
		if(m_primeNumberSeparator == "")
			m_primeNumberSeparator = " ";
		CT_WRITE_REGISTRY(m_primeNumberSeparator, "Separator");
		CT_CLOSE_REGISTRY();
	}
	else
	{

	}

	UpdateData(FALSE);
	
	CDialog::OnOK();
}