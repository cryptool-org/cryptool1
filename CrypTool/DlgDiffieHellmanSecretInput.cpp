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
