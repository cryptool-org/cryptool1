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

// DlgMonSubst.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "DlgMonSubst.h"
#include "KeyRepository.h"
#include ".\dlgmonsubst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgMonSubst 


CDlgMonSubst::CDlgMonSubst(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMonSubst::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMonSubst)
	//}}AFX_DATA_INIT
}

CDlgMonSubst::~CDlgMonSubst()
{
	m_font.DeleteObject();
}


void CDlgMonSubst::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMonSubst)
	DDX_Control(pDX, IDC_TO, m_CtrlTo);
	DDX_Control(pDX, IDC_FROM, m_CtrlFrom);
	DDX_Control(pDX, IDC_KEY, m_CtrlKey);
	DDX_Text(pDX, IDC_TO, m_stringTo);
	DDX_Text(pDX, IDC_FROM, m_stringFrom);
	DDX_Text(pDX, IDC_KEY, m_stringKey);
	DDX_Radio(pDX, IDC_RADIO1, m_RadioChooseKeyVariant);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMonSubst, CDialog)
	//{{AFX_MSG_MAP(CDlgMonSubst)
	ON_EN_CHANGE(IDC_KEY, ComputeSubstKeyMapping)
	ON_BN_CLICKED(IDC_PASTE_KEY, OnPasteKey)
	ON_BN_CLICKED(ID_ENCRYPT, OnEncrypt)
	ON_BN_CLICKED(ID_DECRYPT, OnDecrypt)	
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadioSubstFillAscendingOrder)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadioSubstFillDescendingOrder)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadioAddBash)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_TEXTOPTIONS, &CDlgMonSubst::OnBnClickedButtonTextoptions)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgMonSubst 

BOOL CDlgMonSubst::OnInitDialog() 
{
	CDialog::OnInitDialog();

// Paste Button
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
	typeOfEncryption = pc_str;
	VERIFY(m_Paste.AutoLoad(IDC_PASTE_KEY,this));

	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);

	VERIFY(m_font.CreatePointFont(100,"Courier New"));
	m_CtrlFrom.SetFont(&m_font);
	m_CtrlTo.SetFont(&m_font);
	m_CtrlKey.SetFont(&m_font);
	m_CtrlFrom.SetWindowText("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	m_CtrlTo.SetWindowText  ("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	m_CtrlKey.SetWindowText ("");

	// update the alphabet heading (in particular the size of the alphabet)
	int alphabetSize = theApp.TextOptions.getAlphabet().GetLength();
	CString alphabetHeading;
	alphabetHeading.Format(IDS_STRING_MONOALPHABETIC_SUBSTITUTION_ALPHABET_HEADING, alphabetSize);
	CWnd *window = GetDlgItem(IDC_ALPHABET_HEADING);
	if(window) window->SetWindowText(alphabetHeading);

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgMonSubst::ComputeSubstKeyMapping()
{
	UpdateData(true);

	// alright, we have three different variants from here on:
	//  (A) variable key, ascending padding, dependent on text options
	//  (B) variable key, descending padding, dependent on text options
	//  (C) fixed key (atbash)

	// some init stuff (get the key, get the alphabet)
	CString key = m_stringKey;
	CString newKey;
	CString alphabet = theApp.TextOptions.getAlphabet();
	CString mappedKey;

	// variants (A) and (B) are similar in that they both work with a variable alphabet
	if(m_RadioChooseKeyVariant == 0 || m_RadioChooseKeyVariant == 1) {

		// first, remove all characters from the key that are not part of the alphabet;
		// however, check if the upper/lower case equivalent is part of the key (see 
		// implementation in DlgRot13Caesar.cpp, the idea there is somewhat similar)
		for(int i=0; i<key.GetLength(); i++) {
			if(alphabet.Find(key[i]) == -1) {
				CString tempKey = key;
				char keyUpper = tempKey.MakeUpper()[i];
				char keyLower = tempKey.MakeLower()[i];
				// is only the upper case equivalent part of the alphabet?
				if(alphabet.Find(keyUpper) != -1 && newKey.Find(keyUpper) == -1)
					newKey.AppendChar(keyUpper);
				// is only the lower case equivalent part of the alphabet?
				if(alphabet.Find(keyLower) != -1 && newKey.Find(keyLower) == -1)
					newKey.AppendChar(keyLower);
			}
			else {
				if(newKey.Find(key[i]) == -1)
					newKey.AppendChar(key[i]);
			}
		}

		// now create the key mapping
		// (first the actual key, then the remaining characters in a specific order)
		mappedKey = newKey;
		// ASCENDING order
		if(m_RadioChooseKeyVariant == 0) {
			for(int i=0; i<alphabet.GetLength(); i++) {
				if(mappedKey.Find(alphabet[i]) == -1)
					mappedKey.AppendChar(alphabet[i]);
			}
		}
		// DESCENDING order
		if(m_RadioChooseKeyVariant == 1) {
			for(int i=alphabet.GetLength()-1; i>=0; i--) {
				if(mappedKey.Find(alphabet[i]) == -1)
					mappedKey.AppendChar(alphabet[i]);
			}
		}
		// user may change the key here
		m_CtrlKey.SetReadOnly(0);
	}

	// variant (C) uses a fixed key
	else {
		for (char ch='Z'; ch>='A'; ch--) {
			newKey.AppendChar(ch);
		}
		mappedKey = newKey;
		// user may NOT change the key here
		m_CtrlKey.SetReadOnly(1);	
	}

	// at this point we should have it already...
	m_stringFrom = alphabet;
	m_stringTo = mappedKey;
	m_stringKey = newKey;
	
	UpdateData(false);

	// set the cursor to the end of the input (the actual key)
	m_CtrlKey.SetSel(m_stringKey.GetLength(), m_stringKey.GetLength());
}


void CDlgMonSubst::OnPasteKey() 
{
	CString keyToBePasted;
	if ( CheckPasteKeyVariant(IDS_CRYPT_SUBSTITUTION, keyToBePasted) || CheckPasteKeyVariant(IDS_CRYPT_ATBASH, keyToBePasted) )
		m_CtrlKey.SetWindowText(keyToBePasted);

	// flomar, 01/22/2010
	// when updating the key (see SetWindowText above), invalid characters are automatically 
	// removed; if that happens, we want to notify the user that the pasted key wasn't fully copied
	UpdateData(false);
	if(this->m_stringKey != keyToBePasted) {
		CString message;
		message.LoadString(IDS_STRING_MONOALPHABETIC_SUBSTITUTION_CHARACTERS_REMOVED_DURING_COPYANDPASTE);
		MessageBox(message, "CrypTool", MB_ICONINFORMATION);
		return;
	}
}

void CDlgMonSubst::OnEncrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_cryptDirection = 1;
	OnOK();
}

