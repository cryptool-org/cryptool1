//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// OptionsDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "OptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld OptionsDialog 


OptionsDialog::OptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(OptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(OptionsDialog)
	m_CKey = TRUE;
	m_CKorr = TRUE;
	m_CHist = TRUE;
	m_VKey = TRUE;
	m_VLen = TRUE;
	m_VKorr = TRUE;
	m_VBase = FALSE;
	//}}AFX_DATA_INIT
}


void OptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OptionsDialog)
	DDX_Check(pDX, IDC_CHECK1, m_CKey);
	DDX_Check(pDX, IDC_CHECK2, m_CKorr);
	DDX_Check(pDX, IDC_CHECK3, m_CHist);
	DDX_Check(pDX, IDC_CHECK6, m_VKey);
	DDX_Check(pDX, IDC_CHECK7, m_VLen);
	DDX_Check(pDX, IDC_CHECK8, m_VKorr);
	DDX_Check(pDX, IDC_CHECK4, m_VBase);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OptionsDialog, CDialog)
	//{{AFX_MSG_MAP(OptionsDialog)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten OptionsDialog  