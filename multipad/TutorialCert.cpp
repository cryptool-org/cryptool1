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
: m_HashAlgId(0),
m_NameIsInitialized(FALSE),
m_PSEIsInitialized(FALSE)
{
	memset (&m_Key, 0, sizeof(Key));
	
	//memset (&m_hPSE, 0, sizeof(PSE));
}

CTutorialCert::~CTutorialCert()
{
}

BOOL CTutorialCert::SetName( CString& sName, CString& sFirstName, CString& sKeyId )
{
	sName.TrimLeft();
	sName.TrimRight();
	sFirstName.TrimLeft();
	sFirstName.TrimRight();
	sKeyId.TrimLeft();
	sKeyId.TrimRight();	
	m_sName = sName;
	m_sFirstName = sFirstName;
	m_sKeyId = sKeyId;
	time(&m_lTime);
	m_NameIsInitialized = TRUE;
	m_PSEIsInitialized = FALSE;
	//m_sUserKeyId.Format(IDS_CREATE_USER_KEY_ID2, m_sName, m_sFirstName, TUTORIAL_ALG_NAME, GetBitLength(), m_lTime, m_sKeyId);
	//m_sDisName.Format(IDS_CREATE_DISNAME, m_sFirstName, m_sName, m_lTime);
	
	return TRUE;
}

BOOL CTutorialCert::SetPIN( const CString& sPIN )
{
	if(sPIN.IsEmpty()) return FALSE;
	m_sPIN = sPIN;
	return TRUE;
}

