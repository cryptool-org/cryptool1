// RSA_Berechnungen.cpp: Implementierung der Klasse RSA_Berechnungen.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "RSA_Berechnungen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

RSA_Berechnungen::RSA_Berechnungen()
{

}

RSA_Berechnungen::~RSA_Berechnungen()
{

}
	

long RSA_Berechnungen::oeff_param_pq(CString p, CString q)
{
	return(GetLong(p)*GetLong(q));

}

long RSA_Berechnungen::GetLong(CString eingabe)
{
	return (atol(eingabe));	
}

CString RSA_Berechnungen::GetCString(long eingabe, CString ausgabe)
{
	return (ltoa(eingabe,ausgabe.GetBuffer(20),10));
}
