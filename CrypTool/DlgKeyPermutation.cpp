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

// DialogPermutation.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "AscEdit.h"
#include "DlgKeyPermutation.h"
#include "DlgKeyPermutationInfo.h"		  

#include "KeyRepository.h"
#include "DialogeMessage.h"
#include ".\dlgkeypermutation.h"
#include "CrypToolTools.h"
#include "ChrTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyPermutation 


CDlgKeyPermutation::CDlgKeyPermutation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyPermutation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyPermutation)
	m_Perm1		= _T("");
	m_Perm2		= _T("");
	m_P1out		= _T("");
	m_P2out		= _T("");
	m_P1InSeq	= 0;
	m_P1OutSeq	= 1;
	m_P2InSeq	= 0;
	m_P2OutSeq	= 1;
	m_P1Perm	= -1;
	m_P2Perm	= -1;
	m_Invert	= FALSE;
	m_DataType	= 0;
	//}}AFX_DATA_INIT
}


void CDlgKeyPermutation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyPermutation)
	DDX_Control(pDX, IDC_BUTTON1, m_Decrypt);
	DDX_Control(pDX, IDOK, m_Encrypt);
	DDX_Control(pDX, IDC_EDIT2, m_CPerm2);
	DDX_Control(pDX, IDC_EDIT1, m_CPerm1);
	DDX_Text(pDX, IDC_EDIT1, m_Perm1);
	DDX_Text(pDX, IDC_EDIT2, m_Perm2);
	DDX_Text(pDX, IDC_EDIT3, m_P1out);
	DDX_Text(pDX, IDC_EDIT4, m_P2out);
	DDX_Radio(pDX, IDC_RADIO1, m_P1InSeq);
	DDX_Radio(pDX, IDC_RADIO3, m_P1OutSeq);
	DDX_Radio(pDX, IDC_RADIO5, m_P2InSeq);
	DDX_Radio(pDX, IDC_RADIO7, m_P2OutSeq);
	DDX_Radio(pDX, IDC_RADIO10, m_P1Perm);
	DDX_Radio(pDX, IDC_RADIO12, m_P2Perm);
	DDX_Radio(pDX, IDC_RADIO9, m_DataType);
	DDX_Check(pDX, IDC_CHECK1, m_Invert);
	DDX_Control(pDX, IDC_CHECK2, chk_showPermutations);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyPermutation, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyPermutation)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
	ON_BN_CLICKED(IDC_BUTTON_TxtOpt, OnTextOptions)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_BN_CLICKED(IDC_RADIO9, OnRadioButtonBinaryData)
	ON_BN_CLICKED(IDC_RADIO14, OnRadioButtonText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyPermutation 
void CDlgKeyPermutation::strKeyParam()
{
	LoadString(AfxGetInstanceHandle(),IDS_PARAM_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
	CString Primes = CString(PARAM_TOKEN)
		+ char(m_DataType+ '0') + ' ' + char((int)m_Invert + '0') + ' '
		+ char(m_P1InSeq + '0') + ' ' + char(m_P1Perm + '0') + ' ' + char(m_P1OutSeq + '0') + ' '
		+ char(m_P2InSeq + '0') + ' ' + char(m_P2Perm + '0') + ' ' + char(m_P2OutSeq + '0');
	CopyKey ( pc_str, Primes );
}

void CDlgKeyPermutation::writeRegistry()
{
	if (ERROR_SUCCESS == CT_OPEN_REGISTRY_SETTINGS	(KEY_WRITE, IDS_REGISTRY_SETTINGS, "Permutation"))
	{
		CT_WRITE_REGISTRY((unsigned long)chk_showPermutations.GetCheck(), "ShowPermutationKey");
		CT_CLOSE_REGISTRY();
	}
}

int CDlgKeyPermutation::chekPermInput(CString &m_Perm, CAscEdit &cInput, int MSG_ID )
{
	if( m_Perm.GetLength() && ((m_Perm[0]=='0') || (m_Perm.Find(",0",0)!=(-1))) )
	{
		LoadString(AfxGetInstanceHandle(), MSG_ID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,"CrypTool",MB_ICONWARNING|MB_OK);
		cInput.SetFocus();
		return 0;
	}
	return 1;
}

void CDlgKeyPermutation::OnDecrypt() 
{
	UpdateData(TRUE);

	// Nullen dürfen nicht eingegeben werden
	// Überprüfung IDC_EDIT1
	if ( !chekPermInput(m_Perm1, m_CPerm1, IDS_STRING_MSG_PERM_ZERO_INVALID_INPUT) ||
		 !chekPermInput(m_Perm2, m_CPerm2, IDS_STRING_MSG_PERM_ZERO_INVALID_INPUT2) )
		return;

	m_P1len = MakePerm(&m_Perm1, m_P1, m_P1inv);
	if(m_P1len <= 0) {
		m_CPerm1.SetFocus();
		return;
	}
	m_P2len = MakePerm(&m_Perm2, m_P2, m_P2inv);
	if(m_P2len < 0) {
		m_CPerm2.SetFocus();
		return;
	}
	m_Dec = 1;

	if ( !(chk_showPermutations.GetCheck() && IDOK != ShowPermutations()) )
	{
		// flomar, 11/09/2011: no longer display an information message in binary mode; display the 
		// information message in text mode only if the input text contains non-alphabet characters
		if(m_DataType && !doesInputComplyWithAlphabet()) {
			Message(IDS_INFO_TEXT_ENCRYPTION, MB_ICONINFORMATION);
		}

		strKeyParam();
		writeRegistry();
		OnOK();
	}
}

void CDlgKeyPermutation::OnEncrypt() 
{
	UpdateData(TRUE);

	// Nullen dürfen nicht eingegeben werden
	// Überprüfung IDC_EDIT1
	if ( !chekPermInput(m_Perm1, m_CPerm1, IDS_STRING_MSG_PERM_ZERO_INVALID_INPUT) ||
		 !chekPermInput(m_Perm2, m_CPerm2, IDS_STRING_MSG_PERM_ZERO_INVALID_INPUT2) )
		return;
	
	m_P1len = MakePerm(&m_Perm1, m_P1, m_P1inv);
	if(m_P1len <= 0)
	{
		m_CPerm1.SetFocus();
		return;
	}
	m_P2len = MakePerm(&m_Perm2, m_P2, m_P2inv);
	if(m_P2len < 0)
	{
		m_CPerm2.SetFocus();
		return;
	}
	m_Dec = 0;

	if ( !(chk_showPermutations.GetCheck() && IDOK != ShowPermutations()) )
	{
		// flomar, 11/09/2011: no longer display an information message in binary mode; display the 
		// information message in text mode only if the input text contains non-alphabet characters
		if(m_DataType && !doesInputComplyWithAlphabet()) {
			Message(IDS_INFO_TEXT_ENCRYPTION, MB_ICONINFORMATION);
		}

		strKeyParam();
		writeRegistry();
		OnOK();
	}
}

void CDlgKeyPermutation::setInputFilename(CString _inputFilename) {
	inputFilename = _inputFilename;
}

bool CDlgKeyPermutation::doesInputComplyWithAlphabet() {
	CFile file;
	file.Open(inputFilename, CFile::modeRead);
	ULONGLONG m_fileSize = file.GetLength();	
	file.Close();
	int lSrc = 0;
	char *mSrc = 0;
	FILE *fstrm;
	if(fstrm = fopen(inputFilename, "rb")) {
		lSrc = (int)m_fileSize;
		mSrc = (char*)malloc( lSrc+1 );
		fread(mSrc, sizeof(char), (size_t)m_fileSize, fstrm );
		mSrc[lSrc] = '\0';
		fclose(fstrm);
		CString alphabet = theApp.TextOptions.getAlphabet();
		for(int i=0; i<lSrc; i++) {
			if(alphabet.Find(mSrc[i]) == -1) {
				return false;
			}
		}
	}
	else {
		return false;
	}
	return true;
}

int CDlgKeyPermutation::MakePerm( CString *Pin, int p[], int pinv[])
{
	int i, j, plen;

	if(Pin->GetLength() == 0) return 0;
	if(isdigit((*Pin)[0])) return MakePermInt( Pin, p, pinv);
	Pin->MakeUpper();

	for(i=0;i<Pin->GetLength();) {
		if(strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", Pin->GetAt(i)))
			i++;
		else
			Pin->Delete(i);
	}
	// take into account only the first MAX_PERM_LENGTH characters
	if(Pin->GetLength() > MAX_PERM_LENGTH) {
		Pin->Delete(MAX_PERM_LENGTH, Pin->GetLength() - MAX_PERM_LENGTH);
	}
	plen = Pin->GetLength();
	if(plen == 0) return 0;

	// Analog ADFGVX
	for (i=0; i<plen; i++) p[i] = 0;
	for (i=0; i<plen; i++)
		for (j=i+1; j<plen; j++)
			if ( Pin->GetAt(i) > Pin->GetAt(j) )
				p[i]++;
			else
				p[j]++;
	for(i=0; i<plen; i++) 
		pinv[p[i]]=i;

	return plen;
}

void CDlgKeyPermutation::OnChangeEdit1() 
{
	int l;
	char buffer[1024];
	memset(buffer, 0, 1024);

	UpdateData(TRUE);
	m_CPerm1.EmptyUndoBuffer();
	l= m_Perm1.GetLength();
	if(l>1) {
		m_Decrypt.EnableWindow(TRUE);
		m_Encrypt.EnableWindow(TRUE);
		if(MyIsAlpha(m_Perm1[0])) {
			m_P1len = MakePerm(&m_Perm1, m_P1, m_P1inv);
			if(m_P1len > 0) PrintPerm(buffer, m_P1, m_P1len);
			m_P1out = buffer;
		}
		else {
			makeASCII(m_Perm1);
			m_P1out = "";
			m_P1len = -1;
		}
	}
	else {
		m_Decrypt.EnableWindow(FALSE);
		m_Encrypt.EnableWindow(FALSE);
		m_P1out = "( 1 )";
	}
	UpdateData(FALSE);
}

void CDlgKeyPermutation::OnChangeEdit2() 
{
	int l;
	char buffer[1024];

	UpdateData(TRUE);
	m_CPerm2.EmptyUndoBuffer();
	l= m_Perm2.GetLength();
	if(l>1) {
		if(MyIsAlpha(m_Perm2[0])) {
			m_P2len = MakePerm(&m_Perm2, m_P2, m_P2inv);
			if(m_P2len > 0) PrintPerm(buffer, m_P2, m_P2len);
			m_P2out = buffer;
		}
		else {
			makeASCII(m_Perm2);
			m_P2out = "";
			m_P2len = -1;
		}
	}
	else {
		m_P2out = "( 1 )";
	}
	UpdateData(FALSE);
}

void CDlgKeyPermutation::OnRadioButtonBinaryData()
{
	GetDlgItem(IDC_BUTTON_TxtOpt)->EnableWindow(false);
}

void CDlgKeyPermutation::OnRadioButtonText()
{
	GetDlgItem(IDC_BUTTON_TxtOpt)->EnableWindow(true);
}

void CDlgKeyPermutation::OnTextOptions()
{
	theApp.TextOptions.DoModal();
}

BOOL CDlgKeyPermutation::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LoadString(AfxGetInstanceHandle(),IDS_PARAM_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
	CString Primes;
	if ( PasteKey( pc_str, Primes ) )
	{
		UpdateData(true);
		int d = strlen(PARAM_TOKEN);
		m_DataType	= (int)(Primes[d]	 - '0');
		m_Invert	= (int)(Primes[d+2]	 - '0');
		m_P1InSeq	= (int)(Primes[d+4]  - '0');
		m_P1Perm	= (int)(Primes[d+6]  - '0');
		m_P1OutSeq	= (int)(Primes[d+8]  - '0');
		m_P2InSeq	= (int)(Primes[d+10] - '0');
		m_P2Perm	= (int)(Primes[d+12] - '0');
		m_P2OutSeq	= (int)(Primes[d+14] - '0');
		UpdateData(false);
	}
	else
	{
		UpdateData(true);
		int d = Primes.Find(PARAM_TOKEN, 0);
		m_DataType  = 0;
		m_Invert	= false;
		m_P1InSeq   = 0;
		m_P1Perm	= 1;
		m_P1OutSeq	= 1;
		m_P2InSeq	= 0;
		m_P2Perm	= 1;
		m_P2OutSeq	= 1;
		UpdateData(false);
	}

	m_Decrypt.EnableWindow(FALSE);
	m_Encrypt.EnableWindow(FALSE);
	m_P1out = m_P2out = "( 1 )";
	UpdateData(FALSE);

	CString Title;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
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

	if (ERROR_SUCCESS == CT_OPEN_REGISTRY_SETTINGS	(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "Permutation"))
	{
		unsigned long u_showPermutations = 1;
		if ( CT_READ_REGISTRY_DEFAULT(u_showPermutations, "ShowPermutationKey", u_showPermutations) )
			chk_showPermutations.SetCheck(int(u_showPermutations));
		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

	// enable/disable the text options button depending on the data type 
	// (enabled for text, disabled for binary)
	GetDlgItem(IDC_BUTTON_TxtOpt)->EnableWindow(m_DataType != 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

int CDlgKeyPermutation::PrintPerm(char *dest, int *perm, int len)
{
	int i;
	char buffer[MAX_PERM_LENGTH];

	if(len < 2) {
		strcpy(dest,"( 1 )");
		return strlen(dest);
	}
	sprintf(dest,"( %d", perm[0]+1);
	for(i=1;i<len;i++) {
		sprintf(buffer,", %d", perm[i]+1);
		strcat(dest, buffer);
	}
	strcat(dest, " )");
	return strlen(dest);
}

int CDlgKeyPermutation::readKeyParam(CString &buffer)
{
	int k, t = buffer.Find(PARAM_TOKEN, 0);
	if ( t > 0 )
	{
		k = t + strlen(PARAM_TOKEN);
		m_DataType = 0;
		if ( 0<= buffer.Find(TEXT_TOKEN) )
		{
			k += strlen(TEXT_TOKEN);
			m_DataType = 1;
		}
		else if ( 0<= buffer.Find(BINARY_TOKEN) )
		{
			k += strlen(BINARY_TOKEN);
			m_DataType = 0;
		}
		if ( 0 <= buffer.Find(INV_TOKEN) )
		{
			m_Invert = TRUE;
			k += strlen(INV_TOKEN);
		}
		else
		{
			m_Invert = FALSE;
		}
		m_P1InSeq	= (int)(buffer[k] - '0');
		m_P1Perm	= (int)(buffer[k+2] - '0');
		m_P1OutSeq	= (int)(buffer[k+4] - '0');
		m_P2InSeq	= (int)(buffer[k+6] - '0');
		m_P2Perm	= (int)(buffer[k+8] - '0');
		m_P2OutSeq	= (int)(buffer[k+10] - '0');
	}
	return t;
}


void CDlgKeyPermutation::OnPasteKey() 
{
	CString buffer;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
	if(PasteKey(pc_str, buffer))
	{
		UpdateData(TRUE);
		int k = buffer.Find(';');
		if( k < 0 )
		{
			int t = readKeyParam( buffer );
			if ( t > 0 ) m_Perm1 = makeASCII(buffer.Left(t));
			else         m_Perm1 = makeASCII(buffer);
			m_Perm2.Empty();
		}
		else
		{
			m_Perm1 = makeASCII(buffer.Left(k));
			int t = readKeyParam( buffer );
			if ( t > 0 ) m_Perm2 = makeASCII(buffer.Mid(k+1,(t-k)-1));
			else		 m_Perm2 = makeASCII(buffer.Right(buffer.GetLength()-k-1));
		}
		UpdateData(FALSE);
		OnChangeEdit1();
		OnChangeEdit2();
	}
}

CString CDlgKeyPermutation::makeASCII(CString &line)
{
	int p, l;

	l = line.GetLength();
	if(l==0) return line;
	if(MyIsAlpha(line[0])) { // Alpha mode
		for(p = 0; p<l; p++) {
			if(!strchr("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", line[p])) {
				line.Delete(p);
				p--;
				l--;
			}
		}
	}
	else { // numerischer Modus
		for(p = 0; p<l; p++) {
			if(!strchr("0123456789,", line[p])) {
				line.Delete(p);
				p--;
				l--;
			}
		}
	}
	return line;
}

int CDlgKeyPermutation::MakePermInt(CString *Pin, int p[], int pinv[])
{
	int i, j, k, plen, m, r, e;
	char buffer[1024];

	i = plen = m = 0;
	do {
		do {
			j = Pin->Find(',',i+1);
			if(j!=i-1) break;
			i++;
		} while(1);
		if(j==-1)
			e = Pin->GetLength() - i;
		else
			e = j-i;
		if ( e > 6 ) k = MAX_PERM_LENGTH+1;
		else         k = atoi(Pin->Mid(i,e))-1;
		i = j+1;
		if(k>=MAX_PERM_LENGTH) { // Fehler: zu großer Wert
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_PERM ,pc_str,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_PERM_NUM_2_BIG,pc_str1,STR_LAENGE_STRING_TABLE);
			char tmpStr[1024];
			sprintf(tmpStr, pc_str1, MAX_PERM_LENGTH);
			MessageBox(tmpStr,pc_str,MB_ICONWARNING|MB_OK);
			return -1;
		}
		m = max(m,k);
		for(r=0;r<plen;r++) {
			if(k == p[r]) { // Fehler doppelter Wert
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_PERM ,pc_str,STR_LAENGE_STRING_TABLE);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_PERM_DUPLICATE,pc_str1,STR_LAENGE_STRING_TABLE);
				sprintf(buffer, pc_str1, k+1);
				MessageBox(buffer,pc_str,MB_ICONWARNING|MB_OK);
				return -1;
			}
		}
		p[plen] = k;
		pinv[k] = plen;
		plen++;
	} while (j>=0);

	for(i=0;i<plen;i++) {
		for(j=0;j<plen;j++) {
			if(p[j] == i) break;
		}
		if(j>=plen) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_PERM ,pc_str,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_PERM_MISSING,pc_str1,STR_LAENGE_STRING_TABLE);
			sprintf(buffer, pc_str1, i+1);
			MessageBox(buffer,pc_str,MB_ICONWARNING|MB_OK);
			return -1;
		}
	}

	return plen;
}

int CDlgKeyPermutation::ShowPermutations()
{
	CDlgKeyPermutationInfo KPI;

	CString Titel;
	char Field[4096];

	if(!m_Invert&&! m_Dec)
	{
		Titel.LoadString(IDS_PERMUTATION_ENCRYPT);
	}
	if( m_Invert&&! m_Dec)
	{
		Titel.LoadString(IDS_PERMUTATION_ENCRYPT_INV);
	}
	if(! m_Invert&& m_Dec)
	{
		Titel.LoadString(IDS_PERMUTATION_DECRYPT);
	}
	if( m_Invert&& m_Dec)
	{
		Titel.LoadString(IDS_PERMUTATION_DECRYPT_INV);
	}
	KPI.m_dialogue_title = Titel;

	Titel.Empty();
	if( m_Dec)
	{
		Titel.LoadString(IDS_PERMUTATION_CLEAR);
	}
	else
	{
		Titel.LoadString(IDS_PERMUTATION_CIPHER);
	}
	KPI.m_button_title = Titel;

	if( PrintPerm(Field,  m_P1,  m_P1len))
	{
		KPI.m_Permutation1 = Field;
	}
	if( PrintPerm(Field,  m_P1inv,  m_P1len))
	{
		KPI.m_Inverse1 = Field;
	}
	if( PrintPerm(Field,  m_P2,  m_P2len))
	{
		KPI.m_Permutation2 = Field;
	}
	if( PrintPerm(Field,  m_P2inv,  m_P2len))
	{
		KPI.m_Inverse2 = Field;
	}
	return KPI.DoModal();
}
