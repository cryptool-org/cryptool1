/* @(#) $Id$ SAP*/
/**********************************************************************/
/**********************************************************************/
/*                                                                    */
/*  (C) Copyright SAP AG, Walldorf  1996 - 1999                       */
/*                                                                    */
/*                                                                    */
/*  ssfxxapi.h     C API for SSF (Secude Store & Forward)             */
/*  ==========                                                        */
/*                                                                    */
/* This header file contains all declarations for the SSF API,        */
/* (Macros, constants and types can be found in ssfxxall.h	      */
/*                                                                    */
/* The SSF ("Secure Store & Forward") API provides services to        */
/* protect SAP R/3 data and documents while such data is being stored */
/* on insecure media or is in transit over insecure communication     */
/* channels.                                                          */
/*                                                                    */
/* SSF provides data integrity, authentication and non-repudiation    */
/* services using digital signatures, as well as confidentiality      */
/* through the use of digital envelopes and encryption. Through the   */
/* SSF API security toolkits from external vendors are integrated     */
/* with SAP R/3.                                                      */
/*                                                                    */
/*                                                                    */
/* The following functions are provided in the "all-in-one buffer-    */
/* based processing (abp)" mode (in Version 1.1x):                    */
/*                                                                    */
/*    SsfVersion         return version info of SSF library           */
/*    SsfSign            create digital signature(s) for data         */
/*    SsfVerify          verify digital signatures for data           */
/*    SsfEnvelope        encrypt data for recipient(s)                */
/*    SsfDevelope        decrypt data for recipient                   */
/*    SsfEncode          encode data                                  */
/*    SsfDecode          decode data                                  */
/*    SsfAddSign         add a digital signature                      */
/*    SsfDigest          compute a hash value                         */
/*    SsfDELSsfOctetstring free returned memory from the other Ssf-fnc*/
/*                                                                    */
/*                                                                    */
/*  Auxiliary functions:                                              */
/*                                                                    */
/*  This header file contains the function declarations for the       */
/*  auxiliary functions of the SSF ("Secure Store & Forward") API.    */
/*  The auxiliary functions can be used by applications using the     */
/*  SSF API to work with the SSF list structures which have to be     */
/*  supplied as input parameters or which are returned as output      */
/*  parameters. In particular, the auxiliary functions deal with      */
/*  security information lists for signers and recipients. The        */
/*  following auxiliary functions are provided:                       */
/*                                                                    */
/*    SsfNEWSigRcpSsfInfo     create new signer/recipient info        */
/*    SsfINSSigRcpSsfInfo     insert signer/recipient info into list  */
/*    SsfDELSigRcpSsfInfo     delete signer/recipient info            */
/*    SsfDELSigRcpSsfInfoList delete signer/recipient info list       */
/*                                                                    */
/*                                                                    */
/* Documentation:                                                     */
/*   - "Secure Store & Forward (SSF) - Spezifikation"                 */
/*                                                                    */
/*                                                                    */
/*  Author:    Michael Friedrich                                      */
/*  Reviewer:                                                         */
/*  Version:   1.50                                                   */
/*                                                                    */
/*  Description:                                                      */
/*    This file is to be included in all "C" source files that        */
/*    implement the SSF API.					      */
/*    Sources that want to use SSF please include ssfxxall.h          */
/*                                                                    */
/*  Prerequisites:                                                    */
/*    - standard conformance: platform-independent "C" code           */
/*    - others:                                                       */
/*                                                                    */
/*  Modified:                                                         */
/*                                                                    */
/*  Remarks:                                                          */
/*                                                                    */
/*   -   no UNICODE support - part of libssf.dll with fixed interface */
/*       the chars used here are either raw data or simply used as    */
/*       'identifier'.						      */
/*                                                                    */
/**********************************************************************/

#ifndef SSFXXAPI_H
#define SSFXXAPI_H  1

#include <secude/ssfxxall.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************/
/*                                                                    */
/*  Export interface                                                  */
/*    - Function list                                                 */
/*                                                                    */
/**********************************************************************/

#ifndef APIENTRY
#  if defined(_WINDOWS)
#    define APIENTRY        __far __export __pascal
#  elif defined(_WIN32)
#    define APIENTRY        __stdcall
#  else
#    define APIENTRY
#  endif
#endif



/*--------------------------------------------------------*/
/* SsfVersion                                             */
/*                                                        */
/* Returns version information of the SSF library:        */
/*     - version number of the SSF library                */
/*     - product name of underlying security toolkit      */
/*     - version number of underlying security toolkit    */
/*     - any additional information                       */
/*                                                        */
/* The information is concatenated into the output string */
/* using ';' as delimiter.                                */
/*                                                        */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* ostrOutputData        version information              */
/* ostrOutputDataL       length of above                  */
/*                                                        */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_API_OK            operation successful             */
/* SSF_API_NOSECTK       security toolkit not found       */
/* SSF_API_NOMEMORY      no more memory for output data   */
/*                                                        */
/*--------------------------------------------------------*/
#define ARG2_SSFVERSION   SsfOctetstring *, SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFVERSION)(ARG2_SSFVERSION);
SAPRETURN APIENTRY SsfVersion (ARG2_SSFVERSION);

SAPRETURN APIENTRY SsfVersion (	
	SsfOctetstring		* outputData,
	SsfOctetlen		* outputDataL );


/*--------------------------------------------------------*/
/* SsfQueryProperties                                     */
/*                                                        */
/* Returns properties of the SSF library:                 */
/*     - PROPERTIES	(Arg: ignored)                    */
/*     - FORMATS	(Arg: ignored)                    */
/*     - HASHALGS       (Arg optional: Format)            */
/*     - ENCRALGS       (Arg optional: Format)            */
/*                                                        */
/* The information is returned in ostrOutputData,         */
/* multple entries are separated by ';'.                  */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* strProperty           property                         */
/* strPropertyL          length of strProperty            */
/*                                                        */
/* strArgument           (optional) Argument              */
/* strArgumentL          length of strArgument            */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* ostrOutputData        version information              */
/* ostrOutputDataL       length of above                  */
/*                                                        */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_API_OK            operation successful             */
/* SSF_API_NODATA        couldn't handle this property    */
/* SSF_API_NOMEMORY      no more memory for output data   */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG6_SSFQUERYPROPERTIES  const SsfCharstring, SsfCharlen,	\
				 const SsfCharstring, SsfCharlen,	\
				 SsfOctetstring *, SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFQUERYPROPERTIES)(ARG6_SSFQUERYPROPERTIES);
SAPRETURN APIENTRY SsfQueryProperties (ARG6_SSFQUERYPROPERTIES);

SAPRETURN APIENTRY SsfQueryProperties (	
	const SsfCharstring	  strProperty,
	      SsfCharlen	  strPropertyL,
	const SsfCharstring	  strArgument,
	      SsfCharlen	  strArgumentL,
	      SsfOctetstring	* outputData,
	      SsfOctetlen	* outputDataL );


