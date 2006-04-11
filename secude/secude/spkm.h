/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/spkm.h
 *###
 *### global functions:
 *###
 *###*****************************************/


#ifndef SPKM_H_
#define SPKM_H_

#include <secude/af.h>

/* lst values of Object Identifier */


/* token id's */


#define GSS_SPKM_S_SG_CONTEXT_DELETED 0x10001


#define SPKM_REQ_ID    0x100
#define SPKM_REP_TI_ID 0x200
#define SPKM_REP_IT_ID 0x300
#define SPKM_ERROR_ID  0x400
#define SPKM_GET_MIC_ID   0x101
#define SPKM_WRAP_ID   0x201
#define SPKM_DEL_ID   0x301

#define SPKM_VERSION_0 (1 << 0)
#define SPKM_VERSIONS (SPKM_VERSION_0)

/* object identifier */
#define SPKM_1_OID        '\053','\006','\001','\005','\005','\001','\001'
#define SPKM_2_OID        '\053','\006','\001','\005','\005','\001','\002'

#define SPKM_HASH_ALG md5_aid

typedef AlgId ConfAlg;
typedef SET_OF_AlgId ConfAlgs;

typedef struct {
	int alg;
	OctetString *key;
} GSSSessionKey;

typedef SEQUENCE_OF(GSSSessionKey) SEQUENCE_OF_SessionKey;

typedef struct  {
	OctetString          *channelId;
	int                  *seqnumber;
	BitString            *options;
	SET_OF_AlgId         *confalg;
	SET_OF_AlgId         *intgalg;
	SET_OF_AlgId         *owfalg;
}   ContextData;

typedef struct     {
	int 		      tokid;
	BitString            *contextid;
	BitString            *pvno;   
	UTCTime              *timestamp;
	BitString            *randSrc;
	DName                *targname;
	DName                *srcname; 
	ContextData          *data;
	Validity             *validity;
	SET_OF_AlgId         *keyestbset;
	BitString            *keyestbreq;
	OctetString          *keysrcbind;
} REQCONTENTS;

typedef ASN1signed_TEMPLATE(REQCONTENTS) REQTOKEN;


typedef struct  {
	CertificationPath    *certificationPath;
	CRL                  *certificateRevocationList;
}   CertificationData;


typedef struct   AuthorizationDataElem  {
	int                   adtype;
	OctetString          *addata;
} AuthorizationDataElem;
typedef SEQUENCE_OF(AuthorizationDataElem) AuthorizationData;


typedef struct     {
	REQTOKEN             *token;
	CertificationData    *certifdata;
	AuthorizationData    *authdata;
} SPKMREQ;

typedef struct  {
	int 		      tokid;
	BitString            *contextid;
	BitString            *pvno;   
	UTCTime              *timestamp;
	BitString            *randTarg;
	DName                *srcname; 
	DName                *targname;
	BitString            *randSrc;
	ContextData          *data;
	Validity             *validity;
	AlgId                *keyestbid;
	BitString            *keyestbstr;
}   REPTICONTENTS;


typedef ASN1signed_TEMPLATE(REPTICONTENTS) REPTITOKEN;

typedef struct  {
	REPTITOKEN           *token;
	CertificationData    *certifdata;
}   SPKMREPTI;

typedef struct  {
	int 	              tokid;
	BitString            *contextid;
	BitString            *randSrc;
	BitString            *randTarg;
	DName                *targname;
	DName                *srcname; 
	BitString            *keyestbrep;
}   REPITTOKEN;


typedef ASN1signed_TEMPLATE(REPITTOKEN) SPKMREPIT;

typedef struct  {
	int 		      tokid;
	BitString            *contextid;
}   ERRORTOKEN;

typedef ASN1signed_TEMPLATE(ERRORTOKEN) SPKMERROR;

typedef struct  {
	int                   num;
	Boolean               dirind;          
}   SeqNum;

typedef struct  {
	BitString            *intcksum;
	BitString            *data;          
}   WrapBody;

typedef struct  {
	int 		      tokid;
	BitString            *contextid;
	AlgId                *intalg;
	AlgId                *confalg;
	SeqNum               *sndseq;
}   WrapHeader;

