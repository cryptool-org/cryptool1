//////////////////////////////////////////////////////////////////////////////////
// Name:      actPaddingReg.h
// Product:   cv act library
// Purpose:   registry for the factory functions in actPaddingKit.h
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_PaddingReg_h
#define ACT_PaddingReg_h

namespace act
{
	class IPadding;
	class Blob;

	typedef IPadding* (*CreatePaddingPtr)();

	struct PaddingMapEntry {
		const char* Name;
		CreatePaddingPtr CreatePtr;
	};

	class PaddingReg
	{
	public:
		static IPadding* CreatePadding(const char* name);
		static CreatePaddingPtr GetCreatePointer(const char* name);
		static const char* GetName(void *createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name, CreatePaddingPtr createptr);
		static void Insert(const PaddingMapEntry* paddingmap);
	};
}

#endif

