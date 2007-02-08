//////////////////////////////////////////////////////////////////////////////////
// Name:      actICBCMACKey.h
// Product:   cv act library
// Purpose:   interface for the class CBCMAC.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_ICBCMACKey_h
#define ACT_ICBCMACKey_h

#include "actIMACKey.h"

namespace act
{
	class IBlockCipher;

	class ICBCMACKey : public IMACKey
	{
	public:
		virtual void SetCipher(IBlockCipher* cipher) =0;
		virtual const IBlockCipher* GetCipher() const =0;
		virtual IBlockCipher* GetCipher() =0;
	};

} // namespace act

#endif

