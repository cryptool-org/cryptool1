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

// DlgSignTutorial.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSignatureDemo.h"
#include "FileTools.h"
#include "DlgSignature.h"
#include "DlgDemoRSAKeyGeneration.h"
#include "DlgCertificateGeneration.h"
#include "DlgSelectHashFunction.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char button1, button2, button3, button4;

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignatureDemo 


CDlgSignatureDemo::CDlgSignatureDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSignatureDemo::IDD, pParent),
  m_nCols(18),
  m_Message(0),
  m_NewDoc(0),  
  m_bUpdateHsh(TRUE),
  m_bUpdateEnc(TRUE),
  m_bUpdateSgn(TRUE),
  m_bUpdateCrt(TRUE)
{
	//{{AFX_DATA_INIT(CDlgSignatureDemo)
	m_DisplayInfo = _T("");
	m_DisplayContent = _T("");
	//}}AFX_DATA_INIT

	m_Cert = new CPSEDemo;
	memset(&m_osHash, 0, sizeof(OctetString));
	memset(&m_osHashDER, 0, sizeof(OctetString));
	memset(&m_osHashEnc, 0, sizeof(OctetString));
	memset(&m_SignText, 0, sizeof(OctetString));
}

CDlgSignatureDemo::~CDlgSignatureDemo()
{
	delete m_Cert;
	theApp.SecudeLib.aux_free_OctetString(&m_Message);
	delete[] m_SignText.octets;	
}


void CDlgSignatureDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSignatureDemo)
	DDX_Control(pDX, IDC_DISPLAY_CONTENT, m_DisplayContentCtrl);
	DDX_Control(pDX, IDC_DISPLAY_INFO, m_DisplayInfoCtrl);
	DDX_Text(pDX, IDC_DISPLAY_INFO, m_DisplayInfo);
	DDX_Text(pDX, IDC_DISPLAY_CONTENT, m_DisplayContent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSignatureDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgSignatureDemo)
	ON_BN_CLICKED(IDC_SELECT_DOCUMENT, OnSelectDocument)
	ON_BN_CLICKED(IDC_INFO_DOCUMENT, OnInfoDocument)
	ON_BN_CLICKED(IDC_SELECT_KEY, OnSelectKey)
	ON_BN_CLICKED(IDC_INFO_KEY, OnInfoKey)
	ON_BN_CLICKED(IDC_SELECT_HASHALG, OnSelectHashAlg)
	ON_BN_CLICKED(IDC_COMPUTE, OnCompute)
	ON_BN_CLICKED(IDC_INFO_HASH, OnInfoHash)
	ON_BN_CLICKED(IDC_ENCRYPT, OnEncrypt)
	ON_BN_CLICKED(IDC_INFO_HASH_ENC, OnInfoHashEnc)
	ON_BN_CLICKED(IDC_SELECT_CERT, OnSelectCert)
	ON_BN_CLICKED(IDC_INFO_ALG, OnInfoAlg)
	ON_BN_CLICKED(IDC_COMBINE, OnCombine)
	ON_BN_CLICKED(IDC_INFO_CERT, OnInfoCert)
	ON_BN_CLICKED(IDC_INFO_SIGN, OnInfoSign)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSignatureDemo 