/*--------------------------------------------------------*/
/* SsfEncode                                              */
/*                                                        */
/* Encodes the given data according to the specified      */
/* format.                                                */
/*                                                        */
/* Supported formats:                                     */
/*                                                        */
/* PKCS7                 Data (output format)             */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* strFormat             target format                    */
/* strFormatL            length of strFormat              */
/* ostrInputData         input data to be encoded         */
/* ostrInputDataL        length of ostrInputData          */
/*                                                        */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* ostrEncodedData       encoded data (output data)       */
/* ostrEncodedDataL      length of output data            */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_API_OK                  success for each signer    */
/* SSF_API_NOSECTK             security toolkit not found */
/* SSF_API_INVALID_FORMAT      unknown wrapper format     */
/* SSF_API_NODATA              input data has length zero */
/* SSF_API_NOMEMORY            no main memory output data */
/* SSF_API_ENCODE_FAILED        ASN.1 encoding failed     */
/* SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG6_SSFENCODE  const SsfCharstring,  SsfCharlen,	\
		 	const SsfOctetstring, SsfOctetlen,	\
			SsfOctetstring *,     SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFENCODE)(ARG6_SSFENCODE);
SAPRETURN APIENTRY SsfEncode (ARG6_SSFENCODE);

SAPRETURN APIENTRY SsfEncode ( 
	const SsfCharstring	  strFormat,
	      SsfCharlen	  strFormatL,
	const SsfOctetstring	  ostrInputData,
	      SsfOctetlen	  ostrInputDataL,
	      SsfOctetstring	* ostrEncodedData,
	      SsfOctetlen	* ostrEncodedDataL );


/*--------------------------------------------------------*/
/* SsfDecode                                              */
/*                                                        */
/* Decodes the given data according to the specified      */
/* format.                                                */
/*                                                        */
/* Supported formats:                                     */
/*                                                        */
/* PKCS7                 Data (input format)              */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* strFormat             target format                    */
/* strFormatL            length of strFormat              */
/* ostrEncodedData       input data to be decoded         */
/* ostrEncodedDataL      length of ostrEncodedData        */
/*                                                        */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* ostrOutputData        decoded data (output data)       */
/* ostrOutputDataL       length of output data            */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_API_OK                  success for each signer    */
/* SSF_API_NOSECTK             security toolkit not found */
/* SSF_API_INVALID_FORMAT      unknown wrapper format     */
/* SSF_API_NODATA              input data has length zero */
/* SSF_API_NOMEMORY            no main memory output data */
/* SSF_API_DECODE_FAILED       ASN.1 decoding failed      */
/* SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG6_SSFDECODE  const SsfCharstring,  SsfCharlen,	\
			const SsfOctetstring, SsfOctetlen,	\
			SsfOctetstring *,     SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFDECODE)(ARG6_SSFDECODE);
SAPRETURN APIENTRY SsfDecode (ARG6_SSFDECODE);

SAPRETURN APIENTRY SsfDecode ( 
	const SsfCharstring	  strFormat,
	      SsfCharlen	  strFormatL,
	const SsfOctetstring	  ostrEncodedData,
	      SsfOctetlen	  ostrEncodedDataL,
	      SsfOctetstring	* ostrOutputData,
	      SsfOctetlen	* ostrOutputDataL );


/*--------------------------------------------------------*/
/* SsfSign                                                */
/*                                                        */
/* Produces digital signatures for the given input data   */
/* and the given signers and returns the signed data in   */
/* the desired format.                                    */
/*                                                        */
/* Supported formats:                                     */
/*                                                        */
/* PKCS7                 SignedData (output format)       */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* strFormat             target format                    */
/* strFormatL            length of strFormat              */
/* strHashalg            hash algorithm                   */
/* strHashalgL           length of strHashalg             */
/* bIncCerts             include certificates or not      */
/* bDetached             include data or not              */
/* ostrInputData         input data to be signed          */
/* ostrInputDataL        length of ostrInputData          */
/*                                                        */
/* INPUT/OUTPUT                                           */
/*                                                        */
/* signerList            list of signers, their security  */
/*                       information and SSF result after */
/*                       function return                  */
/*                                                        */
/* SSF_API_SIGNER_OK          operation successful        */
/* SSF_API_INVALID_NAMESPACE  unknown namespace id        */
/* SSF_API_UNKNOWN_SIGNER     unknown signer              */
/* SSF_API_UNKNOWN_PROFILE    security profile not found  */
/* SSF_API_INVALID_PROFILE    security profile not usable */
/* SSF_API_INVALID_PASSWORD   invalid password for signer */
/* SSF_API_NOCERTIFICATE      certificate not found       */
/* SSF_API_SIGNER_NOT_OK      signature not ok for signer */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* ostrSignedData        signed data (output data)        */
/* ostrSignedDataL       length of output data            */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_API_OK                  success for each signer    */
/* SSF_API_NOSECTK             security toolkit not found */
/* SSF_API_INVALID_FORMAT      unknown wrapper format     */
/* SSF_API_NODATA              input data has length zero */
/* SSF_API_NOMEMORY            no main memory output data */
/* SSF_API_SIGNER_ERRORS       there are signer errors    */
/* SSF_API_INVALID_MDALG       unknown hash algorithm     */
/* SSF_API_ENCODE_FAILED        ASN.1 encoding failed     */
/* SSF_API_DECODE_FAILED        ASN.1 decoding failed     */
/* SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG11_SSFSIGN  const SsfCharstring, SsfCharlen,		\
		       const SsfCharstring, SsfCharlen,		\
		       SAP_BOOL, SAP_BOOL, 			\
		       const SsfOctetstring, SsfOctetlen,	\
		       SigRcpSsfInformationList, SsfOctetstring *, \
		       SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFSIGN)(ARG11_SSFSIGN);
SAPRETURN APIENTRY SsfSign (ARG11_SSFSIGN);

SAPRETURN APIENTRY SsfSign (
	const SsfCharstring		  strFormat,
	      SsfCharlen		  strFormatL,
	const SsfCharstring		  strHashalg,
	      SsfCharlen		  strHashalgL,
	      SAP_BOOL			  bIncCerts,
	      SAP_BOOL			  bDetached,
	const SsfOctetstring		  ostrInputData,
	      SsfOctetlen		  ostrInputDataL,
	      SigRcpSsfInformationList    signerList,      
	      SsfOctetstring		* ostrSignedData,
	      SsfOctetlen		* ostrSignedDataL );


/*--------------------------------------------------------*/
/* SsfVerify                                              */
/*                                                        */
/* Checks digital signatures under the given input data   */
/* in the specified format and returns a list with the    */
/* verification results for each signer.                  */
/*                                                        */
/* Supported formats:                                     */
/*                                                        */
/* PKCS7                 SignedData (input format)        */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* strFormat             source format                    */
/* strFormatL            length of strFormat              */
/* bUseCerts             use included certificates or not */
/* ostrSignedData        signed data (input data)         */
/* ostrSignedDataL       length of ostrSignedData         */
/* ostrInputData         data to compare with             */
/* ostrInputDataL        length of data to compare with   */
/* strPab                name of Private Address Book     */
/*                       (if any, string can be empty)    */
/* strPabL               length of strPab                 */
/* strPabPassword        password to open PAB             */
/*                       (if any, string can be empty)    */
/* strPabPasswordL       length of strPabPassword         */
/*                                                        */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* signerResultList      list of result of the operation  */
/*                       for each signer:                 */
/*                                                        */
/* SSF_API_SIGNER_OK          operation successful        */
/* SSF_API_INVALID_NAMESPACE  unknown namespace id        */
/* SSF_API_UNKNOWN_SIGNER     unknown signer              */
/* SSF_API_UNKNOWN_PROFILE    security profile not found  */
/* SSF_API_INVALID_PROFILE    security profile not usable */
/* SSF_API_INVALID_PASSWORD   invalid password for signer */
/* SSF_API_NOCERTIFICATE      certificate not found       */
/* SSF_API_SIGNER_NOT_OK      signature invalid           */
/*                                                        */
/* ostrOutputData        decoded data that was signed     */
/* ostrOutputDataL       length of ostrOutputData         */
/*                                                        */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_API_OK                   success for each signer   */
/* SSF_API_NOSECTK              security toolkit not found*/
/* SSF_API_INVALID_FORMAT       unknown wrapper format    */
/* SSF_API_NODATA               input data has length zero*/
/* SSF_API_NOMEMORY             no main memory output data*/
/* SSF_API_SIGNER_ERRORS        there are signer errors   */
/* SSF_API_NORESULTLISTMEMORY   no main memory result list*/
/* SSF_API_UNKNOWN_PAB          Priv.Addr.Book not found  */
/* SSF_API_INVALID_PAB_PASSWORD invalid PAB password      */
/* SSF_API_ENCODE_FAILED        ASN.1 encoding failed     */
/* SSF_API_DECODE_FAILED        ASN.1 decoding failed     */
/* SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG14_SSFVERIFY  const SsfCharstring,  SsfCharlen, SAP_BOOL,	\
			 const SsfOctetstring, SsfOctetlen,		\
			 const SsfOctetstring, SsfOctetlen,		\
			 const SsfCharstring,  SsfCharlen,		\
			 const SsfCharstring,  SsfCharlen,		\
			 SigRcpSsfInformationList *,			\
			 SsfOctetstring *,     SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFVERIFY)(ARG14_SSFVERIFY);
SAPRETURN APIENTRY SsfVerify (ARG14_SSFVERIFY);

SAPRETURN APIENTRY SsfVerify (	
	const SsfCharstring		  strFormat,
	      SsfCharlen		  strFormatL,
	      SAP_BOOL			  bUseCerts,
	const SsfOctetstring		  ostrSignedData,
	      SsfOctetlen		  ostrSignedDataL,
	const SsfOctetstring		  ostrInputData,
	      SsfOctetlen		  ostrInputDataL,
	const SsfCharstring		  strPab,          
	      SsfCharlen		  strPabL,          
	const SsfCharstring		  strPabPassword,      
	      SsfCharlen		  strPabPasswordL,
	      SigRcpSsfInformationList  * signerResultList,
	      SsfOctetstring		* ostrOutputData,
	      SsfOctetlen		* ostrOutputDataL );


/*--------------------------------------------------------*/
/* SsfEnvelope                                            */
/*                                                        */
/* Produces a digital envelope for the given input data   */
/* and the given list of recipients and returns the       */
/* enveloped data in the desired format. A list with the  */
/* operation results for each recipient is returned as    */
/* as well.                                               */
/*                                                        */
/* Supported formats:                                     */
/*                                                        */
/* PKCS7                 EnvelopedData (output format)    */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* strFormat             target format                    */
/* strFormatL            length of strFormat              */
/* strSymEncr            symmetric encryption method      */
/* strSymEncrL           length of strSymEncr             */
/* ostrInputData         input data to be enveloped       */
/* ostrInputDataL        length of ostrInputData          */
/* strPab                name of Private Address Book     */
/*                       (if any, string can be empty)    */
/* strPabL               length of strPab                 */
/* strPabPassword        password to open PAB             */
/*                       (if any, string can be empty)    */
/* strPabPasswordL       length of strPabPassword         */
/*                                                        */
/*                                                        */
/* INPUT/OUTPUT                                           */
/*                                                        */
/* recipientList         list of recipients, their        */
/*                       security information and the     */
/*                       SSF function result after return */
/*                                                        */
/* SSF_API_RECIPIENT_OK       operation successful        */
/* SSF_API_INVALID_NAMESPACE  unknown namespace id        */
/* SSF_API_UNKNOWN_RECIPIENT  unknown recipient           */
/* SSF_API_UNKNOWN_PROFILE    security profile not found  */
/* SSF_API_INVALID_PROFILE    security profile not usable */
/* SSF_API_NOCERTIFICATE      certificate not found       */
/* SSF_API_RECIPIENT_NOT_OK   operation not successful    */
/*                                                        */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* ostrEnvelopedData     enveloped data (output data)     */
/* ostrEnvelopedDataL    length of output data            */
/*                                                        */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_API_OK                   success for each recipient*/
/* SSF_API_NOSECTK              security toolkit not found*/
/* SSF_API_INVALID_FORMAT       unknown wrapper format    */
/* SSF_API_NODATA               input data has length zero*/
/* SSF_API_NOMEMORY             no main memory output data*/
/* SSF_API_UNKNOWN_PAB          Priv.Addr.Book not found  */
/* SSF_API_INVALID_PAB_PASSWORD invalid PAB password      */
/* SSF_API_RECIPIENT_ERRORS     there are recipient errors*/
/* SSF_API_INVALID_MDALG        unknown encryption alg.   */
/* SSF_API_ENCODE_FAILED        ASN.1 encoding failed     */
/* SSF_API_DECODE_FAILED        ASN.1 decoding failed     */
/* SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG13_SSFENVELOPE  const SsfCharstring,  SsfCharlen,	\
			   const SsfCharstring,  SsfCharlen,	\
			   const SsfOctetstring, SsfOctetlen,	\
			   const SsfCharstring,  SsfCharlen,	\
			   const SsfCharstring,  SsfCharlen,	\
			   SigRcpSsfInformationList,		\
			   SsfOctetstring *, SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFENVELOPE)(ARG13_SSFENVELOPE);
SAPRETURN APIENTRY SsfEnvelope (ARG13_SSFENVELOPE);

SAPRETURN APIENTRY SsfEnvelope (	
	const SsfCharstring		  strFormat,
	      SsfCharlen		  strFormatL,
	const SsfCharstring		  strSymEncr,
	      SsfCharlen		  strSymEncrL,
	const SsfOctetstring		  ostrInputData,
	      SsfOctetlen		  ostrInputDataL,
	const SsfCharstring		  strPab,          
	      SsfCharlen		  strPabL,          
	const SsfCharstring		  strPabPassword,      
	      SsfCharlen		  strPabPasswordL,
	      SigRcpSsfInformationList    recipientList,      
	      SsfOctetstring		* ostrEnvelopedData,
	      SsfOctetlen		* ostrEnvelopedDataL );


/*--------------------------------------------------------*/
/* SsfDevelope                                            */
/*                                                        */
/* Removes the digital envelope from the given input data */
/* for the given recipient and returns the decrypted      */
/* output data. The operation results for the given       */
/* recipient are returned as well.                        */
/*                                                        */
/* Supported formats:                                     */
/*                                                        */
/* PKCS7                 EnvelopedData (input format)     */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* strFormat             source format                    */
/* strFormatL            length of strFormat              */
/* ostrEnvelopedData     input data to be developed       */
/* ostrEnvelopedDataL    length of ostrEnvelopedData      */
/*                                                        */
/*                                                        */
/* INPUT/OUTPUT                                           */
/*                                                        */
/* ptrRecipient          recipient, his/her security      */
/*                       information and the SSF operation*/
/*                       result after function return     */
/*                                                        */
/* SSF_API_RECIPIENT_OK       operation successful        */
/* SSF_API_INVALID_NAMESPACE  unknown namespace id        */
/* SSF_API_UNKNOWN_RECIPIENT  unknown recipient           */
/* SSF_API_UNKNOWN_PROFILE    security profile not found  */
/* SSF_API_INVALID_PROFILE    security profile not usabl  */
/* SSF_API_NOCERTIFICATE      certificate not found       */
/* SSF_API_RECIPIENT_NOT_OK   operation not successful    */
/*                                                        */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* ostrOutputData        developed data (output data)     */
/* ostrOutputDataL       length of output data            */
/*                                                        */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_API_OK                   success for recipient     */
/* SSF_API_NOSECTK              security toolkit not found*/
/* SSF_API_INVALID_FORMAT       unknown wrapper format    */
/* SSF_API_NODATA               input data has length zero*/
/* SSF_API_NOMEMORY             no main memory output data*/
/* SSF_API_RECIPIENT_ERRORS     there are recipient errors*/
/* SSF_API_ENCODE_FAILED        ASN.1 encoding failed     */
/* SSF_API_DECODE_FAILED        ASN.1 decoding failed     */
/* SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG7_SSFDEVELOPE  const SsfCharstring, SsfCharlen,	\
			  const SsfOctetstring, SsfOctetlen,	\
			  PtrSigRcpSsfInformation, 		\
			  SsfOctetstring *, SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFDEVELOPE)(ARG7_SSFDEVELOPE);
SAPRETURN APIENTRY SsfDevelope (ARG7_SSFDEVELOPE);

SAPRETURN APIENTRY SsfDevelope(
	const SsfCharstring		  strFormat,
	      SsfCharlen		  strFormatL,
	const SsfOctetstring		  ostrEnvelopedData,
	      SsfOctetlen		  ostrEnvelopedDataL,
	      PtrSigRcpSsfInformation	  ptrRecipient,      
	      SsfOctetstring		* ostrOutputData,              
	      SsfOctetlen		* ostrOutputDataL );


/*--------------------------------------------------------*/
/* SsfAddSign                                             */
/*                                                        */
/* Adds another signer to already signed data.            */
/*                                                        */
/* Supported formats:                                     */
/*                                                        */
/* PKCS7                 SignedData (in/output format)    */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* strFormat             target format                    */
/* strFormatL            length of strFormat              */
/* strHashalg            hash algorithm                   */
/* strHashalgL           length of strHashalg             */
/* bIncCerts             include certificates or not      */
/* ostrSignedData        signed data to be signed         */
/* ostrSignedDataL       length of ostrSignedData         */
/* ostrInputData         input data to be signed          */
/* ostrInputDataL        length of ostrInputData          */
/*                                                        */
/* INPUT/OUTPUT                                           */
/*                                                        */
/* signer                signer information, security     */
/*                       information and SSF result after */
/*                       function return                  */
/*                                                        */
/* SSF_API_SIGNER_OK          operation successful        */
/* SSF_API_INVALID_NAMESPACE  unknown namespace id        */
/* SSF_API_UNKNOWN_SIGNER     unknown signer              */
/* SSF_API_UNKNOWN_PROFILE    security profile not found  */
/* SSF_API_INVALID_PROFILE    security profile not usable */
/* SSF_API_INVALID_PASSWORD   invalid password for signer */
/* SSF_API_NOCERTIFICATE      certificate not found       */
/* SSF_API_SIGNER_NOT_OK      signature not ok for signer */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* ostrUpdatedSignedData        signed data (output data) */
/* ostrUpdatedSignedDataL       length of output data     */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_API_OK                  success                    */
/* SSF_API_NOSECTK             security toolkit not found */
/* SSF_API_INVALID_FORMAT      unknown wrapper format     */
/* SSF_API_NODATA              wrong input data           */
/* SSF_API_NOMEMORY            no main memory output data */
/* SSF_API_SIGNER_ERRORS       there are signer errors    */
/* SSF_API_INVALID_MDALG       unknown hash algorithm     */
/* SSF_API_ENCODE_FAILED        ASN.1 encoding failed     */
/* SSF_API_DECODE_FAILED        ASN.1 decoding failed     */
/* SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG12_SSFADDSIGN  const SsfCharstring,  SsfCharlen,		\
			  const SsfCharstring,  SsfCharlen, SAP_BOOL,	\
			  const SsfOctetstring, SsfOctetlen,		\
			  const SsfOctetstring, SsfOctetlen,		\
			  PtrSigRcpSsfInformation,			\
			  SsfOctetstring *,     SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFADDSIGN)(ARG12_SSFADDSIGN);
SAPRETURN APIENTRY SsfAddSign (ARG12_SSFADDSIGN);

SAPRETURN APIENTRY SsfAddSign (
	const SsfCharstring		  strFormat,
	      SsfCharlen		  strFormatL,
	const SsfCharstring		  strHashalg,
	      SsfCharlen		  strHashalgL,
	      SAP_BOOL			  bIncCerts,
	const SsfOctetstring		  ostrSignedData,
	      SsfOctetlen		  ostrSignedDataL,
	const SsfOctetstring		  ostrInputData,
	      SsfOctetlen		  ostrInputDataL,
	      PtrSigRcpSsfInformation	  signer,      
	      SsfOctetstring		* ostrUpdatedSignedData,
	      SsfOctetlen		* ostrUpdatedSignedDataL );


/*--------------------------------------------------------*/
/* SsfDigest                                              */
/*                                                        */
/* Computes the hash value for the given input data using */
/* the specified hash algorithm.                          */
/*                                                        */
/* Supported formats:                                     */
/*                                                        */
/* PKCS7                 Data (input format)              */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* strFormat             target format                    */
/* strFormatL            length of strFormat              */
/* bDetached             include data or not              */
/* ostrInputData         input data to be digested        */
/* ostrInputDataL        length of ostrInputData          */
/* strHashalg            hash algorithm                   */
/* strHashalgL           length of strHashalg             */
/*                                                        */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* ostrDigestedData      digested data (output data)      */
/* ostrDigestedDataL     length of output data            */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_API_OK                  success                    */
/* SSF_API_NOSECTK             security toolkit not found */
/* SSF_API_INVALID_FORMAT      unknown wrapper format     */
/* SSF_API_NODATA              input data has length zero */
/* SSF_API_NOMEMORY            no main memory output data */
/* SSF_API_INVALID_MDALG       unknown hash algorithm     */
/* SSF_API_ENCODE_FAILED       ASN.1 encoding failed      */
/* SSF_API_DECODE_FAILED       ASN.1 decoding failed      */
/* SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG9_SSFDIGEST  const SsfCharstring,  SsfCharlen, SAP_BOOL,	\
			const SsfOctetstring, SsfOctetlen,		\
			const SsfCharstring,  SsfCharlen,		\
			SsfOctetstring *,     SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFDIGEST)(ARG9_SSFDIGEST);
SAPRETURN APIENTRY SsfDigest (ARG9_SSFDIGEST);

SAPRETURN APIENTRY SsfDigest (
		const SsfCharstring	  strFormat,
		      SsfCharlen	  strFormatL,
		      SAP_BOOL		  bDetached,
		const SsfOctetstring	  ostrInputData,
		      SsfOctetlen	  ostrInputDataL,
		const SsfCharstring	  strHashalg,
		      SsfCharlen	  strHashalgL,
		      SsfOctetstring	* ostrDigestedData,
		      SsfOctetlen	* ostrDigestedDataL );


/*--------------------------------------------------------*/
/* SsfDELSsfOctetstring                                   */
/*                                                        */
/* Deletes output data from previous SSF calls            */
/* (frees corresponding memory).                          */
/*                                                        */
/*                                                        */
/* INPUT/OUTPUT                                           */
/*                                                        */
/* SsfOctetstring ostrToBeDeleted      data to be deleted */
/* SsfOctetlen    ostrToBeDeletedL     length of above    */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_API_OK               operation successful          */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG2_SSFDELSSFOCTETSTRING  SsfOctetstring *, SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFDELSSFOCTETSTRING)(ARG2_SSFDELSSFOCTETSTRING);
SAPRETURN APIENTRY SsfDELSsfOctetstring (ARG2_SSFDELSSFOCTETSTRING);

