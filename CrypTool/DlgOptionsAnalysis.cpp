//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// OptionsDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgOptionsAnalysis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsAnalysis 


CDlgOptionsAnalysis::CDlgOptionsAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsAnalysis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsAnalysis)
	m_CKey = TRUE;
	m_CKorr = TRUE;
	m_CHist = TRUE;
	m_VKey = TRUE;
	m_VLen = TRUE;
	m_VKorr = TRUE;
	m_VBase = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsAnalysis)
	DDX_Check(pDX, IDC_CHECK1, m_CKey);
	DDX_Check(pDX, IDC_CHECK2, m_CKorr);
	DDX_Check(pDX, IDC_CHECK3, m_CHist);
	DDX_Check(pDX, IDC_CHECK6, m_VKey);
	DDX_Check(pDX, IDC_CHECK7, m_VLen);
	DDX_Check(pDX, IDC_CHECK8, m_VKorr);
	DDX_Check(pDX, IDC_CHECK4, m_VBase);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsAnalysis)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgOptionsAnalysis  