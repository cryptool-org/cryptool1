//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
//
// SecudeLib.h: Schnittstelle für die Klasse CSecudeLib.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECUDELIB_H__E0C5A5EC_D231_11D3_878C_00C04F795E36__INCLUDED_)
#define AFX_SECUDELIB_H__E0C5A5EC_D231_11D3_878C_00C04F795E36__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "secure.h"
#include "pkcs.h"

// DoOneFn(return type, calling converntion, name, Prototype (SEC_PROTOTYPE_x(...))
// DoOneData(type, name)

#define DoAll DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, SECUDE_HasValidTicket,  SEC_PROTOTYPE_1(char ** , rcIdOrError)) \
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, light_version, SEC_PROTOTYPE_0())\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_sprint_version, SEC_PROTOTYPE_1(char *,string))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_sxdump2, SEC_PROTOTYPE_4(char *,a,char *,b,sec_int4,c,sec_int4,d))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_sxdump, SEC_PROTOTYPE_4(char *,a,char *,b,sec_int4,c,sec_int4,d))\
	DoOneFn(KeyBits SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, d_KeyBits, SEC_PROTOTYPE_1(BitString *,s))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_cadb_add_Certificate, SEC_PROTOTYPE_3(PSE, pse_handle,KeyType, keytype,	Certificate	 *,newcert))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_OctetString, SEC_PROTOTYPE_1(OctetString	**, ostr))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_verify_all, SEC_PROTOTYPE_4(OctetString	 *, in_octets,Signature	 *, signature,Key*, key,HashInput*, hash_input))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_comp, SEC_PROTOTYPE_2(register L_NUMBER *, Ap,	register L_NUMBER*, Bp))\
	DoOneFn(SET_OF_Name SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  af_cadb_list_user, SEC_PROTOTYPE_1(PSE, pse_handle))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  af_pse_get, SEC_PROTOTYPE_3(PSE ,pse_handle,char*, objname,ObjId*	, objtype))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_pse_update, SEC_PROTOTYPE_4(PSE , pse_handle,char*, objname,void *, opaque,ObjId*, opaque_type))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, e_OctetString, SEC_PROTOTYPE_1(OctetString*	, ostr))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, lngtouse, SEC_PROTOTYPE_1(L_NUMBER_ARRAY, modul))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_OctetString2LN2, SEC_PROTOTYPE_2(L_NUMBER*, lnum, OctetString*, ostr))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  d_OctetString, SEC_PROTOTYPE_1(OctetString	*, asn1_string))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_DName, SEC_PROTOTYPE_1(DName**,dn))\
	DoOneFn(int	 SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_OctetString2file, SEC_PROTOTYPE_3(OctetString *, ostr,	char *, fn,int, flag))\
	DoOneFn(Certificate  SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, af_certify, SEC_PROTOTYPE_5(PSE, pse_handle, Certificate *, tbc_cert,	Validity*, validity, AlgId*, sig_alg,DName*, name))\
	DoOneFn(Certificate SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  af_create_Certificate, SEC_PROTOTYPE_10(PSE ,  pse_handle,KeyInfo*, keyinfo, AlgId*, sig_alg, char*, obj_name, DName*, subject, OctetString*, serial, GeneralNames *, subject_names, KeyIdentifier*, subjKeyId, Boolean, CA, KeyUsage *, key_usage))\
	DoOneFn(DName SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_Name2DName, SEC_PROTOTYPE_1(register char*, name))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_gen_key, SEC_PROTOTYPE_4(PSE, pse_handle, Key*, key, KeyType, ktype, Boolean, replace))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_encrypt_all, SEC_PROTOTYPE_3(OctetString*, in_octets, BitString*, out_bits, Key*, key))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_decrypt_all, SEC_PROTOTYPE_3(BitString*, in_bits, OctetString*, out_octets, Key*, key))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_mexp, SEC_PROTOTYPE_4(L_NUMBER_ARRAY, bas, L_NUMBER_ARRAY, exp, L_NUMBER_ARRAY , erg, L_NUMBER_ARRAY, modul))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_shift, SEC_PROTOTYPE_3(L_NUMBER_ARRAY, A, int, exp2b, L_NUMBER_ARRAY, S))\
	DoOneFn(BitString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_OString2BString, SEC_PROTOTYPE_1(OctetString*, ostr))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_BitString2LN2, SEC_PROTOTYPE_2(L_NUMBER*, lnum, BitString*, bstr))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_sub, SEC_PROTOTYPE_3(register L_NUMBER_ARRAY, Ap, register L_NUMBER_ARRAY, Bp, register L_NUMBER_ARRAY, Diff))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, rndm, SEC_PROTOTYPE_3(int, lgth,	L_NUMBER_ARRAY, zahl, int, version))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_msub, SEC_PROTOTYPE_4( L_NUMBER_ARRAY, op1, L_NUMBER_ARRAY, op2, L_NUMBER_ARRAY, erg, L_NUMBER_ARRAY, modul))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_mdiv, SEC_PROTOTYPE_4( L_NUMBER_ARRAY, op1, L_NUMBER_ARRAY, op2, L_NUMBER_ARRAY, erg, L_NUMBER_ARRAY, modul))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_mmult, SEC_PROTOTYPE_4( L_NUMBER_ARRAY, op1, L_NUMBER_ARRAY, op2, L_NUMBER_ARRAY, erg, L_NUMBER_ARRAY, modul))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_madd, SEC_PROTOTYPE_4( L_NUMBER_ARRAY, op1, L_NUMBER_ARRAY, op2, L_NUMBER_ARRAY, erg, L_NUMBER_ARRAY, modul))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_div, SEC_PROTOTYPE_4(L_NUMBER_ARRAY, A, L_NUMBER_ARRAY, B, L_NUMBER_ARRAY, Q, L_NUMBER_ARRAY, R))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_mult, SEC_PROTOTYPE_3(L_NUMBER_ARRAY, A, L_NUMBER_ARRAY, B, L_NUMBER_ARRAY, erg))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_add, SEC_PROTOTYPE_3(register L_NUMBER_ARRAY, Ap,	register L_NUMBER_ARRAY, Bp, register L_NUMBER_ARRAY, Sum))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_hash_all, SEC_PROTOTYPE_4(OctetString*, in_octets, OctetString*, hash_result, AlgId*, alg_id, HashInput*, hash_input))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  aux_sprint_Certificate, SEC_PROTOTYPE_3(PSE, pse_handle, char*, string, Certificate	*, cert))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_LN2OctetString, SEC_PROTOTYPE_2(L_NUMBER_ARRAY, lnum, int, size))\
	DoOneFn(PSE SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_create, SEC_PROTOTYPE_5(char*, psename, char*, cadir, char*, pin, SC_DATA*, sc_data, Boolean, onekeypaironly))\
	DoOneFn(Certificate SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, af_cadb_get_Certificate, SEC_PROTOTYPE_2(PSE, pse_handle, OctetString*, serial))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_BString2OString, SEC_PROTOTYPE_1(BitString*, bstr))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_Certificate, SEC_PROTOTYPE_1(Certificate**, cert))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_SET_OF_IssuedCertificate, SEC_PROTOTYPE_1(SET_OF_IssuedCertificate**, isscertset))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_close, SEC_PROTOTYPE_1(PSE, pse_handle))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_encrypt_all, SEC_PROTOTYPE_5(PSE, pse_handle, OctetString*, inoctets, BitString*, outbits, Key*, key, DName*, dname))\
	DoOneFn(SET_OF_IssuedCertificate SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, af_cadb_get_user, SEC_PROTOTYPE_2(PSE, pse_handle, Name*, name))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, th_get_last_error_text, SEC_PROTOTYPE_0())\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, th_last_error, SEC_PROTOTYPE_0())\
	DoOneFn(PSE SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_open, SEC_PROTOTYPE_4(char*, psename, char*, cadir, char*, pin, SC_DATA*, sc_data))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_file2OctetString, SEC_PROTOTYPE_1(const char*, fn))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_decrypt_all, SEC_PROTOTYPE_4(PSE, pse_handle, BitString*, inbits, OctetString*, outoctets, Key*, key))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_sign_all, SEC_PROTOTYPE_3(PSE, pse_handle, OctetString*, in_octets, Signature*, signature))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free, SEC_PROTOTYPE_1(void*, ptr))\
	DoOneFn(struct ErrStack SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, th_remove_last_error, SEC_PROTOTYPE_0())\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_BitString, SEC_PROTOTYPE_1(	BitString	**	, bstr))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_AlgId, SEC_PROTOTYPE_1(	AlgId	**	, bstr))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_KeyInfo, SEC_PROTOTYPE_1(	KeyInfo	**	, bstr))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_ObjId, SEC_PROTOTYPE_1(	ObjId	**	, bstr))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_KeyBits, SEC_PROTOTYPE_1(	KeyBits	**	, bstr))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_PSEToc, SEC_PROTOTYPE_1(	PSEToc	**	, bstr))\
	DoOneData(AlgId, ripemd160WithRSASignature_aid)\
	DoOneData(AlgId, shaWithRSASignature_aid)\
	DoOneData(AlgId, md2WithRsaEncryption_aid)\
	DoOneData(AlgId, dsa_aid)\
	DoOneData(AlgId, rc2CBC_aid)\
	DoOneData(AlgId, rc4_aid)\
	DoOneData(AlgId, md5WithRsaEncryption_aid)\
	DoOneData(AlgId, desEDE_aid)\
	DoOneData(AlgId, desCBC3_aid)\
	DoOneData(AlgId, desCBC_pad_aid)\
	DoOneData(AlgId, desECB_aid)\
	DoOneData(AlgId, idea_aid)\
	DoOneData(AlgId, md2_aid)\
	DoOneData(AlgId, md4_aid)\
	DoOneData(AlgId, md5_aid)\
	DoOneData(AlgId, sha_aid)\
	DoOneData(AlgId, sha1_aid)\
	DoOneData(AlgId, ripemd160_aid)\
	DoOneData(AlgId, sha1WithRSASignature_aid)\
	DoOneData(AlgId, rsa_aid)\
	DoOneData(AlgId, dsaWithSHA_aid)\
	DoOneData(AlgId, dsaWithSHA1_aid)\
	DoOneData(ObjId *, Uid_OID)

// erstellen der Typedefs für die SECUDE lib:
#undef SEC_GLOBAL_FUNC_PREFIX
#define SEC_GLOBAL_FUNC_PREFIX
#define DoOneFn(a, b, c, d) typedef a ( b * c##_t ) d;
#define DoOneData(a, b)
DoAll
#undef DoOneFn
#undef DoOneData
//typedef RC (  __stdcall * SECUDE_HasValidTicket_t ) (char ** rcIdOrError);


// erstellen der Funktionszeiger 
#define DoOneFn(a, b, c, d) c##_t c;
#define DoOneData(a, b) a * b;

class CSecudeLib  
{
public:
	int CloseSecudeLib( void );
	int OpenSecudeLib( void );
	CSecudeLib();
	virtual ~CSecudeLib();
	DoAll
#undef DoOneFn
#undef DoOneData
//	SECUDE_HasValidTicket_t SECUDE_HasValidTicket;
	int MaxBits;
private:
	HINSTANCE hDLL;
	int Status;
};

#endif // !defined(AFX_SECUDELIB_H__E0C5A5EC_D231_11D3_878C_00C04F795E36__INCLUDED_)