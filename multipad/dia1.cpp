//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// dia1.cpp : implementation file
//

#include "stdafx.h"
#include "multipad.h"
#include "dia1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dia1 dialog


dia1::dia1(int maxlen, CWnd* pParent /*=NULL*/)
	: CDialog(dia1::IDD, pParent)
{
	char line[80];

	len = (maxlen > 0) ? maxlen : -maxlen;
	//{{AFX_DATA_INIT(dia1)
	m_text = _T("");
	m_static_text = _T("");
	//}}AFX_DATA_INIT
	if ( maxlen > 0 )
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_MAX_INPUT_LENGTH_TXT,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,len);
		m_static_text = line;
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_INPUT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,len);
		m_static_text = line;
	}
	s_alternativeWindowText[0]=0;
}


//DEL dia1::dia1(int maxlen, const long StringID, CWnd *pParent)
//DEL {
//DEL 	char line[80];
//DEL 
//DEL 	len = maxlen;
//DEL 	//{{AFX_DATA_INIT(dia1)
//DEL 	m_text = _T("");
//DEL 	m_static_text = _T("");
//DEL 	//}}AFX_DATA_INIT
//DEL 	LoadString(AfxGetInstanceHandle(),StringID,pc_str,STR_LAENGE_STRING_TABLE);
//DEL 	sprintf(line,pc_str,len);
//DEL 	m_static_text = line;
//DEL 	s_alternativeWindowText[0]=0;
//DEL }

int dia1::Display()
{
	int res;

	res=DoModal();
	return res;
}

void dia1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dia1)
	DDX_Control(pDX, IDC_EDIT1, m_text_ctl);
	DDX_Text(pDX, IDC_EDIT1, m_text);
	DDV_MaxChars(pDX, m_text, len);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_static_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dia1, CDialog)
	//{{AFX_MSG_MAP(dia1)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dia1 message handlers


char * dia1::GetData( void )
{
	return m_text.GetBuffer(MAX_VIGENERE+1);
}

int dia1::GetLen( void )
{
	return m_text.GetLength();
}

void dia1::OnUpdateEdit1() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); /* get the displayed value in m_text */
	m_text_ctl.GetSel(sels, sele);
	res.Empty();

	if(theApp.TextOptions.m_IgnoreCase) m_text.MakeUpper();

	for(k=i=0;i<m_text.GetLength();i++) {
		c = m_text[i];
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

	m_text = res;
	UpdateData(FALSE);
	m_text_ctl.SetSel(sels,sele);
} 

void dia1::OnDecrypt() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	m_Decrypt = 1;
	OnOK();
}

void dia1::OnEncrypt() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	m_Decrypt = 0;
	OnOK();
}

void dia1::SetAlternativeWindowText(LPCTSTR s_title)
{
    strncpy(s_alternativeWindowText, s_title, 126);
	s_alternativeWindowText[126]=0;
}

BOOL dia1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zus�tzliche Initialisierung hier einf�gen
	if (s_alternativeWindowText[0])
		SetWindowText(s_alternativeWindowText);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

