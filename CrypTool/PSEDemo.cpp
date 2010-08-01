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


// TutorialCert.cpp: Implementierung der Klasse CPSEDemo.
//
//////////////////////////////////////////////////////////////////////
#include <time.h>
#include "stdafx.h"
#include "stdafx.h"
#include "PSEDemo.h"
#include "IntegerArithmetic.h"
#include "DlgKeyAsymGeneration.h"
#include "secudelib.h"
#include "secure.h"	// Header-File für das SECUDE-Toolkit
#include "af.h"		// Header-File für den SECUDE Authentication Framework
#include "CrypToolApp.h"
#include "Cryptography.h"
#include "secudetools.h"
#include "DlgRSADecryption.h"
#include "DialogeMessage.h"

extern char *CaPseDatei, *CaPseVerzeichnis, *Pfad, *PseVerzeichnis; // aus multipad.cpp

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define TUTORIAL_KEY_ID "TUTORIAL"
#define TUTORIAL_ALG_NAME "RSA"

#pragma warning ( disable : 4305 4309 )  
const char DER_MD2[]	   = {0x30, 0x20, 0x30, 0x0c, 0x06, 0x08, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x02, 0x02, 0x05, 0x00, 0x04, 0x10};
const char DER_MD5[]	   = {0x30, 0x20, 0x30, 0x0c, 0x06, 0x08, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x02, 0x05, 0x05, 0x00, 0x04, 0x10};
const char DER_SHA[]	   = {0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2B, 0x0E, 0x03, 0x02, 0x12, 0x05, 0x00, 0x04, 0x14};
const char DER_SHA1[]	   = {0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2b, 0x0e, 0x03, 0x02, 0x1a, 0x05, 0x00, 0x04, 0x14};
const char DER_RIPEMD160[] = {0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2b, 0x24, 0x03, 0x02, 0x01, 0x05, 0x00, 0x04, 0x14};
#pragma warning ( default : 4305 4309 ) 
const int  DER_MD2_SIZE = 18;
const int  DER_MD5_SIZE = 18;
const int  DER_SHA_SIZE = 15;
const int  DER_SHA1_SIZE = 15;
const int  DER_RIPEMD160_SIZE = 15;

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


CPSEDemo::CPSEDemo()
: m_HashAlgId(0),
m_NameIsInitialized(FALSE),
m_PSEIsInitialized(FALSE),
m_lTime(0)
{
	//memset(&m_Key, 0, sizeof(Key));
	//AccessPSE("111", "C:/develop/CrypTool/source/CrypTool/Debug/PSE/[KEY][TEST][RSA-304][1015236527][].pse");
	memset(&m_DER_Encoding, 0, sizeof(OctetString));
	
	//memset (&m_hPSE, 0, sizeof(PSE));

	
}

CPSEDemo::~CPSEDemo()
{
}

BOOL CPSEDemo::SetName( CString& sName, CString& sFirstName, CString& sKeyId )
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
	//time(&m_lTime);
	m_NameIsInitialized = TRUE;
	m_PSEIsInitialized = FALSE;
	//m_sUserKeyId.Format(IDS_CREATE_USER_KEY_ID2, m_sName, m_sFirstName, TUTORIAL_ALG_NAME, GetBitLength(), m_lTime, m_sKeyId);
	//m_sDisName.Format(IDS_CREATE_DISNAME, m_sFirstName, m_sName, m_lTime);
	
	return TRUE;
}

BOOL CPSEDemo::SetPIN( const CString& sPIN )
{
	m_sPIN = sPIN;
	if(sPIN.IsEmpty()) return FALSE;
	return TRUE;
}

void CPSEDemo::GetName( CString& sName, CString& sFirstName, CString& sKeyId)
{
	sName = m_sName;
	sFirstName = m_sFirstName;
	sKeyId = m_sKeyId;
}

void CPSEDemo::GetPrimes( CString &sPrime_p, CString &sPrime_q )
{
	CString tanga;
	BigToCString (m_bigPrime_p, tanga);
	sPrime_p = tanga;
	BigToCString (m_bigPrime_q, tanga);
	sPrime_q = tanga;
}

