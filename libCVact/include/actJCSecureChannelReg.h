//-----------------------------------------------------------------------------
// Name:      actJCSecureChannelReg.h
// Product:   cv act library
// Purpose:   
//            
// Copyright: (c) 2003 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for use of this software are regulated
//            in the cv act libary licence agreement.
//            
// Autor:     
// Data:      08.10.2003 15:53:14
//-----------------------------------------------------------------------------

#ifndef __ACTJCSECURECHANNELREG_H__
#define __ACTJCSECURECHANNELREG_H__

namespace act
{
	class Blob;

	struct JCSecureChannelEntry {
		const char*				hexvalue;
	};


	class JCardSecureChannelReg
	{
	public:
		static Blob		GetValue(int i);
		static int		GetNumber();
		

		static void Insert(const char* hexvalue);
		static void Insert(const JCSecureChannelEntry* entry);

	};

}



#endif //__ACTJCSECURECHANNELREG_H__
