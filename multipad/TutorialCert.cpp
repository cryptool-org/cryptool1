// TutorialCert.cpp: Implementierung der Klasse CTutorialCert.
//
//////////////////////////////////////////////////////////////////////
#include <time.h>
#include "stdafx.h"
#include "stdafx.h"
#include "TutorialCert.h"
#include "CryptologyUsingMiracl.h"
#include "DlgAsymKeyCreat.h"
#include "secure.h"	// Header-File für das SECUDE-Toolkit
#include "af.h"		// Header-File für den SECUDE Authentication Framework
#include "multipad.h"
#include "crypt.h"
#include "secudetools.h"

extern char *CaPseDatei, *CaPseVerzeichnis, *Pfad, *PseVerzeichnis; // aus multipad.cpp

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
#define TUTORIAL_KEY_ID "TUTORIAL"
#define TUTORIAL_ALG_NAME "RSA"

CTutorialCert::CTutorialCert()
{
}

CTutorialCert::~CTutorialCert()
{
}

BOOL CTutorialCert::SetName( CString& sName, CString& sFirstName )
{
	if(sName.IsEmpty()) return FALSE;
	if(sFirstName.IsEmpty()) return FALSE;
	m_sName = sName;
	m_sFirstName = sFirstName;
	return TRUE;
}

BOOL CTutorialCert::SetPIN( CString& sPIN )
{
	if(sPIN.IsEmpty()) return FALSE;
	m_sPIN = sPIN;
	return TRUE;
}

void CTutorialCert::GetName( CString& sName, CString& sFirstName)
{
	sName = m_sName;
	sFirstName = m_sFirstName;
}

void CTutorialCert::GetPrimes( CString &sPrime_p, CString &sPrime_q )
{
	CString tanga;
	BigToCString (m_bigPrime_p, tanga);
	sPrime_p = tanga;
	BigToCString (m_bigPrime_q, tanga);
	sPrime_q = tanga;
}

BOOL CTutorialCert::GetPublicString( CString &sKeyPublic )
{
	if(TutorialRSA::SetPublicKey( m_sKeyPublic ))
	{
		sKeyPublic = m_sKeyPublic;
		return TRUE;
	}
	return FALSE;
}

BOOL CTutorialCert::SetPublicKey( CString &sKeyPublic, int base )
{
	if(TutorialRSA::SetPublicKey( sKeyPublic, base))
	{
		m_sKeyPublic = sKeyPublic;
		return TRUE;
	}
	return FALSE;
}

