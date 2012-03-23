//////////////////////////////////////////////////////////////////////////////////
// Name:      actHashReg.h
// Product:   cv act library
// Purpose:   registry for factory functions in actHashKit.h
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_HASHREG_H
#define ACT_HASHREG_H

namespace act
{
	class IHashAlg;

	typedef IHashAlg* (*CreateHashPtr)();

	struct HashMapEntry {
		const char* Name;
		CreateHashPtr CreatePtr;
	};

	class HashReg
	{
	public:
		static IHashAlg* CreateHashAlg(const char * name);
		static CreateHashPtr GetCreatePointer(const char *name);
		static const char* GetName(void *createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name, CreateHashPtr createptr);
		static void Insert(const HashMapEntry* hashmap);
	};
}

#endif

