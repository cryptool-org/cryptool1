// eval.h: Schnittstelle für die Klasse eval.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVAL_H__EFB9E8E0_5F92_11D5_BB4A_000777640932__INCLUDED_)
#define AFX_EVAL_H__EFB9E8E0_5F92_11D5_BB4A_000777640932__INCLUDED_

#include "BIG.H"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define TIMES '*'
#define RAISE '^'

class evaluateFormula  
{
public:
	static BOOL eval( Big& value, const char * Str );

private:
	static BOOL eval();
	static void eval_product(Big &oldn, Big &n, char op);
	static void eval_sum(Big &oldn, Big &n, char op);
	static void eval_power(Big& oldn, Big& n, char op);
};

static Miracl g_precision=25;

#endif // !defined(AFX_EVAL_H__EFB9E8E0_5F92_11D5_BB4A_000777640932__INCLUDED_)
