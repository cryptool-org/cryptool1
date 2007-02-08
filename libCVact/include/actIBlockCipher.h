//////////////////////////////////////////////////////////////////////////////////
// Name:      actIBlockCipher.h
// Product:   cv act library
// Purpose:   The class IBlockCipher creates the symmetric BlockCypher, which is
//            defined by IBockCipherKey and IBlockCipherMode. It offers operations
//            like encrypt, decrypt and queries involving validity or keylength etc. 
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IBlockCipher_h
#define ACT_IBlockCipher_h

#include "actBasics.h"
#include <typeinfo>

namespace act
{

	class Blob;

	class IBlockCipher
	{
	public:
		virtual IBlockCipher* Clone() const =0;
		virtual void Import( const Blob& indata ) =0;
		virtual void Export( Blob& outdata ) const =0;

		virtual void SetRawKey( const Blob& keyblob ) =0;
		virtual void GetRawKey( Blob& keyblob ) const =0;

		virtual void Encrypt(const byte* in,byte* out) const =0;
		virtual void Decrypt(const byte* in,byte* out) const =0;

		virtual size_t GetKeySize(size_t keysize=0) const =0;
		virtual size_t GetMinKeySize() const =0;
		virtual size_t GetMaxKeySize() const =0;
		virtual size_t GetNextKeySize(size_t prevsize) const =0;
		virtual size_t GetBlockSize() const =0;

		virtual void* GetCreatePointer() const =0;

		virtual ~IBlockCipher() {};
	};


}// namespace act

#endif

