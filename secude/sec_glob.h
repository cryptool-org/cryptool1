/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

/*-----------------------------------------------------------------------*/
/* INCLUDE FILE  sec_global.h                                            */
/* Definition of structures and types for the basic functions   	 */
/*-----------------------------------------------------------------------*/

#ifndef _SEC_GLOBAL_
#define _SEC_GLOBAL_

#include "sec_conf.h"

/* MPW-C defines 'Boolean', too */
#if (defined(applec)||defined(_MAC))
#include <types.h>
#else
/* X11/Intrinsic.h defines 'Boolean', too */
#ifndef _XtIntrinsic_h
typedef char                    Boolean;
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef TeSECUDE

/*-----------------------------------------------------------------------*/
/* 	If SECUDE is used together with the Telesec SME-software	 */
/* 	the following names must be redefined to get unique names.	 */
/*      The SME-software uses the same names.  				 */
/*-----------------------------------------------------------------------*/

#define givenName 		TSgivenName
#define localityName 		TSlocalityName
#define serialNumber 		TSserialNumber
#define countryName 		TScountryName
#define nameDistinguisher 	TSnameDistinguisher
#define streetAddress		TSstreetAddress
#define stateOrProvinceName 	TSstateOrProvinceName
#define commonName		TScommonName
#define title			TStitle
#define businessCategory	TSbusinessCategory
#define Validity 		TSValidity 

#define ToBeSigned		TSToBeSigned
#define Certificate 		TSCertificate 
#define Attribute 		TSAttribute
#define UTCTime			TSUTCTime 
#define KeyType			TSKeyType
#define Name			TSName
#define PrintableString		TSPrintableString

#define rsa			TSrsa
#define idea 			TSidea
#define md5WithRsaEncryption 	TSmd5WithRsaEncryption
#define md4WithRsaEncryption 	TSmd4WithRsaEncryption
#define rsaEncryption 		TSrsaEncryption

#define ASN1info_TSCertificate ASN1info_Certificate
#define ASN1info_TSValidity ASN1info_Validity
#define ASN1info_TSUTCTime ASN1info_UTCTime
#define ASN1info_TSPrintableString ASN1info_PrintableString
#define decode_TSPrintableString decode_PrintableString
#define decode_TSValidity decode_Validity
#define decode_TSUTCTime decode_UTCTime
#define decode_TSCertificate decode_Certificate
#define TSrsa_OID rsa_OID
#define TSidea_OID idea_OID
#define TSrsa_oid rsa_oid
#define TSidea_oid idea_oid
#define TSmd5WithRsaEncryption_OID md5WithRsaEncryption_OID 	
#define TSmd4WithRsaEncryption_OID md4WithRsaEncryption_OID 	
#define TSrsaEncryption_OID rsaEncryption_OID 		
#define TSmd5WithRsaEncryption_oid md5WithRsaEncryption_oid 	
#define TSmd4WithRsaEncryption_oid md4WithRsaEncryption_oid 	
#define TSrsaEncryption_oid rsaEncryption_oid 		

#endif	/* TeSECUDE */



#define T_1SEC		1
#define T_1MIN		60
#define T_1HOUR		( 60*60 )
#define T_1DAY		( 24*60*60 )
#define T_1MONTH	( 30*24*60*60 )		/* Aenderung J.Luehe 15.Juni 1992 */
#define T_1YEAR         ( 365*24*60*60 )


typedef struct
  {
    int		sec;	/* seconds		0 -> 59			*/
    int		minu;	/* minutes		0 -> 59			*/
    int		hour;	/* hours		0 -> 23			*/
    int		day;    /* day of month		0 -> (27,28,29,30)	*/
    int		mon;	/* month		0 -> 11			*/
    int		year;   /* year			AD			*/
    int		zone;	/* time zone (minutes east of GMT) -720 -> 720	*/
	int     wday;   /* day of week  0=Mon to 6=Sun */
  }
	T_REC;


#define TX_MAXLEN	17





#define freepin(pin) {if(pin) { bzero(pin, strlen(pin)); free(pin); pin = CNULL;}}
#define aux_freepin(pin) {if(pin) { bzero(pin, strlen(pin)); aux_free(pin); pin = CNULL;}}

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define CNULL (char *)0


#ifdef MACRO_SEP_LIKE_STDC
#define SET_OF(t) struct set_of_##t {               \
        t *element;                                 \
        struct set_of_##t *next;                    \
}
#define SEQUENCE_OF(t) struct sequence_of_##t {     \
        t *element;                                 \
        struct sequence_of_##t *next;               \
}
#else
#define SET_OF(t) struct set_of_/**/t {             \
        t *element;                                 \
        struct set_of_/**/t *next;                  \
}
#define SEQUENCE_OF(t) struct sequence_of_/**/t {   \
        t *element;                                 \
        struct sequence_of_/**/t *next;             \
}
#endif /* MAC */

/*-----------------------------------------------------------------------*/
/*    T y p e d e f ' s   f o r   s e c                                  */
/*-----------------------------------------------------------------------*/


typedef int                     RC;
typedef enum { SEC_END, SEC_MORE }  More;

