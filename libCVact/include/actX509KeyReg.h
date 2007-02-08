//////////////////////////////////////////////////////////////////////////////////
// Name:      actX509KeyReg.h
// Product:   cv act library
// Purpose:   registry for factory functions in actX509Kit.h
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_X509KeyReg_h
#define ACT_X509KeyReg_h
//#include "actKeyReg.h"

namespace act
{
	class IKey;
	class Blob;

	typedef IKey* (*CreateKeyPtr)();
	typedef void (*X509ToKeyPtr)(const Blob &pkinfo, IKey* key);
	typedef void (*KeyToX509Ptr)(const IKey* key, Blob &pkinfo );

	struct X509KeyMapEntry {
		const char* OID;
		CreateKeyPtr CreatePtr;
		X509ToKeyPtr X509ToKey;
		KeyToX509Ptr KeyToX509;
	};

	class X509KeyReg
	{
	public:
		static IKey* CreateX509Key(const Blob& pkInfo);
		static void GetX509KeyInfo(const IKey* key, Blob& pkInfo);

		static CreateKeyPtr GetCreatePointer(const char* oid);
		static const char* GetOID(void* createptr);
		static const char* GetNextOID(const char* oid);

		static void Insert(const char* name, CreateKeyPtr createptr, X509ToKeyPtr x509tokey, KeyToX509Ptr keytox509 );
		static void Insert(const X509KeyMapEntry* keymap);
	};
}
#endif

