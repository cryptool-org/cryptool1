//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// About.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgAbout.h"
#include "DlgAuthors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAbout 


CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/)
: CDialog(CDlgAbout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAbout)
	if(theApp.SecudeStatus == 2)       // Falls die SecudeLib da
	{                                  // ist, die Version holen      
		int i=0;                       // anzeigen.
		strcpy(pc_str,theApp.SecudeLib.aux_sprint_version(NULL));
		while (pc_str[i]!=0x0d)        // nur bis zum newline
			i++;
		pc_str[i]=0;
	}
	else                               // sonst "lib nicht verfügbar"
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SECUDE_DLL_NOT_AVAILABLE,pc_str,STR_LAENGE_STRING_TABLE);
	m_secude=pc_str;
	//}}AFX_DATA_INIT
}


void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAbout)
	DDX_Text(pDX, IDC_EDIT1, m_secude);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
//{{AFX_MSG_MAP(CDlgAbout)
ON_WM_LBUTTONDBLCLK()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgAbout 


void CDlgAbout::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	CDialog::OnLButtonDblClk(nFlags, point);
	
	CDlgAuthors klasse;
	klasse.DoModal();
	
} 