// TutorialCert.h: Schnittstelle für die Klasse CTutorialCert.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TUTORIALCERT_H__7F7527A3_D4E5_11D5_8A53_000255320F1C__INCLUDED_)
#define AFX_TUTORIALCERT_H__7F7527A3_D4E5_11D5_8A53_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CryptologyUsingMiracl.h"
#include "secure.h"	// Header-File für das SECUDE-Toolkit
#include "af.h"		// Header-File für den SECUDE Authentication Framework

class CTutorialCert : public TutorialRSA  
{
public:
	BOOL isInitialized_Name, isInitialized_FName, isInitialized_PIN;
	CTutorialCert();
	virtual ~CTutorialCert();

	BOOL SetName(CString& sName, CString& sFirstName);
	BOOL SetPIN(CString& sPIN);
	BOOL SetPublicKey ( CString &sKeyPublic, int base = 10 );
	void GetName(CString& sName, CString& sFirstName);
	void GetPrimes( CString &sPrime_p, CString &sPrime_q );
	BOOL GetPublicString( CString &sKeyPublic );
	BOOL InitSecude();
	int InitParameter(CString sPrime_p, CString sPrime_q, int base = 10 );
	int GetBitLength();


protected:
	CString m_sKeyPublic;
	CString m_sName;
	CString m_sFirstName;
	CString m_sPIN;
	Big		m_bigPrime_p;
	Big		m_bigPrime_q;
	// PSE
	PSE		m_hPSE;
	Key		m_Key;
	long	m_lTime;
};

#endif // !defined(AFX_TUTORIALCERT_H__7F7527A3_D4E5_11D5_8A53_000255320F1C__INCLUDED_)
