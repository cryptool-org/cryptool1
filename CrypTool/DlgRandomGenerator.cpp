/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


// DlgGenRandomData.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif
#include "FileTools.h"
#include "s_prng.h"
#include "DlgRandomGenerator.h"
#include "DlgRandomParameterSECUDE.h"
#include "Cryptography.h"
#include "CryptDoc.h"
#include "DlgPrimesGeneratorDemo.h"
#include "DlgShowProgress.h"
#include "CrypToolTools.h"
#include ".\dlgrandomgenerator.h"

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
	char	outfile[256], outfile2[256];
	RandPar* par = static_cast<RandPar*>(pParam);
	GetTmpName(outfile,"cry",".hex");
	ofstream rndData(outfile, ios::binary);
	ofstream rndState;
	CString  rndStateStr;

	if ( par->m_SelGenerator && par->m_PrintInternalStates )
	{
		GetTmpName(outfile2, "cry", ".txt");
		rndState.open( outfile2 );
	}
	unsigned char	o;
	long			i, j, k(0), l;
	progress.LoadString(IDS_RAND_PROGRESS);

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
			title.Format(IDS_RAND_GEN_PARAM, "X^2 (mod N)", par->m_DataSize);
			theApp.fs.Display(LPCTSTR(title));
			par->rnd_x2modN.setSeed( par->m_seed );
			if ( par->m_PrintInternalStates )
			{
				par->rnd_x2modN.randIntStr(rndStateStr);
				rndState << rndStateStr << " ";
			}
			for ( j=0; j<par->m_DataSize; j++ )
			{
				o=0;
				for (i=0; i<8; i++) {
					par->rnd_x2modN.randomize();
					o |= par->rnd_x2modN.randBit() << (7-i);
					if ( par->m_PrintInternalStates )
					{
						par->rnd_x2modN.randIntStr(rndStateStr);
						rndState << rndStateStr << " ";
					}
				}
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
		title.Format(IDS_STRING_RAND_DATA_PARAM, "X^2 (mod N)", par->m_DataSize);
		break;
	case 2:
		{
			title.Format(IDS_RAND_GEN_PARAM, "LCG", par->m_DataSize);
			theApp.fs.Display(LPCTSTR(title));
			Out = par->DLCG.setSeed( par->m_seed );
			if ( par->m_PrintInternalStates )
			{
				par->DLCG.randIntStr(rndStateStr);
				rndState << rndStateStr << " ";
			}
			for(j=0;j<par->m_DataSize;j++)
			{
				o = 0;
				for (i=0; i<8; i++) {
					par->DLCG.randomize();
					o |= par->DLCG.randBit() << (7-i);
					if ( par->m_PrintInternalStates )
					{
						par->DLCG.randIntStr(rndStateStr);
						rndState << rndStateStr << " ";
					}
				}
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
			if ( par->m_PrintInternalStates )
			{
				par->DICG.randIntStr(rndStateStr);
				rndState << rndStateStr << " ";
			}
			for(j=0;j<par->m_DataSize*9;j++)
			{
				o=0;
				for (i=0; i<8 ; i++)
				{
					par->DICG.randomize();
					o |= par->DICG.randBit() << (7-i);
					if ( par->m_PrintInternalStates )
					{
						par->DICG.randIntStr(rndStateStr);
						rndState << rndStateStr << " ";
					}
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
	if ( par->m_PrintInternalStates )
		rndState.close();

	if(!theApp.fs.m_canceled) 
	{
		if ( par->m_PrintInternalStates )
			theApp.ThreadOpenDocumentFileNoMRU(outfile2, title);	
		theApp.ThreadOpenDocumentFileNoMRU(outfile,title);
	}    
	theApp.fs.cancel();

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "RandomGenerator" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(par->m_seed.GetBuffer(), "RandSeed");
		CT_WRITE_REGISTRY((unsigned int)par->m_DataSize, "GenerateBytes");
		CT_WRITE_REGISTRY((unsigned int)par->m_PrintInternalStates, "ShowInternalRandState");
		CT_WRITE_REGISTRY((unsigned int)par->m_SelGenerator, "SelGenerator");

		CT_WRITE_REGISTRY(par->DRPXN.m_EditModul_N.GetBuffer(), "ParamX2MODN_N");

		CT_WRITE_REGISTRY(par->DRP_LCG.m_LinParam_a.GetBuffer(), "ParamLCG_P1");
		CT_WRITE_REGISTRY(par->DRP_LCG.m_LinParam_b.GetBuffer(), "ParamLCG_P2");
		CT_WRITE_REGISTRY(par->DRP_LCG.m_LinParam_N.GetBuffer(), "ParamLCG_N");

		CT_WRITE_REGISTRY(par->DRP_ICG.m_Param_a.GetBuffer(), "ParamICG_P1");
		CT_WRITE_REGISTRY(par->DRP_ICG.m_Param_b.GetBuffer(), "ParamICG_P2");
		CT_WRITE_REGISTRY(par->DRP_ICG.m_Param_N.GetBuffer(), "ParamICG_N");

		CT_CLOSE_REGISTRY();
	}


	delete par;
	par = 0;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRandomGenerator 


CDlgRandomGenerator::CDlgRandomGenerator(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRandomGenerator::IDD, pParent)
	, m_PrintInternalStates(false)
{
	//{{AFX_DATA_INIT(CDlgRandomGenerator)
	m_SelGenerator = 1;
	m_seed = _T("314159");
	m_DataSize = 2500;
	//}}AFX_DATA_INIT
	m_pPara = new (RandPar);
}


void CDlgRandomGenerator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRandomGenerator)
	DDX_Control(pDX, IDC_RADIO1, m_CtrlSecudeGenerator);
	DDX_Control(pDX, IDC_EDIT1, m_seed_ctrl);
	DDX_Radio(pDX, IDC_RADIO1, m_SelGenerator);
	DDX_Text(pDX, IDC_EDIT1, m_seed);
	DDX_Text(pDX, IDC_EDIT2, m_DataSize);
	DDV_MinMaxLong(pDX, m_DataSize, 1, 1048576);
	DDX_Check(pDX, IDC_CHECK1, m_PrintInternalStates);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CHECK1, m_ctrlSetInternalStates);
}


BEGIN_MESSAGE_MAP(CDlgRandomGenerator, CDialog)
	//{{AFX_MSG_MAP(CDlgRandomGenerator)
	ON_BN_CLICKED(IDC_BUTTON1, OnSelGenParam)
	ON_BN_CLICKED(IDOK, OnGenRandomData)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnBnClickedRadio4)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgRandomGenerator 

