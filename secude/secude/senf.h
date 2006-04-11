
#ifndef SENF_H_
#define SENF_H_

#include <secude/sec_glob.h>

#ifdef SENF_INSTALLED

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef unsigned long senf_selector;

typedef unsigned long senf_type;

typedef SEC_CALLBACK(char *, senf_sprint_func) SEC_PROTOTYPE_2(char *, string, const void *, data);

typedef SEC_CALLBACK(RC, senf_free_func) SEC_PROTOTYPE_1(const void **, data);

typedef struct senf_data {
	senf_selector api;
	senf_selector selector;
	const void *value;
	senf_type type;
	senf_free_func *free; /* private */
	senf_sprint_func *sprint; /* private */
} senf_data;

typedef SEC_CALLBACK(int, senf_data_func) SEC_PROTOTYPE_2(senf_data *, data, const void *, context);

typedef struct senf_api_selector {
	senf_selector sel;
	const char *alias;
	const char *description;
	senf_data_func *get_func;
	senf_data_func *set_func;
	const void *context;
} senf_api_selector;

typedef SEC_CALLBACK(RC, senf_unregister_func) SEC_PROTOTYPE_1(void *, context);

/* senf_selector APIs */

#define SENF_API_SENF			(0x53454E46UL) /* 'SENF' */
#define SENF_API_SECUDE			(0x53454344UL) /* 'SECD' */
#define SENF_SEL_IS_API			(0x41504920UL) /* 'API ' */

/* senf_selector selectors */

#define SENF_SEL_VERSION		(0x76657273UL) /* 'vers' */
#define SENF_SEL_FEATURES		(0x66656174UL) /* 'feat' */
#define SENF_SEL_COPYRIGHT		(0x636F7079UL) /* 'copy' */
#define SENF_SEL_APILIST		(0x61706973UL) /* 'apis' */
#define SENF_SEL_LAST			(0x00000000UL) /* '\0\0\0\0' */

/* data types */

typedef enum sec_ver_stage {
	sec_ver_development,
	sec_ver_alpha,
	sec_ver_beta,
	sec_ver_release
} sec_ver_stage;

typedef struct sec_version {
	unsigned short major;
	unsigned short minor;
	unsigned short revision;
	sec_ver_stage stage;
	unsigned short buildnumber; /* patchlevel */
} sec_version;

typedef struct senf_error {
	int err;
	const char *errs;
} senf_error;

typedef const char *senf_features_description[32];

typedef struct senf_features {
	unsigned long features;
	const senf_features_description *description;
} senf_features;

/* senf_type data types */

#define	SENF_TYPE_VOID			(0x566F6964UL) /* 'Void', NULL */
#define	SENF_TYPE_FEATURES		(0x46656174UL) /* 'Feat', (const unsigned long *) */
#define	SENF_TYPE_ULONG			(0x556C6E67UL) /* 'Ulng', (const unsigned long *) */
#define	SENF_TYPE_CSTRING		(0x43737472UL) /* 'Cstr', (const char *) */
#define	SENF_TYPE_INTEGER		(0x496E7420UL) /* 'Int ', (const int *) */
#define	SENF_TYPE_VERSION		(0x56657273UL) /* 'Vers', (const sec_version *) */
#define	SENF_TYPE_SELECTORLIST	(0x53656C6CUL) /* 'Sell', (const senf_selector *) */
#define	SENF_TYPE_ALGID			(0x416C6769UL) /* 'Algi', (const AlgId *) */
#define	SENF_TYPE_OBJID			(0x4F626A69UL) /* 'Obji', (const ObjId *) */
#define	SENF_TYPE_OCTETSTRING	(0x4F637473UL) /* 'Octs', (const OctetString *) */
#define	SENF_TYPE_BITSTRING		(0x42697473UL) /* 'Bits', (const BitString *) */
#define	SENF_TYPE_ERROR			(0x4572726FUL) /* 'Erro', (const senf_error *) */
#define	SENF_TYPE_ANY			(0x2A2A2A2AUL) /* '****', accept any type */
#define	SENF_TYPE_UNKNOWN		(0x3F3F3F3FUL) /* '????', unknown type */

/* SENF_SEL_FEATURES features */

#define SENF_FEAT_IMPLEMENTED (1UL)
#define SENF_FEAT_FEATURE01 (1UL<< 1)
#define SENF_FEAT_FEATURE02 (1UL<< 2)
#define SENF_FEAT_FEATURE03 (1UL<< 3)
#define SENF_FEAT_FEATURE04 (1UL<< 4)
#define SENF_FEAT_FEATURE05 (1UL<< 5)
#define SENF_FEAT_FEATURE06 (1UL<< 6)
#define SENF_FEAT_FEATURE07 (1UL<< 7)
#define SENF_FEAT_FEATURE08 (1UL<< 8)
#define SENF_FEAT_FEATURE09 (1UL<< 9)
#define SENF_FEAT_FEATURE10 (1UL<<10)
#define SENF_FEAT_FEATURE11 (1UL<<11)
#define SENF_FEAT_FEATURE12 (1UL<<12)
#define SENF_FEAT_FEATURE13 (1UL<<13)
#define SENF_FEAT_FEATURE14 (1UL<<14)
#define SENF_FEAT_FEATURE15 (1UL<<15)
#define SENF_FEAT_FEATURE16 (1UL<<16)
#define SENF_FEAT_FEATURE17 (1UL<<17)
#define SENF_FEAT_FEATURE18 (1UL<<18)
#define SENF_FEAT_FEATURE19 (1UL<<19)
#define SENF_FEAT_FEATURE20 (1UL<<20)
#define SENF_FEAT_FEATURE21 (1UL<<21)
#define SENF_FEAT_FEATURE22 (1UL<<22)
#define SENF_FEAT_FEATURE23 (1UL<<23)
#define SENF_FEAT_FEATURE24 (1UL<<24)
#define SENF_FEAT_FEATURE25 (1UL<<25)
#define SENF_FEAT_FEATURE26 (1UL<<26)
#define SENF_FEAT_FEATURE27 (1UL<<27)
#define SENF_FEAT_FEATURE28 (1UL<<28)
#define SENF_FEAT_FEATURE29 (1UL<<29)
#define SENF_FEAT_FEATURE30 (1UL<<30)
#define SENF_FEAT_FEATURE31 (1UL<<31)

/* senf_error error numbers */

#define SENF_ERR_NOTFOUND (-1)
#define SENF_ERR_NOAPI (-2)
#define SENF_ERR_NOSEL (-3)

/* senf_list_selector flags */

#define SENF_LIST_DESCRIPTIONS (1UL)
#define SENF_LIST_HIDDEN       (1UL<< 1)
#define SENF_LIST_NOHEADERS    (1UL<<31)

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#define SECUDE_SENF_INCLUDE 1
#include <secude/senf_p.h>
#undef SECUDE_SENF_INCLUDE

#endif /* SENF_INSTALLED */
#endif /* SENF_H_ */