typedef struct OctetString      OctetString;

typedef struct BitString        BitString;
typedef struct BitString        ENCRYPTED;
typedef struct EncryptedKey     EncryptedKey;  /* e.g. for rsa-encrypted 
                                                  DES-keys               */ 
typedef struct Signature        Signature; 
typedef struct DigestInfo       DigestInfo;

typedef char                    UTCTime;
typedef char			GeneralTime;
typedef char			TIMEType;

typedef struct AlgId            AlgId;
typedef SET_OF(AlgId)           SET_OF_AlgId;
typedef struct AlgList          AlgList;
typedef struct KeyInfo          KeyInfo;
typedef struct KeyBits          KeyBits;

typedef struct ErrStack         ErrStack;



#define NULLOBJID ((ObjId *) 0)
#define NULLALGID ((AlgId *) 0)
#define NULLOCTETSTRING ((OctetString *) 0)
#define NULLBITSTRING   ((BitString *) 0)

/*-----------------------------------------------------------------------*/
/*    T e x t s                                                        */
/*-----------------------------------------------------------------------*/

#define TERROR		0x7001
#define TWARNING	0x7002
/*-----------------------------------------------------------------------*/
/*    E r r o r s                                                        */
/*-----------------------------------------------------------------------*/

#define EALGID          1
#define ESCPSEOPEN      2
#define ESCPSENOTOPEN   3
#define ECREATEPSE      4
#define EOBJ            5
#define EALGIDKS        6
#define EOBJNAME        0x1012
#define ECREATEOBJ      7
#define EKEYSIZE        8
#define EVERIFY         9
#define ESYSTEM         10
#define EMALLOC         13
#define EENCODE         17
#define EDECODE         18
#define EREADPSE        22
#define EKEYNOTREADABLE        25
#define EWRITEPSE       23
#define EPATH           24
#define EROOTCERT       27
#define EVALIDITY      101
#define EPK            102
#define ENOPK          104
#define ENONAME        105
#define EROOTKEY       106
#define ENODIR         107
#define ENAMEDIR       108
#define EACCDIR        109
#define EATTRDIR       110
#define EUPDATE        111
#define EPARSE         112
#define EPKCROSS       113
#define EREVOKE        114
#define EAVAILABLE     115
#define ESCARD         214
#define ESCT         215
#define EDEVLOCK       216
#define ENOCRL         217
#define EWRITEFILE     218
#define EREADFILE      219

#define EINVALID         	0x0500
#define EFILENOTEXISTING        0x0501
#define ECONTEXTINVALID 	0x0502
#define EFILENOTWRITABLE        0x0503
#define EWRONGKEYSIZEDSA        0x0504
#define EWRONGPARM         	0x0505
#define EINTERNAL		0x0506
#define EWRONGVERSION		0x0507
#define ESTATE 	0x0508
#define ERANDOM 	0x0509

#define EPLUGINVER		0x05FE
#define ENOTSUPPORTED		0x05FF

#define EUNKNOWNALGID         	0x0600
#define EALGNOTFITKEY	 	0x0601
#define ENEEDHASHALG	        0x0602
#define ENEEDSIGALG	        0x0605
#define ENEEDENCALG	        0x0606

#define EDECRYPTION        	0x0700
#define EPIN            	0x0720
#define EPINFROMENV            	0x0722
#define ENODSAPARAMETERS	0x0780
#define ESWAPPEDDSASIG      0x0781

#define EPSESYSOPEN      	0x1002  
#define EPSESYSREAD      	0x1003  
#define EPSESYSWRITE     	0x1004  
#define EPSESYSUNLINK    	0x1006  
#define EPSESYSMKDIR     	0x1007  
#define EPSESYSRMDIR     	0x1008  
#define EPSESYSRENAME     	0x1009  
#define EPSESYSFSTAT     	0x1010  
/* see above for EOBJNAME       0x1012 */
#define EPSEALREADYEXISTING 	0x1020
#define EPSENOTEXISTING 	0x1021
#define EPSEOBJECTNOTEXISTING 	0x1022
#define EPSEOBJECTDAMAGED 	0x1023

#define EPSEFILE		0x1100
#define EPSEFILEINCONSISTENT	0x1101
#define EPSEFILEBASE64		0x1102
#define EPSEFILEWRITEMODE	0x1103
#define EPSEFILESTRUCTURE	0x1104

#define EMPSEFILE		0x1180
#define EMPSEFILESTRUCTURE	0x1181
#define EMPSEFILERANGE		0x1182

/* Smartcard specific error codes */
#define ECONFIGONEKEYPAIR  	0x2001
#define ESCPSENEEDED	  	0x2003
#define ESCPSENOTEXISTING  	0x2004	
#define ESCA	       		0x2005	
#define ESWPIN	       		0x2006	
#define ECONFIG        		0x2007	
#define ESCNOTSUPP     		0x2008	
#define ESCPINLOCK     		0x2009	
#define ESCPININV      		0x2010	
#define ESCPUKLOCK     		0x2011	
#define EREADPSEPIN    		0x2012	
#define ESCTINST       		0x2013	
#define ESECMESSMOD    		0x2014	 
#define ESCUNKNOWN     		0x2015	
#define EFILESIZE      		0x2016	
#define ESCNOTEMPTY    		0x2017
#define ENOSC			0x2018
#define ESCWRONGINSERT		0x2019
#define ESCTCOSNEWENTRY		0x2020
#define ESCTCOSOLDENTRY		0x2021
#define ESCTPINPADTIMER		0x2022
#define ESCWRONGEXT 		0x2030
#define ESCNOTACTIV		0x2101