SAPRETURN APIENTRY SsfDELSsfOctetstring (
			SsfOctetstring	* ostrToBeDeleted,
			SsfOctetlen	* ostrToBeDeletedL );


/**********************************************************************/
/*                                                                    */
/*  AUXILIARY                                                         */
/*                                                                    */
/**********************************************************************/

/**********************************************************************/
/*                                                                    */
/*  Export interface                                                  */
/*    - Function list                                                 */
/*                                                                    */
/**********************************************************************/


/* SSF auxiliary functions for signer/recipient SSF information lists */

/*--------------------------------------------------------*/
/* SsfNEWSigRcpSsfInfo                                    */
/*                                                        */
/* Creates a new signer/recipient SSF information data    */
/* structure by allocating and initializing memory.       */
/* Returns a pointer to the new signer/recipient          */
/* information data.                                      */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* SsfCharstring  strSigRcpId           sig./recip. name  */
/* SsfCharlen     strSigRcpIdL          length of above   */
/* SsfCharstring  strSigRcpReserved	reserved for futur*/
/*                                      use (or NULL)     */
/* SsfCharlen     strSigRcpReservedL	length of above   */
/* SsfCharstring  strSigRcpProfile      sig/rcp secinfo   */
/*                                      profile name      */
/*                                      (if any, may be   */
/*                                      empty)            */
/* SsfCharlen     strSigRcpProfileL     length of above   */
/* SsfCharstring  strSigRcpPassword     password for      */
/*                                      sig/rcp secinfo   */
/*                                      (if any, may be   */
/*                                      empty)            */
/* SsfCharlen     strSigRcpPasswordL    length of above   */
/* SAP_UINT       uResult               result value      */
/*                                                        */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* PtrSigRcpSsf                         ptrSigRcpSsfInfo  */
/*                                                        */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_AUX_OK            operation successful             */
/* SSF_AUX_NOMEMORY      insuff. main memory output data  */
/* SSF_AUX_NOSIGRCPID    sig/rcp id is empty              */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG10_SSFNEWSIGRCPSSFINFO  const SsfCharstring, SsfCharlen,	\
				   const SsfCharstring, SsfCharlen,	\
				   const SsfCharstring, SsfCharlen,	\
				   const SsfCharstring, SsfCharlen,	\
				   SAP_UINT, PtrSigRcpSsfInformation *
