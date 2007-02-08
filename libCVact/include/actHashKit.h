//////////////////////////////////////////////////////////////////////////////////
// Name:      actHashKit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_HASHKIT_H
#define ACT_HASHKIT_H

namespace act
{
	class IHashAlg;
	IHashAlg* CreateMD2();
	IHashAlg* CreateMD4();
	IHashAlg* CreateMD5();
	IHashAlg* CreateRipemd128();
	IHashAlg* CreateRipemd160();
	IHashAlg* CreateSHA0();
	IHashAlg* CreateSHA1();
	IHashAlg* CreateSHA224();
	IHashAlg* CreateSHA256();
	IHashAlg* CreateSHA384();
	IHashAlg* CreateSHA512();
	IHashAlg* CreateDummyHash();
}
#endif