void CTutorialCert::GetName( CString& sName, CString& sFirstName, CString& sKeyId)
{
	sName = m_sName;
	sFirstName = m_sFirstName;
	sKeyId = m_sKeyId;
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

BOOL CTutorialCert::SetPublicKey( CString& sKeyPublic, const int base )
{
	if(TutorialRSA::SetPublicKey( sKeyPublic, base))
	{
		m_sKeyPublic = sKeyPublic;
		return TRUE;
	}
	return FALSE;
}

// Zur dauerhaften Speicherung: RSA-KEY in der PSE ablegen
BOOL CTutorialCert::CreatePSE()
{
	// Reset m_Key
	if(m_Key.private_key)
	{
		if(m_Key.private_key->subjectAI) theApp.SecudeLib.aux_free2_AlgId (m_Key.private_key->subjectAI);
		theApp.SecudeLib.aux_free2_BitString (&m_Key.private_key->subjectkey);
		delete m_Key.private_key;
	}
	if(m_Key.key)
	{
		if(m_Key.key->subjectAI) theApp.SecudeLib.aux_free2_AlgId (m_Key.key->subjectAI);
		theApp.SecudeLib.aux_free2_BitString (&m_Key.key->subjectkey);
		delete m_Key.key;
	}
	memset (&m_Key, 0, sizeof(Key));

	// Init m_Key
	m_Key.private_key = new KeyInfo;
	m_Key.key = new KeyInfo;

	int		keysize;
	KeyBits	keybits;
	// Geheimen Schlüssel nach m_Key.private_key kopieren
	memset (&keybits, 0, sizeof(KeyBits));
	keybits.part1.noctets = (bits(m_bigPrime_p)+7)/8;
	keybits.part1.octets = new char[keybits.part1.noctets];
	keybits.part2.noctets = (bits(m_bigPrime_q)+7)/8;
	keybits.part2.octets = new char[keybits.part2.noctets];
	to_binary(m_bigPrime_p, keybits.part1.noctets, keybits.part1.octets);
	to_binary(m_bigPrime_q, keybits.part2.noctets, keybits.part2.octets);
	m_Key.private_key->subjectkey = *theApp.SecudeLib.e_KeyBits(&keybits);	
	m_Key.private_key->subjectAI = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.rsa_aid);
	keysize = (keybits.part1.noctets + keybits.part2.noctets)*8;
	*reinterpret_cast<int*>(m_Key.private_key->subjectAI->param) = keysize;
	delete[] keybits.part1.octets;
	delete[] keybits.part2.octets;

	// Öffentlichen Schlüssel nach m_Key.key kopieren
	memset(&keybits, 0, sizeof(KeyBits));
	keybits.part1.noctets = (bits(N)+7)/8;
	keybits.part1.octets = new char[keybits.part1.noctets];
	keybits.part2.noctets = (bits(e)+7)/8;
	keybits.part2.octets = new char[keybits.part2.noctets];
	to_binary(N, keybits.part1.noctets, keybits.part1.octets);
	to_binary(e, keybits.part2.noctets, keybits.part2.octets);
	m_Key.key->subjectkey = *theApp.SecudeLib.e_KeyBits(&keybits);
	m_Key.key->subjectAI = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.rsa_aid);
	*reinterpret_cast<int*>(m_Key.key->subjectAI->param) = keysize;
	delete[] keybits.part1.octets;
	delete[] keybits.part2.octets;

	// PSE-File erzeugen und öffnen
	m_sUserKeyId.Format(IDS_CREATE_USER_KEY_ID2, m_sName, m_sFirstName, TUTORIAL_ALG_NAME, GetBitLength(), m_lTime, m_sKeyId);
	m_sPseName.Format(IDS_CREATE_PSE, PseVerzeichnis, m_sUserKeyId);
	m_hPSE = theApp.SecudeLib.af_create(const_cast<char*>(LPCTSTR(m_sPseName)), NULL, const_cast<char*>(LPCTSTR(m_sPIN)), NULL, TRUE);
	if(!m_hPSE)
	{
		// Fehler beim erzeugen der PSE
	}

	// Geheimen Schlüssel in PSE schreiben
	OctetString* osKey;
	PSESel*		 psesel;
	psesel = theApp.SecudeLib.af_get_PSESel(m_hPSE, static_cast<ObjId*>(0) );
	psesel->object = theApp.SecudeLib.aux_cpy_String(SKnew_name);
	psesel->object_type = theApp.SecudeLib.SKnew_oid;
	osKey = theApp.SecudeLib.e_KeyInfo(m_Key.private_key);
	if(theApp.SecudeLib.sec_write_PSE(psesel, osKey))
	{
		// Fehler beim schreiben des Schlüssels in die PSE
		return FALSE;
	}
	theApp.SecudeLib.aux_free_OctetString(&osKey);

	// Initialisierung der Variablen, die zur Zertifizierung notwendig sind
	OctetString osSerial;
	char *string="000001";
	osSerial.noctets=strlen(string);
	osSerial.octets=string;
	m_sDisName.Format(IDS_CREATE_DISNAME, m_sFirstName, m_sName, m_lTime);
	m_DName = theApp.SecudeLib.aux_Name2DName(const_cast<char*>(LPCTSTR(m_sDisName)));
	if(!m_DName)
	{
		// Fehler beim Erzeugen des Distinguished Name
		return FALSE;
	}

	// Prototyp Zertifikat erzeugen
	Certificate* Cert;
	Cert=theApp.SecudeLib.af_create_Certificate(m_hPSE, m_Key.key, theApp.SecudeLib.md5WithRsaEncryption_aid/*m_HashAlgId*/, "SKnew", m_DName, &osSerial, NULL, NULL, TRUE, NULL);
	if (!Cert)
	{
		// Fehler bei der Zertifikatserzeugung
		Message(IDS_STRING_ASYMKEY_ERR_CREATE_CERT_1, MB_ICONSTOP);
		// Lösche die neu angelegte PSE

		// Freigeben von dynamisch angelegtem Speicher

		return FALSE;
	}

	// Make it a X509.v3 certificate
	// Add extensions, in particular store the PSE name in a private extension.
	// This is required if the certificate is exported via PKCS#12 and later
	// imported by another CrypTool
	SEQUENCE_OF_Extension extensions;
	extensions.element = (v3Extension *) theApp.SecudeLib.aux_malloc(sizeof(v3Extension));
	extensions.element->extnId = CrypToolPSEName_OID();
	extensions.element->critical = false;
	extensions.element->extnDERcode = theApp.SecudeLib.e_PrintableString(const_cast<char*>(LPCTSTR(m_sPseName)));
	extensions.next = NULL;
	CertExtensions cert_ext;
	memset (&cert_ext, 0, sizeof(CertExtensions));
	cert_ext.nonSupported = &extensions;
	Cert->tbs->extensions = &cert_ext;

	
	// Öffnen der CA-PSE
	PSE hPSE_CA;
	hPSE_CA = theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
	if (hPSE_CA==NULL)
	{
		// Fehler beim Öffnen der CA-PSE
		Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE, MB_ICONSTOP);
		// Lösche die neu angelegte PSE
		//remove("");
		// Freigeben von dynamisch angelegtem Speicher
		//delete string2;
		//delete string4;
		//delete string7;
		return FALSE;
	}

	// Übergabe des Prototyp-Zertifikates an die CA, die den enthaltenen Schlüssel zertifiziert
	Certificate *Cert_CA;
	Cert_CA=theApp.SecudeLib.af_certify(hPSE_CA, Cert, NULL, theApp.SecudeLib.md5WithRsaEncryption_aid, NULL);
	if (Cert_CA==NULL)
	{
		// Fehler bei der Zertifizierung
		Message(IDS_STRING_ASYMKEY_ERR_CREATE_CERT_2, MB_ICONSTOP);
		// Lösche die neu angelegte PSE
		//remove(string3);
		// Freigeben von dynamisch angelegtem Speicher
		//delete string2;
		//delete string4;
		//delete string7;
		return FALSE;
	}
	
	//Zertifikat in die CA-Datenbank einfügen!!!	
	if (theApp.SecudeLib.af_cadb_add_Certificate (hPSE_CA, SIGNATURE, Cert_CA))
	{
		// Fehler beim Einfügen des Zertifikats in die CA-Datenbank
		Message(IDS_STRING_ASYMKEY_ERR_ADD_CERT, MB_ICONSTOP);
		// Lösche die neu angelegte PSE
		//remove(string3);
		// Freigeben von dynamisch angelegtem Speicher
		//delete string2;
		//delete string4;
		//delete string7;
		theApp.SecudeLib.af_close(hPSE_CA);
		theApp.SecudeLib.aux_free_DName (&m_DName);
		theApp.SecudeLib.af_close(m_hPSE);
		return FALSE;
	}


	// get PKRoot object from CA PSE and copy it to the new PSE
	PKRoot * pkroot;
	pkroot = theApp.SecudeLib.af_pse_get_PKRoot(hPSE_CA);
	if (pkroot)
	{
		if (theApp.SecudeLib.af_pse_update_PKRoot(m_hPSE, pkroot))
		{
			// Error writing certificate to the user PSE
			Message(IDS_STRING_ASYMKEY_ERR_ADD_CERT, MB_ICONSTOP);
			// Lösche die neu angelegte PSE
			//remove(string3);
			// Freigeben von dynamisch angelegtem Speicher
			//delete string2;
			//delete string4;
			//delete string7;
			theApp.SecudeLib.af_close(hPSE_CA);
			theApp.SecudeLib.aux_free_DName (&m_DName);
			theApp.SecudeLib.aux_free_PKRoot(&pkroot);
			theApp.SecudeLib.af_close(m_hPSE);
			return FALSE;
		}
	}
	theApp.SecudeLib.aux_free_PKRoot(&pkroot);
	

	// write certificate to PSE object
	if (theApp.SecudeLib.af_pse_update(m_hPSE, "Cert", Cert_CA, *theApp.SecudeLib.Cert_OID))
	{
		// Error writing certificate to the user PSE
		Message(IDS_STRING_ASYMKEY_ERR_ADD_CERT, MB_ICONSTOP);
		// Lösche die neu angelegte PSE
		//remove(string3);
		// Freigeben von dynamisch angelegtem Speicher
		//delete string2;
		//delete string4;
		//delete string7;
		theApp.SecudeLib.af_close(hPSE_CA);
		theApp.SecudeLib.aux_free_DName (&m_DName);
		theApp.SecudeLib.af_close(m_hPSE);
		return FALSE;
	}
		
	theApp.SecudeLib.af_close(hPSE_CA);
	theApp.SecudeLib.aux_free_DName (&m_DName);
	theApp.SecudeLib.af_close(m_hPSE);
	m_PSEIsInitialized = TRUE;
	// Freigeben von dynamisch angelegtem Speicher

	//delete string2;
	//delete string4;
	//delete string7;
	

	// Eine Sekunde Verzögerung eingebaut, damit time_of_creat: Time in seconds since UTC 1/1/70
	// für verschiedene Schlüssel immer verschieden ist (Wahrung der EINDEUTIGKEIT von UserKeyId)
	Sleep(1000); // wait a second

	// user-information: key pair succesfully created.
	//LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_MSG_STORE_KEYPAIR,pc_str,STR_LAENGE_STRING_TABLE);
	//sprintf(pc_str1, pc_str, m_sUserKeyId);
	//LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KEY_GENERATION_TIME,pc_str,STR_LAENGE_STRING_TABLE);
	//char temp[256];
	//sprintf(temp, pc_str, duration);
	//AfxMessageBox (((CString)pc_str1)+((CString)"\n\n")+temp,MB_ICONINFORMATION);

	/************************************/

	PSE PseHandle;
	PseHandle = theApp.SecudeLib.af_open(const_cast<char*>(LPCTSTR(m_sPseName)), NULL, const_cast<char*>(LPCTSTR(m_sPIN)), NULL);

	return TRUE;	
}

							  
int CTutorialCert::InitParameter(CString& sPrime_p, CString& sPrime_q, int base)
{
	CStringToBig(sPrime_p, m_bigPrime_p, base);
	CStringToBig(sPrime_q, m_bigPrime_q, base);
	return TutorialRSA::InitParameter(m_bigPrime_p, m_bigPrime_q);
}