void CDlgMonSubst::OnDecrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_cryptDirection = 0;
	OnOK();
}

int CDlgMonSubst::CheckPasteKeyVariant(int SID, CString &keyStr)
{
	LoadString(AfxGetInstanceHandle(),SID,pc_str,STR_LAENGE_STRING_TABLE);
	if ( PasteKey(pc_str,keyStr) )
		return 1;
	return 0;
}

void CDlgMonSubst::OnBnClickedRadioSubstFillAscendingOrder()
{
	UpdateData(true);

	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
	typeOfEncryption = pc_str;

	CString tmpStr;
	if ( CheckPasteKeyVariant(IDS_CRYPT_SUBSTITUTION, tmpStr) || CheckPasteKeyVariant(IDS_CRYPT_ATBASH, tmpStr) )
		m_Paste.EnableWindow(TRUE);
	else
		m_Paste.EnableWindow(FALSE);

	m_CtrlKey.SetReadOnly(0);
	ComputeSubstKeyMapping();
}

void CDlgMonSubst::OnBnClickedRadioSubstFillDescendingOrder()
{
	UpdateData(true);

	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
	typeOfEncryption = pc_str;

	CString tmpStr;
	if ( CheckPasteKeyVariant(IDS_CRYPT_SUBSTITUTION, tmpStr) || CheckPasteKeyVariant(IDS_CRYPT_ATBASH, tmpStr) )
		m_Paste.EnableWindow(TRUE);
	else
		m_Paste.EnableWindow(FALSE);

	m_CtrlKey.SetReadOnly(0);
	ComputeSubstKeyMapping();
}


void CDlgMonSubst::OnBnClickedRadioAddBash()
{
	UpdateData(true);

	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_ATBASH,pc_str,STR_LAENGE_STRING_TABLE);
	typeOfEncryption = pc_str;
	m_Paste.EnableWindow(FALSE); // Note: PasteKey makes here no sense 

	// we're using a fixed alphabet and a fixed key
	CString alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	// assign the fixed values
	m_stringFrom = alphabet;
	m_stringTo = alphabet.MakeReverse();
	m_stringKey = m_stringTo;

	m_CtrlKey.SetReadOnly(1);

	UpdateData(false);
}


void CDlgMonSubst::OnBnClickedButtonTextoptions()
{
	UpdateData(true);

	CString oldAlphabet;

	// save the old alphabet for usage later on
	oldAlphabet = theApp.TextOptions.getAlphabet();

	// return if the user cancels the text options dialog
	if(theApp.TextOptions.DoModal() != IDOK)
		return;

	// get the new alphabet
	CString alphabet = theApp.TextOptions.getAlphabet();

	// now, in case the alphabet didn't change we can return right away
	if(oldAlphabet == alphabet)
		return;

	// update the alphabet heading (in particular the size of the alphabet)
	int alphabetSize = alphabet.GetLength();
	CString alphabetHeading;
	alphabetHeading.Format(IDS_STRING_MONOALPHABETIC_SUBSTITUTION_ALPHABET_HEADING, alphabetSize);
	CWnd *window = GetDlgItem(IDC_ALPHABET_HEADING);
	if(window) window->SetWindowText(alphabetHeading);

	// compute the new key mapping
	ComputeSubstKeyMapping();

	UpdateData(false);
}
