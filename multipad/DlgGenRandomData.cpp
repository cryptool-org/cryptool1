// DlgGenRandomData.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "iostream.h"
#include "fileutil.h"
#include "s_prng.h"
#include "DlgGenRandomData.h"
#include "DlgParamRandSECUDE.h"
#include "DlgRandParameter_x2_mod_N.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// später raus !
long multmodn(long a, long b, long n)
{
	long s,t,u;

	if(b<a)
	{
		t=b;
		u=a;
	}
	else
	{
		t=a;
		u=b;
	}
	s=0;
	while(t)
	{
		if(t&1)
			s=(s+u)%n;
		u=(u+u)%n;
		t>>=1;
	}
	return s;
}

long powermod(long a, long x, long n)
{
	unsigned long s,t,u;
	
	s=1;
	t=a;
	u=x;
	
	while(u)
	{
		if(u&1)
			s=multmodn(s,t,n);
		u>>=1;
		t=multmodn(t,t,n);
	}
	return(s);
}



/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgGenRandomData 


DlgGenRandomData::DlgGenRandomData(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGenRandomData::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgGenRandomData)
	m_SelGenerator = 0;
	m_seed = _T("");
	m_DataSize = 1024;
	//}}AFX_DATA_INIT
	l_modul_x2_mod_N = 718335467;
}


void DlgGenRandomData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGenRandomData)
	DDX_Control(pDX, IDC_EDIT1, m_seed_ctrl);
	DDX_Radio(pDX, IDC_RADIO1, m_SelGenerator);
	DDX_Text(pDX, IDC_EDIT1, m_seed);
	DDX_Text(pDX, IDC_EDIT2, m_DataSize);
	DDV_MinMaxLong(pDX, m_DataSize, 1, 1048576);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgGenRandomData, CDialog)
	//{{AFX_MSG_MAP(DlgGenRandomData)
	ON_BN_CLICKED(IDC_BUTTON1, OnSelGenParam)
	ON_BN_CLICKED(IDOK, OnGenRandomData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten DlgGenRandomData 

void DlgGenRandomData::OnSelGenParam() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(TRUE);
	switch (m_SelGenerator) {
	case 0: {
				DlgParamRandSECUDE DPRS;
				DPRS.DoModal();
			}
			break;
	case 1: {
				DlgRandParameter_x2_mod_N DRPXN;
				DRPXN.SetModul(l_modul_x2_mod_N); 
				DRPXN.DoModal();
				l_modul_x2_mod_N = DRPXN.GetModul();
			}
		break;
	case 2:
		break;
	case 3:
		break;
	}
	UpdateData(FALSE);
}


void DlgGenRandomData::OnGenRandomData() 
{
	UpdateData(TRUE);

	GetTmpName(outfile,"rnd",".hex");
	ofstream rndData(outfile);
	unsigned char	o;
	long			i, j, l;

	switch ( m_SelGenerator ) {
	case 0:
		for ( j=0; j<m_DataSize; j++ )
		{
			o=0;
			for(i=0;i<8;i++)
				o|=(_rand_bit())<<i;
			rndData << o;
		}	
		break;
	case 1:
		{
			long l_seed = 31459;
			long l_s = l_seed;
			l = 0;
			for(j=0;j<m_DataSize;j++)
			{
				o = 0;
				for (i=0; i<8; i++)
				{
					l_s = powermod(l_s, 2, l_modul_x2_mod_N);
					o |= (l_s %2) << (7-i);
				}
				rndData << o;
			}
			l_seed = l_s;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	}
	rndData.close();

	UpdateData(FALSE);
	CDialog::OnOK();
}
