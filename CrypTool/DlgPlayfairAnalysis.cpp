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

//////////////////////////////////////////////////////////////////

// DialogPlayfair.cpp: Implementierungsdatei
//
// Menüfolge: Analyse -> manuelle Analyse / Algorithmen -> Playfair...
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgPlayfairAnalysis.h"
#include "PlayfairAnalysis.h"
#include "assert.h"
#include "DialogeMessage.h"



/////////////////////////////////////////////////////////////////////////////
//
// Dialogfeld CDlgPlayfairAnalysis 
//

CDlgPlayfairAnalysis::CDlgPlayfairAnalysis(const char *infile,const char *outfile,int r,int c,CWnd* pParent /*=NULL*/)
               : CDialog(CDlgPlayfairAnalysis::IDD, pParent)
{
	int i,j;

	m_Alg = new CPlayfairAnalysis("",0,infile,outfile,r,c,1);
	m_Alg->getMatrix()->clear(m_Alg->getAlphabet()->getNullElement());

	for (i=0;i<6;i++)
	{
		for (j=0;j<6;j++)
		{
			char p[2];
			p[1]=0;
  		    p[0]=m_Alg->getCharOfMatrix(i,j);
			m_einfeld[i][j].SetAlg(m_Alg,this);

			if (i<5&&j<5)
				m_mat[i][j]=p;
		}
	}
	m_Alg->UpdateDigrams(1);

	//{{AFX_DATA_INIT(CDlgPlayfairAnalysis)
	m_use                 = 1;
	m_Dec                 = 1;
	m_sechs               = 0;
	m_iScroll             = 0;
	m_ActualiseExpectedPlaintext = 1;
	m_txtfeld.SetAlg(m_Alg);
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CDlgPlayfairAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlayfairAnalysis)
	DDX_Control(pDX, IDC_EDIT_1_1, m_einfeld[0][0]);
	DDX_Control(pDX, IDC_EDIT_1_2, m_einfeld[0][1]);
	DDX_Control(pDX, IDC_EDIT_1_3, m_einfeld[0][2]);
	DDX_Control(pDX, IDC_EDIT_1_4, m_einfeld[0][3]);
	DDX_Control(pDX, IDC_EDIT_1_5, m_einfeld[0][4]);
	DDX_Control(pDX, IDC_EDIT_1_6, m_einfeld[0][5]);
	DDX_Control(pDX, IDC_EDIT_2_1, m_einfeld[1][0]);
	DDX_Control(pDX, IDC_EDIT_2_2, m_einfeld[1][1]);
	DDX_Control(pDX, IDC_EDIT_2_3, m_einfeld[1][2]);
	DDX_Control(pDX, IDC_EDIT_2_4, m_einfeld[1][3]);
	DDX_Control(pDX, IDC_EDIT_2_5, m_einfeld[1][4]);
	DDX_Control(pDX, IDC_EDIT_2_6, m_einfeld[1][5]);
	DDX_Control(pDX, IDC_EDIT_3_1, m_einfeld[2][0]);
	DDX_Control(pDX, IDC_EDIT_3_2, m_einfeld[2][1]);
	DDX_Control(pDX, IDC_EDIT_3_3, m_einfeld[2][2]);
	DDX_Control(pDX, IDC_EDIT_3_4, m_einfeld[2][3]);
	DDX_Control(pDX, IDC_EDIT_3_5, m_einfeld[2][4]);
	DDX_Control(pDX, IDC_EDIT_3_6, m_einfeld[2][5]);
	DDX_Control(pDX, IDC_EDIT_4_1, m_einfeld[3][0]);
	DDX_Control(pDX, IDC_EDIT_4_2, m_einfeld[3][1]);
	DDX_Control(pDX, IDC_EDIT_4_3, m_einfeld[3][2]);
	DDX_Control(pDX, IDC_EDIT_4_4, m_einfeld[3][3]);
	DDX_Control(pDX, IDC_EDIT_4_5, m_einfeld[3][4]);
	DDX_Control(pDX, IDC_EDIT_4_6, m_einfeld[3][5]);
	DDX_Control(pDX, IDC_EDIT_5_1, m_einfeld[4][0]);
	DDX_Control(pDX, IDC_EDIT_5_2, m_einfeld[4][1]);
	DDX_Control(pDX, IDC_EDIT_5_3, m_einfeld[4][2]);
	DDX_Control(pDX, IDC_EDIT_5_4, m_einfeld[4][3]);
	DDX_Control(pDX, IDC_EDIT_5_5, m_einfeld[4][4]);
	DDX_Control(pDX, IDC_EDIT_5_6, m_einfeld[4][5]);
	DDX_Control(pDX, IDC_EDIT_6_1, m_einfeld[5][0]);
	DDX_Control(pDX, IDC_EDIT_6_2, m_einfeld[5][1]);
	DDX_Control(pDX, IDC_EDIT_6_3, m_einfeld[5][2]);
	DDX_Control(pDX, IDC_EDIT_6_4, m_einfeld[5][3]);
	DDX_Control(pDX, IDC_EDIT_6_5, m_einfeld[5][4]);
	DDX_Control(pDX, IDC_EDIT_6_6, m_einfeld[5][5]);
	DDX_Text(pDX, IDC_EDIT_1_1, m_mat[0][0]);
	DDV_MaxChars(pDX, m_mat[0][0], 1);
	DDX_Text(pDX, IDC_EDIT_1_2, m_mat[0][1]);
	DDV_MaxChars(pDX, m_mat[0][1], 1);
	DDX_Text(pDX, IDC_EDIT_1_3, m_mat[0][2]);
	DDV_MaxChars(pDX, m_mat[0][2], 1);
	DDX_Text(pDX, IDC_EDIT_1_4, m_mat[0][3]);
	DDV_MaxChars(pDX, m_mat[0][3], 1);
	DDX_Text(pDX, IDC_EDIT_1_5, m_mat[0][4]);
	DDV_MaxChars(pDX, m_mat[0][4], 1);
	DDX_Text(pDX, IDC_EDIT_1_6, m_mat[0][5]);
	DDV_MaxChars(pDX, m_mat[0][5], 1);
	DDX_Text(pDX, IDC_EDIT_2_1, m_mat[1][0]);
	DDV_MaxChars(pDX, m_mat[1][0], 1);
	DDX_Text(pDX, IDC_EDIT_2_2, m_mat[1][1]);
	DDV_MaxChars(pDX, m_mat[1][1], 1);
	DDX_Text(pDX, IDC_EDIT_2_3, m_mat[1][2]);
	DDV_MaxChars(pDX, m_mat[1][2], 1);
	DDX_Text(pDX, IDC_EDIT_2_4, m_mat[1][3]);
	DDV_MaxChars(pDX, m_mat[1][3], 1);
	DDX_Text(pDX, IDC_EDIT_2_5, m_mat[1][4]);
	DDV_MaxChars(pDX, m_mat[1][4], 1);
	DDX_Text(pDX, IDC_EDIT_2_6, m_mat[1][5]);
	DDV_MaxChars(pDX, m_mat[1][5], 1);
	DDX_Text(pDX, IDC_EDIT_3_1, m_mat[2][0]);
	DDV_MaxChars(pDX, m_mat[2][0], 1);
	DDX_Text(pDX, IDC_EDIT_3_2, m_mat[2][1]);
	DDV_MaxChars(pDX, m_mat[2][1], 1);
	DDX_Text(pDX, IDC_EDIT_3_3, m_mat[2][2]);
	DDV_MaxChars(pDX, m_mat[2][2], 1);
	DDX_Text(pDX, IDC_EDIT_3_4, m_mat[2][3]);
	DDV_MaxChars(pDX, m_mat[2][3], 1);
	DDX_Text(pDX, IDC_EDIT_3_5, m_mat[2][4]);
	DDV_MaxChars(pDX, m_mat[2][4], 1);
	DDX_Text(pDX, IDC_EDIT_3_6, m_mat[2][5]);
	DDV_MaxChars(pDX, m_mat[2][5], 1);
	DDX_Text(pDX, IDC_EDIT_4_1, m_mat[3][0]);
	DDV_MaxChars(pDX, m_mat[3][0], 1);
	DDX_Text(pDX, IDC_EDIT_4_2, m_mat[3][1]);
	DDV_MaxChars(pDX, m_mat[3][1], 1);
	DDX_Text(pDX, IDC_EDIT_4_3, m_mat[3][2]);
	DDV_MaxChars(pDX, m_mat[3][2], 1);
	DDX_Text(pDX, IDC_EDIT_4_4, m_mat[3][3]);
	DDV_MaxChars(pDX, m_mat[3][3], 1);
	DDX_Text(pDX, IDC_EDIT_4_5, m_mat[3][4]);
	DDV_MaxChars(pDX, m_mat[3][4], 1);
	DDX_Text(pDX, IDC_EDIT_4_6, m_mat[3][5]);
	DDV_MaxChars(pDX, m_mat[3][5], 1);
	DDX_Text(pDX, IDC_EDIT_5_1, m_mat[4][0]);
	DDV_MaxChars(pDX, m_mat[4][0], 1);
	DDX_Text(pDX, IDC_EDIT_5_2, m_mat[4][1]);
	DDV_MaxChars(pDX, m_mat[4][1], 1);
	DDX_Text(pDX, IDC_EDIT_5_3, m_mat[4][2]);
	DDV_MaxChars(pDX, m_mat[4][2], 1);
	DDX_Text(pDX, IDC_EDIT_5_4, m_mat[4][3]);
	DDV_MaxChars(pDX, m_mat[4][3], 1);
	DDX_Text(pDX, IDC_EDIT_5_5, m_mat[4][4]);
	DDV_MaxChars(pDX, m_mat[4][4], 1);
	DDX_Text(pDX, IDC_EDIT_5_6, m_mat[4][5]);
	DDV_MaxChars(pDX, m_mat[4][5], 1);
	DDX_Text(pDX, IDC_EDIT_6_1, m_mat[5][0]);
	DDV_MaxChars(pDX, m_mat[5][0], 1);
	DDX_Text(pDX, IDC_EDIT_6_2, m_mat[5][1]);
	DDV_MaxChars(pDX, m_mat[5][1], 1);
	DDX_Text(pDX, IDC_EDIT_6_3, m_mat[5][2]);
	DDV_MaxChars(pDX, m_mat[5][2], 1);
	DDX_Text(pDX, IDC_EDIT_6_4, m_mat[5][3]);
	DDV_MaxChars(pDX, m_mat[5][3], 1);
	DDX_Text(pDX, IDC_EDIT_6_5, m_mat[5][4]);
	DDV_MaxChars(pDX, m_mat[5][4], 1);
	DDX_Text(pDX, IDC_EDIT_6_6, m_mat[5][5]);
	DDV_MaxChars(pDX, m_mat[5][5], 1);
	DDX_Radio(pDX, IDC_RAD6, m_sechs);
	DDX_Control(pDX, IDC_PLAYFAIR_LIST, m_listview);
	DDX_Control(pDX, IDC_PASSWORD, m_pwfeld);
	DDX_Control(pDX, IDC_MYTXT, m_txtfeld);
	DDX_Check(pDX, IDC_CHECK4, m_ActualiseExpectedPlaintext);
	// DDV_MaxChars(pDX, m_mytxt, MAXSHOWLETTER); m_mytxt ersetzt durch lokale Variable
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 36);
	DDX_Control(pDX, IDC_LIST, m_ciphfeld);
	DDX_Text(pDX, IDC_LIST, m_cipher);
	DDV_MaxChars(pDX, m_cipher, MAXSHOWLETTER*10);
	DDX_Check(pDX, IDC_CHECK1, m_use);
	// DDX_Text(pDX, IDC_MYTXT, m_mytxt);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_ctrlScroll);
	DDX_Scroll(pDX, IDC_SCROLLBAR1, m_iScroll);
	//}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
