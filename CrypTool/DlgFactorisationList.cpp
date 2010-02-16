/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

// DlgDetailsFactorisation.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgFactorisationList.h"
#include "FileTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFactorisationList 




CDlgFactorisationList::CDlgFactorisationList(CWnd* pParent)
 : CDialog(CDlgFactorisationList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFactorisationList)
	m_orignNumber = _T("");
	m_factorisedNumber = _T("");
	m_Factor1isPrime = _T("");
	m_Factor2isPrime = _T("");
	m_factor2 = _T("");
	m_factor1 = _T("");
	//}}AFX_DATA_INIT
	List = NULL;
	b_SaveFactorList = false;
	m_benoetigte_zeit_global = _T("");
}


void CDlgFactorisationList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFactorisationList)
	DDX_Control(pDX, IDC_LIST1, m_FactorisationDetails);
	DDX_Text(pDX, IDC_EDIT1, m_orignNumber);
	DDX_Text(pDX, IDC_EDIT2, m_factorisedNumber);
	DDX_Text(pDX, IDC_EDIT3, m_Factor1isPrime);
	DDX_Text(pDX, IDC_EDIT5, m_Factor2isPrime);
	DDX_Text(pDX, IDC_EDIT4, m_factor2);
	DDX_Text(pDX, IDC_EDIT6, m_factor1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFactorisationList, CDialog)
	//{{AFX_MSG_MAP(CDlgFactorisationList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgFactorisationList 

BOOL CDlgFactorisationList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	Init_ListBox();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CDlgFactorisationList::Init_ListBox()
// füllt die Liste auf mit
//	1.	den im Alphabet (Textoptionen) eingestellten Zeichen
//	2.	der Anzahl der ciphers, mit denen jedes Zeichen verschlüsselt werden kann
//	3.	den ciphers selbst
{
	int colWidth = 100;										// Spaltenbreite in Pixel
	char line[256];
	UpdateData();
	m_FactorisationDetails.SetExtendedStyle( LVS_EX_FULLROWSELECT ); 
	LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HLNUMBER,pc_str,STR_LAENGE_STRING_TABLE);
	m_FactorisationDetails.InsertColumn(1,pc_str,LVCFMT_LEFT,colWidth+14,1);	//Faktorisierte Zahl
	LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HLFACTOR,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line, pc_str, 1);
	m_FactorisationDetails.InsertColumn(2,line,LVCFMT_LEFT,colWidth+14,2);		// Faktor1
	sprintf(line, pc_str, 2);
	m_FactorisationDetails.InsertColumn(3,line,LVCFMT_LEFT,colWidth+14,3);		// Faktor2
	LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HLMETHOD,pc_str,STR_LAENGE_STRING_TABLE);
	m_FactorisationDetails.InsertColumn(4,pc_str,LVCFMT_LEFT,colWidth+7,4);		//Methode
	LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HLTIME,pc_str,STR_LAENGE_STRING_TABLE);
	m_FactorisationDetails.InsertColumn(5,pc_str,LVCFMT_LEFT,colWidth,5);		//Zeit

	struct DFItem *Seek = List;	
	int ndx = 0;
	while ( Seek != NULL )
	{
		int j=m_FactorisationDetails.InsertItem(ndx++,Seek->Num);
		m_FactorisationDetails.SetItemText(j,1,Seek->Factor1);
		m_FactorisationDetails.SetItemText(j,2,Seek->Factor2);
		m_FactorisationDetails.SetItemText(j,3,Seek->Method);
		m_FactorisationDetails.SetItemText(j,4,Seek->Time);
		Seek = Seek->next;
	}
	UpdateData(FALSE);
}

void CDlgFactorisationList::InsertFactDetail(CString &Num, CString &Factor1, 
		                                        CString &Factor2, CString &Method , CString &Time,
												int PrimeMask, int BitlengthF1, int BitlengthF2)
{
	struct DFItem *Last = new (struct DFItem);
	Last->Num     = Num;
	Last->Factor1 = Factor1;
	Last->Factor2 = Factor2;
	Last->Method  = Method;
	Last->Time    = Time;
	Last->PrimeMask = PrimeMask;
	Last->BitlengthF1 = BitlengthF1;
	Last->BitlengthF2 = BitlengthF2;
	Last->next    = NULL;

	
	if ( List == NULL ) 
	{
		List = Last;
	}
	else
	{
		struct DFItem *Seek = List;	
		while ( Seek->next != NULL ) Seek = Seek->next;
		Seek->next = Last;
	}
}

void CDlgFactorisationList::ClearFactDetail()
{
	struct DFItem *Seek = List;	
	while ( Seek != NULL )
	{
		List = Seek;
		Seek = Seek->next;
		delete List;
	}
	List = NULL;
}


