/******************************************************************************************************/
/*            Dlg_Schluessel_gen.cpp: Implementierungsdatei der Klasse Dlg_Schluessel_gen.            */
/*                         Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main                    */
/*			                                                                                          */
/*                         Programmiert von Roger Oyono, März 2001	     							  */
/*																                                      */
/*                         Deutsche Bank AG Frankfurt - IT Security                                   */
/******************************************************************************************************/


#include "stdafx.h"
#include "multipad.h"
#include "Dlg_Schluessel_gen.h"
#include "string.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/******************************************************************************************************/
/*                                       Dialogfeld Dlg_Schluessel_gen                                */
/******************************************************************************************************/


Dlg_Schluessel_gen::Dlg_Schluessel_gen(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Schluessel_gen::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_Schluessel_gen)
	m_schluessel = _T("");
	m_passwort = _T("");
	m_radio1 = 0;
	m_salt = _T("");
	m_dkLen = _T("16");
	m_zaehler = _T("1000");
	//}}AFX_DATA_INIT
}


void Dlg_Schluessel_gen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Schluessel_gen)
	DDX_Control(pDX, IDC_EDIT4, m_control_zaehler);
	DDX_Control(pDX, IDC_EDIT5, m_control_dkLen);
	DDX_Control(pDX, IDC_EDIT2, m_control_schluessel);
	DDX_Control(pDX, IDC_EDIT1, m_control_passwort);
	DDX_Text(pDX, IDC_EDIT2, m_schluessel);
	DDX_Text(pDX, IDC_EDIT1, m_passwort);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Text(pDX, IDC_EDIT3, m_salt);
	DDX_Text(pDX, IDC_EDIT5, m_dkLen);
	DDX_Text(pDX, IDC_EDIT4, m_zaehler);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_Schluessel_gen, CDialog)
	//{{AFX_MSG_MAP(Dlg_Schluessel_gen)
	ON_BN_CLICKED(IDC_BUTTON_Generieren, OnBUTTONGenerieren)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit2)
	ON_BN_CLICKED(IDC_BUTTON_cancel, OnBUTTONcancel)
	ON_BN_CLICKED(IDC_BUTTON_Uebernehmen, OnBUTTONUebernehmen)
	ON_EN_UPDATE(IDC_EDIT4, OnUpdateEdit4)
	ON_EN_UPDATE(IDC_EDIT5, OnUpdateEdit5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Dlg_Schluessel_gen 

BOOL Dlg_Schluessel_gen::OnInitDialog() 
{
	CDialog::OnInitDialog();

	UpdateData(true);
	char line[20];
	sprintf(line, "%i%i", rand(), rand() );
	m_salt = line;
	UpdateData(false);
	// TODO: Zusätzliche Initialisierung hier einfügen
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void Dlg_Schluessel_gen::OnBUTTONGenerieren() 
{
	UpdateData(true);
	theApp.DoWaitCursor(0);				// aktiviert die Sanduhr (statt des Mauszeigers)
	if (0==SG.password_based_key_deriv_funct(m_passwort, m_salt,m_dkLen,m_radio1,m_zaehler))
	{
		int ndx = 0, md = 0;
		if ( SG.str[0] == '0' && ( SG.str[1] == 'X' || SG.str[1] == 'x' ) ) ndx = 2;
		m_schluessel = (CString)"";
        while ( SG.str[ndx] != 0 )
		{
			m_schluessel += SG.str[ndx++]; 
			md = (md+1) % 2;
		    if (!md && SG.str[ndx]  != 0 ) m_schluessel += " ";
		}
		// m_schluessel= ((CString) SG.str);
	}
	theApp.DoWaitCursor(-1);				// deaktiviert die Sanduhr (statt des Mauszeigers)
	UpdateData(false);
}

void Dlg_Schluessel_gen::OnUpdateEdit1() 
{
	UpdateData(true);
	int sels,sele;
	m_control_passwort.GetSel(sels,sele);
	UpdateData(false);
	m_control_passwort.SetSel(sels,sele);
}

void Dlg_Schluessel_gen::OnUpdateEdit2() 
{
	UpdateData(true);
	int sels,sele;
	m_control_schluessel.GetSel(sels,sele);
	UpdateData(false);
	m_control_schluessel.SetSel(sels,sele);
}

void Dlg_Schluessel_gen::OnBUTTONcancel() 
{
	CDialog::OnOK();	
}

void Dlg_Schluessel_gen::OnBUTTONUebernehmen() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(TRUE);
	m_control_schluessel.SetSel(0,-1);
	m_control_schluessel.Copy();
	UpdateData(FALSE);
}

void Dlg_Schluessel_gen::CheckEdit(CString &m_edit,int & sels, int & sele)
		// sorgt dafür, daß keine syntaktisch falsche Eingabe in die Eingabefelder
		// möglich ist, führende Nullen werden entfernt, die Variablen sels und sele dienen der
		// Formatierung
{
	while((0==m_edit.IsEmpty())&&('0'==m_edit.GetAt(0)))
		//Ruft Funktion IsEmpty auf. Diese gibt 0 zurück, wenn der CString nicht leer ist
		//GetAt(a) gibt Zeichen zurück, das an der a. Position steht
		//in diesem Fall, wenn dieses Zeichen 0 ist, dann geht er in die Schleife
		//Diese Funktionen gelten für die übergebenen Wert aus dem Dialog.
		//* Überprüfung, ob überhaupt was in dem Eingabefeld steht, UND ob das erste Zeichen 0 ist.
	{
		m_edit=m_edit.Right(m_edit.GetLength()-1);
		//* Var. m_edit ist Beispielsweise 0567. Der Rückgabe der Funktion Right gibt dir letzten x
		//* Stellen eines CStrings zurück, in diesem Fall gibt er mir 3 Stllen zurück (length-1), so dass die 0 gelöscht wird
		sels=sele=0;								
	}

	int exp_counter=0;
	for(int i=0;i<m_edit.GetLength();i++)
	{
		char ch=m_edit.GetAt(i);
		//* GetAt=holt sich das Zeichen an der i. Stelle
		if((ch>='0')&&(ch<='9'))
		{
			
		}
		else
		{
			m_edit=m_edit.Left(i)+m_edit.Right(m_edit.GetLength()-i-1);	
			//* die ersten i Stellen von links werden mit den Stellen rechts vom ungültigen Zeichen verbunden
			//* -1 damit das Zeichen an der Position i von m_edit gelöscht wird.

			if(i<=sele)
			{
				sele--;
				sels--;
			}
			i--;
		}
	}
}

void Dlg_Schluessel_gen::OnUpdateEdit4() 
{
		UpdateData(true);
	int sels,sele;
	m_control_zaehler.GetSel(sels,sele);
	CheckEdit(m_zaehler,sels,sele);
	UpdateData(false);
	m_control_zaehler.SetSel(sels,sele);
}

void Dlg_Schluessel_gen::OnUpdateEdit5() 
{
	UpdateData(true);
	int sels,sele;
	m_control_dkLen.GetSel(sels,sele);
	CheckEdit(m_dkLen,sels,sele);
	UpdateData(false);
	m_control_dkLen.SetSel(sels,sele);
}
