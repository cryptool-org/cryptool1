//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// TextOptions.cpp: Implementierungsdatei
//



#include "stdafx.h"
#include "multipad.h"
#include "ChrTools.h"
#include "TextOptions.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CTextOptions 

CTextOptions::CTextOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CTextOptions::IDD, pParent)
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_STANDARD_REF_TEXT,pc_str,STR_LAENGE_STRING_TABLE);

	//{{AFX_DATA_INIT(CTextOptions)
	m_Format = TRUE;
	m_alphabet = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	m_Case = FALSE;
	m_LeerVal = FALSE;
	m_GrossVal = FALSE;
	m_KleinVal = FALSE;
	m_SatzVal = FALSE;
	m_ZahlVal = FALSE;
	m_ConvertCase = FALSE;
	m_trenn = _T("X");
	m_addx = TRUE;
	m_StrRefFile=pc_str;
	//}}AFX_DATA_INIT

	m_ConvertCase = TRUE;
	m_IgnoreCase = 1;
}





void CTextOptions::DoDataExchange(CDataExchange* pDX)

{

	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CTextOptions)
	DDX_Control(pDX, IDC_EDIT_TEXTOPTIONEN_REFERENZDATEI, m_CtrlRefFile);
	DDX_Control(pDX, IDC_CHECK2, m_CaseControl);
	DDX_Control(pDX, IDC_EDIT1, m_alphacontrol);
	DDX_Check(pDX, IDC_CHECK1, m_Format);
	DDX_Text(pDX, IDC_EDIT1, m_alphabet);
	DDX_Check(pDX, IDC_CHECK2, m_Case);
	DDX_Check(pDX, IDC_CHECK5, m_LeerVal);
	DDX_Check(pDX, IDC_CHECK3, m_GrossVal);
	DDX_Check(pDX, IDC_CHECK4, m_KleinVal);
	DDX_Check(pDX, IDC_CHECK6, m_SatzVal);
	DDX_Check(pDX, IDC_CHECK7, m_ZahlVal);
	DDX_Check(pDX, IDC_CHECK8, m_ConvertCase);
	DDX_Text(pDX, IDC_EDIT2, m_trenn);
	DDV_MaxChars(pDX, m_trenn, 1);
	DDX_Check(pDX, IDC_CHECK9, m_addx);
	DDX_Text(pDX, IDC_EDIT_TEXTOPTIONEN_REFERENZDATEI, m_StrRefFile);
	//}}AFX_DATA_MAP

}





BEGIN_MESSAGE_MAP(CTextOptions, CDialog)

	//{{AFX_MSG_MAP(CTextOptions)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnUpdateEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_BUTTON_TEXTOPTIONEN_SUCHE_REFERENZDATEI, OnButtonTextoptionenSucheReferenzdatei)
	ON_EN_UPDATE(IDC_EDIT_TEXTOPTIONEN_REFERENZDATEI, OnUpdateEditTextoptionenReferenzdatei)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CTextOptions  

#define ALLOWED_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890-.,_:;+*!\"§$%&/()=?"


void CTextOptions::OnUpdateEdit2() 
{
	UpdateData(TRUE);
	m_trenn.MakeUpper();
	if(m_trenn.IsEmpty()||m_trenn[0]<'A'||m_trenn[0]>'Z')
		m_trenn=_T("X");
	UpdateData(FALSE);
}



void CTextOptions::OnUpdateEdit1() 
{
	int i, SS, SE;
	unsigned char c, set[256];
	CString Old;

	m_alphacontrol.GetSel(SS, SE);
	Old = m_alphabet;

	UpdateData(TRUE);  // Werte aus Eingabemaske lesen

	if(!m_Case) {
		for(i=0;i<m_alphabet.GetLength();i++) {
			if(MyIsLower(m_alphabet[i])) {
				m_Case=TRUE;
				m_ConvertCase = FALSE;
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SWITCH_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
				theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONINFORMATION);
				break;
			}
		}
	}

	memset(set,0,sizeof(set));
	for(i=0;i<m_alphabet.GetLength();i++) {
		c = m_alphabet[i];
		if(set[c]) {
			m_alphabet = Old;
			m_alphacontrol.SetSel(SS, SE);
			MessageBeep(MB_ICONEXCLAMATION);
			break;
		}
		set[c]=1;
	}
	if(m_alphabet.GetLength() != m_alphabet.SpanIncluding(ALLOWED_CHARS).GetLength()) {
			m_alphabet = Old;
			m_alphacontrol.SetSel(SS, SE);
			MessageBeep(MB_ICONEXCLAMATION);
	}
	m_alphacontrol.GetSel(SS, SE);
	UpdateTags();
	m_alphacontrol.SetSel(SS, SE);
}



void CTextOptions::OnButton1() 
{
	m_alphabet = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	m_Case = FALSE;
	m_ConvertCase = TRUE;
	m_Format = TRUE;
	UpdateTags();
}





