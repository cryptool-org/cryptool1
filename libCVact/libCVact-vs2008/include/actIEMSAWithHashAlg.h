//////////////////////////////////////////////////////////////////////////////////
// Name:      actIEMSAWithHashAlg.h
// Product:   cv act library
// Purpose:   IEMSAWithHashAlg is the abstract class derived from IEMSAAlg
//            which provides access on the aggregated hashobject of an 
//            EMSA-object. 
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IEMSAWithHashAlg_h
#define ACT_IEMSAWithHashAlg_h

#include "actIEMSAAlg.h"

namespace act
{
	class IHashAlg;

	class IEMSAWithHashAlg : public IEMSAAlg 
	{
	public:
		virtual void SetHash(IHashAlg* hash) =0;
		virtual const IHashAlg* GetHash() const =0;
		virtual IHashAlg* GetHash() =0;
	};
} // namespace act

#endif