#ifdef TeSECUDE				/* TeSECUDE specific error codes */
#define ESMEINIT		0x2102
#define ESME			0x2103
#define ETTP			0x2104
#define EISDN			0x2105
#endif /* TeSECUDE */ 

 /* end of SCA */ 

#define EEXTNOTFOUND		0x2201
#define ENOEXTNAME		0x2202

#define ECACOMMAND	  	0x3001
#define ECADBCERT	  	0x3011
#define ECADBUSER	  	0x3012
#define ECADBCRL	  	0x3013

#define ENODNAME	  	0x3021
#define ENODNAMEORALIAS	  	0x3022
#define EPKNOTFOUND		0x3023

#define EDIRCERTALREADYEXISTING 0x3031
#define ENORDNALIASFOUND	0x3034

#define ESUBORDINATIONRULE   	0x3041
#define EFCPATHWRONG	   	0x3042
#define ENORECIP       		0x3043
#define ENOORIGKEYINFO       	0x3045
#define ENOORIGCERT       	0x3044

#define ENOCROSSCERTS	   	0x3051

#define EALIASEXISTS	   	0x3061
#define EALIASFILTER	   	0x3062
#define ENOALIASLIST	   	0x3063
#define EALIASWRITEPROTECTION  	0x3064

#define EVERIFICATION   	0x3230
#define EVERIFICATIONTEXT   	0x3231
#define EVERIFICATIONCERT   	0x3232
#define EVERIFICATIONPATH   	0x3233
#define EVERIFICATIONALIAS   	0x3234
#define EVERIFICATIONNOKEY	0x3235
#define EVERIFICATIONCRL	0x3236
#define EVERIFICATIONNOCERT	0x3237
#define EVERIFICATIONSUBRULE	0x3238
#define EVERIFICATIONREVOKED	0x3239
#define EVERIFICATIONCRLEXP	0x323a
#define EVERIFICATIONNOCRL	0x323b
#define EVERIFICATIONCERTEXP	0x323c
#define EKEYUSAGE		0x323d

#define ECONFIRM		0x3301
#define EFILECORRUPTED		0x3302

#define EWRONGNAME		0x4001

#define EFORMATOBJID		0x4101
#define EFORMATIPADDR		0x4102

#define EPEMWRONGMICALG		0x4301
#define EPEMWRONGMICENCALG	0x4302
#define EPEMWRONGFIELD		0x4303
#define EPEMUNPREPENDEDMINUS	0x4305
#define EPEMNOBODYFILE		0x4306
#define EPEMNOSRCFILE		0x4307
#define ENOMAILHDR		0x4308

#define EDYNAMICOPEN		0x4401
#define EDYNAMICCLOSE		0x4402
#define EDYNAMICSYM         0x4403
#define EDRIVERNOTINSTALLED		0x4404
#define EDYNAMVERIFFAILED       0x4405 /* change to EDYNAMICVERIFY ??? */

#define ENOCRED			0x4501
#define ENODEFCRED		0x4502
#define EBADCREDFILE	0x4503
#define EBADCREDFILEUSER	0x4504

#define EEXTSYNTAX		0x4601
#define EEXTKEYWORD		0x4602
#define EEXTVALUE		0x4603
#define EEXTMOREBLOCKNAMES	0x4604
#define EEXTUNKNOWNBLOCKNAME	0x4605

#define ESTREAMFUNC		0x4701
#define ESTREAMDSFILE		0x4702
#define ESTREAMFILEHDL		0x4703
#define ESTREAMFILEPTR		0x4704

#define ECOMPRESSION		0x4801
#define EDECOMPRESSION		0x4802

#define EP12INTMODE		0x4901
#define EP12ENCMODE		0x4902
#define EP12ENCALG		0x4903
#define EP12BAGCONTENT		0x4904

#define EUSERBREAK		0x4A01
#define ETICKET			0x4A02
#define ENOETC			0x4A03
#define ENOPSEDIR		0x4A04
#define EINSTALLPL		0x4A05

#define EACNOMAGIC          0x4D01
#define EACNOSECDIR         0x4D02
#define EACNOWRITE          0x4D03
#define EACNOREAD           0x4D04
#define EACNOSEEK           0x4D05
#define EACBADAUTHBLOCK     0x4D06
#define EACSHORTFILE        0x4D07
#define EACINVALIDPKCS      0x4D08
#define EACDECODE           0x4D09
#define EACENCODE           0x4D0A
#define EACNOCERT           0x4D0B
#define EACVERIFICATION     0x4D0C
#define EACALREADYSIGNED    0x4D0D



