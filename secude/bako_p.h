/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/


/*-----------------------------------------------------------------------*/
/* INCLUDE FILE  bako_p.h                                                */
/* Prototypes for SECUDE BAKO API                                        */
/*-----------------------------------------------------------------------*/


#ifdef BAKO_INSTALLED


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */




/*      ------------------------------------------------------------------------     */
/*                                                                                   */
/*       © GMD & SECUDE 1997 by Stephan André (mailto:andre@secude.com)              */
/*                                                                                   */
/*      ------------------------------------------------------------------------     */
/*                                                                                   */
/*      BAKO - Basic Cooperation Protocol                                            */
/*             BAKO API implementation of BAKO Specification V1.0                    */
/*                                                                                   */
/*      ------------------------------------------------------------------------     */
/*                                                                                   */
/*      Windows Dialogs by Jochen Dückminor (mailto:dueckminor@darmstadt.gmd.de)     */
/*                                                                                   */
/*      ------------------------------------------------------------------------     */
  

/*
 *      src/bako.c
 */



/*-------------------
 * bako_open_client() - open a new BAKO context on client-side
 *-------------------*/
BAKO SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_open_client SEC_PROTOTYPE_1(
	
	BakoResult **   , bakoresult			/* OUT  status of initialisation                */
);

/*-------------------
 * bako_open_server() - open a new BAKO context on server-side
 *-------------------*/
BAKO SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_open_server SEC_PROTOTYPE_2(
	
	char *		, psefile,			/* IN   server PSE file name (optional)  	*/
	BakoResult **   , bakoresult			/* OUT  resulting bakograms, status, ...        */
);

/*-------------
 * bako_close() - close BAKO session and free memory allocated for a previously returned BAKO structure
 *-------------*/
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_close SEC_PROTOTYPE_1(
	
	BAKO *          , bakogram                      /* IN   BAKO context to be closed		*/
);

/*------------------
 * bako_client_hello() - generate client HELLO with session PSE
 *------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_client_hello SEC_PROTOTYPE_2(
	
	BAKO            , bako,				/* IN   BAKO session context			*/
	BakoResult **   , result			/* OUT  resulting bakograms, status, ...	*/
);

/*------------------
 * bako_server_hello() - generate server HELLO with server PSE
 *------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_server_hello SEC_PROTOTYPE_2(
	
	BAKO            , bako,				/* IN   BAKO session context			*/
	BakoResult **   , result			/* OUT  resulting bakograms, status, ...	*/
);

/*------------------
 * bako_registration() - generate user registration for session and transaction PSE as sequence: CRtransaction(cr_body) + CRsession(cr_body)
 *------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_registration SEC_PROTOTYPE_3(
	
	BAKO            , bako,				/* IN   BAKO session context			*/
	BakoRcpts *	, recipients,			/* IN	list of recipient names			*/
	BakoResult **   , result			/* OUT  resulting bakograms, status, ...	*/
);

/*------------------
 * bako_cert_request() - generate Certification Request for session and transaction PSE as sequence: CRtransaction(cr_body) + CRsession(cr_body)
 *------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_cert_request SEC_PROTOTYPE_3(
	
	BAKO            , bako,				/* IN   BAKO session context			*/
	BakoRcpts *	, recipients,			/* IN	list of recipient names			*/
	BakoResult **   , result			/* OUT  resulting bakograms, status, ...	*/
);

/*------------------
 * bako_revocation_request() - generate nested Revocation Request for session and transaction PSE: RRsession(RRtransaction(rr_body))
 *------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_revocation_request SEC_PROTOTYPE_3(
	
	BAKO            , bako,				/* IN   BAKO session context			*/
	BakoRcpts *	, recipients,			/* IN	list of recipient names			*/
	BakoResult **   , result			/* OUT  resulting bakograms, status, ...	*/
);

/*------------------
 * bako_update_pse() - Updating of open session/transaction PSE if Certification Reply or Public Key List is given
 *------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_update_pse SEC_PROTOTYPE_3(
	
	BAKO            , bakoContext,                  /* IN   BAKO session context                    */
	Bakogram    *   , bakogram,			/* IN   signed bakogram to-be-scanned           */
	BakoResult **   , bakoresult                    /* OUT  resulting bakograms, status, ...        */
);

/*------------------
 * bako_validate() - Scan, parse, and validate given set of Bakograms
 *------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_validate SEC_PROTOTYPE_3(
	
	BAKO            , bako,				/* IN   BAKO session context                    */
	Bakogram *      , bakogram,			/* IN   bakogram to-be-scanned                  */
	BakoResult **   , bakoresult			/* OUT  resulting bakograms, status, ...        */
);

/*------------------
 * bako_sign() - sign given bakogram, with open client session PSE or open server PSE
 *------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_sign SEC_PROTOTYPE_4(
	
	BAKO            , bako,				/* IN   BAKO session context                    */
	Bakogram *      , bakogram,			/* IN   bakogram to-be-signed                   */
	OctetString *   , data,                 /* IN   application data to be appended         */
	BakoResult **   , result			/* OUT  resulting bakograms, status, ...        */
);

