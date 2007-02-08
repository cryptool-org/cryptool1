//////////////////////////////////////////////////////////////////////////////////
// Name:      actIIESKey.h
// Product:   cv act library
// Purpose:   The interface IIESKey enables access to the aggregated objects of
//            an IES-key, like DL-IES or EC-IES.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IIESKey_H
#define ACT_IIESKey_H

#include "actIKey.h"

namespace act
{
	class IAgreementKey;
	class IMACKey;

	class IIESKey : public IKey
	{
	public:
		virtual void SetMAC(IMACKey* mac) =0;
		virtual const IMACKey* GetMAC() const =0;
		virtual IMACKey* GetMAC() =0;
		virtual void SetAgreement(IAgreementKey* derivator) =0;
		virtual const IAgreementKey* GetAgreement() const =0;
		virtual IAgreementKey* GetAgreement() =0;
	};
} // act
#endif

