// AnalyseNGram.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "fileutil.h"
#include "AnalyseNGram.h"
#include "crypt.h"

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
	NGramPtr = NULL;
	NGramActualized = FALSE;
}

AnalyseNGram::~AnalyseNGram()
{
	if ( NGramPtr ) delete NGramPtr;
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
	DDV_MinMaxLong(pDX, m_NrNGram, 3, 16);
	//}}AFX_DATA_MAP
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
	m_NrNGramCtrl.EnableWindow(true);
	return(TRUE);

}

// -----------------------------------------------------------------------------------------------------

void AnalyseNGram::LoadText( char *buffer, const unsigned long Size, const char *OldTitle,
							 BOOL BinaryFile )
{
	bufferRef  = buffer;  
	bufferSize = Size;
	isBinary   = BinaryFile;
	strcpy(Title, OldTitle);
}


// -----------------------------------------------------------------------------------------------------

void AnalyseNGram::Register(int N)
{
	int  i,j;
	l_N = N;

	if ( NGramPtr ) delete NGramPtr;
	if ( isBinary )
	{
		NGramPtr = new CNGram( bufferSize, (unsigned short)l_N, 256 );
		char SubStr[NGRAM_NMAX];
		SubStr[l_N] = 0;
		for ( i=0; (unsigned long)i<bufferSize; i++ )
		{
			if (i < l_N) SubStr[i] = bufferRef[i];
			else      
			{
				for ( j=1; j<l_N; j++) SubStr[j-1] = SubStr[j];
				SubStr[l_N-1] = bufferRef[i];
			}
			if ( i+1>= l_N ) // register Substring in N-Gram analysis
			{
				NGramPtr->add( SubStr );				
			}
		}
	}
	else
	{
		NGramPtr = new CNGram( bufferSize, (unsigned short)l_N, theApp.TextOptions.m_alphabet.GetLength() );
		char SubStr[NGRAM_NMAX];
		SubStr[l_N] = 0;
		int  l=0;
		for ( i=0; (unsigned long)i<bufferSize; i++ )
		{
			bool Flag = false;

			char chr = bufferRef[i];
			if ( !theApp.TextOptions.m_Case && chr >= 'a' && chr <= 'z' ) 
				chr = chr + ('A'-'a');
			for (j=0; j<theApp.TextOptions.m_alphabet.GetLength(); j++ )
				if ( chr == theApp.TextOptions.m_alphabet[j] ) 
				{ 
					Flag = true; 
					break;
				}
			if ( Flag )
			{
				if ( l<l_N ) 
				{
					SubStr[l++] = chr;
				}
				else
				{
					for ( j=1; j<l_N; j++) SubStr[j-1] = SubStr[j];
					SubStr[l_N-1] = chr;
				}
			}
			else
			{
				l=0;
			}
			if ( l>=l_N ) // register Substring in N-Gram analysis
			{
				NGramPtr->add( SubStr ); 
			}
		}

	}
	NGramPtr->sort();
}


// -----------------------------------------------------------------------------------------------------

