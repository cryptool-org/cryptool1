//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DlgSubstAna.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgSubstAna.h"
#include "fileutil.h"
#include "crypt.h"

extern char *Eingabedatei;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSubstAna 


CDlgSubstAna::CDlgSubstAna(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSubstAna::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSubstAna)
	m_radio1 = -1;
	m_check1 = FALSE;
	m_check2 = FALSE;
	m_check3 = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgSubstAna::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSubstAna)
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK2, m_check2);
	DDX_Check(pDX, IDC_CHECK3, m_check3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSubstAna, CDialog)
	//{{AFX_MSG_MAP(CDlgSubstAna)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgSubstAna 


BOOL CDlgSubstAna::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Default-Einstellung ist englischer Klartext mit reiner Pattern Suche
	CheckRadioButton (IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
	
	return TRUE;  
}

void CDlgSubstAna::OnCheck2() 
{
	// Wenn der Knopf "erweiterte Analyse" gew�hlt wird:
	// Diese Option schlie�t die Option "'e' als h�ufigstes Zeichen logisch ein, so da� 
	// diese Option automatsich auch angew�hlt wird.
	// Ferner mu� ausgeschlossen werden, da� der Benutzer eine erweiterte Analyse f�r
	// englischen Klartext gew�hlt hat, da das derzeit vom Programm noch nicht unterst�tzt
	// wird.
	UpdateData(TRUE);
	if ((m_radio1==1)&&(m_check2==(int)true)){		// Englisch gew�hlt
		LoadString(AfxGetInstanceHandle(),IDS_STRING41534,pc_str,1000);
		AfxMessageBox (pc_str);
		m_check2=false;
	}
	else{
		m_check1=true;
	}
	if (m_check2==(int)true){
		m_check3=false;}
	UpdateData(FALSE);	
}

void CDlgSubstAna::OnCheck1() 
{
	// Wenn die Option "'e' als h�ufigstes Zeichen" ge�ndert wird, mu� die Option
	// "erweiterte Analyse" automatisch abgeschaltet werden, damit es nicht vorkommt,
	// da� die zweite ohne die erste Option ausgew�hlt wurde
	UpdateData(TRUE);
	m_check2=false;
	m_check3=false;
	UpdateData(FALSE);
}

void CDlgSubstAna::OnRadio2() 
{
	// Wird englischer Klartext gew�hlt, so mu� die Option "erweiterte Analyse" abgeschaltet werden
	UpdateData(TRUE);
	if (m_check2==(int)true){
		LoadString(AfxGetInstanceHandle(),IDS_STRING41534,pc_str,1000);
		AfxMessageBox (pc_str);
		UpdateData(FALSE);
		CheckRadioButton (IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
	}
		
}

void CDlgSubstAna::OnCheck3() 
{
	UpdateData(TRUE);
	if (m_check3==(int)true){
		m_check1=false;
		m_check2=false;
		UpdateData(FALSE);
	}
} 
void CDlgSubstAna::OnRadio1() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	
}
