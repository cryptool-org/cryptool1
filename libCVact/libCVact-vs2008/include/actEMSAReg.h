//////////////////////////////////////////////////////////////////////////////////
// Name:      actEMSAReg.h
// Product:   cv act library
// Purpose:   registry for factory functions in actEMSAKit.h
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_EMSAReg_h
#define ACT_EMSAReg_h

namespace act
{
	class IEMSAAlg;

	typedef IEMSAAlg* (*CreateEMSAPtr)();

	struct EMSAMapEntry {
		const char* Name;
		CreateEMSAPtr CreatePtr;
	};

	class EMSAReg
	{
	public:
		static IEMSAAlg* CreateEMSAAlg(const char* name);
		static CreateEMSAPtr GetCreatePointer(const char* name);
		static const char* GetName(void *createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name,CreateEMSAPtr createptr);
		static void Insert(const EMSAMapEntry* map);
	};
}

#endif

