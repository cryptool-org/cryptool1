//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// AESSuche.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "HexEdit.h"
#include "DlgBruteForceAES.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgBruteForceAES 

CDlgBruteForceAES::CDlgBruteForceAES(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBruteForceAES::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBruteForceAES)
	m_text = _T("");
	m_text_len=96;
	m_len=0;
	//}}AFX_DATA_INIT
}

void CDlgBruteForceAES::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBruteForceAES)
	DDX_Control(pDX, IDC_EDIT1, m_text_ctl);
	DDX_Text(pDX, IDC_EDIT1, m_text);
	DDV_MaxChars(pDX, m_text, m_text_len);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBruteForceAES, CDialog)
	//{{AFX_MSG_MAP(CDlgBruteForceAES)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgBruteForceAES 

void CDlgBruteForceAES::OnUpdate() 
{
	int l, i,j, k,num;
	char c;
	CString res;

	for (i=0;i<64;i++)
		m_data[i]='0';
	for (i=0;i<6;i++)
		m_mask[i]=100;
	UpdateData(TRUE);
	for(k=i=num=l=j=0;i<m_text.GetLength();i++)
	{
		c = m_text[i];
		if((c >= 'A' && c <= 'F')||(c >= '0'&& c <= '9')||(c=='*'))
		{
			if (c== '*')
				m_mask[l++]=j;
			m_data[j++]=c;
		}
	}
	UpdateData(FALSE);

	if(j == 0) m_len=0;
	else if(j <= 32) m_len = 16;
	else if(j <= 48) m_len = 24;
	else m_len = 32;
	m_data[m_len<<1]=0;
	m_co=0;
	m_max=(1<<(l*4))-1;
}

char *CDlgBruteForceAES::GetData()
{
	return m_data;
}

void CDlgBruteForceAES::GetDataInt(char *p)
{
	int i;
	for (i=0;i<m_len*2;i++)
	{
		if (i%2)
			p[i/2]+=m_text_ctl.HexVal(m_data[i]);
		else
			p[i/2]=m_text_ctl.HexVal(m_data[i])<<4;
	}
}

int CDlgBruteForceAES::GetLen()
{
	return m_len;
}

int CDlgBruteForceAES::GetBinlen()
{
	return m_text_ctl.BinLen;
}

int CDlgBruteForceAES::Display(char *titel,int max)
{
	int res;
	m_text_len=(max*3)-1;
	res=DoModal();
	return res;
}

int CDlgBruteForceAES::Display(char *titel)
{
	int res;
	res=DoModal();
	return res;
}

int CDlgBruteForceAES::Step()
{
	int i,n,m;
	if (m_co<=m_max)
	{
		i=0;
		while((n=m_mask[i])!=100&&i<STARS)
		{
			m=(m_co>>(i*4))%16;
			m_data[n]=m>9?m-10+'A':m+'0';
			i++;
		}
		m_co++;
		return 1+(m_co*99/(m_max+1));
	}
	return 0;
}

bool CMyHexEdit::isvalidchar(char c)
{
	if ((c >= 'A' && c <= 'F')||(c >= '0'&& c <= '9'))
		return true;
	if (c=='*'&&starcount<STARS)
	{
		starcount++;
		return true;
	}
	if ((c == 8) || (c == 3) || (c == 16) || (c == 18) || (c == 22) || (c == 23)|| (c == 24))
		return true;
	if (c==0)
		starcount=0;
	return false;
}

CMyHexEdit::CMyHexEdit()
{
	starcount=0;
}
