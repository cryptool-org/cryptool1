//////////////////////////////////////////////////////////////////////////////////
// Name:      actRNGKit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_RNGKit_h
#define ACT_RNGKit_h
namespace act
{
	class IRNGAlg;

	IRNGAlg* CreateDevRandomRNG();
	IRNGAlg* CreateBBS();
	IRNGAlg* CreateLCG();
	IRNGAlg* CreateFIPS186();
	IRNGAlg* CreateFIPS186DES();
	IRNGAlg* CreateARC4RNG();
#ifndef UNDER_CE_30
	IRNGAlg* CreateWinRNG();
#endif
	IRNGAlg* CreateDummyPRNG();

#ifndef NO_SMARTCARD
	IRNGAlg* CreateTokenRNG();
#endif
}

#endif

