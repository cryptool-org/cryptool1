// ---------------------------------------------------------------------------
// Name:      actAppletKit.h
// Product:   cv act library
// Purpose:   registry for factory functions to create JavaCard Applet
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:
// Date:	  02/10/2003
// ---------------------------------------------------------------------------

#ifndef JCARDAPPLETKIT_H
#define JCARDAPPLETKIT_H

#include "actBlob.h"
namespace act
{
	class JavaCardOS;
	class IToken;

	bool IsEdgeApplet(JavaCardOS* os, const Blob& aid);					
	IToken* CreateEdgeApplet(JavaCardOS* os, const Blob& aid);

}
#endif
