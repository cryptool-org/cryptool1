// Dlg_Tests.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "Dlg_Tests.h"
#include "Zufallsgenerator_Tests_Alles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Dlg_Tests_Freq 


Dlg_Tests_Freq::Dlg_Tests_Freq(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Tests_Freq::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Tests_Freq)
	m_Ergebnis = _T("Taste \n\"Tests durchführen\"\n drücken!!!");
	infile = NULL;
	oldTitle = NULL;
	//}}AFX_DATA_INIT
}


void Dlg_Tests_Freq::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Tests_Freq)
	DDX_Control(pDX, IDC_BITMAP_2, m_Bitmap_Ctrl2);
	DDX_Control(pDX, IDC_BITMAP_1, m_Bitmap_Ctrl);
	DDX_Text(pDX, IDC_STATIC_ERGEBNIS, m_Ergebnis);
	//}}AFX_DATA_MAP
}

void Dlg_Tests_Freq::init (const char *Infile_, const char *OldTitle_)
{
	infile = Infile_;
	oldTitle = OldTitle_;
}

BEGIN_MESSAGE_MAP(Dlg_Tests_Freq, CDialog)
	//{{AFX_MSG_MAP(Dlg_Tests_Freq)
	ON_BN_CLICKED(IDC_BUTTON_FREQTEST, OnButtonFreqtest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Dlg_Tests_Freq 

void Dlg_Tests_Freq::OnButtonFreqtest() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	Freq_Test test;
	test.Set_infile(Get_infile());
	test.Set_oldtitle(Get_oldTitle());
	test.test();
	if(!test.GetResult())
	{
		m_Bitmap_Ctrl2.ShowWindow(FALSE);
		m_Bitmap_Ctrl.ShowWindow(TRUE);
		m_Ergebnis = "\n Test nicht bestanden !!!";
		UpdateData(FALSE);
	}
	else
	{
		m_Bitmap_Ctrl.ShowWindow(FALSE);
		m_Bitmap_Ctrl2.ShowWindow(TRUE);
		UpdateData(TRUE);
		m_Ergebnis = "\n Test bestanden !!!";
		UpdateData(FALSE);
	}
}