//
// 
//


BEGIN_MESSAGE_MAP(CDlgPlayfairAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgPlayfairAnalysis)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck)
	ON_BN_CLICKED(IDC_RAD5, OnSechs)
	ON_BN_CLICKED(IDC_RAD6, OnSechs)
	ON_BN_CLICKED(IDC_BUTTON5, OnAnalyse)
	ON_BN_CLICKED(IDC_BUTTON6, OnSynchronise)
	ON_EN_UPDATE(IDC_MYTXT, OnManAnalyse)
	ON_EN_UPDATE(IDC_PASSWORD, OnUpdate)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_MYTXT, OnChangeEditPlaintext)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgPlayfairAnalysis 
char *CDlgPlayfairAnalysis::GetData()
{
	return m_password.GetBuffer(25);
}

/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CDlgPlayfairAnalysis::OnManAnalyse()
{
	char buf[MAXSHOWLETTER+2], line[256];
	int i,j, n, k;
	int maxchars=MAXSHOWLETTER;
	playfair_digrammlist* diglist;
	
	UpdateData();
	
	i=0; j=0;
	CString m_plaintext;
	m_txtfeld.GetWindowText(m_plaintext);
	while ((i<maxchars)&&(j<m_plaintext.GetLength())) 
	{
		char nChar = m_plaintext[j];
		
			if (m_Alg->myisalpha2(nChar)) buf[i] = nChar;
			else  
			{
				if ((nChar=='j')||(nChar=='J')||(('0'<=nChar)&&(nChar<='9'))) 
				{
					Message(IDS_STRING_PLAYFAIR_WARNMSG003, MB_ICONEXCLAMATION);
				}
				buf[i] = NULLELEMENT;
			}
			i++;

		j++;
	}

	buf[i]='\0';
	digbuf[0]='\0';
	m_Alg->initDigrams();
	diglist = new playfair_digrammlist(m_Alg->getAlphabet(), m_Alg->getDigrams(), 
										buf, m_Alg->inbuf, min (maxchars, m_Alg->inbuflen));
	// in der Initialisierung läuft die eigentliche Arbeit ab:
	// für jedes Pärchen des Klartextes, wird das passende Digramm gesucht, das durch das Chiffrat festgelegt ist.

	n = 2*diglist->getLen();
	m_txtfeld.SetLimitText (n); // limitiere Ausgabe
	diglist->getPlainString(digbuf, n); // lege Ausgabe des Klartextes fest (2.Zeile)

	try {
		if (true || (i%2==0)) {
			m_Alg->DeleteLetterGraph();
			m_Alg->AnalyseDigramme(diglist);  //untersuchen der Digramme und erstellen des Lettergraphen
		}
	}
	catch (playfair_error e) {
		switch (e.getCode()) {
		case 1:
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PLAYFAIR_ERRMSG001,pc_str,STR_LAENGE_STRING_TABLE);
			break;
		case 101: case 102: case 103: case 104: case 105: case 106: case 107:
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PLAYFAIR_ERRMSG100,pc_str,STR_LAENGE_STRING_TABLE);
			break;
		case 113: case 114:
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PLAYFAIR_ERRMSG110,pc_str,STR_LAENGE_STRING_TABLE);
			break;
		case 201: case 202: case 203: case 204:
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PLAYFAIR_ERRMSG200,pc_str,STR_LAENGE_STRING_TABLE);
			break;
		default:
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PLAYFAIR_ERRMSGALLG,pc_str,STR_LAENGE_STRING_TABLE);
			break;
		}
		sprintf(line,pc_str,e.getPosition()+1,(e.getLetter())?e.getLetter()->getValue():m_Alg->getAlphabet()->getNullElement()->getValue());
		AfxMessageBox (line);
	}

	if ((false) && (i%2==0) && (i>0)) {
		//automatische Generierung der Matrix aktiv
		if (!m_Alg->CreateMatrixStandalone (buf, i)) { // Analyse Peer Wichmann
			// keine gültige Matrix gefunden
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PLAYFAIR_NOMATRIX,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str);
			AfxMessageBox (line);
		}

		m_password = m_Alg->CreatePassfromMatrix();
	}

	delete (diglist);

	// Matrix neu schreiben
	for (i=0;i<m_Alg->getSize();i++)
	{
		for (k=0;k<m_Alg->getSize();k++)
		{
			m_mat[i][k]=m_Alg->getCharOfMatrix(i,k);
		}
	}

	UpdateData(FALSE);
	UpdateListBox();
}


