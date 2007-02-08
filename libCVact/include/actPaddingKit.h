//////////////////////////////////////////////////////////////////////////////////
// Name:      actPaddingKit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_PaddingKit_h
#define ACT_PaddingKit_h

namespace act
{
	class IPadding;

	IPadding* CreatePKCS5Pad();
	IPadding* CreatePKCS1V1_5EMEPad();
	IPadding* CreateOneAndZerosPad();
	IPadding* CreateISO9796Pad();
	IPadding* CreateNoPad();
}
#endif

