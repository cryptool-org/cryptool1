// NTLExpPars.h: Schnittstelle für die Klasse NTLExpPars.
//
//////////////////////////////////////////////////////////////////////
#define NOMINMAX
#include "NTL/ZZ.h"
#include "afx.h"
using namespace NTL;
#if !defined(AFX_NTLEXPPARS_H__6DF4E263_4879_4A94_9CD0_5E85B8AC0053__INCLUDED_)
#define AFX_NTLEXPPARS_H__6DF4E263_4879_4A94_9CD0_5E85B8AC0053__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NTL_OP_END 0
#define NTL_OP_PLUS 1
#define NTL_OP_MINUS 2
#define NTL_OP_TIMES 3
#define NTL_OP_DIV 4
#define NTL_OP_POWER 5
#define NTL_OP_OPENPAR 6
#define NTL_OP_CLOSEPAR 7
#define NTL_OP_NUMBER 8
#define NTL_OP_ERROR 255



class NTLExpPars  
{
public:
	CString verbose;
	ZZ parseExp(CString ex);
	NTLExpPars();
	virtual ~NTLExpPars();

private:
	int lastToken;
	bool lowPrecedence(int a, int b);
	ZZ calc(ZZ a, ZZ b, int op);
	int nextToken(CString& ex, ZZ& v);
};

#endif // !defined(AFX_NTLEXPPARS_H__6DF4E263_4879_4A94_9CD0_5E85B8AC0053__INCLUDED_)
