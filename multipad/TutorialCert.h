// TutorialCert.h: Schnittstelle für die Klasse CTutorialCert.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_TUTORIALCERT_H__7F7527A3_D4E5_11D5_8A53_000255320F1C__INCLUDED_)
//#define AFX_TUTORIALCERT_H__7F7527A3_D4E5_11D5_8A53_000255320F1C__INCLUDED_
#ifndef _MS_TUTORIALCERT_H_
#define _MS_TUTORIALCERT_H_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#include "CryptologyUsingMiracl.h"
#include "secure.h"	// Header-File für das SECUDE-Toolkit
#include "af.h"		// Header-File für den SECUDE Authentication Framework


class CTutorialCert : public TutorialRSA  
{
public:
	CTutorialCert();
	virtual ~CTutorialCert();

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
	BOOL Sign(OctetString* hash, OctetString** sign);



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
};

#endif // !defined(AFX_TUTORIALCERT_H__7F7527A3_D4E5_11D5_8A53_000255320F1C__INCLUDED_)
