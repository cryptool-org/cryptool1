//////////////////////////////////////////////////////////////////////////////////
// Name:      actIRSAKey.h
// Product:   cv act library
// Purpose:   IRSAKey is the interface for the class IRSAKey enabling access to
//            the aggregated padding-object of an RSAKeys.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IRSAKey_h
#define ACT_IRSAKey_h

#include "actISignatureKey.h"

namespace act
{
	class IPadding;

	class IRSAKey : public ISignatureKey
	{
	public:
		virtual void SetPadding(IPadding* padding) =0;
		virtual const IPadding* GetPadding() const =0;
		virtual IPadding* GetPadding() =0;
	};
}
#endif

