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


// DlgRandParamICG.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgICGRandomParamater.h"
#include "IntegerArithmetic.h"
#include "DlgPrimesGeneratorDemo.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgICGRandomParamater 


CDlgICGRandomParamater::CDlgICGRandomParamater(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgICGRandomParamater::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgICGRandomParamater)
	m_Param_a = _T("22211");
	m_Param_b = _T("11926380");
	m_Param_N = _T("2147483053");
	m_PrimLang = 128;
	//}}AFX_DATA_INIT
}


void CDlgICGRandomParamater::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgICGRandomParamater)
	DDX_Control(pDX, IDC_STATIC_GPA, m_StaticGPA);
	DDX_Control(pDX, IDC_EDIT4, m_PrimLang_Ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_Param_NCtrl);
	DDX_Control(pDX, IDC_EDIT2, m_Param_bCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_Param_aCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_Param_a);
	DDX_Text(pDX, IDC_EDIT2, m_Param_b);
	DDX_Text(pDX, IDC_EDIT3, m_Param_N);
	DDX_Text(pDX, IDC_EDIT4, m_PrimLang);
	DDV_MinMaxUInt(pDX, m_PrimLang, 0, 256);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgICGRandomParamater, CDialog)
	//{{AFX_MSG_MAP(CDlgICGRandomParamater)
	ON_BN_CLICKED(IDC_STATIC_GPA, OnStaticGp_a)
	ON_BN_CLICKED(IDC_PRIMBUTTON, OnPrimbutton)
	ON_BN_CLICKED(IDC_STATIC_GPC, OnStaticGpc)
	ON_BN_CLICKED(IDC_STATIC_GPP, OnStaticGpp)
	ON_BN_CLICKED(IDC_STATIC_GPL, OnStaticGpl)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgICGRandomParamater 


void CDlgICGRandomParamater::OnStaticGp_a() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_Param_aCtrl.SetFocus();
}

void CDlgICGRandomParamater::OnStaticGpc() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(TRUE);
	m_Param_bCtrl.SetFocus();
	UpdateData(FALSE);
}

void CDlgICGRandomParamater::OnStaticGpp() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_Param_NCtrl.SetFocus();
}

void CDlgICGRandomParamater::OnStaticGpl() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_PrimLang_Ctrl.SetFocus();
}

void CDlgICGRandomParamater::OnPrimbutton() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(TRUE);
	GeneratePrimes P;
	CDlgPrimesGeneratorDemo Gen;
	if(8 >= m_PrimLang) m_PrimLang = 128;
	char tmpStr[12];
	sprintf(tmpStr, "%i", m_PrimLang-1);
	CString lowerBound = CString("2^") + CString(tmpStr);
	sprintf(tmpStr, "%i", m_PrimLang);
	CString upperBound = CString("2^") + CString(tmpStr);
	P.SetLimits( lowerBound, upperBound );

	SHOW_HOUR_GLASS;		// aktiviert die Sanduhr (statt des Mauszeigers)
	Gen.GetRandomPrime( m_Param_N, P );
	HIDE_HOUR_GLASS			// deaktiviert die Sanduhr

	UpdateData(FALSE);
}


void CDlgICGRandomParamater::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nFlags & (1<<13)) {
		switch(nChar) {
		case('p'):
		case('P'): m_Param_NCtrl.SetFocus();
			return;
		case('a'):
		case('A'): m_Param_bCtrl.SetFocus();
			return;
		}
	}
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDlgICGRandomParamater::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	
	BOOL Modul_N_IsOK;
	BOOL Multiplikator_a_IsOK;
	BOOL Inkrement_b_IsOK;
	int     ndx_a;
	int     ndx_b;
	int     ndx_N;
	UpdateData(TRUE);
	{ 
		CString upnStr;
		Modul_N_IsOK = EvalFormula(m_Param_N, ndx_N);
		Multiplikator_a_IsOK = EvalFormula(m_Param_a, ndx_a);
		Inkrement_b_IsOK = EvalFormula(m_Param_b, ndx_b);
	}
	UpdateData(FALSE);
	if ( Modul_N_IsOK  && Multiplikator_a_IsOK && Inkrement_b_IsOK)
	{
		GeneratePrimes P;
		P.SetP(Get_N());
		BOOL test=FALSE;
		test = P.MillerRabinTest(100);
		test = P.SolvayStrassenTest(100);
		test = P.FermatTest(100);

		if ( !test ) 
		{
			Message(IDS_STRING_MODUL_NOT_PRIME, MB_ICONSTOP);
			m_Param_NCtrl.SetSel(0,-1);
			m_Param_NCtrl.SetFocus();
		}
		else
		{
			CDialog::OnOK();
		}
	}
	else
	{
		// ********* Fehlermeldung
		if ( !Modul_N_IsOK )
		{
			if (ndx_N == -1)
			{
				Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
				m_Param_NCtrl.SetSel(0,-1);
				m_Param_NCtrl.SetFocus();
			}
			else
			{
				Message(IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
				m_Param_NCtrl.SetSel(ndx_N-1,-1);
				m_Param_NCtrl.SetFocus();
			}
		}
		else if ( !Multiplikator_a_IsOK )
		{
			if (ndx_a == -1)
			{
				Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
				m_Param_aCtrl.SetSel(0,-1);
				m_Param_aCtrl.SetFocus();
			}
			else
			{
				Message(IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
				m_Param_aCtrl.SetSel(ndx_a-1,-1);
				m_Param_aCtrl.SetFocus();
			}
		}
		else
		{
			if (ndx_b == -1)
			{
				Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
				m_Param_bCtrl.SetSel(0,-1);
				m_Param_bCtrl.SetFocus();
			}
			else
			{
				Message(IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
				m_Param_bCtrl.SetSel(ndx_b-1,-1);
				m_Param_bCtrl.SetFocus();
			}
		}
	}
}
