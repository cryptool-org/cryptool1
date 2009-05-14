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
	f_FillAscendingOrder = TRUE;
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
	DDX_Control(pDX, IDC_RADIO1, m_RadioChooseKeyVariant);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMonSubst, CDialog)
	//{{AFX_MSG_MAP(CDlgMonSubst)
	ON_EN_CHANGE(IDC_KEY, OnChangeKey)
	ON_BN_CLICKED(IDC_PASTE_KEY, OnPasteKey)
	ON_BN_CLICKED(ID_ENCRYPT, OnEncrypt)
	ON_BN_CLICKED(ID_DECRYPT, OnDecrypt)	
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadioSubstFillAscendingOrder)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadioAddBash)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadioSubstFillDescendingOrder)
	//}}AFX_MSG_MAP
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

	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1); UpdateData();
	OnBnClickedRadioSubstFillAscendingOrder();

	VERIFY(m_font.CreatePointFont(100,"Courier New"));
	m_CtrlFrom.SetFont(&m_font);
	m_CtrlTo.SetFont(&m_font);
	m_CtrlKey.SetFont(&m_font);
	m_CtrlFrom.SetWindowText("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	m_CtrlTo.SetWindowText  ("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	m_CtrlKey.SetWindowText ("");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CDlgMonSubst::OnChangeKey() 
{
	static int BUSY = 0;  // FIXME
	if (BUSY) return;
	BUSY++;
	CString s_Key;
	int cStart, cEnd;
	m_CtrlKey.GetSel(cStart, cEnd);
	m_CtrlKey.GetWindowText(s_Key);
	s_Key.MakeUpper();
	for (int i=0 ;i<s_Key.GetLength(); i++)
		if ( (s_Key[i]<'A') || (s_Key[i]>'Z') )
		{
			if (i<cStart) cStart--;
			if (i<cEnd)   cEnd--;
			s_Key.Delete(i--);
		}
	m_CtrlKey.SetWindowText(s_Key); // FIXME: Without the BUSY-Flag SetWindowText MAY call recursively OnChangeKey (as obtained by B.E.)
	m_CtrlKey.SetSel(cStart, cEnd);

	ComputeSubstKeyMapping();
	BUSY--;
}

void CDlgMonSubst::ComputeSubstKeyMapping()
{

/*  Herleitung des (eigentlichen) Schlüssels aus dem eingegebenen Schlüsselwort:
	Doppelte Buchstaben im Schlüsselwort werden nicht berücksichtigt.
	Ansonsten wird das a auf den ersten Buchstaben des Schlüsselwortes abgebildet,
	das b auf den zweiten,...
	Danach werden alle Buchstaben, die nicht im Schlüsselwort vorkommen in
	umgekehrter Reihenfolge den restlichen Buchstaben des Alphabetes zugeordnet.	*/

//	char key[26+1];
	key[26] = '\0';

	bool schonda[26];//Ist der i-te Buchstabe bereits im Schlüsselwort aufgetreten??

	int i;
	for (i=0; i<=25; i++){
		key[i]=' ';
		schonda[i]=FALSE;}
	
	CString s_Key;
	m_CtrlKey.GetWindowText(s_Key);

	int lang=s_Key.GetLength();
	int Nummer=0;
	for (int j=0; j<=(lang-1); j++){
		if ((s_Key[j]>='A')&&(s_Key[j]<='Z')){
			if (schonda[s_Key[j]-65]==FALSE){
				key[Nummer]=s_Key[j];
				Nummer++;
				schonda[s_Key[j]-65]=TRUE;
			}
		}
	}
	
	//Die verbleibenden Schlüsselbuchstaben vergeben
	if (f_FillAscendingOrder)
	{
		for (i=0; i<=25; i++) 
			if (schonda[i]==FALSE) key[Nummer++]=i+65;
	}
	else
	{
		for (i=25; i>=0; i--) 
			if (schonda[i]==FALSE) key[Nummer++]=i+65;
	}
	m_CtrlTo.SetWindowText(key);

}


void CDlgMonSubst::OnPasteKey() 
{
	CString m_text;
	if ( CheckPasteKeyVariant(IDS_CRYPT_SUBSTITUTION, m_text) || CheckPasteKeyVariant(IDS_CRYPT_ATBASH, m_text) )
		m_CtrlKey.SetWindowText(m_text);
}

void CDlgMonSubst::OnEncrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_cryptDirection = 1;
	m_CtrlTo.GetWindowText(key, 27); key[26] = 0;
	OnOK();
}

void CDlgMonSubst::OnDecrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_cryptDirection = 0;
	m_CtrlTo.GetWindowText(key, 27); key[26] = 0;
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
	// TODO: Add your control notification handler code here
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
	typeOfEncryption = pc_str;

	CString tmpStr;
	if ( CheckPasteKeyVariant(IDS_CRYPT_SUBSTITUTION, tmpStr) || CheckPasteKeyVariant(IDS_CRYPT_ATBASH, tmpStr) )
		m_Paste.EnableWindow(TRUE);
	else
		m_Paste.EnableWindow(FALSE);
	f_FillAscendingOrder = TRUE;
	m_CtrlKey.SetReadOnly(0);
	ComputeSubstKeyMapping();
}

void CDlgMonSubst::OnBnClickedRadioSubstFillDescendingOrder()
{
	// TODO: Add your control notification handler code here
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
	typeOfEncryption = pc_str;

	CString tmpStr;
	if ( CheckPasteKeyVariant(IDS_CRYPT_SUBSTITUTION, tmpStr) || CheckPasteKeyVariant(IDS_CRYPT_ATBASH, tmpStr) )
		m_Paste.EnableWindow(TRUE);
	else
		m_Paste.EnableWindow(FALSE);

	f_FillAscendingOrder = FALSE;
	m_CtrlKey.SetReadOnly(0);
	ComputeSubstKeyMapping();
}


void CDlgMonSubst::OnBnClickedRadioAddBash()
{
	// TODO: Add your control notification handler code here
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_ATBASH,pc_str,STR_LAENGE_STRING_TABLE);
	typeOfEncryption = pc_str;
	m_Paste.EnableWindow(FALSE); // Note: PasteKey makes here no sense 

	CString tmpStr = "";
	for (char ch='Z'; ch>='A'; ch--)
		tmpStr += ch;
	m_CtrlKey.SetWindowText(tmpStr);
	m_CtrlKey.SetReadOnly();
}

