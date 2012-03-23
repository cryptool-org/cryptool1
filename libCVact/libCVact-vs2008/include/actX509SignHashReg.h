//////////////////////////////////////////////////////////////////////////////////
// Name:      actX509SignHashReg.h
// Product:   cv act library
// Purpose:   registry for factory functions in actX509Kit.h
//
// Copyright: (c) 2000-2001 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_X509SignHashReg_h
#define ACT_X509SignHashReg_h

namespace act
{
	class Blob;

	// ------------------------------------------------------------------------
	struct X509SignHashMapEntry {
		const char* OID;
		const char* HashAlg;
		const char* SignAlg;
	};

	// ------------------------------------------------------------------------
	class X509SignHashReg
	{
	public:
		static void GetOID(const char* algo, const char* sign_algo, Blob& algid);
		static const char* GetHashAlg(const Blob& algid);
		static const char* GetSignAlg(const Blob& algid);
		static void Insert(const X509SignHashMapEntry* map);

		static const char* GetHashAlg(const Blob& algid, const char* sign_algo);	// deprecated
	};

}
#endif

