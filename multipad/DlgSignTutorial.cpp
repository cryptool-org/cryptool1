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
  m_nCols(16)
{
	//{{AFX_DATA_INIT(CDlgSignTutorial)
	m_DisplayInfo = _T("");
	m_DisplayContent = _T("");
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	m_Cert = new CTutorialCert;
	m_NewDoc = 0;
	m_Message = 0;
	m_Signature = 0;
	m_osHash.noctets = 0;
	m_osHash.octets = 0;
	m_osHashEnc.noctets = 0;
	m_osHashEnc.octets = 0;	

	m_bUpdateHsh = TRUE;
	m_bUpdateEnc = TRUE;
	m_bUpdateRsl = TRUE;
}

CDlgSignTutorial::~CDlgSignTutorial()
{
	if(m_Cert) delete m_Cert;
	if(m_osHashEnc.octets) delete[] m_osHashEnc.octets;
	theApp.SecudeLib.aux_free_OctetString(&m_Message);
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
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
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
		if( m_sPathName != doc->GetPathName() )
		{
			m_bUpdateHsh = TRUE;
			m_bUpdateEnc = TRUE;
			m_bUpdateRsl = TRUE;
			m_sFileName = doc->GetFileName(); // Titel setzen
			m_sPathName = doc->GetPathName(); // Pfadnamen setzen
		}		
		if( !doc->GetFileName().IsEmpty() )
		{   // Dateiinhalt in die Variable m_Message einlesen
			theApp.SecudeLib.aux_free_OctetString(&m_Message);
			m_Message=theApp.SecudeLib.aux_file2OctetString(m_sPathName);
		}
	}	
	delete doc;

	EnableButtons(); // Bitmap-Butttons ein/ausblenden
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
	if (m_Message->noctets)
	{
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
}

void CDlgSignTutorial::OnSelectKey() 
{
	CString a1, a2, a3, a4, a5, a6, b1, b2, b3, b4, b5, b6;
	m_Cert->GetParameter(a1, a2, a3, a4); // alte Werte retten
	m_Cert->GetName(a5, a6);
	CDlgKeyTutorial* KeyDialog;
	KeyDialog = new CDlgKeyTutorial(this);

	KeyDialog->InitRSA(m_Cert);
	if(KeyDialog->DoModal()==IDOK) 
	{
		m_Cert->GetParameter(b1, b2, b3, b4);
		m_Cert->GetName(b5, b6);
		if(a1 != b1 || a2 != b2 || a3 != b3 || a4 != b4)
		{
			m_bUpdateEnc = TRUE;
			m_bUpdateRsl = TRUE;
		}
		if(a5 != b5 || a6 != b6) 
		{
			m_bUpdateRsl = TRUE;
		}
	}

	delete KeyDialog;

	EnableButtons();
}

