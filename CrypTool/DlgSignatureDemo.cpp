// DlgSignTutorial.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSignatureDemo.h"
#include "FileTools.h"
#include "DlgSignature.h"
#include "DlgDemoRSAKeyGeneration.h"
#include "DlgSelHash.h"
#include "DlgCertificateGeneration.h"
//#include "AsymmetricEncryption"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignatureDemo 


CDlgSignatureDemo::CDlgSignatureDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSignatureDemo::IDD, pParent),
  m_nIDHash(0), 
  m_nCols(16),
  m_Message(0),
  m_Signature(0),
  m_NewDoc(0),  
  m_SignText(0),
  m_bUpdateHsh(TRUE),
  m_bUpdateEnc(TRUE),
  m_bUpdateSgn(TRUE),
  m_bUpdateCrt(TRUE)
{
	//{{AFX_DATA_INIT(CDlgSignatureDemo)
	m_DisplayInfo = _T("");
	m_DisplayContent = _T("");
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	m_Cert = new CPSEDemo;
	m_osHash=0;
	m_osHashEnc = 0;
}

CDlgSignatureDemo::~CDlgSignatureDemo()
{
	delete m_Cert;

	//if(m_osHashEnc.octets) delete[] m_osHashEnc.octets;
	theApp.SecudeLib.aux_free_OctetString(&m_Message);
	if(m_SignText) delete[] m_SignText->octets;
	delete   m_SignText;
	m_SignText = 0;
}


void CDlgSignatureDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSignatureDemo)
	DDX_Control(pDX, IDC_DISPLAY_CONTENT, m_DisplayContentCtrl);
	DDX_Control(pDX, IDC_DISPLAY_INFO, m_DisplayInfoCtrl);
	DDX_Text(pDX, IDC_DISPLAY_INFO, m_DisplayInfo);
	DDX_Text(pDX, IDC_DISPLAY_CONTENT, m_DisplayContent);
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
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
	VERIFY(m_ButtonSelectDoc.AutoLoad(IDC_SELECT_DOCUMENT, this));
	
	VERIFY(m_ButtonInfoDoc.AutoLoad(IDC_INFO_DOCUMENT,this));

	EnableButtons(); // Bitmap-Butttons ein/ausblenden

	if(!m_sPathName.IsEmpty()) OnInfoDocument(); // Dokument anzeigen	
	
	return TRUE;  // return TRUE unless you set the focus to a control
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
	sTitle.LoadString(IDS_OPEN_DOCUMENT);
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
			m_Message=theApp.SecudeLib.aux_file2OctetString(m_sPathName);
		}
		EnableButtons(); // Bitmap-Butttons ein/ausblenden
	}	
	delete doc;
}

BOOL CDlgSignatureDemo::InitDocument(const char *infile, const char* OldTitle)
{
	m_sFileName = OldTitle;
	m_sPathName = infile;
	if(m_Message=theApp.SecudeLib.aux_file2OctetString(m_sPathName)) return TRUE;

	return FALSE;	
}

void CDlgSignatureDemo::OnInfoDocument() 
{
	if (!m_Message->noctets) return;
	
	int srcSize = m_Message->noctets;
	int destSize = (srcSize+m_nCols-1)/m_nCols * (11+m_nCols*4) - (srcSize % m_nCols? m_nCols - srcSize % m_nCols: 0);

	char *msgdata = new char[destSize+1];

	if (!HexDumpMem(msgdata, destSize, reinterpret_cast<unsigned char*>(m_Message->octets), srcSize, m_nCols))
	{
		//FEHLER xxxxxxxxxxxxx MARKSSSS
	}
	
	UpdateData(TRUE);
	m_DisplayContent.LoadString(IDS_CONTENT_DOCUMENT);
	m_DisplayInfo = static_cast<CString>(msgdata);
	m_DisplayContent += m_sFileName;
	UpdateData(FALSE);	
	
	delete[] msgdata;

}


