//////////////////////////////////////////////////////////////////////////////////
// Name:      actBlockCipherModeReg.h
// Product:   cv act library
// Purpose:   registry for factory functions in actBlockCipherModeKit.h
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_BlockCipherModeReg_h
#define ACT_BlockCipherModeReg_h

namespace act
{
	class IBlockCipherMode;

	typedef IBlockCipherMode* (*CreateBlockCipherModePtr)();

	struct BlockCipherModeMapEntry {
		const char* Name;
		CreateBlockCipherModePtr CreatePtr;
	};

	class BlockCipherModeReg
	{
	public:
		static IBlockCipherMode* CreateBlockCipherMode(const char* name);
		static CreateBlockCipherModePtr GetCreatePointer(const char* name);
		static const char* GetName(void *createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name,CreateBlockCipherModePtr createptr);
		static void Insert(const BlockCipherModeMapEntry* map);
	};
}

#endif

