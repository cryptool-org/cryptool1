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
	PSE				m_hPSE;
	CString			sPseName;
	CString			sUserKeyId;
	char*			szPin;
	char*			szPseName;
	PSESel*			psesel;

	KeyBits			kbSecret;
	KeyInfo			kiSecret;
	BitString*		bsSecret;
	OctetString*	osSecret;

	KeyBits			kbPublic;
	KeyInfo			kiPublic;
	BitString*		bsPublic;

	int*			keysize;

	int				fehler;
	int				pBit, qBit, NBit, eBit;
	pBit = bits(m_bigPrime_p);
	qBit = bits(m_bigPrime_q);
	NBit = bits(N);
	eBit = bits(e);

	// PSE-Namen erstellen
	sUserKeyId.Format(IDS_CREATE_USER_KEY_ID2, m_sName, m_sFirstName, TUTORIAL_ALG_NAME, GetBitLength(), time(&m_lTime), TUTORIAL_KEY_ID);
	sPseName.Format(IDS_CREATE_PSE, PseVerzeichnis, sUserKeyId);
	szPseName = new char[sPseName.GetLength()+1];
	strcpy(szPseName, LPCTSTR(sPseName));

	// PSE-File erzeugen und öffnen
	szPin = new char[m_sPIN.GetLength()+1];
	strcpy(szPin, LPCTSTR(m_sPIN));
	ASSERT(m_hPSE = theApp.SecudeLib.af_create(szPseName, NULL, szPin, NULL, TRUE));


	memset(&kbSecret, 0, sizeof(KeyBits));
	kbSecret.part1.noctets = (bits(m_bigPrime_p)+7)/8;
	kbSecret.part1.octets = new char[kbSecret.part1.noctets];
	kbSecret.part2.noctets = (bits(m_bigPrime_q)+7)/8;
	kbSecret.part2.octets = new char[kbSecret.part2.noctets];
	ASSERT(static_cast<unsigned>(to_binary(m_bigPrime_p, kbSecret.part1.noctets, kbSecret.part1.octets))==kbSecret.part1.noctets);
	ASSERT(static_cast<unsigned>(to_binary(m_bigPrime_q, kbSecret.part2.noctets, kbSecret.part2.octets))==kbSecret.part2.noctets);

	bsSecret = theApp.SecudeLib.e_KeyBits(&kbSecret);

	memset(&kiSecret, 0, sizeof(KeyInfo));
	kiSecret.subjectkey.nbits = bsSecret->nbits;
	kiSecret.subjectkey.bits = bsSecret->bits;
	bsSecret->bits = NULL;	
	kiSecret.subjectAI = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.rsa_aid);
	keysize = reinterpret_cast<int*>(kiSecret.subjectAI->param);
	*keysize = (kbSecret.part1.noctets + kbSecret.part2.noctets)*8;

	//(reinterpret_cast<int*>(kiSecret.subjectAI->param))* = kbSecret.part1.noctets + kbSecret.part2.noctets;

	// write private key to PSE
	psesel = theApp.SecudeLib.af_get_PSESel(m_hPSE, static_cast<ObjId*>(0) );
	psesel->object = theApp.SecudeLib.aux_cpy_String(SKnew_name);
	psesel->object_type = theApp.SecudeLib.SKnew_oid;
	osSecret = theApp.SecudeLib.e_KeyInfo(&kiSecret);
	fehler = theApp.SecudeLib.sec_write_PSE(psesel, osSecret);
	theApp.SecudeLib.aux_free_OctetString(&osSecret);
	
	
	// Initialisierung der Variablen, die zur Zertifizierung notwendig sind
	OctetString osSerial;
	char *string="000001";
	osSerial.noctets=strlen(string);
	osSerial.octets=string;

	CString sDisName;
	DName*	dname;
	sDisName.Format(IDS_CREATE_DISNAME, m_sFirstName, m_sName, m_lTime);
	LPTSTR	szDName = new TCHAR[sDisName.GetLength()+1];
	_tcscpy(szDName, LPCTSTR(sDisName));
	ASSERT(dname = theApp.SecudeLib.aux_Name2DName(szDName));

	memset(&kbPublic, 0, sizeof(KeyBits));
	kbPublic.part1.noctets = (bits(N)+7)/8;
	kbPublic.part1.octets = new char[kbPublic.part1.noctets];
	kbPublic.part2.noctets = (bits(e)+7)/8;
	kbPublic.part2.octets = new char[kbPublic.part2.noctets];
	ASSERT(static_cast<unsigned>(to_binary(N, kbPublic.part1.noctets, kbPublic.part1.octets))==kbPublic.part1.noctets);
	ASSERT(static_cast<unsigned>(to_binary(e, kbPublic.part2.noctets, kbPublic.part2.octets))==kbPublic.part2.noctets);

	bsPublic = theApp.SecudeLib.e_KeyBits(&kbPublic);

	memset(&kiPublic, 0, sizeof(KeyInfo));
	kiPublic.subjectkey.nbits = bsPublic->nbits;
	kiPublic.subjectkey.bits = bsPublic->bits;
	bsPublic->bits = NULL;
	kiPublic.subjectAI = theApp.SecudeLib.aux_cpy_AlgId (theApp.SecudeLib.rsa_aid);
	keysize = reinterpret_cast<int*>(kiPublic.subjectAI->param);
	*keysize = (kbSecret.part1.noctets + kbSecret.part2.noctets)*8;

	Certificate* Cert;
	ASSERT(Cert=theApp.SecudeLib.af_create_Certificate(m_hPSE, &kiPublic, theApp.SecudeLib.md5WithRsaEncryption_aid, "SKnew", dname, &osSerial, NULL, NULL, TRUE, NULL));


	fehler = theApp.SecudeLib.af_close(m_hPSE);

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
