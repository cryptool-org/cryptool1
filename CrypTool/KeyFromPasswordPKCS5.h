// Schluessel_gen.h: Schnittstelle für die Klasse Schluessel_gen.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHLUESSEL_GEN_H__68EC2361_1E13_11D5_88AA_00062919F268__INCLUDED_)
#define AFX_SCHLUESSEL_GEN_H__68EC2361_1E13_11D5_88AA_00062919F268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <string.h>

#include <math.h>

#include "arithmet.h"

#include "s_ecconv.h"

#include "s_bithdl.h"

#include "emsa1.h"

#include "pkcs.h"

#include "ECsecude.h"
//#include "CrypToolApp.h"


class CKeyFromPasswordPKCS5  
{
public:
	char *str1;
	OctetString Salt_octetstring;
	OctetString help3;
	OctetString help2;
	OctetString Passwort_octetstring;
	OctetString hash;
	char *str;
	int err;
	L_NUMBER hashwert[MAXLGTH];
	int base;
	int password_based_key_deriv_funct (CString Passwort, CString Salt, CString dkLen, int AlgId, CString zaehler);
	CKeyFromPasswordPKCS5();
	virtual ~CKeyFromPasswordPKCS5();

};

#endif // !defined(AFX_SCHLUESSEL_GEN_H__68EC2361_1E13_11D5_88AA_00062919F268__INCLUDED_)
