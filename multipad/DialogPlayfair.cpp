//////////////////////////////////////////////////////////////////
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

// DialogPlayfair.cpp: Implementierungsdatei
//
// Menüfolge: Analyse -> manuelle Analyse / Algorithmen -> Playfair...
//

#include "stdafx.h"
#include "multipad.h"
#include "DialogPlayfair.h"
#include "playfair.h"
#include "assert.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogPlayfair 

CDialogPlayfair::CDialogPlayfair(const char *infile,const char *outfile,int r,int c,CWnd* pParent /*=NULL*/)
               : CDialog(CDialogPlayfair::IDD, pParent)
{
	int i,j;

	m_Alg = new Playfair("",0,infile,outfile,r,c,1);
//	m_Alg->SetSize(false);
//	m_Alg->GetDiGrams();

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
	m_txtfeld.SetAlg(m_Alg);

	//{{AFX_DATA_INIT(CDialogPlayfair)
	m_use=1;
	m_Dec=1;
	m_sechs=0;
	m_mytxt=_T("");
	//}}AFX_DATA_INIT
}


void CDialogPlayfair::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPlayfair)
	DDX_Radio(pDX, IDC_RADE, m_Dec);
	DDX_Radio(pDX, IDC_RAD6, m_sechs);
	DDX_Control(pDX, IDC_PLAYFAIR_LIST, m_listview);
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
	DDX_Control(pDX, IDC_LIST, m_ciphfeld);
	DDX_Control(pDX, IDC_PASSWORD, m_pwfeld);
	DDX_Control(pDX, IDC_MYTXT, m_txtfeld);
	DDV_MaxChars(pDX, m_mytxt, 300);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 36);
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
	DDX_Text(pDX, IDC_LIST, m_cipher);
	DDV_MaxChars(pDX, m_cipher, 3000);
	//DDX_Text(pDX, IDC_NUMD, m_Alg->numdigrams);
	DDX_Check(pDX, IDC_CHECK1, m_use);
	DDX_Text(pDX, IDC_MYTXT, m_mytxt);
	//}}AFX_DATA_MAP

}



