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
	if (b==0)
		g=a;
	else
	{
		extgcd(b, a % b);
		modify(a/b);
	}
}

void ExtEuclid::modify(long q)
{
	long x=u;
	u=v;
	v=x-q*v;
}
