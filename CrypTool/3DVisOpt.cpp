// 3DVisOpt.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "3DVisOpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld C3DVisOpt 


C3DVisOpt::C3DVisOpt(CWnd* pParent /*=NULL*/)
	: CDialog(C3DVisOpt::IDD, pParent)
{
	//{{AFX_DATA_INIT(C3DVisOpt)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	resolution = 128;
}


void C3DVisOpt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3DVisOpt)
	DDX_Control(pDX, IDC_SLIDER1, m_CtrlSliderResolution);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3DVisOpt, CDialog)
	//{{AFX_MSG_MAP(C3DVisOpt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten C3DVisOpt 

BOOL C3DVisOpt::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	m_CtrlSliderResolution.SetRange(0, 255);
	m_CtrlSliderResolution.SetPos(resolution);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
