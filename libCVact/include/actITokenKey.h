//////////////////////////////////////////////////////////////////////////////////
// Name:      actITokenKey.h
// Product:   cv act library
// Purpose:   The interface ITokenKey enables access to a key stored in a secure token.
//
// Copyright: (c) 2003 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_ITokenKey_h
#define ACT_ITokenKey_h

#include "actISignatureKey.h"
#include "actBlob.h"
#include "actITokenPIN.h"

namespace act
{
	class ITokenKey : public ISignatureKey
	{
	public:

		virtual Blob GetCertificate() const = 0;
		virtual IKey* GetPublicKey() const = 0;

		virtual void VerifyPin(const Blob& pinvalue)  const= 0; 
		virtual void SetPin(const ITokenPIN* pin) = 0;
		virtual const ITokenPIN* GetPin() const = 0;

	};
}
#endif