int CTutorialCert::GetBitLength()
{
	return isInitialized_N? ((bits(N)+7)/8)*8: 0;
}


BOOL CTutorialCert::SetHashAlg(const CString& sHashAlg)
{
	if(sHashAlg=="MD2")
	{
				m_sHashAlg = sHashAlg;
				theApp.SecudeLib.aux_free_AlgId(&m_HashAlgId);
				m_HashAlgId = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.md2WithRsaEncryption_aid);
				return TRUE;
	}
	if(sHashAlg=="MD5")
	{
				m_sHashAlg = sHashAlg;
				theApp.SecudeLib.aux_free_AlgId(&m_HashAlgId);
				m_HashAlgId = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.md5WithRsaEncryption_aid);
				return TRUE;
	}
	if(sHashAlg=="SHA")
	{
				m_sHashAlg = sHashAlg;
				theApp.SecudeLib.aux_free_AlgId(&m_HashAlgId);
				m_HashAlgId = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.shaWithRSASignature_aid);
				return TRUE;
	}
	if(sHashAlg=="SHA-1")
	{
				m_sHashAlg = sHashAlg;
				theApp.SecudeLib.aux_free_AlgId(&m_HashAlgId);
				m_HashAlgId = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.sha1WithRSASignature_aid);
				return TRUE;
	}
	if(sHashAlg=="RIPEMD160")
	{
				m_sHashAlg = sHashAlg;
				theApp.SecudeLib.aux_free_AlgId(&m_HashAlgId);
				m_HashAlgId = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.ripemd160WithRSASignature_aid);
				return TRUE;
	}

	m_sHashAlg.Empty();
	theApp.SecudeLib.aux_free_AlgId(&m_HashAlgId);
	m_HashAlgId = NULL;

	return FALSE;
}

