/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/
 
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef X500

#ifdef __STDC__
/***************************************************************
 *
 * Headers from file af/af_dir.c
 *
 ***************************************************************/
       Certificate * quipuCert2secudeCert(struct certificate * quipu_cert);
       struct certificate * secudeCert2quipuCert(Certificate * secude_cert);
       struct certificate_list * secudeCPair2quipuCPair(CertificatePair * secude_cpair);

#else

/***************************************************************
 *
 * Headers from file af/af_dir.c
 *
 ***************************************************************/
       Certificate * quipuCert2secudeCert();
       struct certificate * secudeCert2quipuCert();
       struct certificate_list * secudeCPair2quipuCPair();

#endif

#endif

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

 