typedef SAPRETURN (APIENTRY FN_SSFNEWSIGRCPSSFINFO)(ARG10_SSFNEWSIGRCPSSFINFO);
SAPRETURN APIENTRY SsfNEWSigRcpSsfInfo (ARG10_SSFNEWSIGRCPSSFINFO);

SAPRETURN APIENTRY SsfNEWSigRcpSsfInfo (
	const SsfCharstring		  strSigRcpId,
	      SsfCharlen		  strSigRcpIdL,
	const SsfCharstring		  strSigRcpReserved,
	      SsfCharlen		  strSigRcpReservedL,
	const SsfCharstring		  strSigRcpProfile,
	      SsfCharlen		  strSigRcpProfileL,
	const SsfCharstring		  strSigRcpPassword,
	      SsfCharlen		  strSigRcpPasswordL,
	      SAP_UINT			  uResult,
	      PtrSigRcpSsfInformation	* ptrSigRcpSsfInfo );


/*--------------------------------------------------------*/
/* SsfDELSigRcpSsfInfo                                    */
/*                                                        */
/* Deletes a signer/recipient information data structure  */
/* and frees all associated memory (including contents).  */
/* Returns a NULL pointer.                                */
/*                                                        */
/*                                                        */
/* INPUT/OUTPUT                                           */
/*                                                        */
/* PtrSigRcpSsfInformation         ptrSigRcpSsfInfo       */
/*                                                        */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_AUX_OK            operation successful             */
/* SSF_AUX_NOSIGRCPINFO  signer/recipient information     */
/*                       data structure is empty          */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG1_SSFDELSIGRCPSSFINFO  PtrSigRcpSsfInformation *
typedef SAPRETURN (APIENTRY FN_SSFDELSIGRCPSSFINFO)(ARG1_SSFDELSIGRCPSSFINFO);
SAPRETURN APIENTRY SsfDELSigRcpSsfInfo (ARG1_SSFDELSIGRCPSSFINFO);

