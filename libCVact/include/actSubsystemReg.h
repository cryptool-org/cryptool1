// ---------------------------------------------------------------------------
// Name:      actSubsystemReg.h
// Product:   cv act library
// Purpose:   registry for factory functions to create subsystem
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  05/14/2002
// ---------------------------------------------------------------------------

#ifndef SubsystemREG_H
#define SubsystemREG_H

namespace act
{
	class ISubsystem;
	class ISCardAccess;

	typedef ISubsystem* (*CreateSubsystemPtr)(const char*);

	struct SubsystemMapEntry {
		const char* Name;
		CreateSubsystemPtr CreatePtr;
	};

	class SubsystemReg
	{
	public:
		static ISubsystem* CreateSubsystem(const char * name, const char* dll_name = 0);
		static CreateSubsystemPtr GetCreatePointer(const char *name);
		static const char* GetName(void *createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name, CreateSubsystemPtr createptr);
		static void Insert(const SubsystemMapEntry* entry);
	};


}

#endif

