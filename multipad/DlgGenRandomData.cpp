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
#include "DlgFortschritt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


UINT GenRandomDataThread( PVOID pParam ) // Thread-Version
{
	BOOL Out;
	CString title;
	CString progress;
	char	outfile[128];
	RandPar* par = static_cast<RandPar*>(pParam);
	GetTmpName(outfile,"rnd",".hex");
	ofstream rndData(outfile, ios::binary);
	unsigned char	o;
	long			i, j, k(0), l;
	progress.LoadString(IDS_RAND_PROGRESS);


	//LoadString(AfxGetInstanceHandle(),IDS_STRING_RAND_DATA_PARAM,pc_str,STR_LAENGE_STRING_TABLE);
	switch ( par->m_SelGenerator ) {
	case 0:
		title.Format(IDS_RAND_GEN_PARAM, "SECUDE", par->m_DataSize);
		theApp.fs.Display(LPCTSTR(title));
		for ( j=0; j<par->m_DataSize; j++ )
		{
			o=0;
			for(i=0;i<8;i++) o|=(_rand_bit())<<i;
			rndData << o;			
			if(theApp.fs.m_canceled)
			{
				theApp.fs.cancel();
				return 0;
			}
			if((l=(j*100)/par->m_DataSize)>k)            // nur einmal für jedes Prozent
			{
				theApp.fs.Set(k=l, "", progress);
			}
		}	
		title.Format(IDS_STRING_RAND_DATA_PARAM, "SECUDE", par->m_DataSize);
		break;
	case 1:
		{
			title.Format(IDS_RAND_GEN_PARAM, "x^2 (mod N)", par->m_DataSize);
			theApp.fs.Display(LPCTSTR(title));
			par->rnd_x2modN.setSeed( par->m_seed );
			for ( j=0; j<par->m_DataSize; j++ )
			{
				o=0;
				for (i=0; i<8; i++) o |= par->rnd_x2modN.randBit() << (7-i);
				rndData << o;
				if(theApp.fs.m_canceled)
				{
					theApp.fs.cancel();
					return 0;
				}
				if((l=(j*100)/par->m_DataSize)>k)            // nur einmal für jedes Prozent
				{
					theApp.fs.Set(k=l, "", progress);
				}
			}		
		}
		title.Format(IDS_STRING_RAND_DATA_PARAM, "x^2 (mod N)", par->m_DataSize);
		break;
	case 2:
		{
			title.Format(IDS_RAND_GEN_PARAM, "LCG", par->m_DataSize);
			theApp.fs.Display(LPCTSTR(title));
			Out = par->DLCG.setSeed( par->m_seed );
			for(j=0;j<par->m_DataSize;j++)
			{
				o = 0;
				for (i=0; i<8; i++) o |= par->DLCG.randBit() << (7-i);
				rndData << o;
				if(theApp.fs.m_canceled)
				{
					theApp.fs.cancel();
					return 0;
				}
				if((l=(j*100)/par->m_DataSize)>k)            // nur einmal für jedes Prozent
				{
					theApp.fs.Set(k=l, "", progress);
				}
			}
		}
		title.Format(IDS_STRING_RAND_DATA_PARAM, "LCG", par->m_DataSize);
		break;
	case 3:
		{
			title.Format(IDS_RAND_GEN_PARAM, "ICG", par->m_DataSize);
			theApp.fs.Display(LPCTSTR(title));
			Out = par->DICG.setSeed( par->m_seed );
			for(j=0;j<par->m_DataSize*9;j++)
			{
				o=0;
				for (i=0; i<8 ; i++)
				{
					o |= par->DICG.randBit() << (7-i);
					par->DICG.SetCount(j+i);
				}
				rndData << o;
				j += i; //weil j+i als SetCount gestellt wird, und m_DataSize*9 genommen ist
						//d.h. counter soll immer um 1 erhöht sein
				if(theApp.fs.m_canceled)
				{
					theApp.fs.cancel();
					return 0;
				}
				if((l=(j*100)/(par->m_DataSize*9))>k)            // nur einmal für jedes Prozent
				{
					theApp.fs.Set(k=l, "", progress);
				}
			}
		}
		title.Format(IDS_STRING_RAND_DATA_PARAM, "ICG", par->m_DataSize);
		break;
	}
	rndData.close();
    
	delete par;
	par = 0;

	if(!theApp.fs.m_canceled) theApp.ThreadOpenDocumentFileNoMRU(outfile,title);
	theApp.fs.cancel();
	return 0;
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
	m_pPara = new (RandPar);
	// x2modN-Generator
	m_pPara->DRPXN.SetModul(CString(STANDARD_X2MOD_N_MODUL));
	// LCG-Parameter nach Lehmer
    m_pPara->DLCG.SetParameter(CString("23"), CString("0"), CString("100000001"));
	// ICG-Parameter nach ???
	m_pPara->DLCG.SetParameter(CString("22211"), CString("11926380"), CString("2147483053"));
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
	UpdateData(TRUE);
	switch (m_SelGenerator) {
	case 0: {
				DlgParamRandSECUDE DPRS;
				DPRS.DoModal();
			}
			break;
	case 1: {
				if (IDOK == m_pPara->DRPXN.DoModal() )
				{
					m_pPara->rnd_x2modN.setModul( m_pPara->DRPXN.GetModul() );
				}
			}
		break;
	case 2: {
				if (IDOK == m_pPara->DRP_LCG.DoModal() )
				{
					m_pPara->DLCG.SetParameter(m_pPara->DRP_LCG.Get_a(), m_pPara->DRP_LCG.Get_b(), m_pPara->DRP_LCG.Get_N());
				}
			}
		break;
	case 3: {
				if (IDOK == m_pPara->DRP_ICG.DoModal() )
				{
					GeneratePrimes P;
					P.SetP(m_pPara->DRP_ICG.Get_N());
					BOOL test=FALSE;
					test = P.MillerRabinTest(100);
					test = P.SolvayStrassenTest(100);
					test = P.FermatTest(100);

					if (test) m_pPara->DICG.SetParameter(m_pPara->DRP_ICG.Get_a(), m_pPara->DRP_ICG.Get_b(), m_pPara->DRP_ICG.Get_N());
					else 
					{
						AfxMessageBox("Keine Primzahl ist für P eingegeben, die Initialwerte werden aufgeruft !!!");
						m_pPara->DRP_ICG.Set(CString("22211"), CString("11926380"),CString("2147483053"));
					}
				}

		break;
			}
	UpdateData(FALSE);
	}
}


void DlgGenRandomData::OnGenRandomData() 
{
	UpdateData(TRUE);
	m_pPara->m_DataSize = m_DataSize;
	m_pPara->m_SelGenerator = m_SelGenerator;
	m_pPara->m_seed = m_seed;
	UpdateData(FALSE);
	if ( m_DataSize >= 1 && m_DataSize < 1048576 )
	{
		// theApp.OpenBGFlag = 1; Peer Fragen
		AfxBeginThread( GenRandomDataThread, PVOID(m_pPara) );
		CDialog::OnOK();
	}
	else
	{
		// Fehlermeldung erscheint aufgrund der RessourcenSchranken :)
	}
}

void DlgGenRandomData::OnCancel() 
{
	delete m_pPara;
	
	CDialog::OnCancel();
}