typedef struct  {
	WrapHeader           *header; 
	WrapBody             *body;
}   SPKMWRAP;

typedef struct  {
	int 		      tokid;
	BitString            *contextid;
	AlgId                *intalg;
	SeqNum               *sndseq;
}   MicHeader;

typedef struct  {
	MicHeader 	     *header;
	BitString            *intcksum;
}   SPKMMIC;

typedef struct  {
	int 		      tokid;
	BitString            *contextid;
	AlgId                *intalg;
	SeqNum               *sndseq;
}   DelHeader;

typedef struct  {
	DelHeader 	     *header;
	BitString            *intcksum;
}   SPKMDEL;

typedef enum {
	SPKM_REQ, 
	SPKM_REP_TI,
	SPKM_REP_IT,
	SPKM_ERROR,
	SPKM_MIC,
	SPKM_WRAP,
	SPKM_DEL } SPKM_TOKEN_TYPES;

typedef struct  {
	SPKM_TOKEN_TYPES 	 type;
	void 			*value;
}   SPKMInnerContextToken;

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_verify_certificationPath SEC_PROTOTYPE_2(
        PSE ,  pse_handle,CertificationPath *, c_path);
CertificationPath SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_certificationPath SEC_PROTOTYPE_1(
        PSE ,  pse_handle);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV build_gss_token SEC_PROTOTYPE_3(
	OctetString *, token,
	OctetString *, objid,
	OctetString *, inner_token
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV parse_gss_token SEC_PROTOTYPE_3(
	OctetString *, token,
	OctetString *, objid,
	OctetString *, inner_token
);
ASN1_en_de_PROTO(SPKMInnerContextToken)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SPKMInnerContextToken;

ASN1_en_de_PROTO(SPKMREQ)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SPKMREQ;

ASN1_en_de_PROTO(SPKMREPTI)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SPKMREPTI;

#define decode_SPKMREPIT(i, f, e, r) \
    (SPKMREPIT *)ASN1decode_SIGNED(i, f, e, (ASN1signed *)r)
#define encode_SPKMREPIT(i, g, f) ASN1encode_SIGNED(i, g, (ASN1signed *)f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SPKMREPIT;

#define decode_SPKMERROR(i, f, e, r) \
    (SPKMERROR *)ASN1decode_SIGNED(i, f, e, (ASN1signed *)r)
#define encode_SPKMERROR(i, g, f) ASN1encode_SIGNED(i, g, (ASN1signed *)f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SPKMERROR;

ASN1_en_de_PROTO(SPKMWRAP)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SPKMWRAP;

ASN1_en_de_PROTO(SPKMMIC)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SPKMMIC;

ASN1_en_de_PROTO(SPKMDEL)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SPKMDEL;

#define decode_REQTOKEN(i, f, e, r) \
    (REQTOKEN *)ASN1decode_SIGNED(i, f, e, (ASN1signed *)r)
#define encode_REQTOKEN(i, g, f) ASN1encode_SIGNED(i, g, (ASN1signed *)f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_REQTOKEN;

#define decode_REPTITOKEN(i, f, e, r) \
    (REPTITOKEN *)ASN1decode_SIGNED(i, f, e, (ASN1signed *)r)
#define encode_REPTITOKEN(i, g, f) ASN1encode_SIGNED(i, g, (ASN1signed *)f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_REPTITOKEN;

#define decode_SEQ_OF_SessionKey(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SEQ_OF_SessionKey(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SEQ_OF_SessionKey;

ASN1_en_de_PROTO(CertificationData)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CertificationData;

ASN1_en_de_PROTO(AuthorizationData)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_AuthorizationData;

ASN1_en_de_PROTO(CertificationPath)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CertificationPath;

ASN1_en_de_PROTO(ContextData)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ContextData;

ASN1_en_de_PROTO(REQCONTENTS)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_REQCONTENTS;

ASN1_en_de_PROTO(ConfAlg)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ConfAlg;

ASN1_en_de_PROTO(ConfAlgs)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ConfAlgs;

ASN1_en_de_PROTO(GSSSessionKey)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SessionKey;

ASN1_en_de_PROTO(REPTICONTENTS)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_REPTICONTENTS;

ASN1_en_de_PROTO(REPITTOKEN)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_REPITTOKEN;

ASN1_en_de_PROTO(ERRORTOKEN)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ERRORTOKEN;

ASN1_en_de_PROTO(SeqNum)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SeqNum;

ASN1_en_de_PROTO(WrapBody)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_WrapBody;

ASN1_en_de_PROTO(WrapHeader)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_WrapHeader;

ASN1_en_de_PROTO(MicHeader)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_MicHeader;

ASN1_en_de_PROTO(DelHeader)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_DelHeader;

ASN1_en_de_PROTO(AuthorizationDataElem)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_AuthorizationDataElem;


#define decode_SEQ_OF_CertificatePair(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SEQ_OF_CertificatePair(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SEQ_OF_CertificatePair;

#define decode_SEQ_OF_AuthorizationDataElem(i, f, e, r) ASN1d_gen_List(i, f, e, r)
#define encode_SEQ_OF_AuthorizationDataElem(i, g, f) ASN1e_gen_List(i, g, f)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SEQ_OF_AuthorizationDataElem;


D_PROTOTYPE(GSS,SPKMInnerContextToken)
E_PROTOTYPE(GSS,SPKMInnerContextToken)
D_PROTOTYPE(GSS,SPKMREQ)
E_PROTOTYPE(GSS,SPKMREQ)
D_PROTOTYPE(GSS,SPKMREPTI)
E_PROTOTYPE(GSS,SPKMREPTI)
D_PROTOTYPE(GSS,SPKMREPIT)
E_PROTOTYPE(GSS,SPKMREPIT)
D_PROTOTYPE(GSS,SPKMERROR)
E_PROTOTYPE(GSS,SPKMERROR)
D_PROTOTYPE(GSS,SPKMWRAP)
E_PROTOTYPE(GSS,SPKMWRAP)
D_PROTOTYPE(GSS,SPKMMIC)
E_PROTOTYPE(GSS,SPKMMIC)
D_PROTOTYPE(GSS,SPKMDEL)
E_PROTOTYPE(GSS,SPKMDEL)
D_PROTOTYPE(GSS,CertificationData)
E_PROTOTYPE(GSS,CertificationData)
D_PROTOTYPE(GSS,AuthorizationData)
E_PROTOTYPE(GSS,AuthorizationData)
D_PROTOTYPE(GSS,CertificationPath)
E_PROTOTYPE(GSS,CertificationPath)
D_PROTOTYPE(GSS,ContextData)
E_PROTOTYPE(GSS,ContextData)
D_PROTOTYPE(GSS,REQCONTENTS)
E_PROTOTYPE(GSS,REQCONTENTS)
D_PROTOTYPE(GSS,AuthorizationDataElem)
E_PROTOTYPE(GSS,AuthorizationDataElem)
D_PROTOTYPE(GSS,REPTICONTENTS)
E_PROTOTYPE(GSS,REPTICONTENTS)
D_PROTOTYPE(GSS,ERRORTOKEN)
E_PROTOTYPE(GSS,ERRORTOKEN)
D_PROTOTYPE(GSS,REPITTOKEN)
E_PROTOTYPE(GSS,REPITTOKEN)
D_PROTOTYPE(GSS,WrapHeader)
E_PROTOTYPE(GSS,WrapHeader)
D_PROTOTYPE(GSS,MicHeader)
E_PROTOTYPE(GSS,MicHeader)
D_PROTOTYPE(GSS,DelHeader)
E_PROTOTYPE(GSS,DelHeader)

AUX_FREE_PROTOTYPE(ContextData)
AUX_FREE_PROTOTYPE(CertificationData)
AUX_FREE_PROTOTYPE(REQTOKEN)
AUX_FREE_PROTOTYPE(REQCONTENTS)
AUX_FREE_PROTOTYPE(AuthorizationData)
AUX_FREE_PROTOTYPE(SPKMREQ)
AUX_FREE_PROTOTYPE(SPKMREPTI)
AUX_FREE_PROTOTYPE(SPKMREPIT)
AUX_FREE_PROTOTYPE(SPKMERROR)
AUX_FREE_PROTOTYPE(SeqNum)
AUX_FREE_PROTOTYPE(MicHeader)
AUX_FREE_PROTOTYPE(SPKMMIC)
AUX_FREE_PROTOTYPE(WrapHeader)
AUX_FREE_PROTOTYPE(WrapBody)
AUX_FREE_PROTOTYPE(SPKMWRAP)
AUX_FREE_PROTOTYPE(DelHeader)
AUX_FREE_PROTOTYPE(SEQUENCE_OF_SessionKey)
AUX_FREE_PROTOTYPE(SPKMDEL)

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ContextData SEC_PROTOTYPE_1(
	ContextData	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CertificationData SEC_PROTOTYPE_1(
	CertificationData	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_REQTOKEN SEC_PROTOTYPE_1(
	REQTOKEN	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SessionKey SEC_PROTOTYPE_1(
	GSSSessionKey	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SEQUENCE_OF_SessionKey SEC_PROTOTYPE_1(
	SEQUENCE_OF_SessionKey	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_REQCONTENTS SEC_PROTOTYPE_1(
	REQCONTENTS	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AuthorizationDataElem SEC_PROTOTYPE_1(
	AuthorizationDataElem	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AuthorizationData SEC_PROTOTYPE_1(
	AuthorizationData	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SPKMREQ SEC_PROTOTYPE_1(
	SPKMREQ	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_REPTICONTENTS SEC_PROTOTYPE_1(
	REPTICONTENTS	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_REPTITOKEN SEC_PROTOTYPE_1(
	REPTITOKEN	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SPKMREPTI SEC_PROTOTYPE_1(
	SPKMREPTI	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_REPITTOKEN SEC_PROTOTYPE_1(
	REPITTOKEN	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SPKMREPIT SEC_PROTOTYPE_1(
	SPKMREPIT	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ERRORTOKEN SEC_PROTOTYPE_1(
	ERRORTOKEN	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SPKMERROR SEC_PROTOTYPE_1(
	SPKMERROR	*	, ptr
);
/*
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SeqNum SEC_PROTOTYPE_1(
	SeqNum	*	, ptr
);
// unnecessary, because has no "content"
*/
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_MicHeader SEC_PROTOTYPE_1(
	MicHeader	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SPKMMIC SEC_PROTOTYPE_1(
	SPKMMIC	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_WrapHeader SEC_PROTOTYPE_1(
	WrapHeader	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_WrapBody SEC_PROTOTYPE_1(
	WrapBody	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SPKMWRAP SEC_PROTOTYPE_1(
	SPKMWRAP	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_DelHeader SEC_PROTOTYPE_1(
	DelHeader	*	, ptr
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SPKMDEL SEC_PROTOTYPE_1(
	SPKMDEL	*	, ptr
);


AUX_PRINT_PROTOTYPE(SPKMREQ)
AUX_PRINT_PROTOTYPE(SPKMREPTI)
AUX_PRINT_PROTOTYPE(SPKMREPIT)
AUX_PRINT_PROTOTYPE(SPKMWRAP)
AUX_PRINT_PROTOTYPE(SPKMMIC)
AUX_PRINT_PROTOTYPE(SPKMERROR)
AUX_PRINT_PROTOTYPE(SPKMDEL)
AUX_PRINT_PROTOTYPE(REQCONTENTS)
AUX_PRINT_PROTOTYPE(REQTOKEN)
AUX_PRINT_PROTOTYPE(Signature)
AUX_PRINT_PROTOTYPE(ContextData)
AUX_PRINT_PROTOTYPE(CertificationData)
AUX_PRINT_PROTOTYPE(REPTITOKEN)
AUX_PRINT_PROTOTYPE(REPITTOKEN)
AUX_PRINT_PROTOTYPE(SeqNum)
AUX_PRINT_PROTOTYPE(WrapBody)
AUX_PRINT_PROTOTYPE(WrapHeader)
AUX_PRINT_PROTOTYPE(MicHeader)
AUX_PRINT_PROTOTYPE(DelHeader)

/*
D_PROTOTYPE(GSS,SPKMERRORTBS)
E_PROTOTYPE(GSS,SPKMERRORTBS)
D_PROTOTYPE(GSS,SPKMERROR)
E_PROTOTYPE(GSS,SPKMERROR)
D_PROTOTYPE(GSS,SPKMWRAP)
E_PROTOTYPE(GSS,SPKMWRAP)
D_PROTOTYPE(GSS,SPKMMIC)
E_PROTOTYPE(GSS,SPKMMIC)
D_PROTOTYPE(GSS,WrapHeader)
E_PROTOTYPE(GSS,WrapHeader)
D_PROTOTYPE(GSS,MicHeader)
E_PROTOTYPE(GSS,MicHeader)
D_PROTOTYPE(GSS,SPKMREPTI)
E_PROTOTYPE(GSS,SPKMREPTI)
D_PROTOTYPE(GSS,SPKMREPIT)
E_PROTOTYPE(GSS,SPKMREPIT)
D_PROTOTYPE(GSS,SPKMREPITTBS)
E_PROTOTYPE(GSS,SPKMREPITTBS)
D_PROTOTYPE(GSS,SPKMREQ)
E_PROTOTYPE(GSS,SPKMREQ)
D_PROTOTYPE(GSS,KeySrcBindTBH)
E_PROTOTYPE(GSS,KeySrcBindTBH)
D_PROTOTYPE(GSS,REQTOKEN)
E_PROTOTYPE(GSS,REQTOKEN)
D_PROTOTYPE(GSS,REPTOKENTBS)
E_PROTOTYPE(GSS,REPTOKENTBS)
D_PROTOTYPE(GSS,CertificationData)
E_PROTOTYPE(GSS,CertificationData)
D_PROTOTYPE(SECAF,CertificationPath)
E_PROTOTYPE(SECAF,CertificationPath)

AUX_FREE_PROTOTYPE(ContextData)
AUX_FREE_PROTOTYPE(CertificationData)
AUX_FREE_PROTOTYPE(REQTOKEN)
AUX_FREE_PROTOTYPE(REQCONTENTS)
AUX_FREE_PROTOTYPE(AuthorizationData)
AUX_FREE_PROTOTYPE(SPKMREQ)
AUX_FREE_PROTOTYPE(REPTOKENTBS)
AUX_FREE_PROTOTYPE(REPTOKEN)
AUX_FREE_PROTOTYPE(SPKMREPTI)
AUX_FREE_PROTOTYPE(SPKMREPITTBS)
AUX_FREE_PROTOTYPE(SPKMREPIT)
AUX_FREE_PROTOTYPE(SPKMERRORTBS)
AUX_FREE_PROTOTYPE(SPKMERROR)
AUX_FREE_PROTOTYPE(SeqNum)
AUX_FREE_PROTOTYPE(MicHeader)
AUX_FREE_PROTOTYPE(SPKMMIC)
AUX_FREE_PROTOTYPE(WrapHeader)
AUX_FREE_PROTOTYPE(WrapBody)
AUX_FREE_PROTOTYPE(SPKMWRAP)
AUX_FREE_PROTOTYPE(DelHeader)
AUX_FREE_PROTOTYPE(SPKMDEL)



typedef struct   KeySrcBindTBH KeySrcBindTBH;
struct   KeySrcBindTBH  {
  DName                *name;
  BitString            *key;
};

typedef struct   SPKMERROR  {
	REPITTOKEN           *token;
	SPKMREPITTBS         *tbs;
	Signature            *sig;          
}   SPKMERROR;

typedef struct     {
	REQCONTENTS 	     *cont;
	Signature            *integrity;   
} REQTOKEN;

typedef struct  {
	REPITTOKEN           *token;
	SPKMREPITTBS         *tbs;
	Signature            *sig;          
}   SPKMREPIT;

typedef struct  {
	REPTICONTENTS        *cont;
	Signature            *integrity;   
}   REPTITOKEN;


*/

#endif

