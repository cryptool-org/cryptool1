
/******************************************************************************************************/
/*            Dlg_Faktorisieren.cpp: Implementierungsdatei der Klasse Dlg_Faktorisieren.             */
/*                     Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main                        */
/*                     Programmiert von Roger Oyono März 2001                                         */
/*                     Deutsche Bank AG Frankfurt - IT Security                                       */
/******************************************************************************************************/

#include "stdafx.h"
#include "multipad.h"
#include "Dlg_Faktorisieren.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Dlg_Faktorisieren 


Dlg_Faktorisieren::Dlg_Faktorisieren(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Faktorisieren::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Faktorisieren)
	m_edit1_eingabe = _T("179123741*302519933");
	m_edit_prim1 = _T("");
	m_edit_prim2 = _T("");
	m_edit_coprim1 = _T("");
	m_edit_coprim2 = _T("");
	m_radio1 = 0;
	m_edit_prim3 = _T("");
	m_edit_prim4 = _T("");
	m_lastprime = 0;
	m_lastcofaktor = 0;
	m_radio7 = -1;
	m_edit_2erfaktor = _T("");
	//}}AFX_DATA_INIT
}


void Dlg_Faktorisieren::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Faktorisieren)
	DDX_Control(pDX, IDC_EDIT10, m_control_2erfaktor);
	DDX_Control(pDX, IDC_EDIT9, m_control_lastcofaktor);
	DDX_Control(pDX, IDC_EDIT8, m_control_lastprime);
	DDX_Control(pDX, IDC_EDIT7, m_control_prim4);
	DDX_Control(pDX, IDC_EDIT6, m_control_prim3);
	DDX_Control(pDX, IDC_EDIT5, m_control_coprim2);
	DDX_Control(pDX, IDC_EDIT4, m_control_coprim1);
	DDX_Control(pDX, IDC_EDIT3, m_control_prim2);
	DDX_Control(pDX, IDC_EDIT2, m_control_prim1);
	DDX_Control(pDX, IDC_EDIT1, m_control_eingabe);
	DDX_Text(pDX, IDC_EDIT1, m_edit1_eingabe);
	DDX_Text(pDX, IDC_EDIT2, m_edit_prim1);
	DDX_Text(pDX, IDC_EDIT3, m_edit_prim2);
	DDX_Text(pDX, IDC_EDIT4, m_edit_coprim1);
	DDX_Text(pDX, IDC_EDIT5, m_edit_coprim2);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Text(pDX, IDC_EDIT6, m_edit_prim3);
	DDX_Text(pDX, IDC_EDIT7, m_edit_prim4);
	DDX_Text(pDX, IDC_EDIT8, m_lastprime);
	DDX_Text(pDX, IDC_EDIT9, m_lastcofaktor);
	DDX_Radio(pDX, IDC_RADIO7, m_radio7);
	DDX_Text(pDX, IDC_EDIT10, m_edit_2erfaktor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Faktorisieren, CDialog)
	//{{AFX_MSG_MAP(Dlg_Faktorisieren)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_BN_CLICKED(IDC_BUTTON_Faktorisieren, OnBUTTONFaktorisieren)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit2)
	ON_EN_UPDATE(IDC_EDIT3, OnUpdateEdit3)
	ON_EN_UPDATE(IDC_EDIT4, OnUpdateEdit4)
	ON_EN_UPDATE(IDC_EDIT5, OnUpdateEdit5)
	ON_EN_UPDATE(IDC_EDIT6, OnUpdateEdit6)
	ON_EN_UPDATE(IDC_EDIT7, OnUpdateEdit7)
	ON_EN_UPDATE(IDC_EDIT8, OnUpdateEdit8)
	ON_EN_UPDATE(IDC_EDIT9, OnUpdateEdit9)
	ON_EN_UPDATE(IDC_EDIT10, OnUpdateEdit10)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_cancel, OnBUTTONcancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Dlg_Faktorisieren 

BOOL Dlg_Faktorisieren::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void Dlg_Faktorisieren::OnUpdateEdit1() 
{
	UpdateData(true);
	int sels,sele;
	m_control_eingabe.GetSel(sels,sele);
	UpdateData(false);
	m_control_eingabe.SetSel(sels,sele);
}



