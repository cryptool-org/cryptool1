// DlgDetailsFactorisation.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgDetailsFactorisation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgDetailsFactorisation 


DlgDetailsFactorisation::DlgDetailsFactorisation(CWnd* pParent /*=NULL*/)
	: CDialog(DlgDetailsFactorisation::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgDetailsFactorisation)
	m_orignNumber = _T("");
	m_factorisedNumber = _T("");
	m_Factor1isPrime = _T("");
	m_Factor2isPrime = _T("");
	m_factor2 = _T("");
	m_factor1 = _T("");
	//}}AFX_DATA_INIT
	List = NULL;
}


void DlgDetailsFactorisation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgDetailsFactorisation)
	DDX_Control(pDX, IDC_LIST1, m_FactorisationDetails);
	DDX_Text(pDX, IDC_EDIT1, m_orignNumber);
	DDX_Text(pDX, IDC_EDIT2, m_factorisedNumber);
	DDX_Text(pDX, IDC_EDIT3, m_Factor1isPrime);
	DDX_Text(pDX, IDC_EDIT5, m_Factor2isPrime);
	DDX_Text(pDX, IDC_EDIT4, m_factor2);
	DDX_Text(pDX, IDC_EDIT6, m_factor1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgDetailsFactorisation, CDialog)
	//{{AFX_MSG_MAP(DlgDetailsFactorisation)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten DlgDetailsFactorisation 

BOOL DlgDetailsFactorisation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	Init_ListBox();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void DlgDetailsFactorisation::Init_ListBox()
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

void DlgDetailsFactorisation::InsertFactDetail(CString &Num, CString &Factor1, 
		                                        CString &Factor2, CString &Method , CString &Time,
												int PrimeMask)
{
	struct DFItem *Last = new (struct DFItem);
	Last->Num     = Num;
	Last->Factor1 = Factor1;
	Last->Factor2 = Factor2;
	Last->Method  = Method;
	Last->Time    = Time;
	Last->PrimeMask = PrimeMask;
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

void DlgDetailsFactorisation::ClearFactDetail()
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


void DlgDetailsFactorisation::OnDblclkSelect(NMHDR* pNMHDR, LRESULT* pResult) 
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
	m_Factor1isPrime = pc_str;
	if ( Seek->PrimeMask & 2 )
	{
		LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_FACTORPRIME,pc_str,STR_LAENGE_STRING_TABLE);
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_DETFACTORISATION_FACTORCOMPOSITE,pc_str,STR_LAENGE_STRING_TABLE);
	}
	m_Factor2isPrime = pc_str;
	UpdateData(FALSE);
	
	*pResult = 0;
}
