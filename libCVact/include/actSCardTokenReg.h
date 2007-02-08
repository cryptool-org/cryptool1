// ---------------------------------------------------------------------------
// Name:      actSCardTokenReg.h
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

#ifndef SCARDTOKENREG_H
#define SCARDTOKENREG_H

#ifdef _MSC_VER
#pragma warning (disable:4786)
#endif

namespace act
{
	class ISCardOS;
	class SCardToken;

	typedef SCardToken* (*CreateSCardTokenPtr)(ISCardOS*);
	typedef bool (*CheckSCardTokenPtr)(ISCardOS*);

	struct SCardTokenMapEntry {
		CheckSCardTokenPtr CheckPtr;
		CreateSCardTokenPtr CreatePtr;
	};

	class SCardTokenReg
	{
	public:
		static SCardToken* CreateSCardToken(ISCardOS* os);
		static void Insert(CheckSCardTokenPtr checkptr, CreateSCardTokenPtr createptr);
		static void Insert(const SCardTokenMapEntry* entry);

	};

}

#endif

