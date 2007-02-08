//////////////////////////////////////////////////////////////////////////////////
// Name:      actIStreamCipherKey.h
// Product:   cv act library
// Purpose:   The class IStreamCipherKey extends the interface of the class IKey
//            and supports the peculiarities of symmetric keys.  
//
//
// Copyright: (c) 2001 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IStreamCipherKey_h
#define ACT_IStreamCipherKey_h

#include "actIKey.h"

namespace act
{
	class IStreamCipher;
	class IDerivator;

	class IStreamCipherKey : public IKey
	{
	public:

		virtual void SetCipher(IStreamCipher* cipher) =0;
		virtual const IStreamCipher* GetCipher() const =0;
		virtual IStreamCipher* GetCipher() =0;

		virtual void SetDerivator(IDerivator* derive) =0;
		virtual const IDerivator* GetDerivator() const =0;
		virtual IDerivator* GetDerivator()  =0;
	};
} //namespace act
#endif

