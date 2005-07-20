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

// DlgAutoSubstitutionAnalysisAlgorithmChoice.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "DlgAutoSubstitutionAnalysisAlgorithmChoice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAutoSubstitutionAnalysisAlgorithmChoice 


CDlgAutoSubstitutionAnalysisAlgorithmChoice::CDlgAutoSubstitutionAnalysisAlgorithmChoice(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAutoSubstitutionAnalysisAlgorithmChoice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAutoSubstitutionAnalysisAlgorithmChoice)
	m_algChoice = 1;
	//}}AFX_DATA_INIT
}


void CDlgAutoSubstitutionAnalysisAlgorithmChoice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAutoSubstitutionAnalysisAlgorithmChoice)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAutoSubstitutionAnalysisAlgorithmChoice, CDialog)
	//{{AFX_MSG_MAP(CDlgAutoSubstitutionAnalysisAlgorithmChoice)
	ON_BN_CLICKED(IDC_ALG_DIGRAM, OnAlgDigram)
	ON_BN_CLICKED(IDC_ALG_WORD, OnAlgWord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgAutoSubstitutionAnalysisAlgorithmChoice 

void CDlgAutoSubstitutionAnalysisAlgorithmChoice::OnAlgDigram() 
{
	m_algChoice = 1;
	CheckRadioButton (IDC_ALG_DIGRAM, IDC_ALG_WORD, IDC_ALG_DIGRAM);
}

void CDlgAutoSubstitutionAnalysisAlgorithmChoice::OnAlgWord() 
{
	m_algChoice = 2;
	CheckRadioButton (IDC_ALG_DIGRAM, IDC_ALG_WORD, IDC_ALG_WORD);
}

int CDlgAutoSubstitutionAnalysisAlgorithmChoice::DoModal() 
{
	return CDialog::DoModal();
}

BOOL CDlgAutoSubstitutionAnalysisAlgorithmChoice::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CheckRadioButton (IDC_ALG_DIGRAM, IDC_ALG_WORD, IDC_ALG_DIGRAM);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
