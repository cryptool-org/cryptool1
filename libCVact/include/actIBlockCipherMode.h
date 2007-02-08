//////////////////////////////////////////////////////////////////////////////////
// Name:      actIBlockCipherMode.h
// Product:   cv act library
// Purpose:   By using this interface every blockcipher-algorithm can be run in
//            the modes CBC or ECB. Other modes e.g. OFB or CFB are supported.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IBlockCipherMode_h
#define ACT_IBlockCipherMode_h

#include "actBasics.h"

namespace act
{
	class IBlockCipher;
	class IAlgorithm;
	class IPadding;
	class Blob;

	class IBlockCipherMode
	{
	public:
		virtual IBlockCipherMode* Clone() const =0;
		virtual void Import(const Blob& indata) =0;
		virtual void Export(Blob& outdata) const =0;
		virtual void SetParam(paramid_t id, const Blob &blob) =0;
		virtual void SetParam(paramid_t id, int val) =0;
		virtual void SetParam(paramid_t id, const char* cstr) =0;
		virtual int GetParam(paramid_t) const =0;
		virtual void GetParam(paramid_t, Blob &blob) const =0;
		virtual IAlgorithm* CreateEncAlgorithm(IBlockCipher* cipher, IPadding* padding, const Blob& iv) const=0;
		virtual IAlgorithm* CreateDecAlgorithm(IBlockCipher* cipher, IPadding* padding) const=0;
		virtual void* GetCreatePointer() const=0;
		virtual ~IBlockCipherMode() {}
	};
} // namespace act

#endif


