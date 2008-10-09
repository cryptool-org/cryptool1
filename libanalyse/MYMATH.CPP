/////////////////////////////////////////////////////////////////
//
// Diese Datei ist Bestandteil der Diplomarbeit
// "Eine C++-Bibliothek zur informationstheoretischen Kryptanalyse 
// von Stromchiffren und PZ-Folgen" am Europaeischen Institut fuer
// Systemsicherheit, Prof. Dr. Th. Beth
//
// von und (c) 1997-98 Michael Friedrich
//
/////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "mymath.h"

// This file defines:
//long pow(long a, int b);
//int ilog2(unsigned long l);
//long gcd(long x, long y);
//long minverse(long x, long n);
//char* ToString(int n);

/////////////////////////////////////////////////////////////////////
// Implementation


long pow(long a, int b) 
{
	ASSERT(b>=0);
	long c=1;
	while (b) {
		if (b&1) c=c*a;
		b>>=1;
		a=a*a;
	}
	return c;
}

int ilog2(unsigned long l)	// returns min {r|2^r>=l}
{							// note: ilog(0)=-1, ilog(1)=0, ilog2(2)=1, ilog(3)=2
#ifdef _DEBUG
	unsigned long ll=l;
#endif
	int r=0;
	if (l--==0) return -1;
	while (l) {l>>=1; r++;}
	ASSERT(pow((long)2,(int)r)>=(long)ll && (r==0 || pow((long)2,(int)(r-1))<(long)ll));
	return r;
}

/////////////////////////////////////////////////////////////////////
long gcd(long x, long y)
{
	long a = abs(x);
	long b = abs(y);
	if (b>a) swap(a,b);
	for(;;)	{
		if (b == 0)	return a;
		if (b == 1) return b;
		// (a,b)=(b,a%b)
		a=a%b; swap(a,b);
	} /* for */
}

/////////////////////////////////////////////////////////////////////
static inline void minverse_update(long& a, long& b, long y) 
	{long t=b; b=a-y*t; a=t;}
long minverse(long x, long n)
{
	long g,h,w,z,v,r;
	g=n; h=x; w=1; z=0; v=0; r=1;
	while (h>0) {
		long y=g/h;
		minverse_update(g,h,y);
		minverse_update(w,z,y);
		minverse_update(v,r,y);
	}
	return mod(v,n);
}

/////////////////////////////////////////////////////////////////////
char* ToString(int n) 
{
	static char buffer[256];
	sprintf(buffer,"%d",n);
	return buffer;
}