BOOL CDlgSignatureDemo::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Fonts initialisieren:
	m_Font1.CreatePointFont(80, "Courier");
	m_DisplayInfoCtrl.SetFont(&m_Font1);
	
	// BitmapButtons laden:	
	m_ButtonSelectDoc.AutoLoad(IDC_SELECT_DOCUMENT, this);
	m_ButtonSelectHashAlg.AutoLoad(IDC_SELECT_HASHALG, this);
	m_ButtonSelectKey.AutoLoad(IDC_SELECT_KEY, this);
	m_ButtonSelectCert.AutoLoad(IDC_SELECT_CERT, this);
	
	m_ButtonInfoDoc.AutoLoad(IDC_INFO_DOCUMENT,this);
	m_ButtonInfoHashAlg.AutoLoad(IDC_INFO_HASHALG,this);
	m_ButtonInfoKey.AutoLoad(IDC_INFO_KEY,this);
	m_ButtonInfoCert.AutoLoad(IDC_INFO_CERT,this);

	m_ButtonCompute.AutoLoad(IDC_COMPUTE, this);
	m_ButtonEncrypt.AutoLoad(IDC_ENCRYPT, this);
	m_ButtonCombine.AutoLoad(IDC_COMBINE,this);

	m_ButtonInfoHash.AutoLoad(IDC_INFO_HASH,this);
	m_ButtonInfoHashEnc.AutoLoad(IDC_INFO_HASH_ENC,this);
	m_ButtonInfoSign.AutoLoad(IDC_INFO_SIGN,this);

	m_ButtonCancel.AutoLoad(IDCANCEL, this);
	m_ButtonOK.AutoLoad(IDOK, this);

	if(!m_sPathName.IsEmpty()) // Dokument anzeigen
	{	
		OnInfoDocument(); 
		m_ButtonInfoDoc.SetFocus();
		button1 = -1;
	}
	else
		button1 = 0;
	button2 = button3 = button4;
	EnableButtons(); // Bitmap-Butttons ein/ausblenden	

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgSignatureDemo::OnSelectDocument()
{
	// Initialisierung des File-Dialogs:
	CString sFileFilter;
	CString sDefName("*.TXT");
	CString sTitle;
	DWORD   dwFlags(OFN_HIDEREADONLY);
	sFileFilter.LoadString(IDS_OPEN_DOCUMENT_FILTER);
	sTitle.LoadString(IDS_OPEN_DOC);
	CFileDialog* doc;
	doc = new CFileDialog(TRUE, NULL, sDefName, dwFlags, sFileFilter);
	doc->m_ofn.lpstrTitle = sTitle;

	if(doc->DoModal()==IDOK)// Aufruf des File-Dialogs
	{
		m_bUpdateHsh = TRUE;
		m_bUpdateEnc = TRUE;
		m_bUpdateSgn = TRUE;
		if( m_sPathName != doc->GetPathName() )
		{
			m_sFileName = doc->GetFileName(); // Titel setzen
			m_sPathName = doc->GetPathName(); // Pfadnamen setzen
		}		
		if( !doc->GetFileName().IsEmpty() )
		{   // Dateiinhalt in die Variable m_Message einlesen
			theApp.SecudeLib.aux_free_OctetString(&m_Message);
			m_Message = theApp.SecudeLib.aux_file2OctetString(m_sPathName);
			if ( !m_Message || !m_Message->noctets )
			{
				Message( IDS_SIGDEMO_FILE_EMPTY, MB_ICONEXCLAMATION );
				return;
			}
			button1 = -1;
			EnableButtons();
			//OnInfoDocument();
			m_ButtonInfoDoc.SetFocus();
			ClearInfo();
		}
	}	

	delete doc;
}

