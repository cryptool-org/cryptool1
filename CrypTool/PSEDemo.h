/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


// TutorialCert.h: Schnittstelle f�r die Klasse CRSADemo.
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
#include "asn1.h"
#include "secure.h"	// Header-File f�r das SECUDE-Toolkit
#include "af.h"		// Header-File f�r den SECUDE Authentication Framework


/////////////////////////////////////////////////////////////////////////////
extern const char DER_MD2[];
extern const char DER_MD5[];
extern const char DER_SHA[];
extern const char DER_SHA1[];
extern const char DER_RIPEMD160[];
extern const int  DER_MD2_SIZE;
extern const int  DER_MD5_SIZE;
extern const int  DER_SHA_SIZE;
extern const int  DER_SHA1_SIZE;
extern const int  DER_RIPEMD160_SIZE;
/////////////////////////////////////////////////////////////////////////////


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
	BOOL AccessPSE(){ return AccessPSE(m_sPIN, m_sPseName);}
	BOOL AccessPSE(const CString& sPIN, const CString& sPseName);
	BOOL AccessPSE_DLG();
	void SetTime(){time(&m_lTime);}
	void SetTime(const CString& sTime){m_lTime = atol(sTime);}
	void SetTime(const long lTime){m_lTime = lTime;}
	long GetTime(){return m_lTime;}
	CString CreateUserKeyID(const CString& sName, const CString& sFirstName, const CString& sKeyID, const long lTime);
	CString CreateUserKeyID(){return CreateUserKeyID(m_sName, m_sFirstName, m_sKeyId, m_lTime);}
	CString CreateDisName(const CString& sName, const CString& sFirstName, const long lTime);
	CString CreateDisName(){return CreateDisName(m_sName, m_sFirstName, m_lTime);}
	void getRSAPrivateKey(CString&);

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
	//Key		m_Key;
	CString m_sHashAlg;
	AlgId*  m_HashAlgId;
	DName*  m_DName;
	long	m_lTime;

private:
	BOOL EMSA_PKCS1_v1_5_ENCODE( OctetString& EM, const OctetString& H);
	BOOL TestAccess();
};

#endif // !defined(AFX_TUTORIALCERT_H__7F7527A3_D4E5_11D5_8A53_000255320F1C__INCLUDED_)
