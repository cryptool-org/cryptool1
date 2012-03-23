//////////////////////////////////////////////////////////////////////////////////
// Name:      actStreamCipherKit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2001 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_StreamCipherKit_h
#define ACT_StreamCipherKit_h

namespace act
{
	class IStreamCipher;

	IStreamCipher* CreateARC4();
}
#endif

