//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Christian Tobias
//////////////////////////////////////////////////////////////////
// Diese Quellcode-Datei enthält alle Funktionalitäten für
// die Dialogbox zur Auswahl der Analyseart bei
// monoalphabetischer Substitution.
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "multipad.h"
#include "DlgMono.h"
#include "crypt.h"
//#include "MyCEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define INIT_STRING ""

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgMono 


CDlgMono::CDlgMono(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMono::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMono)
	m_edit = _T("");
	//}}AFX_DATA_INIT
}


void CDlgMono::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMono)
	DDX_Control(pDX, IDC_EDIT1, m_edit2);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMono, CDialog)
	//{{AFX_MSG_MAP(CDlgMono)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgMono 

void CDlgMono::OnDecrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_check = 1;
	OnOK();
}

void CDlgMono::OnEncrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_check = 0;
	OnOK();
}



void CDlgMono::OnChangeEdit1() 
{
	// TODO: Wenn es sich hierbei um ein RICHEDIT-Steuerelement handelt, sendet es
	// diese Benachrichtigung nur, wenn die Funktion CDialog::OnInitDialog()
	// überschrieben wird, um die EM_SETEVENTMASK-Nachricht an das Steuerelement
	// mit dem ENM_CHANGE-Attribut ORed in die Maske lParam zu senden.
	
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
		
	UpdateData(TRUE);
	int lang=m_edit.GetLength();
	if (lang!=0){
		for (int i=0 ;i<lang; i++){
			if ((m_edit[i]<'A')||(m_edit[i]>'Z')){
				//Entfernen des fehlerhaften Zeichens.
				//Der Cursor wird anschließend an die Stelle gesetzt, an der das
				//fehlerhafte Zeichen stand.
				m_edit.SetAt(i,' ');
				m_edit=m_edit.SpanExcluding(" ")+m_edit.Right(lang-(i+1));
				UpdateData(FALSE);
				m_edit2.SetSel(i,i);
				break;
			}
		}
	}
}

BOOL CDlgMono::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString Title;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
	Title = pc_str;
	VERIFY(m_Paste.AutoLoad(IDC_BUTTON2,this));
	if ( IsKeyEmpty( Title ))
	{
		m_Paste.EnableWindow(TRUE);
	}
	else
	{
		m_Paste.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgMono::OnPasteKey() 
{
	UpdateData(TRUE);

	CString Title;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
	PasteKey(pc_str,m_edit);
	UpdateData(FALSE);	
}
