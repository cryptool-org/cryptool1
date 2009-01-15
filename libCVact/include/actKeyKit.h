//////////////////////////////////////////////////////////////////////////////////
// Name:      actKeyKit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_KEYKIT_H
#define ACT_KEYKIT_H

namespace act
{
	class IKey;

	IKey* CreateBlockCipherKey();

	IKey* CreateStreamCipherKey();

	IKey* CreateHashMACKey();
	IKey* CreateSecretKeyMACKey();
	IKey* CreateCBCMACKey();
	IKey* CreateRetailCFBMACKey();

	IKey* CreateRSAKey();

	IKey* CreateDSAKey();
	IKey* CreateECDSAKey();
	IKey* CreateECGDSAKey();

	IKey* CreateDHKey();
	IKey* CreateECDHKey();

	IKey* CreateIESKey();
}
#endif

