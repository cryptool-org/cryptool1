//////////////////////////////////////////////////////////////////////////////////
// Name:      actIMACKEY.h
// Product:   cv act library
// Purpose:   interface for the class CBCMAC
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IMACKey_h
#define ACT_IMACKey_h

#include "actIKey.h"

namespace act
{

	class IMACKey : public IKey
	{
	public:
		virtual const char* KeyName() const =0;
	};

} // namespace act

#endif