void Dlg_Faktorisieren::OnBUTTONFaktorisieren() 
{
	char string[100];
	UpdateData(true);
	theApp.DoWaitCursor(0);				// aktiviert die Sanduhr (statt des Mauszeigers)
	
	PFAKT.CFL.reset();
	PFAKT.PL.reset();



	if(4==m_radio1)
	{
	
	PFAKT.lenstra_fakt(m_edit1_eingabe);

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim1.GetBuffer(100) << PFAKT.PL.prime[0];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim2.GetBuffer(100) << PFAKT.PL.prime[1];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim3.GetBuffer(100) << PFAKT.PL.prime[2];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim4.GetBuffer(100) << PFAKT.PL.prime[3];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_coprim1.GetBuffer(100) << PFAKT.CFL.CoFaktor[0];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_coprim2.GetBuffer(100) << PFAKT.CFL.CoFaktor[1];

	

	m_edit_2erfaktor=_itoa(PFAKT.exp2, string, 10);

	m_lastprime=PFAKT.PL.lastprime;
	m_lastcofaktor=PFAKT.CFL.lastcofaktor;

	PFAKT.CFL.reset();
	PFAKT.PL.reset();

	}

	if(5==m_radio1)
	{
	
	PFAKT.QSieve(m_edit1_eingabe);

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim1.GetBuffer(100) << PFAKT.PL.prime[0];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim2.GetBuffer(100) << PFAKT.PL.prime[1];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim3.GetBuffer(100) << PFAKT.PL.prime[2];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim4.GetBuffer(100) << PFAKT.PL.prime[3];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_coprim1.GetBuffer(100) << PFAKT.CFL.CoFaktor[0];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_coprim2.GetBuffer(100) << PFAKT.CFL.CoFaktor[1];

	m_edit_2erfaktor=_itoa(PFAKT.exp2, string, 10);

	m_lastprime=PFAKT.PL.lastprime;
	m_lastcofaktor=PFAKT.CFL.lastcofaktor;

	PFAKT.CFL.reset();
	PFAKT.PL.reset();

	}

	if(3==m_radio1)
	{
	
	PFAKT.Williams(m_edit1_eingabe);

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim1.GetBuffer(100) << PFAKT.PL.prime[0];
	
//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim3.GetBuffer(100) << PFAKT.PL.prime[2];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim4.GetBuffer(100) << PFAKT.PL.prime[3];
//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim2.GetBuffer(100) << PFAKT.PL.prime[1];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_coprim1.GetBuffer(100) << PFAKT.CFL.CoFaktor[0];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_coprim2.GetBuffer(100) << PFAKT.CFL.CoFaktor[1];

	m_edit_2erfaktor=_itoa(PFAKT.exp2, string, 10);

	m_lastprime=PFAKT.PL.lastprime;
	m_lastcofaktor=PFAKT.CFL.lastcofaktor;

	PFAKT.CFL.reset();
	PFAKT.PL.reset();
	
	}
	
	if(2==m_radio1)
	{
	
	PFAKT.Pollard(m_edit1_eingabe);

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim1.GetBuffer(100) << PFAKT.PL.prime[0];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim2.GetBuffer(100) << PFAKT.PL.prime[1];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim3.GetBuffer(100) << PFAKT.PL.prime[2];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim4.GetBuffer(100) << PFAKT.PL.prime[3];
//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_coprim1.GetBuffer(100) << PFAKT.CFL.CoFaktor[0];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_coprim2.GetBuffer(100) << PFAKT.CFL.CoFaktor[1];

	m_edit_2erfaktor=_itoa(PFAKT.exp2, string, 10);

	m_lastprime=PFAKT.PL.lastprime;
	m_lastcofaktor=PFAKT.CFL.lastcofaktor;

	PFAKT.CFL.reset();
	PFAKT.PL.reset();

	}

	if(1==m_radio1)
	{
	
	PFAKT.brent(m_edit1_eingabe);

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim1.GetBuffer(100) << PFAKT.PL.prime[0];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim2.GetBuffer(100) << PFAKT.PL.prime[1];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim3.GetBuffer(100) << PFAKT.PL.prime[2];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim4.GetBuffer(100) << PFAKT.PL.prime[3];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_coprim1.GetBuffer(100) << PFAKT.CFL.CoFaktor[0];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_coprim2.GetBuffer(100) << PFAKT.CFL.CoFaktor[1];

	m_edit_2erfaktor=_itoa(PFAKT.exp2, string, 10);

	m_lastprime=PFAKT.PL.lastprime;
	m_lastcofaktor=PFAKT.CFL.lastcofaktor;

	PFAKT.CFL.reset();
	PFAKT.PL.reset();

	}

	if(0==m_radio1)
	{
	
	PFAKT.brute(m_edit1_eingabe);

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim1.GetBuffer(100) << PFAKT.PL.prime[0];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim2.GetBuffer(100) << PFAKT.PL.prime[1];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim3.GetBuffer(100) << PFAKT.PL.prime[2];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_prim4.GetBuffer(100) << PFAKT.PL.prime[3];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_coprim1.GetBuffer(100) << PFAKT.CFL.CoFaktor[0];

//	PFAKT.SetIOBASE(10);
//	PFAKT.mip2->IOBASE=10;
	m_edit_coprim2.GetBuffer(100) << PFAKT.CFL.CoFaktor[1];

	m_edit_2erfaktor=_itoa(PFAKT.exp2, string, 10);

	m_lastprime=PFAKT.PL.lastprime;
	m_lastcofaktor=PFAKT.CFL.lastcofaktor;

	PFAKT.CFL.reset();
	PFAKT.PL.reset();

	}
	

	theApp.DoWaitCursor(-1);			// deaktiviert die Sanduhr
	UpdateData(false);
	
}