/* here comes the PKCS #11 error code with an offset of 0x5000 */
#define ECKR_OK                                0x5000
#define ECKR_CANCEL                            0x5001
#define ECKR_HOST_MEMORY                       0x5002
#define ECKR_SLOT_ID_INVALID                   0x5003
#define ECKR_FLAGS_INVALID                     0x5004
#define ECKR_GENERAL_ERROR                     0x5005
#define ECKR_FUNCTION_FAILED                   0x5006
#define ECKR_ARGUMENTS_BAD                     0x5007
#define ECKR_NO_EVENT                          0x5008
#define ECKR_NEED_TO_CREATE_THREADS            0x5009
#define ECKR_CANT_LOCK                         0x500A
#define ECKR_ATTRIBUTE_READ_ONLY               0x5010
#define ECKR_ATTRIBUTE_SENSITIVE               0x5011
#define ECKR_ATTRIBUTE_TYPE_INVALID            0x5012
#define ECKR_ATTRIBUTE_VALUE_INVALID           0x5013
#define ECKR_DATA_INVALID                      0x5020
#define ECKR_DATA_LEN_RANGE                    0x5021
#define ECKR_DEVICE_ERROR                      0x5030
#define ECKR_DEVICE_MEMORY                     0x5031
#define ECKR_DEVICE_REMOVED                    0x5032
#define ECKR_ENCRYPTED_DATA_INVALID            0x5040
#define ECKR_ENCRYPTED_DATA_LEN_RANGE          0x5041
#define ECKR_FUNCTION_CANCELED                 0x5050
#define ECKR_FUNCTION_NOT_PARALLEL             0x5051
#define ECKR_FUNCTION_PARALLEL                 0x5052
#define ECKR_FUNCTION_NOT_SUPPORTED            0x5054
#define ECKR_KEY_HANDLE_INVALID                0x5060
#define ECKR_KEY_SENSITIVE                     0x5061
#define ECKR_KEY_SIZE_RANGE                    0x5062
#define ECKR_KEY_TYPE_INCONSISTENT             0x5063
#define ECKR_KEY_NOT_NEEDED                    0x5064
#define ECKR_KEY_CHANGED                       0x5065
#define ECKR_KEY_NEEDED                        0x5066
#define ECKR_KEY_INDIGESTIBLE                  0x5067
#define ECKR_KEY_FUNCTION_NOT_PERMITTED        0x5068
#define ECKR_KEY_NOT_WRAPPABLE                 0x5069
#define ECKR_KEY_UNEXTRACTABLE                 0x506A
#define ECKR_MECHANISM_INVALID                 0x5070
#define ECKR_MECHANISM_PARAM_INVALID           0x5071
#define ECKR_OBJECT_CLASS_INCONSISTENT         0x5080
#define ECKR_OBJECT_CLASS_INVALID              0x5081
#define ECKR_OBJECT_HANDLE_INVALID             0x5082
#define ECKR_OPERATION_ACTIVE                  0x5090
#define ECKR_OPERATION_NOT_INITIALIZED         0x5091
#define ECKR_PIN_INCORRECT                     0x50A0
#define ECKR_PIN_INVALID                       0x50A1
#define ECKR_PIN_LEN_RANGE                     0x50A2
#define ECKR_PIN_EXPIRED                       0x50A3
#define ECKR_PIN_LOCKED                        0x50A4
#define ECKR_SESSION_CLOSED                    0x50B0
#define ECKR_SESSION_COUNT                     0x50B1
#define ECKR_SESSION_EXCLUSIVE_EXISTS          0x50B2
#define ECKR_SESSION_HANDLE_INVALID            0x50B3
#define ECKR_SESSION_PARALLEL_NOT_SUPPORTED    0x50B4
#define ECKR_SESSION_READ_ONLY                 0x50B5
#define ECKR_SESSION_EXISTS                    0x50B6
#define ECKR_SESSION_READ_ONLY_EXISTS          0x50B7
#define ECKR_SESSION_READ_WRITE_SO_EXISTS      0x50B8
#define ECKR_SIGNATURE_INVALID                 0x50C0
#define ECKR_SIGNATURE_LEN_RANGE               0x50C1
#define ECKR_TEMPLATE_INCOMPLETE               0x50D0
#define ECKR_TEMPLATE_INCONSISTENT             0x50D1
#define ECKR_TOKEN_NOT_PRESENT                 0x50E0
#define ECKR_TOKEN_NOT_RECOGNIZED              0x50E1
#define ECKR_TOKEN_WRITE_PROTECTED             0x50E2
#define ECKR_UNWRAPPING_KEY_HANDLE_INVALID     0x50F0
#define ECKR_UNWRAPPING_KEY_SIZE_RANGE         0x50F1
#define ECKR_UNWRAPPING_KEY_TYPE_INCONSISTENT  0x50F2
#define ECKR_USER_ALREADY_LOGGED_IN            0x5100
#define ECKR_USER_NOT_LOGGED_IN                0x5101
#define ECKR_USER_PIN_NOT_INITIALIZED          0x5102
#define ECKR_USER_TYPE_INVALID                 0x5103
#define ECKR_USER_ANOTHER_ALREADY_LOGGED_IN    0x5104
#define ECKR_USER_TOO_MANY_TYPES               0x5105
#define ECKR_WRAPPED_KEY_INVALID               0x5110
#define ECKR_WRAPPED_KEY_LEN_RANGE             0x5112
#define ECKR_WRAPPING_KEY_HANDLE_INVALID       0x5113
#define ECKR_WRAPPING_KEY_SIZE_RANGE           0x5114
#define ECKR_WRAPPING_KEY_TYPE_INCONSISTENT    0x5115
#define ECKR_RANDOM_SEED_NOT_SUPPORTED         0x5120
#define ECKR_RANDOM_NO_RNG                     0x5121
#define ECKR_BUFFER_TOO_SMALL                  0x5150
#define ECKR_SAVED_STATE_INVALID               0x5160
#define ECKR_INFORMATION_SENSITIVE             0x5170
#define ECKR_STATE_UNSAVEABLE                  0x5180
#define ECKR_CRYPTOKI_NOT_INITIALIZED          0x5190
#define ECKR_CRYPTOKI_ALREADY_INITIALIZED      0x5191
#define ECKR_MUTEX_BAD                         0x51A0
#define ECKR_MUTEX_NOT_LOCKED                  0x51A1
#define ECKR_VENDOR_DEFINED                    0xD000
/* end of PKCS #11 error codes */





