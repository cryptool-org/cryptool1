//////////////////////////////////////////////////////////////////////////////////
// Name:      actX509SignReg.h
// Product:   cv act library
// Purpose:   registry for factory functions in actX509Kit.h
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_X509SignReg_h
#define ACT_X509SignReg_h

namespace act
{
	class IKey;
	class Blob;

	typedef IKey* (*CreateKeyPtr)();
	typedef void (*GetX509AlgIDPtr)(const IKey* key, Blob& algid);
	typedef void (*SetX509AlgIDPtr)(const Blob& algid, IKey* key);

	struct X509SignMapEntry {
		CreateKeyPtr CreatePtr;
		GetX509AlgIDPtr GetAlgID;
		SetX509AlgIDPtr SetAlgID;
	};

	class X509SignReg
	{
	public:
		static void GetAlgID(const IKey* key, Blob& algid);
		static void SetAlgID(const Blob& algid, IKey* key);

		static void Insert(CreateKeyPtr createptr, GetX509AlgIDPtr getalgid, SetX509AlgIDPtr setalgid );
		static void Insert(const X509SignMapEntry* keymap);
	};
}
#endif