/*------------------
 * bako_explicit_sign() - sign given bakogram, open and close transaction PSE for that purpose
 *------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_explicit_sign SEC_PROTOTYPE_4(
	
	BAKO            , bako,				/* IN   BAKO session context			*/
	Bakogram *      , bakogram,			/* IN   bakogram to-be-signed			*/
	OctetString *   , data,                 /* IN   application data to be appended         */
	BakoResult **   , bakoresult			/* OUT  resulting bakograms, status, ...	*/
);

/*------------------
 * bako_display_order() - display given bakogram without any security enhancements
 *------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_display_order SEC_PROTOTYPE_3(
	
	BAKO            , bako,				/* IN   BAKO session context			*/
	Bakogram *      , bakogram,			/* IN   bakogram to-be-signed			*/
	BakoResult **   , bakoresult			/* OUT  resulting bakograms, status, ...	*/
);

/*------------------
 * bako_encrypt_order() - sign and encrypt given bakogram using open session PSE
 *------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_encrypt_order SEC_PROTOTYPE_4(
	
	BAKO            , bako,				/* IN   BAKO session context			*/
	Bakogram *      , bakogram,			/* IN   bakogram to-be-signed			*/
	BakoRcpts *	, recipients,			/* IN	list of recipient names			*/
	BakoResult **   , bakoresult			/* OUT  resulting bakograms, status, ...	*/
);

/*------------------
 * bako_encrypt_response() - sign and encrypt given bakogram using open server PSE
 *------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_encrypt_response SEC_PROTOTYPE_3(
	
	BAKO            , bako,				/* IN   BAKO session context			*/
	Bakogram *      , bakogram,			/* IN   bakogram to-be-encrypted		*/
	BakoResult **   , result			/* OUT  resulting bakograms, status, ...	*/
);

/*-----------------------
 * bako_Bakogram2ClientDB() - append given bakogram with time stamp and comment to client data base 
 *-----------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_Bakogram2ClientDB SEC_PROTOTYPE_5(
	
	BAKO		, bako,					/* IN   result to-be-printed			*/
	Bakogram *	, bakogram,				/* IN   bakogram				*/
	char *		, clientDB,				/* IN   file name of client data base		*/
	char *		, comment,				/* IN   application's comment on bakogram	*/
	Boolean 	, autoconvert				/* IN   autoconvert ENCRYPTED to MIC if TRUE	*/
);

/*-----------------------
 * bako_print_BakoResult() - print BakoResult structure to stderr
 *-----------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_print_BakoResult SEC_PROTOTYPE_2(
	
	BakoResult *	, result,				/* IN   result to-be-printed		*/
	Boolean 	, verbose				/* IN   verbose TRUE/FALSE		*/
);

/*-----------------------
 * bako_fprint_BakoResult() - print BakoResult structure to file
 *-----------------------*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_fprint_BakoResult SEC_PROTOTYPE_3(
	
	FILE		* , ff,					/* IN   file to print to		*/
	BakoResult	* , result,				/* IN   result to-be-printed		*/
	Boolean 	  , verbose				/* IN   verbose TRUE/FALSE		*/
);

/*-----------------------
 * bako_sprint_BakoResult() - print BakoResult structure to string
 *-----------------------*/
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV bako_sprint_BakoResult SEC_PROTOTYPE_3(
	
	char *		, string,			/* IN   pointer to string			*/
	BakoResult *	, result,			/* IN   result to-be-printed			*/
	Boolean 	, verbose			/* IN   verbose TRUE/FALSE			*/
);

/*-------------------
 * bako_new_Bakogram() - get a new Bakogram structure
 *-------------------*/
Bakogram SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV bako_new_Bakogram SEC_PROTOTYPE_2(
	char *		, message_octets,		/* IN   initial string for message component	*/
	unsigned int	, message_noctets		/* IN   initial string length			*/
);

/*---------------------
 * bako_Result2Bakogram() - get a new Bakogram structure, initialise from first result level
 *---------------------*/
Bakogram SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV bako_Result2Bakogram SEC_PROTOTYPE_1(
	BakoResult *	, result			/* IN    result for initial message component	*/
);

/*---------------------
 * bako_new_BakoResult() - get a new BakoResult structure
 *---------------------*/
BakoResult SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV bako_new_BakoResult SEC_PROTOTYPE_0(
	
);

/*---------------------
 * bako_free_Bakogram() - free memory allocated for a previously returned Bakogram structure
 *---------------------*/
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_free_Bakogram SEC_PROTOTYPE_1(
	
	Bakogram **     , bakogram                      /* IN   bakogram to-be-freed                    */
);

/*-----------------------
 * bako_free_BakoResult() - free memory allocated for a previously returned BakoResult structure
 *-----------------------*/
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_free_BakoResult SEC_PROTOTYPE_1(
	
	BakoResult **   , result                        /* IN   result to-be-freed                      */
);

/*---------------------
 * bako_free_BakoRecipients() - free memory allocated for a previously returned bakorecipients structure
 *---------------------*/
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV bako_free_BakoRecipients SEC_PROTOTYPE_1(
	
	BakoRcpts **     , recipients			/* IN   recipients to-be-freed			*/
);

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */



#endif /* BAKO_INSTALLED */