BOOL CPSEDemo::GetPublicString( CString &sKeyPublic )
{
	if(CRSADemo::SetPublicKey( m_sKeyPublic ))
	{
		sKeyPublic = m_sKeyPublic;
		return TRUE;
	}
	return FALSE;
}

BOOL CPSEDemo::SetPublicKey( CString& sKeyPublic, const int base )
{
	if(CRSADemo::SetPublicKey( sKeyPublic, base))
	{
		m_sKeyPublic = sKeyPublic;
		return TRUE;
	}
	return FALSE;
}

// Zur dauerhaften Speicherung: RSA-KEY in der PSE ablegen
BOOL CPSEDemo::CreatePSE()
{
	

	int fehler;
	KeyBits	keybits;

	KeyInfo keyinfo;
	PSE_Sel* psesel;
	BitString* bitstring;
	OctetString* octetstring;


	// Geheimen Schlüssel kopieren
	memset (&keybits, 0, sizeof(KeyBits));
	keybits.part1.noctets = (bits(m_bigPrime_p)+7)/8;
	keybits.part1.octets = new char[keybits.part1.noctets];
	keybits.part2.noctets = (bits(m_bigPrime_q)+7)/8;
	keybits.part2.octets = new char[keybits.part2.noctets];
	to_binary(m_bigPrime_p, keybits.part1.noctets, keybits.part1.octets);
	to_binary(m_bigPrime_q, keybits.part2.noctets, keybits.part2.octets);
	bitstring = theApp.SecudeLib.e_KeyBits(&keybits);
	delete[] keybits.part1.octets;
	delete[] keybits.part2.octets;
	fehler = theApp.SecudeLib.aux_cpy2_BitString(&keyinfo.subjectkey, bitstring);
	theApp.SecudeLib.aux_free_BitString(&bitstring);
	keyinfo.subjectAI = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.rsa_aid);
	*reinterpret_cast<int*>(keyinfo.subjectAI->param) = (keybits.part1.noctets + keybits.part2.noctets)*8;

	// PSE-File erzeugen und öffnen
	m_sUserKeyId = CreateUserKeyID();
	m_sPseName.Format(IDS_CREATE_PSE, PseVerzeichnis, m_sUserKeyId);
	m_hPSE = theApp.SecudeLib.af_create(const_cast<char*>(LPCTSTR(m_sPseName)), NULL, const_cast<char*>(LPCTSTR(m_sPIN)), NULL, TRUE);
	if(!m_hPSE)
	{
		// Fehler beim erzeugen der PSE
		theApp.SecudeLib.ErrorMessage(IDS_STRING_ASYMKEY_ERR_CREATE_PSE, m_hPSE);
		return FALSE;
	}

	// Geheimen Schlüssel in PSE schreiben
	psesel = theApp.SecudeLib.af_get_PSESel(m_hPSE, static_cast<ObjId*>(0) );
	if (!psesel) {
		theApp.SecudeLib.ErrorMessage(IDS_STRING_ASYMKEY_ERR_CREATE_PSE, m_hPSE);
		return FALSE;
	}
	psesel->object = theApp.SecudeLib.aux_cpy_String(SKnew_name);
	psesel->object_type = theApp.SecudeLib.SKnew_oid;
	octetstring = theApp.SecudeLib.e_KeyInfo(&keyinfo);
	theApp.SecudeLib.aux_free2_KeyInfo(&keyinfo);
	if(theApp.SecudeLib.sec_write_PSE(psesel, octetstring))
	{
		// Fehler beim schreiben des Schlüssels in die PSE
		theApp.SecudeLib.ErrorMessage(IDS_STRING_ASYMKEY_ERR_CREATE_PSE, m_hPSE);
		theApp.SecudeLib.aux_free_OctetString(&octetstring);
		return FALSE;
	}
	theApp.SecudeLib.aux_free_OctetString(&octetstring);

	// Initialisierung der Variablen, die zur Zertifizierung notwendig sind
	OctetString osSerial;
	char *string="000001";
	osSerial.noctets=strlen(string);
	osSerial.octets=string;
	m_sDisName = CreateDisName();
	m_DName = theApp.SecudeLib.aux_Name2DName(const_cast<char*>(LPCTSTR(m_sDisName)));
	if(!m_DName)
	{
		// Fehler beim Erzeugen des Distinguished Name
		return FALSE;
	}
	// Öffentlichen Schlüssel  kopieren
	memset(&keybits, 0, sizeof(KeyBits));
	keybits.part1.noctets = (bits(N)+7)/8;
	keybits.part1.octets = new char[keybits.part1.noctets];
	keybits.part2.noctets = (bits(e)+7)/8;
	keybits.part2.octets = new char[keybits.part2.noctets];
	to_binary(N, keybits.part1.noctets, keybits.part1.octets);
	to_binary(e, keybits.part2.noctets, keybits.part2.octets);
	bitstring = theApp.SecudeLib.e_KeyBits(&keybits);
	delete[] keybits.part1.octets;
	delete[] keybits.part2.octets;
	fehler = theApp.SecudeLib.aux_cpy2_BitString(&keyinfo.subjectkey, bitstring);
	theApp.SecudeLib.aux_free_BitString(&bitstring);
	keyinfo.subjectAI = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.rsa_aid);

	// Prototyp Zertifikat erzeugen
	Certificate* Cert;
	Cert=theApp.SecudeLib.af_create_Certificate(m_hPSE, &keyinfo, theApp.SecudeLib.sha1WithRSASignature_aid /* theApp.SecudeLib.md5WithRsaEncryption_aid m_HashAlgId*/, "SKnew", m_DName, &osSerial, NULL, NULL, TRUE, NULL);
	if (!Cert)
	{
		// Fehler bei der Zertifikatserzeugung
		Message(IDS_STRING_ASYMKEY_ERR_CREATE_CERT_1, MB_ICONSTOP); /*FIXME*/
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
		Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE, MB_ICONSTOP); /*FIXME*/
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
	Cert_CA=theApp.SecudeLib.af_certify(hPSE_CA, Cert, NULL, theApp.SecudeLib.sha1WithRSASignature_aid /* theApp.SecudeLib.md5WithRsaEncryption_aid */, NULL);
	if (Cert_CA==NULL)
	{
		// Fehler bei der Zertifizierung
		Message(IDS_STRING_ASYMKEY_ERR_CREATE_CERT_2, MB_ICONSTOP); /*FIXME*/
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
		Message(IDS_STRING_ASYMKEY_ERR_ADD_CERT, MB_ICONSTOP); /*FIXME*/
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
			Message(IDS_STRING_ASYMKEY_ERR_ADD_CERT, MB_ICONSTOP); /*FIXME*/
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
		Message(IDS_STRING_ASYMKEY_ERR_ADD_CERT, MB_ICONSTOP); /*FIXME*/
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

	/*
	PSE PseHandle;
	PseHandle = theApp.SecudeLib.af_open(const_cast<char*>(LPCTSTR(m_sPseName)), NULL, const_cast<char*>(LPCTSTR(m_sPIN)), NULL);
	theApp.SecudeLib.af_close (PseHandle);
	*/

	return TRUE;	
}

							  
int CPSEDemo::InitParameter(CString& sPrime_p, CString& sPrime_q, int base)
{
	CStringToBig(sPrime_p, m_bigPrime_p, base);
	CStringToBig(sPrime_q, m_bigPrime_q, base);
	return CRSADemo::InitParameter(m_bigPrime_p, m_bigPrime_q);
}

