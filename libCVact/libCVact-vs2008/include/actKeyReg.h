//////////////////////////////////////////////////////////////////////////////////
// Name:      actKeyReg.h
// Product:   cv act library
// Purpose:   registry for factory functions in actKeyKit.h
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_KEYREG_H
#define ACT_KEYREG_H

namespace act
{
	class IKey;

	typedef IKey* (*CreateKeyPtr)();

	struct KeyMapEntry {
		const char* Name;
		CreateKeyPtr CreatePtr;
	};

	class KeyReg
	{
	public:
		static IKey* CreateKey(const char* name);
		static CreateKeyPtr GetCreatePointer(const char* name);
		static const char* GetName(void* createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name, CreateKeyPtr createptr);
		static void Insert(const KeyMapEntry* keymap);
	};
}
#endif

