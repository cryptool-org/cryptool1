// AnalyseNGram.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "fileutil.h"
#include "AnalyseNGram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld AnalyseNGram 


AnalyseNGram::AnalyseNGram(CWnd* pParent /*=NULL*/)
	: CDialog(AnalyseNGram::IDD, pParent)
{
	//{{AFX_DATA_INIT(AnalyseNGram)
		m_N_NGram      = 0;
	    m_ShowCntNGram = 20;
		m_NrNGram      = 3;
	//}}AFX_DATA_INIT
	b_SaveNGramList = false;
}


void AnalyseNGram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AnalyseNGram)
	DDX_Control(pDX, IDC_EDIT2, m_NrNGramCtrl);
		DDX_Control(pDX, IDC_LIST1,  m_ListView);
	    DDX_Radio  (pDX, IDC_RADIO1, m_N_NGram);
	    DDX_Text(pDX, IDC_EDIT1, m_ShowCntNGram);
	    DDV_MinMaxLong(pDX, m_ShowCntNGram, 0, 2147483647);
		DDX_Text(pDX, IDC_EDIT2, m_NrNGram);
		DDV_MinMaxLong(pDX, m_NrNGram, 3, 3);
	//}}AFX_DATA_MAP
	toAnalyze = 0;
	SA = 0;
}


BEGIN_MESSAGE_MAP(AnalyseNGram, CDialog)
	//{{AFX_MSG_MAP(AnalyseNGram)
		ON_BN_CLICKED(IDC_BUTTON2, OnEvalNGram)
		ON_BN_CLICKED(IDOK, OnSaveNGramList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten AnalyseNGram 

int AnalyseNGram::DoModal() 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	
	return CDialog::DoModal();
}

BOOL AnalyseNGram::OnInitDialog()
{
	int colWidth = 100;										// Spaltenbreite in Pixel

	CDialog::OnInitDialog();

	LoadString(AfxGetInstanceHandle(),IDS_STRING_HOMOPHONE_NR,pc_str,STR_LAENGE_STRING_TABLE);
	m_ListView.InsertColumn(1,pc_str,LVCFMT_LEFT,colWidth-32,1);							// Zeichen
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_LIST2,pc_str,STR_LAENGE_STRING_TABLE);
	m_ListView.InsertColumn(2,pc_str,LVCFMT_LEFT,colWidth-40,2);							// Anzahl
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_LIST3,pc_str,STR_LAENGE_STRING_TABLE);
	m_ListView.InsertColumn(3,pc_str,LVCFMT_LEFT,colWidth+2000,3);						
	SetupListBox( m_N_NGram+1 );
	m_NrNGramCtrl.EnableWindow(false);
	return(TRUE);

}


void AnalyseNGram::LoadText(SymbolArray & text, BOOL BinaryFile )
{
	textRef  = &text;  
	isBinary = BinaryFile;
}

void AnalyseNGram::SetupListBox( int N )
{
	char string[100];
	int  i,j;
	l_N = N;

	if ( toAnalyze ) delete toAnalyze;
	toAnalyze = new NGram( *textRef, N );

	if ( SA ) delete SA;
	SA = new SortedArray<double>( *toAnalyze );
	l_DispNGrams = (m_ShowCntNGram < toAnalyze->GetSize()) ? m_ShowCntNGram : toAnalyze->GetSize();

	m_ListView.DeleteAllItems(); 

	for (i=0; i<l_DispNGrams; i++)
	{
		sprintf(string, "%3i", i+1);
		j=m_ListView.InsertItem(i,string);

		int i_Ndx = SA->GetIndex(i);
		int nr = i_Ndx;
		if ( isBinary )
		{
			for (int k=0; k<N; k++)	
			{
				char ch; 
				long c = nr % 16;

				nr /= 16;
				if (c<10)
				{
					ch = '0'+(char)c;
				}
				else
				{
					c-= 10; 
					ch = 'A'+(char)c;
				} 
				string[4*k+1] = ch;

				c = nr % 16;
				nr /= 16;
				if (c<10)
				{
					ch = '0'+(char)c;
				}
				else
				{
					c-= 10; 
					ch = 'A'+(char)c;
				} 
				string[4*k] = ch;

				if (k+1<N) 
				{
					string[4*k+2] = ',';
					string[4*k+3] = ' ';
				}
			}
			string[4*N-2] = 0;
		}
		else
		{
			for (int k=0; k<N; k++)
			{
				string[N-(k+1)] = AppConv.Conv(nr % AppConv.GetModulus());
				nr /= AppConv.GetModulus();
			}
			string[N] = 0;
		}
		m_ListView.SetItemText(j,1,string);
		sprintf(string,"%2.3f", toAnalyze->GetFrequency(i_Ndx)*100.0);
		m_ListView.SetItemText(j,2,string);
	}
}

int AnalyseNGram::GetN()
{
	return m_N_NGram;
}

void AnalyseNGram::OnEvalNGram() 
{
	theApp.DoWaitCursor(1);
	UpdateData(TRUE);
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
    if ( m_N_NGram < 3 )
	{
		SetupListBox( m_N_NGram +1 );
	}
	else
	{
		SetupListBox( m_NrNGram );
	}
	UpdateData(FALSE);
	theApp.DoWaitCursor(-1);
}

void AnalyseNGram::OnSaveNGramList() 
{
	theApp.DoWaitCursor(1);
	b_SaveNGramList = true;
	
	GetTmpName(outfile,"NGram",".tmp");
	ofstream txt_NGram(outfile);
	txt_NGram << " " << l_N << "-Gramm Analyse von .... \n\n";
	char string[100];

	if ( toAnalyze ) delete toAnalyze;
	toAnalyze = new NGram( *textRef, l_N );
	if ( SA ) delete SA;
	SA = new SortedArray<double>( *toAnalyze );

	for ( int i=0; i<l_DispNGrams; i++ )
	{
		txt_NGram << i+1 << "\t";

		int i_Ndx = SA->GetIndex(i);
		int nr = i_Ndx;
		if ( isBinary )
		{
			for (int k=0; k<l_N; k++)	
			{
				char ch; 
				long c = nr % 16;

				nr /= 16;
				if (c<10)
				{
					ch = '0'+(char)c;
				}
				else
				{
					c-= 10; 
					ch = 'A'+(char)c;
				} 
				string[4*k+1] = ch;

				c = nr % 16;
				nr /= 16;
				if (c<10)
				{
					ch = '0'+(char)c;
				}
				else
				{
					c-= 10; 
					ch = 'A'+(char)c;
				} 
				string[4*k] = ch;

				if (k+1<l_N) 
				{
					string[4*k+2] = ',';
					string[4*k+3] = ' ';
				}
			}
			string[4*l_N-2] = 0;
		}
		else
		{
			for (int k=0; k<l_N; k++)
			{
				string[l_N-(k+1)] = AppConv.Conv(nr % AppConv.GetModulus());
				nr /= AppConv.GetModulus();
			}
			string[l_N] = 0;
		}
		txt_NGram << string << "\t";
		txt_NGram << toAnalyze->GetFrequency(i_Ndx)*100.0 << "\n";
	}

	txt_NGram.close();
	theApp.DoWaitCursor(-1);
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CDialog::OnOK();
}

AnalyseNGram::~AnalyseNGram()
{
	if ( toAnalyze ) delete toAnalyze;
	if ( SA ) delete SA;
}

bool AnalyseNGram::b_saveNGramList()
{
	return b_SaveNGramList;
}
