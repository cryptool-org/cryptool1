//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DialogLaengeBin.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DialogLaengeBin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgBinKeyLength 


CDlgBinKeyLength::CDlgBinKeyLength(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBinKeyLength::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBinKeyLength)
	m_Char = _T("00");
	m_laenge = 0;
	//}}AFX_DATA_INIT
}


void CDlgBinKeyLength::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBinKeyLength)
	DDX_Control(pDX, IDC_EDIT2, m_Ctl);
	DDX_Text(pDX, IDC_EDIT2, m_Char);
	DDV_MaxChars(pDX, m_Char, 2);
	DDX_Text(pDX, IDC_EDIT1, m_laenge);
	DDV_MinMaxUInt(pDX, m_laenge, 1, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBinKeyLength, CDialog)
	//{{AFX_MSG_MAP(CDlgBinKeyLength)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgBinKeyLength 

void CDlgBinKeyLength::OnChangeEdit2() 
{
	int i;
	char c;

	UpdateData(TRUE);  // Werte aus Eingabemaske lesen

	for(i=0;i<m_Char.GetLength();i++) {
		c=m_Char[i];
		if(!((('0'<=c) && (c <='9'))||(('A'<=c)&&(c<='F')))) m_Ctl.Undo();
	}
}

void CDlgBinKeyLength::OnOK() 
{
	int i;
	char c;

	m_c = 0;

	UpdateData(TRUE);  // Werte aus Eingabemaske lesen

	for(i=0;i<m_Char.GetLength();i++) {
		c = m_Char[i];
		if(('0'<=c) && (c<='9')) m_c = m_c*16 + (c-'0');
		if(('A'<=c) && (c<='F')) m_c = m_c*16 + (c-'A') + 10;
	}
	
	CDialog::OnOK();
} 