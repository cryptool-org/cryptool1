//////////////////////////////////////////////////////////////////////////////////
// Name:      actBlockCipherReg.h
// Product:   cv act library
// Purpose:   registry for factory functions in actBlockCipherKit.h
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_BlockCipherReg_h
#define ACT_BlockCipherReg_h

namespace act
{
	class IBlockCipher;

	typedef IBlockCipher* (*CreateBlockCipherPtr)();

	struct BlockCipherMapEntry {
		const char* Name;
		CreateBlockCipherPtr CreatePtr;
	};

	class BlockCipherReg
	{
	public:
		static IBlockCipher* CreateBlockCipher(const char* name);
		static CreateBlockCipherPtr GetCreatePointer(const char* name);
		static const char* GetName(void* createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name,CreateBlockCipherPtr createptr);
		static void Insert(const BlockCipherMapEntry* map);
	};
}

#endif

