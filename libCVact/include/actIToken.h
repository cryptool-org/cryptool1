// ---------------------------------------------------------------------------
// Name:      actIToken.h
// Product:   cv act library
// Purpose:   The class IToken implements the profile and the application supported by a token.
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/22/2002
// ---------------------------------------------------------------------------

#ifndef ITOKEN_H
#define ITOKEN_H

#include "actBasics.h"
#include "actBlob.h"

namespace act
{
	class IKey;
	class ITokenPIN;
	class IEMSAAlg;


	enum  TokenType {
		TOKEN_RSA			= 0x01,
		TOKEN_DSA           = 0x02,
		TOKEN_DH            = 0x04,
		TOKEN_ECDSA         = 0x08,
		TOKEN_ECDH			= 0x10,
		TOKEN_SECRET		= 0x80
	};

	enum  KeyType {
		KEY_RSA				= 0x00,
		KEY_DSA             = 0x01,
		KEY_DH              = 0x02,
		KEY_ECDSA           = 0x03,
		KEY_ECDH			= 0x04,
		KEY_SECRET			= 0x10
	};

	enum  TokenStatusCode {
		TOKEN_EMPTY			= 0,
		TOKEN_INITIALIZED	= 1,
		TOKEN_PERSONALIZED	= 2
	};

	enum  CertificateUsage {
		EMPTY_CERT			= 0x0000, 
		SIGN_CERT			= 0x0001, 
		DEC_CERT			= 0x0002, 
		ROOT_CERT			= 0x0004, 
		AUTH_CERT			= 0x0008, 
		CA_CERT				= 0x0010,
		UNSPECIFIED_CERT	= 0xffff
	} ;

	struct CertEntry {
		int usage;
		Blob certblob;
	};


	class IToken
	{
	public:
		virtual void IncReferenceCounter() = 0;
		virtual void Destroy() = 0;

		virtual int GetStatus() const = 0;					// initialized, personalized,...
		virtual int GetType() const = 0;					// KEY_RSA, KEY_ECDSA,...
		virtual const char* GetName() const = 0;
		virtual Blob GetSerialNumber() const = 0;
		virtual Blob GetCardholderName() const = 0;
		virtual IKey* CreateKey(const Blob& cert) const = 0;
		virtual Blob GetRandom(const unsigned long) const = 0;
		virtual void SetSeed(const Blob& seed) = 0;

		// used to generate a new key
		virtual IKey* NewKey(int key_type = KEY_RSA) = 0;											

		// write a certificate (corresponding to a key) to token
		virtual void WriteCertificate(const Blob& cert, const IKey* key = 0) = 0;

		// write/import a (soft) key to token
		virtual IKey* WriteKey(const IKey* key) = 0;

		// Key List
		virtual IKey* GetKey(int pos) const = 0;
		virtual int GetKeyNumber() const = 0;

		// Certificate List
		virtual CertEntry GetCertificate(int pos) const = 0;
		virtual int GetCertificateNumber() const = 0;

		// Pin List
		virtual ITokenPIN* GetPIN(int pos) const = 0;
		virtual int GetPINNumber() const = 0;

		virtual void ResetSecurityState() const = 0;

		virtual void VerifyUserPin(const Blob& pinvalue) = 0;
		virtual void ChangeUserPin(const Blob& oldpin, const Blob& newpin) = 0;
		virtual void UnlockUserPin(const Blob& so_pin, const Blob& new_userpin) = 0;
		virtual void VerifySOPin(const Blob& pinvalue) = 0;
		virtual void ChangeSOPin(const Blob& oldpin, const Blob& newpin) = 0;
		ITokenPIN* GetUserPin() const;
		ITokenPIN* GetSOPin() const;


	protected:
		virtual ~IToken() {}

	};

} // namespace act

#endif


