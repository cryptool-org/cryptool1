//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DialogVienereKey.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DialogVienereKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogVienereKey 


CDialogVienereKey::CDialogVienereKey(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogVienereKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogVienereKey)
	m_Str = _T("");
	//}}AFX_DATA_INIT
}


void CDialogVienereKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogVienereKey)
	DDX_Control(pDX, IDC_EDIT1, m_text_ctl);
	DDX_Text(pDX, IDC_EDIT1, m_Str);
	DDV_MaxChars(pDX, m_Str, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogVienereKey, CDialog)
	//{{AFX_MSG_MAP(CDialogVienereKey)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDialogVienereKey  
void CDialogVienereKey::OnUpdateEdit1() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); /* get the displayed value in m_text */
	m_text_ctl.GetSel(sels, sele);
	res.Empty();

	if(theApp.TextOptions.m_IgnoreCase) m_Str.MakeUpper();

	for(k=i=0;i<m_Str.GetLength();i++) {
		c = m_Str[i];
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

	m_Str = res;
	UpdateData(FALSE);
	m_text_ctl.SetSel(sels,sele);
}
