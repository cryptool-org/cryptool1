/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

#include "af.h"

struct s_smime_decode_rv {
  OctetString *ostr;
  DName       *dn;
};

typedef struct s_smime_decode_rv smime_decode_rv;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV smime_encode SEC_PROTOTYPE_5(  
                    PSE, pse,
                    OctetString*, octet_in, 
                    char*, alias,
                    DName*, dn,
                    int, mode);
                    
smime_decode_rv SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV smime_decode SEC_PROTOTYPE_2(  
                  PSE, pse, 
                  OctetString*, octet_in);

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#define DATA_TYPE 1
#define SIGNED_DATA_TYPE 2
#define ENVELOPED_DATA_TYPE 3
#define SIGNED_ENVELOPED_DATA_TYPE 4
                  