BEGIN_MESSAGE_MAP(CDialogPlayfair, CDialog)
	//{{AFX_MSG_MAP(CDialogPlayfair)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck)
	ON_BN_CLICKED(IDC_RAD5, OnSechs)
	ON_BN_CLICKED(IDC_RAD6, OnSechs)
	ON_BN_CLICKED(IDC_RADE, OnDec)
	ON_BN_CLICKED(IDC_RADV, OnDec)
	ON_BN_CLICKED(IDC_BUTTON5, OnAnalyse)
	ON_EN_UPDATE(IDC_MYTXT, OnManAnalyse)
	ON_EN_UPDATE(IDC_PASSWORD, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDialogPlayfair 
char *CDialogPlayfair::GetData()
{
	return m_password.GetBuffer(25);
}

void CDialogPlayfair::OnManAnalyse()
{
	char buf[302], line[256];
	int i,n, k;
	int maxchars=300;
	playfair_digrammlist* diglist;

	UpdateData(TRUE);
	
	i=0;
	while ((i<maxchars)&&(i<m_mytxt.GetLength())) {
		buf[i] = m_mytxt[i]; i++;
	}
	buf[i]='\0';
	diglist = new playfair_digrammlist(m_Alg->getAlphabet(), m_Alg->getDigrams(), buf, m_Alg->inbuf, min (maxchars, m_Alg->inbuflen));
	// in der Initialisierung läuft die eigentliche Arbeit ab:
	// für jedes Pärchen des Klartextes, wird das passende Digramm gesucht, das durch das Chiffrat festgelegt ist.

	n = 2*diglist->getLen();
	m_txtfeld.SetLimitText (n); // limitiere Ausgabe
	//diglist->getChiffreString(buf, n); // belege Ausgabevariable buf (1.Zeile)mit Chiffrat
	diglist->getPlainString(digbuf, n); // lege Ausgabe des Klartextes fest (2.Zeile)

	try {
		if (i%2==0) {
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
		sprintf(line,pc_str,e.getCode(),(e.getLetter())?e.getLetter()->getValue():m_Alg->getAlphabet()->getNullElement()->getValue());
		AfxMessageBox (line);
	}

	if ((true) && (i%2==0)) {
		//automatische Generierung der Matrix aktiv

//		if (!m_Alg->CreateMatrixfromLettergraph (buf, i)) { // Analyse Thomas Gauweiler
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


void CDialogPlayfair::OnAnalyse()
// Schalter "erzeuge Matrix", war "Häufigkeitsanalyse"
{
/*
	char buf[302],c;
	struct digram *dig;
	class Playfair *plf;
	int i,n,j,s;

	// erstmal von der Vorlage eine Häufigkeitsverteilung der Digramme fürs deutsche Alphabet erstellen.
	plf = new class Playfair("",m_Alg->size==6?1:0,theApp.TextOptions.m_StrRefFile,"tmp",m_Alg->ReFormat,m_Alg->ConvertCase,1);
	n=min(m_Alg->numdigrams,plf->numdigrams);

	dig=(struct digram *)malloc(n*sizeof(struct digram));
	for(i=0;i<n;i++)
	{
		strncpy(dig[i].di,plf->digrams[i].di,3);
		strncpy(dig[i].ciphdi,m_Alg->digrams[i].di,3);
	}
	m_Alg->AnalyseDigramme(&n,dig);
	i=j=0;
	while(i<300&&j<m_Alg->inbuflen)
	{
		c=m_Alg->inbuf[j++];
		if(m_Alg->myisalpha(c))
			buf[i++]=toupper(c);
	}
	buf[i]=0;
	m_txtfeld.SetLimitText(i);
	s=i/2;
	for(i=0;i<s;i++)
	{
		char d[2],e[2];

		d[0]=d[1]=NULLELEMENT;
		strncpy(e,buf+(i*2),2); 
		for(j=0;j<n;j++)
		{
			if(strncmp(e,dig[j].ciphdi,2)==0)
				strncpy(d,dig[j].di,2);
		}
		strncpy(digbuf+(i*2),d,2);
	}
	*(digbuf+(i*2))=0;
	free(dig);

	// jetzt wird die Ausgabe aktualisiert
	UpdateData(TRUE); // hole Daten vom Formular
	m_mytxt=digbuf;
	m_Alg->GetDiGrams();
	m_Alg->UpdateDigrams(m_Dec);
	for (i=0;i<m_Alg->size;i++)
	{
		for (j=0;j<m_Alg->size;j++)
			m_mat[i][j]=m_Alg->matrix[i][j];
	}
	m_password=m_Alg->CreatePassfromMatrix();
	UpdateData(FALSE); // schiebe Daten aus den Variablen ins Formular
	UpdateListBox(); // akualisiere die unteren drei Zeilen (Code,Vorgabe,Klartext)
*/
}



void CDialogPlayfair::OnCheck()
// Doppelte ignorieren oder nicht
{
	m_Alg->PassUse(m_use);
	OnUpdate();
	m_Alg->SetPass("");
}



void CDialogPlayfair::OnDec() 
// Ver- oder Entschlüsseln
{
	UpdateData(TRUE);
	m_Alg->UpdateDigrams(m_Dec);
	UpdateData(FALSE);
	UpdateListBox();
}



void CDialogPlayfair::OnSechs() 
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
//	m_Alg->GetDiGrams();
	m_Alg->UpdateDigrams(m_Dec);
	for (i=0;i<m_Alg->getSize();i++)
	{
		for (j=0;j<m_Alg->getSize();j++)
		{
			m_mat[i][j]=m_Alg->getCharOfMatrix(i,j);
		}
	}
	UpdateData(FALSE);
	InitListBox();	
} // void CDialogPlayfair::OnSechs()

BOOL CDialogPlayfair::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// m_listview in Report-Mode initialisieren

	m_Font.CreateFont(0,0,0,0,0,0,0,0,DEFAULT_CHARSET,OUT_RASTER_PRECIS,0,DEFAULT_QUALITY,FIXED_PITCH|FF_DONTCARE,NULL);
	m_ciphfeld.SetFont(&m_Font);
	m_txtfeld.SetFont(&m_Font);

	int colWidth = 55;  // Spaltenbreite in Pixel

//	LoadString(AfxGetInstanceHandle(),IDS_STRING_BEFORE,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 0, " ", LVCFMT_LEFT, colWidth-30 , 0); // Buchstabe
//	Wie schaltet man Wingdins ein?
//	m_listview.InsertColumn( 1, "ïðñò", LVCFMT_LEFT, colWidth-20 , 3); // 
	m_listview.InsertColumn( 1, "LROU", LVCFMT_LEFT, colWidth , 3); // 
	m_listview.InsertColumn( 2, "Nb?", LVCFMT_LEFT, colWidth , 3); // 
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HORIZ,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 3, pc_str, LVCFMT_LEFT, colWidth+30 , 1); // 
	LoadString(AfxGetInstanceHandle(),IDS_STRING_VERT,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 4, pc_str, LVCFMT_LEFT, colWidth+30 , 2); // 
	m_listview.InsertColumn( 5, "row or col?", LVCFMT_LEFT, colWidth+60 , 3); // 
	m_listview.InsertColumn( 6, "Metrik", LVCFMT_LEFT, colWidth , 3); // 

	InitListBox();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDialogPlayfair::UpdateListBox()
{
	int i,j;
	char buf[302],c,s[100];
	playfair_letter *let;

	m_listview.DeleteAllItems( );

//TG	for (i=0;i<m_Alg->numdigrams;i++)
//		m_listview.SetItemText( i, 1, m_Alg->digrams[i].ciphdi);
	for (j=i=0; i < m_Alg->getLetterlist()->getLen(); i++) {
//		if (m_Alg->getAlphabet()->getValidOfLetter(i)) {
//			let = &(m_Alg->getAlphabet()->getLetters()[i]);
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

//	m_ciphfeld.SetSel(0,m_ciphfeld.LineLength());
//	m_ciphfeld.ReplaceSel(m_Alg->outbuf);
//	m_ciphfeld.SetSel(0,0);

	m_Alg->DoCipher(m_Dec,300);
	UpdateData(TRUE);

//	/* wird veralteten
	i=j=0;
	while(i<300&&j<m_Alg->inbuflen)
	{
		c=m_Alg->inbuf[j++];
		if(!m_Alg->myisalpha2(c))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
			c = m_Alg->getAlphabet()->replaceInvalidLetter(true, c);
		if(m_Alg->myisalpha2(c))
			buf[i++]=toupper(c);
	}
	buf[i]=0;
//	*/
	m_cipher.Format("%s\r\n%s\r\n%s\r\n",buf,digbuf,m_Alg->outbuf);
	UpdateData(FALSE);
} // void CDialogPlayfair::UpdateListBox()

void CDialogPlayfair::UpdatePassword()
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
	m_password=m_Alg->CreatePassfromMatrix();
	UpdateData(FALSE);
} // void CDialogPlayfair::UpdatePassword()


void CDialogPlayfair::InitListBox()
{
//	int i; // Zeile

/*	m_listview.DeleteAllItems( );

	for (i=0;i<m_Alg->numdigrams;i++)
	{
		char c[10];

		sprintf(c,"%d",m_Alg->digrams[i].anz);
		m_listview.InsertItem(i,m_Alg->digrams[i].di);
		m_listview.SetItemText( i, 1, m_Alg->digrams[i].ciphdi);
		m_listview.SetItemText( i, 2, c );
	}
*/
	m_Alg->DoCipher(m_Dec,300);

	UpdateData(TRUE);
	m_cipher=m_Alg->outbuf;
	UpdateData(FALSE);

	// Gauweiler 30.1.01, statt eine einzelne Zeile, sollten gleich alle drei Zeilen angezeigt werden.
	// da die Update-Fkt das richtig macht, soll sie gleich mal zum ersten Mal ihre Arbeit machen.
	strcpy(digbuf,"");
	UpdateListBox();

} // void CDialogPlayfair::InitListBox()



int CDialogPlayfair::Display()
{
	int res;

	res=DoModal();

	return res;
}


void CDialogPlayfair::OnUpdate() 
// sobald ein neues Zeichen eingegeben wurde (Passwort, Matrix, oder Klartextvorgabe)
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
	m_Alg->SetPass(m_password.GetBuffer(25));
	//m_Alg->CreateMatrixFromPass();
	//m_Alg->GetDiGrams();
	//m_Alg->UpdateDigrams(m_Dec);

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
	m_pwfeld.SetSel(sels,sele);
} // void CDialogPlayfair::OnUpdate()


CChEdit::CChEdit()
{
}

CChEdit::~CChEdit()
{
}

/* jetzt als Inline-Funktion in Header-Datei [TG]
void CChEdit::SetAlg(class Playfair *alg,class CDialogPlayfair *dia)
{
	m_Alg=alg;
	m_Dia=dia;
}
*/

BEGIN_MESSAGE_MAP(CChEdit, CEdit)
	//{{AFX_MSG_MAP(CHexEdit)
	ON_WM_CHAR()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CChEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	char b1[2],b2[2];

	if(!m_Alg->myisalpha2(nChar))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
		nChar = m_Alg->getAlphabet()->replaceInvalidLetter(true, toupper(nChar));
	if (m_Alg->myisalpha2(nChar))
	{
		int i,j,s,a,b,c,d;

		a=-1; c =-1;
		b2[1]=0;
		b2[0]=toupper(nChar);
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
//					char jkl = [0];
//					char jkl = m_Dia->getEinfeld(i,j)->GetWindowText()[0];
//					if (b2[0] == m_Dia->getMatrixElement(i,j)) {
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
		m_Alg->DoCipher(m_Dia->getDec(),300);
		m_Dia->UpdateListBox();
		m_Dia->UpdatePassword();
	} else  // invalid character
		MessageBeep(MB_OK);

} // void CChEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)