int CPSEDemo::GetBitLength()
{
	return isInitialized_N? ((bits(N)+7)/8)*8: 0;
}


BOOL CPSEDemo::SetHashAlg(const CString& sHashAlg)
{
	if(sHashAlg=="MD2")
	{
				m_sHashAlg = sHashAlg;
				theApp.SecudeLib.aux_free_AlgId(&m_HashAlgId);
				m_HashAlgId = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.md2WithRsaEncryption_aid);
				return TRUE;
	} 
	else if(sHashAlg=="MD5")
	{
				m_sHashAlg = sHashAlg;
				theApp.SecudeLib.aux_free_AlgId(&m_HashAlgId);
				m_HashAlgId = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.md5WithRsaEncryption_aid);
				return TRUE;
	} 
	else if(sHashAlg=="SHA")
	{
				m_sHashAlg = sHashAlg;
				theApp.SecudeLib.aux_free_AlgId(&m_HashAlgId);
				m_HashAlgId = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.shaWithRSASignature_aid);
				return TRUE;
	}
	else if(sHashAlg=="SHA-1")
	{
				m_sHashAlg = sHashAlg;
				theApp.SecudeLib.aux_free_AlgId(&m_HashAlgId);
				m_HashAlgId = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.sha1WithRSASignature_aid);
				return TRUE;
	} 
	else if(sHashAlg=="RIPEMD-160")
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

