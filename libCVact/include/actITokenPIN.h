// ---------------------------------------------------------------------------
// Name:      actITokenPIN.h
// Product:   cv act library
// Purpose:   The class ITokenPIN defines the interfaces of the PIN operations
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  04/05/2002
// ---------------------------------------------------------------------------

#ifndef ITOKENPIN_H
#define ITOKENPIN_H

#include "actBasics.h"
#include "actBlob.h"

namespace act
{
	enum PINType {SO_PIN = 1, USER_PIN = 2};

	enum KeyUsage {			// usuage of key, pin
		KEY_EMPTY		= 0x0000,
		SIGN_DATA		= 0x0001,
		DEC_DATA		= 0x0002,
		AGREE_KEY		= 0x0004,
		AUTH_DATA		= 0x0008,
		BLOCKCIPHER_KEY	= 0x0010,
//		VERIFY_DATA		= 0x0010,
//		ENCRYPT_DATA	= 0x0020,
		UNLOCK_PIN		= 0x0100,
		UPDATE_BINARY	= 0x0200,
		DELETE_BINARY	= 0x0400,
		ALL_USAGE		= 0xffff
	} ;


	class ITokenPIN
	{
	public:

		virtual ~ITokenPIN() {}

		virtual ITokenPIN* Clone() const = 0;

		virtual const char* GetName() const = 0;
		virtual int GetUsage() const = 0;
		virtual int GetType() const = 0;

		virtual bool IsPinInited() const = 0;
		virtual bool CheckPinLength(const Blob &pin) const = 0;

		virtual void VerifyPin(const Blob &pin) const = 0;
		virtual void ChangePin(const Blob &oldpin, const Blob &newpin) const = 0;
		virtual void UnlockPin(const ITokenPIN* so, const Blob &so_pin, const Blob &newpin) const = 0;
		virtual void SetPINValue(const ITokenPIN* so, const Blob &so_pin, const Blob &newpin) const = 0;

	};

} // namespace act

#endif



