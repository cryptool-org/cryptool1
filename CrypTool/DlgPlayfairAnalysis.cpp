/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

// DialogPlayfair.cpp: Implementierungsdatei
//
// Men�folge: Analyse -> manuelle Analyse / Algorithmen -> Playfair...
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
	m_TextWasPreformatted = 1;
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
	DDX_Check(pDX, IDC_CHECK2, m_TextWasPreformatted);
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
	ON_BN_CLICKED(IDC_CHECK2, OnCheckTextWasPreformatted)
	ON_BN_CLICKED(IDC_RAD5, OnSechs)
	ON_BN_CLICKED(IDC_RAD6, OnSechs)
	ON_BN_CLICKED(IDC_BUTTON5, OnAnalyse)
	ON_BN_CLICKED(IDC_BUTTON6, OnSynchronise)
	ON_EN_UPDATE(IDC_MYTXT, OnManAnalyse)
	ON_EN_UPDATE(IDC_PASSWORD, OnUpdate)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_MYTXT, OnChangeEditPlaintext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgPlayfairAnalysis 
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
		if ( m_TextWasPreformatted )
		{
			if (NULLELEMENT != nChar && !m_Alg->myisalpha2(nChar))  
				nChar = m_Alg->getAlphabet()->replaceInvalidLetter(true, toupper(nChar));
			if ((NULLELEMENT==nChar) || (m_Alg->myisalpha2(nChar))) 
			{
				if ( i > 0 && NULLELEMENT != nChar && buf[i-1] == nChar )
				{
					Message(IDS_STRING_PLAYFAIR_ERRMSG121, MB_ICONEXCLAMATION);
					m_txtfeld.SetSel(i,i);
					return;
				}
				buf[i] = nChar; i++;
			}
			else 
			{
				if ((nChar=='j')||(nChar=='J')||(('0'<=nChar)&&(nChar<='9'))) 
				{
					Message(IDS_STRING_PLAYFAIR_WARNMSG003, MB_ICONEXCLAMATION);
				}
				else
				{
					Message(IDS_STRING_PLAYFAIR_ERRMSG122, MB_ICONEXCLAMATION);
				}
				m_txtfeld.SetSel(i, i+1);
				return;
			}
		} 
		else
		{
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
		}
		j++;
	}

	buf[i]='\0';
	digbuf[0]='\0';
	m_Alg->initDigrams();
	diglist = new playfair_digrammlist(m_Alg->getAlphabet(), m_Alg->getDigrams(), 
										buf, m_Alg->inbuf, min (maxchars, m_Alg->inbuflen));
	// in der Initialisierung l�uft die eigentliche Arbeit ab:
	// f�r jedes P�rchen des Klartextes, wird das passende Digramm gesucht, das durch das Chiffrat festgelegt ist.

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
			// keine g�ltige Matrix gefunden
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
// Schalter "erzeuge Matrix", war "H�ufigkeitsanalyse"
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
		// keine g�ltige Matrix gefunden
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


void CDlgPlayfairAnalysis::OnCheckTextWasPreformatted()
{
	UpdateData();
	m_txtfeld.m_TextWasPreformatted = m_TextWasPreformatted;
	UpdateData(FALSE);
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
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
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

    // ist vielleicht mit 6x6 Matrix verschl�sselt worden?
	i=0;
	while(i<MAXSHOWLETTER&&i<m_Alg->inbuflen)
	{
		c=m_Alg->inbuf[i++];
		if(!m_Alg->myisalpha2(c))  // TG, Umlaute oder franz�sische Zeichen zu etwas �hnlichem ersetzen.
			if (('J'==toupper(c)) || (('0'<=c) && (c<='9')))
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
				m_txtfeld.m_TextWasPreformatted = m_TextWasPreformatted = 0;
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
	m_txtfeld.m_TextWasPreformatted = m_TextWasPreformatted;
	m_iPos = 0;

	InitListBox();
	SetupListBox();
	SetupAnalysisWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
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
		if(!m_Alg->myisalpha2(c) && !isinvalidoccured)  // TG, Umlaute oder franz�sische Zeichen zu etwas �hnlichem ersetzen.
			c = m_Alg->getAlphabet()->replaceInvalidLetter(true, c);
		if(m_Alg->myisalpha2(c)) {
			ibuf[i] = toupper(c);
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
	m_password=m_Alg->CreatePassfromMatrix();
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

    //abpr�fen, ob ein ung�ltiges Zeichen in der Pa�wortzeile eingegeben wurde
	for(k=i=0;i<m_password.GetLength();i++) {
		c = m_password[i];
		if(!m_Alg->myisalpha2(c))  // TG, Umlaute oder franz�sische Zeichen zu etwas �hnlichem ersetzen.
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
	char b1[2],b2[2];

	if(!m_Alg->myisalpha2(nChar))  // TG, Umlaute oder franz�sische Zeichen zu etwas �hnlichem ersetzen.
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
		if(!m_Alg->myisalpha2(b1[0])){  // TG, Umlaute oder franz�sische Zeichen zu etwas �hnlichem ersetzen.
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



