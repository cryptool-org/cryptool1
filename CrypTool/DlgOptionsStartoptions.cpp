/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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
// Behandlungsroutinen f�r Nachrichten CDlgOptionsStartoptions 

BOOL CDlgOptionsStartoptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_READ ) == ERROR_SUCCESS )
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
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void CDlgOptionsStartoptions::OnOK() 
{
	UpdateData(true);
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE ) == ERROR_SUCCESS )
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