#define LASTERROR      th_last_error()
#define LASTTEXT       th_get_last_error_text()
#define LASTADDR       (char *)th_get_last_error_addr(), th_get_last_error_type()

#define SEC_ADD_ERROR sec_add_error(LASTERROR, LASTTEXT, LASTADDR, proc)
#define AUX_ADD_ERROR aux_add_error(LASTERROR, LASTTEXT, LASTADDR, proc)
#define AUX_ADD_WARNING aux_add_warning(LASTERROR, LASTTEXT, LASTADDR, proc)

#define VERIFICATION_ERROR ((LASTERROR & 0xFFF0) == EVERIFICATION || LASTERROR == EROOTCERT || LASTERROR == EROOTKEY)

typedef enum{
	L_DEUTSCH,
	L_ENGLISH,
	L_GET_BY_ENVIRONMENT = 0xFF
} LANGUAGES;

#define L_DEFAULT_LANGUAGE L_ENGLISH
#define L_NO_OF_LANGUAGES 2

struct TextList {
        int  id;
        char *msg[L_NO_OF_LANGUAGES];
};
typedef enum{
        char_n,
        DName_n,
        OctetString_n,
        BitString_n,                       
        Certificate_n,
        Certificates_n,
        CertificatePair_n,
        PKList_n,
        SET_OF_Certificate_n,
        SET_OF_CertificatePair_n,
        AlgId_n,
        CRLTBS_n,
        CRL_n,
        CRLEntry_n,
        CrlSet_n,
        Crl_n,
        KeyInfo_n,
        FCPath_n,
        PKRoot_n,
        IssuedCertificate_n,
        SET_OF_IssuedCertificate_n,
        SET_OF_Name_n,
        ToBeSigned_n,
        ObjId_n,
        KeyBits_n,
        PSEToc_n,
        CRLWithCertificates_n,
        SET_OF_CRLWithCertificates_n,
        int_n
} Struct_No;

struct ErrStack{
        Boolean          e_is_error;
        int              e_number;
        char            *e_text;
        char            *e_addr;
        Struct_No        e_addrtype;
        char            *e_proc;
        struct ErrStack *next;
} ;
/*-----------------------------------------------------------------------*/
/*    B i t s t r i n g   and   O c t e t s t r i n g                    */
/*-----------------------------------------------------------------------*/

struct OctetString {
        sec_uint4    noctets;
        char           *octets;
};
typedef struct  {
	sec_uint4	 noctets;
        char		*octets;
	char 		*file;
} DataStore;

#define OSTREAM_DEF_SIZE			MAX_STACK_ARRAY_LEN
#define OSTREAM_TMPFILE_DEF_SIZE	0x100000
typedef int  		( IO_Function_PTR )    	SEC_PROTOTYPE_3( void * , io_func_value, void * , buf, size_t , size );
typedef int  		( IO_Seek_PTR )    		SEC_PROTOTYPE_3( void * , io_func_value, long , offset, int , origin );

typedef struct  {
	IO_Function_PTR	*io_func;
	void			*io_func_value;
	IO_Seek_PTR		*io_seek;
	
} IO_Function;

typedef struct  {
	char	*io_file_name;
	int	 io_length;
	int	 io_offset;
	int	 io_size;
	int	 io_hdl;
	Boolean  io_unlink;
	OctetString *io_cache;
	
} IO_File;
#define IO_READ 0
#define IO_WRITE 1

typedef enum { IO_DATA_STORE, IO_FUNC, IO_OSTR, IO_FILE, IO_FILE_PTR, IO_FILE_HDL, IO_NULL } OctetStreamType;

typedef struct  {

	OctetStreamType	 type;
	
	union {
	
	    IO_Function     *io_func;
    
	    DataStore       *store;
    
	    OctetString     *ostr;
    
	    FILE            *file_ptr;
    
        
	} un; 
	
	int      file_hdl;
	int	 offset;
	
	OctetString read_cache;
	sec_uint4 size;
	Boolean seek;
	
} OctetStream;


