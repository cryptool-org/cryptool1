//////////////////////////////////////////////////////////////////////////////////
// Name:      actIDerivatorWithHash.h
// Product:   cv act library
// Purpose:   The abstract class IDerivatorWithHash is derived from IDerivator and
//            uses hash algorithms. 
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IDerivatorWithHash_h
#define ACT_IDerivatorWithHash_h

#include "actIDerivator.h"

namespace act
{
	class IHashAlg;

	class IDerivatorWithHash : public IDerivator
	{
	public:
		virtual void SetHash(IHashAlg* hash) =0;
		virtual const IHashAlg* GetHash() const =0;
		virtual IHashAlg* GetHash() =0;
	};
} // namespace act

#endif


