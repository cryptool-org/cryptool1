// DlgSignTutorial.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgSignTutorial.h"
#include "fileutil.h"
#include "DlgSign.h"
#include "DlgKeyTutorial.h"
#include "DlgSelHash.h"
#include "DlgCertTutorial.h"
//#include "asymmetric.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignTutorial 


CDlgSignTutorial::CDlgSignTutorial(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSignTutorial::IDD, pParent),
  m_nIDHash(0), 
  m_Message(0),
  m_Signature(0),
  m_NewDoc(0),
  m_nCols(16),
  m_SignText(0)
{
	//{{AFX_DATA_INIT(CDlgSignTutorial)
	m_DisplayInfo = _T("");
	m_DisplayContent = _T("");
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	m_Cert = new CTutorialCert;
	m_osHash=0;
	m_osHashEnc = 0;
	m_bUpdateHsh = TRUE;
	m_bUpdateEnc = TRUE;
	m_bUpdateSgn = TRUE;
	m_bUpdateCrt = TRUE;
}

CDlgSignTutorial::~CDlgSignTutorial()
{
	if(m_Cert) delete m_Cert;

	//if(m_osHashEnc.octets) delete[] m_osHashEnc.octets;
	theApp.SecudeLib.aux_free_OctetString(&m_Message);
	if(m_SignText) delete[] m_SignText->octets;
	delete   m_SignText;
	m_SignText = 0;
}


void CDlgSignTutorial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSignTutorial)
	DDX_Control(pDX, IDC_DISPLAY_CONTENT, m_DisplayContentCtrl);
	DDX_Control(pDX, IDC_DISPLAY_INFO, m_DisplayInfoCtrl);
	DDX_Text(pDX, IDC_DISPLAY_INFO, m_DisplayInfo);
	DDX_Text(pDX, IDC_DISPLAY_CONTENT, m_DisplayContent);
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSignTutorial, CDialog)
	//{{AFX_MSG_MAP(CDlgSignTutorial)
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
// Behandlungsroutinen für Nachrichten CDlgSignTutorial 

BOOL CDlgSignTutorial::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Fonts initialisieren:
	m_Font1.CreatePointFont(80, "Courier");
	m_DisplayInfoCtrl.SetFont(&m_Font1);
	
	// BitmapButtons laden:
	// m_ButtonSelectDoc.SetWindowText("OPNDOC_T_");
	VERIFY(m_ButtonSelectDoc.AutoLoad(IDC_SELECT_DOCUMENT, this));
	
	VERIFY(m_ButtonInfoDoc.AutoLoad(IDC_INFO_DOCUMENT,this));

	EnableButtons(); // Bitmap-Butttons ein/ausblenden

	if(!m_sPathName.IsEmpty()) OnInfoDocument(); // Dokument anzeigen	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgSignTutorial::OnSelectDocument()
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

BOOL CDlgSignTutorial::InitDocument(const char *infile, const char* OldTitle)
{
	m_sFileName = OldTitle;
	m_sPathName = infile;
	if(m_Message=theApp.SecudeLib.aux_file2OctetString(m_sPathName)) return TRUE;

	return FALSE;	
}

void CDlgSignTutorial::OnInfoDocument() 
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



	const char DER_MD2[]	   = {0x30, 0x20, 0x30, 0x0c, 0x06, 0x08, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x02, 0x02, 0x05, 0x00, 0x04, 0x10};
	const char DER_MD5[]	   = {0x30, 0x20, 0x30, 0x0c, 0x06, 0x08, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x02, 0x05, 0x05, 0x00, 0x04, 0x10};
	const char DER_SHA1[]	   = {0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2b, 0x0e, 0x03, 0x02, 0x1a, 0x05, 0x00, 0x04, 0x14};
	const char DER_RIPEMD160[] = {0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2b, 0x24, 0x03, 0x02, 0x01, 0x05, 0x00, 0x04, 0x14};
	const int  DER_MD2_SIZE = 18;
	const int  DER_MD5_SIZE = 18;
	const int  DER_SHA1_SIZE = 15;
	const int  DER_RIPEMD160_SIZE = 15;

	CString hexDump;
	dataToHexDump(DER_MD2, DER_MD2_SIZE, hexDump);

	char* data2 = new char[50];
	HexDumpToData(hexDump, data2);
}