struct BitString {
        sec_uint4    nbits;
        char           *bits;
};
struct Signature {                   /* algorithm of subject's signature */
        AlgId     *signAI;
        BitString signature;
};
struct DigestInfo { /* DigestInfo as defined in PKCS#1 and PEM and PKCS#7 */
        AlgId       *digestAI;
        OctetString digest;
};
struct EncryptedKey {
        AlgId     *encryptionAI;
        AlgId     *subjectAI;
        ENCRYPTED subjectkey;
};

/*-----------------------------------------------------------------------*/
/*    O I D ' s  and  A L G I d 's                                       */
/*-----------------------------------------------------------------------*/

/*
 *    Parameter types (parmtype member of struct AlgList, 
 *    returned by aux_ObjId2ParmType())
 */

typedef enum {
        NoParmType = -1,
        PARM_ABSENT,
        PARM_INTEGER,
        PARM_OctetString,
        PARM_KeyBits,
        PARM_NULL,
	PARM_RC2CBC,
	PARM_PKCS5,
	PARM_EC
} ParmType;


/*
 *    Algorithm types (algtype member of struct AlgList, 
 *    returned by aux_ObjId2AlgType())
 */

typedef enum { 
        NoAlgType = -1,
        SYM_ENC, 
        ASYM_ENC, 
        HASH, 
        SIG, 
        KEY_AGREEMENT,
	PBE,
/* added for PKCS#11 */
		SSL3_PMS,
		SSL3_MS,
		SSL3_KEY_MAC,
		SSL3_MAC
/* end */
} AlgType;

/*
 *    Encryption method of algorithm (algenc member of struct AlgList, 
 *    returned by aux_ObjId2AlgEnc())
 */

typedef enum { 
        NoAlgEnc = -1,
        RSA, 
        DES, 
        DES3,
        DSA,
        IDEA,
        RC2,
        RC4,
        DES3X,
		NULLENCRYPTION,
/* added for PKCS#11 */
	GENERIC,
	ELLIPTIC
/* end */
} AlgEnc;

/*
 *    Encryption mode of algorithm (algmode member of struct AlgList, 
 *    returned by aux_ObjId2AlgMode())
 */

typedef enum { 
        NoAlgMode = -1,
        ECB, 
        CBC
} AlgMode;

/*
 *    Hash method of algorithm (alghash member of struct AlgList, 
 *    returned by aux_ObjId2AlgHash())
 */

typedef enum { 
        NoAlgHash = -1,
        SQMODN, 
        MD2, 
        MD4,
        MD5,
        SHA,
	SHA1,
	RIPEMD160        
} AlgHash;

typedef enum { 
        NoAlgSpecial = -1,
        PKCS_BT_01 = 1,
        PKCS_BT_02,
        WITH_PADDING,
        WITH_PEM_PADDING,
        PKCS_BT_TD,
        WITH_B0_PADDING,
        WITH_B1_PADDING,
        TELESEC_PADDING,
        SSL_PADDING,
		ISO9796_2,
		ISO9796_2RND,
		ISO9796_2ENC
} AlgSpecial;

typedef struct ObjId ObjId;

struct ObjId {
        int             oid_nelem;
        unsigned int   *oid_elements;
};

typedef struct rc2CBC_Parm {
    int version;
    OctetString IV; /* no pointer! */
} rc2CBC_Parm;

typedef struct PBEParameter {
    OctetString salt; /* no pointer! (8 bytes) */
    int iterationCount;
} PBEParameter;

/*
 *    Algorithm parameter types
 */

#define null_parm  0

typedef struct OctetString      ideaCBC_parm_type;

typedef struct OctetString      md5WithdesCBC_parm_type;
typedef struct OctetString      md5WithdesCBC3_parm_type;

typedef unsigned int            rsa_parm_type;
/* STARCOS */
typedef unsigned int            rsa_B1_parm_type;
/* STARCOS - ENDE */
typedef unsigned int            sqmodn_parm_type;
typedef unsigned int            sqmodnWithRsa_parm_type;
typedef struct OctetString      desCBC_parm_type;
typedef struct OctetString      desCBC_pad_parm_type;
typedef struct OctetString      desCBC_no_pad_parm_type;
typedef struct OctetString      desCBC3_parm_type;
typedef struct OctetString      desEDE3CBC_parm_type;
typedef struct OctetString      desCBC3_pad_parm_type;
/* STARCOS */
typedef struct OctetString      desCBC_ISO0_parm_type;
typedef struct OctetString      desCBC_ISO1_parm_type;
typedef struct OctetString      desCBC3_ISO0_parm_type;
typedef struct OctetString      desCBC3_ISO1_parm_type;
/* STARCOS - ENDE */

typedef struct KeyBits          dhKeyAgreement_parm_type;
typedef struct KeyBits          dsa_parm_type;
typedef struct KeyBits          dsaWithSHA_parm_type;
typedef struct KeyBits          dsaWithSHA1_parm_type;
typedef struct KeyBits          id_dsa_parm_type;

