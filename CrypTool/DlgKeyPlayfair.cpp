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

// Dlg_PlayfairKey.cpp: Implementierungsdatei
//
// Menüfolge: Ver-/entschlüsseln -> Klassisch -> Playfair...
//

#include "stdafx.h"
#include "assert.h"
#include "CrypToolApp.h"
#include "DlgKeyPlayfair.h"
#include "PlayfairAnalysis.h"
#include "KeyRepository.h"
#include "CrypToolTools.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyPlayfair 

CDlgKeyPlayfair::CDlgKeyPlayfair(const char *infile, const char *outfile, int reformat, int convert, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyPlayfair::IDD, pParent)
{
	int i,j;

	//{{AFX_DATA_INIT(CDlgKeyPlayfair)
	m_Alg = new CPlayfairAnalysis("", 0, infile, outfile, reformat, convert, 1);
	m_sechs = 0;
	for (i=0;i<m_Alg->getSize();i++)
	{
		for (j=0;j<m_Alg->getSize();j++)
		{
			m_mat[i][j]=m_Alg->getCharOfMatrix(i,j);
		}
	}
	//}}AFX_DATA_INIT

	// initialize Playfair options
	decryption = false;
	fileNameCleartext = infile;
	fileNameCiphertext = outfile;
	separateDoubleCharacters = true;
	separator1 = "X";
	separator2 = "Y";
	separateDoubleCharactersOnlyWithinPairs = true;
	ignoreDoubleCharactersInKey = true;
}

CDlgKeyPlayfair::~CDlgKeyPlayfair()
{
	assert (m_Alg);
    delete m_Alg; m_Alg = NULL;
}