void CDlgFactorisationList::OnDblclkSelect(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int selRow;
	int j = 0;

	{
		UINT itemState;
		// Überprüfe welches Item der Maske "mask" entspricht
		for (selRow=0; selRow < m_FactorisationDetails.GetItemCount(); selRow++)
		{
			itemState = m_FactorisationDetails.GetItemState( selRow, LVIS_FOCUSED);
			if ( (itemState & LVIS_FOCUSED) == LVIS_FOCUSED )
			{
				break; // gefunden
			}
		}
		if ( selRow == m_FactorisationDetails.GetItemCount() ) return;
	}

	struct DFItem *Seek = List;	
	while ( Seek != NULL && j < selRow ) 
	{
		Seek = Seek->next;
		j++;
	}
	if ( Seek == NULL ) return;

	{
		char line[128];
		UpdateData();
		m_factorisedNumber = Seek->Num;
		m_factor1 = Seek->Factor1;
		m_factor2 = Seek->Factor2;
		if ( Seek->PrimeMask & 1 )
		{
			LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_FACTORPRIME,pc_str,STR_LAENGE_STRING_TABLE);
		}
		else
		{
			LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_FACTORCOMPOSITE,pc_str,STR_LAENGE_STRING_TABLE);
		}
		sprintf(line, pc_str, Seek->BitlengthF1);
		m_Factor1isPrime = line;
		if ( Seek->PrimeMask & 2 )
		{
			LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_FACTORPRIME,pc_str,STR_LAENGE_STRING_TABLE);
		}
		else
		{
			LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_FACTORCOMPOSITE,pc_str,STR_LAENGE_STRING_TABLE);
		}
		sprintf(line, pc_str, Seek->BitlengthF2);
		m_Factor2isPrime = line;
		UpdateData(FALSE);
	}
	*pResult = 0;
}


#define _FACTORISATION_LIST_INDENT_BULLET "      - "
#define _FACTORISATION_LIST_INDENT        "        "

void CDlgFactorisationList::OnCancel() 
{
	
	UpdateData(TRUE);
	SHOW_HOUR_GLASS
	b_SaveFactorList = true;
	int i_No = 0;
	
	GetTmpName(outfile,"cry",".tmp");
	ofstream f_Details(outfile);

	LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HL_INPUT,pc_str,STR_LAENGE_STRING_TABLE);
    f_Details << pc_str << m_orignNumber << endl << endl;
	
	LoadString(AfxGetInstanceHandle(),IDS_FACTORISATION_LIST_DESCRIPTION,pc_str,STR_LAENGE_STRING_TABLE);
    f_Details << pc_str << endl << endl;
	struct DFItem *Seek = List;	
	while ( Seek != NULL ) 
	{
		char line[128];
		i_No++;
		f_Details << i_No << ". ";

		if ( Seek->Factor1.GetLength() > 0 )
		{
			{ // Factorized Number
				LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HL_FACTORISEDNUMBER,
					pc_str,STR_LAENGE_STRING_TABLE);
				f_Details << pc_str << Seek->Num << endl;
				LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_BITLENGTH,
					pc_str,STR_LAENGE_STRING_TABLE);
				f_Details << pc_str << " = " << int(ceil(BitLength(Seek->Num))) << endl;
				LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HLMETHOD,
					pc_str,STR_LAENGE_STRING_TABLE);
				f_Details << pc_str << ": " << Seek->Method << ".  ";
				LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HLTIME,
					pc_str,STR_LAENGE_STRING_TABLE);
				f_Details << pc_str << ": " << Seek->Time << endl;
			}
			{ // Factor 1
				LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HL_FACTOR1,
					pc_str,STR_LAENGE_STRING_TABLE);
				f_Details << _FACTORISATION_LIST_INDENT_BULLET << pc_str  << Seek->Factor1 << endl;
				if ( Seek->PrimeMask & 1 )
				{
					LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_FACTORPRIME,pc_str,STR_LAENGE_STRING_TABLE);
				}
				else
				{
					LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_FACTORCOMPOSITE,pc_str,STR_LAENGE_STRING_TABLE);
				}
				sprintf(line, pc_str, Seek->BitlengthF1);
				f_Details << _FACTORISATION_LIST_INDENT << line << endl;
			}
			{ // Factor 2
				LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HL_FACTOR2,
					pc_str,STR_LAENGE_STRING_TABLE);
				f_Details << _FACTORISATION_LIST_INDENT_BULLET << pc_str  << Seek->Factor2 << endl;
				if ( Seek->PrimeMask & 2 )
				{
					LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_FACTORPRIME,pc_str,STR_LAENGE_STRING_TABLE);
				}
				else
				{
					LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_FACTORCOMPOSITE,pc_str,STR_LAENGE_STRING_TABLE);
				}
				sprintf(line, pc_str, Seek->BitlengthF2);
				f_Details << _FACTORISATION_LIST_INDENT << line << endl << endl;		
			}
		}
		else
		{
			LoadString(AfxGetInstanceHandle(),IDS_FACTORISATION_LIST_CURRENT_FACTORISATION,
				pc_str,STR_LAENGE_STRING_TABLE);
			f_Details << pc_str << " " << Seek->Method << endl;
			LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_HLTIME,
				pc_str,STR_LAENGE_STRING_TABLE);
			f_Details << pc_str << ": " << Seek->Time << endl << endl << endl;
		}
		Seek = Seek->next;
	}

	f_Details << m_benoetigte_zeit_global << endl << endl;
	LoadString(AfxGetInstanceHandle(),IDS_FACTORISATION_LIST_RESULT,
		pc_str,STR_LAENGE_STRING_TABLE);
	f_Details << pc_str  << endl;
	f_Details << m_Factorisation << endl;

	f_Details.close();	
	CDialog::OnCancel();
}

CDlgFactorisationList::~CDlgFactorisationList()
{
	ClearFactDetail();
}
