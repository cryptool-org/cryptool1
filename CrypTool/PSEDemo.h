// TutorialCert.h: Schnittstelle für die Klasse CRSADemo.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_TUTORIALCERT_H__7F7527A3_D4E5_11D5_8A53_000255320F1C__INCLUDED_)
//#define AFX_TUTORIALCERT_H__7F7527A3_D4E5_11D5_8A53_000255320F1C__INCLUDED_
#ifndef _MS_TUTORIALCERT_H_
#define _MS_TUTORIALCERT_H_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#include "IntegerArithmetic.h"
#include "secure.h"	// Header-File für das SECUDE-Toolkit
#include "af.h"		// Header-File für den SECUDE Authentication Framework


class CPSEDemo : public CRSADemo  
{
public:
	CPSEDemo();
	virtual ~CPSEDemo();

	BOOL SetName(CString& sName, CString& sFirstName, CString& sKeyId);
	void GetName(CString& sName, CString& sFirstName, CString& sKeyId);
	BOOL SetHashAlg(const CString& sHashAlg);
	CString GetHashAlg(){return m_sHashAlg;}
	BOOL SetPIN(const CString& sPIN);
	BOOL CheckPIN(const CString& sPIN){return m_sPIN == sPIN;}
	CString GetPIN(){return m_sPIN; }
	BOOL SetPublicKey ( CString &sKeyPublic, const int base = 10 );
	void GetPrimes( CString &sPrime_p, CString &sPrime_q );
	BOOL GetPublicString( CString &sKeyPublic );
	BOOL CreatePSE();
	CString GetCert();
	void GetKeyId(CString& sUserKeyId, CString& sDisName);
	int InitParameter(CString& sPrime_p, CString& sPrime_q, int base = 10 );
	int GetBitLength();
	BOOL NameIsInitialized(){return m_NameIsInitialized;}
	BOOL PSEIsInitialized(){return m_PSEIsInitialized;}
	BOOL Encode(const OctetString& hash, OctetString& sign);
	void HashAll(const OctetString& osMessage, OctetString& osHash);
	void GetDER_Encoding(OctetString& DER_Encoding){GetDER_Encoding(DER_Encoding, m_sHashAlg);}
	void GetDER_Encoding(OctetString& DER_Encoding, const CString& sHashAlg);
	int  GetHashLength(){return GetHashLength(m_sHashAlg);}
	int  GetHashLength(const CString& sHashAlg);
	BOOL AccessPSE(){ return AccessPSE(m_sPIN, m_sPseName); }
	BOOL AccessPSE(const CString& sPIN, const CString& sPseName);
	BOOL AccessPSE_DLG();


protected:
	CString m_sKeyPublic;
	CString m_sName;
	CString m_sFirstName;
	CString m_sPIN;
	CString m_sCert;
	Big		m_bigPrime_p;
	Big		m_bigPrime_q;
	BOOL	m_NameIsInitialized;
	BOOL	m_PSEIsInitialized;
	OctetString m_DER_Encoding;
	// PSE
	CString	m_sPseName;
	CString	m_sUserKeyId;
	CString m_sKeyId;
	CString m_sDisName;
	PSE		m_hPSE;
	Key		m_Key;
	CString m_sHashAlg;
	AlgId*  m_HashAlgId;
	DName*  m_DName;
	long	m_lTime;

private:
	BOOL EMSA_PKCS1_v1_5_ENCODE( OctetString& EM, const OctetString& H);
};

#endif // !defined(AFX_TUTORIALCERT_H__7F7527A3_D4E5_11D5_8A53_000255320F1C__INCLUDED_)
