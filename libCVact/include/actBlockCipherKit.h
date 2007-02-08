//////////////////////////////////////////////////////////////////////////////////
// Name:      actBlockCipherKit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_BlockCipherKit_h
#define ACT_BlockCipherKit_h

namespace act
{
	class IBlockCipher;

	IBlockCipher* CreateDES();
	IBlockCipher* CreateTripleDES();
	IBlockCipher* CreateCAST128();
	IBlockCipher* CreateBlowFish();
	IBlockCipher* CreateTwoFish();
	IBlockCipher* CreateMars();
	IBlockCipher* CreateRijndael();
	IBlockCipher* CreateSerpent();
	IBlockCipher* CreateRC2();
	//IBlockCipher* CreateRC6();
}
#endif

