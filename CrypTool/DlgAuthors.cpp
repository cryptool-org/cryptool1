//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Autoren.cpp: Implementierungsdatei
//


#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgAuthors.h"
#include "DlgPrimesGeneratorDemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAuthors 

CDlgAuthors::CDlgAuthors(CWnd* pParent /*=NULL*/)
: CDialog(CDlgAuthors::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAuthors)
	// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}

void CDlgAuthors::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAuthors)
	// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgAuthors, CDialog)
//{{AFX_MSG_MAP(CDlgAuthors)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgAuthors 

