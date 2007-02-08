// ---------------------------------------------------------------------------
// Name:      actSCardOSReg.h
// Product:   cv act library
// Purpose:   registry for factory functions to create SCardOS object
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  04/09/2002
// ---------------------------------------------------------------------------

#ifndef SCARDOSREG_H
#define SCARDOSREG_H

namespace act
{
	class ISCardOS;
	class ISCardAccess;

	typedef ISCardOS* (*CreateSCardOSPtr)(ISCardAccess*);

	struct SCardOSMapEntry {
		const char* Name;
		CreateSCardOSPtr CreatePtr;
	};

	class SCardOSReg
	{
	public:
		static ISCardOS* CreateSCardOS(const char * name, ISCardAccess* ac);
		static CreateSCardOSPtr GetCreatePointer(const char *name);
		static const char* GetName(void *createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name, CreateSCardOSPtr createptr);
		static void Insert(const SCardOSMapEntry* entry);
	};


}

#endif

