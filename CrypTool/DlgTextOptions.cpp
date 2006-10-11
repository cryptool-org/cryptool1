/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

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
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// TextOptions.cpp: Implementierungsdatei
//



#include "stdafx.h"
#include "CrypToolApp.h"
#include "ChrTools.h"
#include "DialogeMessage.h"
#include "DlgTextOptions.h"
#include ".\dlgtextoptions.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgTextOptions 

CDlgTextOptions::CDlgTextOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTextOptions::IDD, pParent)
{
	LoadString(/*AfxGetInstanceHandle()*/ NULL,IDS_STRING_STANDARD_REF_TEXT,pc_str,STR_LAENGE_STRING_TABLE);
	char buffer[CRYPTOOL_PATH_LENGTH];
	int n = SearchPath(NULL, pc_str, NULL, CRYPTOOL_PATH_LENGTH - 1, buffer, NULL);
	//{{AFX_DATA_INIT(CDlgTextOptions)
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
	if(n>0) {
		m_StrRefFile=buffer;	
		int pos = m_StrRefFile.ReverseFind('\\');
		m_StrTitle= m_StrRefFile.Mid(pos+1);
	}
	else
		m_StrRefFile=_T("");

	//}}AFX_DATA_INIT

	m_ConvertCase = TRUE;
	m_IgnoreCase = 1;
}


void CDlgTextOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CDlgTextOptions)
	DDX_Control(pDX, IDC_TEXTOPTIONS_ALPHABET, m_InformationAlphabetSize);
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


BEGIN_MESSAGE_MAP(CDlgTextOptions, CDialog)

	//{{AFX_MSG_MAP(CDlgTextOptions)
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
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgTextOptions  

#define ALLOWED_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890-.,_:;+*!\"§$%&/()=?"


void CDlgTextOptions::OnUpdateEdit2() 
{
	UpdateData(TRUE);
	m_trenn.MakeUpper();
	if(m_trenn.IsEmpty()||m_trenn[0]<'A'||m_trenn[0]>'Z')
		m_trenn=_T("X");
	UpdateData(FALSE);
}



void CDlgTextOptions::OnUpdateEdit1() 
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
	UpdateHeaderAlphabet();
}


void CDlgTextOptions::OnButton1() 
{
	m_alphabet = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	m_Case = FALSE;
	m_ConvertCase = TRUE;
	m_Format = TRUE;
	m_trenn = "X";
	UpdateTags();
	UpdateHeaderAlphabet();
}


BOOL CDlgTextOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();

	OldAlphabet = m_alphabet;
	OldCase = m_Case;
	OldFormat = m_Format;
	UpdateTags();

	m_CtrlRefFile.SetFocus();
	m_CtrlRefFile.SetSel(0,-1);

	UpdateHeaderAlphabet();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CDlgTextOptions::OnCancel() 
{
	m_alphabet = OldAlphabet;
	m_Case = OldCase;
	m_Format = OldFormat;
	CDialog::OnCancel();
}


void CDlgTextOptions::OnCheck2() // Groß-Keinschreibubg beachten
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
	UpdateHeaderAlphabet();
}


void CDlgTextOptions::OnOK() 
{
	UpdateData(TRUE);  // Werte aus Eingabemaske lesen

	if(m_Case) m_IgnoreCase = 0;
	else m_IgnoreCase = 1;

	AppConv.SetAlphabet(m_alphabet.GetBuffer(257), m_IgnoreCase);
	CDialog::OnOK();
}


void CDlgTextOptions::OnCheck3() // Großbuchstaben
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
	UpdateHeaderAlphabet();
}


void CDlgTextOptions::OnCheck4() // Kleinbuchstaben
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
	UpdateHeaderAlphabet();
}


void CDlgTextOptions::OnCheck5() // Leerzeichen
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
	UpdateHeaderAlphabet();
}


void CDlgTextOptions::OnCheck6() // Satzzeichen
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
	UpdateHeaderAlphabet();
}


int CDlgTextOptions::UpdateTags()
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



void CDlgTextOptions::OnCheck7() // Zahlen

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
	UpdateHeaderAlphabet();
}



void CDlgTextOptions::OnCheck8() // Groß-Keinschreibubg konvertieren
{
	UpdateData(TRUE);  // Werte aus Eingabemaske lesen	

	if (m_ConvertCase && m_Case) { // unzulässig
		Message(IDS_TEXTOPTIONS_KEEP_UPPERCASE_LOWERCASE, MB_ICONSTOP);
		m_ConvertCase = FALSE;
		UpdateData(FALSE);
	}
	UpdateHeaderAlphabet();
}

void CDlgTextOptions::OnButtonTextoptionenSucheReferenzdatei() 
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
	GotoDlgCtrl( GetDlgItem(IDC_BUTTON_TEXTOPTIONEN_SUCHE_REFERENZDATEI));
}

void CDlgTextOptions::OnUpdateEditTextoptionenReferenzdatei() 
{
	// TODO: Wenn es sich hierbei um ein RICHEDIT-Steuerelement handelt, sendet es
	// sendet diese Benachrichtigung nur, wenn die Funktion CDialog::OnInitDialog()
	// überschrieben wird, um die EM_SETEVENTMASK-Nachricht an das Steuerelement
	// mit dem ENM_UPDATE-Attribut Ored in die Maske lParam zu senden.
	
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
}

void CDlgTextOptions::UpdateHeaderAlphabet()
{
	LoadString(AfxGetInstanceHandle(),IDS_TEXTOPTIONS_HEADER_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
	char line[256];
	sprintf(line, pc_str, m_alphabet.GetLength());
	m_InformationAlphabetSize.SetWindowText(line);
}

void CDlgTextOptions::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
