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


// DlgKeyTutorial.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgDemoRSAKeyGeneration.h"
#include "DlgPrimesGeneratorDemo.h"
#include "KeyRepository.h"
#include "IntegerArithmetic.h"
#include "DialogeMessage.h"
#include "DlgKeyAsymGeneration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDemoRSAKeyGeneration 


CDlgDemoRSAKeyGeneration::CDlgDemoRSAKeyGeneration(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDemoRSAKeyGeneration::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDemoRSAKeyGeneration)
	m_sPrime_p = _T("");
	m_sPrime_q = _T("");
	m_sKeyPublic = _T("2^16+1");
	m_sKeyPrivate = _T("");
	m_sModN = _T("");
	m_sPhiN = _T("");
	m_sCheckPrime = _T("");
	m_sCheckPublic = _T("");
	m_sBitLength = _T("");
	//}}AFX_DATA_INIT
}


void CDlgDemoRSAKeyGeneration::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDemoRSAKeyGeneration)
	DDX_Control(pDX, IDC_EDIT_RSA_BITLENGTH, m_BitLengthCtrl);
	DDX_Control(pDX, IDC_CHECK_PRIME, m_CheckPrimeCtrl);
	DDX_Control(pDX, IDC_CHECK_PUBLIC, m_CheckPublicCtrl);
	DDX_Control(pDX, IDC_EDIT_RSA_KEY_PUBLIC, m_KeyPublicCtrl);
	DDX_Control(pDX, IDOK, m_ButtonOKCtrl);
	DDX_Text(pDX, IDC_EDIT_PRIME_P, m_sPrime_p);
	DDX_Text(pDX, IDC_EDIT_PRIME_Q, m_sPrime_q);
	DDX_Text(pDX, IDC_EDIT_RSA_KEY_PUBLIC, m_sKeyPublic);
	DDX_Text(pDX, IDC_EDIT_RSA_KEY_PRIVATE, m_sKeyPrivate);
	DDX_Text(pDX, IDC_EDIT_RSA_MODUL_N, m_sModN);
	DDX_Text(pDX, IDC_EDIT_RSA_PHI_N, m_sPhiN);
	DDX_Text(pDX, IDC_CHECK_PRIME, m_sCheckPrime);
	DDX_Text(pDX, IDC_CHECK_PUBLIC, m_sCheckPublic);
	DDX_Text(pDX, IDC_EDIT_RSA_BITLENGTH, m_sBitLength);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDemoRSAKeyGeneration, CDialog)
	//{{AFX_MSG_MAP(CDlgDemoRSAKeyGeneration)
	ON_BN_CLICKED(IDC_GENERATE_PRIME, OnGeneratePrime)
	ON_EN_UPDATE(IDC_EDIT_RSA_KEY_PUBLIC, OnUpdateParameter)
	ON_BN_CLICKED(IDOK, OnOK)
	ON_EN_UPDATE(IDC_EDIT_PRIME_P, OnUpdateParameter)
	ON_EN_UPDATE(IDC_EDIT_PRIME_Q, OnUpdateParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDemoRSAKeyGeneration 

BOOL CDlgDemoRSAKeyGeneration::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ASSERT(m_Cert); // Zertifikat muß initialisiert sein -> InitRSA

	UpdateData(TRUE);	
	
	if(m_Cert->IsInitialized())
	{
		// Schlüsseldaten holen:
		m_Cert->GetParameter(m_sModN, m_sPhiN, m_sKeyPublic, m_sKeyPrivate); 
		m_Cert->GetPublicString( m_sKeyPublic );
		m_Cert->GetPrimes(m_sPrime_p, m_sPrime_q); // Primzahlen holen
		m_ButtonOKCtrl.EnableWindow(FALSE);
		m_sPrime_p_OLD = m_sPrime_p;
		m_sPrime_q_OLD = m_sPrime_q;
		m_sKeyPublic_OLD = m_sKeyPublic;
	}

	UpdateData(FALSE);

	OnUpdateParameter(); // Schlüssel und Anzeige initialisieren
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgDemoRSAKeyGeneration::OnGeneratePrime() 
{
	CDlgPrimesGeneratorDemo* PrimeDialog;
	PrimeDialog = new CDlgPrimesGeneratorDemo(this);

	PrimeDialog->m_edit1 = "2^150";
	//PrimeDialog->m_edit3 = "2^150";
	PrimeDialog->m_edit2 = "2^151";
	//PrimeDialog->m_edit4 = "2^151";
	PrimeDialog->m_radio4 = 1;

	if(PrimeDialog->DoModal()==IDOK) // Primzahl Generierung
	{
		UpdateData(TRUE);
		m_sPrime_p = PrimeDialog->m_edit5;
		m_sPrime_q = PrimeDialog->m_edit6;
		UpdateData(FALSE);
	}

	delete PrimeDialog;

    OnUpdateParameter();	
}

void CDlgDemoRSAKeyGeneration::InitRSA(CPSEDemo* Cert)
{
	m_Cert = Cert;
}

/*****************************************************************************/
/*	Übernimmt die automatische Aktualisierung der Anzeigen des Dialogs/*
/*****************************************************************************/
void CDlgDemoRSAKeyGeneration::OnUpdateParameter() 
{
	UpdateData(TRUE);

	CString sKeyPublic = m_sKeyPublic; // Eingegebene Formel (z.B. 2^16+1) sichern.
	int		ePrime = m_Cert->InitParameter( m_sPrime_p, m_sPrime_q );
	BOOL	bIsEmpty = m_sPrime_p.IsEmpty() || m_sPrime_q.IsEmpty();
	int		iBitLength = m_Cert->GetBitLength();
	if(iBitLength) m_sBitLength.Format(IDS_BIT, iBitLength);
		else m_sBitLength.Empty();

	if( bIsEmpty )
	{
		m_CheckPrimeCtrl.ShowWindow( SW_HIDE );
		m_CheckPublicCtrl.ShowWindow( SW_HIDE );
		m_KeyPublicCtrl.EnableWindow(FALSE); 
		m_sKeyPrivate.Empty();	
		m_sPhiN.Empty();	
		m_sModN.Empty();	
	}
	else
	{
		m_CheckPrimeCtrl.ShowWindow( SW_SHOW );
		if( ePrime )
		{
			m_CheckPublicCtrl.ShowWindow( SW_HIDE );
			m_KeyPublicCtrl.EnableWindow( FALSE ); 
			m_sKeyPrivate.Empty();	
			m_sPhiN.Empty();		
			m_sModN.Empty();	
			if ( ePrime & ERR_P_LESS_THAN_TWO ) m_sCheckPrime.LoadString( IDS_PRIME_LESS_THAN_TWO_P );
			else if( (ePrime & ERR_P_NOT_PRIME) && (ePrime & ERR_Q_NOT_PRIME) ) m_sCheckPrime.LoadString( IDS_PRIME_NO_CHECK_PQ );
			else if ( ePrime & ERR_Q_LESS_THAN_TWO ) m_sCheckPrime.LoadString( IDS_PRIME_LESS_THAN_TWO_Q );
			else if ( ePrime & ERR_P_NOT_PRIME ) m_sCheckPrime.LoadString( IDS_PRIME_NO_CHECK_P );
			else if ( ePrime & ERR_Q_NOT_PRIME ) m_sCheckPrime.LoadString( IDS_PRIME_NO_CHECK_Q );
			else if ( ePrime & ERR_P_EQUALS_Q ) m_sCheckPrime.LoadString( IDS_PRIME_P_EQUALS_Q );
			else if ( ePrime & ERR_MAX_BIT_LENGTH ) m_sCheckPrime.LoadString( IDS_PRIME_BIT_LENGTH );
			else ASSERT( FALSE );
		}
		else
		{
			m_sCheckPrime.LoadString( IDS_PRIME_CHECK ); // "p und q sind Primzahlen."		
			m_CheckPublicCtrl.ShowWindow( SW_SHOW ); // CheckPublic anzeigen.
			// removed for medida: m_KeyPublicCtrl.EnableWindow( TRUE );	// Eingabe für Public Key ermöglichen...
			m_KeyPublicCtrl.EnableWindow( FALSE ); // this is the medida version (workaround for secude problem with keys != 2^16+1
			if ( m_Cert->SetPublicKey( m_sKeyPublic ) ) // Ist e teilerfremd zu phi (N)?
			{
				m_sCheckPublic.LoadString( IDS_PUBLIC_CHECK ); // "e ist teilerfremd zu phi (N) ."
				m_Cert->SetPrivateKey(); // Private Key ermitteln..
				m_Cert->GetParameter( m_sModN, m_sPhiN, sKeyPublic, m_sKeyPrivate ); // Parameter abfragen...
				// Schlüssel kopieren:
				LoadString( AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE );
				CopyKey ( pc_str, m_sPrime_p + ";" + m_sPrime_q + ";" + sKeyPublic );
			}
			else // Ist e teilerfremd zu phi (N)?
			{
				m_sCheckPublic.LoadString( IDS_PUBLIC_NO_CHECK ); // "e ist NICHT teilerfremd zu phi (N) !"
				m_Cert->GetParameter( m_sModN, m_sPhiN, sKeyPublic, m_sKeyPrivate ); // Parameter abfragen...
				m_sKeyPrivate.Empty(); // Private Key = ""
			}
		}
	}
	if ( m_Cert->IsInitialized() ) // Zertifikat initialisiert?
	{
		// Zertifikat INITIALISIERT!
		m_ButtonOKCtrl.EnableWindow(TRUE); // OK - Button einblenden
	}
	else
	{
		// Zertifikat NICHT INITIALISIERT!
		m_ButtonOKCtrl.EnableWindow(FALSE);	// OK - Button ausblenden
	}
	UpdateData(FALSE);
}

void CDlgDemoRSAKeyGeneration::OnOK() 
{
	UpdateData(TRUE);
	UpdateData(FALSE);

	if((m_Cert->GetBitLength()<MIN_RSA_MODULSIZE) || (m_Cert->GetBitLength()>MAX_RSA_MODULSIZE))
	{
		CString sMsg, sCpt;
		sMsg.Format(IDS_STRING_ASYMKEY_ERR_WRONG_RSAMODUL_BITLENGTH, MIN_RSA_MODULSIZE-1, MAX_RSA_MODULSIZE+1);	
		sCpt.LoadString(IDS_STRING_ASYMKEY_ERR_NONVALID_INPUT);
		MessageBox( sMsg, sCpt, MB_ICONWARNING|MB_OK);		
		return;
	}
	if( (m_sPrime_p != m_sPrime_p_OLD) || (m_sPrime_q != m_sPrime_q_OLD) || (m_sKeyPublic != m_sKeyPublic_OLD) )
	{
		m_Cert->SetName(static_cast<CString>(""), static_cast<CString>(""), static_cast<CString>(""));
		m_Cert->SetTime(0);
		m_Cert->SetPIN(static_cast<CString>(""));
		CDialog::OnOK();
	}
	else  CDialog::OnCancel();
}


void CDlgDemoRSAKeyGeneration::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	UpdateData(TRUE);
	m_sPrime_p = m_sPrime_p_OLD;
	m_sPrime_q = m_sPrime_q_OLD;
	m_sKeyPublic = m_sKeyPublic_OLD;
	UpdateData(FALSE);

	OnUpdateParameter();
	
	CDialog::OnCancel();
}
