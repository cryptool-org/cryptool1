/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/cmp_mac.h
 *###
 *### global functions:
 *###
 *###*****************************************//* cmp_mac.h */
/* internal */



/* Macro definitions for CMP ASN.1 */

#ifndef _CMP_MAC_H_
#define _CMP_MAC_H_

extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Extension;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CMP_PKICertReqMsg;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CMP_PKISinglePubInfo;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SeqCertRespMsg;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SeqPubInfo;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CMP_PKICertRespMsg;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CMP_PKIRevDetails;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SeqCertId;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SeqCRL;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CMP_PKICertId;
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CMP_PKIStatusInfo;

#define encode_SeqPubInfo(i, g, h) ASN1e_gen_List(i, g, h)
#define decode_SeqPubInfo(i, f, e, r) ASN1d_gen_List(i, f, e, r)

#define encode_SeqCertRespMsg(i, g, h) ASN1e_gen_List(i, g, h)
#define decode_SeqCertRespMsg(i, f, e, r) ASN1d_gen_List(i, f, e, r)

#define encode_SeqCert(i, g, h) ASN1e_gen_List(i, g, h)
#define decode_SeqCert(i, f, e, r) ASN1d_gen_List(i, f, e, r)

#define encode_Extensions(i, g, h) ASN1e_gen_List(i, g, h)
#define decode_Extensions(i, f, e, r) ASN1d_gen_List(i, f, e, r)

#define encode_CMP_PKIBody_CertRequest(i, g, h) ASN1e_gen_List(i, g, h)
#define decode_CMP_PKIBody_CertRequest(i, f, e, r) ASN1d_gen_List(i, f, e, r)

#define encode_SeqofInfoType(i, g, h) ASN1e_gen_List(i, g, h)
#define decode_SeqofInfoType(i, f, e, r) ASN1d_gen_List(i, f, e, r)

#define encode_SeqofRevDetails(i, g, h) ASN1e_gen_List(i, g, h)
#define decode_SeqofRevDetails(i, f, e, r) ASN1d_gen_List(i, f, e, r)

#define encode_SeqCertId(i, g, h) ASN1e_gen_List(i, g, h)
#define decode_SeqCertId(i, f, e, r) ASN1d_gen_List(i, f, e, r)

#define encode_SeqCRL(i, g, h) ASN1e_gen_List(i, g, h)
#define decode_SeqCRL(i, f, e, r) ASN1d_gen_List(i, f, e, r)

#define encode_SeqStatusInfo(i, g, h) ASN1e_gen_List(i, g, h)
#define decode_SeqStatusInfo(i, f, e, r) ASN1d_gen_List(i, f, e, r)

#define encode_SeqValueAttr(i, g, h) ASN1e_gen_List(i, g, h)
#define decode_SeqValueAttr(i, f, e, r) ASN1d_gen_List(i, f, e, r)

#endif /* _CMP_MAC_H_ */

