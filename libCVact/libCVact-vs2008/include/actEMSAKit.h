//////////////////////////////////////////////////////////////////////////////////
// Name:      actEMSAKit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_EMSAKit_h
#define ACT_EMSAKit_h

namespace act
{
	class IEMSAAlg;

	IEMSAAlg* CreateEMSA1();
	IEMSAAlg* CreatePKCS1V1_5EMSA();
	IEMSAAlg* CreateTLS_EMSA();
	IEMSAAlg* CreatePKCS1_PSS_EMSA();

}
#endif