/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CDlgPlayfairAnalysis::OnAnalyse()
// Schalter "erzeuge Matrix", war "Häufigkeitsanalyse"
{
	int i, k;
	char buf[MAXSHOWLETTER+2], line[256];
	int maxchars=MAXSHOWLETTER;
	BOOL flagSuccess;

	UpdateData(TRUE);

	CString m_plaintext;
	m_txtfeld.GetWindowText(m_plaintext);
	i=0;
	while ((i<maxchars)&&(i<m_plaintext.GetLength())) {
		buf[i] = m_plaintext[i]; i++;
	}
	buf[i]='\0';
	if (!(flagSuccess = m_Alg->CreateMatrixStandalone(buf, i))) { // Analyse Peer Wichmann
		// keine gültige Matrix gefunden
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PLAYFAIR_NOMATRIX,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str);
		AfxMessageBox (line);
	}

	m_password = m_Alg->CreatePassfromMatrix();


	// Matrix neu schreiben
	for (i=0;i<m_Alg->getSize();i++)
	{
		for (k=0;k<m_Alg->getSize();k++)
		{
			m_mat[i][k]=m_Alg->getCharOfMatrix(i,k);
		}
	}
		
	UpdateData(FALSE);
	UpdateListBox();	
	if ( m_ActualiseExpectedPlaintext && flagSuccess ) 
	{
		char obuf[MAXSHOWLETTER+2];
		int i,j,k;
		i=j=k=0;
		while(i<MAXSHOWLETTER&&j<m_Alg->inbuflen)
		{
			char c=m_Alg->inbuf[j++];
			if(!m_Alg->myisalpha2(c) && !isinvalidoccured)  
				c = m_Alg->getAlphabet()->replaceInvalidLetter(true, c);
			if(m_Alg->myisalpha2(c)) {
				obuf[i] = m_Alg->outbuf[k];
				k++;
			} else {
				obuf[i] = '.';
			}
			i++;
		}
		obuf[i] = '\0';
		CString tmp = obuf;
		int ps, pe;
		m_txtfeld.GetSel(ps, pe);
		m_txtfeld.SetSel(0,-1);
		m_txtfeld.ReplaceSel(tmp, TRUE);
		m_txtfeld.SetSel(ps,ps);
	}
	m_txtfeld.SetFocus();
}