void CDlgSignTutorial::OnSelectKey() 
{
	CString a1, a2, a3, a4, a5, a6, a7, b1, b2, b3, b4, b5, b6, b7;
	m_Cert->GetParameter(a1, a2, a3, a4); // alte Werte retten
	m_Cert->GetName(a5, a6, a7);
	CDlgKeyTutorial* KeyDialog;
	KeyDialog = new CDlgKeyTutorial(this);

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

void CDlgSignTutorial::OnInfoKey() 
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
void CDlgSignTutorial::EnableButtons()
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

void CDlgSignTutorial::OnSelectHashAlg() 
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
			case IDC_RIPEMD160: m_Cert->SetHashAlg(static_cast<CString>("RIPEMD160"));	break;
			default:			m_Cert->SetHashAlg(static_cast<CString>(""));
		}
		EnableButtons();
	}	
	delete HashDialog;	
}



void CDlgSignTutorial::OnCompute() 
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

void CDlgSignTutorial::OnInfoHash() 
{
	if (!m_osHash || m_bUpdateHsh) return;
	
	int srcSize = m_osHash->noctets;
	OctetString msgdata;

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

void CDlgSignTutorial::OnEncrypt() 
{
	if(!m_osHash) return;
	Big C, N, p, D, e;
	if(!m_Cert->GetParameter(N, p, e, D)) return;		
	Big Hash = from_binary(m_osHash->noctets, m_osHash->octets);

	OctetString* osHashAlg;
	osHashAlg = theApp.SecudeLib.e_AlgId(theApp.SecudeLib.md2_aid);
	osHashAlg = theApp.SecudeLib.e_AlgId(theApp.SecudeLib.md2WithRSASignature_aid);
	//osHashAlg = theApp.SecudeLib.e_AlgId(theApp.SecudeLib.md2WithRsa_aid);
	osHashAlg = theApp.SecudeLib.e_AlgId(theApp.SecudeLib.md2WithRsaEncryption_aid);	
	
	/*
	Hash %= N;
	C = pow(Hash, D, N);
	m_osHashEnc.noctets = (bits(N)+7)/8;
	if(m_osHashEnc.octets) delete[] m_osHashEnc.octets;
	m_osHashEnc.octets = new char[m_osHashEnc.noctets];
	to_binary(C, m_osHashEnc.noctets, m_osHashEnc.octets);
	*/
	if(!m_Cert->Sign(m_osHash, &m_osHashEnc)) return;
	
	m_bUpdateEnc = FALSE;
	EnableButtons();
}

void CDlgSignTutorial::OnInfoHashEnc() 
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

void CDlgSignTutorial::OnSelectCert() 
{
	if(!m_Cert->IsInitialized()) return;

	CDlgCertTutorial* CertDialog;
	CertDialog = new CDlgCertTutorial(this);

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

void CDlgSignTutorial::OnInfoAlg() 
{
	if(m_Cert->GetHashAlg().IsEmpty()) return;

	UpdateData(TRUE);
	m_DisplayContent.LoadString(IDS_CONTENT_ALG);
	m_DisplayInfo = m_Cert->GetHashAlg();
	UpdateData(FALSE);
}

void CDlgSignTutorial::OnCombine() 
{
	if(!m_Message->noctets) return;
	if(m_SignText) delete[] m_SignText->octets;
	delete   m_SignText;
	m_SignText = 0;
		
	CString UserKeyId, Buffer;
	m_Cert->GetKeyId(UserKeyId, Buffer);
	m_SignText = PrintSignature(*m_osHashEnc, "RSA", m_Cert->GetHashAlg(),UserKeyId);
}

void CDlgSignTutorial::OnOK() 
{
	if(m_Message && m_Message->noctets)
	{
		char outfile[128];
		CMyDocument* NewDoc;		

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

void CDlgSignTutorial::ClearInfo()
{
	UpdateData(TRUE);
	m_DisplayContent.Empty();
	m_DisplayInfo.Empty();	
	UpdateData(FALSE);
}

void CDlgSignTutorial::OnInfoCert() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	if(!m_Cert->PSEIsInitialized()) return;

	UpdateData(TRUE);
	m_DisplayContent.LoadString(IDS_CONTENT_CERT);
	m_DisplayInfo = m_Cert->GetCert();
	UpdateData(FALSE);
}

void CDlgSignTutorial::OnInfoSign() 
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