void CChEdit::OnLButtonUp(UINT nFlags, CPoint point )
{
	CEdit::OnLButtonUp(nFlags,point);
	SetSel(0, 1);                // funktioniert nicht !!!
} 

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
}

/* jetzt als Inline-Fkt in Header-Datei [TG]
void CMyEdit::SetAlg(class Playfair *alg)
{
	m_Alg=alg;
}
*/

BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CHexEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	char b2[2];
	int i,j,k;

	if((!m_Alg->myisalpha2(nChar)) && (nChar>32))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
			nChar = m_Alg->getAlphabet()->replaceInvalidLetter(true, nChar);
	if (m_Alg->myisalpha2(nChar))
	{
		b2[1]=0;
		b2[0]=toupper(nChar);
		GetSel(i,j);
		if(i==j)
			SetSel(i,j=i+1);
		ReplaceSel(b2);
		SetSel(j,j);
	}
	else if(nChar==8)
	{
		GetSel(i,j);
		if(i==j&&i==0)
			return;
		b2[0] = NULLELEMENT;
		b2[1] = 0;
		for(k=(i==0?0:i-1);k<j;k++)
		{
			SetSel(k,k+1);
			ReplaceSel(b2);
		}
		SetSel(i-1,i-1);
	}
	else if(nChar==3||nChar==22||nChar==24)
		CEdit::OnChar(nChar,nRepCnt,nFlags);
	else
	{
		b2[0] = NULLELEMENT;
		b2[1] = '\0';
		GetSel(i,j);
		if(i==j)
			SetSel(i,j=i+1);
		ReplaceSel(b2);
		SetSel(j,j);
	}
} // void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