/////////////////////////////////////////////////////////////////////////////
//
// 
//


void CDlgPlayfairAnalysis::OnCheck()
// Doppelte ignorieren oder nicht
{
	m_Alg->PassUse(!m_use);
	OnUpdate();
	m_Alg->SetPass("");
}

/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CDlgPlayfairAnalysis::OnSechs() 
// auf 5x5 oder 6x6 Matrix einstellen
{
	int i,j;

	UpdateData(TRUE);
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if (m_sechs == 1)
	{
		m_Alg->SetSize(true);
		for (i=0;i<6;i++)
			m_einfeld[i][5].EnableWindow(TRUE);
		for (i=0;i<5;i++)
			m_einfeld[5][i].EnableWindow(TRUE);
	}
	else
	{
 		m_Alg->SetSize(false);
		for (i=0;i<6;i++)
		{
			m_einfeld[i][5].EnableWindow(FALSE);
			m_mat[i][5]="";
		}
		for (i=0;i<5;i++)
		{
			m_einfeld[5][i].EnableWindow(FALSE);
			m_mat[5][i]="";
		}
	}
	m_password="";
	m_Alg->SetPass("");
	m_Alg->UpdateDigrams(true);
	m_Alg->getMatrix()->clear(m_Alg->getAlphabet()->getNullElement());

	for (i=0;i<m_Alg->getSize();i++)
	{
		for (j=0;j<m_Alg->getSize();j++)
		{
			m_mat[i][j]=m_Alg->getCharOfMatrix(i,j);
		}
	}
	UpdateData(FALSE);
	OnManAnalyse();
} 


/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CDlgPlayfairAnalysis::InitListBox()
{
	is6x6possible = false;
	isinvalidoccured = false;
	int i;
	char c, s[245];

	m_Alg->DoCipher(false, true,MAXSHOWLETTER);

	UpdateData(TRUE);
	m_cipher=m_Alg->outbuf;
	UpdateData(FALSE);

	// Gauweiler 30.1.01, statt eine einzelne Zeile, sollten gleich alle drei Zeilen angezeigt werden.
	// da die Update-Fkt das richtig macht, soll sie gleich mal zum ersten Mal ihre Arbeit machen.
	strcpy(digbuf,"");

    // ist vielleicht mit 6x6 Matrix verschlüsselt worden?
	i=0;
	while(i<MAXSHOWLETTER&&i<m_Alg->inbuflen)
	{
		c=m_Alg->inbuf[i++];
		if(!m_Alg->myisalpha2(c))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
			if (('J'==MyToUpper(c)) || (('0'<=c) && (c<='9')))
				is6x6possible = true;
			else
				isinvalidoccured = true;
	}
	if (is6x6possible || isinvalidoccured) {
			if (is6x6possible)
				LoadString(AfxGetInstanceHandle(),IDS_STRING_PLAYFAIR_WARNMSG001,pc_str,STR_LAENGE_STRING_TABLE);
			if (isinvalidoccured)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_PLAYFAIR_WARNMSG002,pc_str,STR_LAENGE_STRING_TABLE);
				UpdateData();
				UpdateData(FALSE);
			}
			sprintf(s,pc_str);
			AfxMessageBox (s);
			UpdateData(TRUE);
				m_sechs = (is6x6possible && !isinvalidoccured)?1:0;
			UpdateData(FALSE);
			OnSechs();
	}
} 


////////////////////////////////////////////////////////////////////////////////////////
//
// ON INIT DIALOG
//

BOOL CDlgPlayfairAnalysis::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// m_listview in Report-Mode initialisieren

	m_Font.CreateFont(0,0,0,0,0,0,0,0,DEFAULT_CHARSET,OUT_RASTER_PRECIS,0,DEFAULT_QUALITY,FIXED_PITCH|FF_DONTCARE,NULL);
	m_ciphfeld.SetFont(&m_Font);
	m_txtfeld.SetFont(&m_Font);

	int colWidth = 55;  // Spaltenbreite in Pixel


	m_listview.InsertColumn( 0, " ", LVCFMT_LEFT, colWidth-30 , 0); // Buchstabe
	m_listview.InsertColumn( 1, "LROU", LVCFMT_LEFT, colWidth , 3); // 
	m_listview.InsertColumn( 2, "Nb?", LVCFMT_LEFT, colWidth , 3); // 
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HORIZ,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 3, pc_str, LVCFMT_LEFT, colWidth+30 , 1); // 
	LoadString(AfxGetInstanceHandle(),IDS_STRING_VERT,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 4, pc_str, LVCFMT_LEFT, colWidth+30 , 2); // 
	m_listview.InsertColumn( 5, "row or col?", LVCFMT_LEFT, colWidth+60 , 3); // 
	m_listview.InsertColumn( 6, "Metrik", LVCFMT_LEFT, colWidth , 3); // 

	m_bHScroll = FALSE;
	m_iPos = 0;

	InitListBox();
	SetupListBox();
	SetupAnalysisWindow();

	// read window rects at dialog initialization
	GetWindowRect(&initialRectDialog);
	GetDlgItem(IDC_PLAYFAIR_LIST)->GetWindowRect(&initialRectListLetterInformation);
	GetDlgItem(IDC_LIST)->GetWindowRect(&initialRectFieldResult);
	GetDlgItem(IDC_MYTXT)->GetWindowRect(&initialRectFieldPlaintext);
	GetDlgItem(IDCANCEL)->GetWindowRect(&initialRectButtonCancel);
	GetDlgItem(IDC_SCROLLBAR1)->GetWindowRect(&initialRectScrollbar);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

