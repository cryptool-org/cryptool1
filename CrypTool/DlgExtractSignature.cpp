// DlgSignExtract.cpp: Implementierungsdatei
//
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic, 2000
//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgExtractSignature.h"
#include "DialogeMessage.h"

#include "AsymmetricEncryption.h"
#include "FileTools.h"
#include "KeyFileHandling.h"
#include "s_ecconv.h"

#include "SecudeLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgExtractSignature 


CDlgExtractSignature::CDlgExtractSignature(char* infile_name, const char *title, CWnd* pParent /*= NULL*/)
	: CDialog(CDlgExtractSignature::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgExtractSignature)
	m_sigButtonGroup = -1;
	m_KeyInfo = _T("");
	m_Signature = _T("");
	m_SignatureLength = _T("");
	m_Message = _T("");
	m_MessageLength = _T("");
	m_InfoAboutSigner = _T("");
	m_SigHashAlg = _T("");
	m_TextSig = _T("");
	m_TextMsg = _T("");
	m_TextSigner = _T("");
	m_TextKey = _T("");
	m_TextAlg = _T("");
	//}}AFX_DATA_INIT

	inFileName = infile_name;
	doctitle = title;

	hexdumpCols = 14;
	base = 10;

	Signatur.signature.bits = NULL;
	message.octets = NULL;
}


