// RSA_Berechnungen.h: Schnittstelle für die Klasse RSA_Berechnungen.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RSA_BERECHNUNGEN_H__4D7B9813_FC37_11D4_BEF3_0006291976BD__INCLUDED_)
#define AFX_RSA_BERECHNUNGEN_H__4D7B9813_FC37_11D4_BEF3_0006291976BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class RSA_Berechnungen  
{
public:
	CString GetCString (long, CString);
	long GetLong(CString);
	long oeff_param_pq(CString, CString);
	RSA_Berechnungen();
	virtual ~RSA_Berechnungen();
};

#endif // !defined(AFX_RSA_BERECHNUNGEN_H__4D7B9813_FC37_11D4_BEF3_0006291976BD__INCLUDED_)