void CDlgSignTutorial::OnInfoKey() 
{
	CString sName, sFirstName, sKeyID, sModN, sPhiN, sKeyPublic, sKeyPrivate, sOutput;
	m_Cert->GetParameter(sModN, sPhiN,sKeyPublic,sKeyPrivate);
	m_Cert->GetName(sName, sFirstName);
	UpdateData(TRUE);
	m_DisplayContent.LoadString(IDS_CONTENT_KEY);

	// AUSGABE
	sOutput.Format(IDS_NAME2, sFirstName, sName);
	m_DisplayInfo = sOutput;
	//sOutput.Format(IDS_KEY_IDENTIFIER2, sKeyID);
	//m_DisplayInfo += sOutput;
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
	if( m_osHash.octets && !m_bUpdateHsh )
	{}
	else
	{}

	// Info  verschlüsselter Hashwert
	if( m_osHashEnc.octets && !m_bUpdateEnc )
	{}
	else
	{}

	/*
	// Info signiertes Dokument
	if( && !m_bUpdateHsh && !m_bUpdateEnc && !m_bUpdateRsl)
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
	if( m_Cert->IsInitialized() && m_osHash.noctets && !m_bUpdateHsh )
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
		m_bUpdateRsl = TRUE;
		m_nIDHash = HashDialog->GetHashID();
		switch( m_nIDHash ) 
		{
			case IDC_MD2:		m_sHashAlg = "MD2";			break;
			case IDC_MD4:		m_sHashAlg = "MD4";			break;
			case IDC_MD5:		m_sHashAlg = "MD5";			break;
			case IDC_SHA:		m_sHashAlg = "SHA";			break;
			case IDC_SHA_1:		m_sHashAlg = "SHA-1";		break;
			case IDC_RIPEMD160: m_sHashAlg = "RIPEMD160";	break;
			default:			m_sHashAlg.Empty();
		}
	}
	
	delete HashDialog;

	EnableButtons();
}



void CDlgSignTutorial::OnCompute() 
{
	m_osHash.noctets = 0;
   
	if(!m_sPathName.IsEmpty())
	{
		switch (m_nIDHash)
		{
			case IDC_MD2:
				theApp.SecudeLib.sec_hash_all(m_Message, &m_osHash, theApp.SecudeLib.md2_aid, NULL);
				break;
			case IDC_MD4:
				theApp.SecudeLib.sec_hash_all(m_Message,&m_osHash,theApp.SecudeLib.md4_aid,NULL);
				break;
			case IDC_MD5:
				theApp.SecudeLib.sec_hash_all(m_Message,&m_osHash,theApp.SecudeLib.md5_aid,NULL);
				break;
			case IDC_SHA:
				theApp.SecudeLib.sec_hash_all(m_Message,&m_osHash,theApp.SecudeLib.sha_aid,NULL);
				break;
			case IDC_SHA_1:
				theApp.SecudeLib.sec_hash_all(m_Message,&m_osHash,theApp.SecudeLib.sha1_aid,NULL);
				break;
			case IDC_RIPEMD160:
				theApp.SecudeLib.sec_hash_all(m_Message,&m_osHash,theApp.SecudeLib.ripemd160_aid,NULL);
				break;
		}
		m_bUpdateHsh = FALSE;
		EnableButtons();	
	}	
}

void CDlgSignTutorial::OnInfoHash() 
{
	if (m_osHash.noctets)
	{
		int srcSize = m_osHash.noctets;
		OctetString msgdata;

		if (!HexDumpOct(msgdata, m_osHash, m_nCols))
		{
			//FEHLER
		}
		
		UpdateData(TRUE);
		m_DisplayInfo = static_cast<CString>(msgdata.octets);
		m_DisplayContent.Format(IDS_STRING_HASH_VALUE_OF, m_sHashAlg, m_sFileName);
		UpdateData(FALSE);

		delete[] msgdata.octets;
	}
}

void CDlgSignTutorial::OnEncrypt() 
{
	CString sN, sD, sC, sp, se, test;
	m_Cert->GetParameter(sN, sp, se, sD);
	Big Hash = from_binary(m_osHash.noctets, m_osHash.octets);
	Big C, N, D;
	CStringToBig (sN, N, 10);
	CStringToBig (sD, D, 10);
	
	if(m_Cert->IsInitialized())
	{
		Hash %= N;
		C = pow(Hash, D, N);
		m_osHashEnc.noctets = (bits(N)/8)+1;
		if(m_osHashEnc.octets) delete[] m_osHashEnc.octets;
		m_osHashEnc.octets = new char[m_osHashEnc.noctets];
		to_binary(C, m_osHashEnc.noctets, m_osHashEnc.octets);
	}

	m_bUpdateEnc = FALSE;
	EnableButtons();
}

void CDlgSignTutorial::OnInfoHashEnc() 
{
	if (m_osHashEnc.noctets)
	{
		int srcSize = m_osHashEnc.noctets;
		int destSize = (srcSize+m_nCols-1)/m_nCols * (11+m_nCols*4) - (srcSize % m_nCols? m_nCols - srcSize % m_nCols: 0);

	
		char *msgdata = new char[destSize+1];

		if (!HexDumpMem(msgdata, destSize, reinterpret_cast<unsigned char*>(m_osHashEnc.octets), srcSize, m_nCols))
		{
			//FEHLER
		}
		
		UpdateData(TRUE);
		m_DisplayInfo = static_cast<CString>(msgdata);
		m_DisplayContent.Format(IDS_STRING_HASH_VALUE_OF, m_sHashAlg, m_sFileName);
		UpdateData(FALSE);	
		
		delete[] msgdata;
	}
}

void CDlgSignTutorial::OnSelectCert() 
{
	CDlgCertTutorial* CertDialog;
	CertDialog = new CDlgCertTutorial(this);

	CertDialog->InitRSA(m_Cert);
	if(CertDialog->DoModal()==IDOK) 
	{
		
	}

	delete CertDialog;

	EnableButtons();	
}

void CDlgSignTutorial::OnInfoAlg() 
{
	UpdateData(TRUE);
	m_DisplayContent.LoadString(IDS_CONTENT_ALG);
	m_DisplayInfo = m_sHashAlg;
	UpdateData(FALSE);
}

void CDlgSignTutorial::OnCombine() 
{
	if(m_Message->noctets)
	{
		/*
		char outfile[128];
		WINDOWPLACEMENT place;
		CWnd* CWnd_hilf;
		BOOL NotFirst(FALSE);

		if(m_NewDoc)
		{
			// Älters Signiertes Dokument ersetzen
			CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
			CWnd_hilf->GetWindowPlacement( &place );
			m_NewDoc->SetModifiedFlag(FALSE);
			m_NewDoc->OnCloseDocument();
			m_NewDoc = 0;
			NotFirst = TRUE;
		}

		GetTmpName(outfile,"cry",".hex");

		// Signatur erstellen:
		theApp.SecudeLib.aux_OctetString2file(m_Message,outfile,2);


		m_NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
		remove(outfile);
		m_sFileNameNew.Format(IDS_RSA_SIGNATURE_OF, m_sHashAlg, m_sFileName);
		m_NewDoc->SetTitle(m_sFileNameNew);
		if(NotFirst)
		{
			// Position des Vorgängerdokuments zuweisen
			CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
			CWnd_hilf->SetWindowPlacement( &place );
		}
		*/		
	}
}

void CDlgSignTutorial::OnOK() 
{
	if(m_Message && m_Message->noctets)
	{
		char outfile[128];
		CMyDocument* NewDoc;		

		// Signatur erstellen:
		GetTmpName(outfile,"cry",".hex");
		theApp.SecudeLib.aux_OctetString2file(m_Message,outfile,2);
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
		remove(outfile);
		m_sFileNameNew.Format(IDS_RSA_SIGNATURE_OF, m_sHashAlg, m_sFileName);
		NewDoc->SetTitle(m_sFileNameNew);
	}
	
	CDialog::OnOK();
}