void AnalyseNGram::SetupListBox( int N )
{
	char          string[100];
	char          SubStr[NGRAM_NMAX+1];
	unsigned long cnt;
	double        rel;
	int  i,j;

	m_ListView.DeleteAllItems(); 
	if ( !NGramActualized ) Register( N );
	
	NGramPtr->resetIterator();
	unsigned long ListSize = (m_ShowCntNGram<NGramPtr->getIndividuals()) ? m_ShowCntNGram : NGramPtr->getIndividuals();
	for (i=0; (unsigned long)i<ListSize; i++)
	{
		NGramPtr->get( SubStr, cnt, rel );

		sprintf(string, "%3i", i+1);
		j=m_ListView.InsertItem(i,string);

		if ( isBinary )
		{
			for (int k=0; k<N; k++)	
			{
				int nr = (unsigned char)SubStr[k];
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
			strcpy(string, SubStr);
		}
		m_ListView.SetItemText(j,1,string);
		sprintf(string,"%2.3f", rel*100.0);
		m_ListView.SetItemText(j,2,string);
	}
}


// -----------------------------------------------------------------------------------------------------

int AnalyseNGram::GetN()
{
	return m_N_NGram;
}


// -----------------------------------------------------------------------------------------------------

void AnalyseNGram::OnEvalNGram() 
{
	theApp.DoWaitCursor(1);
	UpdateData(TRUE);
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
    if ( m_N_NGram > 2 )
	{
		if ( m_NrNGram > NGRAM_NMAX ) 
		{
			m_NrNGram = NGRAM_NMAX;
		}
		SetupListBox( m_NrNGram );
	}
	else
	{
		SetupListBox( m_N_NGram+1 );
	}
	UpdateData(FALSE);
	theApp.DoWaitCursor(-1);
}


// -----------------------------------------------------------------------------------------------------

void AnalyseNGram::OnSaveNGramList() 
{
	char          SubStr[NGRAM_NMAX+1];
	unsigned long cnt;
	double        rel;
	
	theApp.DoWaitCursor(1);
	b_SaveNGramList = true;
	
	GetTmpName(outfile,"NGram",".tmp");
	ofstream txt_NGram(outfile);
	// TODO Title via Ressourcen String Einfügen
	char string[100];
	char title[128], method[20]; 
	switch ( m_N_NGram )  {
	case 0: LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_HISTOGRAM,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy( method, pc_str );
		break;
	case 1: LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_DIGRAM,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy( method, pc_str );
		break;
	case 2: LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_TRIGRAM,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy( method, pc_str );
		break;
	case 3:  LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_NGRAM,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf( method, pc_str, m_NrNGram );
		break;
	}
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_ANALYSIS_OF,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName2(title,sizeof(title),pc_str, Title,method);
	txt_NGram << title << "\n";
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_DESCRIPTION,pc_str,STR_LAENGE_STRING_TABLE);
	txt_NGram << pc_str << "\n\n";
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_NO,pc_str,STR_LAENGE_STRING_TABLE);
	txt_NGram.width(5); 
	txt_NGram << pc_str << '\t';
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_SUBSTR,pc_str,STR_LAENGE_STRING_TABLE);
	int wd = 0;
	while(pc_str[wd] != 0 ) wd++;
	if (isBinary)
		wd = (wd > l_N*3 -1) ? wd+2 : l_N*3+1;
	else
		wd = (wd > l_N ) ? wd +2 : l_N +2;
	txt_NGram.width(wd);
	txt_NGram << pc_str << '\t';
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_RELFREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
	txt_NGram << pc_str << '\n';

	if ( !NGramActualized ) 
		Register ( l_N );

	NGramPtr->resetIterator();
	unsigned long ListSize = (m_ShowCntNGram<NGramPtr->getIndividuals()) ? m_ShowCntNGram : NGramPtr->getIndividuals();
	for (int i=0; (unsigned long)i<ListSize; i++)
	{
		txt_NGram.width(5);
		txt_NGram << i+1 << "\t";

		NGramPtr->get( SubStr, cnt, rel );

		// int i_Ndx = SA->GetIndex(i);
		if ( isBinary )
		{
			for (int k=0; k<l_N; k++)	
			{
				int nr = (unsigned char)SubStr[k];
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
			strcpy(string, SubStr);
		}
		txt_NGram.width(wd);
		txt_NGram << string << "\t";
		txt_NGram.precision(4);
		txt_NGram << rel*100.0 << "\n";
	}

	txt_NGram.close();
	theApp.DoWaitCursor(-1);
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CDialog::OnOK();
}


// -----------------------------------------------------------------------------------------------------

bool AnalyseNGram::b_saveNGramList()
{
	return b_SaveNGramList;
}

//////////////////////////////////////////////////////////////////////
// CNGram Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CNGram::CNGram()
{
}

CNGram::~CNGram()
{
	delete []NGramHashTable;
}

struct hashEntry {
	unsigned long count;
	char          SubStr[NGRAM_NMAX];
};

CNGram::CNGram(const unsigned long fileSize, const unsigned short _N, const unsigned short alphabetSize )
{
	N            = _N;
	Size         = fileSize - N+1;
	hashed       = 0;
	AlphabetSize = alphabetSize;
	if ( N <= 2 ) 
	{
		unsigned long Sz = unsigned long(pow(AlphabetSize, N));
		HashTableSize = min(Sz+Sz/8, Size+Size/8);
	}
	else
		HashTableSize = Size+Size/8;
	NGramHashTable = new char[HashTableSize*(4+N)];
	memset(NGramHashTable, 0, HashTableSize*(4+N));
	individuals = 0;
	resetIterator();
}

void CNGram::add( const char *substring )
{
	unsigned long hashAddress = 0;
	for (unsigned short i=0; i<N; i++) 
	{
		char chr = substring[i];
		hashAddress = (hashAddress +(unsigned short)chr) % HashTableSize;
	}
	hashEntry *hPtr; 
	unsigned long qP = 1;
	while ( qP < HashTableSize )  
	{
		hPtr = (hashEntry*)(NGramHashTable + ((4+N)*hashAddress) );
		if ( !hPtr->SubStr[0] )
		{
			hPtr->count = 1;
			strncpy( hPtr->SubStr, substring, N );
			individuals++;
			break;
		}
		// in case of free Table
		if ( strncmp(hPtr->SubStr, substring, N) )
		{
			hashAddress = (hashAddress + qP*qP) % HashTableSize; 
			qP++;
		}
		else
		{
			hPtr->count++;
			break;	
		}
	}
	hashed++;
}

int compare( const void *arg1, const void *arg2 )
{
	hashEntry *he_1, *he_2;
	he_1 = (hashEntry*)arg1;
	he_2 = (hashEntry*)arg2;
	if ( he_1->count < he_2->count ) return 1;
	if ( he_1->count > he_2->count ) return -1;
	return 0;
}

void CNGram::sort()
{
	qsort((void*)NGramHashTable, (size_t)HashTableSize, 4+N, compare );
}

void CNGram::get( char *SubStr, unsigned long &cnt, double &rel )
{
	hashEntry *hPtr;
	char *charPtr = NGramHashTable + ((4+N)*iterator);
	hPtr = (hashEntry*)charPtr;
	for (int i=0; i<N; i++) SubStr[i] = hPtr->SubStr[i];
	SubStr[i] = 0;
	cnt = hPtr->count;
	rel = (double)cnt / hashed;
	iterator++;
}

