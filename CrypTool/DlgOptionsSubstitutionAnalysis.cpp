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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DlgSubstAna.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgOptionsSubstitutionAnalysis.h"
#include "FileTools.h"
#include "Cryptography.h"
#include "KeyRepository.h"

extern char *Eingabedatei;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsSubstitutionAnalysis 


CDlgOptionsSubstitutionAnalysis::CDlgOptionsSubstitutionAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsSubstitutionAnalysis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsSubstitutionAnalysis)
	m_radio1 = 0;
	m_check1 = FALSE;
	m_check2 = FALSE;
	m_storedKey = -1;
	//}}AFX_DATA_INIT
}


void CDlgOptionsSubstitutionAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsSubstitutionAnalysis)
	DDX_Control(pDX, IDC_RADIO4, m_ctrl_storedKey);
	DDX_Control(pDX, IDC_CHECK2, m_control2);
	DDX_Control(pDX, IDC_CHECK1, m_control1);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK2, m_check2);
	DDX_Radio(pDX, IDC_RADIO4, m_storedKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsSubstitutionAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsSubstitutionAnalysis)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgOptionsSubstitutionAnalysis 


BOOL CDlgOptionsSubstitutionAnalysis::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Default-Einstellung ist englischer Klartext mit reiner Pattern Suche
	CheckRadioButton (IDC_RADIO1, IDC_RADIO3, IDC_RADIO2);
	m_control2.EnableWindow(FALSE);	
	
	LoadString(AfxGetInstanceHandle(),IDS_ANALYSIS_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
	if ( IsKeyEmpty( pc_str ))
	{
		m_ctrl_storedKey.EnableWindow(TRUE);
	}
	else
	{
		m_ctrl_storedKey.EnableWindow(FALSE);
	}
	return TRUE;  
}

void CDlgOptionsSubstitutionAnalysis::OnCheck2() 
{
	// Wenn der Knopf "erweiterte Analyse" gewählt wird:
	// Diese Option schließt die Option "'e' als häufigstes Zeichen logisch ein, so daß 
	// diese Option automatsich auch angewählt wird.
	// Ferner muß ausgeschlossen werden, daß der Benutzer eine erweiterte Analyse für
	// englischen Klartext gewählt hat, da das derzeit vom Programm noch nicht unterstützt
	// wird.
	UpdateData(TRUE);
	m_check1=true;
	UpdateData(FALSE);	
}

void CDlgOptionsSubstitutionAnalysis::OnCheck1() 
{
	// Wenn die Option "'e' als häufigstes Zeichen" geändert wird, muß die Option
	// "erweiterte Analyse" automatisch abgeschaltet werden, damit es nicht vorkommt,
	// daß die zweite ohne die erste Option ausgewählt wurde
	UpdateData(TRUE);
	if ( false == m_check1 )
		m_check2=false;
	UpdateData(FALSE);
}

void CDlgOptionsSubstitutionAnalysis::OnRadio1() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData();
	m_control1.EnableWindow();
	m_control2.EnableWindow();
	m_storedKey = -1;
	UpdateData(FALSE);
}

void CDlgOptionsSubstitutionAnalysis::OnRadio2() 
{
	// Wird englischer Klartext gewählt, so muß die Option "erweiterte Analyse" abgeschaltet werden
	UpdateData();
	m_control1.EnableWindow();
	m_check2 = false;
	m_control2.EnableWindow(FALSE);
	m_storedKey = -1;
	UpdateData(FALSE);
}

void CDlgOptionsSubstitutionAnalysis::OnRadio3() 
{
	UpdateData();
	m_check1 = false;
	m_control1.EnableWindow(FALSE);
	m_check2 = false;
	m_control2.EnableWindow(FALSE);
	m_storedKey = -1;
	UpdateData(FALSE);
}

void CDlgOptionsSubstitutionAnalysis::OnRadio4() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData();
	m_check1 = false;
	m_control1.EnableWindow(FALSE);
	m_check2 = false;
	m_control2.EnableWindow(FALSE);
	m_storedKey = 0;
	m_radio1    = -1;
	UpdateData(FALSE);
}