void CDlgExtractSignature::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgExtractSignature)
	DDX_Control(pDX, IDC_EDIT12, m_TextAlgCtrl);
	DDX_Control(pDX, IDC_EDIT11, m_TextKeyCtrl);
	DDX_Control(pDX, IDC_EDIT10, m_TextSignerCtrl);
	DDX_Control(pDX, IDC_EDIT3, m_DefEditCtrl);
	DDX_Control(pDX, IDC_EDIT9, m_TextMsgCtrl);
	DDX_Control(pDX, IDC_EDIT8, m_TextSigCtrl);
	DDX_Control(pDX, IDC_EDIT6, m_MessageCtrl);
	DDX_Control(pDX, IDC_EDIT4, m_SignatureCtrl);
	DDX_Control(pDX, IDC_RADIO4, m_RadioHexadezimal);
	DDX_Control(pDX, IDC_RADIO3, m_RadioDezimal);
	DDX_Control(pDX, IDC_RADIO2, m_RadioOktal);
	DDX_Control(pDX, IDC_RADIO1, m_RadioOctets);
	DDX_Radio(pDX, IDC_RADIO1, m_sigButtonGroup);
	DDX_Text(pDX, IDC_EDIT1, m_KeyInfo);
	DDX_Text(pDX, IDC_EDIT4, m_Signature);
	DDX_Text(pDX, IDC_EDIT5, m_SignatureLength);
	DDX_Text(pDX, IDC_EDIT6, m_Message);
	DDX_Text(pDX, IDC_EDIT7, m_MessageLength);
	DDX_Text(pDX, IDC_EDIT3, m_InfoAboutSigner);
	DDX_Text(pDX, IDC_EDIT2, m_SigHashAlg);
	DDX_Text(pDX, IDC_EDIT8, m_TextSig);
	DDX_Text(pDX, IDC_EDIT9, m_TextMsg);
	DDX_Text(pDX, IDC_EDIT10, m_TextSigner);
	DDX_Text(pDX, IDC_EDIT11, m_TextKey);
	DDX_Text(pDX, IDC_EDIT12, m_TextAlg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgExtractSignature, CDialog)
	//{{AFX_MSG_MAP(CDlgExtractSignature)
	ON_BN_CLICKED(IDC_RADIO1, OnRadioOctets)
	ON_BN_CLICKED(IDC_RADIO2, OnRadioOktal)
	ON_BN_CLICKED(IDC_RADIO3, OnRadioDezimal)
	ON_BN_CLICKED(IDC_RADIO4, OnRadioHexadezimal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgExtractSignature 

BOOL CDlgExtractSignature::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zus�tzliche Initialisierung hier einf�gen

	LOGFONT LogFont;
	char DefaultFontName[32];
	LONG defaultFontWeight;
	CFont *defaultFont = m_DefEditCtrl.GetFont();
	defaultFont->GetLogFont( &LogFont ); // Default Systemschrift ermitteln
	strncpy(DefaultFontName, LogFont.lfFaceName, 32); // Default Wert sichern
	defaultFontWeight = LogFont.lfWeight; // Default Wert sichern
	LogFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	Font.CreateFontIndirect( &LogFont ); // Font initialisieren
	m_TextMsgCtrl.SetFont(&Font);
	m_TextSigCtrl.SetFont(&Font);
	m_TextSignerCtrl.SetFont(&Font);
	m_TextKeyCtrl.SetFont(&Font);
	m_TextAlgCtrl.SetFont(&Font);

	LogFont.lfWeight = defaultFontWeight; // Auf default Wert zur�ckstellen
	strncpy(LogFont.lfFaceName, "Courier", 32); // Auf Courier umstellen
	Font2.CreateFontIndirect( &LogFont ); // Font2 initialisieren
    m_MessageCtrl.SetFont(&Font2);
	m_SignatureCtrl.SetFont(&Font2);
	//strncpy(LogFont.lfFaceName, DefaultFontStyle, 32);

	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextSig = (CString) pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNED_MESSAGE,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextMsg = (CString) pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_ORIGINATOR,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextSigner = (CString) pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_USED_KEY,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextKey = (CString) pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_METHOD,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextAlg = (CString) pc_str;
	UpdateData(FALSE);

	int err;

	bool messagefromfile=false; // zeigt an, ob die signierte Nachricht aus einer Datei
	// gelesen werden musste
	CString filename;
				
	CString SigAlg="";
	CString HashAlg="";
	CString UserKeyId="";
	int SignLength; // (Aus dem Ausgabefenster eingelesene) L�nge der Signatur in Bits

	CKeyFile FileHandling;

	SignatureType = GetSignData(inFileName,messagefromfile,filename,&message,SigAlg,HashAlg,UserKeyId,&SignLength,&Signatur,c,d);
	// Folgende Speicherbereiche sind von GetSignData() alloziert worden und
	// m�ssen sp�ter wieder freigegeben werden:
	// message.octets (falls != NULL) 
	// Signatur.signature.bits (falls != NULL)

	if ( (SignatureType > 0) && (SignatureType != EC_SIGN) &&\
		(SignatureType != RSA_OR_DSA_SIGN) && (SignatureType != UNKNOWN_SIGN) )
	{
		// Fehler beim auslesen der Daten (Nicht gen�gend Speicher vorhanden)
		Message(IDS_STRING_ERR_MEMORY_SIGNATURE_VERIFICATION, MB_ICONSTOP);
		if (Signatur.signature.bits) free(Signatur.signature.bits);
		if (message.octets) free(message.octets);
		EndDialog(-1);
		return TRUE;
	}
	else if ((SignatureType != EC_SIGN) && (SignatureType != RSA_OR_DSA_SIGN) &&\
		(SignatureType != UNKNOWN_SIGN))
	{
		// Fehler beim auslesen der Daten (Formatierung der Daten nicht korrekt)
		Message(IDS_STRING_ASYMKEY_COULD_NOT_EXTRACT_SIGNATURE,MB_ICONSTOP);
		if (Signatur.signature.bits) free(Signatur.signature.bits);
		if (message.octets) free(message.octets);
		EndDialog(-2);
		return TRUE;
	}

	if (messagefromfile == true)
	{
		// Die signierte Nachricht ist zu gross und passt nicht komplett
		// in ein CEdit Feld. Es wird lediglich ein erster Teil der Nachricht dargestellt
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNED_MESSAGE_FIRST_PART,pc_str,STR_LAENGE_STRING_TABLE);
		m_TextMsg = (CString) pc_str;
	}

	// �berpr�fe, ob angegebener Schl�sselbezeichner tats�chlich existiert
	bool keyExists = FileHandling.FilenameExisting(UserKeyId);

	char *name=NULL;
	char *firstname=NULL;
	char *keyType=NULL;
	char *keyInfo=NULL;
	char *creattime=NULL;
	char *ctstr=NULL;

	CString kInfo;

	if (keyExists == true)
	{
		err = FileHandling.ExtractData(UserKeyId,&ctstr,&creattime,&name,&firstname,&keyType,&keyInfo);
		if (ctstr) free(ctstr); // wird hier nicht ben�tigt
		if (keyInfo==NULL)
			kInfo="";
		else
			kInfo = ((CString)" (")+((CString)keyInfo)+((CString)") ");

		// Infos �ber den Signaturersteller
		m_InfoAboutSigner = (CString) ((CString)firstname)+((CString)" ")+((CString)name); // Signatur erzeugt von:

		// Infos �ber Schl�ssel
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_DATE,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, pc_str1,((CString)keyType)+kInfo,((CString)creattime));
		m_KeyInfo = (CString) pc_str; // Benutzter Schl�ssel:
	}
	else
	{
		// Schl�sselbezeichner "UserKeyId" existiert nicht
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_UNKNOWN_KEY_IDENTIFIER,pc_str1,STR_LAENGE_STRING_TABLE);
		// pc_str1 = "�bermittelter Schl�sselbezeichner existiert nicht!"
		m_InfoAboutSigner = ((CString)pc_str1);
		// Signaturerzeuger unbekannt
	}

	// �berpr�fe ob angegebener Signatur-/Hashalgorithmus bekannt ist
	if ( (SigAlg!="RSA") && (SigAlg!="DSA") && (SigAlg!="ECSP-NR") && (SigAlg!="ECSP-DSA") )
	{
		// unbekannter Signaturalgorithmus angegeben
		LoadString(AfxGetInstanceHandle(),IDS_STRING_UNKNOWN,pc_str,STR_LAENGE_STRING_TABLE);
		// pc_str = "unbekannt !"
		SigAlg = SigAlg+((CString)" (")+((CString)pc_str)+((CString)")");
	}
	if ( (HashAlg!="MD2") && (HashAlg!="MD5") && (HashAlg!="SHA") && (HashAlg!="SHA-1") &&\
		(HashAlg!="RIPEMD-160") )
	{
		// unbekannter Hashalgorithmus angegeben
		LoadString(AfxGetInstanceHandle(),IDS_STRING_UNKNOWN,pc_str,STR_LAENGE_STRING_TABLE);
		// pc_str = "unbekannt !"
		HashAlg = HashAlg+((CString)" (")+((CString)pc_str)+((CString)")");
	}

	// Benutzter Signaturalgorithmus
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_HASH_FUNCTION,pc_str1,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str, pc_str1, SigAlg, HashAlg);
	m_SigHashAlg = (CString) pc_str;

	UpdateData(FALSE);

	int srcSize;
	int destSize;

	// Signierte Nachricht ausgeben
	if (message.noctets != 0)
	{
		// Nachricht ist kein leerer String
		srcSize = message.noctets;
		destSize = ((srcSize+hexdumpCols-1)/hexdumpCols)*(11+hexdumpCols*4)-hexdumpCols+(srcSize%hexdumpCols)+1;

		char *msgdata = (char *) malloc(destSize+1);

		err = HexDumpMem(msgdata, destSize, (unsigned char *) message.octets, srcSize, hexdumpCols);
		if (err == 0)
		{
			// Fehler
			if (Signatur.signature.bits) free(Signatur.signature.bits);
			if (message.octets) free(message.octets);
			return TRUE;
		}
		CString mData(msgdata);
		m_Message = mData;
		free(msgdata);
	}
	// L�nge der signierten Nachricht
	char buffer[30];
	_itoa( message.noctets, buffer, 10 );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_MESSAGE_LENGTH,pc_str1,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str, pc_str1,((CString)buffer));
	m_MessageLength = (CString) pc_str;
	UpdateData(FALSE);

	if (SignatureType == EC_SIGN)
	{
		//
		CheckRadioButton (IDC_RADIO1, IDC_RADIO4, IDC_RADIO3); UpdateData(TRUE);
		base = 10; // Signatur als Dezimalzahlen darstellen

		int signlength = theApp.SecudeLib.lngtouse(c)+theApp.SecudeLib.lngtouse(d)+2;// Bit-L�nge der Signatur

		char buffer[30];
		_itoa( signlength, buffer, 10 );
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_LENGTH,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, pc_str1,((CString)buffer));
		m_SignatureLength = (CString) pc_str;
		UpdateData(FALSE);

		UpdateSigEditBox();
	}
	else if (SignatureType == RSA_OR_DSA_SIGN)
	{
		//
		CheckRadioButton (IDC_RADIO1, IDC_RADIO4, IDC_RADIO1); UpdateData(TRUE);
		base = -1; // Signatur als Octets darstellen

		srcSize = (Signatur.signature.nbits+7)/8;
		destSize = ((srcSize+hexdumpCols-1)/hexdumpCols)*(11+hexdumpCols*4)-hexdumpCols+(srcSize%hexdumpCols)+1;

		char *sigdata = (char *) malloc(destSize+1);

		err = HexDumpMem(sigdata, destSize, (unsigned char *) Signatur.signature.bits, srcSize, hexdumpCols);
		if (err == 0)
		{
			// Fehler
			if (Signatur.signature.bits) free(Signatur.signature.bits);
			if (message.octets) free(message.octets);
			return TRUE;
		}
		m_Signature = (CString) sigdata; UpdateData(FALSE);
		free(sigdata);
		
		char buffer[30];
		_itoa( Signatur.signature.nbits, buffer, 10 );
		LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_LENGTH,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, pc_str1,((CString)buffer));
		m_SignatureLength = (CString) pc_str;
		UpdateData(FALSE);
	}
	else // (SignatureType == UNKNOWN_SIGN)
	{
		// unbekanntes Signaturverfahren angegeben
		m_RadioOctets.EnableWindow(FALSE);
		m_RadioOktal.EnableWindow(FALSE);
		m_RadioDezimal.EnableWindow(FALSE);
		m_RadioHexadezimal.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

int CDlgExtractSignature::UpdateSigEditBox()
{
	int err;

	char *strC;
	char *strD;
	char *strSig;

	int srcSize;
	int destSize;

	if (SignatureType == EC_SIGN)
	{
		if ( (base == 8) || (base == 10) || (base == 16) )
		{
			// wandele c und d (beides L_NUMBERs) nach Zahlen in Basis "base"

			err = ln_to_string (c, &strC, base); // Dezimalsystem
			if (err)
			{
				// Fehler.
				return -1;
			}
			err = ln_to_string (d, &strD, base); // Dezimalsystem
			if (err)
			{
				// Fehler.
				free(strC);
				return -1;
			}

			if (base == 16) 
			{
				m_Signature = ((CString)"\r\nc = ")+((CString)(strC+2))+((CString)" ");
				m_Signature = m_Signature+((CString)"\r\n\r\nd = ")+((CString)(strD+2))+((CString)" ");
			}
			else
            {
				m_Signature = ((CString)"\r\nc = ")+((CString)strC)+((CString)" ");
				m_Signature = m_Signature+((CString)"\r\n\r\nd = ")+((CString)strD)+((CString)" ");
			}
			UpdateData(FALSE);

			free(strC);
			free(strD);
		}
		else
		{
			// Signatur als Octets darstellen

			OctetString *cOcts = theApp.SecudeLib.aux_LN2OctetString(c, (theApp.SecudeLib.lngtouse(c)+7)/8);
			if (cOcts == NULL)
			{
				// Fehler
				return -2;
			}
			OctetString *dOcts = theApp.SecudeLib.aux_LN2OctetString(d, (theApp.SecudeLib.lngtouse(d)+7)/8);
			if (dOcts == NULL)
			{
				// Fehler
				theApp.SecudeLib.aux_free_OctetString(&cOcts);
				return -2;
			}

			m_Signature = ((CString)"c:\r\n"); UpdateData(FALSE);

			// cOcts als Hexdump ausgeben
			srcSize = cOcts->noctets;
			destSize = ((srcSize+hexdumpCols-1)/hexdumpCols)*(11+hexdumpCols*4)-hexdumpCols+(srcSize%hexdumpCols)+1;

			char *cData = (char *) malloc(destSize+1);

			err = HexDumpMem(cData, destSize, (unsigned char *) cOcts->octets, srcSize, hexdumpCols);
			if (err == 0)
			{
				// Fehler
				theApp.SecudeLib.aux_free_OctetString(&cOcts);
				theApp.SecudeLib.aux_free_OctetString(&dOcts);
				free(cData);
				return -3;
			}
			m_Signature = m_Signature + ((CString)cData) + ((CString)"\r\n\r\n"); UpdateData(FALSE);
			theApp.SecudeLib.aux_free_OctetString(&cOcts);

			m_Signature = m_Signature + ((CString)"d:\r\n"); UpdateData(FALSE);

			// dOcts als Hexdump ausgeben
			srcSize = dOcts->noctets;
			destSize = ((srcSize+hexdumpCols-1)/hexdumpCols)*(11+hexdumpCols*4)-hexdumpCols+(srcSize%hexdumpCols)+1;

			char *dData = (char *) malloc(destSize+1);

			err = HexDumpMem(dData, destSize, (unsigned char *) dOcts->octets, srcSize, hexdumpCols);
			if (err == 0)
			{
				// Fehler
				theApp.SecudeLib.aux_free_OctetString(&dOcts);
				free(dData);
				return -3;
			}
			m_Signature = m_Signature + ((CString)dData);
			UpdateData(FALSE);
			theApp.SecudeLib.aux_free_OctetString(&dOcts);
			free(cData);
			free(dData);
		}
	}
	else if (SignatureType == RSA_OR_DSA_SIGN)
	{
		//BitString *SigBitString = &Signatur.signature;
		//c = theApp.SecudeLib.aux_BitString2LN( (BitString *) SigBitString );
		theApp.SecudeLib.aux_BitString2LN2(c, &Signatur.signature);

		if ( (base == 8) || (base == 10) || (base == 16) )
		{
			// wandele c nach Zahl in Basis "base"

			err = ln_to_string (c, &strSig, base); // Dezimalsystem
			if (err)
			{
				// Fehler.
				return -1;
			}

			if (base == 16) m_Signature = ((CString)"\r\n ")+((CString)(strSig+2))+((CString)" ");
			else            m_Signature = ((CString)"\r\n ")+((CString)strSig)+((CString)" ");
			UpdateData(FALSE);

			free(strSig);
		}
		else
		{
			// Signatur als Octets darstellen

			srcSize = (Signatur.signature.nbits+7)/8;
			destSize = ((srcSize+hexdumpCols-1)/hexdumpCols)*(11+hexdumpCols*4)-hexdumpCols+(srcSize%hexdumpCols)+1;

			char *sigdata = (char *) malloc(destSize+1);
			if (sigdata == NULL)
			{
				//
				return -1;
			}

			err = HexDumpMem(sigdata, destSize, (unsigned char *) Signatur.signature.bits, srcSize, hexdumpCols);
			if (err == 0)
			{
				// Fehler
				free (sigdata);
				return -2;
			}
			m_Signature = (CString) sigdata;
			UpdateData(FALSE);
			
			char buffer[30];
			_itoa( Signatur.signature.nbits, buffer, 10 );
			LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGNATURE_LENGTH,pc_str1,STR_LAENGE_STRING_TABLE);
			sprintf(pc_str, pc_str1,((CString)buffer));
			m_SignatureLength = (CString) pc_str;
			UpdateData(FALSE);
			free(sigdata);
		}
	}

	UpdateData(FALSE);

	return 0;
}

void CDlgExtractSignature::OnOK() 
{
	// TODO: Zus�tzliche Pr�fung hier einf�gen

	if (Signatur.signature.bits) free(Signatur.signature.bits);
	if (message.octets) free(message.octets);
	
	CDialog::OnOK();
}

void CDlgExtractSignature::OnRadioOctets() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen

	UpdateData(TRUE);
	base = -1;
	UpdateSigEditBox();
}

void CDlgExtractSignature::OnRadioOktal() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	
	UpdateData(TRUE);
	base = 8;
	UpdateSigEditBox();	
}

void CDlgExtractSignature::OnRadioDezimal() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen

	UpdateData(TRUE);
	base = 10;
	UpdateSigEditBox();		
}

void CDlgExtractSignature::OnRadioHexadezimal() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen

	UpdateData(TRUE);
	base = 16;
	UpdateSigEditBox();		
}
