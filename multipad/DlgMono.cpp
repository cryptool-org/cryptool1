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
	m_check = 0;
	//}}AFX_DATA_INIT
}


void CDlgMono::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMono)
	DDX_Control(pDX, IDC_EDIT1, m_edit2);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDX_Radio(pDX, IDC_RADIO1, m_check);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMono, CDialog)
	//{{AFX_MSG_MAP(CDlgMono)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgMono 


void CDlgMono::OnChangeEdit1() 
{
	// TODO: Wenn es sich hierbei um ein RICHEDIT-Steuerelement handelt, sendet es
	// sendet diese Benachrichtigung nur, wenn die Funktion CDialog::OnInitDialog()
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
				//AfxMessageBox(m_edit);
				UpdateData(FALSE);
				m_edit2.SetSel(i,i);
				break;
			}
		}
	}
}