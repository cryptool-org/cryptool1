// DlgGenRandomData.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "iostream.h"
#include "fileutil.h"
#include "s_prng.h"
#include "DlgGenRandomData.h"
#include "DlgParamRandSECUDE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	switch (m_SelGenerator) {
	case 0: {
				DlgParamRandSECUDE DPRS;
				DPRS.DoModal();
			}
			break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}


void DlgGenRandomData::OnGenRandomData() 
{

	GetTmpName(outfile,"rnd",".hex");
	ofstream rndData(outfile);
	unsigned char o;
	int i;
	
	for ( int j=0; j<m_DataSize; j++ )
	{
		o=0;
		for(i=0;i<8;i++)
			o|=(_rand_bit())<<i;
		rndData << o;
	}	
	rndData.close();

	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CDialog::OnOK();
}