SAPRETURN APIENTRY SsfDELSigRcpSsfInfo ( 
	      PtrSigRcpSsfInformation	* ptrSigRcpSsfInfo);


/*--------------------------------------------------------*/
/* SsfINSSigRcpSsfInfo                                    */
/*                                                        */
/* Creates a new signer/recipient information list element*/
/* and inserts a given signer/recipient information data  */
/* structure at the end of a given signer/recipient       */
/* information list.                                      */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* PtrSigRcpSsfInformation        ptrSigRcpSsfInfo        */
/*                                                        */
/*                                                        */
/* INPUT/OUTPUT                                           */
/*                                                        */
/* SigRcpSsfInformationList       sigRcpSsfInfoList       */
/*                                                        */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_AUX_OK            operation successful             */
/* SSF_AUX_NOMEMORY      insuff. main memory output data  */
/* SSF_AUX_NOSIGRCPINFO  signer/recipient information     */
/*                       data structure is empty          */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG2_SSFINSSIGRCPSSFINFO  const PtrSigRcpSsfInformation,	\
				  SigRcpSsfInformationList *
typedef SAPRETURN (APIENTRY FN_SSFINSSIGRCPSSFINFO)(ARG2_SSFINSSIGRCPSSFINFO);
SAPRETURN APIENTRY SsfINSSigRcpSsfInfo (ARG2_SSFINSSIGRCPSSFINFO);

SAPRETURN APIENTRY SsfINSSigRcpSsfInfo ( 
	const PtrSigRcpSsfInformation	  ptrSigRcpSsfInfo,
	      SigRcpSsfInformationList	* sigRcpSsfInfoList );


/*--------------------------------------------------------*/
/* SsfDELSigRcpSsfInfoList                                */
/*                                                        */
/* Deletes a signer/recipient information list element by */
/* element and frees the corresponding memory.            */
/* (including content structure)                          */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* SigRcpSsfInformationList       sigRcpSsfInfoList       */
/*                                                        */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_AUX_OK               operation successful          */
/* SSF_AUX_NOSIGRCPINFOLIST signer/recipient info list is */
/*                          empty                         */
/*                                                        */
/*--------------------------------------------------------*/

#define ARG1_SSFDELSIGRCPSSFINFOLIST  SigRcpSsfInformationList *
typedef SAPRETURN (APIENTRY FN_SSFDELSIGRCPSSFINFOLIST)(ARG1_SSFDELSIGRCPSSFINFOLIST);
SAPRETURN APIENTRY SsfDELSigRcpSsfInfoList (ARG1_SSFDELSIGRCPSSFINFOLIST);

SAPRETURN APIENTRY SsfDELSigRcpSsfInfoList (
			SigRcpSsfInformationList * sigRcpSsfInfoList );


/**********************************************************/
/*                                                        */
/*  Function:  SsfPRISigRcpSsfInfo                        */
/*                                                        */
/*  Author:    M. FRIEDRICH                               */
/*  Version:   1.32                                       */
/*                                                        */
/* Prints  a signer/recipient information data structure  */
/* to memory                                              */
/*                                                        */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* PtrSigRcpSsfInformation        ptrSigRcpSsfInfo        */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* ostrOutputData        signer/recipient information     */
/* ostrOutputDataL       length of above                  */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_AUX_OK            operation successful             */
/* SSF_AUX_NOMEMORY      no more memory for output data   */
/* SSF_AUX_NOSIGRCPINFO  signer/recipient information     */
/*                       data structure is empty          */
/*                                                        */
/**********************************************************/

/* NOTE: the next two functions have been removed from the API */
/*       and aren't used any more. They are left here so that  */
/*       old kernels will not core. The functions currently    */
/*       always return SSF_AUX_NOMEMORY !!!                    */
SAPRETURN APIENTRY SsfPRISigRcpSsfInfo (
	      PtrSigRcpSsfInformation	  ptrSigRcpSsfInfo,
	      SsfOctetstring		* outputData,
	      SsfOctetlen		* outputDataL );

/**********************************************************/
/*                                                        */
/*  Function:  SsfPRISigRcpSsfInfoList                    */
/*                                                        */
/*  Author:    M. FRIEDRICH                               */
/*  Version:   1.32                                       */
/*                                                        */
/* Prints  a signer/recipient information list element by */
/* element to memory                                      */
/*                                                        */
/* INPUT                                                  */
/*                                                        */
/* SigRcpSsfInformationList       sigRcpSsfInfoList       */
/*                                                        */
/* OUTPUT                                                 */
/*                                                        */
/* ostrOutputData        list information                 */
/* ostrOutputDataL       length of above                  */
/*                                                        */
/* RETURN                                                 */
/*                                                        */
/* SSF_AUX_OK            operation successful             */
/* SSF_AUX_NOMEMORY      no more memory for output data   */
/* SSF_AUX_NOSIGRCPINFOLIST signer/recipient info list is */
/*                          empty                         */
/*                                                        */
/**********************************************************/

SAPRETURN APIENTRY SsfPRISigRcpSsfInfoList (
	      SigRcpSsfInformationList	  sigRcpSsfInfoList,
	      SsfOctetstring		* outputData,
	      SsfOctetlen		* outputDataL );



#ifdef SSF_VERSION2

