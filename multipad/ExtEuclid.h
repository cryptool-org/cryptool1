// ExtEuclid.h: Schnittstelle für die Klasse ExtEuclid.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXTEUCLID_H__F8D078E1_7CD1_11D5_A851_00025532117A__INCLUDED_)
#define AFX_EXTEUCLID_H__F8D078E1_7CD1_11D5_A851_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ExtEuclid  
{
public:

	long g, u, v;

	ExtEuclid(long, long);
	long get_g() { return g; };
	long get_u() { return u; };
	long get_v() { return v; };
	virtual ~ExtEuclid();

private:

	void extgcd(long, long);
	void modify(long);

};

#endif // !defined(AFX_EXTEUCLID_H__F8D078E1_7CD1_11D5_A851_00025532117A__INCLUDED_)