//////////////////////////////////////////////////////////////////////////////
//
void CDlgKeyPlayfair::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyPlayfair)
	DDX_Control(pDX, IDC_KEYENTER, m_text_ctl);
	DDX_Text(pDX, IDC_KEYENTER, m_text);
	DDV_MaxChars(pDX, m_text, 36);
	DDX_Radio(pDX, IDC_RADIO3, m_sechs);
	DDX_Text(pDX, IDC_EDIT11, m_mat[0][0]);
	DDX_Text(pDX, IDC_EDIT12, m_mat[0][1]);
	DDX_Text(pDX, IDC_EDIT13, m_mat[0][2]);
	DDX_Text(pDX, IDC_EDIT14, m_mat[0][3]);
	DDX_Text(pDX, IDC_EDIT15, m_mat[0][4]);
	DDX_Control(pDX, IDC_EDIT16, m_matc[0]);
	DDX_Text(pDX, IDC_EDIT16, m_mat[0][5]);
	DDX_Text(pDX, IDC_EDIT21, m_mat[1][0]);
	DDX_Text(pDX, IDC_EDIT22, m_mat[1][1]);
	DDX_Text(pDX, IDC_EDIT23, m_mat[1][2]);
	DDX_Text(pDX, IDC_EDIT24, m_mat[1][3]);
	DDX_Text(pDX, IDC_EDIT25, m_mat[1][4]);
	DDX_Control(pDX, IDC_EDIT26, m_matc[1]);
	DDX_Text(pDX, IDC_EDIT26, m_mat[1][5]);
	DDX_Text(pDX, IDC_EDIT31, m_mat[2][0]);
	DDX_Text(pDX, IDC_EDIT32, m_mat[2][1]);
	DDX_Text(pDX, IDC_EDIT33, m_mat[2][2]);
	DDX_Text(pDX, IDC_EDIT34, m_mat[2][3]);
	DDX_Text(pDX, IDC_EDIT35, m_mat[2][4]);
	DDX_Control(pDX, IDC_EDIT36, m_matc[2]);
	DDX_Text(pDX, IDC_EDIT36, m_mat[2][5]);
	DDX_Text(pDX, IDC_EDIT41, m_mat[3][0]);
	DDX_Text(pDX, IDC_EDIT42, m_mat[3][1]);
	DDX_Text(pDX, IDC_EDIT43, m_mat[3][2]);
	DDX_Text(pDX, IDC_EDIT44, m_mat[3][3]);
	DDX_Text(pDX, IDC_EDIT45, m_mat[3][4]);
	DDX_Control(pDX, IDC_EDIT46, m_matc[3]);
	DDX_Text(pDX, IDC_EDIT46, m_mat[3][5]);
	DDX_Text(pDX, IDC_EDIT51, m_mat[4][0]);
	DDX_Text(pDX, IDC_EDIT52, m_mat[4][1]);
	DDX_Text(pDX, IDC_EDIT53, m_mat[4][2]);
	DDX_Text(pDX, IDC_EDIT54, m_mat[4][3]);
	DDX_Text(pDX, IDC_EDIT55, m_mat[4][4]);
	DDX_Control(pDX, IDC_EDIT56, m_matc[4]);
	DDX_Text(pDX, IDC_EDIT56, m_mat[4][5]);
	DDX_Control(pDX, IDC_EDIT61, m_matc[5]);
	DDX_Text(pDX, IDC_EDIT61, m_mat[5][0]);
	DDX_Control(pDX, IDC_EDIT62, m_matc[6]);
	DDX_Text(pDX, IDC_EDIT62, m_mat[5][1]);
	DDX_Control(pDX, IDC_EDIT63, m_matc[7]);
	DDX_Text(pDX, IDC_EDIT63, m_mat[5][2]);
	DDX_Control(pDX, IDC_EDIT64, m_matc[8]);
	DDX_Text(pDX, IDC_EDIT64, m_mat[5][3]);
	DDX_Control(pDX, IDC_EDIT65, m_matc[9]);
	DDX_Text(pDX, IDC_EDIT65, m_mat[5][4]);
	DDX_Control(pDX, IDC_EDIT66, m_matc[10]);
	DDX_Text(pDX, IDC_EDIT66, m_mat[5][5]);
	DDX_Check(pDX, IDC_CHECK_SEPARATE_DOUBLE_CHARACTERS, separateDoubleCharacters);
	DDX_Text(pDX, IDC_EDIT_SEPARATOR1, separator1);
	DDX_Text(pDX, IDC_EDIT_SEPARATOR2, separator2);
	DDX_Check(pDX, IDC_CHECK_SEPARATE_DOUBLE_CHARACTERS_ONLY_WITHIN_PAIRS, separateDoubleCharactersOnlyWithinPairs);
	DDX_Check(pDX, IDC_CHECK_IGNORE_DOUBLE_CHARACTERS_IN_KEY, ignoreDoubleCharactersInKey);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyPlayfair, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyPlayfair)
	ON_EN_UPDATE(IDC_KEYENTER, OnUpdateEdit1)
	ON_BN_CLICKED(IDC_RADIO3, OnSechs)
	ON_BN_CLICKED(IDC_RADIO4, OnSechs)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck)
	ON_BN_CLICKED(IDC_PREFORM, OnCheck)
	ON_BN_CLICKED(IDC_CHECK_SEPARATE_LETTERS, OnCheck)
	ON_EN_CHANGE(IDC_EDIT_SEPARATOR1, OnChangeSeparator)
	ON_EN_CHANGE(IDC_EDIT_SEPARATOR2, OnChangeSeparator)
	ON_BN_CLICKED(IDC_CHECK_SEPARATE_LETTERS_ONLY_IN_PAIRS, OnCheck)
	ON_BN_CLICKED(IDC_CHECK_IGNORE_DOUBLE_CHARACTERS_IN_KEY, OnCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////
//

BOOL CDlgKeyPlayfair::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString Title;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PLAYFAIR,pc_str,STR_LAENGE_STRING_TABLE);
	Title = pc_str;
	VERIFY(m_Paste.AutoLoad(IDC_BUTTON2,this));
	if ( IsKeyEmpty( Title ))
	{
		m_Paste.EnableWindow(TRUE);
	}
	else
	{
		m_Paste.EnableWindow(FALSE);
	}

	// add tool tip to the paste button
	CString buttonPasteText;
	buttonPasteText.LoadString(IDS_STRING_PASTE_KEY_FROM_KEY_STORE);
	m_Paste.SetToolTipText(&buttonPasteText);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyPlayfair 

