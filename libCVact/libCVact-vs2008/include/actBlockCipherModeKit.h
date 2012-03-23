//////////////////////////////////////////////////////////////////////////////////
// Name:      actBlockCipherModeKit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////


#ifndef ACT_BlockCipherModeKit_h
#define ACT_BlockCipherModeKit_h

namespace act
{
	class IBlockCipherMode;

	IBlockCipherMode* CreateECBMode();
	IBlockCipherMode* CreateCBCMode();
	IBlockCipherMode* CreateCFBMode();
	IBlockCipherMode* CreateOFBMode();
	IBlockCipherMode* CreateCTRMode();
}
#endif

