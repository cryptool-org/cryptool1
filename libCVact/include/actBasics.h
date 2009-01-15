//////////////////////////////////////////////////////////////////////////////////
// Name:      actBasics.h
// Product:   cv act library
// Purpose:   integration of globally available identifiers
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_Basics_h
#define ACT_Basics_h

//
// Disable specific VC6 warnings here.
#if defined(_MSC_VER) & _MSC_VER < 1300
	#pragma warning(disable:4786)
#endif


#ifdef __sun__
	#undef	LITTLE_ENDIAN
#else
	#ifndef LITTLE_ENDIAN
	#define LITTLE_ENDIAN
	#endif
#endif	// __sun__


#ifndef NO_STL_SUPPORT
	#include <cstddef>	// used for ptrdiff_t,size_t
#else
	#ifndef _PTRDIFF_T_DEFINED
	typedef int ptrdiff_t;
	#define _PTRDIFF_T_DEFINED
	#endif


	#ifndef _SIZE_T_DEFINED
	typedef unsigned int size_t;
	#define _SIZE_T_DEFINED
	#endif
#endif //NO_STL_SUPPORT

namespace act
{

   typedef unsigned long ulong;
   typedef unsigned int uint;
   typedef unsigned short ushort;
   typedef unsigned char uchar;
   typedef unsigned char byte;
   typedef unsigned short word;
   typedef unsigned long dword;

#if defined(_MSC_VER) & !defined(__MWERKS__)
   using ::size_t;
   using ::ptrdiff_t;
#else
   using std::size_t;
   using std::ptrdiff_t;
#endif

   typedef int paramid_t;
   typedef int status_t;
   typedef int mode_t;
   typedef int export_t;
  
   typedef ushort uint16;
   typedef ulong uint32;
#if defined(__GNUC__) || defined(__MWERKS__)
	typedef unsigned long long uint64;
	#define U64(x) x##ULL
#else
	//#ifdef _MSC_EXTENSIONS
	typedef unsigned __int64 uint64;
	#define U64(x) x##ui64
#endif


  const export_t DEFAULT=0;
} // namespace act

#endif // ACT_Basics_h