void Dlg_Faktorisieren::OnUpdateEdit2() 
{
	UpdateData(true);
	int sels,sele;
	m_control_prim1.GetSel(sels,sele);
	UpdateData(false);
	m_control_prim1.SetSel(sels,sele);
	
}

void Dlg_Faktorisieren::OnUpdateEdit3() 
{
	UpdateData(true);
	int sels,sele;
	m_control_prim2.GetSel(sels,sele);
	UpdateData(false);
	m_control_prim2.SetSel(sels,sele);
	
}

void Dlg_Faktorisieren::OnUpdateEdit4() 
{
	UpdateData(true);
	int sels,sele;
	m_control_coprim1.GetSel(sels,sele);
	UpdateData(false);
	m_control_coprim1.SetSel(sels,sele);
	
}

void Dlg_Faktorisieren::OnUpdateEdit5() 
{
	UpdateData(true);
	int sels,sele;
	m_control_coprim2.GetSel(sels,sele);
	UpdateData(false);
	m_control_coprim2.SetSel(sels,sele);

}

void Dlg_Faktorisieren::OnUpdateEdit6() 
{
	UpdateData(true);
	int sels,sele;
	m_control_prim3.GetSel(sels,sele);
	UpdateData(false);
	m_control_prim3.SetSel(sels,sele);
	
}

void Dlg_Faktorisieren::OnUpdateEdit7() 
{
	UpdateData(true);
	int sels,sele;
	m_control_prim4.GetSel(sels,sele);
	UpdateData(false);
	m_control_prim4.SetSel(sels,sele);
	
}

void Dlg_Faktorisieren::OnUpdateEdit8() 
{
	UpdateData(true);
	int sels,sele;
	m_control_lastprime.GetSel(sels,sele);
	UpdateData(false);
	m_control_lastprime.SetSel(sels,sele);
	
}

void Dlg_Faktorisieren::OnUpdateEdit9() 
{
	UpdateData(true);
	int sels,sele;
	m_control_lastcofaktor.GetSel(sels,sele);
	UpdateData(false);
	m_control_lastcofaktor.SetSel(sels,sele);
	
}

void Dlg_Faktorisieren::OnUpdateEdit10() 
{
	UpdateData(true);
	int sels,sele;
	m_control_2erfaktor.GetSel(sels,sele);
	UpdateData(false);
	m_control_2erfaktor.SetSel(sels,sele);
	
}

void Dlg_Faktorisieren::OnButtonOk() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	
	CDialog::OnOK();	
}

void Dlg_Faktorisieren::OnBUTTONcancel() 
{
	
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	CDialog::OnCancel();	
}