void CDlgKeyPlayfair::OnCheck() 
// Doppelte Zeichen ignorieren oder nicht
{
	UpdateData(TRUE);
	m_Alg->PassUse(ignoreDoubleCharactersInKey);
	
	// flomar, 04/16/2010
	CWnd *windowCheckSeparator = GetDlgItem(IDC_CHECK_SEPARATE_DOUBLE_CHARACTERS);
	CWnd *windowTextSeparator1 = GetDlgItem(IDC_STATIC_TEXT_SEPARATOR1);
	CWnd *windowTextSeparator2 = GetDlgItem(IDC_STATIC_TEXT_SEPARATOR2);
	CWnd *windowEditSeparator1 = GetDlgItem(IDC_EDIT_SEPARATOR1);
	CWnd *windowEditSeparator2 = GetDlgItem(IDC_EDIT_SEPARATOR2);
	CWnd *windowCheckSeparatorOnlyWithinPairs = GetDlgItem(IDC_CHECK_SEPARATE_DOUBLE_CHARACTERS_ONLY_WITHIN_PAIRS);

	// don't do anything if there's an invalid window
	if(windowCheckSeparator && windowTextSeparator1 && windowTextSeparator2 && windowEditSeparator1 && windowEditSeparator2 && windowCheckSeparatorOnlyWithinPairs) {
		// disable all separator-related windows by default
		windowTextSeparator1->EnableWindow(false);
		windowTextSeparator2->EnableWindow(false);
		windowEditSeparator1->EnableWindow(false);
		windowEditSeparator2->EnableWindow(false);
		windowCheckSeparatorOnlyWithinPairs->EnableWindow(false);
		// enable them if "separateDoubleCharacters" is set
		if(separateDoubleCharacters) {
			windowTextSeparator1->EnableWindow(true);
			windowTextSeparator2->EnableWindow(true);
			windowEditSeparator1->EnableWindow(true);
			windowEditSeparator2->EnableWindow(true);
			windowCheckSeparatorOnlyWithinPairs->EnableWindow(true);
		}
		// implicitly check the separator
		OnChangeSeparator();
	}

	UpdateData(FALSE);
	OnUpdateEdit1();
}

void CDlgKeyPlayfair::OnSechs() 
// statt 5x5 wurde 6x6 oder umgekehrt ausgewählt
{
	int i;

	UpdateData(TRUE);
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if (m_sechs == 1)
	{
		m_Alg->SetSize(true);
		for (i=0;i<11;i++)
			m_matc[i].EnableWindow(TRUE);
	}
	else
	{
		m_Alg->SetSize(false);
		for (i=0;i<11;i++)
			m_matc[i].EnableWindow(FALSE);
		for (i=0;i<6;i++)
			m_mat[i][5]="";
		for (i=0;i<5;i++)
			m_mat[5][i]="";
	}
	UpdateData(FALSE);
	OnUpdateEdit1();
}

void CDlgKeyPlayfair::OnChange() 
{
	char tmp[100];
	int i,j;

	UpdateData(TRUE);
	strcpy(tmp,m_text);
	m_Alg->SetPass( tmp );
	for (i=0;i<m_Alg->getSize();i++)
	{
		for (j=0;j<m_Alg->getSize();j++)
		{
			m_mat[i][j]=m_Alg->getCharOfMatrix(i,j);
		}
	}
	UpdateData(FALSE);
}

char *CDlgKeyPlayfair::GetData()
{
	return m_text.GetBuffer(25);
}

int CDlgKeyPlayfair::Display()
{
	int res;
	res=DoModal();
	return res;
}

