// ---------------------------------------------------------------------------
// Name:      actSubsystemKit.h
// Product:   cv act library
// Purpose:   registry for factory functions to create subsystem
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  05/13/2002
// ---------------------------------------------------------------------------

#ifndef SUBSYSTEMKIT_H
#define SUBSYSTEMKIT_H

namespace act
{
	class ISubsystem;

	ISubsystem* CreateCTAPISystem(const char*);
	ISubsystem* CreatePCSCSystem(const char*);
	ISubsystem* CreateCSPSystem(const char*);
	ISubsystem* CreatePKCS11System(const char*);

}
#endif

