//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DialogLaenge.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DialogLaenge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogLaenge 


CDialogLaenge::CDialogLaenge(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogLaenge::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogLaenge)
	m_laenge = 0;
	//}}AFX_DATA_INIT
}


void CDialogLaenge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogLaenge)
	DDX_Text(pDX, IDC_EDIT1, m_laenge);
	DDV_MinMaxUInt(pDX, m_laenge, 1, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogLaenge, CDialog)
	//{{AFX_MSG_MAP(CDialogLaenge)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDialogLaenge  