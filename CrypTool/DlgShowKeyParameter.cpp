// DLG_param.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowKeyParameter.h"
#include "s_ecconv.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKeyParameter 


CDlgShowKeyParameter::CDlgShowKeyParameter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowKeyParameter::IDD, pParent)
{
	m_entries=0;
	//{{AFX_DATA_INIT(CDlgShowKeyParameter)
	m_radio = 1;
	m_titel = _T("");
	//}}AFX_DATA_INIT
	disableOkButton = false;
}


void CDlgShowKeyParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowKeyParameter)
	DDX_Control(pDX, IDOK, m_ctrlOK);
	DDX_Control(pDX, IDC_LIST, m_listctrl);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Text(pDX, IDC_TITEL, m_titel);
	DDV_MaxChars(pDX, m_titel, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowKeyParameter, CDialog)
	//{{AFX_MSG_MAP(CDlgShowKeyParameter)
	ON_BN_CLICKED(IDC_RADIO1, OnUpdate)
	ON_BN_CLICKED(IDC_RADIO2, OnUpdate)
	ON_BN_CLICKED(IDC_RADIO3, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowKeyParameter 

void CDlgShowKeyParameter::OnUpdate() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateListBox();
}

void CDlgShowKeyParameter::addentry(char *bez,L_NUMBER *num)
{
	strcpy(m_data[m_entries].titel,bez);
	memcpy(m_data[m_entries].data,num,MAXLGTH*sizeof(L_NUMBER));
	m_entries++;
}

void CDlgShowKeyParameter::settitel(char *a)
{
	m_titel=a;
}

void CDlgShowKeyParameter::UpdateListBox()
{
	int i;
	
	UpdateData(TRUE);
	for (i=0;i<m_entries;i++)
	{
		char *a;

		switch (m_radio)
		{
		case 0:
			ln_to_string(m_data[i].data,&a,8);
			break;
		case 1:
			ln_to_string(m_data[i].data,&a,10);
			break;
		case 2:
			ln_to_string(m_data[i].data,&a,16);
			break;
		}
		m_listctrl.SetItemText(i,1,a);
		free(a);
	}
	UpdateData(FALSE);
}

BOOL CDlgShowKeyParameter::OnInitDialog() 
{
	int i;
	CDialog::OnInitDialog();

	m_listctrl.DeleteAllItems();
	LoadString(AfxGetInstanceHandle(),IDS_STRING_VARIABLE,pc_str,STR_LAENGE_STRING_TABLE);
	m_listctrl.InsertColumn(0,pc_str,LVCFMT_RIGHT,50,0);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_VALUE,pc_str,STR_LAENGE_STRING_TABLE);
	m_listctrl.InsertColumn(1,pc_str,LVCFMT_LEFT,375,1);

	//disableOKButton wird in CDlgHybridEncryptionDemo auf true gesetzt.
	//dieser Abschnitt modifiziert den Dialog für die Anzeige bei der
	//Hybridverschlüsselung
    if(disableOkButton)
	{
		m_ctrlOK.ShowWindow(false);
	}

	for (i=0;i<m_entries;i++)
		m_listctrl.InsertItem(i,m_data[i].titel);
	disableOkButton = false;
	UpdateListBox();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
} 