void CTutorialCert::GetKeyId(CString& sUserKeyId, CString& sDisName)
{
	sUserKeyId.Format(IDS_CREATE_USER_KEY_ID2, m_sName, m_sFirstName, TUTORIAL_ALG_NAME, GetBitLength(), m_lTime, m_sKeyId);
	sDisName.Format(IDS_CREATE_DISNAME, m_sFirstName, m_sName, m_lTime);
}

CString CTutorialCert::GetCert()
{
	if (!NameIsInitialized()) return m_sCert;

	PSE hPSE_CA;
	hPSE_CA=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
	if (hPSE_CA==NULL)
	{
		// Fehler beim öffnen der CA-Datenbank
		Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
		// Freigeben von dynamisch angelegtem Speicher

		return m_sCert;
	}

	//Routine für das Holen von Zertifikaten aus der CA-Datenbank
	SET_OF_IssuedCertificate *Cert;
	Cert=theApp.SecudeLib.af_cadb_get_user(hPSE_CA, const_cast<char*>(LPCTSTR(m_sDisName)));
	if (Cert==NULL)
	{
		// Fehler beim lesen des Zertifikats
		char *Fehler=theApp.SecudeLib.LASTTEXT;
		CString Fehler2=Fehler;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_GET_PSE,pc_str,STR_LAENGE_STRING_TABLE);
		CString Fehler3=(CString)pc_str+(CString)Fehler2;
		AfxMessageBox (Fehler3,MB_ICONSTOP);
		// Freigeben von dynamisch angelegtem Speicher
		
		theApp.SecudeLib.af_close(hPSE_CA);
		return m_sCert;
	}
		
	Certificate *Cert2;
	OctetString *osSerial;
	osSerial=Cert->element->serial;
	Cert2=theApp.SecudeLib.af_cadb_get_Certificate(hPSE_CA, osSerial);
	m_sCert=theApp.SecudeLib.aux_sprint_Certificate(hPSE_CA,NULL,Cert2);
	
	theApp.SecudeLib.af_close(hPSE_CA);
	
	return m_sCert;
}


