// ExtEuclid.cpp: Implementierung der Klasse ExtEuclid.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "ExtEuclid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ExtEuclid::ExtEuclid(long a, long b)
{
	u=1, v=0;
	extgcd(a, b);
}

ExtEuclid::~ExtEuclid()
{
}

void ExtEuclid::extgcd(long a, long b)
{
	if ( b > a )
	{
		long x = a; a = b; b = x;
		long y = u; u = v; v = y;
	}
	while (b != 0)
	{
		long x = b; b = a % b; a = x;
		if ( b != 0 )
		{
		    long y = u; u = v; v = y - (a/b)*v;
		}
		else
		{
		    long y = u; u = v; v = y;
		}
// 		modify(a/b);
	}
	g = a;
}

void ExtEuclid::modify(long q)
{
	long x=u;
	u=v;
	v=x-q*v;
}