void CDlgRandomGenerator::OnSelGenParam() 
{
	UpdateData(TRUE);

	switch (m_SelGenerator) {
	case 0: {
				CDlgRandomParameterSECUDE DPRS;
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
					m_pPara->DICG.SetParameter(m_pPara->DRP_ICG.Get_a(), m_pPara->DRP_ICG.Get_b(), m_pPara->DRP_ICG.Get_N());
				}

		break;
			}
	UpdateData(FALSE);
	}
}


void CDlgRandomGenerator::OnGenRandomData() 
{
	UpdateData(TRUE);
	m_pPara->m_DataSize				= m_DataSize;
	m_pPara->m_SelGenerator			= m_SelGenerator;
	m_pPara->m_seed					= m_seed;
	m_pPara->m_PrintInternalStates	= m_PrintInternalStates;
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

void CDlgRandomGenerator::OnCancel() 
{
	delete m_pPara;
	
	CDialog::OnCancel();
}

BOOL CDlgRandomGenerator::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "RandomGenerator" ) == ERROR_SUCCESS )
	{
		char tmpStr1[2048], tmpStr2[2048], tmpStr3[2048];  
		unsigned long dataSize, outputInternalState, randomGeneratorTypeID, l;

		l = 2047; 
		CT_READ_REGISTRY_DEFAULT(tmpStr1, "RandSeed", "314159", l);
		dataSize = 2500; 
		CT_READ_REGISTRY_DEFAULT(dataSize, "GenerateBytes", 2500);
		outputInternalState = 1;
		CT_READ_REGISTRY_DEFAULT(outputInternalState, "ShowInternalRandState", 1);
		randomGeneratorTypeID = 0;
		CT_READ_REGISTRY_DEFAULT(randomGeneratorTypeID, "SelGenerator", 0);
		UpdateData(true);
		m_seed					= tmpStr1;
		m_DataSize				= dataSize;
		m_PrintInternalStates	= outputInternalState;
		m_SelGenerator			= randomGeneratorTypeID;

		l = 2047;
		CT_READ_REGISTRY_DEFAULT(tmpStr1, "ParamX2MODN_N", STANDARD_X2MOD_N_MODUL, l);
		m_pPara->DRPXN.SetModul(CString(tmpStr1));

		l = 2047; 
		CT_READ_REGISTRY_DEFAULT(tmpStr1, "ParamLCG_P1", "23", l);
		l = 2047; 
		CT_READ_REGISTRY_DEFAULT(tmpStr2, "ParamLCG_P2", "0", l);
		l = 2047; 
		CT_READ_REGISTRY_DEFAULT(tmpStr3, "ParamLCG_N", "100000001", l);
		// LCG-Parameter nach Lehmer
		m_pPara->DRP_LCG.m_LinParam_a = tmpStr1;
		m_pPara->DRP_LCG.m_LinParam_b = tmpStr2;
		m_pPara->DRP_LCG.m_LinParam_N = tmpStr3;

		l = 2047; CT_READ_REGISTRY_DEFAULT(tmpStr1, "ParamICG_P1", "22211", l);
		l = 2047; CT_READ_REGISTRY_DEFAULT(tmpStr2, "ParamICG_P2", "11926380", l);
		l = 2047; CT_READ_REGISTRY_DEFAULT(tmpStr3, "ParamICG_N", "2147483053", l);
		// ICG-Parameter nach ???
		m_pPara->DRP_ICG.m_Param_a = tmpStr1;
		m_pPara->DRP_ICG.m_Param_b = tmpStr2;
		m_pPara->DRP_ICG.m_Param_N = tmpStr3;

		UpdateData(false);
		CT_CLOSE_REGISTRY();
	}

    if(theApp.SecudeStatus == 2) 
	{
		m_CtrlSecudeGenerator.EnableWindow(TRUE);
	}
	else 
	{
		m_CtrlSecudeGenerator.EnableWindow(FALSE);
		if ( m_SelGenerator == 0 )
		{
			UpdateData();
			m_SelGenerator = 1;
			UpdateData(FALSE);
		}
	}
	OnBnClickedRadio1();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgRandomGenerator::OnBnClickedRadio1()
{
	UpdateData();
	if ( m_SelGenerator )
		m_ctrlSetInternalStates.EnableWindow();
	else
	{
		m_PrintInternalStates = 0;
		m_ctrlSetInternalStates.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void CDlgRandomGenerator::OnBnClickedRadio2()
{
	OnBnClickedRadio1();
}

void CDlgRandomGenerator::OnBnClickedRadio3()
{
	OnBnClickedRadio1();
}

void CDlgRandomGenerator::OnBnClickedRadio4()
{
	OnBnClickedRadio1();
}
