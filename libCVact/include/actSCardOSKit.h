// ---------------------------------------------------------------------------
// Name:      actSCardOSKit.h
// Product:   cv act library
// Purpose:   registry for factory functions to create SCardOS object
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  05/13/2002
// ---------------------------------------------------------------------------

#ifndef SCARDOSKIT_H
#define SCARDOSKIT_H

namespace act
{
	class ISCardOS;
	class ISCardAccess;

	ISCardOS* CreateStarCOS(ISCardAccess*);
	ISCardOS* CreateCardOS_M4(ISCardAccess*);
	ISCardOS* CreateCardOS_V4(ISCardAccess*);
	ISCardOS* CreateTCOS(ISCardAccess*);
	ISCardOS* CreateMicardOS(ISCardAccess*);
	ISCardOS* CreateMicardo20E(ISCardAccess*);
	ISCardOS* CreateACOS(ISCardAccess*);
	ISCardOS* CreateMicardo23E(ISCardAccess* ac);
	ISCardOS* CreateCardOS_M4_ECC(ISCardAccess*);
	ISCardOS* CreateJavaCardEdgeOS(ISCardAccess*);

}
#endif

