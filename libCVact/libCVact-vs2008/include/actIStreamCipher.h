//////////////////////////////////////////////////////////////////////////////////
// Name:      actIStreamCipher.h
// Product:   cv act library
// Purpose:   The class IStreamCipher creates the symmetric StreamCipher, which is
//            defined by IStreamCipherKey. It offers operations like encrypt, decrypt 
//            and queries involving validity or keylength etc. 
//
// Copyright: (c) 2001 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IStreamCipher_h
#define ACT_IStreamCipher_h

#include "actBasics.h"

namespace act
{

	class Blob;

	class IStreamCipher
	{
	public:

		virtual IStreamCipher* Clone() const =0;
		virtual void Import( const Blob& indata ) =0;
		virtual void Export( Blob& outdata ) const =0;

		virtual void SetRawKey( const Blob& keyblob ) =0;
		virtual void GetRawKey( Blob& keyblob ) const =0;

		virtual void Process(const byte* input, byte* output, size_t input_len) const =0;

		virtual size_t GetKeySize(size_t keysize=0) const =0;
		virtual size_t GetMinKeySize() const =0;
		virtual size_t GetMaxKeySize() const =0;
		virtual size_t GetNextKeySize(size_t prevsize) const =0;

		virtual void* GetCreatePointer() const =0;

		virtual ~IStreamCipher() {};
	};


}// namespace act

#endif