/****** Mark Santiago, Henrik Koy *******/
const int iEditSize=69;

void CDlgPlayfairAnalysis::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_bHScroll = !m_bHScroll;
	
	int iMin, iMax, iPos, iPrev;
	pScrollBar->GetScrollRange(&iMin, &iMax);
	iPos = pScrollBar->GetScrollPos();
	if(m_bHScroll)
	{
		switch(nSBCode)
		{
		case SB_LINELEFT:	iPos = iPos-1; break;  //Scroll left.
		case SB_LINERIGHT:	iPos = iPos+1; break;     //Scroll right.
		case SB_PAGELEFT:	iPos = iPos-iEditSize/2; break;    //Scroll one page left.
		case SB_PAGERIGHT:	iPos = iPos+iEditSize/2; break;    //Scroll one page right.
		case SB_THUMBTRACK:	iPos = (int)nPos; break;  //Drag scroll box to specified position. The current position is specified by the nPos parameter. 
		}
		m_iPos = iPos = min(max(0, iPos), iMax);
		iPrev = m_ctrlScroll.SetScrollPos(iPos);
		m_ciphfeld.LineScroll(0, iPos-iPrev);
		// m_txtfeld.LineScroll(0, iPos-iPrev);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	m_bHScroll = FALSE;
}


/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CDlgPlayfairAnalysis::ScrollRange(int length_in_characters)
{
	if ( length_in_characters )
	{
		m_iSMax = length_in_characters - iEditSize; 
		if ( m_iSMax < 0 ) m_iSMax = 0;
	}
	m_ctrlScroll.SetScrollRange(0, m_iSMax);
	m_iPos = m_ctrlScroll.GetScrollPos();
	m_ciphfeld.SetScrollRange(SB_HORZ, 0, m_iSMax);
	m_ciphfeld.LineScroll(0, m_iPos);
	m_ciphfeld.ShowScrollBar(SB_HORZ, FALSE);
}

/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CDlgPlayfairAnalysis::OnChangeEditPlaintext() 
{
	ScrollRange();
}


/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CDlgPlayfairAnalysis::OnSynchronise()
{
	int iMin, iPos;
	m_txtfeld.GetSel(iMin, iPos);
	CPoint cur = m_txtfeld.GetCaretPos();
	iPos = max((int) 0, (int) (iPos-(cur.x+1)/9));	
	m_ctrlScroll.ShowWindow(SW_HIDE);
	m_ctrlScroll.SetScrollPos(0);
	m_ctrlScroll.SetScrollPos(iPos);
	m_ctrlScroll.ShowWindow(SW_SHOW);
	m_ciphfeld.ShowWindow(SW_HIDE);
	m_ciphfeld.LineScroll(0, -MAXSHOWLETTER);
	m_ciphfeld.LineScroll(0, iPos);
	m_ciphfeld.ShowWindow(SW_SHOW);
}


/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CDlgPlayfairAnalysis::SetupListBox()
{
	int i,j;
	playfair_letter *let;
	char s[MAXSHOWLETTER+2];

	m_listview.DeleteAllItems();
	for (j=i=0; i < m_Alg->getLetterlist()->getLen(); i++) 
	{
		let = (m_Alg->getLetterlist()->getLetter(i));
		assert (let); assert (let->getValue()<='Z'); assert (let->getValue()>=NULLELEMENT);
		s[0] = let->getValue();	s[1] = '\0';
		j = m_listview.InsertItem(i,s);
		assert (let); assert (let->getValue()<='Z'); assert (let->getValue()>=NULLELEMENT);
		let->getNeighboursString (s, 10);			// Neighbours
		m_listview.SetItemText( j, 1, s);
		assert (let); assert (let->getValue()<='Z'); assert (let->getValue()>=NULLELEMENT);
		let->getUndefinedNeighboursString (s, 10);	// poss. Neighbours
		m_listview.SetItemText( j, 2, s);
		assert (let); assert (let->getValue()<='Z'); assert (let->getValue()>=NULLELEMENT);
		let->getRowString (s, 20);					// Rows
		m_listview.SetItemText( j, 3, s);
		assert (let); assert (let->getValue()<='Z'); assert (let->getValue()>=NULLELEMENT);
		let->getColString (s, 20);					// Col
		m_listview.SetItemText( j, 4, s);
		assert (let); assert (let->getValue()<='Z'); assert (let->getValue()>=NULLELEMENT);
		let->getRoworcolString (s, 25);				// RoworCol
		m_listview.SetItemText( j, 5, s);
		sprintf(s,"%d", let->getWeight());			// Metrik
		m_listview.SetItemText( j, 6, s);
	}
}

int CDlgPlayfairAnalysis::SetupAnalysisWindow()
{
	int i,j,k;
	char ibuf[MAXSHOWLETTER+2],dbuf[MAXSHOWLETTER+2],obuf[MAXSHOWLETTER+2],c;

	m_Alg->DoCipher(false, true, MAXSHOWLETTER);

	UpdateData(TRUE);
	i=j=k=0;
	while(i<MAXSHOWLETTER&&j<m_Alg->inbuflen)
	{
		c=m_Alg->inbuf[j++];
		if(!m_Alg->myisalpha2(c) && !isinvalidoccured)  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
			c = m_Alg->getAlphabet()->replaceInvalidLetter(true, c);
		if(m_Alg->myisalpha2(c)) {
			ibuf[i] = MyToUpper(c);
			dbuf[i] = digbuf[k];
			obuf[i] = m_Alg->outbuf[k];
			k++;
		} else {
			ibuf[i] = '.';
			dbuf[i] = '.';
			obuf[i] = '.';
		}
		i++;
	}
	ibuf[i]=0;	dbuf[i]=0;	obuf[i]=0;
	m_cipher.Format("%s\r\n%s\r\n%s\r\n",ibuf,dbuf,obuf);
	UpdateData(FALSE);
	return i;
}


