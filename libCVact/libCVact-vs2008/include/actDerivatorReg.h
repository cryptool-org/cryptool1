//////////////////////////////////////////////////////////////////////////////////
// Name:      actDerivatorReg.h
// Product:   cv act library
// Purpose:   registry for the factory functions in actDerivatorKit.h
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_DerivatorReg_h
#define ACT_DerivatorReg_h

namespace act
{
	class IDerivator;
	class Blob;

	typedef IDerivator* (*CreateDerivatorPtr)();

	struct DerivatorMapEntry {
		const char* Name;
		CreateDerivatorPtr CreatePtr;
	};


	class DerivatorReg
	{
	public:
		static IDerivator* CreateDerivator(const char* name);
		static CreateDerivatorPtr GetCreatePointer(const char* name);
		static const char* GetName(void *createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name, CreateDerivatorPtr createptr);
		static void Insert(const DerivatorMapEntry* derivatormap);
	};
}

#endif

