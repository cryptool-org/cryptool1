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


// DlgOptionsStartoptions.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"

#include "DlgOptionsStartoptions.h"

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
	
	UpdateData(true);
	m_how_to_start = !int(theApp.GetProfileInt("Settings", "NoTipps", FALSE));
	m_sample_text_file = int(theApp.GetProfileInt("Settings", "SampleTextFile", FALSE));	
	UpdateData(false);
	// TODO: Zusätzliche Initialisierung hier einfügen
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgOptionsStartoptions::OnOK() 
{
	UpdateData(true);
	theApp.WriteProfileInt("Settings","NoTipps", int(!m_how_to_start));
	theApp.WriteProfileInt("Settings","SampleTextFile", int(m_sample_text_file));
	UpdateData(false);
	
	CDialog::OnOK();
}
