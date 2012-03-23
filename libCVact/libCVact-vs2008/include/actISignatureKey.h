//////////////////////////////////////////////////////////////////////////////////
// Name:      actISignatureKey.h
// Product:   cv act library
// Purpose:   The interface ISignatureKey enables access to the aggregated
//            EMSA-object of the SignatureKeys.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_ISignatureKey_h
#define ACT_ISignatureKey_h

#include "actIKey.h"

namespace act
{
	class IEMSAAlg;

	class ISignatureKey : public IKey
	{
	public:
		virtual void SetEncoder(IEMSAAlg* padding) =0;
		virtual const IEMSAAlg* GetEncoder() const =0;
		virtual IEMSAAlg* GetEncoder() =0;
	};
}
#endif