BOOL CTutorialCert::Sign(OctetString* hash, OctetString** sign)
{
	/*
	memset (&keybits, 0, sizeof(KeyBits));
	keybits.part1.noctets = (bits(m_bigPrime_p)+7)/8;
	keybits.part1.octets = new char[keybits.part1.noctets];
	keybits.part2.noctets = (bits(m_bigPrime_q)+7)/8;
	keybits.part2.octets = new char[keybits.part2.noctets];
	to_binary(m_bigPrime_p, keybits.part1.noctets, keybits.part1.octets);
	to_binary(m_bigPrime_q, keybits.part2.noctets, keybits.part2.octets);
	m_Key.private_key->subjectkey = *theApp.SecudeLib.e_KeyBits(&keybits);	
	m_Key.private_key->subjectAI = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.rsa_aid);
	keysize = (keybits.part1.noctets + keybits.part2.noctets)*8;
	*reinterpret_cast<int*>(m_Key.private_key->subjectAI->param) = keysize;
	delete[] keybits.part1.octets;
	delete[] keybits.part2.octets;
	*/
	
	

	if(!IsInitialized()) return FALSE;
	KeyBits	keybits;
	BitString	bitstring;
	//if(!(keybits)) return FALSE;
	
	memset (&bitstring, 0, sizeof(BitString));
	memset (&keybits, 0, sizeof(KeyBits));
	keybits.part1.noctets = (bits(m_bigPrime_p)+7)/8;
	keybits.part1.octets = new char[keybits.part1.noctets];
	keybits.part2.noctets = (bits(m_bigPrime_q)+7)/8;
	keybits.part2.octets = new char[keybits.part2.noctets];
	keybits.choice = 2;
	to_binary(m_bigPrime_p, keybits.part1.noctets, keybits.part1.octets);
	to_binary(m_bigPrime_q, keybits.part2.noctets, keybits.part2.octets);

	bitstring.nbits = (keybits.part1.noctets + keybits.part2.noctets)* 8;
	bitstring.bits = new char[bitstring.nbits];

	if(theApp.SecudeLib.rsa_sign_all(hash, &bitstring, &keybits))
	{
		//delete keybits; 

		return FALSE;
	}
	//delete keybits; 
	if(!(*sign = theApp.SecudeLib.aux_BString2OString(&bitstring)))
	{

		return FALSE;
	}











	return TRUE;
}