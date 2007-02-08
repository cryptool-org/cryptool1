//////////////////////////////////////////////////////////////////////////////////
// Name:      actIBlockCipherKey.h
// Product:   cv act library
// Purpose:   The class IBlockCipherKey extends the interface of the class IKey
//            and supports the peculiarities of symmetric keys.  
//
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IBlockCipherKey_h
#define ACT_IBlockCipherKey_h

#include "actIKey.h"

namespace act
{
	class IPadding;
	class IBlockCipher;
	class IBlockCipherMode;
	class IDerivator;

	class IBlockCipherKey : public IKey
	{

	public:
		virtual void SetPadding(IPadding* padding) =0;
		virtual const IPadding* GetPadding() const =0;
		virtual IPadding* GetPadding()  =0;

		virtual void SetCipher(IBlockCipher* cipher) =0;
		virtual const IBlockCipher* GetCipher() const =0;
		virtual IBlockCipher* GetCipher() =0;


		virtual void SetMode(IBlockCipherMode* mode) =0;
		virtual const IBlockCipherMode* GetMode() const =0;
		virtual IBlockCipherMode* GetMode() =0;

		virtual void SetDerivator(IDerivator* derive) =0;
		virtual const IDerivator* GetDerivator() const =0;
		virtual IDerivator* GetDerivator()  =0;
	};
} //namespace act
#endif

