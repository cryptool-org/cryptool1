// Dlg_homophone.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "Dlg_homophone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Dlg_homophone 


Dlg_homophone::Dlg_homophone(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_homophone::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_homophone)
	m_crypt = 0;
	//}}AFX_DATA_INIT
}


void Dlg_homophone::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_homophone)
	DDX_Control(pDX, IDC_LIST1, m_listview);
	DDX_Radio(pDX, IDC_RADIO1, m_crypt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_homophone, CDialog)
	//{{AFX_MSG_MAP(Dlg_homophone)
	ON_BN_CLICKED(IDC_ERZEUGEN, OnErzeugen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Dlg_homophone 

void Dlg_homophone::OnErzeugen() 
{
	UpdateData(true);
	HB.Generate_key();
	//m_key=Get_key();
	UpdateData(false);
}

bool Dlg_homophone::Is_key()
{
	//return(!(m_key.IsEmpty()));
	return(true);
}

int Dlg_homophone::Display()
{
	return(DoModal());
}

int Dlg_homophone::Get_crypt()
{
	return(m_crypt);
}

CString Dlg_homophone::Get_key()
{
	CString key,help;
	int value;
	key.Empty();
	for(int i=0;i<=255;i++)
	{
		value=HB.Get_key(i);
		if(value<10)
		{
			key+="00";
		}
		else if(value<100)
		{
			key+="0";
		}
		itoa(value,help.GetBuffer(10),10);
		key.Insert(key.GetLength(),help);
		key.Insert(key.GetLength()," ");
		help.Empty();
	}
	return(key);
}

BOOL Dlg_homophone::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int colWidth = 100;  // Spaltenbreite in Pixel

	LoadString(AfxGetInstanceHandle(),IDS_STRING37001,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(0,pc_str,LVCFMT_LEFT,colWidth-45,0); // Zeichen

	LoadString(AfxGetInstanceHandle(),IDS_STRING37002,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(1,pc_str,LVCFMT_LEFT,colWidth-45,1); // Anzahl

	LoadString(AfxGetInstanceHandle(),IDS_STRING37003,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(2,pc_str,LVCFMT_LEFT,colWidth+235,2); // Verschlüsselung
	
	//sortBy = BY_NAME; // default Einstellung: sortiere Liste nach Namen

	Init_ListBox();

	return(TRUE);
}

void Dlg_homophone::Init_ListBox()
{
	m_listview.DeleteAllItems( ); 

	m_listview.InsertItem(0,"Zeichen");
	m_listview.SetItemText(0,1,"Testtext");
	m_listview.SetItemText(0,2,"Deutsche Bank AG+");
	m_listview.InsertItem(1,"Zeichen");
	m_listview.SetItemText(0,1,"Testtext");
	m_listview.InsertItem(2,"Zeichen");
	m_listview.SetItemText(0,1,"Testtext");
}