void CDlgKeyPlayfair::OnUpdateEdit1() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); /* get the displayed value in m_text */
	m_text_ctl.GetSel(sels, sele);
	res.Empty();

	m_text.MakeUpper();

	for(k=i=0;i<m_text.GetLength();i++) {
		c = m_text[i];
		if(!m_Alg->myisalpha2(c))  // TG, Umlaute oder französische Zeichen zu etwas ähnlichem ersetzen.
#pragma warning( disable : 4800 )
			c = m_Alg->getAlphabet()->replaceInvalidLetter(true, c);
		if(m_Alg->myisalpha2(c)) { // valid character
			res += c;
			k++;
		}
		else { // invalid character (e.g. white spaces)
			MessageBeep(MB_OK);
			if(k<sels) sels--;
			if(k<sele) sele--;
		} 
	}

	m_text = res;
	UpdateData(FALSE);
	m_text_ctl.SetSel(sels,sele);
	OnChange();
} 

void CDlgKeyPlayfair::OnDecrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	decryption = true;
	OnOK();
}

void CDlgKeyPlayfair::OnEncrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	decryption = false;
	OnOK();
}

void CDlgKeyPlayfair::OnPasteKey() 
{
	UpdateData(TRUE);
	// retrieve complete Playfair key from the key store
	CString stringCompleteKey;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PLAYFAIR,pc_str,STR_LAENGE_STRING_TABLE);
	if(PasteKey(pc_str, stringCompleteKey)) {
		m_text = extractValueFromStringByKey("KEY", stringCompleteKey);
		separator1 = extractValueFromStringByKey("SEPARATOR1", stringCompleteKey);
		separator2 = extractValueFromStringByKey("SEPARATOR2", stringCompleteKey);
		m_sechs = extractValueFromStringByKey("MATRIXSIZE", stringCompleteKey) == "6" ? 1 : 0;
		if(stringCompleteKey.Find(STR_OPT_SEPERATE_DUPLICATE_ONLY_WITHIN_PAIRS))
			separateDoubleCharactersOnlyWithinPairs = 1;
		if(stringCompleteKey.Find(STR_OPT_IGNORE_DUPLICATE_LETTERS_IN_KEY))
			ignoreDoubleCharactersInKey = 1;
	}
	UpdateData(FALSE);	
	OnChange();
}

void CDlgKeyPlayfair::OnChangeSeparator()
{
	UpdateData(TRUE);
	
	// flomar, 04/16/2010
	// valid separators are A-Z, and we go with "X" and "Y" by default;
	// this behavior is based on the old implementation in CDlgTextOptions
	
	if(separator1.GetLength() == 0) {
		separator1 = "X";
	}
	if(separator1.GetLength() > 1) {
		separator1.Delete(1, separator1.GetLength() - 1);
	}
	// at this point we have exactly one character
	if(separator1[0] < 'A' || separator1[0] > 'Z') {
		separator1 = "X";
	}

	if(separator2.GetLength() == 0) {
		separator2 = "Y";
	}
	if(separator2.GetLength() > 1) {
		separator2.Delete(1, separator2.GetLength() - 1);
	}
	// at this point we have exactly one character
	if(separator2[0] < 'A' || separator2[0] > 'Z') {
		separator2 = "Y";
	}

	// if both separators are equal, we go with X and Y
	if(separator1 == separator2) {
		separator1 = "X";
		separator2 = "Y";
	}

	UpdateData(FALSE);
}

PlayfairOptions CDlgKeyPlayfair::getPlayfairOptions()
{
	PlayfairOptions playfairOptions;
	playfairOptions.decryption = decryption;
	playfairOptions.fileNameCleartext = fileNameCleartext;
	playfairOptions.fileNameCiphertext = fileNameCiphertext;
	playfairOptions.separateDoubleCharacters = separateDoubleCharacters;
	playfairOptions.separator1 = separator1;
	playfairOptions.separator2 = separator2;
	playfairOptions.separateDoubleCharactersOnlyWithinPairs = separateDoubleCharactersOnlyWithinPairs;
	playfairOptions.ignoreDoubleCharactersInKey = ignoreDoubleCharactersInKey;
	playfairOptions.matrixSize = m_sechs ? 6 : 5;
	return playfairOptions;
}