BOOL CTextOptions::OnInitDialog() 

{

	CDialog::OnInitDialog();

	OldAlphabet = m_alphabet;
	OldCase = m_Case;
	OldFormat = m_Format;
	UpdateTags();

	m_CtrlRefFile.SetFocus();
	m_CtrlRefFile.SetSel(0,-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}



void CTextOptions::OnCancel() 
{
	m_alphabet = OldAlphabet;
	m_Case = OldCase;
	m_Format = OldFormat;

	CDialog::OnCancel();
}



void CTextOptions::OnCheck2() // Groß-Keinschreibubg beachten
{
	int i, r;


	UpdateData(TRUE);  // Werte aus Eingabemaske lesen	

	if(!m_Case) { // ignore Case
		m_alphabet.MakeUpper();
		for(i=0;i<m_alphabet.GetLength();i++) {
			r = m_alphabet.ReverseFind(m_alphabet[i]);
			if(r>i) m_alphabet = m_alphabet.Left(r) + m_alphabet.Right(m_alphabet.GetLength() - r - 1);
		}
	}
	else { //setzen auf case sensitiv
		m_ConvertCase = FALSE;
	}
	UpdateTags();
}



void CTextOptions::OnOK() 
{
	UpdateData(TRUE);  // Werte aus Eingabemaske lesen

	if(m_Case) m_IgnoreCase = 0;
	else m_IgnoreCase = 1;

	AppConv.SetAlphabet(m_alphabet.GetBuffer(257), m_IgnoreCase);
	CDialog::OnOK();
}



void CTextOptions::OnCheck3() // Großbuchstaben
{
	char c;
	int i;

	if(m_GrossVal != 1) { // falls nicht gesetzt, alle hinzufügen
		for(c='A';c<='Z';c++) {
			if(-1 == m_alphabet.Find(c))
				m_alphabet += c; // ein Zeichen nicht gefunden
		}
		m_GrossVal = 1;
	}
	else { // Zeichen Löschen
		for(c='A';c<='Z';c++) {
			if(-1 != (i=m_alphabet.Find(c)))
				m_alphabet = m_alphabet.Left(i) + m_alphabet.Right(m_alphabet.GetLength() - i - 1); // ein Zeichen gefunden
		}
		m_GrossVal = 0;
	}
	UpdateData(FALSE);
}



void CTextOptions::OnCheck4() // Kleinbuchstaben
{
	char c;
	int i;

	if(1 != m_KleinVal) { // falls nicht gesetzt, alle hinzufügen
		for(c='a';c<='z';c++) {
			if(-1 == m_alphabet.Find(c))
				m_alphabet += c; // ein Zeichen nicht gefunden
		}
		m_Case = TRUE;
		m_ConvertCase = FALSE;
		m_KleinVal = 1;
	}
	else { // Zeichen Löschen
		for(c='a';c<='z';c++) {
			if(-1 != (i=m_alphabet.Find(c)))
				m_alphabet = m_alphabet.Left(i) + m_alphabet.Right(m_alphabet.GetLength() - i - 1); // ein Zeichen gefunden
		}
		m_KleinVal = 0;
	}
	UpdateData(FALSE);
}



void CTextOptions::OnCheck5() // Leerzeichen

{
	int i;

	if(m_LeerVal == FALSE) { // falls nicht gesetzt, hinzufügen
		if(-1 == m_alphabet.Find(' '))
			m_alphabet += ' '; // ein Zeichen nicht gefunden
		m_LeerVal = TRUE;
	}
	else { // Zeichen Löschen
		if(-1 != (i=m_alphabet.Find(' ')))
			m_alphabet = m_alphabet.Left(i) + m_alphabet.Right(m_alphabet.GetLength() - i - 1); // ein Zeichen gefunden
		m_LeerVal = FALSE;
	}
	UpdateData(FALSE);
}



void CTextOptions::OnCheck6() // Satzzeichen
{
	char *s;
	int i;

	if(m_SatzVal != 1) { // falls nicht gesetzt, ale hinzufügen
		for(s=".,:;!?()" ;*s;s++) {
			if(-1 == m_alphabet.Find(*s))
				m_alphabet += *s; // ein Zeichen nicht gefunden
		}
		m_SatzVal = 1;
	}
	else { // Zeichen Löschen
		for(s=".,:;!?()" ;*s;s++) {
			if(-1 != (i=m_alphabet.Find(*s)))
				m_alphabet = m_alphabet.Left(i) + m_alphabet.Right(m_alphabet.GetLength() - i - 1); // ein Zeichen gefunden
		}
		m_SatzVal = 0;
	}
	UpdateData(FALSE);
}



int CTextOptions::UpdateTags()
{
	char c, *s;
	int OK;

	// Update Großbuchstaben 
	OK = 0;
	for(c='A';c<='Z';c++) {
		if(-1 == m_alphabet.Find(c))
			OK |= 1; // ein Zeichen nicht gefunden
		else
			OK |= 2; // ein Zeichen gefunden
	}
	switch(OK) {
	case(1): m_GrossVal = 0; // keine Zeichen gefunden
		break;
	case(2): m_GrossVal = 1; // alle Zeichen gefunden
		break;
	case(3): m_GrossVal = 2; // gemischt
	}


	// Update Leerzeichen 
	if(-1 == m_alphabet.Find(' '))
			m_LeerVal = FALSE; // Zeichen nicht gefunden
		else
			m_LeerVal = TRUE; // Zeichen gefunden


	// Update Kleinbuchstaben 

	OK = 0;

	for(c='a';c<='z';c++) {

		if(-1 == m_alphabet.Find(c))
			OK |= 1; // ein Zeichen nicht gefunden
		else
			OK |= 2; // ein Zeichen gefunden
	}
	switch(OK) {
	case(1): m_KleinVal = 0; // keine Zeichen gefunden
		break;
	case(2): m_KleinVal = 1; // alle Zeichen gefunden
		break;
	case(3): m_KleinVal = 2; // gemischt
	}


	// Update Satzzeichen 
	OK = 0;
	for(s=".,:;!?()" ;*s;s++) {
		if(-1 == m_alphabet.Find(*s))
			OK |= 1; // ein Zeichen nicht gefunden
		else
			OK |= 2; // ein Zeichen gefunden

	}
	switch(OK) {
	case(1): m_SatzVal = 0; // keine Zeichen gefunden
		break;
	case(2): m_SatzVal = 1; // alle Zeichen gefunden
		break;
	case(3): m_SatzVal = 2; // gemischt
	}


	// Update Zahlen 
	OK = 0;
	for(c='0';c<='9'; c++) {
		if(-1 == m_alphabet.Find(c))
			OK |= 1; // ein Zeichen nicht gefunden
		else
			OK |= 2; // ein Zeichen gefunden
	}

	switch(OK) {
	case(1): m_ZahlVal = 0; // keine Zeichen gefunden
		break;
	case(2): m_ZahlVal = 1; // alle Zeichen gefunden
		break;
	case(3): m_ZahlVal = 2; // gemischt
	}

	UpdateData(FALSE);
	return 0;
}



void CTextOptions::OnCheck7() // Zahlen

{
	char c;
	int i;

	if(m_ZahlVal != 1) { // falls nicht gesetzt, alle hinzufügen
		for(c='0';c<='9';c++) {
			if(-1 == m_alphabet.Find(c))
				m_alphabet += c; // ein Zeichen nicht gefunden
		}
		m_ZahlVal = 1;
	}
	else { // Zeichen Löschen
		for(c='0';c<='9';c++) {
			if(-1 != (i=m_alphabet.Find(c)))
				m_alphabet = m_alphabet.Left(i) + m_alphabet.Right(m_alphabet.GetLength() - i - 1); // ein Zeichen gefunden
		}
		m_ZahlVal = 0;
	}
	UpdateData(FALSE);
}



void CTextOptions::OnCheck8() // Groß-Keinschreibubg konvertieren
{
	UpdateData(TRUE);  // Werte aus Eingabemaske lesen	

	if (m_ConvertCase && m_Case) { // unzulässig
		MessageBeep(MB_ICONHAND);
		m_ConvertCase = FALSE;
		UpdateData(FALSE);
	}
}

void CTextOptions::OnButtonTextoptionenSucheReferenzdatei() 
{
	OPENFILENAME ofn;
	char fname[257], ftitle[128];
	const char* s_FileFilter = "text files (*.txt)\0*.txt\0all files\0*.*;*\0\0";

	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_CHOOSE_REF_FILENAME,pc_str,STR_LAENGE_STRING_TABLE);
	ofn.lpstrTitle = pc_str;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	ofn.lpstrFile = fname;
	sprintf(fname, "*.txt");
	ofn.nMaxFile = sizeof(fname)-1;
	ofn.lpstrFileTitle = ftitle;
	ofn.lpstrFilter = s_FileFilter;
	ftitle[0] = 0;
	ofn.nMaxFileTitle = sizeof(ftitle)-1;
	if(!GetOpenFileName(&ofn)) return;
	if(fname[0]==0) return;
	
	UpdateData(TRUE);
	m_StrRefFile=fname;
	m_StrTitle = ofn.lpstrFileTitle;
	UpdateData(FALSE);
	m_CtrlRefFile.SetFocus();
	m_CtrlRefFile.SetSel(0,-1);
	
}

void CTextOptions::OnUpdateEditTextoptionenReferenzdatei() 
{
	// TODO: Wenn es sich hierbei um ein RICHEDIT-Steuerelement handelt, sendet es
	// sendet diese Benachrichtigung nur, wenn die Funktion CDialog::OnInitDialog()
	// überschrieben wird, um die EM_SETEVENTMASK-Nachricht an das Steuerelement
	// mit dem ENM_UPDATE-Attribut Ored in die Maske lParam zu senden.
	
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
}