CString CPSEDemo::CreateUserKeyID(const CString& sName, const CString& sFirstName, const CString& sKeyID, const time_t lTime)
{
	CString sUserKeyId;
	CString Name = sName;
	CString FirstName = sFirstName;
	CString KeyID = sKeyID;
	Name.TrimLeft();
	Name.TrimRight();
	FirstName.TrimLeft();
	FirstName.TrimRight();
	KeyID.TrimLeft();
	KeyID.TrimRight();
	sUserKeyId.Format(KeyID.IsEmpty()? IDS_CREATE_USER_KEY_ID1: IDS_CREATE_USER_KEY_ID2, Name, FirstName, TUTORIAL_ALG_NAME, GetBitLength(), lTime, sKeyID);
	return sUserKeyId;
}

CString CPSEDemo::CreateDisName(const CString& sName, const CString& sFirstName, const time_t lTime)
{
	CString sDisName;
	CString Name = sName;
	CString FirstName = sFirstName;
	Name.TrimLeft();
	Name.TrimRight();
	FirstName.TrimLeft();
	FirstName.TrimRight();
	sDisName.Format("CN=%s %s [%I64i], %s", FirstName, Name, lTime, DN_SUFFIX);
	return sDisName;
}

CString CPSEDemo::GetCert()
{
	if (!NameIsInitialized()) return m_sCert;

	PSE hPSE_CA;
	hPSE_CA=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
	if (hPSE_CA==NULL)
	{
		// Fehler beim öffnen der CA-Datenbank
		Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT); /*FIXME*/
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
	m_sCert=sprint_Certificate_with_key(hPSE_CA,NULL,Cert2);
	
	theApp.SecudeLib.af_close(hPSE_CA);
	
	return m_sCert;
}


BOOL CPSEDemo::Encode(const OctetString& hash, OctetString& sign)
{

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

	sign.noctets = (bits(N)-1)/8;
	sign.octets = new char[sign.noctets];
	if(!EMSA_PKCS1_v1_5_ENCODE(sign, hash)) return FALSE;


	return TRUE;
}


BOOL CPSEDemo::EMSA_PKCS1_v1_5_ENCODE(OctetString& EM, const OctetString& H)
{

	delete[] m_DER_Encoding.octets;
	memset(&m_DER_Encoding, 0, sizeof(OctetString));
	unsigned i;
	
	GetDER_Encoding(m_DER_Encoding);
	if(!m_DER_Encoding.noctets) return FALSE;

	if(EM.noctets < m_DER_Encoding.noctets+10) return FALSE;

	unsigned int PSsize = EM.noctets - m_DER_Encoding.noctets - H.noctets - 2;
	char* EMptr = EM.octets;

	#pragma warning ( disable : 4305 4309 ) 
	*EMptr = 0x01; EMptr++;	
	for(; EMptr <= EM.octets+PSsize; EMptr++) *EMptr = 0xff;
	*EMptr = 0x00; EMptr++;	
	for(i=0; i < m_DER_Encoding.noctets; i++, EMptr++) *EMptr = m_DER_Encoding.octets[i];
	for(i=0; i < H.noctets; i++, EMptr++) *EMptr = H.octets[i];
	#pragma warning ( default : 4305 4309 ) 

	return TRUE;
}