/************************************************************/
/*							    */
/*  Function:  SsfOpenProfile				    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Opens a profile and returns a handle to that profile.  */
/*   Use this handle for the other SSf V2 functions	    */
/*   Close the profile with SsfCloseProfile		    */
/*							    */
/* INPUT						    */
/*   ProfileName	name of the profile		    */
/*   ProfileNameL	length of above			    */
/*   Password		profile's password		    */
/*   PasswordL		length of above			    */
/*   Mode		unused, pass NULL		    */
/*   ModeL		length of above			    */
/*							    */
/* OUTPUT						    */
/*							    */
/*   Handle		Handle to the opened profile	    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK			profile successfully opened */
/*   SSF_API_NOMEMORY		no main memory		    */
/*   SSF_API_UNKNOWN_PROFILE	security profile not found  */
/*   SSF_API_INVALID_PROFILE	security profile not usable */
/*   SSF_API_INVALID_PASSWORD	invalid password for signer */
/*   SSF_API_UNKNOWN_SECTK_ERROR  unknown sec. toolk. error */
/*							    */
/*----------------------------------------------------------*/

#define ARG7_SSFOPENPROFILE  const SsfCharstring,  SsfCharlen,		\
			     const SsfCharstring,  SsfCharlen,		\
			     const SsfCharstring,  SsfCharlen,		\
			     SsfProfileHandle *
typedef SAPRETURN (APIENTRY FN_SSFOPENPROFILE)(ARG7_SSFOPENPROFILE);
SAPRETURN APIENTRY SsfOpenProfile (ARG7_SSFOPENPROFILE);

SAPRETURN APIENTRY SsfOpenProfile (
	const SsfCharstring		  ProfileName,
	      SsfCharlen		  ProfileNameL,
	const SsfCharstring		  Password,
	      SsfCharlen		  PasswordL,
	const SsfCharstring		  Mode,
	      SsfCharlen		  ModeL,
	      SsfProfileHandle		* Handle );


/************************************************************/
/*							    */
/*  Function:  SsfCloseProfile				    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Closes a profile that has been opened with		    */
/*   SsfOpenProfile					    */
/*							    */
/*							    */
/* INPUT/OUTPUT						    */
/*							    */
/*   Handle	    Handle to the opened profile	    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK	    profile successfully closed		    */
/*							    */
/*----------------------------------------------------------*/
#define ARG1_SSFCLOSEPROFILE  SsfProfileHandle *
typedef SAPRETURN (APIENTRY FN_SSFCLOSEPROFILE)(ARG1_SSFCLOSEPROFILE);
SAPRETURN APIENTRY SsfCloseProfile (ARG1_SSFCLOSEPROFILE);

SAPRETURN APIENTRY SsfCloseProfile (
	      SsfProfileHandle		* Handle );


/************************************************************/
/*							    */
/*  Function:  SsfCreateProfile				    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Creates a new profile.				    */
/*   Note that the profile isn't opened after this call!    */
/*							    */
/*							    */
/* INPUT						    */
/*							    */
/*   ProfileName	name of the profile		    */
/*   ProfileNameL	length of above			    */
/*   Password		profile's password		    */
/*   PasswordL		length of above			    */
/*   Mode		unused, pass NULL		    */
/*   ModeL		length of above			    */
/*							    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK                profile successfully created */
/*   SSF_API_NOMEMORY          no main memory		    */
/*   SSF_API_INVALID_PROFILE   profile already exists	    */
/*   SSF_API_UNKNOWN_PROFILE   error creating profile	    */
/*   SSF_API_INVALID_PASSWORD  wrong password		    */
/*   SSF_API_UNKNOWN_SECTK_ERROR  unknown sec. toolk. error */
/*							    */
/*----------------------------------------------------------*/

#define ARG6_SSFCREATEPROFILE  const SsfCharstring, SsfCharlen, \
			       const SsfCharstring, SsfCharlen, \
			       const SsfCharstring, SsfCharlen
typedef SAPRETURN (APIENTRY FN_SSFCREATEPROFILE)(ARG6_SSFCREATEPROFILE);
SAPRETURN APIENTRY SsfCreateProfile (ARG6_SSFCREATEPROFILE);

SAPRETURN APIENTRY SsfCreateProfile (
	const SsfCharstring		  ProfileName,
	      SsfCharlen		  ProfileNameL,
	const SsfCharstring		  Password,
	      SsfCharlen		  PasswordL,
	const SsfCharstring		  Mode,
	      SsfCharlen		  ModeL );


/************************************************************/
/*							    */
/*  Function:  SsfRemoveProfile				    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Physically destroyes the profile.			    */
/*							    */
/*							    */
/* INPUT						    */
/*							    */
/*   ProfileName	name of the profile		    */
/*   ProfileNameL	length of above			    */
/*							    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK                   success for each signer   */
/*   SSF_API_NOMEMORY             no main memory	    */
/*   SSF_API_INVALID_PROFILE	  profile file is read only */
/*   SSF_API_UNKNOWN_PROFILE	  profile file not found    */
/*   SSF_API_UNKNOWN_SECTK_ERROR  unknown sec. toolk. error */
/*							    */
/*----------------------------------------------------------*/
#define ARG2_SSFREMOVEPROFILE  const SsfCharstring, SsfCharlen
typedef SAPRETURN (APIENTRY FN_SSFREMOVEPROFILE)(ARG2_SSFREMOVEPROFILE);
SAPRETURN APIENTRY SsfRemoveProfile (ARG2_SSFREMOVEPROFILE);

SAPRETURN APIENTRY SsfRemoveProfile (
	const SsfCharstring		  ProfileName,
	      SsfCharlen		  ProfileNameL );


/**********************************************************/
/**********************************************************/
/**********************************************************/
/**********************************************************/

/************************************************************/
/*							    */
/*  Function:  SsfGetCertificate			    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*  Retrieves a certificate from the given profile.	    */
/*  Free the handle with SsfFreeCertificate		    */
/*							    */
/* INPUT						    */
/*							    */
/*  Handle		Handle to the opened profile	    */
/*  Identification	which certificate		    */
/*							    */
/* OUTPUT						    */
/*							    */
/*  Cert		Handle to the found certificate	    */
/*							    */
/* RETURN						    */
/*							    */
/*  SSF_API_OK                   success for each signer    */
/*  SSF_API_NOMEMORY             no main memory		    */
/*  SSF_API_UNKNOWN_SIGNER	 cert not found		    */
/*  SSF_API_UNKNOWN_SECTK_ERROR  unknown sec. toolk. error  */
/*							    */
/*----------------------------------------------------------*/
#define ARG3_SSFGETCERTIFICATE  SsfProfileHandle,	\
				SsfCertIdent *, SsfCertHandle *
typedef SAPRETURN (APIENTRY FN_SSFGETCERTIFICATE)(ARG3_SSFGETCERTIFICATE);
SAPRETURN APIENTRY SsfGetCertificate (ARG3_SSFGETCERTIFICATE);

SAPRETURN APIENTRY SsfGetCertificate (
	      SsfProfileHandle		  Handle,
	      SsfCertIdent		* Identification,
	      SsfCertHandle		* Cert );


/************************************************************/
/*							    */
/*  Function:  SsfPutCertificate			    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Adds a certificate to the given profile.		    */
/*   Note that the certificate isn't freed by this routine  */
/*							    */
/* INPUT						    */
/*							    */
/*   Handle		Handle to the opened profile	    */
/*   Cert		Handle to the found certificate	    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK                  success for each signer    */
/*   SSF_API_NOMEMORY            no main memory output data */
/*   SSF_API_SIGNER_NOT_OK	 Cert already exists	    */
/*   SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*							    */
/*----------------------------------------------------------*/
#define ARG2_SSFPUTCERTIFICATE  SsfProfileHandle, SsfCertHandle
typedef SAPRETURN (APIENTRY FN_SSFPUTCERTIFICATE)(ARG2_SSFPUTCERTIFICATE);
SAPRETURN APIENTRY SsfPutCertificate (ARG2_SSFPUTCERTIFICATE);

SAPRETURN APIENTRY SsfPutCertificate (
	      SsfProfileHandle		  Handle,
	      SsfCertHandle		  Cert );


