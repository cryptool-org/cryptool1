#if !defined(AFX_ZZGEN_H__B511ADE2_6131_11D4_A05B_002035F23D41__INCLUDED_)
#define AFX_ZZGEN_H__B511ADE2_6131_11D4_A05B_002035F23D41__INCLUDED_

#include "HexEdit1.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// zzgen.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld zzgen 

class zzgen 
{
// Konstruktion
public:
	//virtual ~zzgen();   // Standardkonstruktor
	char *prim;
	unsigned int primlen;
	int pblen;
	bool isprime(unsigned int,FILE *,unsigned int *);
	unsigned long getrnd(unsigned long);
	unsigned long ggt(unsigned long,unsigned long);
	long jacobi(long,long);
	bool isprimefast (unsigned long);
	bool isprimefast2 (unsigned long);

	unsigned char zzgen1(unsigned long *,unsigned long,int);
	unsigned char zzgen2(unsigned long *,unsigned long,unsigned long,unsigned long);
	unsigned char zzgen3(unsigned long *,unsigned long);
	unsigned char zzgen4();
	unsigned long multmodn(unsigned long,unsigned long,unsigned long);
	unsigned long powermod(unsigned long,unsigned long,unsigned long);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ZZGEN_H__B511ADE2_6131_11D4_A05B_002035F23D41__INCLUDED_
