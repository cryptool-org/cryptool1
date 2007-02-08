//////////////////////////////////////////////////////////////////////////////////
// Name:      actIAgreementKey.h
// Product:   cv act library
// Purpose:   The abstract class IAgreementKey derived from IKey is the 
//            interface to all key agreements.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IAgreementKey_H
#define ACT_IAgreementKey_H

#include "actIKey.h"

namespace act
{
	class IDerivator;

	class IAgreementKey : public IKey
	{
	public:
		virtual void SetDerivator(IDerivator* derivator) =0;
		virtual const IDerivator* GetDerivator() const =0;
		virtual IDerivator* GetDerivator() =0;
	};

} // act
#endif