/************************************************************/
/*							    */
/*  Function:  SsfRemoveCertificate			    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/* Removes a certificate from the given profile.	    */
/*							    */
/*							    */
/* INPUT						    */
/*							    */
/*  Handle		Handle to the opened profile	    */
/*  Identification	which certificate		    */
/*							    */
/*							    */
/* RETURN						    */
/*							    */
/*  SSF_API_OK                  success for each signer	    */
/*  SSF_API_NOMEMORY            no main memory output data  */
/*  SSF_API_UNKNOWN_SIGNER	Cert not found		    */
/*  SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error   */
/*							    */
/*----------------------------------------------------------*/
#define ARG2_SSFREMOVECERTIFICATE  SsfProfileHandle, SsfCertIdent *
typedef SAPRETURN (APIENTRY FN_SSFREMOVECERTIFICATE)(ARG2_SSFREMOVECERTIFICATE);
SAPRETURN APIENTRY SsfRemoveCertificate (ARG2_SSFREMOVECERTIFICATE);

SAPRETURN APIENTRY SsfRemoveCertificate (
	      SsfProfileHandle		  Handle,
	      SsfCertIdent		* Identification );


/************************************************************/
/*							    */
/*  Function:  SsfFreeCertificate			    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Frees a certificate returned by SsfGetCertificate	    */
/*							    */
/*							    */
/* INPUT/OUTPUT						    */
/*							    */
/*   Cert	Handle to the found certificate		    */
/*							    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK        success for each signer		    */
/*							    */
/*----------------------------------------------------------*/
#define ARG1_SSFFREECERTIFICATE  SsfCertHandle *
typedef SAPRETURN (APIENTRY FN_SSFFREECERTIFICATE)(ARG1_SSFFREECERTIFICATE);
SAPRETURN APIENTRY SsfFreeCertificate (ARG1_SSFFREECERTIFICATE);

SAPRETURN APIENTRY SsfFreeCertificate (
	      SsfCertHandle		* Cert );


/**********************************************************/
/**********************************************************/
/**********************************************************/
/**********************************************************/

/************************************************************/
/*							    */
/*  Function:  SsfGetOwnCertificate			    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Retrieves own certificate from the given profile.	    */
/*   Free the handle with SsfFreeCertificate		    */
/*							    */
/* INPUT						    */
/*							    */
/*   Handle	Handle to the opened profile		    */
/*							    */
/* OUTPUT						    */
/*							    */
/*   Cert	Handle to the found certificate		    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK                   success for each signer   */
/*   SSF_API_NOMEMORY             no main memory	    */
/*   SSF_API_UNKNOWN_SIGNER	  cert not found	    */
/*   SSF_API_UNKNOWN_SECTK_ERROR  unknown sec. toolk. error */
/*							    */
/*----------------------------------------------------------*/
#define ARG2_SSFGETOWNCERTIFICATE  SsfProfileHandle, SsfCertHandle *
typedef SAPRETURN (APIENTRY FN_SSFGETOWNCERTIFICATE)(ARG2_SSFGETOWNCERTIFICATE);
SAPRETURN APIENTRY SsfGetOwnCertificate (ARG2_SSFGETOWNCERTIFICATE);

SAPRETURN APIENTRY SsfGetOwnCertificate (
	      SsfProfileHandle		  Handle,
	      SsfCertHandle		* Cert );


/************************************************************/
/*							    */
/*  Function:  SsfGetCertificateList			    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Retrieves a certificate list from the given profile.   */
/*   Get the individual certificates with		    */
/*   SsfEnumCertificateList				    */
/*   Free the handle with SsfFreeCertificateList	    */
/*							    */
/* INPUT						    */
/*							    */
/*   Handle		Handle to the opened profile	    */
/*							    */
/* OUTPUT						    */
/*							    */
/*   CertList		Handle to the certificate list	    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK                  success for each signer    */
/*   SSF_API_NOMEMORY            no main memory output data */
/*   SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*							    */
/*----------------------------------------------------------*/
#define ARG2_SSFGETCERTIFICATELIST  SsfProfileHandle, SsfCertListHandle *
typedef SAPRETURN (APIENTRY FN_SSFGETCERTIFICATELIST)(ARG2_SSFGETCERTIFICATELIST);
SAPRETURN APIENTRY SsfGetCertificateList (ARG2_SSFGETCERTIFICATELIST);

SAPRETURN APIENTRY SsfGetCertificateList (
	      SsfProfileHandle		  Handle,
	      SsfCertListHandle		* CertList );


/************************************************************/
/*							    */
/*  Function:  SsfEnumCertificateList			    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Retrieves the next certificate from the certificate    */
/*   list returned by SsfGetCertificateList		    */
/*   Free the handle with SsfFreeCertificate		    */
/*							    */
/* INPUT						    */
/*							    */
/*   CertList		Handle to the certificate list	    */
/*							    */
/* OUTPUT						    */
/*							    */
/*   Cert		Handle to the found certificate	    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK                  success for each signer    */
/*   SSF_API_NODATA		 end of certificate list    */
/*   SSF_API_NOMEMORY            no main memory output data */
/*   SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*							    */
/*----------------------------------------------------------*/
#define ARG2_SSFENUMCERTIFICATELIST  SsfCertListHandle, SsfCertHandle *
typedef SAPRETURN (APIENTRY FN_SSFENUMCERTIFICATELIST)(ARG2_SSFENUMCERTIFICATELIST);
SAPRETURN APIENTRY SsfEnumCertificateList (ARG2_SSFENUMCERTIFICATELIST);

SAPRETURN APIENTRY SsfEnumCertificateList (
	      SsfCertListHandle		  CertList,
	      SsfCertHandle		* Cert );


/************************************************************/
/*							    */
/*  Function:  SsfFreeCertificateList			    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Frees the certificate list returned by		    */
/*   SsfGetCertificateList				    */
/*							    */
/* INPUT/OUTPUT						    */
/*							    */
/*   CertList		Handle to the certificate list	    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK                  success for each signer    */
/*							    */
/*----------------------------------------------------------*/
#define ARG1_SSFFREECERTIFICATELIST  SsfCertListHandle *
typedef SAPRETURN (APIENTRY FN_SSFFREECERTIFICATELIST)(ARG1_SSFFREECERTIFICATELIST);
SAPRETURN APIENTRY SsfFreeCertificateList (ARG1_SSFFREECERTIFICATELIST);

SAPRETURN APIENTRY SsfFreeCertificateList (
	      SsfCertListHandle		* CertList );


/**********************************************************/
/**********************************************************/
/**********************************************************/
/**********************************************************/

/************************************************************/
/*							    */
/*  Function:  SsfCertfromASN1				    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Converts an ASN1-encoded certificate to the internal   */
/*   format.						    */
/*   Free the handle with SsfFreeCertificate		    */
/*							    */
/* INPUT						    */
/*							    */
/*   ASN1Cert		X.509 certificate (ASN1 encoded)    */
/*   ASN1CertL		length of above			    */
/*							    */
/* OUTPUT						    */
/*							    */
/*   Cert		Handle to the found certificate	    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK                  success for each signer    */
/*   SSF_API_NOMEMORY            no main memory		    */
/*   SSF_API_DECODE_FAILED		decoding failed	    */
/*   SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*							    */
/*----------------------------------------------------------*/
#define ARG3_SSFCERTFROMASN1  const SsfOctetstring, SsfOctetlen,	\
			      SsfCertHandle *
typedef SAPRETURN (APIENTRY FN_SSFCERTFROMASN1)(ARG3_SSFCERTFROMASN1);
SAPRETURN APIENTRY SsfCertfromASN1 (ARG3_SSFCERTFROMASN1);

SAPRETURN APIENTRY SsfCertfromASN1 (
	const SsfOctetstring		  ASN1Cert,
	      SsfOctetlen		  ASN1CertL,
	      SsfCertHandle		* Cert );


/************************************************************/
/*							    */
/*  Function:  SsfCerttoASN1				    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Converts a certificate from the internal format	    */
/*   to the ASN1-encoded format				    */
/*							    */
/* INPUT						    */
/*							    */
/*   Cert		Handle to the certificate	    */
/*							    */
/* OUTPUT						    */
/*							    */
/*   ASN1Cert		X.509 certificate (ASN1 encoded)    */
/*   ASN1CertL		length of above			    */
/*			Free with SsfDELSsfOctetstring	    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK                  success for each signer    */
/*   SSF_API_NOMEMORY            no main memory		    */
/*   SSF_API_ENCODE_FAILED		encoding failed	    */
/*   SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*							    */
/*----------------------------------------------------------*/
#define ARG3_SSFCERTTOASN1  SsfCertHandle, SsfOctetstring *, SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFCERTTOASN1)(ARG3_SSFCERTTOASN1);
SAPRETURN APIENTRY SsfCerttoASN1 (ARG3_SSFCERTTOASN1);

