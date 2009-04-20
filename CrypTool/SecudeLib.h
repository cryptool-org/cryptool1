/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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

#include "asn1.h"
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
	DoOneFn(OctetString * SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_alloc_OctetString, SEC_PROTOTYPE_0())\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_verify_all, SEC_PROTOTYPE_4(OctetString	 *, in_octets,Signature	 *, signature,Key*, key,HashInput*, hash_input))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, arithmetic_comp, SEC_PROTOTYPE_2(register L_NUMBER *, Ap,	register L_NUMBER*, Bp))\
	DoOneFn(SET_OF_Name SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  af_cadb_list_user, SEC_PROTOTYPE_1(PSE, pse_handle))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  af_pse_get, SEC_PROTOTYPE_3(PSE ,pse_handle,char*, objname,ObjId*	, objtype))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_pse_update, SEC_PROTOTYPE_4(PSE , pse_handle,char*, objname,void *, opaque,ObjId*, opaque_type))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_pse_update_SerialNumber, SEC_PROTOTYPE_2(PSE, pse_handle, SerialNumber *, serial))\
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
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_hash_init, SEC_PROTOTYPE_3(void **, context, AlgId*, alg_id, HashInput*, hash_input))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_hash_more, SEC_PROTOTYPE_2(void **, context, OctetString*, in_octets))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_hash_end, SEC_PROTOTYPE_2(void **, context, OctetString*, hash_result))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  aux_sprint_Certificate, SEC_PROTOTYPE_3(PSE, pse_handle, char*, string, Certificate	*, cert))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  aux_sprint_error, SEC_PROTOTYPE_3(PSE, pse_handle, char *, string, int, verbose))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_LN2OctetString, SEC_PROTOTYPE_2(L_NUMBER_ARRAY, lnum, int, size))\
	DoOneFn(PSE SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_create, SEC_PROTOTYPE_5(char*, psename, char*, cadir, char*, pin, SC_DATA*, sc_data, Boolean, onekeypaironly))\
	DoOneFn(PSESel SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, sec_create, SEC_PROTOTYPE_4(char *, psename, char *, pin, SC_DATA *, sc_data, Boolean, onekeypaironly))\
	DoOneFn(Certificate SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, af_cadb_get_Certificate, SEC_PROTOTYPE_2(PSE, pse_handle, OctetString*, serial))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_BString2OString, SEC_PROTOTYPE_1(BitString*, bstr))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_Certificate, SEC_PROTOTYPE_1(Certificate**, cert))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_Certificates, SEC_PROTOTYPE_1(Certificates**, to_be_freed))\
	DoOneFn(ContentInfo SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, d_ContentInfo, SEC_PROTOTYPE_1(OctetString*, asn1_string))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_SET_OF_IssuedCertificate, SEC_PROTOTYPE_1(SET_OF_IssuedCertificate**, isscertset))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_close, SEC_PROTOTYPE_1(PSE, pse_handle))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_close, SEC_PROTOTYPE_1(PSESel *, pse_sel))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_encrypt_all, SEC_PROTOTYPE_5(PSE, pse_handle, OctetString*, inoctets, BitString*, outbits, Key*, key, DName*, dname))\
	DoOneFn(SET_OF_IssuedCertificate SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, af_cadb_get_user, SEC_PROTOTYPE_2(PSE, pse_handle, Name*, name))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, th_get_last_error_text, SEC_PROTOTYPE_0())\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, th_last_error, SEC_PROTOTYPE_0())\
	DoOneFn(PSE SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_open, SEC_PROTOTYPE_4(char*, psename, char*, cadir, char*, pin, SC_DATA*, sc_data))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_file2OctetString, SEC_PROTOTYPE_1(const char*, fn))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, sdumpasn, SEC_PROTOTYPE_3(OctetString*, ostr, int, options, int, displayed_offset))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_adump, SEC_PROTOTYPE_4(char*,from,int,num,int,options,int,displayed_offset))\
	DoOneFn(DName SEC_GLOBAL_FUNC_PREFIX *,SEC_API_CALLING_CONV,af_pse_get_Name,SEC_PROTOTYPE_1(PSE,pse_handle))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,aux_DName2Attr,SEC_PROTOTYPE_2(DName*,dname,char*,attr_key))\
	DoOneFn(SerialNumber SEC_GLOBAL_FUNC_PREFIX *,SEC_API_CALLING_CONV,af_pse_get_SerialNumber,SEC_PROTOTYPE_1(PSE,pse_handle))\
	DoOneFn(Certificates SEC_GLOBAL_FUNC_PREFIX *,SEC_API_CALLING_CONV,af_pse_get_Certificates,SEC_PROTOTYPE_3(PSE,pse_handle,KeyType,type,DName*,name))\
	DoOneFn(CrlSet SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,af_pse_get_CrlSet,SEC_PROTOTYPE_1(PSE,pse_handle))\
	DoOneFn(PSEToc SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, d_PSEToc, SEC_PROTOTYPE_1(OctetString*, asn1_string))\
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
	DoOneFn(ObjId SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  aux_cpy_ObjId, SEC_PROTOTYPE_1(ObjId	*, oid))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  aux_cpy_String, SEC_PROTOTYPE_1(char *, str))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_String, SEC_PROTOTYPE_1(char	**	, str))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_onekeypaironly, SEC_PROTOTYPE_1(PSESel *, pse_sel))\
	DoOneFn(PSESel SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, af_get_PSESel, SEC_PROTOTYPE_2(PSE, pse_hdl, ObjId *, af_object))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_latin1_to_unicode, SEC_PROTOTYPE_2(char *, latin_string, Boolean, termination))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_calloc, SEC_PROTOTYPE_2(size_t, nr, size_t, size))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_malloc, SEC_PROTOTYPE_1(size_t, size))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  aux_cpy_OctetString, SEC_PROTOTYPE_1(OctetString *, ostr))\
	DoOneFn(PrivateKeyInfo SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  aux_create_PrivateKeyInfo, SEC_PROTOTYPE_3(KeyInfo *, key, Certificate *, cert, SET_OF_Attr *, attributes))\
	DoOneFn(FCPath SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  af_pse_get_FCPath, SEC_PROTOTYPE_2(PSE, pse_handle, DName *, name))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_FCPath, SEC_PROTOTYPE_1(	FCPath	**	, path))\
	DoOneFn(PKRoot SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  af_pse_get_PKRoot, SEC_PROTOTYPE_1(PSE, pse_handle))\
	DoOneFn(Certificate SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  af_PKRoot2Protocert, SEC_PROTOTYPE_1(PKRoot *, pkroot))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_PKRoot, SEC_PROTOTYPE_1(	PKRoot	**	, pkroot))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_RSAPrivateKey, SEC_PROTOTYPE_1(RSAPrivateKey **	, privkey))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, pkcs12_encode, SEC_PROTOTYPE_3(P12_Safe *, safe, OctetString *, password, OctetString *, asn1_out))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_error, SEC_PROTOTYPE_0())\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_pse_update_PKRoot, SEC_PROTOTYPE_2(PSE, pse_handle, PKRoot *, pkroot))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_cmp_DName, SEC_PROTOTYPE_2(DName *, a, DName *, b))\
	DoOneFn(PKRoot SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_create_PKRoot, SEC_PROTOTYPE_2(Certificate *, cert1, Certificate *, cert2))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_write_PSE, SEC_PROTOTYPE_2(PSESel *, pse_sel, OctetString *, value))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, e_FCPath, SEC_PROTOTYPE_1(FCPath *, fcpath))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, e_Certificate, SEC_PROTOTYPE_1(Certificate *, certificate))\
	DoOneFn(AlgEnc SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_ObjId2AlgEnc, SEC_PROTOTYPE_1(ObjId *, given_objid))\
	DoOneFn(RSAPrivateKey SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, d_RSAPrivateKey, SEC_PROTOTYPE_1(OctetString *, asn1_string))\
	DoOneFn(BitString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, e_KeyBits, SEC_PROTOTYPE_1(KeyBits *, kb))\
	DoOneFn(AlgId SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_cpy_AlgId, SEC_PROTOTYPE_1(AlgId *, aid))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, e_KeyInfo, SEC_PROTOTYPE_1(KeyInfo *, ki))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, e_PKRoot, SEC_PROTOTYPE_1(PKRoot *, pkroot))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, pkcs12_decode, SEC_PROTOTYPE_4(OctetString *, asn1string, OctetString *, password, P12_Safe *, safe, Boolean *, verified))\
	DoOneFn(Certificate SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, af_pse_get_Certificate, SEC_PROTOTYPE_4(PSE, pse_handle, KeyType, type, DName *, issuer, OctetString *, serial))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_DName2Name, SEC_PROTOTYPE_1(DName *, name_ae))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, aux_sprint_AlgId, SEC_PROTOTYPE_2(char *, string, AlgId *, aid))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, e_PrintableString, SEC_PROTOTYPE_1(char *, infostruct))\
	DoOneFn(char SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, d_PrintableString, SEC_PROTOTYPE_1(OctetString *, asn1string))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_cmp_ObjId, SEC_PROTOTYPE_2(ObjId *, oid1, ObjId *, oid2))\
	DoOneFn(ObjId SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  af_get_objoid, SEC_PROTOTYPE_1(char *, objname))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_pse_get_keysize, SEC_PROTOTYPE_4(PSE , pse_handle, int *, sig, int *, enc, AlgEnc *, sig_type))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_write, SEC_PROTOTYPE_2(PSESel	*, pse_sel, OctetString	 *, content))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_read, SEC_PROTOTYPE_2(PSESel *, pse_sel, OctetString *, content))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_read_PSE, SEC_PROTOTYPE_2(PSESel *, pse_sel, OctetString *, value))\
	DoOneFn(KeyInfo SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  d_KeyInfo, SEC_PROTOTYPE_1(OctetString *, asn1_string))\
	DoOneFn(AlgId SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  aux_Name2AlgId, SEC_PROTOTYPE_1(char *, name))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, af_get_options, SEC_PROTOTYPE_2(PSE, pse,	AF_options *, options))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_cpy2_AlgId, SEC_PROTOTYPE_2(AlgId *, dup_aid, AlgId *, aid))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free2_AlgId, SEC_PROTOTYPE_1(register AlgId *, algid))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_cpy2_ObjId, SEC_PROTOTYPE_2(ObjId *, dup_oid, ObjId *, oid))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free2_BitString, SEC_PROTOTYPE_1(BitString *, bstr))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free_PSESel, SEC_PROTOTYPE_1(PSESel **, pse_sel))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, e_AlgId, SEC_PROTOTYPE_1(AlgId *, algid))\
	DoOneFn(RC SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, rsa_sign_all, SEC_PROTOTYPE_3(OctetString *, hash,	BitString *, sign, KeyBits *, key))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_get_key, SEC_PROTOTYPE_2(KeyInfo *, keyinfo, Key *, key))\
	DoOneFn(PSESel SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  sec_open, SEC_PROTOTYPE_3(char *, pse_name,	char *, pin, SC_DATA *, sc_data))\
	DoOneFn(Certificate SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV,  d_Certificate, SEC_PROTOTYPE_1(OctetString *, asn1_string))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free2_KeyBits, SEC_PROTOTYPE_1(register KeyBits *, p))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free2_KeyInfo, SEC_PROTOTYPE_1(register KeyInfo *, p))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_free2_OctetString, SEC_PROTOTYPE_1(OctetString *, ostr))\
	DoOneFn(int SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, aux_cpy2_BitString, SEC_PROTOTYPE_2(BitString *, dup_bstr, BitString *, bstr))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_MD2Init, SEC_PROTOTYPE_1(SEC_MD2_CTX *, context))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_MD2Update, SEC_PROTOTYPE_3(SEC_MD2_CTX *, context, unsigned char *, input, sec_uint4, inputLen))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_MD2Final, SEC_PROTOTYPE_2(unsigned char *, digest, SEC_MD2_CTX *, context))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_MD4Init, SEC_PROTOTYPE_1(SEC_MD4_CTX *, context))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_MD4Update, SEC_PROTOTYPE_3(SEC_MD4_CTX *, context, unsigned char *, input, sec_uint4, inputLen))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_MD4Final, SEC_PROTOTYPE_2(unsigned char *, digest, SEC_MD4_CTX *, context))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_MD5Init, SEC_PROTOTYPE_1(SEC_MD5_CTX *, context))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_MD5Update, SEC_PROTOTYPE_3(SEC_MD5_CTX *, context, unsigned char *, input, sec_uint4, inputLen))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, sec_MD5Final, SEC_PROTOTYPE_2(unsigned char *, digest, SEC_MD5_CTX *, context))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, shsInit, SEC_PROTOTYPE_1(SHS_INFO *, shsInfo))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, shsUpdate, SEC_PROTOTYPE_3(SHS_INFO *, shsInfo, unsigned char *, buffer, sec_int4, count))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, shsFinal, SEC_PROTOTYPE_1(SHS_INFO *, shsInfo))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, shs1Init, SEC_PROTOTYPE_1(SHS_INFO *, shsInfo))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, shs1Update, SEC_PROTOTYPE_3(SHS_INFO *, shsInfo, unsigned char *, buffer, sec_int4, count))\
	DoOneFn(void SEC_GLOBAL_FUNC_PREFIX, SEC_API_CALLING_CONV, shs1Final, SEC_PROTOTYPE_1(SHS_INFO *, shsInfo))\
	DoOneFn(OctetString SEC_GLOBAL_FUNC_PREFIX *, SEC_API_CALLING_CONV, sec_random_ostr, SEC_PROTOTYPE_2(sec_uint4, noctects, int, security))\
	DoOneData(AlgId, ripemd160WithRSASignature_aid)\
	DoOneData(AlgId, shaWithRSASignature_aid)\
	DoOneData(AlgId, md2WithRsaEncryption_aid)\
	DoOneData(AlgId, md2WithRSASignature_aid)\
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
	DoOneData(AlgId, rsaEncryption_aid)\
	DoOneData(AlgId, dsaWithSHA_aid)\
	DoOneData(AlgId, dsaWithSHA1_aid)\
	DoOneData(ObjId *, Uid_OID)\
	DoOneData(ObjId *, Cert_OID)\
	DoOneData(ObjId, sha1_oid)\
	DoOneData(ObjId, pbeWithSHA1And40BitRC2CBC_oid)\
	DoOneData(ObjId, pbeWithSHA1AndDES3xCBC_oid)\
	DoOneData(ObjId, PKRoot_oid)\
	DoOneData(ObjId, SKnew_oid)\
	DoOneData(ObjId, Cert_oid)\
	DoOneData(ObjId, FCPath_oid)\
	DoOneData(sec_uint4, print_cert_flag)\
	DoOneData(sec_uint4, print_keyinfo_flag)
	

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
	int GetStatus() { return Status; }
	void ErrorMessage( UINT resid, PSE pse_handle);
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
