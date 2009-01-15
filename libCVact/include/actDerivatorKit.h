//////////////////////////////////////////////////////////////////////////////////
// Name:      actDerivatorKit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2006 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_DerivatorKit_h
#define ACT_DerivatorKit_h

namespace act
{
	class IDerivator;
	class Blob;

	IDerivator* CreateKDF1();
	IDerivator* CreateX963KDF();
	IDerivator* CreatePBKDF1();
	IDerivator* CreatePBKDF2();
}
#endif

