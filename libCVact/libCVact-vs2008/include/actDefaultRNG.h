//////////////////////////////////////////////////////////////////////////////////
// Name:      actDefaultRNG.h
// Product:   cv act library
// Purpose:   actDefaultRNG.h provides defaults for the class IRNGAlg.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_DefaultRNG_h
#define ACT_DefaultRNG_h
namespace act
{
	class IRNGAlg;
	typedef IRNGAlg* (*CreateRNGPtr)();

	extern CreateRNGPtr CreateFastRNG;
	extern CreateRNGPtr CreateStrongRNG;
}

#endif