void CPSEDemo::HashAll(const OctetString& osMessage, OctetString& osHash)
{
	if(m_sHashAlg == "MD2") theApp.SecudeLib.sec_hash_all(const_cast<OctetString*>(&osMessage), &osHash, theApp.SecudeLib.md2_aid, NULL);
	else if(m_sHashAlg == "MD5") theApp.SecudeLib.sec_hash_all(const_cast<OctetString*>(&osMessage), &osHash, theApp.SecudeLib.md5_aid, NULL);
	else if(m_sHashAlg == "SHA") theApp.SecudeLib.sec_hash_all(const_cast<OctetString*>(&osMessage), &osHash, theApp.SecudeLib.sha_aid, NULL);
	else if(m_sHashAlg == "SHA-1") theApp.SecudeLib.sec_hash_all(const_cast<OctetString*>(&osMessage), &osHash, theApp.SecudeLib.sha1_aid, NULL);
	else if(m_sHashAlg == "RIPEMD-160") theApp.SecudeLib.sec_hash_all(const_cast<OctetString*>(&osMessage), &osHash, theApp.SecudeLib.ripemd160_aid, NULL);
	else memset(&osHash, 0, sizeof(OctetString));
}



void CPSEDemo::GetDER_Encoding(OctetString& DER_Encoding, const CString& sHashAlg)
{
	unsigned int i;
	if(sHashAlg=="MD2")
	{
		DER_Encoding.noctets = DER_MD2_SIZE;
		DER_Encoding.octets = new char[DER_Encoding.noctets];
		for(i=0; i<DER_Encoding.noctets; i++) DER_Encoding.octets[i] = DER_MD2[i];
	} 
	else if(sHashAlg=="MD5")
	{
		DER_Encoding.noctets = DER_MD5_SIZE;
		DER_Encoding.octets = new char[DER_Encoding.noctets];
		for(i=0; i<DER_Encoding.noctets; i++) DER_Encoding.octets[i] = DER_MD5[i];
	} 
	else if(sHashAlg=="SHA")
	{
			DER_Encoding.noctets = DER_SHA_SIZE;
		DER_Encoding.octets = new char[DER_Encoding.noctets];
		for(i=0; i<DER_Encoding.noctets; i++) DER_Encoding.octets[i] = DER_SHA[i];
	}
	else if(sHashAlg=="SHA-1")
	{
		DER_Encoding.noctets = DER_SHA1_SIZE;
		DER_Encoding.octets = new char[DER_Encoding.noctets];
		for(i=0; i<DER_Encoding.noctets; i++) DER_Encoding.octets[i] = DER_SHA1[i];
	} 
	else if(sHashAlg=="RIPEMD-160")
	{
		DER_Encoding.noctets = DER_RIPEMD160_SIZE;
		DER_Encoding.octets = new char[DER_Encoding.noctets];
		for(i=0; i<DER_Encoding.noctets; i++) DER_Encoding.octets[i] = DER_RIPEMD160[i];
	}
	else memset(&DER_Encoding, 0, sizeof(OctetString));
}

int CPSEDemo::GetHashLength(const CString& sHashAlg)
{
	if(sHashAlg=="MD2") return 128;
	if(sHashAlg=="MD5") return 128;
	if(sHashAlg=="SHA")  return 160;
	if(sHashAlg=="SHA-1")  return 160;
	if(sHashAlg=="RIPEMD-160")  return 160;
	return 0;
}

