// AESSuche.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "HexEdit1.h"
#include "AESSuche.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld AESSuche 


AESSuche::AESSuche(CWnd* pParent /*=NULL*/)
	: CDialog(AESSuche::IDD, pParent)
{
	//{{AFX_DATA_INIT(AESSuche)
	m_text = _T("");
	m_text_len=96;
	m_len=0;
	//}}AFX_DATA_INIT
}

void AESSuche::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AESSuche)
	DDX_Control(pDX, IDC_EDIT1, m_text_ctl);
	DDX_Text(pDX, IDC_EDIT1, m_text);
	DDV_MaxChars(pDX, m_text, m_text_len);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AESSuche, CDialog)
	//{{AFX_MSG_MAP(AESSuche)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten AESSuche 

void AESSuche::OnUpdate() 
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

char *AESSuche::GetData()
{
	return m_data;
}

void AESSuche::GetDataInt(char *p)
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

int AESSuche::GetLen()
{
	return m_len;
}

int AESSuche::GetBinlen()
{
	return m_text_ctl.BinLen;
}

int AESSuche::Display(char *titel,int max)
{
	int res;

	m_text_len=(max*3)-1;

	res=DoModal();

	return res;
}

int AESSuche::Display(char *titel)
{
	int res;

	res=DoModal();

	return res;
}

int AESSuche::Step()
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
