//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

#include "secure.h"
#include "pkcs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef LINK_SECUDE

#define DoECAll DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_comp, SEC_PROTOTYPE_2(register L_NUMBER *, Ap,	register L_NUMBER*, Bp))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_mexp, SEC_PROTOTYPE_4(L_NUMBER_ARRAY, bas, L_NUMBER_ARRAY, exp, L_NUMBER_ARRAY , erg, L_NUMBER_ARRAY, modul))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_shift, SEC_PROTOTYPE_3(L_NUMBER_ARRAY, A, int, exp2b, L_NUMBER_ARRAY, S))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_sub, SEC_PROTOTYPE_3(register L_NUMBER_ARRAY, Ap, register L_NUMBER_ARRAY, Bp, register L_NUMBER_ARRAY, Diff))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, rndm, SEC_PROTOTYPE_3(int, lgth,	L_NUMBER_ARRAY, zahl, int, version))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_msub, SEC_PROTOTYPE_4( L_NUMBER_ARRAY, op1, L_NUMBER_ARRAY, op2, L_NUMBER_ARRAY, erg, L_NUMBER_ARRAY, modul))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_mdiv, SEC_PROTOTYPE_4( L_NUMBER_ARRAY, op1, L_NUMBER_ARRAY, op2, L_NUMBER_ARRAY, erg, L_NUMBER_ARRAY, modul))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_mmult, SEC_PROTOTYPE_4( L_NUMBER_ARRAY, op1, L_NUMBER_ARRAY, op2, L_NUMBER_ARRAY, erg, L_NUMBER_ARRAY, modul))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_madd, SEC_PROTOTYPE_4( L_NUMBER_ARRAY, op1, L_NUMBER_ARRAY, op2, L_NUMBER_ARRAY, erg, L_NUMBER_ARRAY, modul))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_div, SEC_PROTOTYPE_4(L_NUMBER_ARRAY, A, L_NUMBER_ARRAY, B, L_NUMBER_ARRAY, Q, L_NUMBER_ARRAY, R))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_mult, SEC_PROTOTYPE_3(L_NUMBER_ARRAY, A, L_NUMBER_ARRAY, B, L_NUMBER_ARRAY, erg))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_add, SEC_PROTOTYPE_3(register L_NUMBER_ARRAY, Ap,	register L_NUMBER_ARRAY, Bp, register L_NUMBER_ARRAY, Sum))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_OctetString2LN2, SEC_PROTOTYPE_2(L_NUMBER*, lnum, OctetString*, ostr))\
	DoOneFn(BitString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_OString2BString, SEC_PROTOTYPE_1(OctetString*, ostr))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_hash_all, SEC_PROTOTYPE_4(OctetString*, in_octets, OctetString*, hash_result, AlgId*, alg_id, HashInput*, hash_input))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, lngtouse, SEC_PROTOTYPE_1(L_NUMBER_ARRAY, modul))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_BitString2LN2, SEC_PROTOTYPE_2(L_NUMBER*, lnum, BitString*, bstr))\
	DoOneData(AlgId, sha1_aid)\
	DoOneData(AlgId, ripemd160_aid)

// erstellen der Typedefs für die SECUDE lib:
#undef SEC_GLOBAL_FUNC_PREFIX
#define SEC_GLOBAL_FUNC_PREFIX
#define DoOneFn(a, b, c, d) typedef a ( b * c##_t ) d;
#define DoOneData(a, b)
DoECAll
#undef DoOneFn
#undef DoOneData

// erstellen der Funktionszeiger 
#define DoOneFn(a, b, c, d) c##_t c;
#define DoOneData(a, b) a * b;

struct Secude_s
{
	DoECAll
#undef DoOneFn
#undef DoOneData
};

extern struct Secude_s ECSecudeLib;

#define SECUDE(a) ECSecudeLib.##a
#define SECUDE_DATA_PTR(a) ECSecudeLib.##a

#else

#define SECUDE(a)	a
#define SECUDE_DATA_PTR(a) &##a

#endif //LINK_SECUDE

#ifdef __cplusplus
}
#endif /* __cplusplus */
