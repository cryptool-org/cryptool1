// VolumeUtilities.h: interface for the VolumeUtilities class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_VOLUMEUTILITIES_H_INCLUDED_)
#define _VOLUMEUTILITIES_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef VOLREN_EXPORTS
#define VOLREN_API __declspec(dllexport)
#else
#define VOLREN_API __declspec(dllimport)
#endif

class VOLREN_API VolumeUtilities  
{
public:
	static void convertUSHORTtoUCHAR_Linear(const unsigned short *pReadBuffer, unsigned char *pWriteBuffer, unsigned long nNumVoxels);
	static void convertUSHORTtoUCHAR_HistLinear(const unsigned short *pReadBuffer, unsigned char *pWriteBuffer, unsigned long nNumVoxels);

	static void getMappingTableUSHORTtoUCHAR_Linear(const unsigned short *pReadBuffer, unsigned char *pMapTable, unsigned long nNumVoxels);
	static void getMappingTableUSHORTtoUCHAR_HistLinear(const unsigned short *pReadBuffer, unsigned char *pMapTable, unsigned long nNumVoxels);

};

#endif // !defined(_VOLUMEUTILITIES_H_INCLUDED_)
