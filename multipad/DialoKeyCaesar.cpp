//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DialoKeyCaesar.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DialoKeyCaesar.h"
// #include "DlgPrimesGenerator.h" // ## Weg 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialoKeyCaesar 


CDialoKeyCaesar::CDialoKeyCaesar(CWnd* pParent /*=NULL*/)
	: CDialog(CDialoKeyCaesar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialoKeyCaesar)
	m_string = _T("");
	//}}AFX_DATA_INIT
}


void CDialoKeyCaesar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialoKeyCaesar)
	DDX_Control(pDX, IDC_EDIT1, m_text_ctl);
	DDX_Text(pDX, IDC_EDIT1, m_string);
	DDV_MaxChars(pDX, m_string, 1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialoKeyCaesar, CDialog)
	//{{AFX_MSG_MAP(CDialoKeyCaesar)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDialoKeyCaesar 

void CDialoKeyCaesar::OnUpdateEdit1() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); /* get the displayed value in m_text */
	m_text_ctl.GetSel(sels, sele);
	res.Empty();

	if(theApp.TextOptions.m_IgnoreCase) m_string.MakeUpper();

	for(k=i=0;i<m_string.GetLength();i++) {
		c = m_string[i];
		if(AppConv.IsInAlphabet(c)) { // valid character
			res += c;
			k++;
		}
		else { // invalid character
			MessageBeep(MB_OK);
			if(k<sels) sels--;
			if(k<sele) sele--;
		}
	}

	m_string = res;
	UpdateData(FALSE);
	m_text_ctl.SetSel(sels,sele);
}
