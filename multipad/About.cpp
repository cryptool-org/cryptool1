//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// About.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "About.h"
#include "Autoren.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CAbout 


CAbout::CAbout(CWnd* pParent /*=NULL*/)
: CDialog(CAbout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAbout)
	if(theApp.SecudeStatus == 2)       // Falls die SecudeLib da
	{                                  // ist, die Version holen      
		int i=0;                       // anzeigen.
		strcpy(pc_str,theApp.SecudeLib.aux_sprint_version(NULL));
		while (pc_str[i]!=0x0d)        // nur bis zum newline
			i++;
		pc_str[i]=0;
	}
	else                               // sonst "lib nicht verfügbar"
		LoadString(AfxGetInstanceHandle(),IDS_STRING61425,pc_str,STR_LAENGE_STRING_TABLE);
	m_secude=pc_str;
	//}}AFX_DATA_INIT
}


void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbout)
	DDX_Text(pDX, IDC_EDIT1, m_secude);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAbout, CDialog)
//{{AFX_MSG_MAP(CAbout)
ON_WM_LBUTTONDBLCLK()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CAbout 


void CAbout::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CDialog::OnLButtonDblClk(nFlags, point);
	
	CAutoren klasse;
	klasse.DoModal();
	
} 