void CDlgPlayfairAnalysis::UpdateListBox()
{
	m_listview.ShowWindow(SW_HIDE);
	SetupListBox();
	m_listview.ShowWindow(SW_SHOW);
	int i = SetupAnalysisWindow();
	ScrollRange( i );
} 


/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CDlgPlayfairAnalysis::UpdatePassword()
{
	int i,j;
	char p[37];

	if (m_sechs)
	{
		for (j=0;j<36;j++)
			p[j]=m_mat[j/6][j%6][0];
	}
	else
	{
		for (i=0,j=0;i<30;i++)
		{
			if ( (i+1)%6)
				p[j++]=m_mat[i/6][i%6][0];
		}
	}
	p[j--]=0;

	UpdateData(TRUE);
 	m_password=p;
//	m_password=m_Alg->CreatePassfromMatrix();
	UpdateData(FALSE);
} 


/////////////////////////////////////////////////////////////////////////////
//
// 
//

int CDlgPlayfairAnalysis::Display()
{
	int res;
	res=DoModal();
	return res;
}


/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CDlgPlayfairAnalysis::OnUpdate() 
// sobald ein neues Zeichen im Passwort eingegeben wurde
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); //erstmal wieder die Daten aus dem Formular holen

	m_pwfeld.GetSel(sels, sele);
	res.Empty();

	m_password.MakeUpper();

    //abprüfen, ob ein ungültiges Zeichen in der Paßwortzeile eingegeben wurde
	for(k=i=0;i<m_password.GetLength();i++) {
		c = m_password[i];
		if(!m_Alg->myisalpha2(c))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
			c = m_Alg->getAlphabet()->replaceInvalidLetter(true, c);
		if(m_Alg->myisalpha2(c)) { // valid character
			res += c;
			k++;
		}
		else { // invalid character
			MessageBeep(MB_OK);
			if(k<sels) sels--;
			if(k<sele) sele--;
		}
	}

	m_password = res;
	m_Alg->SetPass(m_password.GetBuffer(36)); // GetBuffer(25) auf GetBuffer(36) ???
	for (i=0;i<m_Alg->getSize();i++)
	{
		for (k=0;k<m_Alg->getSize();k++)
		{
			m_mat[i][k]=m_Alg->getCharOfMatrix(i,k);
		}
	}

	UpdateData(FALSE);
	UpdateListBox();
	m_pwfeld.SetSel(sels,sele);
} 

// flomar, 01/07/09
// this function is a quick hack (compare ListResults.cpp) 
// to make the dialog window scalable along the x-axis
void CDlgPlayfairAnalysis::OnSize(UINT nType, int cx, int cy)
{
	CWnd *windowListLetterInformation = GetDlgItem(IDC_PLAYFAIR_LIST);
	CWnd *windowFieldResult = GetDlgItem(IDC_LIST);
	CWnd *windowFieldPlaintext = GetDlgItem(IDC_MYTXT);
	CWnd *windowButtonCancel = GetDlgItem(IDCANCEL);
	CWnd *windowScrollbar = GetDlgItem(IDC_SCROLLBAR1);

	// make sure we have valid pointers; if not, return
	if(!windowListLetterInformation || !windowFieldResult || !windowFieldPlaintext || !windowButtonCancel || !windowScrollbar)
		return;

	// read the new dialog rect
	RECT newRectDialog;
	this->GetWindowRect(&newRectDialog);

	// return if the new dialog rect is smaller then the initial one, 
	int widthOld = initialRectDialog.right - initialRectDialog.left;
	int widthNew = newRectDialog.right - newRectDialog.left;
	int heightOld = initialRectDialog.bottom - initialRectDialog.top;
	int heightNew = newRectDialog.bottom - newRectDialog.top;
	if(widthNew < widthOld || heightNew != heightOld) {
		this->MoveWindow(newRectDialog.left, newRectDialog.top, widthOld, heightOld);
		return;
	}

	// compute how much wider the dialog is compared to its original state
	int widthIncrement = widthNew - widthOld;

	// in order to deal with Microsoft's weird behaviour here, we need some 
	// correctional parameters to make the dialog look less weird (WTF?) 
	int correctionX = -4;
	int correctionY = +7;

	// compute new list letter information rect
	int widthListLetterInformation = initialRectListLetterInformation.right - initialRectListLetterInformation.left + widthIncrement;
	int heightListLetterInformation = initialRectListLetterInformation.bottom - initialRectListLetterInformation.top;
	int marginRightListLetterInformation = initialRectDialog.right - initialRectListLetterInformation.right;
	int marginBottomListLetterInformation = initialRectDialog.bottom - initialRectListLetterInformation.bottom;
	int xListLetterInformation = cx - widthListLetterInformation - marginRightListLetterInformation + correctionX;
	int yListLetterInformation = cy - heightListLetterInformation - marginBottomListLetterInformation + correctionY;

	// compute new field result rect
	int widthFieldResult = initialRectFieldResult.right - initialRectFieldResult.left + widthIncrement;
	int heightFieldResult = initialRectFieldResult.bottom - initialRectFieldResult.top;
	int marginRightFieldResult = initialRectDialog.right - initialRectFieldResult.right;
	int marginBottomFieldResult = initialRectDialog.bottom - initialRectFieldResult.bottom;
	int xFieldResult = cx - widthFieldResult - marginRightFieldResult + correctionX;
	int yFieldResult = cy - heightFieldResult - marginBottomFieldResult + correctionY;

	// compute new field plaintext rect
	int widthFieldPlaintext = initialRectFieldPlaintext.right - initialRectFieldPlaintext.left + widthIncrement;
	int heightFieldPlaintext = initialRectFieldPlaintext.bottom - initialRectFieldPlaintext.top;
	int marginRightFieldPlaintext = initialRectDialog.right - initialRectFieldPlaintext.right;
	int marginBottomFieldPlaintext = initialRectDialog.bottom - initialRectFieldPlaintext.bottom;
	int xFieldPlaintext = cx - widthFieldPlaintext - marginRightFieldPlaintext + correctionX;
	int yFieldPlaintext = cy - heightFieldPlaintext - marginBottomFieldPlaintext + correctionY;

	// compute new CANCEL button rect
	int widthButtonCancel = initialRectButtonCancel.right - initialRectButtonCancel.left;
	int heightButtonCancel = initialRectButtonCancel.bottom - initialRectButtonCancel.top;
	int marginRightButtonCancel = initialRectDialog.right - initialRectButtonCancel.right;
	int marginBottomButtonCancel = initialRectDialog.bottom - initialRectButtonCancel.bottom;
	int xButtonCancel = cx - widthButtonCancel - marginRightButtonCancel;
	int yButtonCancel = cy - heightButtonCancel - marginBottomButtonCancel;

	// compute new SCROLLBAR rect
	int marginRightScrollbar = initialRectDialog.right - initialRectScrollbar.right;
	int marginBottomScrollbar = initialRectDialog.bottom - initialRectScrollbar.bottom;
	int widthScrollbar = cx - marginRightScrollbar;
	int heightScrollbar = initialRectScrollbar.bottom - initialRectScrollbar.top;
	int xScrollbar = cx - widthScrollbar - marginRightScrollbar;
	int yScrollbar = cy - heightScrollbar - marginBottomScrollbar;

	// align dialog components
	windowListLetterInformation->MoveWindow(xListLetterInformation, yListLetterInformation, widthListLetterInformation, heightListLetterInformation);
	windowFieldResult->MoveWindow(xFieldResult, yFieldResult, widthFieldResult, heightFieldResult);
	windowFieldPlaintext->MoveWindow(xFieldPlaintext, yFieldPlaintext, widthFieldPlaintext, heightFieldPlaintext);
	windowButtonCancel->MoveWindow(xButtonCancel, yButtonCancel, widthButtonCancel, heightButtonCancel);
	windowScrollbar->MoveWindow(xScrollbar, yScrollbar, widthScrollbar, heightScrollbar);

	Invalidate();
}

