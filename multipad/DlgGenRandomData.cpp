// DlgGenRandomData.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "iostream.h"
#include "fileutil.h"
#include "s_prng.h"
#include "DlgGenRandomData.h"
#include "DlgParamRandSECUDE.h"
#include "ExtEuclid.h"
#include "crypt.h"
#include "cryptdoc.h"
#include "DlgPrimesGenerator.h"

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

long inverse( long a, long b )
{
	ExtEuclid Euclid(a, b);
	return Euclid.get_u();
}

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgGenRandomData 


DlgGenRandomData::DlgGenRandomData(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGenRandomData::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgGenRandomData)
	m_SelGenerator = 0;
	m_seed = _T("314159");
	m_DataSize = 2500;
	//}}AFX_DATA_INIT
// x2modN-Generator
	DRPXN.SetModul(CString(STANDARD_X2MOD_N_MODUL));
// LCG-Parameter nach Lehmer
    DLCG.SetParameter(CString("23"), CString("0"), CString("100000001"));
// ICG-Parameter nach ???
	DLCG.SetParameter(CString("22211"), CString("11926380"), CString("2147483053"));
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
				if (IDOK == DRPXN.DoModal() )
					rnd_x2modN.setModul( DRPXN.GetModul() );
			}
		break;
	case 2: {
				if (IDOK == DRP_LCG.DoModal() )
				{
					DLCG.SetParameter(DRP_LCG.Get_a(), DRP_LCG.Get_b(), DRP_LCG.Get_N());
				}
			}
		break;
	case 3: {
				if (IDOK == DRP_ICG.DoModal() )
				{
					GeneratePrimes P;
					P.SetP(DRP_ICG.Get_N());
					BOOL test=FALSE;
					test = P.MillerRabinTest(100);
					test = P.SolvayStrassenTest(100);
					test = P.FermatTest(100);

					if (test) DICG.SetParameter(DRP_ICG.Get_a(), DRP_ICG.Get_b(), DRP_ICG.Get_N());
					else 
					{
						AfxMessageBox("Keine Primzahl ist für P eingegeben, die Initialwerte werden aufgeruft !!!");
						DRP_ICG.Set(CString("22211"), CString("11926380"),CString("2147483053"));
					}
				}

		break;
			}
	UpdateData(FALSE);
	}
}


void DlgGenRandomData::OnGenRandomData() 
{
	theApp.DoWaitCursor(1);
	UpdateData(TRUE);
	GenRandomData();
	UpdateData(FALSE);
	theApp.DoWaitCursor(-1);
	CDialog::OnOK();
}

const char * DlgGenRandomData::GetRandInfo()
{
	return c_generated_by;
}

void DlgGenRandomData::GenRandomData()
{

	GetTmpName(outfile,"rnd",".hex");
	ofstream rndData(outfile, ios::binary);
	unsigned char	o;
	long			i, j;

	LoadString(AfxGetInstanceHandle(),IDS_STRING_RAND_DATA_PARAM,pc_str,STR_LAENGE_STRING_TABLE);
	switch ( m_SelGenerator ) {
	case 0:
		for ( j=0; j<m_DataSize; j++ )
		{
			o=0;
			for(i=0;i<8;i++)
				o|=(_rand_bit())<<i;
			rndData << o;
		}	
		sprintf(c_generated_by, pc_str, "SECUDE", m_DataSize);
		break;
	case 1:
		{
			rnd_x2modN.setSeed( m_seed );
			for ( j=0; j<m_DataSize; j++ )
			{
				o=0;
				for (i=0; i<8; i++) o |= rnd_x2modN.randBit() << (7-i);
				rndData << o;
			}
		}
		sprintf(c_generated_by, pc_str, "x^2 (mod N)", m_DataSize);
		break;
	case 2:
		{
			DLCG.setSeed( m_seed );
			for(j=0;j<m_DataSize;j++)
			{
				o = 0;
				for (i=0; i<8; i++) o |= DLCG.randBit() << (7-i);
				rndData << o;
			}
		}
		sprintf(c_generated_by, pc_str, "LCG", m_DataSize);
		break;
	case 3:
		{
			DICG.setSeed( m_seed );
			for(j=0;j<m_DataSize*9;j++)
			{
				o=0;
				for (i=0; i<8 ; i++)
				{
					o |= DICG.randBit() << (7-i);
					DICG.SetCount(j+i);
				}
				rndData << o;
				j += i; //weil j+i als SetCount gestellt wird, und m_DataSize*9 genommen ist
						//d.h. counter soll immer um 1 erhöht sein
			}
		}
		sprintf(c_generated_by, pc_str, "ICG", m_DataSize);
		break;
	}
	rndData.close();

}


