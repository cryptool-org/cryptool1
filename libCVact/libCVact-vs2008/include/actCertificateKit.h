//////////////////////////////////////////////////////////////////////////////////
// Name:      actCertificateKit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_CERTIFICATEKIT_H
#define ACT_CERTIFICATEKIT_H

namespace act
{
	class ICertificate;
	class ICRL;
	
	ICertificate* CreateX509Certificate();
	ICRL* CreateX509CRL();
}
#endif

