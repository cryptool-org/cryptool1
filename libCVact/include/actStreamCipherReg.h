//////////////////////////////////////////////////////////////////////////////////
// Name:      actStreamCipherReg.h
// Product:   cv act library
// Purpose:   registry for factory functions in actStreamCipherKit.h
//
// Copyright: (c) 2001 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_StreamCipherReg_h
#define ACT_StreamCipherReg_h

namespace act
{
	class IStreamCipher;

	typedef IStreamCipher* (*CreateStreamCipherPtr)();

	struct StreamCipherMapEntry {
		const char* Name;
		CreateStreamCipherPtr CreatePtr;
	};

	class StreamCipherReg
	{
	public:
		static IStreamCipher* CreateStreamCipher(const char* name);
		static CreateStreamCipherPtr GetCreatePointer(const char* name);
		static const char* GetName(void* createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name,CreateStreamCipherPtr createptr);
		static void Insert(const StreamCipherMapEntry* map);
	};
}

#endif