PlayfairOptions CDlgPlayfairAnalysis::getPlayfairOptions()
{
	// create a PlayfairOptions structure that is to be returned
	PlayfairOptions playfairOptions;
	
	playfairOptions.decryption = this->m_Dec;
	playfairOptions.fileNameCleartext = "";
	playfairOptions.fileNameCiphertext = "";
	// TODO playfairOptions.separateDoubleCharacters = true;
	// TODO playfairOptions.separator1 = "X";
	// TODO playfairOptions.separator2 = "Y";
	// TODO playfairOptions.separateDoubleCharactersOnlyWithinPairs = true;
	playfairOptions.ignoreDoubleCharactersInKey = this->m_use;
	playfairOptions.matrixSize = m_sechs ? 6 : 5;

	return playfairOptions;
}




/////////////////////////////////////////////////////////////////////////////
//
// 
//

CChEdit::CChEdit()
{
}


/////////////////////////////////////////////////////////////////////////////
//
// 
//


CChEdit::~CChEdit()
{
}


/////////////////////////////////////////////////////////////////////////////
//
// 
//

BEGIN_MESSAGE_MAP(CChEdit, CEdit)
	//{{AFX_MSG_MAP(CChEdit)
	ON_WM_CHAR()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CChEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
#if 1

	// flomar, 03/28/2013: after hours of debugging I finally located the source of 
	// the problem; obviously the user's key strokes weren't correctly processed, in 
	// other words a character inserted at a specific location would get assigned to an 
	// incorrect matrix cell-- before digging in any deeper I completely re-wrote this 
	// function; it *should* work as intended now; I left the old code in here on purpose 
	// (see the '#if' blocks above and below) in case someone has to deal with this in 
	// another 10 or so years, and I'm not 100% sure I didn't introduce some bugs myself

	// the character the user tried to insert-- in case the character is invalid with regards 
	// to the analysis alphabet, it gets replaced implicitly; if the replacement fails (i.e. 
	// the character is still invalid), we return right away and notify the user with a beep
	const char newCharacter = MyToUpper(m_Alg->getAlphabet()->replaceInvalidLetter(true, nChar));
	if(!m_Alg->myisalpha2(newCharacter)) {
		MessageBeep(MB_OK);
	}
	// the character that was replaced by the new character; the way this is handled 
	// is pretty ugly with all that SetSel/GetLine stuff, but I'm certainly not gonna 
	// touch any other parts of this dialog for the meantime (note: a better solution 
	// would be to have member variables for each and every cell of the GUI matrix);
	// in case the character is not part of the analysis alphabet, we're trying to 
	// convert it just like we did with the new character above
	char tempCharacter[2];
	memset(tempCharacter, 0, sizeof(char) * 2);
	SetSel(0, 1);
	GetLine(0, tempCharacter, 1);
	ReplaceSel(CString(newCharacter));
	SetSel(0, 1);
	// try to replace the temp character with something valid, if necessary
	tempCharacter[0] = MyToUpper(m_Alg->getAlphabet()->replaceInvalidLetter(true, tempCharacter[0]));
	// if the character is still invalid after the conversion, we proceed with a 
	// null element which, as of today, is denoted by the '*' character
	if(!tempCharacter[0]) {
		tempCharacter[0] = m_Alg->getAlphabet()->getNullElement()->getValue();
	}
	// at this point all conversion work is done, we can now assign the old character
	const char oldCharacter = tempCharacter[0];
	// if old a new character are identical, return without doing anything else
	if(newCharacter == oldCharacter) {
		return;
	}
	// if the new character is invalid (not part of the alphabet), return as well
	if(!m_Alg->myisalpha2(newCharacter)) {
		return;
	}
	// we're gonna need those in a minute...
	int newCharacterIndexColumn = -1;
	int newCharacterIndexRow = -1;
	// get the size of the current maxtrix (either 5x5 or 6x6)
	const int matrixSize = m_Alg->getSize();
	// go through all cells of the matrix and find the newly inserted character
	for(int indexRow=0; indexRow<matrixSize; indexRow++) {
		for(int indexColumn=0; indexColumn<matrixSize; indexColumn++) {
			// get the current character
			char currentCharacter = m_Alg->getCharOfMatrix(indexColumn, indexRow);
			// ignore null elements
			if(currentCharacter != m_Alg->getAlphabet()->getNullElement()->getValue()) {
				// assign indices for new character
				if(newCharacter == currentCharacter) {
					newCharacterIndexColumn = indexColumn;
					newCharacterIndexRow = indexRow;
				}
			}
		}
	}
	// this variable tells us if the new character did already exist in the matrix
	const bool newCharacterAlreadyExisted = newCharacterIndexColumn != -1 && newCharacterIndexRow != -1;
	// if the new character did NOT exist in the matrix, determine its indices (column/row)
	if(!newCharacterAlreadyExisted) {
		for(int indexRow=0; indexRow<matrixSize && newCharacterIndexRow<0; indexRow++) {
			for(int indexColumn=0; indexColumn<matrixSize && newCharacterIndexColumn<0; indexColumn++) {
				// get the content of the current matrix cell
				CString stringCurrentMatrixCell;
				m_Dia->getEinfeld(indexColumn, indexRow)->GetWindowText(stringCurrentMatrixCell);
				// check if we've arrived at the new character
				if(newCharacter == stringCurrentMatrixCell[0]) {
					// update indices for the new character
					newCharacterIndexColumn = indexColumn;
					newCharacterIndexRow = indexRow;
					// now update the matrix (actually insert the new character at its appropriate position)
					m_Alg->setElMatrix(newCharacter, newCharacterIndexColumn, newCharacterIndexRow);
				}
			}
		}
	}
	// in case the new character was already inserted, switch back to the old character
	if(newCharacterAlreadyExisted) {
		// update the dialog
		m_Dia->getEinfeld(newCharacterIndexColumn, newCharacterIndexRow)->SetWindowText(CString(oldCharacter));
		// update the analysis
		m_Alg->setElMatrix(oldCharacter, newCharacterIndexColumn, newCharacterIndexRow);
	}
	// some clean-up work
	m_Alg->UpdateDigrams(m_Dia->getDec());
	m_Alg->DoCipher(false, m_Dia->getDec(),MAXSHOWLETTER);
	m_Dia->UpdateListBox();
	m_Dia->UpdatePassword();
	