BOOL CDlgSignatureDemo::InitDocument(const char *infile, const char* OldTitle)
{
	m_sFileName = OldTitle;
	m_sPathName = infile;
	if(m_Message = theApp.SecudeLib.aux_file2OctetString(m_sPathName)) 
	{
		if ( !m_Message || m_Message->noctets )
		{
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;	
}

void CDlgSignatureDemo::OnInfoDocument() 
{
	if (!m_Message->noctets) return;
	
	int srcSize = m_Message->noctets;
	int destSize = (srcSize+m_nCols-1)/m_nCols * (11+m_nCols*4) - (srcSize % m_nCols? m_nCols - srcSize % m_nCols: 0);

	char *msgdata = new char[destSize+1];

	if (!HexDumpMem(msgdata, destSize, reinterpret_cast<unsigned char*>(m_Message->octets), srcSize, m_nCols)) return;
	
	UpdateData(TRUE);
	m_DisplayContent.LoadString(IDS_CONTENT_DOCUMENT);
	m_DisplayInfo = static_cast<CString>(msgdata);
	m_DisplayContent += m_sFileName;
	UpdateData(FALSE);	
	
	delete[] msgdata;
}


void CDlgSignatureDemo::OnSelectKey() 
{
	CDlgDemoRSAKeyGeneration* KeyDialog;
	KeyDialog = new CDlgDemoRSAKeyGeneration(this);

	KeyDialog->InitRSA(m_Cert);
	if(KeyDialog->DoModal()==IDOK) 
	{
		m_bUpdateEnc = TRUE;
		m_bUpdateSgn = TRUE;
		m_bUpdateCrt = TRUE;
		button3 = -1;
		button4 = -1;
		EnableButtons();
		//OnInfoKey();
		m_ButtonInfoKey.SetFocus();	
		ClearInfo();
	}
	delete KeyDialog;			
}

void CDlgSignatureDemo::OnInfoKey() 
{
	if(!m_Cert->IsInitialized()) return;

	CString sModN, sPhiN, sKeyPublic, sKeyPrivate, sOutput;
	m_Cert->GetParameter(sModN, sPhiN,sKeyPublic,sKeyPrivate);

	ClearInfo();
	UpdateData(TRUE);
	m_DisplayContent.LoadString(IDS_CONTENT_KEY);
	sOutput.Format(IDS_BITLENGTH_MODN, m_Cert->GetBitLength());
	m_DisplayInfo += sOutput;
	sOutput.Format(IDS_MOD_N, sModN);
	m_DisplayInfo += sOutput;
	sOutput.Format(IDS_PHI_N, sPhiN);
	m_DisplayInfo += sOutput;
	sOutput.Format(IDS_KEY_PUBLIC, sKeyPublic);
	m_DisplayInfo += sOutput;
	sOutput.Format(IDS_KEY_PRIVATE, sKeyPrivate);
	m_DisplayInfo += sOutput;
	UpdateData(FALSE);
}


/********************************************************************************
/* Diese Funktion aktiviert / deaktiviert die Bitmapbuttons
/********************************************************************************/


void CDlgSignatureDemo::EnableButtons()
{
	m_hFocus = GetFocus();

	unsigned long newsdStatus = 0;

	UpdateData(TRUE);

	// Info Signatur


	if( m_SignText.noctets  && !m_bUpdateSgn)
	{
		m_ButtonOK.EnableWindow(TRUE);
		m_ButtonInfoSign.EnableWindow(TRUE);
		m_ButtonCombine.LoadBitmaps("COMBINE_G_U", "COMBINE_G_D", "COMBINE_G_F", "COMBINE_R_X");
		m_ButtonCombine.ShowWindow(SW_HIDE);
		m_ButtonCombine.ShowWindow(SW_SHOW);
	}
	else
	{
		m_ButtonOK.EnableWindow(FALSE);
		m_ButtonInfoSign.EnableWindow(FALSE);
		m_ButtonCombine.LoadBitmaps("COMBINE_R_U", "COMBINE_R_D", "COMBINE_R_F", "COMBINE_R_X");
		m_ButtonCombine.ShowWindow(SW_HIDE);
		m_ButtonCombine.ShowWindow(SW_SHOW);
	}	

	// Info Hashwert
	if( m_osHash.noctets && !m_bUpdateHsh )
	{
		m_ButtonInfoHash.EnableWindow(TRUE);
		m_ButtonCompute.LoadBitmaps("COMPUTE_G_U", "COMPUTE_G_D", "COMPUTE_G_F", "COMPUTE_R_X");
		m_ButtonCompute.ShowWindow(SW_HIDE);
		m_ButtonCompute.ShowWindow(SW_SHOW);
	}
	else
	{
		m_ButtonInfoHash.EnableWindow(FALSE);
		m_ButtonCompute.LoadBitmaps("COMPUTE_R_U", "COMPUTE_R_D", "COMPUTE_R_F", "COMPUTE_R_X");
		m_ButtonCompute.ShowWindow(SW_HIDE);
		m_ButtonCompute.ShowWindow(SW_SHOW);
	}

	// Info  verschlüsselter Hashwert
	if( m_osHashEnc.noctets && !m_bUpdateEnc )
	{
		m_ButtonInfoHashEnc.EnableWindow(TRUE);
		m_ButtonEncrypt.LoadBitmaps("ENCRYPT_G_U", "ENCRYPT_G_D", "ENCRYPT_G_F", "ENCRYPT_R_X");
		m_ButtonEncrypt.ShowWindow(SW_HIDE);
		m_ButtonEncrypt.ShowWindow(SW_SHOW);
	}
	else
	{
		m_ButtonInfoHashEnc.EnableWindow(FALSE);
		m_ButtonEncrypt.LoadBitmaps("ENCRYPT_R_U", "ENCRYPT_R_D", "ENCRYPT_R_F", "ENCRYPT_R_X");
		m_ButtonEncrypt.ShowWindow(SW_HIDE);
		m_ButtonEncrypt.ShowWindow(SW_SHOW);
	}
	
	// Hashwert berechnen
	if( m_Message && !m_Cert->GetHashAlg().IsEmpty() )
	{
		m_ButtonCompute.EnableWindow(TRUE);
	}
	else
	{
		m_ButtonCompute.EnableWindow(FALSE);
	}

	// Hashwert verschlüsseln
	if( m_Cert->IsInitialized() && m_osHash.noctets && !m_bUpdateHsh )
	{
		m_ButtonEncrypt.EnableWindow(TRUE);
	}
	else
	{
		m_ButtonEncrypt.EnableWindow(FALSE);
	}

	// Daten zusammenfügen
	if(  m_Cert->PSEIsInitialized() && !m_bUpdateEnc &&  !m_bUpdateCrt )
	{
		m_ButtonCombine.EnableWindow(TRUE);
	}
	else
	{
		m_ButtonCombine.EnableWindow(FALSE);
	}
	
	
	
	
	// Info Dokument
	if( !m_sPathName.IsEmpty() )
		m_ButtonInfoDoc.EnableWindow(TRUE);
	else
		m_ButtonInfoDoc.EnableWindow(FALSE);

	if ( button1 == -1 ) 
	{
		if( !m_sPathName.IsEmpty() )
		{
			m_ButtonSelectDoc.LoadBitmaps("OPENDOC_G_U", "OPENDOC_G_D", "OPENDOC_G_F", NULL);
			m_ButtonSelectDoc.ShowWindow(SW_HIDE);
			m_ButtonSelectDoc.ShowWindow(SW_SHOW);
		}
		else
		{
			m_ButtonSelectDoc.LoadBitmaps("OPENDOC_R_U", "OPENDOC_R_D", "OPENDOC_R_F", NULL);
			m_ButtonSelectDoc.ShowWindow(SW_HIDE);
			m_ButtonSelectDoc.ShowWindow(SW_SHOW);
		}
		button1 = 1;
	}
	// Info Hash Algorithmus
	if( !m_Cert->GetHashAlg().IsEmpty() )
		m_ButtonInfoHashAlg.EnableWindow(TRUE);
	else
		m_ButtonInfoHashAlg.EnableWindow(FALSE);

	if ( button2 = -1 )
	{
		if( !m_Cert->GetHashAlg().IsEmpty() )
		{
			m_ButtonSelectHashAlg.LoadBitmaps("SELECTALG_G_U", "SELECTALG_G_D", "SELECTALG_G_F", NULL);
			m_ButtonSelectHashAlg.ShowWindow(SW_HIDE);
			m_ButtonSelectHashAlg.ShowWindow(SW_SHOW);	
		}
		else
		{
			m_ButtonSelectHashAlg.LoadBitmaps("SELECTALG_R_U", "SELECTALG_R_D", "SELECTALG_R_F", NULL);
			m_ButtonSelectHashAlg.ShowWindow(SW_HIDE);
			m_ButtonSelectHashAlg.ShowWindow(SW_SHOW);
		}
		button2 = 1;
	}

	// Info Schlüssel
	if( m_Cert->IsInitialized() )
		m_ButtonInfoKey.EnableWindow(TRUE);
	else
		m_ButtonInfoKey.EnableWindow(FALSE);
	if ( button3 == -1 )
	{
		if( m_Cert->IsInitialized() )
		{
			m_ButtonSelectKey.LoadBitmaps("GENKEY_G_U", "GENKEY_G_D", "GENKEY_G_F", NULL);
			m_ButtonSelectKey.ShowWindow(SW_HIDE);
			m_ButtonSelectKey.ShowWindow(SW_SHOW);
		}
		else
		{
			m_ButtonSelectKey.LoadBitmaps("GENKEY_R_U", "GENKEY_R_D", "GENKEY_R_F", NULL);
			m_ButtonSelectKey.ShowWindow(SW_HIDE);
			m_ButtonSelectKey.ShowWindow(SW_SHOW);
		}
		button3 = 1;
	}

	// Info Zertifikat
	if( m_Cert->PSEIsInitialized() && !m_bUpdateCrt )
		m_ButtonInfoCert.EnableWindow(TRUE);
	else
		m_ButtonInfoCert.EnableWindow(FALSE);
	if ( button4 == -1 )
	{
		if( m_Cert->PSEIsInitialized() && !m_bUpdateCrt )
		{
			m_ButtonSelectCert.LoadBitmaps("GENCERT_G_U", "GENCERT_G_D", "GENCERT_G_F", NULL);
			m_ButtonSelectCert.ShowWindow(SW_HIDE);
			m_ButtonSelectCert.ShowWindow(SW_SHOW);	
		}
		else
		{
			m_ButtonSelectCert.LoadBitmaps("GENCERT_R_U", "GENCERT_R_D", "GENCERT_R_F", NULL);
			m_ButtonSelectCert.ShowWindow(SW_HIDE);
			m_ButtonSelectCert.ShowWindow(SW_SHOW);
		}
		button4 = 1;
	}

	UpdateData(FALSE);

	if (m_hFocus)
		m_hFocus->SetFocus();
}

void CDlgSignatureDemo::OnSelectHashAlg() 
{	
	CDlgSelectHashFunction* HashDialog;
	HashDialog = new CDlgSelectHashFunction(this);

	// we're in signature demo mode; thus, no SHA-2 support
	HashDialog->m_deactivateSHA2 = true;

	if (m_Cert->GetHashAlg() && m_Cert->GetHashAlg() != "")
		HashDialog->m_sHashAlg = m_Cert->GetHashAlg();
	else
		HashDialog->m_sHashAlg = CString("SHA-1");
	HashDialog->m_deactivateMD4 = TRUE;
	if ( IDOK == HashDialog->DoModal() && m_Cert->GetHashAlg() != HashDialog->m_sHashAlg )
	{
		m_bUpdateHsh = TRUE;
		m_bUpdateEnc = TRUE;
		m_bUpdateSgn = TRUE;
		m_Cert->SetHashAlg(HashDialog->m_sHashAlg);
		button2 = -1;
		EnableButtons();
		//OnInfoAlg();
		m_ButtonInfoHashAlg.SetFocus();	
		ClearInfo();
	}	
	delete HashDialog;
}



void CDlgSignatureDemo::OnCompute() 
{
	if(!m_Message) return;
	m_Cert->HashAll(*m_Message, m_osHash);
	if(!m_osHash.noctets) return;

	m_bUpdateHsh = FALSE;		
	EnableButtons();
	//OnInfoHash();
	m_ButtonInfoHash.SetFocus();
}

void CDlgSignatureDemo::OnInfoHash() 
{
	if (!m_osHash.noctets || m_bUpdateHsh) 
	{
		Message(IDS_STRING_HYB_SHOW_ENC_DOC, MB_ICONEXCLAMATION);
		return;
	}
	//Message(IDS_STRING_HYB_SHOW_ENC_DOC, MB_ICONEXCLAMATION);
	
	UpdateData(TRUE);
	int srcSize = m_osHash.noctets;
	dataToHexDump(m_osHash.octets, m_osHash.noctets, m_DisplayInfo); /*FIXME*/
	m_DisplayContent.Format(IDS_STRING_HASH_VALUE_OF, m_Cert->GetHashAlg(), m_sFileName);
	UpdateData(FALSE);
}

void CDlgSignatureDemo::OnEncrypt() 
{
	if(!m_osHash.noctets) return;

	memset(&m_osHashDER, 0, sizeof(OctetString));
	if(!m_Cert->Encode(m_osHash, m_osHashDER)) return;
	Big C, N, p, D, e;
	if(!m_Cert->GetParameter(N, p, e, D)) return;		
	Big Hash = from_binary(m_osHashDER.noctets, m_osHashDER.octets);
	Hash %= N;
	C = pow(Hash, D, N);

	delete[] m_osHashEnc.octets;
	memset(&m_osHashEnc, 0, sizeof(OctetString));	
	OctetString osC;
	osC.noctets = (bits(C)+7)/8;	
	osC.octets = new char[osC.noctets];
	to_binary(C, osC.noctets, osC.octets);
	m_osHashEnc.noctets = (bits(N)+7)/8 - osC.noctets;
	if(m_osHashEnc.noctets) 
	{
		m_osHashEnc.octets = new char[m_osHashEnc.noctets];
		memset(m_osHashEnc.octets, 0, m_osHashEnc.noctets);
	}
	Add2OString(&m_osHashEnc, osC.octets, osC.noctets);
	delete[] osC.octets;	
	m_bUpdateEnc = FALSE; 
	EnableButtons();
	//OnInfoHashEnc();
	m_ButtonInfoHashEnc.SetFocus();
}

void CDlgSignatureDemo::OnInfoHashEnc() 
{
	if (!m_osHashEnc.noctets || m_bUpdateEnc) return;

	CString Text;
	CString Encoding;
	CString Padding;
	CString Hash;
	CString HashDER;
	CString HashEnc;
	OctetString DER_Encoding;
	memset(&DER_Encoding, 0, sizeof(OctetString));
	m_Cert->GetDER_Encoding(DER_Encoding);
	dataToHexDump(DER_Encoding.octets, DER_Encoding.noctets, Encoding);
	dataToHexDump(m_osHashDER.octets, strlen(m_osHashDER.octets)+1, Padding);
	dataToHexDump(m_osHash.octets, m_osHash.noctets, Hash);
	dataToHexDump(m_osHashDER.octets, m_osHashDER.noctets, HashDER);
	dataToHexDump(m_osHashEnc.octets, m_osHashEnc.noctets, HashEnc);	

	UpdateData(TRUE);
	m_DisplayInfo.Empty();
	m_DisplayContent.LoadString(IDS_CONTENT_HASH_ENC);
	Text.Format(IDS_PADDING, Padding);
	m_DisplayInfo += Text;
	Text.Format(IDS_DERCODE, Encoding);
	m_DisplayInfo += Text;
	Text.Format(IDS_HASHVALUE, Hash);
	m_DisplayInfo += Text+"\r\n";
	Text.Format(IDS_HASHDER, HashDER);
	m_DisplayInfo += Text;
	Text.Format(IDS_BITLENGTH, m_osHashDER.noctets*8);
	m_DisplayInfo += Text+"\r\n";
	Text.Format(IDS_HASHENC, HashEnc);
	m_DisplayInfo += Text;
	Text.Format(IDS_BITLENGTH, m_osHashEnc.noctets*8);
	m_DisplayInfo += Text+"\r\n";
	UpdateData(FALSE);

	delete[] DER_Encoding.octets;
}

void CDlgSignatureDemo::OnSelectCert() 
{
	CDlgCertificateGeneration* CertDialog;
	CertDialog = new CDlgCertificateGeneration(this);

	CertDialog->InitRSA(m_Cert);
	if(CertDialog->DoModal()==IDOK) 
	{
		m_bUpdateSgn=TRUE;
		if(CertDialog->m_PSEIsExtern)
		{
			m_bUpdateEnc = TRUE;
			m_bUpdateCrt = FALSE;
		}
		else if(m_Cert->CreatePSE())
		{
			m_bUpdateCrt=FALSE;
		}
		button4 = button3 = -1;
		EnableButtons();
		//OnInfoCert();
		m_ButtonInfoCert.SetFocus();	
		ClearInfo();
	}
	m_bPSEIsExtern = CertDialog->m_PSEIsExtern;

	delete CertDialog;
}

void CDlgSignatureDemo::OnInfoAlg() 
{
	if(m_Cert->GetHashAlg().IsEmpty()) return;

	CString Text;
	CString Encoding;
	OctetString DER_Encoding;
	memset(&DER_Encoding, 0, sizeof(OctetString));
	m_Cert->GetDER_Encoding(DER_Encoding);
	dataToHexDump(DER_Encoding.octets, DER_Encoding.noctets, Encoding);	

	UpdateData(TRUE);
	m_DisplayInfo.Empty();
	m_DisplayContent.LoadString(IDS_CONTENT_ALG);
	Text.Format(IDS_NAME2, m_Cert->GetHashAlg(), "");
	m_DisplayInfo += Text;
	Text.Format(IDS_BITLENGTH, m_Cert->GetHashLength());
	m_DisplayInfo += Text;
	Text.Format(IDS_DERCODE, Encoding);
	m_DisplayInfo += Text;
	UpdateData(FALSE);

	delete[] DER_Encoding.octets;
}

void CDlgSignatureDemo::OnCombine() 
{
	if(!m_Message || !m_Message->noctets) return;
	delete[] m_SignText.octets;
	memset(&m_SignText, 0, sizeof(OctetString));
	CString UserKeyId;
	UserKeyId = m_Cert->CreateUserKeyID();
	if(PrintSignature(m_SignText, m_osHashEnc, "RSA", m_Cert->GetHashAlg(),UserKeyId))
	{
		m_bUpdateSgn = FALSE;
	}
	EnableButtons();
	//OnInfoSign();
	m_ButtonInfoSign.SetFocus();
}

void CDlgSignatureDemo::OnOK() 
{
	if(m_Message && m_SignText.noctets)
	{
		char outfile[128];
		CAppDocument* NewDoc;
		GetTmpName(outfile,"cry",".hex");
		Add2OString(&m_SignText, m_Message->octets, m_Message->noctets);
		theApp.SecudeLib.aux_OctetString2file(&m_SignText, outfile,2);
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
		remove(outfile);
		m_sFileNameNew.Format(IDS_RSA_SIGNATURE_OF, m_Cert->GetHashAlg(), m_sFileName);
		NewDoc->SetTitle(m_sFileNameNew);

		CString Text;
		CString Msg;
		Msg.LoadString(IDS_CONGRATULATIONS);
		Text.Format(IDS_RSASGN_DOCNAME, m_sFileName);
		Msg += Text;		
		Text.Format(m_bPSEIsExtern? IDS_RSASGN_PSE_IMP: IDS_RSASGN_PSE, m_Cert->CreateUserKeyID());
		Msg += Text;
		Text.Format(IDS_RSASGN_ALG, m_Cert->GetHashAlg());
		Msg += Text;
		AfxMessageBox(Msg, MB_OK | MB_ICONINFORMATION);
	}	
	CDialog::OnOK();
}

void CDlgSignatureDemo::ClearInfo()
{
	UpdateData(TRUE);
	m_DisplayContent.Empty();
	m_DisplayInfo.Empty();	
	UpdateData(FALSE);
}

void CDlgSignatureDemo::OnInfoCert() 
{
	if(!m_Cert->PSEIsInitialized()) return;

	UpdateData(TRUE);
	m_DisplayContent.LoadString(IDS_CONTENT_CERT);
	m_DisplayInfo = m_Cert->GetCert();
	UpdateData(FALSE);
}

void CDlgSignatureDemo::OnInfoSign() 
{
	int srcSize = m_SignText.noctets;
	int destSize = (srcSize+m_nCols-1)/m_nCols * (11+m_nCols*4) - (srcSize % m_nCols? m_nCols - srcSize % m_nCols: 0);
	char *msgdata = new char[destSize+1];
	if (!HexDumpMem(msgdata, destSize, reinterpret_cast<unsigned char*>(m_SignText.octets), srcSize, m_nCols)) return;

	UpdateData(TRUE);
	m_DisplayContent.Format(IDS_CONTENT_SIGN, m_Cert->GetHashAlg(), m_sFileName);
	m_DisplayInfo = static_cast<CString>(msgdata);
	UpdateData(FALSE);
}


void CDlgSignatureDemo::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
		// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	dc.FillSolidRect(0,0,800,700,0x00C6C3C6);
	// Kein Aufruf von CDialog::OnPaint() für Zeichnungsnachrichten
}
