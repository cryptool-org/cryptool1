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


// DlgRandParameter_x2_mod_N.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgX2ModNRandomParamater.h"
#include "IntegerArithmetic.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgX2ModNRandomParamater 


CDlgX2ModNRandomParamater::CDlgX2ModNRandomParamater(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgX2ModNRandomParamater::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgX2ModNRandomParamater)
	m_EditModul_N = _T("");
	//}}AFX_DATA_INIT
}


void CDlgX2ModNRandomParamater::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgX2ModNRandomParamater)
	DDX_Control(pDX, IDC_EDIT1, m_Control_Edit_Modul_N);
	DDX_Text(pDX, IDC_EDIT1, m_EditModul_N);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgX2ModNRandomParamater, CDialog)
	//{{AFX_MSG_MAP(CDlgX2ModNRandomParamater)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgX2ModNRandomParamater 

void CDlgX2ModNRandomParamater::SetModul(CString &NStr)
{
	m_EditModul_N = NStr;
}

CString CDlgX2ModNRandomParamater::GetModul()
{
	return m_EditModul_N;
}

void CDlgX2ModNRandomParamater::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	BOOL NumberIsOK;
	int     ndx;
	UpdateData(TRUE);
	{ 
		CString upnStr;
		NumberIsOK = EvalFormula(m_EditModul_N, ndx);
	}
	UpdateData(FALSE);
	if ( !NumberIsOK )
	{
		// ********* Fehlermeldung
		if (ndx == -1)
		{
			Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
			m_Control_Edit_Modul_N.SetSel(0,-1);
			m_Control_Edit_Modul_N.SetFocus();
		}
		else
		{
			Message(IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
			m_Control_Edit_Modul_N.SetSel(ndx-1,-1);
			m_Control_Edit_Modul_N.SetFocus();
		}
		return;
	}
	Big tmp; 
	CStringFormulaToBig( m_EditModul_N, tmp );
	if (tmp < 2) {
		Message(IDS_STRING_GE_2, MB_ICONINFORMATION);
		//m_Control_Edit_Modul_N.SetSel(0,-1);
		m_Control_Edit_Modul_N.SetFocus();
		return;
	}
	CDialog::OnOK();
}