#else
	char b1[2],b2[2];

	if(!m_Alg->myisalpha2(nChar))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
		nChar = m_Alg->getAlphabet()->replaceInvalidLetter(true, MyToUpper(nChar));
	if (m_Alg->myisalpha2(nChar))
	{
		int i,j,s,a,b,c,d;

		a=-1; c =-1;
		b2[1]=0;
		b2[0]=MyToUpper(nChar);
		SetSel(0, 1);
		GetLine(0,b1,2);
		ReplaceSel(b2);
		SetSel(0, 1);
		if(!m_Alg->myisalpha2(b1[0])){  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
			b1[0] = m_Alg->getAlphabet()->replaceInvalidLetter(true, b1[0]);
			if (b1[0] == '\0')
				b1[0] = m_Alg->getAlphabet()->getNullElement()->getValue();
		}
		if (b1[0]==b2[0]||!m_Alg->myisalpha2(b2[0]))
			return;
		s=m_Alg->getSize();
		for (i=0;i<s;i++)
		{
			for (j=0;j<s;j++)
			{
				if (b1[0] == m_Alg->getCharOfMatrix (i,j))
				{ // hole Indices vom alten Buchstaben
					a=i;
					b=j;
				}
				if (b2[0] == m_Alg->getCharOfMatrix (i,j))
				{ // hole Indices vom eingetippten Buchstaben
					c=i;
					d=j;
				}
			}
		}
		if (a>=0) { // zu ersetzender Buchstabe gefunden
			i=i;
		} else { // wie erfahre ich meine Koordinaten?
			for (i=0;(i<s)&&(a<0);i++)
				for (j=0;(j<s)&&(a<0);j++) {
					CString tmpstr;
					m_Dia->getEinfeld(i,j)->GetWindowText(tmpstr);
					if (b2[0] == tmpstr[0]) {
						a=i; b=j;
					}
				}
			i=i;
		}
		m_Alg->setElMatrix (b2[0], a, b);
		if (c>=0) { // eingetippter Buchstabe war schon vorhanden
			m_Dia->getEinfeld(c,d)->SetWindowText(b1);
			m_Alg->setElMatrix (b1[0], c, d);
		} else {
			i=i;
		}
		m_Alg->UpdateDigrams(m_Dia->getDec());
		m_Alg->DoCipher(false, m_Dia->getDec(),MAXSHOWLETTER);
		m_Dia->UpdateListBox();
		m_Dia->UpdatePassword();
	} else  // invalid character
		MessageBeep(MB_OK);
#endif
} // void CChEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)


/////////////////////////////////////////////////////////////////////////////
//
// 
//

void CChEdit::OnLButtonUp(UINT nFlags, CPoint point )
{
	CEdit::OnLButtonUp(nFlags,point);
	SetSel(0, 1);                // funktioniert nicht !!!
} 