typedef struct rc2CBC_Parm      rc2CBC_parm_type;

/* PKCS#5 */
typedef struct PBEParameter	pbeWithMD2AnddesCBC_parm_type;
typedef struct PBEParameter	pbeWithMD5AnddesCBC_parm_type;
/* PKCS#12 */
typedef struct PBEParameter	pbeWithSHA1And128BitRC4_parm_type;
typedef struct PBEParameter	pbeWithSHA1And40BitRC4_parm_type;
typedef struct PBEParameter	pbeWithSHA1AndDES3xCBC_parm_type;
typedef struct PBEParameter	pbeWithSHA1AndDES3CBC_parm_type;
typedef struct PBEParameter	pbeWithSHA1And128BitRC2CBC_parm_type;
typedef struct PBEParameter	pbeWithSHA1And40BitRC2CBC_parm_type;

struct AlgId {
        ObjId          * objid;
        void           * param;
};

struct AlgList {
        char           *name;
        AlgId          *algid;
        ParmType       parmtype;
        AlgType        algtype;
        AlgEnc         algenc;
        AlgHash        alghash;
        AlgSpecial     algspecial;
        AlgMode        algmode;
};


#define DES_PARM(x) ((OctetString *) (x))

#define DH_ALG_WITH_PARAM 1
#define DH_ALG_WITHOUT_PARAM 0

/*
 *  HashInput
 */

typedef BitString       SQMODN_input;

typedef union Hashinput {
        SQMODN_input sqmodn_input;
} HashInput;

struct KeyInfo {
        AlgId     *subjectAI;
        BitString subjectkey;
};

struct KeyBits {           /* internal structure of BitString subjectkey
                              in case of RSA keys and DSA keys and of the 
                              signature BitString in case of DSA signatures.
                              In case of private RSA keys, part1 and part2 
                              contain the prime numbers p and q or part1 - part5 
                              contain the CRT elements or part3 and part4 contains n and d
                              In case of public RSA keys, part1 and part2
                              contain the modulus m and the exponent e.
                              In case of private DSA keys, part1 to part4
                              contain x, p, q and g.
                              In case of public DSA keys, part1 to part4
                              contain y, p, q and g.
                              In case of a DSA signature part1 contains r
                              and part2 contains s.
                              [ The following buggy behaviour was in SECUDE versions 
                                prior to 5.2.31, 5.3.13, and 5.4.3
                                In case of a DSA signature part1 contains s
                                and part2 contains r.
                              ]
                          */
        OctetString part1;
        OctetString part2;
        OctetString part3;
        OctetString part4;
        OctetString part5;
        int choice;
};


typedef enum {
        F_NOT_EXISTING = 15,
        F_DIRECTORY, 
        F_FILE, 
        F_OTHER,
        F_ERROR
} FILE_Type;





typedef struct RSAPrivateKey 				RSAPrivateKey;
struct RSAPrivateKey {
	int 	    version;
	OctetString modulus;
	OctetString pubex;
	OctetString privex;
	OctetString prime1;
	OctetString prime2;
	OctetString exp1;
	OctetString exp2;
	OctetString coeff;
};



/*
 *	Print flags
 */ 
 
 
 /* controls aux_?print_KeyInfo() : 
                                            ALGID:   AlgId
                                            ALGINFO: Algorithm characteristics from alglist
                                            BITSTRING:    DER-Code of BitString 
                                                     subjectkey
                                            KEYBITS: Components of subjectKey 
                                                     in case of RSA, DSA, DH
                                            SK, PK:  */
#define ALGID        1
#define BITSTRING         2
#define KEYBITS      4
#define PK           8
#define SK          16
#define ALGINFO     32


/* controls aux_?print_Certificate() */
#define DER          1
#define TBS          2
#define KEYINFO      4
#define VAL          8
#define ISSUER      16
#define ALG         32
#define SIGNAT      64
#define HSH        128 
#define VER        256 
#define SUBJECT    512 
#define EXTENSIONS 1024 
#define NOASN1     2048


#ifndef NULL
#define NULL        (void *)0
#endif

#ifdef SEC_PC
#define NEWLINE "\r\n"
#else
#ifdef AS_400
#define NEWLINE "\015\n"
#else
#define NEWLINE "\n"
#endif
#endif

/* used by aux_parity_bstr() */
typedef enum { ODD_PARITY, EVEN_PARITY }  Parity;

#ifndef ASN1NEW
#define ASN1NEW(type) (type *)calloc(1, sizeof(type))
#endif

/* random values are generated for the following purposes */
typedef enum {
	RND_IV 		/* IV 			*/, 
	RND_SYM_KEY	/* symmetric key 	*/, 
	RND_ASYM_KEY 	/* asymmetric key	*/,
	RND_PIN		/* random PIN		*/,
	RND_DSA_SIG 	/* DSA signature parm	*/,
	RND_PAD 	/* random pading	*/,
	RND_DEFAULT	/* other		*/,
	RND_COMM	/* value used in communication for authentication purpose	*/,
	RND_WEAK	/* weak			*/,
	RND_STRONG	/* strong		*/,
	RND_SALT	/* salt (e.g. PKCS#5)	*/
} RND_TYPES;

