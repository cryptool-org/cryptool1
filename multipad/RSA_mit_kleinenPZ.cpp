// RSA_mit_kleinenPZ.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "RSA_mit_kleinenPZ.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld RSA_mit_kleinenPZ 


RSA_mit_kleinenPZ::RSA_mit_kleinenPZ(CWnd* pParent /*=NULL*/)
	: CDialog(RSA_mit_kleinenPZ::IDD, pParent)
{
	//{{AFX_DATA_INIT(RSA_mit_kleinenPZ)
	m_eingabe_pz_p = _T("");
	m_eingabe_pz_q = _T("");
	m_oeffentliche_param_pq = _T("");
	m_text_eingabe = _T("");
	m_text_locherung = _T("");
	m_verschluesselter_text = _T("");
	m_oeffentl_schluessel_e = _T("");
	m_geheimer_schluessel_d = _T("");
	m_geheime_param = _T("");
	//}}AFX_DATA_INIT
}


void RSA_mit_kleinenPZ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RSA_mit_kleinenPZ)
	DDX_Control(pDX, IDC_BUTTON_VERSCHLUESSELN, m_verschluesseln);
	DDX_Control(pDX, IDC_BUTTON_PZ_GENERIEREN, m_pz_generieren);
	DDX_Control(pDX, IDC_BUTTON_ENTSCHLUESSELN, m_entschluesseln);
	DDX_Control(pDX, IDC_EINGABE_PZ_q, m_control_eingabe_pz_q);
	DDX_Control(pDX, IDC_EINGABE_PZ_p, m_control_eingabe_pz_p);
	DDX_Text(pDX, IDC_EINGABE_PZ_p, m_eingabe_pz_p);
	DDX_Text(pDX, IDC_EINGABE_PZ_q, m_eingabe_pz_q);
	DDX_Text(pDX, IDC_EDIT_OEFFENTLICHE_PARAM, m_oeffentliche_param_pq);
	DDX_LBString(pDX, IDC_LIST_TEXTEINGABE, m_text_eingabe);
	DDX_LBString(pDX, IDC_LIST_LOCHERUNG, m_text_locherung);
	DDX_LBString(pDX, IDC_LIST_VERSCHLUESSELTER_TEXT, m_verschluesselter_text);
	DDX_Text(pDX, IDC_EDIT_OEFF_SCHLUESSEL_e, m_oeffentl_schluessel_e);
	DDX_Text(pDX, IDC_EDIT_GEHEIMER_SCHLUESSEL_d, m_geheimer_schluessel_d);
	DDX_Text(pDX, IDC_EDIT_GEHEIME_PARAM, m_geheime_param);
	//}}AFX_DATA_MAP
}
//******************************************************************************


void RSA_mit_kleinenPZ::CheckEdit_Input(CString & m_edit, int & sels, int & sele)

		// sorgt dafür, daß keine syntaktisch falsche Eingabe in die Ober- und Untergrenze-Eingabefelder
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

/*	if(Get_Value(m_edit)>LONG_MAX)
	{
		if(0==exp_counter)
		{
			while(Get_Value(m_edit)>LONG_MAX)
			{
				m_edit=m_edit.Left(m_edit.GetLength()-1);
			}
		}
		else
		{
			itoa(LONG_MAX,m_edit.GetBuffer(20),10);
			sels=sele=20;
		}
	}*/
}
//***********************************************************************


BEGIN_MESSAGE_MAP(RSA_mit_kleinenPZ, CDialog)
	//{{AFX_MSG_MAP(RSA_mit_kleinenPZ)
	ON_EN_UPDATE(IDC_EINGABE_PZ_p, OnUpdateEINGABEPZp)
	ON_EN_UPDATE(IDC_EINGABE_PZ_q, OnUpdateEINGABEPZq)
	ON_BN_CLICKED(IDC_BUTTON_VERSCHLUESSELN, OnButtonVerschluesseln)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten RSA_mit_kleinenPZ 

void RSA_mit_kleinenPZ::OnUpdateEINGABEPZp() 
{
	UpdateData(true);
	int sels,sele;
	m_control_eingabe_pz_p.GetSel(sels,sele);
	CheckEdit_Input(m_eingabe_pz_p,sels,sele);
	UpdateData(false);
	m_control_eingabe_pz_p.SetSel(sels,sele);
}

void RSA_mit_kleinenPZ::OnUpdateEINGABEPZq() 
{
	UpdateData(true);
	int sels,sele;
	m_control_eingabe_pz_q.GetSel(sels,sele);
	CheckEdit_Input(m_eingabe_pz_q,sels,sele);
	UpdateData(false);
	m_control_eingabe_pz_q.SetSel(sels,sele);
}




void RSA_mit_kleinenPZ::OnButtonVerschluesseln() 
{
	UpdateData(true);

	UpdateData(false);	
	
}
