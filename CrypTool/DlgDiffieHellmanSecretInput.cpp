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

// DlgDiffieHellmanSecretInput.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanSecretInput.h"
#include ".\dlgdiffiehellmansecretinput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanSecretInput 


CDlgDiffieHellmanSecretInput::CDlgDiffieHellmanSecretInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanSecretInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanSecretInput)
	m_Secret = _T("");
	m_PartyHeader = _T("");
	//}}AFX_DATA_INIT
	m_SecretExceedsPrime = false;
}

CDlgDiffieHellmanSecretInput::CDlgDiffieHellmanSecretInput( std::string party, Big& prime, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanSecretInput::IDD, pParent)
{
	m_Party = party;
	m_Prime = prime;
	m_Secret = _T("");
	m_SecretExceedsPrime = false;
}

CDlgDiffieHellmanSecretInput::CDlgDiffieHellmanSecretInput( std::string party, std::string prev_secret,Big& prime, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanSecretInput::IDD, pParent)
{
	m_Party = party;
	m_Prime = prime;
	m_Secret = prev_secret.c_str();
	m_SecretExceedsPrime = false;
}

void CDlgDiffieHellmanSecretInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanSecretInput)
	DDX_Control(pDX, IDOK, m_CtrlOKButton);
	DDX_Control(pDX, IDC_GENERATE_SECRET, m_ButtonGenSec);
	DDX_Control(pDX, IDC_SECRET, m_SecretControl);
	DDX_Text(pDX, IDC_SECRET, m_Secret);
	DDX_Text(pDX, IDC_PARTY, m_PartyHeader);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanSecretInput, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanSecretInput)
	ON_BN_CLICKED(IDC_GENERATE_SECRET, OnGenerateSecret)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDiffieHellmanSecretInput 

void CDlgDiffieHellmanSecretInput::OnOK() 
{
	UpdateData(true);

	// Keine "leeren" Eingabefelder zulassen
	if(this->m_Secret.IsEmpty())
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_NO_USER_INPUT, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_SecretControl.SetFocus();
		return;
	}
	
	
	// Falls eine Formel erkannt wird, den Wert berechnen und den Formelausdruck
	// durch den entsprechenden Zahlenwert ersetzen
	CString formula = m_Secret;
	int err_ndx;
	if(EvalFormula( formula, err_ndx, true )) m_Secret = formula; 
	
	// Fehlermeldung ausgeben, wenn Geheimnis keine Dezimalzahl ist
	if(!IsDecimalNumber(m_Secret))
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_NON_DECIMAL_VALUE, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_SecretControl.SetFocus();
		return;
	}

	Big S = (char*)(LPCTSTR)this->m_Secret;
	
	// Fehlermeldung ausgeben, wenn das Geheimnis kleiner Null ist.
	if(/*S >= this->m_Prime ||*/ S < 0)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_SECRET_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_SecretControl.SetFocus();
		return;
	}

	if ( S >= this->m_Prime )
	{
		m_SecretExceedsPrime = true;
	}
	// Warnmeldung ausgeben, wenn das Geheimnis gleich p-1 ist oder 0, da das Verfahren dann
	// unsicher ist, weil der Sessionkey deshalb zu 1 wird
	if( S == (m_Prime-1) || S == 0 )
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_SECRET_DANGEROUS, pc_str, STR_LAENGE_STRING_TABLE);
		if( MessageBox(pc_str,"CrypTool", MB_ICONINFORMATION | MB_OKCANCEL) == IDCANCEL )
		{
			this->m_SecretControl.SetFocus();
			return;
		}
	}
	// auch eine Warnmeldung ausgeben, falls das Geheimnis gleich 1 ist, denn dann
	// kann der errechnete Sessionkey u.U. gleich dem ÖFFENTLICHEN Generator sein!
	else if( S == 1 )
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_SECRET_PREDICTABLE, pc_str, STR_LAENGE_STRING_TABLE);
		if( MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION | MB_OKCANCEL) == IDCANCEL )
		{
			this->m_SecretControl.SetFocus();
			return;
		}
		
	}

	UpdateData(false);

	CDialog::OnOK();
}

void CDlgDiffieHellmanSecretInput::OnGenerateSecret() 
{
	// "Das Geheimnis" (Big-Format)
	Big S;
	irand((unsigned)time(NULL));
	bigrand(this->m_Prime.getbig(), S.getbig());
	char *s = new char[512];
	s << S;
	this->m_Secret = s;
	delete s;
	UpdateData(false);
	m_CtrlOKButton.SetFocus();
}

BOOL CDlgDiffieHellmanSecretInput::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Temporäre Variablen
	CString temp1,temp2;

	// Name der DH-Partei dynamisch im Fenstertitel anzeigen
	temp1.LoadString(IDS_DH_SECRET_DIALOGUEHEADER);
	temp2.Format((LPCTSTR)temp1, (LPCTSTR)this->m_Party.c_str());
	this->SetWindowText((LPCTSTR)temp2);
	
	// Name der DH-Partei dynamisch im Dialog anzeigen
	temp1.LoadString(IDS_DH_SECRET_PARTYNAME);
	temp2.Format((LPCTSTR)temp1, (LPCTSTR)this->m_Party.c_str());
	this->m_PartyHeader = (LPCTSTR)temp2;

	// Initial den Focus auf das Eingabefeld für das Geheimnis legen
	this->m_SecretControl.SetFocus();

	UpdateData(false);

	return FALSE;	
	//return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgDiffieHellmanSecretInput::OnBnClickedOk()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	OnOK();
}