// Zur dauerhaften Speicherung: RSA-KEY in der PSE ablegen
BOOL CTutorialCert::InitSecude()
{
	KeyBits		kbSecret;
	KeyBits		kbPublic;
	KeyInfo		kiSecret;
	KeyInfo		kiPublic;
	BitString*  bsSecret;
	BitString*  bsPublic;
	PSE			m_hPSE;
	CString		sPseName;
	CString		sUserKeyId;
	char*		szPin;
	char*		szPseName;
	OctetString* osKey;
	int			fehler;
	
	/*		
		// Generate RSA key pair
		Algorithmus = theApp.SecudeLib.md5WithRsaEncryption_aid;
		verfahren = RSA_KEYFILE_IDSTRING;
		keyBits = m_rsa_modul_str; // used keysize as string
	*/


	// Initialisierung
	memset(&kiSecret, 0, sizeof(KeyInfo));
	memset(&kbSecret, 0, sizeof(KeyBits));
	memset(&kiPublic, 0, sizeof(KeyInfo));
	memset(&kbPublic, 0, sizeof(KeyBits));

	// Allokation
	kbSecret.part1.noctets = bits(m_bigPrime_p)/8+1;
	kbSecret.part1.octets = new char[kbSecret.part1.noctets];
	kbSecret.part2.noctets = bits(m_bigPrime_q)/8+1;
	kbSecret.part2.octets = new char[kbSecret.part2.noctets];
	kbPublic.part1.noctets = bits(N)/8+1;
	kbPublic.part1.octets = new char[kbPublic.part1.noctets];
	kbPublic.part2.noctets = bits(e)/8+1;
	kbPublic.part2.octets = new char[kbPublic.part2.noctets];

	// GEHEIMEN SCHLÜSSEL KONVERTIEREN IN 3 SCHRITTEN
	// 1.Schritt: Konvertierung von Big p und Big q nach KeyBits
	ASSERT(static_cast<unsigned>(to_binary(m_bigPrime_p, kbSecret.part1.noctets, kbSecret.part1.octets))==kbSecret.part1.noctets);
	ASSERT(static_cast<unsigned>(to_binary(m_bigPrime_q, kbSecret.part2.noctets, kbSecret.part2.octets))==kbSecret.part2.noctets);
	kbSecret.choice = 2;	
	// 2.Schritt: Konvertierung von KeyBits nach KeyInfo (ASN.1 Format)
	kiSecret.subjectAI = theApp.SecudeLib.rsa_aid; // RSA Algorithmus-ID
	ASSERT(bsSecret = theApp.SecudeLib.e_KeyBits(&kbSecret));
	kiSecret.subjectkey = *bsSecret;
	// 3.Schritt: Konvertierung von KeyInfo nach OctetString
	ASSERT(osKey = theApp.SecudeLib.e_KeyInfo( &kiSecret ));

	// ÖFFENTLICHEN SCHLÜSSEL KONVERTIEREN IN 2 SCHRITTEN
	// 1.Schritt: Konvertierung von Big N und Big e nach KeyBits
	ASSERT(static_cast<unsigned>(to_binary(N, kbPublic.part1.noctets, kbPublic.part1.octets))==kbPublic.part1.noctets);
	ASSERT(static_cast<unsigned>(to_binary(e, kbPublic.part2.noctets, kbPublic.part2.octets))==kbPublic.part2.noctets);
	kbPublic.choice = 2;
	// 2.Schritt: Konvertierung von KeyBits nach KeyInfo (ASN.1 Format)
	kiPublic.subjectAI = theApp.SecudeLib.rsa_aid; // RSA Algorithmus-ID
	ASSERT(bsPublic = theApp.SecudeLib.e_KeyBits(&kbPublic));
	kiPublic.subjectkey = *bsPublic;

	// PSE-Namen erstellen
	sUserKeyId.Format(IDS_CREATE_USER_KEY_ID2, m_sName, m_sFirstName, TUTORIAL_ALG_NAME, GetBitLength(), time(&m_lTime), TUTORIAL_KEY_ID);
	sPseName.Format(IDS_CREATE_PSE, PseVerzeichnis, sUserKeyId);
	szPseName = new char[sPseName.GetLength()+1];
	strcpy(szPseName, LPCTSTR(sPseName));

	// PSE-File erzeugen und öffnen
	szPin = new char[m_sPIN.GetLength()+1];
	strcpy(szPin, LPCTSTR(m_sPIN));
	ASSERT(m_hPSE = theApp.SecudeLib.af_create(szPseName, NULL, szPin, NULL, TRUE));

	/*
	m_Key.alg = theApp.SecudeLib.rsa_aid;
	m_Key.key_size = GetBitLength();
	m_Key.key=NULL;
	m_Key.pse_sel=NULL;
	m_Key.add_object=NULL;
	m_Key.add_object_type=NULL;
	m_Key.private_key=NULL;
	ASSERT(!theApp.SecudeLib.af_gen_key (m_hPSE, &m_Key, SIGNATURE, 1));
	*/

	// Schlüssel-Objekt-ID finden
	m_hPSE->psesel->object = "SKnew"; 
	m_hPSE->psesel->object_type = theApp.SecudeLib.af_get_objoid(m_hPSE->psesel->object);
	// Privaten Schlüssel in die PSE schreiben
	fehler = theApp.SecudeLib.sec_write_PSE (m_hPSE->psesel, osKey);

	
	OctetString* os1;
	fehler = theApp.SecudeLib.sec_read(m_hPSE->psesel, os1);
	KeyInfo* ki1= theApp.SecudeLib.d_KeyInfo(os1);
	

	/*
	
	// Öffentlichen Schlüssel ersetzen
	theApp.SecudeLib.aux_free_KeyInfo(&(m_Key.key));
	m_Key.key = &kiPublic;
	*/
	
	// Zertifikat
	CString sDisName;
	DName*	dname;
	sDisName.Format(IDS_CREATE_DISNAME, m_sFirstName, m_sName, m_lTime);
	char*	szDName = new char[sDisName.GetLength()+1];
	strcpy(szDName, LPCTSTR(sDisName));

	ASSERT(dname = theApp.SecudeLib.aux_Name2DName(szDName));
	

	/*
	OctetString osSerial;
	char *string="000001";
	osSerial.noctets=strlen(string);
	osSerial.octets = new char[osSerial.noctets];
	strcpy(osSerial.octets, string);
	*/
	

	Certificate* Cert;
	//ASSERT(Cert=theApp.SecudeLib.af_create_Certificate( m_hPSE, m_Key.key, theApp.SecudeLib.md5WithRsaEncryption_aid, "SKnew", dname, &osSerial, NULL, NULL, TRUE, NULL));
	/*
	// Make it a X509.v3 certificate
	// Add extensions, in particular store the PSE name in a private extension.
	// This is required if the certificate is exported via PKCS#12 and later
	// imported by another CrypTool

	// get PSE name
	LPTSTR UserKeyId_str= new TCHAR[sUserKeyId.GetLength()+1];
	_tcscpy(UserKeyId_str, sUserKeyId);

	SEQUENCE_OF_Extension extensions;
	extensions.element = (v3Extension *) theApp.SecudeLib.aux_malloc(sizeof(v3Extension));
	extensions.element->extnId = CrypToolPSEName_OID();
	extensions.element->critical = false;
	extensions.element->extnDERcode = theApp.SecudeLib.e_PrintableString((char *) UserKeyId_str);
	extensions.next = NULL;
	delete [] UserKeyId_str;

	CertExtensions cert_ext;
	memset (&cert_ext, 0, sizeof(CertExtensions));
	cert_ext.nonSupported = &extensions;

	Cert->tbs->extensions = &cert_ext;

	PSE hPSE_CA;
	ASSERT(hPSE_CA=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL));
	Certificate* Cert2;
	ASSERT(Cert2=theApp.SecudeLib.af_certify(hPSE_CA, Cert, NULL, theApp.SecudeLib.md5WithRsaEncryption_aid, NULL));

	//Zertifikat in die CA-Datenbank einfügen!!!
	ASSERT(!theApp.SecudeLib.af_cadb_add_Certificate (hPSE_CA, SIGNATURE, Cert2));

	PKRoot* pkroot;
	VERIFY(pkroot = theApp.SecudeLib.af_pse_get_PKRoot(hPSE_CA));
	if(pkroot)
	{
		ASSERT(!theApp.SecudeLib.af_pse_update_PKRoot(m_hPSE, pkroot));
	}
	theApp.SecudeLib.aux_free_PKRoot(&pkroot);
	
	ASSERT(!theApp.SecudeLib.af_pse_update(m_hPSE, "Cert", Cert2, *theApp.SecudeLib.Cert_OID));


	/*
	AlgId* Algorithmus = theApp.SecudeLib.md5WithRsaEncryption_aid;
	m_Key.alg = theApp.SecudeLib.rsa_aid;
	m_Key.key_size = 512; // used keysize as int
	char* verfahren = RSA_KEYFILE_IDSTRING;
	char* keyBits = "512"; // used keysize as string
	*/

	// Delokation
	theApp.SecudeLib.sec_close(m_hPSE->psesel);
	//theApp.SecudeLib.af_close(hPSE_CA);
	theApp.SecudeLib.aux_free_DName(&dname); 
	//theApp.SecudeLib.aux_free_BitString(&bsSecret); 
	//theApp.SecudeLib.aux_free_OctetString(&osKey);
	//delete[] kbSecret.part1.octets;
	//delete[] kbSecret.part2.octets;
	delete[] szPin;
	delete[] szPseName;
	delete[] szDName;

	return TRUE;
}

							  
int CTutorialCert::InitParameter(CString sPrime_p, CString sPrime_q, int base)
{
	CStringToBig(sPrime_p, m_bigPrime_p, base);
	CStringToBig(sPrime_q, m_bigPrime_q, base);
	return TutorialRSA::InitParameter(m_bigPrime_p, m_bigPrime_q);
}

int CTutorialCert::GetBitLength()
{
	int b2;
	int bl;
	if(isInitialized_N)
	{
	b2 = bits(N);
	bl = (int) ceil(double(bits(N))/8.0)*8;
	}
	//return isInitialized_N? (int) ceil(double(bits(N))/8.0)*8: 0;
	return bl;
}