void CDlgSignatureDemo::OnSelectKey() 
{
	CString a1, a2, a3, a4, a5, a6, a7, b1, b2, b3, b4, b5, b6, b7;
	m_Cert->GetParameter(a1, a2, a3, a4); // alte Werte retten
	m_Cert->GetName(a5, a6, a7);
	CDlgDemoRSAKeyGeneration* KeyDialog;
	KeyDialog = new CDlgDemoRSAKeyGeneration(this);

	KeyDialog->InitRSA(m_Cert);
	if(KeyDialog->DoModal()==IDOK) 
	{
		m_Cert->GetParameter(b1, b2, b3, b4);
		m_Cert->GetName(b5, b6, b7);
		if(a1 != b1 || a2 != b2 || a3 != b3 || a4 != b4)
		{
			m_bUpdateEnc = TRUE;
			m_bUpdateSgn = TRUE;
			m_bUpdateCrt = TRUE;
		}
		if(a5 != b5 || a6 != b6 || a7 != b7 ) 
		{
			m_bUpdateSgn = TRUE;
			m_bUpdateCrt = TRUE;
		}
		EnableButtons();
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
	sOutput.Format(IDS_BITLENGTH, m_Cert->GetBitLength());
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
	ClearInfo();

	UpdateData(TRUE);
	// Info Dokument
	if( !m_sPathName.IsEmpty() )
	{
		m_ButtonInfoDoc.EnableWindow(TRUE);
		m_ButtonSelectDoc.LoadBitmaps("OPNDOC_T_U", "OPNDOC_T_D", "OPNDOC_T_F", "OPNDOC_D");
		CWnd* hFocus = m_ButtonSelectDoc.GetFocus();
		m_ButtonSelectDoc.ShowWindow(SW_HIDE);
		m_ButtonSelectDoc.ShowWindow(SW_SHOW);
		if(hFocus->GetSafeHwnd() == m_ButtonSelectDoc.GetSafeHwnd())  m_ButtonSelectDoc.SetFocus();
		
	
	}
	else
	{
		m_ButtonInfoDoc.EnableWindow(FALSE);
		m_ButtonSelectDoc.LoadBitmaps("OPNDOC_F_U", "OPNDOC_F_D", "OPNDOC_F_F", "OPNDOC_D");
		CWnd* hFocus = m_ButtonSelectDoc.GetFocus();
		m_ButtonSelectDoc.ShowWindow(SW_HIDE);
		m_ButtonSelectDoc.ShowWindow(SW_SHOW);
		m_ButtonSelectDoc.SetFocus();
		if(hFocus->GetSafeHwnd() == m_ButtonSelectDoc.GetSafeHwnd())  m_ButtonSelectDoc.SetFocus();
	}

	// Info Hash Algorithmus
	if( m_nIDHash )
	{}
	else
	{}

	// Info Schlüssel
	if( m_Cert->IsInitialized() )
	{}
	else
	{}

	// Info Hashwert
	if( m_osHash && !m_bUpdateHsh )
	{}
	else
	{}

	// Info  verschlüsselter Hashwert
	if( m_osHashEnc && !m_bUpdateEnc )
	{}
	else
	{}

	/*
	// Info signiertes Dokument
	if( && !m_UpdateCrt && !m_bUpdateHsh && !m_bUpdateEnc && !m_bUpdateSgn)
	{}
	else
	{}
	*/

	// Hashwert berechnen
	if( m_Message && m_nIDHash )
	{}
	else
	{}

	// Hashwert verschlüsseln
	if( m_Cert->IsInitialized() && m_osHash && !m_bUpdateHsh )
	{}
	else
	{}

	/*
	// Daten zusammenfügen
	if(   && !m_bUpdateHsh && !m_bUpdateEnc )
	{}
	else
	{}
	*/
	UpdateData(FALSE);
}

void CDlgSignatureDemo::OnSelectHashAlg() 
{		
	CDlgSelHash* HashDialog;
	HashDialog = new CDlgSelHash(this);

	HashDialog->InitHashID(m_nIDHash);
	HashDialog->DoModal();
	if(m_nIDHash != HashDialog->GetHashID())
	{
		m_bUpdateHsh = TRUE;
		m_bUpdateEnc = TRUE;
		m_bUpdateSgn = TRUE;
		m_nIDHash = HashDialog->GetHashID();
		switch( m_nIDHash ) 
		{
			case IDC_MD2:		m_Cert->SetHashAlg(static_cast<CString>("MD2"));		break;
			case IDC_MD5:		m_Cert->SetHashAlg(static_cast<CString>("MD5"));		break;
			case IDC_SHA:		m_Cert->SetHashAlg(static_cast<CString>("SHA"));		break;
			case IDC_SHA_1:		m_Cert->SetHashAlg(static_cast<CString>("SHA-1"));		break;
			case IDC_RIPEMD160: m_Cert->SetHashAlg(static_cast<CString>("RIPEMD-160"));	break;
			default:			m_Cert->SetHashAlg(static_cast<CString>(""));
		}
		EnableButtons();
	}	
	delete HashDialog;	
}



void CDlgSignatureDemo::OnCompute() 
{
	if(m_sPathName.IsEmpty()) return;

	if(!(m_osHash = new OctetString)) return;
	
   
	switch (m_nIDHash)
	{
		case IDC_MD2:
			theApp.SecudeLib.sec_hash_all(m_Message, m_osHash, theApp.SecudeLib.md2_aid, NULL);
			break;
		case IDC_MD4:
			theApp.SecudeLib.sec_hash_all(m_Message, m_osHash,theApp.SecudeLib.md4_aid,NULL);
			break;
		case IDC_MD5:
			theApp.SecudeLib.sec_hash_all(m_Message, m_osHash,theApp.SecudeLib.md5_aid,NULL);
			break;
		case IDC_SHA:
			theApp.SecudeLib.sec_hash_all(m_Message, m_osHash,theApp.SecudeLib.sha_aid,NULL);
			break;
		case IDC_SHA_1:
			theApp.SecudeLib.sec_hash_all(m_Message, m_osHash,theApp.SecudeLib.sha1_aid,NULL);
			break;
		case IDC_RIPEMD160:
			theApp.SecudeLib.sec_hash_all(m_Message, m_osHash,theApp.SecudeLib.ripemd160_aid,NULL);
			break;
	}
	m_bUpdateHsh = FALSE;		
	EnableButtons();
}

void CDlgSignatureDemo::OnInfoHash() 
{
	if (!m_osHash || m_bUpdateHsh) return;
	
	int srcSize = m_osHash->noctets;
	//OctetString msgdata;

	/*if (!HexDumpOct(msgdata, m_osHash, m_nCols))
	{
		//FEHLER
		return;
	}*/

	
	UpdateData(TRUE);
	dataToHexDump(m_osHash->octets, m_osHash->noctets, m_DisplayInfo); /*FIXME*/
	//m_DisplayInfo = static_cast<CString>(msgdata);
	m_DisplayContent.Format(IDS_STRING_HASH_VALUE_OF, m_Cert->GetHashAlg(), m_sFileName);
	UpdateData(FALSE);

	//delete[] msgdata.octets;
	
}

void CDlgSignatureDemo::OnEncrypt() 
{
	if(!m_osHash) return;

	OctetString* osHashDER = new OctetString;

	if(!osHashDER) return;
	memset(osHashDER, 0, sizeof(OctetString));

	if(!m_Cert->Encode(*m_osHash, *osHashDER)) return;

	/**********************************************/

	int srcSize = osHashDER->noctets;
	int destSize = (srcSize+m_nCols-1)/m_nCols * (11+m_nCols*4) - (srcSize % m_nCols? m_nCols - srcSize % m_nCols: 0);
	char *msgdata = new char[destSize+1];
	HexDumpMem(msgdata, destSize, reinterpret_cast<unsigned char*>(osHashDER->octets), srcSize, m_nCols);
	UpdateData(TRUE);
	m_DisplayInfo = static_cast<CString>(msgdata);
	UpdateData(FALSE);


	/**********************************************/

	Big C, N, p, D, e;
	if(!m_Cert->GetParameter(N, p, e, D)) return;		
	Big Hash = from_binary(osHashDER->noctets, osHashDER->octets);

	/*
	OctetString* osHashAlg;
	osHashAlg = theApp.SecudeLib.e_AlgId(theApp.SecudeLib.md2_aid);
	osHashAlg = theApp.SecudeLib.e_AlgId(theApp.SecudeLib.md2WithRSASignature_aid);
	//osHashAlg = theApp.SecudeLib.e_AlgId(theApp.SecudeLib.md2WithRsa_aid);
	osHashAlg = theApp.SecudeLib.e_AlgId(theApp.SecudeLib.md2WithRsaEncryption_aid);	
	*/

	Hash %= N;
	C = pow(Hash, D, N);
	if(m_osHashEnc)
	{
		if (m_osHashEnc->octets) delete[] m_osHashEnc->octets;
	}
	delete m_osHashEnc;
	m_osHashEnc = new OctetString;
	memset(m_osHashEnc, 0, sizeof(OctetString));
	OctetString* osC = new OctetString;

	osC->noctets = (bits(C)+7)/8;	
	osC->octets = new char[osC->noctets];
	to_binary(C, osC->noctets, osC->octets);


	m_osHashEnc->noctets = (bits(N)+7)/8 - osC->noctets;
	if(m_osHashEnc->noctets) 
	{
		m_osHashEnc->octets = new char[m_osHashEnc->noctets];
		memset(m_osHashEnc->octets, 0, m_osHashEnc->noctets);
	}
	Add2OString(m_osHashEnc, osC->octets, osC->noctets);
	delete[] osC->octets;
	delete osC;
	
	m_bUpdateEnc = FALSE; 
	//EnableButtons();
}

void CDlgSignatureDemo::OnInfoHashEnc() 
{
	if (!m_osHashEnc || m_bUpdateEnc) return;
	
	int srcSize = m_osHashEnc->noctets;
	int destSize = (srcSize+m_nCols-1)/m_nCols * (11+m_nCols*4) - (srcSize % m_nCols? m_nCols - srcSize % m_nCols: 0);


	char *msgdata = new char[destSize+1];

	if (!HexDumpMem(msgdata, destSize, reinterpret_cast<unsigned char*>(m_osHashEnc->octets), srcSize, m_nCols))
	{
		//FEHLER
		return;
	}
	
	UpdateData(TRUE);
	m_DisplayInfo = static_cast<CString>(msgdata);
	m_DisplayContent.Format(IDS_STRING_ENC_HASH_VALUE_OF, m_Cert->GetHashAlg(), m_sFileName);
	UpdateData(FALSE);	
	
	delete[] msgdata;
	
}

void CDlgSignatureDemo::OnSelectCert() 
{
	if(!m_Cert->IsInitialized()) return;

	CDlgCertificateGeneration* CertDialog;
	CertDialog = new CDlgCertificateGeneration(this);

	CertDialog->InitRSA(m_Cert);
	if(CertDialog->DoModal()==IDOK) 
	{
		m_bUpdateSgn=TRUE;
		if(m_Cert->CreatePSE())
		{
			m_bUpdateCrt=FALSE;
		}
		EnableButtons();
	}

	delete CertDialog;

	
}

void CDlgSignatureDemo::OnInfoAlg() 
{
	if(m_Cert->GetHashAlg().IsEmpty()) return;

	UpdateData(TRUE);
	m_DisplayContent.LoadString(IDS_CONTENT_ALG);
	m_DisplayInfo = m_Cert->GetHashAlg();
	UpdateData(FALSE);
}

void CDlgSignatureDemo::OnCombine() 
{
	if(!m_Message->noctets) return;
	if(m_SignText) delete[] m_SignText->octets;
	delete   m_SignText;
	m_SignText = new OctetString;
	memset(m_SignText, 0, sizeof(OctetString));
		
	CString UserKeyId, Buffer;
	m_Cert->GetKeyId(UserKeyId, Buffer);
	PrintSignature(*m_SignText, *m_osHashEnc, "RSA", m_Cert->GetHashAlg(),UserKeyId);
}

void CDlgSignatureDemo::OnOK() 
{
	if(m_Message && m_Message->noctets)
	{
		char outfile[128];
		CAppDocument* NewDoc;		

		if(m_SignText)
		{
			GetTmpName(outfile,"cry",".hex");
			

			Add2OString(m_SignText, m_Message->octets, m_Message->noctets);
			theApp.SecudeLib.aux_OctetString2file(m_SignText,outfile,2);
			NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
			remove(outfile);
			m_sFileNameNew.Format(IDS_RSA_SIGNATURE_OF, m_Cert->GetHashAlg(), m_sFileName);
			NewDoc->SetTitle(m_sFileNameNew);
		}
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
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	if(!m_Cert->PSEIsInitialized()) return;

	UpdateData(TRUE);
	m_DisplayContent.LoadString(IDS_CONTENT_CERT);
	m_DisplayInfo = m_Cert->GetCert();
	UpdateData(FALSE);
}

void CDlgSignatureDemo::OnInfoSign() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	int srcSize = m_SignText->noctets;
	int destSize = (srcSize+m_nCols-1)/m_nCols * (11+m_nCols*4) - (srcSize % m_nCols? m_nCols - srcSize % m_nCols: 0);


	char *msgdata = new char[destSize+1];

	if (!HexDumpMem(msgdata, destSize, reinterpret_cast<unsigned char*>(m_SignText->octets), srcSize, m_nCols))
	{
		//FEHLER
		return;
	}


	UpdateData(TRUE);
	m_DisplayContent.Format(IDS_CONTENT_SIGN, m_Cert->GetHashAlg(), m_sFileName);
	m_DisplayInfo = static_cast<CString>(msgdata);
	UpdateData(FALSE);
}