/* structures return by sec_random() */
typedef enum {
	RND_STR		/* character string 		*/, 
	RND_ASCII	/* readable character string 	*/, 
	RND_OSTR	/* OctetString			*/, 
	RND_BSTR	/* BitString			*/, 
	RND_INT		/* int				*/
} RND_STRUCTS;

/* random number generator callback type */
typedef RC  	( SEC_API_CALLING_CONV Rand_CB )    	        SEC_PROTOTYPE_3( char * , buf, int , size,  RND_TYPES , type);

/* strong random number generator */
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_random_cb_strong SEC_PROTOTYPE_3(
	char	*	, buf,
	int	  	, nchars,
	RND_TYPES	, type
);
/* medium random number generator (DEFAULT) */
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_random_cb_medium SEC_PROTOTYPE_3(
	char	*	, buf,
	int	  	, nchars,
	RND_TYPES	, type
);
/* weak random number generator */
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_random_cb_weak SEC_PROTOTYPE_3(
	char	*	, buf,
	int	  	, nchars,
	RND_TYPES	, type
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV userandommaster SEC_PROTOTYPE_3(
	char	*	, buf,
	int	  	, nchars,
	RND_TYPES	, type
);
int SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX  initrandommaster SEC_PROTOTYPE_0();
int SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX  endrandommaster SEC_PROTOTYPE_0();

/* main random number function */
void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV sec_random SEC_PROTOTYPE_3(
	RND_STRUCTS	, rndstruct,
	int	  	, len,
	RND_TYPES	, type
);
/* this variable stores the address of the actual random number generator (default medium ) */
extern Rand_CB SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX random_callback;

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_random_test SEC_PROTOTYPE_5(
	char	*	, buf,
	int	  	, nchars,
	int , type,
	int , parm,
	double *, value
);
enum { RANDOM_TEST_POKER, RANDOM_TEST_MONOBIT, RANDOM_TEST_RUNS, RANDOM_TEST_LONGEST_RUN };

enum { PROCESS_X_INIT,
	PROCESS_X_DATA,
	PROCESS_X_END};

enum { 
	PROCESS_API_OTHER = 0x1,
	PROCESS_API_SECURE = 0x2,
	PROCESS_API_CRYPT = 0x4,
	PROCESS_API_AF = 0x8,
	PROCESS_API_PEM = 0x10,
	PROCESS_API_PKCS = 0x20,
	PROCESS_API_GSS = 0x40,
	PROCESS_OTHER = 0x10000,
	PROCESS_HASH = 0x20000,
	PROCESS_ENCRYPT = 0x40000,
	PROCESS_SIGN = 0x80000,
	PROCESS_DECRYPT = 0x100000,
	PROCESS_VERIFY = 0x200000,
	PROCESS_GEN_KEY = 0x400000,
	PROCESS_ENCODE = 0x800000,
	PROCESS_DECODE = 0x1000000,
	PROCESS_READ_FILE = 0x2000000,
	PROCESS_WRITE_FILE = 0x4000000
}; 
typedef struct {
	void	  *id;				/* variable to be used by application (initialized with 0) */
	sec_uint4  bytes_processed;		/* Bytes (or other things) processed at the last step */
	sec_uint4  sum_of_bytes_processed;	/* Sum of bytes processed in this context */
	sec_uint4  complete_length;		/* Complete length or -1 if the length couldn't evaluated */
	sec_uint4  action;			/* The type of operation */
	sec_uint4  state;			/* First call: PROCESS_X_INIT
						   Next calls: PROCESS_X_DATA
						   Last call : PROCESS_X_END */
} PROCESSING_STRUCT;

typedef Boolean ( SEC_API_CALLING_CONV PROCESSING_CB)	SEC_PROTOTYPE_2( PROCESSING_STRUCT * , p_process, void *, data);


void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV secude_set_processing_cb SEC_PROTOTYPE_2(
	PROCESSING_CB *	, cb,
	void *	, data
);
Boolean SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV secude_call_processing_cb SEC_PROTOTYPE_1(
	PROCESSING_STRUCT  *	, p_str
);



typedef RC ( SEC_API_CALLING_CONV PAD_Func)	SEC_PROTOTYPE_4( char *,block,	int *,used_bytes,int , length,Boolean , unpad);

RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_padding_raw SEC_PROTOTYPE_4(
	char * , block,	int * , used_bytes,	int , length,	Boolean , unpad	);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_padding_pem SEC_PROTOTYPE_4(
	char * , block,	int * , used_bytes,	int , length,	Boolean , unpad	);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_padding_std SEC_PROTOTYPE_4(
	char * , block,	int * , used_bytes,	int , length,	Boolean , unpad	);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_padding_b1 SEC_PROTOTYPE_4(
	char * , block,	int * , used_bytes,	int , length,	Boolean , unpad	);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_padding_ssl SEC_PROTOTYPE_4(
	char * , block,	int * , used_bytes,	int , length,	Boolean , unpad	);

PAD_Func SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_padding_function SEC_PROTOTYPE_1(
	AlgSpecial , pad
	);



#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */



#endif /* _SEC_GLOBAL_ */