BOOL CPSEDemo::AccessPSE(const CString& sPIN, const CString& sPseName)
{
	KeyInfo* keyinfo;
	KeyBits* keybits;
	PSE_Sel* psesel;
	OctetString octetstring;	
	Certificate* cert;
	int	fehler;

	psesel = theApp.SecudeLib.sec_open(const_cast<char*>(LPCTSTR(sPseName)), const_cast<char*>(LPCTSTR(sPIN)), NULL);
	
	psesel->object = theApp.SecudeLib.aux_cpy_String(SKnew_name);
	psesel->object_type = theApp.SecudeLib.aux_cpy_ObjId(theApp.SecudeLib.SKnew_oid);
	fehler = theApp.SecudeLib.sec_read_PSE(psesel, &octetstring);
	keyinfo = theApp.SecudeLib.d_KeyInfo(&octetstring);
	keybits = theApp.SecudeLib.d_KeyBits(&keyinfo->subjectkey);
	m_bigPrime_p = from_binary(keybits->part1.noctets, keybits->part1.octets);
	m_bigPrime_q = from_binary(keybits->part2.noctets, keybits->part2.octets);	
	theApp.SecudeLib.aux_free_KeyInfo(&keyinfo);
	theApp.SecudeLib.aux_free2_OctetString(&octetstring);
	theApp.SecudeLib.aux_free_KeyBits(&keybits);
	theApp.SecudeLib.aux_free_String(&psesel->object);
	theApp.SecudeLib.aux_free_ObjId(&psesel->object_type);
	
	psesel->object = theApp.SecudeLib.aux_cpy_String(Cert_name);
	psesel->object_type = theApp.SecudeLib.aux_cpy_ObjId(theApp.SecudeLib.Cert_oid);
	fehler = theApp.SecudeLib.sec_read_PSE(psesel, &octetstring);
	cert = theApp.SecudeLib.d_Certificate(&octetstring);
	m_sDisName = theApp.SecudeLib.aux_DName2Name(cert->tbs->subject);
	keybits = theApp.SecudeLib.d_KeyBits(&cert->tbs->subjectPK->subjectkey);
	e = from_binary(keybits->part2.noctets, keybits->part2.octets);
	BigToCString(e, m_sKeyPublic);
	theApp.SecudeLib.aux_free_KeyBits(&keybits);
	theApp.SecudeLib.aux_free_String(&psesel->object);
	theApp.SecudeLib.aux_free_ObjId(&psesel->object_type);
	theApp.SecudeLib.aux_free_Certificate(&cert);

	fehler = theApp.SecudeLib.sec_close(psesel);

	CRSADemo::InitParameter(m_bigPrime_p, m_bigPrime_q);
	CRSADemo::SetPublicKey(e);
	m_PSEIsInitialized = CRSADemo::SetPrivateKey();	

	return m_PSEIsInitialized;
}

BOOL CPSEDemo::AccessPSE_DLG()
{
	CDlgRSADecryption DlgPSE;

	DlgPSE.m_sDialogText.LoadString(IDS_ACCESS_PSE);
	DlgPSE.m_sCancelText.LoadString(IDS_CANCEL);
	DlgPSE.m_sOKText.LoadString(IDS_IMPORT);
	DlgPSE.m_bHideDuration = TRUE;
	if(DlgPSE.DoModal()==IDOK)
	{
		SetName(DlgPSE.Name, DlgPSE.Firstname, DlgPSE.KeyInfo);
		SetTime(DlgPSE.CreatTime);
		SetPIN(DlgPSE.m_PinCode);
		m_sUserKeyId = DlgPSE.UserKeyId;
		m_sPseName.Format(IDS_CREATE_PSE, PseVerzeichnis, m_sUserKeyId);
		return TestAccess() && AccessPSE();
	}
	return FALSE;
}

BOOL CPSEDemo::TestAccess()
{
		// Öffnen der PSE des Absenders (Siganturerstellers) - nur um Gültigkeit der PIN zu überprüfen
		PSE PseHandle;
		PseHandle = theApp.SecudeLib.af_open(const_cast<char*>(LPCTSTR(m_sPseName)), NULL, const_cast<char*>(LPCTSTR(m_sPIN)), NULL);
		if (!PseHandle)
		{
			if (theApp.SecudeLib.LASTERROR==EPIN)
			{
				// falsche PIN-Nummer benutzt
				Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);
				return FALSE;
			}
			// sonstige Fehler beim öffnen der PSE
			Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			return FALSE;
		}
		theApp.SecudeLib.af_close (PseHandle);
		return TRUE;
}

void CPSEDemo::getRSAPrivateKey(CString &privatekey)
{
   char *privateKeyTemp = new char[4934]; // FIXME HK: MEMORY FOR DECIMAL STRING REPRESENTATION UP to 16K RSA MODULI
	privateKeyTemp << d;
	privatekey = privateKeyTemp;
   delete []privateKeyTemp;
}