SAPRETURN APIENTRY SsfCerttoASN1 (
	      SsfCertHandle		  Cert,
	      SsfOctetstring		* ASN1Cert,
	      SsfOctetlen		* ASN1CertL );


/************************************************************/
/*							    */
/*  Function:  SsfParseCertificate			    */
/*							    */
/*  Author:    Michael Friedrich			    */
/*  Version:   1.00					    */
/*							    */
/*   Extracts information from a given certificate handle.  */
/*							    */
/* INPUT						    */
/*							    */
/*   Cert	Handle to the found certificate		    */
/*   Type	what kind of information. one of:	    */
/*   		  SUMMARY, SUBJECT, ISSUER, SERIALNO	    */
/*		  FINGERPRINT,				    */
/*		  SERIAL (serialnumber as defined in	    */
/*				structure SsfCertIdent)	    */
/*   TypeL	length of above				    */
/*							    */
/*							    */
/* OUTPUT						    */
/*   Value	free with SsfDELSsfOctetstring		    */
/*   ValueL						    */
/*							    */
/* RETURN						    */
/*							    */
/*   SSF_API_OK                  success for each signer    */
/*   SSF_API_NODATA		 unknown type, no data	    */
/*   SSF_API_NOMEMORY            no main memory output data */
/*   SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error  */
/*							    */
/* Note: When storing certificates in the profile, the      */
/*       fingerprint is lost.				    */
/*							    */
/*----------------------------------------------------------*/

#define ARG5_SSFPARSECERTIFICATE  SsfCertHandle,			\
				  const SsfCharstring, SsfCharlen,	\
				  SsfOctetstring *, SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFPARSECERTIFICATE)(ARG5_SSFPARSECERTIFICATE);
SAPRETURN APIENTRY SsfParseCertificate (ARG5_SSFPARSECERTIFICATE);

SAPRETURN APIENTRY SsfParseCertificate (
	      SsfCertHandle		  Cert,
	const SsfCharstring		  Type,
	      SsfCharlen		  TypeL,
	      SsfOctetstring		* Value,
	      SsfOctetlen		* ValueL );


/****************************************************************/ 
/*								*/ 
/*  Function:  SsfGetCertificateRequest				*/ 
/*								*/ 
/*  Author:    Maik Mueller					*/ 
/*  Version:   1.00						*/ 
/*								*/ 
/*   Retrieves own certificate request from the given profile.	*/ 
/*   Free the output data with SsfFreeOctetString		*/ 
/*								*/ 
/* INPUT							*/ 
/*								*/ 
/*   Handle		Handle to the opened profile		*/ 
/*								*/ 
/* OUTPUT							*/ 
/*								*/ 
/*   CertRequest	certificate request			*/ 
/*   CertRequestL	length of data				*/ 
/*								*/ 
/* RETURN							*/ 
/*								*/ 
/*   SSF_API_OK                  success for each signer	*/ 
/*   SSF_API_NOMEMORY            no main memory			*/ 
/*   SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error	*/ 
/*								*/ 
/*--------------------------------------------------------------*/ 
#define ARG3_SSFGETCERTIFICATEREQUEST  SsfProfileHandle,		\
				       SsfOctetstring *, SsfOctetlen *
typedef SAPRETURN (APIENTRY FN_SSFGETCERTIFICATEREQUEST)(ARG3_SSFGETCERTIFICATEREQUEST);
SAPRETURN APIENTRY SsfGetCertificateRequest (ARG3_SSFGETCERTIFICATEREQUEST);

SAPRETURN APIENTRY SsfGetCertificateRequest ( 
	      SsfProfileHandle		  Handle, 
	      SsfOctetstring		* CertRequest, 
	      SsfOctetlen		* CertRequestL ); 

 
/****************************************************************/ 
/*								*/ 
/*  Function:  SsfPutCertificateResponse			*/ 
/*								*/ 
/*  Author:    Maik Mueller					*/ 
/*  Version:   1.00						*/ 
/*								*/ 
/*   Stores the signed certificate reponse to the given profile.*/ 
/*   Note that the certificate isn't freed by this routine	*/ 
/*								*/ 
/* INPUT							*/ 
/*								*/ 
/*   Handle		Handle to the opened profile		*/ 
/*   CertResponse	certificate response			*/ 
/*   CertResponseL	length of data				*/ 
/*								*/ 
/* RETURN							*/ 
/*								*/ 
/*   SSF_API_OK                  success for each signer	*/ 
/*   SSF_API_NOMEMORY            no main memory output data	*/ 
/*   SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error	*/ 
/*   and the error codes defined in pkcs_install_CertificationRequest */ 
/*								*/ 
/*--------------------------------------------------------------*/ 
#define ARG3_SSFPUTCERTIFICATERESPONSE  SsfProfileHandle,		\
					SsfOctetstring, SsfOctetlen
typedef SAPRETURN (APIENTRY FN_SSFPUTCERTIFICATERESPONSE)(ARG3_SSFPUTCERTIFICATERESPONSE);
SAPRETURN APIENTRY SsfPutCertificateResponse (ARG3_SSFPUTCERTIFICATERESPONSE);

SAPRETURN APIENTRY SsfPutCertificateResponse (
	      SsfProfileHandle		  Handle, 
	      SsfOctetstring		  CertResponse, 
	      SsfOctetlen		  CertResponseL ); 


#endif /* SSF_VERSION2 */

/****************************************************************/ 
/*							    	*/ 
/*  Function:  sapsecu_parseobject				*/ 
/*								*/ 
/*  Author:    Maik Mueller					*/ 
/*  Version:   1.00						*/ 
/*								*/ 
/*   Stores the signed certificate reponse to the given profile.*/ 
/*   Note that the certificate isn't freed by this routine	*/ 
/*								*/ 
/* INPUT							*/ 
/*								*/ 
/*   Format		try "PKCS10RFC1421"			*/ 
/*   Type		try "SubjectName"			*/ 
/*   object		should correspond to given Format	*/ 
/*   objectL		length of data				*/ 
/*								*/ 
/* OUTPUT							*/ 
/*								*/ 
/*   value		hopefully what you requested		*/ 
/*   valueL		length of data				*/ 
/*								*/ 
/* RETURN							*/ 
/*								*/ 
/*   SSF_API_OK                  success for each signer	*/ 
/*   SSF_API_NOMEMORY            no main memory output data	*/ 
/*   SSF_API_UNKNOWN_SECTK_ERROR unknown sec. toolk. error	*/ 
/*								*/ 
/*--------------------------------------------------------------*/ 
#define ASN1_PKCS10RFC1421	"PKCS10RFC1421" 
#define ASN1_SubjectName	"SubjectName" 
/* #define ASN1_IssuerName"	"IssuerName" 
   #define ASN1_SerialNumber	"SerialNumber" */

#define ARG6_SAPSECU_PARSEOBJECT  const char *, const char *,	\
				  const char *, SAP_INT,	\
				  char **,      SAP_INT *
typedef SAPRETURN (APIENTRY FN_SAPSECU_PARSEOBJECT)(ARG6_SAPSECU_PARSEOBJECT);
SAPRETURN APIENTRY sapsecu_parseobject (ARG6_SAPSECU_PARSEOBJECT);
 
SAPRETURN APIENTRY sapsecu_parseobject (
	const char			 * Format, 
	const char			 * Type, 
	const char			 * object, 
	      SAP_INT			   objectL, 
	      char			** value, 
	      SAP_INT			 * valueL ); 


#ifdef __cplusplus
}
#endif

#endif  /* SSFXXAPI_H */


