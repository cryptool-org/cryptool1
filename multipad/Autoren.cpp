//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Autoren.cpp: Implementierungsdatei
//


#include "stdafx.h"
#include "multipad.h"
#include "Autoren.h"
#include "DlgPrimesGenerator.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CAutoren 




CAutoren::CAutoren(CWnd* pParent /*=NULL*/)
: CDialog(CAutoren::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAutoren)
	// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}




void CAutoren::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoren)
	// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CAutoren, CDialog)
//{{AFX_MSG_MAP(CAutoren)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CAutoren 

