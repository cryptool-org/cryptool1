//////////////////////////////////////////////////////////////////////////////////
// Name:      actIHashMacKey.h
// Product:   cv act library
// Purpose:   interface for the class HashMAC
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IHashMACKey_h
#define ACT_IHashMACKey_h

#include "actIMACKey.h"

namespace act
{
	class IHashAlg;

	class IHashMACKey : public IMACKey
	{
	public:
		virtual void SetHash(IHashAlg* cipher) =0;
		virtual const IHashAlg* GetHash() const =0;
		virtual IHashAlg* GetHash() =0;
	};

} // namespace act

#endif

