// ---------------------------------------------------------------------------
// Name:      actAppletReg.h
// Product:   cv act library
// Purpose:   registry for factory functions to create JavaCardApplet object
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:
// Date:	  02/10/2003
// ---------------------------------------------------------------------------

#ifndef JCARDAPPLETREG_H
#define JCARDAPPLETREG_H

#ifdef _MSC_VER
#pragma warning (disable:4786)
#endif

namespace act
{
	class JavaCardOS;
	class IToken;
	class Blob;

	typedef IToken* (*CreateJCardAppletPtr)(JavaCardOS*,const Blob& aid);
	typedef bool (*CheckJCardAppletPtr)(JavaCardOS*,const Blob& aid);

	struct JCardAppletEntry {
		const char*				hexid;
		CheckJCardAppletPtr		CheckPtr;
		CreateJCardAppletPtr	CreatePtr;
		int						keys;
		int						pins;
		int						certs;
	};

	struct JCardAppletInfoEntry {
		int						keys;
		int						pins;
		int						certs;
	};

	class JCardAppletReg
	{
	public:
		static IToken*				CreateJCardApplet(JavaCardOS* os, const Blob& aid);
		static JCardAppletInfoEntry GetJCardAppletInfo(JavaCardOS* os, const Blob& aid);
		static bool					IsJCardApplet(JavaCardOS* os, const Blob& aid);
		

		static void Insert(const char* id, CheckJCardAppletPtr checkptr, CreateJCardAppletPtr createptr,
							int keys = -1, int pins = -1, int certs = -1);
		static void Insert(const JCardAppletEntry* entry);

	};

}

#endif

