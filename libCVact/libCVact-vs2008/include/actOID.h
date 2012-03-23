//////////////////////////////////////////////////////////////////////////////////
// Name:      actOID.h
// Product:   cv act library
// Purpose:   
//            
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_OID_H
#define ACT_OID_H

#define CV_OID_DEF(x) (act::Blob((x),(x)+sizeof((x))))

#ifdef _MSC_VER
#pragma warning(disable : 4305) //Verkuerzung von 'static const int' in 'static const unsigned char'
#pragma warning(disable : 4309) //Verkuerzung eines konstanten Wertes
#endif

//1.2.840.10045.4.1			ECDSA cvECDSA
static const unsigned char cvOID_cvECDSA[]			= {0x2a, 0x86, 0x48, 0xce, 0x3d, 0x04, 0x01};
//1.2.840.113549.1.9.1		Alternate Name cvAlternateName
static const unsigned char cvOID_cvAlternateName[]	= {0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x09, 0x01};

//0.2.262.1.10		Deutsche Telekom Telesec 
static const unsigned char cvOID_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A};
//0.2.262.1.10.0		Telesec extension 
static const unsigned char cvOID_extension [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x00};
//0.2.262.1.10.1		Telesec mechanism 
static const unsigned char cvOID_mechanism [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01};
//0.2.262.1.10.1.0		Telesec mechanism authentication 
static const unsigned char cvOID_authentication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00};
//0.2.262.1.10.1.0.1		Telesec authentication passwordAuthentication 
static const unsigned char cvOID_passwordAuthentication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x01};
//0.2.262.1.10.1.0.2		Telesec authentication protectedPasswordAuthentication 
static const unsigned char cvOID_protectedPasswordAuthentication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x02};
//0.2.262.1.10.1.0.3		Telesec authentication oneWayX509Authentication 
static const unsigned char cvOID_oneWayX509Authentication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x03};
//0.2.262.1.10.1.0.4		Telesec authentication twoWayX509Authentication 
static const unsigned char cvOID_twoWayX509Authentication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x04};
//0.2.262.1.10.1.0.5		Telesec authentication threeWayX509Authentication 
static const unsigned char cvOID_threeWayX509Authentication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x05};
//0.2.262.1.10.1.0.6		Telesec authentication oneWayISO9798Authentication 
static const unsigned char cvOID_oneWayISO9798Authentication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x06};
//0.2.262.1.10.1.0.7		Telesec authentication twoWayISO9798Authentication 
static const unsigned char cvOID_twoWayISO9798Authentication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x07};
//0.2.262.1.10.1.0.8		Telesec authentication telekomAuthentication 
static const unsigned char cvOID_telekomAuthentication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x08};
//0.2.262.1.10.1.1		Telesec mechanism signature 
static const unsigned char cvOID_signature [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01};
//0.2.262.1.10.1.1.1		Telesec mechanism md4WithRSAAndISO9697 
static const unsigned char cvOID_md4WithRSAAndISO9697 [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01, 0x01};
//0.2.262.1.10.1.1.2		Telesec mechanism md4WithRSAAndTelesecSignatureStandard 
static const unsigned char cvOID_md4WithRSAAndTelesecSignatureStandard [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01, 0x02};
//0.2.262.1.10.1.1.3		Telesec mechanism md5WithRSAAndISO9697 
static const unsigned char cvOID_md5WithRSAAndISO9697 [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01, 0x03};
//0.2.262.1.10.1.1.4		Telesec mechanism md5WithRSAAndTelesecSignatureStandard 
static const unsigned char cvOID_md5WithRSAAndTelesecSignatureStandard [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01, 0x04};
//0.2.262.1.10.1.1.5		Telesec mechanism ripemd160WithRSAAndTelekomSignatureStandard 
static const unsigned char cvOID_ripemd160WithRSAAndTelekomSignatureStandard [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01, 0x05};
//0.2.262.1.10.1.1.9		Telesec signature hbciRsaSignature 
static const unsigned char cvOID_hbciRsaSignature [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01, 0x09};
//0.2.262.1.10.1.2		Telesec mechanism encryption 
static const unsigned char cvOID_encryption [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02};
//0.2.262.1.10.1.2.0		Telesec encryption none 
static const unsigned char cvOID_none [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x00};
//0.2.262.1.10.1.2.1		Telesec encryption rsaTelesec 
static const unsigned char cvOID_rsaTelesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x01};
//0.2.262.1.10.1.2.2		Telesec encryption des 
static const unsigned char cvOID_des [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x02};
//0.2.262.1.10.1.2.2.1		Telesec encryption desECB 
static const unsigned char cvOID_desECB [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x02, 0x01};
//0.2.262.1.10.1.2.2.2		Telesec encryption desCBC 
static const unsigned char cvOID_desCBC [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x02, 0x02};
//0.2.262.1.10.1.2.2.3		Telesec encryption desOFB 
static const unsigned char cvOID_desOFB [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x02, 0x03};
//0.2.262.1.10.1.2.2.4		Telesec encryption desCFB8 
static const unsigned char cvOID_desCFB8 [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x02, 0x04};
//0.2.262.1.10.1.2.2.5		Telesec encryption desCFB64 
static const unsigned char cvOID_desCFB64 [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x02, 0x05};
//0.2.262.1.10.1.2.3		Telesec encryption des3 
static const unsigned char cvOID_des3 [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x03};
//0.2.262.1.10.1.2.3.1		Telesec encryption des3ECB 
static const unsigned char cvOID_des3ECB [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x03, 0x01};
//0.2.262.1.10.1.2.3.2		Telesec encryption des3CBC 
static const unsigned char cvOID_des3CBC [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x03, 0x02};
//0.2.262.1.10.1.2.3.3		Telesec encryption des3OFB 
static const unsigned char cvOID_des3OFB [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x03, 0x03};
//0.2.262.1.10.1.2.3.4		Telesec encryption des3CFB8 
static const unsigned char cvOID_des3CFB8 [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x03, 0x04};
//0.2.262.1.10.1.2.3.5		Telesec encryption des3CFB64 
static const unsigned char cvOID_des3CFB64 [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x03, 0x05};
//0.2.262.1.10.1.2.4		Telesec encryption magenta 
static const unsigned char cvOID_magenta [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x04};
//0.2.262.1.10.1.2.5		Telesec encryption idea 
static const unsigned char cvOID_idea [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x05};
//0.2.262.1.10.1.2.5.1		Telesec encryption ideaECB 
static const unsigned char cvOID_ideaECB_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x05, 0x01};
//0.2.262.1.10.1.2.5.2		Telesec encryption ideaCBC 
static const unsigned char cvOID_ideaCBC_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x05, 0x02};
//0.2.262.1.10.1.2.5.3		Telesec encryption ideaOFB 
static const unsigned char cvOID_ideaOFB_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x05, 0x03};
//0.2.262.1.10.1.2.5.4		Telesec encryption ideaCFB8 
static const unsigned char cvOID_ideaCFB8_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x05, 0x04};
//0.2.262.1.10.1.2.5.5		Telesec encryption ideaCFB64 
static const unsigned char cvOID_ideaCFB64_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x05, 0x05};
//0.2.262.1.10.1.3		Telesec mechanism oneWayFunction 
static const unsigned char cvOID_oneWayFunction [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03};
//0.2.262.1.10.1.3.1		Telesec one-way function md4 
static const unsigned char cvOID_md4_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x01};
//0.2.262.1.10.1.3.2		Telesec one-way function md5 
static const unsigned char cvOID_md5_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x02};
//0.2.262.1.10.1.3.3		Telesec one-way function sqModNX509 
static const unsigned char cvOID_sqModNX509 [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x03};
//0.2.262.1.10.1.3.4		Telesec one-way function sqModNISO 
static const unsigned char cvOID_sqModNISO [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x04};
//0.2.262.1.10.1.3.5		Telesec one-way function ripemd128 
static const unsigned char cvOID_ripemd128 [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x05};
//0.2.262.1.10.1.3.6		Telesec one-way function hashUsingBlockCipher 
static const unsigned char cvOID_hashUsingBlockCipher [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x06};
//0.2.262.1.10.1.3.7		Telesec one-way function                     mac 
static const unsigned char cvOID_mac [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x07};
//0.2.262.1.10.1.3.8		Telesec one-way function ripemd160 
static const unsigned char cvOID_ripemd160 [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x08};
//0.2.262.1.10.1.4		Telesec mechanism fecFunction 
static const unsigned char cvOID_fecFunction [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x04};
//0.2.262.1.10.1.4.1		Telesec mechanism reedSolomon 
static const unsigned char cvOID_reedSolomon [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x04, 0x01};
//0.2.262.1.10.2		Telesec module 
static const unsigned char cvOID_module_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02};
//0.2.262.1.10.2.0		Telesec module algorithms 
static const unsigned char cvOID_algorithms [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x00};
//0.2.262.1.10.2.1		Telesec module attributeTypes 
static const unsigned char cvOID_attributeTypes [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x01};
//0.2.262.1.10.2.2		Telesec module certificateTypes 
static const unsigned char cvOID_certificateTypes [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x02};
//0.2.262.1.10.2.3)..		Telesec module messageTypes 
static const unsigned char cvOID_messageTypes [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x03};
//0.2.262.1.10.2.4		Telesec module plProtocol 
static const unsigned char cvOID_plProtocol [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x04};
//0.2.262.1.10.2.5		Telesec module smeAndComponentsOfSme 
static const unsigned char cvOID_smeAndComponentsOfSme [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x05};
//0.2.262.1.10.2.6		Telesec module fec 
static const unsigned char cvOID_fec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x06};
//0.2.262.1.10.2.7		Telesec module usefulDefinitions 
static const unsigned char cvOID_usefulDefinitions [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x07};
//0.2.262.1.10.2.8		Telesec module stefiles 
static const unsigned char cvOID_stefiles [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x08};
//0.2.262.1.10.2.9		Telesec module sadmib 
static const unsigned char cvOID_sadmib [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x09};
//0.2.262.1.10.2.10		Telesec module electronicOrder 
static const unsigned char cvOID_electronicOrder [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x0A};
//0.2.262.1.10.2.11		Telesec module telesecTtpAsymmetricApplication 
static const unsigned char cvOID_telesecTtpAsymmetricApplication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x0B};
//0.2.262.1.10.2.12).....		Telesec module telesecTtpBasisApplication 
static const unsigned char cvOID_telesecTtpBasisApplication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x0C};
//0.2.262.1.10.2.13).......		Telesec module telesecTtpMessages 
static const unsigned char cvOID_telesecTtpMessages [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x0D};
//0.2.262.1.10.2.14).......		Telesec module telesecTtpTimeStampApplication 
static const unsigned char cvOID_telesecTtpTimeStampApplication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x0E};
//0.2.262.1.10.3		Telesec objectClass 
static const unsigned char cvOID_objectClass_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x03};
//0.2.262.1.10.3.0		Telesec object class telesecOtherName 
static const unsigned char cvOID_telesecOtherName_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x03, 0x00};
//0.2.262.1.10.3.1		Telesec object class directory 
static const unsigned char cvOID_directory_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x03, 0x01};
//0.2.262.1.10.3.2		Telesec object class directoryType 
static const unsigned char cvOID_directoryType_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x03, 0x02};
//0.2.262.1.10.3.3		Telesec object class directroyGroup 
static const unsigned char cvOID_directroyGroup_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x03, 0x03};
//0.2.262.1.10.3.4		Telesec object class directoryUser 
static const unsigned char cvOID_directoryUser_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x03, 0x04};
//0.2.262.1.10.3.5		Telesec object class symmetricKeyEntry 
static const unsigned char cvOID_symmetricKeyEntry [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x03, 0x05};
//0.2.262.1.10.4		Telesec package 
static const unsigned char cvOID_package [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x04};
//0.2.262.1.10.5		Telesec parameter 
static const unsigned char cvOID_parameter [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x05};
//0.2.262.1.10.6		Telesec nameBinding 
static const unsigned char cvOID_nameBinding [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x06};
//0.2.262.1.10.7		Telesec attribute 
static const unsigned char cvOID_attribute_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07};
//0.2.262.1.10.7.0		Telesec attribute applicationGroupIdentifier 
static const unsigned char cvOID_applicationGroupIdentifier [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x00};
//0.2.262.1.10.7.1		Telesec attribute certificateType 
static const unsigned char cvOID_certificateType [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x01};
//0.2.262.1.10.7.2		Telesec attribute telesecCertificate 
static const unsigned char cvOID_Certificate_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x02};
//0.2.262.1.10.7.3		Telesec attribute certificateNumber 
static const unsigned char cvOID_certificateNumber [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x03};
//0.2.262.1.10.7.4		Telesec attribute certificateRevocationList 
static const unsigned char cvOID_certificateRevocationList_Telesec [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x04};
//0.2.262.1.10.7.5		Telesec attribute                               creationDate 
static const unsigned char cvOID_creationDate [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x05};
//0.2.262.1.10.7.6)....		Telesec attribute issuer 
static const unsigned char cvOID_issuer [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x06};
//0.2.262.1.10.7.7		Telesec attribute namingAuthority 
static const unsigned char cvOID_namingAuthority [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x07};
//0.2.262.1.10.7.8		Telesec attribute                     publicKeyDirectory 
static const unsigned char cvOID_publicKeyDirectory [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x08};
//0.2.262.1.10.7.9)..		Telesec attribute securityDomain 
static const unsigned char cvOID_securityDomain [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x09};
//0.2.262.1.10.7.10).....		Telesec attribute subject 
static const unsigned char cvOID_subject [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x0A};
//0.2.262.1.10.7.11		Telesec attribute             timeOfRevocation 
static const unsigned char cvOID_timeOfRevocation [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x0B};
//0.2.262.1.10.7.12		Telesec attribute userGroupReference 
static const unsigned char cvOID_userGroupReference [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x0C};
//0.2.262.1.10.7.13		Telesec attribute validity 
static const unsigned char cvOID_validity [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x0D};
//0.2.262.1.10.7.14		Telesec attribute zert93 
static const unsigned char cvOID_zert93 [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x0E};
//0.2.262.1.10.7.15		Telesec attribute securityMessEnv 
static const unsigned char cvOID_securityMessEnv [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x0F};
//0.2.262.1.10.7.16		Telesec attribute anonymizedPublicKeyDirectory 
static const unsigned char cvOID_anonymizedPublicKeyDirectory [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x10};
//0.2.262.1.10.7.17		Telesec attribute telesecGivenName 
static const unsigned char cvOID_telesecGivenName [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x11};
//0.2.262.1.10.7.18).		Telesec attribute nameAdditions 
static const unsigned char cvOID_nameAdditions [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x12};
//0.2.262.1.10.7.19		Telesec attribute telesecPostalCode 
static const unsigned char cvOID_telesecPostalCode [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x13};
//0.2.262.1.10.7.20		Telesec attribute nameDistinguisher 
static const unsigned char cvOID_nameDistinguisher [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x14};
//0.2.262.1.10.7.21		Telesec attribute telesecCertificateList 
static const unsigned char cvOID_telesecCertificateList [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x15};
//0.2.262.1.10.7.22		Telesec attribute teletrustCertificateList 
static const unsigned char cvOID_teletrustCertificateList [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x16};
//0.2.262.1.10.7.23)...		Telesec attribute x509CertificateList 
static const unsigned char cvOID_x509CertificateList [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x17};
//0.2.262.1.10.7.24		Telesec attribute                          timeOfIssue 
static const unsigned char cvOID_timeOfIssue [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x18};
//0.2.262.1.10.7.25		Telesec attribute physicalCardNumber 
static const unsigned char cvOID_physicalCardNumber [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x19};
//0.2.262.1.10.7.26)........		Telesec attribute fileType 
static const unsigned char cvOID_fileType [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x1A};
//0.2.262.1.10.7.27		Telesec attribute ctlFileIsArchive 
static const unsigned char cvOID_ctlFileIsArchive [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x1B};
//0.2.262.1.10.7.28)........		Telesec attribute emailAddress 
static const unsigned char cvOID_emailAddress [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x1C};
//0.2.262.1.10.7.29)........		Telesec attribute certificateTemplateList 
static const unsigned char cvOID_certificateTemplateList [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x1D};
//0.2.262.1.10.7.30)........		Telesec attribute directoryName 
static const unsigned char cvOID_directoryName [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x1E};
//0.2.262.1.10.7.31)........		Telesec attribute directoryTypeName 
static const unsigned char cvOID_directoryTypeName [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x1F};
//0.2.262.1.10.7.32		Telesec attribute directoryGroupName 
static const unsigned char cvOID_directoryGroupName [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x20};
//0.2.262.1.10.7.33		Telesec attribute directoryUserName 
static const unsigned char cvOID_directoryUserName [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x21};
//0.2.262.1.10.7.34		Telesec attribute revocationFlag 
static const unsigned char cvOID_revocationFlag [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x22};
//0.2.262.1.10.7.35		Telesec attribute symmetricKeyEntryName 
static const unsigned char cvOID_symmetricKeyEntryName [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x23};
//0.2.262.1.10.7.36		Telesec attribute glNumber 
static const unsigned char cvOID_glNumber [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x24};
//0.2.262.1.10.7.37		Telesec attribute goNumber 
static const unsigned char cvOID_goNumber [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x25};
//0.2.262.1.10.7.38		Telesec attribute gKeyData 
static const unsigned char cvOID_gKeyData [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x26};
//0.2.262.1.10.7.39		Telesec attribute zKeyData 
static const unsigned char cvOID_zKeyData [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x27};
//0.2.262.1.10.7.40		Telesec attribute ktKeyData 
static const unsigned char cvOID_ktKeyData [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x28};
//0.2.262.1.10.7.41		Telesec attribute ktKeyNumber 
static const unsigned char cvOID_ktKeyNumber [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x2A};
//0.2.262.1.10.7.51		Telesec attribute timeOfRevocationGen 
static const unsigned char cvOID_timeOfRevocationGen [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x33};
//0.2.262.1.10.7.52)....		Telesec attribute liabilityText 
static const unsigned char cvOID_liabilityText [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x34};
//0.2.262.1.10.8		Telesec attributeGroup 
static const unsigned char cvOID_attributeGroup [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x08};
//0.2.262.1.10.9		Telesec action 
static const unsigned char cvOID_action [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x09};
//0.2.262.1.10.10		Telesec notification 
static const unsigned char cvOID_notification [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x0A};
//0.2.262.1.10.11		Telesec snmp-mibs 
static const unsigned char cvOID_snmp_mibs [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x0B};
//0.2.262.1.10.11.1		Telesec SNMP MIBs securityApplication 
static const unsigned char cvOID_securityApplication [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x0B, 0x01};
//0.2.262.1.10.12		Telesec certAndCrlExtensionDefinitions 
static const unsigned char cvOID_certAndCrlExtensionDefinitions [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C};
//0.2.262.1.10.12.0		Telesec cert/CRL extension certExtensionLiabilityLimitationExt 
static const unsigned char cvOID_certExtensionLiabilityLimitationExt [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x00};
//0.2.262.1.10.12.1		Telesec cert/CRL extension telesecCertIdExt 
static const unsigned char cvOID_telesecCertIdExt [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x01};
//0.2.262.1.10.12.2		Telesec cert/CRL extension telesecPolicyIdentifier 
static const unsigned char cvOID_telesecPolicyIdentifier [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x02};
//0.2.262.1.10.12.3		Telesec cert/CRL extension telesecPolicyQualifierID 
static const unsigned char cvOID_telesecPolicyQualifierID [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x03};
//0.2.262.1.10.12.4		Telesec cert/CRL extension telesecCRLFilteredExt 
static const unsigned char cvOID_telesecCRLFilteredExt [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x04};
//0.2.262.1.10.12.5		Telesec cert/CRL extension telesecCRLFilterExt 
static const unsigned char cvOID_telesecCRLFilterExt [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x05};
//0.2.262.1.10.12.6		Telesec cert/CRL extension telesecNamingAuthorityExt 
static const unsigned char cvOID_telesecNamingAuthorityExt [] = {  0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x06};
//0.9.2342.19200300.1.3		Some oddball X.500 attribute collection rfc822Mailbox 
static const unsigned char cvOID_rfc822Mailbox [] = {  0x09, 0x92, 0x26, 0x89, 0x93, 0xF2, 0x2C, 0x01, 0x03};
//0.9.2342.19200300.100.1.25		Men are from Mars, this OID is from Pluto domainComponent 
static const unsigned char cvOID_domainComponent [] = {  0x09, 0x92, 0x26, 0x89, 0x93, 0xF2, 0x2C, 0x64, 0x01, 0x019};
//1.2.36.75878867.1.100.1.1		Certificates Australia CA Certificates Australia policyIdentifier 
static const unsigned char cvOID_Certificates_Australia_policyIdentifier [] = {  0x2A, 0x24, 0xA4, 0x97, 0xA3, 0x53, 0x01, 0x64, 0x01, 0x01};
//1.2.36.68980861.1.1.2		Signet CA Signet personal 
static const unsigned char cvOID_Signet_personal [] = {  0x2A, 0x24, 0xA0, 0xF2, 0xA0, 0x7D, 0x01, 0x01, 0x02};
//1.2.36.68980861.1.1.3		Signet CA Signet business 
static const unsigned char cvOID_Signet_business [] = {  0x2A, 0x24, 0xA0, 0xF2, 0xA0, 0x7D, 0x01, 0x01, 0x03};
//1.2.36.68980861.1.1.4		Signet CA Signet legal 
static const unsigned char cvOID_Signet_legal [] = {  0x2A, 0x24, 0xA0, 0xF2, 0xA0, 0x7D, 0x01, 0x01, 0x04};
//1.2.36.68980861.1.1.10		Signet CA Signet pilot 
static const unsigned char cvOID_Signet_pilot [] = {  0x2A, 0x24, 0xA0, 0xF2, 0xA0, 0x7D, 0x01, 0x01, 0x0A};
//1.2.36.68980861.1.1.11		Signet CA Signet intraNet 
static const unsigned char cvOID_Signet_intraNet [] = {  0x2A, 0x24, 0xA0, 0xF2, 0xA0, 0x7D, 0x01, 0x01, 0x0B};
//1.2.36.68980861.1.1.20		Signet CA Signet securityPolicy 
static const unsigned char cvOID_Signet_securityPolicy [] = {  0x2A, 0x24, 0xA0, 0xF2, 0xA0, 0x7D, 0x01, 0x01, 0x14};
//1.2.392.200011.61.1.1.1		Mitsubishi security algorithm symmetric-encryption-algorithm 
static const unsigned char cvOID_symmetric_encryption_algorithm [] = {  0x2A, 0x83, 0x08, 0x8C, 0x1A, 0x4B, 0x3D, 0x01, 0x01, 0x01};
//1.2.392.200011.61.1.1.1.1		Mitsubishi security algorithm misty1-cbc 
static const unsigned char cvOID_misty1_cbc [] = {  0x2A, 0x83, 0x08, 0x8C, 0x9A, 0x4B, 0x3D, 0x01, 0x01, 0x01, 0x01};
//1.2.752.34.1		SEIS Project seis-cp 
static const unsigned char cvOID_seis_cp [] = {  0x2A, 0x85, 0x70, 0x22, 0x01};
//1.2.752.34.1.1		SEIS Project certificate policies SEIS high-assurnace certificatePolicy 
static const unsigned char cvOID_SEIS_high_assurnace_certificatePolicy [] = {  0x2A, 0x85, 0x70, 0x22, 0x01, 0x01};
//1.2.752.34.1.2		SEIS Project certificate policies SEIS GAK certificatePolicy 
static const unsigned char cvOID_SEIS_GAK_certificatePolicy [] = {  0x2A, 0x85, 0x70, 0x22, 0x01, 0x02};
//1.2.752.34.2		SEIS Project SEIS pe 
static const unsigned char cvOID_SEIS_pe [] = {  0x2A, 0x85, 0x70, 0x22, 0x02};
//1.2.752.34.3		SEIS Project SEIS at 
static const unsigned char cvOID_SEIS_at [] = {  0x2A, 0x85, 0x70, 0x22, 0x03};
//1.2.752.34.3.1		SEIS Project attribute SEIS at-personalIdentifier 
static const unsigned char cvOID_SEIS_at_personalIdentifier [] = {  0x2A, 0x85, 0x70, 0x22, 0x03, 0x01};
//1.2.840.10040.1		ANSI X9.57 module 
static const unsigned char cvOID_module [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x01};
//1.2.840.10040.1.1		ANSI X9.57 module x9f1-cert-mgmt 
static const unsigned char cvOID_x9f1_cert_mgmt [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x01, 0x01};
//1.2.840.10040.2		ANSI X9.57 holdinstruction 
static const unsigned char cvOID_holdinstruction [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x02};
//1.2.840.10040.2.1		ANSI X9.57 hold instruction holdinstruction-none 
static const unsigned char cvOID_holdinstruction_none [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x02, 0x01};
//1.2.840.10040.2.2		ANSI X9.57 hold instruction callissuer 
static const unsigned char cvOID_callissuer [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x02, 0x02};
//1.2.840.10040.2.3		ANSI X9.57 hold instruction reject 
static const unsigned char cvOID_reject [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x02, 0x03};
//1.2.840.10040.2.4		ANSI X9.57 hold instruction pickupToken 
static const unsigned char cvOID_pickupToken [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x02, 0x04};
//1.2.840.10040.3		ANSI X9.57 attribute 
static const unsigned char cvOID_attribute [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x03};
//1.2.840.10040.3.1		ANSI X9.57 attribute countersignature 
static const unsigned char cvOID_countersignature [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x03, 0x01};
//1.2.840.10040.3.2		ANSI X9.57 attribute attribute-cert 
static const unsigned char cvOID_attribute_cert [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x03, 0x02};
//1.2.840.10040.4		ANSI X9.57 algorithm 
static const unsigned char cvOID_algorithm [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x04};
//1.2.840.10040.4.1		ANSI X9.57 algorithm dsa 
static const unsigned char cvOID_dsa [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x04, 0x01};
//1.2.840.10040.4.2		ANSI X9.57 algorithm dsa-match 
static const unsigned char cvOID_dsa_match [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x04, 0x02};
//1.2.840.10040.4.3		ANSI X9.57 algorithm dsaWithSha1 
static const unsigned char cvOID_dsaWithSha1 [] = {  0x2A, 0x86, 0x48, 0xCE, 0x38, 0x04, 0x03};
//1.2.840.10045.1		ANSI X9.62.  This OID is also assigned as ecdsa-with-SHA1 fieldType 
static const unsigned char cvOID_fieldType [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01};
//1.2.840.10045.1.1		ANSI X9.62 field type prime-field 
static const unsigned char cvOID_prime_field [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01, 0x01};
//1.2.840.10045.1.2		ANSI X9.62 field type characteristic-two-field 
static const unsigned char cvOID_characteristic_two_field [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01, 0x02};
//1.2.840.10045.1.2.3		ANSI X9.62 field type characteristic-two-basis 
static const unsigned char cvOID_characteristic_two_basis [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01, 0x02, 0x03};
//1.2.840.10045.1.2.3.1		ANSI X9.62 field basis onBasis 
static const unsigned char cvOID_onBasis [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01, 0x02, 0x03, 0x01};
//1.2.840.10045.1.2.3.2		ANSI X9.62 field basis tpBasis 
static const unsigned char cvOID_tpBasis [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01, 0x02, 0x03, 0x02};
//1.2.840.10045.1.2.3.3		ANSI X9.62 field basis ppBasis 
static const unsigned char cvOID_ppBasis [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01, 0x02, 0x03, 0x03};
//1.2.840.10045.2		ANSI X9.62 publicKeyType 
static const unsigned char cvOID_publicKeyType [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02};
//1.2.840.10045.2.1		ANSI X9.62 public key type ecPublicKey 
static const unsigned char cvOID_ecPublicKey [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02, 0x01};
//1.2.840.10046.1		ANSI X9.42 fieldType 
static const unsigned char cvOID_fieldType42 [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x01};
//1.2.840.10046.1.1		ANSI X9.42 field type gf-prime 
static const unsigned char cvOID_gf_prime [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x01, 0x01};
//1.2.840.10046.2		ANSI X9.42 numberType 
static const unsigned char cvOID_numberType [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x02};
//1.2.840.10046.2.1		ANSI X9.42 number type dhPublicKey 
static const unsigned char cvOID_dhPublicKey [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x02, 0x01};
//1.2.840.10046.3		ANSI X9.42 scheme 
static const unsigned char cvOID_scheme [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03};
//1.2.840.10046.3.1		ANSI X9.42 scheme dhStatic 
static const unsigned char cvOID_dhStatic [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03, 0x01};
//1.2.840.10046.3.2		ANSI X9.42 scheme dhEphem 
static const unsigned char cvOID_dhEphem [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03, 0x02};
//1.2.840.10046.3.3		ANSI X9.42 scheme dhHybrid1 
static const unsigned char cvOID_dhHybrid1 [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03, 0x03};
//1.2.840.10046.3.4		ANSI X9.42 scheme dhHybrid2 
static const unsigned char cvOID_dhHybrid2 [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03, 0x04};
//1.2.840.10046.3.5		ANSI X9.42 scheme mqv2 
static const unsigned char cvOID_mqv2 [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03, 0x05};
//1.2.840.10046.3.6		ANSI X9.42 scheme mqv1 
static const unsigned char cvOID_mqv1 [] = {  0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03, 0x06};
//1.2.840.113533.7.65.0		Nortel Secure Networks ce (1 2 840 113533 7 65) entrustVersInfo 
static const unsigned char cvOID_entrustVersInfo [] = {  0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x41, 0x00};
//1.2.840.113533.7.66.3		Nortel Secure Networks alg (1 2 840 113533 7 66) cast3CBC 
static const unsigned char cvOID_cast3CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x42, 0x03};
//1.2.840.113533.7.66.10		Nortel Secure Networks alg (1 2 840 113533 7 66) cast5CBC 
static const unsigned char cvOID_cast5CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x42, 0x0A};
//1.2.840.113533.7.66.11		Nortel Secure Networks alg (1 2 840 113533 7 66) cast5MAC 
static const unsigned char cvOID_cast5MAC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x42, 0x0B};
//1.2.840.113533.7.66.12		Nortel Secure Networks alg (1 2 840 113533 7 66) pbeWithMD5AndCAST5-CBC 
static const unsigned char cvOID_pbeWithMD5AndCAST5_CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x42, 0x0C};
//1.2.840.113533.7.66.13		Nortel Secure Networks alg (1 2 840 113533 7 66) passwordBasedMac 
static const unsigned char cvOID_passwordBasedMac [] = {  0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x42, 0x0D};
//1.2.840.113
static const unsigned char cvOID_entrustUser [] = {  0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x43, 0x0C};
//1.2.840.113533.7.68.0		Nortel Secure Networks at (1 2 840 113533 7 68) entrustCAInfo 
static const unsigned char cvOID_entrustCAInfo [] = {  0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x44, 0x00};
//1.2.840.113533.7.68.10		Nortel Secure Networks at (1 2 840 113533 7 68) attributeCertificate 
static const unsigned char cvOID_attributeCertificate [] = {  0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x44, 0x0A};
//1.2.840.113549.1.1.1		PKCS #1 rsaEncryption 
static const unsigned char cvOID_rsaEncryption [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01};
//1.2.840.113549.1.1.2		PKCS #1 md2withRSAEncryption 
static const unsigned char cvOID_md2withRSAEncryption [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x02};
//1.2.840.113549.1.1.3		PKCS #1 md4withRSAEncryption 
static const unsigned char cvOID_md4withRSAEncryption [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x03};
//1.2.840.113549.1.1.4		PKCS #1 md5withRSAEncryption 
static const unsigned char cvOID_md5withRSAEncryption [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x04};
//1.2.840.113549.1.1.5		PKCS #1 sha1withRSAEncryption 
static const unsigned char cvOID_sha1withRSAEncryption [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05};
//1.2.840.113549.1.1.6		PKCS #1.  This OID may also be assigned as ripemd160WithRSAEncryption rsaOAEPEncryptionSET 
static const unsigned char cvOID_rsaOAEPEncryptionSET [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x06};
//1.2.840.113549.1.1.8		PKCS #1. id-mgf1 (0x2A864886F70D010108)
static const unsigned char cvOID_mgf1 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x08};
//1.2.840.113549.1.1.10		PKCS #1. id-RSASSA-PSS (0x2A864886F70D01010A)
static const unsigned char cvOID_rsaSSA_PSS [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x0A};
//1.2.840.113549.1.2		Obsolete BSAFE OID bsafeRsaEncr 
static const unsigned char cvOID_bsafeRsaEncr [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01};
//1.2.840.113549.1.3.1		PKCS #3 dhKeyAgreement 
static const unsigned char cvOID_dhKeyAgreement [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x03, 0x01};
//1.2.840.113549.1.5.1		PKCS #5 pbeWithMD2AndDES-CBC 
static const unsigned char cvOID_pbeWithMD2AndDES_CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x01};
//1.2.840.113549.1.5.3		PKCS #5 pbeWithMD5AndDES-CBC 
static const unsigned char cvOID_pbeWithMD5AndDES_CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x03};
//1.2.840.113549.1.5.4		PKCS #5 pbeWithMD2AndRC2-CBC 
static const unsigned char cvOID_pbeWithMD2AndRC2_CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x04};
//1.2.840.113549.1.5.6		PKCS #5 pbeWithMD5AndRC2-CBC 
static const unsigned char cvOID_pbeWithMD5AndRC2_CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x06};
//1.2.840.113549.1.5.9		PKCS #5, used in BSAFE only pbeWithMD5AndXOR 
static const unsigned char cvOID_pbeWithMD5AndXOR [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x09};
//1.2.840.113549.1.5.10		PKCS #5 pbeWithSHAAndDES-CBC 
static const unsigned char cvOID_pbeWithSHAAndDES_CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x0A};
//1.2.840.113549.1.5.12		PKCS #5 v2.0 id-PBKDF2 
static const unsigned char cvOID_id_PBKDF2 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x0C};
//1.2.840.113549.1.5.13		PKCS #5 v2.0 id-PBES2 
static const unsigned char cvOID_id_PBES2 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x0D};
//1.2.840.113549.1.5.14		PKCS #5 v2.0 id-PBMAC1 
static const unsigned char cvOID_id_PBMAC1 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x0E};
//1.2.840.113549.1.7.1		PKCS #7 data 
static const unsigned char cvOID_data [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x01};
//1.2.840.113549.1.7.2		PKCS #7 signedData 
static const unsigned char cvOID_signedData [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x02};
//1.2.840.113549.1.7.3		PKCS #7 envelopedData 
static const unsigned char cvOID_envelopedData [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x03};
//1.2.840.113549.1.7.4		PKCS #7 signedAndEnvelopedData 
static const unsigned char cvOID_signedAndEnvelopedData [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x04};
//1.2.840.113549.1.7.5		PKCS #7 digestedData 
static const unsigned char cvOID_digestedData [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x05};
//1.2.840.113549.1.7.6		PKCS #7 encryptedData 
static const unsigned char cvOID_encryptedData [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x06};
//1.2.840.113549.1.7.7		PKCS #7 experimental dataWithAttributes 
static const unsigned char cvOID_dataWithAttributes [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x07};
//1.2.840.113549.1.7.8		PKCS #7 experimental encryptedPrivateKeyInfo 
static const unsigned char cvOID_encryptedPrivateKeyInfo [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x08};
//1.2.840.113549.1.9.1		PKCS #9 (1 2 840 113549 1 9).  Deprecated, use an altName extension instead emailAddress 
static const unsigned char cvOID_emailAddress_PKCS9 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x01};
//1.2.840.113549.1.9.2		PKCS #9 (1 2 840 113549 1 9) unstructuredName 
static const unsigned char cvOID_unstructuredName [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x02};
//1.2.840.113549.1.9.3		PKCS #9 (1 2 840 113549 1 9) contentType 
static const unsigned char cvOID_contentType [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x03};
//1.2.840.113549.1.9.4		PKCS #9 (1 2 840 113549 1 9) messageDigest 
static const unsigned char cvOID_messageDigest [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x04};
//1.2.840.113549.1.9.5		PKCS #9 (1 2 840 113549 1 9) signingTime 
static const unsigned char cvOID_signingTime [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x05};
//1.2.840.113549.1.9.6		PKCS #9 (1 2 840 113549 1 9) countersignature 
static const unsigned char cvOID_countersignature_PKCS9 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x06};
//1.2.840.113549.1.9.7		PKCS #9 (1 2 840 113549 1 9) challengePassword 
static const unsigned char cvOID_challengePassword [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x07};
//1.2.840.113549.1.9.8		PKCS #9 (1 2 840 113549 1 9) unstructuredAddress 
static const unsigned char cvOID_unstructuredAddress [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x08};
//1.2.840.113549.1.9.9		PKCS #9 (1 2 840 113549 1 9) extendedCertificateAttributes 
static const unsigned char cvOID_extendedCertificateAttributes [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x09};
//1.2.840.113549.1.9.10		PKCS #9 (1 2 840 113549 1 9) experimental issuerAndSerialNumber 
static const unsigned char cvOID_issuerAndSerialNumber [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0A};
//1.2.840.113549.1.9.11		PKCS #9 (1 2 840 113549 1 9) experimental passwordCheck 
static const unsigned char cvOID_passwordCheck [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0B};
//1.2.840.113549.1.9.12		PKCS #9 (1 2 840 113549 1 9) experimental publicKey 
static const unsigned char cvOID_publicKey [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0C};
//1.2.840.113549.1.9.13		PKCS #9 (1 2 840 113549 1 9) experimental signingDescription 
static const unsigned char cvOID_signingDescription [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0D};
//1.2.840.113549.1.9.14		PKCS #9 (1 2 840 113549 1 9) experimental extensionReq 
static const unsigned char cvOID_extensionReq [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0E};
//1.2.840.113549.1.9.15		PKCS #9 (1 2 840 113549 1 9).  This OID was formerly assigned as symmetricCapabilities, then reassigned as SMIMECapabilities, then renamed to the current name sMIMECapabilities 
static const unsigned char cvOID_sMIMECapabilities [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F};
//1.2.840.113549.1.9.15.1		sMIMECapabilities (1 2 840 113549 1 9 15) preferSignedData 
static const unsigned char cvOID_preferSignedData [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F, 0x01};
//1.2.840.113549.1.9.15.2		sMIMECapabilities (1 2 840 113549 1 9 15) canNotDecryptAny 
static const unsigned char cvOID_canNotDecryptAny [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F, 0x02};
//1.2.840.113549.1.9.15.3		sMIMECapabilities (1 2 840 113549 1 9 15).  Deprecated, use (1 2 840 113549 1 9 16 2 1) instead receiptRequest 
static const unsigned char cvOID_receiptRequest [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F, 0x03};
//1.2.840.113549.1.9.15.4		sMIMECapabilities (1 2 840 113549 1 9 15).  Deprecated, use (1 2 840 113549 1 9 16 1 1) instead receipt 
static const unsigned char cvOID_receipt [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F, 0x04};
//1.2.840.113549.1.9.15.5		sMIMECapabilities (1 2 840 113549 1 9 15).  Deprecated, use (1 2 840 113549 1 9 16 2 4) instead contentHints 
static const unsigned char cvOID_contentHints [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F, 0x05};
//1.2.840.113549.1.9.15.6		sMIMECapabilities (1 2 840 113549 1 9 15).  Deprecated, use (1 2 840 113549 1 9 16 2 3) instead mlExpansionHistory 
static const unsigned char cvOID_mlExpansionHistory [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F, 0x06};
//1.2.840.113549.1.9.16		PKCS #9 (1 2 840 113549 1 9) id-sMIME 
static const unsigned char cvOID_id_sMIME [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10};
//1.2.840.113549.1.9.16.0		id-sMIME (1 2 840 113549 1 9 16) id-mod 
static const unsigned char cvOID_id_mod [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x00};
//1.2.840.113549.1.9.16.0.1		S/MIME Modules (1 2 840 113549 1 9 16 0) id-mod-cms 
static const unsigned char cvOID_id_mod_cms [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x00, 0x01};
//1.2.840.113549.1.9.16.0.2		S/MIME Modules (1 2 840 113549 1 9 16 0) id-mod-ess 
static const unsigned char cvOID_id_mod_ess [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x00, 0x02};
//1.2.840.113549.1.9.16.1		id-sMIME (1 2 840 113549 1 9 16) id-ct 
static const unsigned char cvOID_id_ct [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x01};
//1.2.840.113549.1.9.16.1.1		S/MIME Content Types (1 2 840 113549 1 9 16 1) id-ct-receipt 
static const unsigned char cvOID_id_ct_receipt [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x01, 0x01};
//1.2.840.113549.1.9.16.1.2		S/MIME Content Types (1 2 840 113549 1 9 16 1) id-ct-authData 
static const unsigned char cvOID_id_ct_authData [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x01, 0x02};
//1.2.840.113549.1.9.16.1.3		S/MIME Content Types (1 2 840 113549 1 9 16 1) id-ct-compressedData 
static const unsigned char cvOID_id_ct_compressedData [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x01, 0x03};
//1.2.840.113549.1.9.16.2		id-sMIME (1 2 840 113549 1 9 16) id-aa 
static const unsigned char cvOID_id_aa [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02};
//1.2.840.113549.1.9.16.2.1		S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-receiptRequest 
static const unsigned char cvOID_id_aa_receiptRequest [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x01};
//1.2.840.113549.1.9.16.2.2		S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-securityLabel 
static const unsigned char cvOID_id_aa_securityLabel [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x02};
//1.2.840.113549.1.9.16.2.3		S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-mlExpandHistory 
static const unsigned char cvOID_id_aa_mlExpandHistory [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x03};
//1.2.840.113549.1.9.16.2.4		S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-contentHint 
static const unsigned char cvOID_id_aa_contentHint [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x04};
//1.2.840.113549.1.9.16.2.5		S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-msgSigDigest 
static const unsigned char cvOID_id_aa_msgSigDigest [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x05};
//1.2.840.113549.1.9.16.2.7		S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-contentIdentifier 
static const unsigned char cvOID_id_aa_contentIdentifier [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x07};
//1.2.840.113549.1.9.16.2.8		S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-macValue 
static const unsigned char cvOID_id_aa_macValue [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x08};
//1.2.840.113549.1.9.16.2.9		S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-equivalentLabels 
static const unsigned char cvOID_id_aa_equivalentLabels [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x09};
//1.2.840.113549.1.9.16.2.10		S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-contentReference 
static const unsigned char cvOID_id_aa_contentReference [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x0A};
//1.2.840.113549.1.9.16.3.5		S/MIME Algorithms (1 2 840 113549 1 9 16 3) id-alg-ESDH 
static const unsigned char cvOID_id_alg_ESDH [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x03, 0x05};
//1.2.840.113549.1.9.16.3.6		S/MIME Algorithms (1 2 840 113549 1 9 16 3) id-alg-CMS3DESwrap 
static const unsigned char cvOID_id_alg_CMS3DESwrap [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x03, 0x06};
//1.2.840.113549.1.9.16.3.7		S/MIME Algorithms (1 2 840 113549 1 9 16 3) id-alg-CMSRC2wrap 
static const unsigned char cvOID_id_alg_CMSRC2wrap [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x03, 0x07};
//1.2.840.113549.1.9.16.3.8		S/MIME Algorithms (1 2 840 113549 1 9 16 3) id-alg-zlib 
static const unsigned char cvOID_id_alg_zlib [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x03, 0x08};
//1.2.840.113549.1.9.20		PKCS #9 (1 2 840 113549 1 9) friendlyName (for PKCS #12) 
static const unsigned char cvOID_friendlyName [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x14};
//1.2.840.113549.1.9.21		PKCS #9 (1 2 840 113549 1 9) localKeyID (for PKCS #12) 
static const unsigned char cvOID_localKeyID[] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x15};
//1.2.840.113549.1.9.22		PKCS #9 (1 2 840 113549 1 9) certTypes (for PKCS #12) 
static const unsigned char cvOID_certTypes[] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x16};
//1.2.840.113549.1.9.22.1		PKCS #9 (1 2 840 113549 1 9) x509Certificate (for PKCS #12) 
static const unsigned char cvOID_x509Certificate[] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x16, 0x01};
//1.2.840.113549.1.9.22.2		PKCS #9 (1 2 840 113549 1 9) sdsiCertificate (for PKCS #12) 
static const unsigned char cvOID_sdsiCertificate [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x16, 0x02};
//1.2.840.113549.1.9.23		PKCS #9 (1 2 840 113549 1 9) crlTypes (for PKCS #12) 
static const unsigned char cvOID_crlTypes[] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x17};
//1.2.840.113549.1.9.23.1		PKCS #9 (1 2 840 113549 1 9) x509Crl (for PKCS #12) 
static const unsigned char cvOID_x509Crl[] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x17, 0x01};
//1.2.840.113549.1.12.1		This OID was formerly assigned as PKCS #12 modeID pkcs-12-PbeIds 
static const unsigned char cvOID_pkcs_12_PbeIds [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01};
//1.2.840.113549.1.12.1.1		PKCS #12 PbeIds (1 2 840 113549 1 12 1). This OID was formerly assigned as pkcs-12-OfflineTransportMode pbeWithSHAAnd128BitRC4 
static const unsigned char cvOID_pbeWithSHAAnd128BitRC4 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01, 0x01};
//1.2.840.113549.1.12.1.2		PKCS #12 PbeIds (1 2 840 113549 1 12 2). This OID was formerly assigned as pkcs-12-OnlineTransportMode pbeWithSHAAnd40BitRC4 
static const unsigned char cvOID_pbeWithSHAAnd40BitRC4 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01, 0x02};
//1.2.840.113549.1.12.1.3		PKCS #12 PbeIds (1 2 840 113549 1 12 3) pbeWithSHAAnd3-KeyTripleDES-CBC 
static const unsigned char cvOID_pbeWithSHAAnd3_KeyTripleDES_CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01, 0x03};
//1.2.840.113549.1.12.1.4		PKCS #12 PbeIds (1 2 840 113549 1 12 3) pbeWithSHAAnd2-KeyTripleDES-CBC 
static const unsigned char cvOID_pbeWithSHAAnd2_KeyTripleDES_CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01, 0x04};
//1.2.840.113549.1.12.1.5		PKCS #12 PbeIds (1 2 840 113549 1 12 3) pbeWithSHAAnd128BitRC2-CBC 
static const unsigned char cvOID_pbeWithSHAAnd128BitRC2_CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01, 0x05};
//1.2.840.113549.1.12.1.6		PKCS #12 PbeIds (1 2 840 113549 1 12 3) pbeWithSHAAnd40BitRC2-CBC 
static const unsigned char cvOID_pbeWithSHAAnd40BitRC2_CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01, 0x06};
//1.2.840.113549.1.12.2		Deprecated pkcs-12-ESPVKID 
static const unsigned char cvOID_pkcs_12_ESPVKID [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x02};
//1.2.840.113549.1.12.2.1		PKCS #12 ESPVKID (1 2 840 113549 1 12 2). Deprecated, use (1 2 840 113549 1 12 3 5) instead pkcs-12-PKCS8KeyShrouding 
static const unsigned char cvOID_pkcs_12_PKCS8KeyShrouding [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x02, 0x01};
//1.2.840.113549.1.12.3.1		PKCS #12 BagIds (1 2 840 113549 1 12 3) pkcs-12-keyBagId 
static const unsigned char cvOID_pkcs_12_keyBagId [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x03, 0x01};
//1.2.840.113549.1.12.3.2		PKCS #12 BagIds (1 2 840 113549 1 12 3) pkcs-12-certAndCRLBagId 
static const unsigned char cvOID_pkcs_12_certAndCRLBagId [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x03, 0x02};
//1.2.840.113549.1.12.3.3		PKCS #12 BagIds (1 2 840 113549 1 12 3) pkcs-12-secretBagId 
static const unsigned char cvOID_pkcs_12_secretBagId [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x03, 0x03};
//1.2.840.113549.1.12.3.4		PKCS #12 BagIds (1 2 840 113549 1 12 3) pkcs-12-safeContentsId 
static const unsigned char cvOID_pkcs_12_safeContentsId [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x03, 0x04};
//1.2.840.113549.1.12.3.5		PKCS #12 BagIds (1 2 840 113549 1 12 3) pkcs-12-pkcs-8ShroudedKeyBagId 
static const unsigned char cvOID_pkcs_12_pkcs_8ShroudedKeyBagId [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x03, 0x05};
//1.2.840.113549.1.12.4		Deprecated pkcs-12-CertBagID 
static const unsigned char cvOID_pkcs_12_CertBagID [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x04};
//1.2.840.113549.1.12.4.1		PKCS #12 CertBagID (1 2 840 113549 1 12 4).  This OID was formerly assigned as pkcs-12-X509CertCRLBag pkcs-12-X509CertCRLBagID 
static const unsigned char cvOID_pkcs_12_X509CertCRLBagID [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x04, 0x01};
//1.2.840.113549.1.12.4.2		PKCS #12 CertBagID (1 2 840 113549 1 12 4).  This OID was formerly assigned as pkcs-12-SDSICertBag pkcs-12-SDSICertBagID 
static const unsigned char cvOID_pkcs_12_SDSICertBagID [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x04, 0x02};
//1.2.840.113549.1.12.5.1		PKCS #12 OID (1 2 840 113549 1 12 5).  Deprecated, use the partially compatible (1 2 840 113549 1 12 1) OIDs instead pkcs-12-PBEID 
static const unsigned char cvOID_pkcs_12_PBEID [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01};
//1.2.840.113549.1.12.5.1.1		PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use (1 2 840 113549 1 12 1 1) instead pkcs-12-PBEWithSha1And128BitRC4 
static const unsigned char cvOID_pkcs_12_PBEWithSha1And128BitRC4 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x01};
//1.2.840.113549.1.12.5.1.2		PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use (1 2 840 113549 1 12 1 2) instead pkcs-12-PBEWithSha1And40BitRC4 
static const unsigned char cvOID_pkcs_12_PBEWithSha1And40BitRC4 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x02};
//1.2.840.113549.1.12.5.1.3		PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use the incompatible but similar (1 2 840 113549 1 12 1 3) or (1 2 840 113549 1 12 1 4) instead pkcs-12-PBEWithSha1AndTripleDESCBC 
static const unsigned char cvOID_pkcs_12_PBEWithSha1AndTripleDESCBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x03};
//1.2.840.113549.1.12.5.1.4		PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use (1 2 840 113549 1 12 1 5) instead pkcs-12-PBEWithSha1And128BitRC2CBC 
static const unsigned char cvOID_pkcs_12_PBEWithSha1And128BitRC2CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x04};
//1.2.840.113549.1.12.5.1.5		PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use (1 2 840 113549 1 12 1 6) instead pkcs-12-PBEWithSha1And40BitRC2CBC 
static const unsigned char cvOID_pkcs_12_PBEWithSha1And40BitRC2CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x05};
//1.2.840.113549.1.12.5.1.6		PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use the incompatible but similar (1 2 840 113549 1 12 1 1) or (1 2 840 113549 1 12 1 2) instead pkcs-12-PBEWithSha1AndRC4 
static const unsigned char cvOID_pkcs_12_PBEWithSha1AndRC4 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x06};
//1.2.840.113549.1.12.5.1.7		PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use the incompatible but similar (1 2 840 113549 1 12 1 5) or (1 2 840 113549 1 12 1 6) instead pkcs-12-PBEWithSha1AndRC2CBC 
static const unsigned char cvOID_pkcs_12_PBEWithSha1AndRC2CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x07};
//1.2.840.113549.1.12.5.2.1		PKCS #12 OID EnvelopingID (1 2 840 113549 1 12 5 2).  Deprecated, use the conventional PKCS #1 OIDs instead pkcs-12-RSAEncryptionWith128BitRC4 
static const unsigned char cvOID_pkcs_12_RSAEncryptionWith128BitRC4 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x02, 0x01};
//1.2.840.113549.1.12.5.2.2		PKCS #12 OID EnvelopingID (1 2 840 113549 1 12 5 2).  Deprecated, use the conventional PKCS #1 OIDs instead pkcs-12-RSAEncryptionWith40BitRC4 
static const unsigned char cvOID_pkcs_12_RSAEncryptionWith40BitRC4 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x02, 0x02};
//1.2.840.113549.1.12.5.2.3		PKCS #12 OID EnvelopingID (1 2 840 113549 1 12 5 2).  Deprecated, use the conventional PKCS #1 OIDs instead pkcs-12-RSAEncryptionWithTripleDES 
static const unsigned char cvOID_pkcs_12_RSAEncryptionWithTripleDES [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x02, 0x03};
//1.2.840.113549.1.12.5.3.1		PKCS #12 OID SignatureID (1 2 840 113549 1 12 5 3).  Deprecated, use the conventional PKCS #1 OIDs instead pkcs-12-RSASignatureWithSHA1Digest 
static const unsigned char cvOID_pkcs_12_RSASignatureWithSHA1Digest [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x03, 0x01};
//1.2.840.113549.1.12.10.1.1		PKCS #12 BagIds (1 2 840 113549 1 12 10 1) pkcs-12-keyBag 
static const unsigned char cvOID_pkcs_12_keyBag [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x0A, 0x01, 0x01};
//1.2.840.113549.1.12.10.1.2		PKCS #12 BagIds (1 2 840 113549 1 12 10 1) pkcs-12-pkcs-8ShroudedKeyBag 
static const unsigned char cvOID_pkcs_12_pkcs_8ShroudedKeyBag [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x0A, 0x01, 0x02};
//1.2.840.113549.1.12.10.1.3		PKCS #12 BagIds (1 2 840 113549 1 12 10 1) pkcs-12-certBag 
static const unsigned char cvOID_pkcs_12_certBag [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x0A, 0x01, 0x03};
//1.2.840.113549.1.12.10.1.4		PKCS #12 BagIds (1 2 840 113549 1 12 10 1) pkcs-12-crlBag 
static const unsigned char cvOID_pkcs_12_crlBag [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x0A, 0x01, 0x04};
//1.2.840.113549.1.12.10.1.5		PKCS #12 BagIds (1 2 840 113549 1 12 10 1) pkcs-12-secretBag 
static const unsigned char cvOID_pkcs_12_secretBag [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x0A, 0x01, 0x05};
//1.2.840.113549.1.12.10.1.6		PKCS #12 BagIds (1 2 840 113549 1 12 10 1) pkcs-12-safeContentsBag 
static const unsigned char cvOID_pkcs_12_safeContentsBag [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x0A, 0x01, 0x06};
//1.2.840.113549.2.2		RSADSI digestAlgorithm (1 2 840 113549 2) md2 
static const unsigned char cvOID_md2 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x02, 0x02};
//1.2.840.113549.2.4		RSADSI digestAlgorithm (1 2 840 113549 2) md4 
static const unsigned char cvOID_md4 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x02, 0x04};
//1.2.840.113549.2.5		RSADSI digestAlgorithm (1 2 840 113549 2) md5 
static const unsigned char cvOID_md5 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x02, 0x05};
//1.2.840.113549.3.2		RSADSI encryptionAlgorithm (1 2 840 113549 3) rc2CBC 
static const unsigned char cvOID_rc2CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x02};
//1.2.840.113549.3.3		RSADSI encryptionAlgorithm (1 2 840 113549 3) rc2ECB 
static const unsigned char cvOID_rc2ECB [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x03};
//1.2.840.113549.3.4		RSADSI encryptionAlgorithm (1 2 840 113549 3) rc4 
static const unsigned char cvOID_rc4 [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x04};
//1.2.840.113549.3.5		RSADSI encryptionAlgorithm (1 2 840 113549 3) rc4WithMAC 
static const unsigned char cvOID_rc4WithMAC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x05};
//1.2.840.113549.3.6		RSADSI encryptionAlgorithm (1 2 840 113549 3) desx-CBC 
static const unsigned char cvOID_desx_CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x06};
//1.2.840.113549.3.7		RSADSI encryptionAlgorithm (1 2 840 113549 3) des-EDE3-CBC 
static const unsigned char cvOID_des_EDE3_CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x07};
//1.2.840.113549.3.8		RSADSI encryptionAlgorithm (1 2 840 113549 3) rc5CBC 
static const unsigned char cvOID_rc5CBC [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x08};
//1.2.840.113549.3.9		RSADSI encryptionAlgorithm (1 2 840 113549 3) rc5-CBCPad 
static const unsigned char cvOID_rc5_CBCPad [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x09};
//1.2.840.113549.3.10		RSADSI encryptionAlgorithm (1 2 840 113549 3).  Formerly called CDMFCBCPad desCDMF 
static const unsigned char cvOID_desCDMF [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x0A};
//1.3.6.1.4.1.188.7.1.1		Ascom Systech ascom 
static const unsigned char cvOID_ascom [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x81, 0x3C, 0x07, 0x01, 0x01};
//1.3.6.1.4.1.188.7.1.1.1		Ascom Systech ideaECB 
static const unsigned char cvOID_ideaECB [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x81, 0x3C, 0x07, 0x01, 0x01, 0x01};
//1.3.6.1.4.1.188.7.1.1.2		Ascom Systech ideaCBC 
static const unsigned char cvOID_ideaCBC [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x81, 0x3C, 0x07, 0x01, 0x01, 0x02};
//1.3.6.1.4.1.188.7.1.1.3		Ascom Systech ideaCFB 
static const unsigned char cvOID_ideaCFB [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x81, 0x3C, 0x07, 0x01, 0x01, 0x03};
//1.3.6.1.4.1.188.7.1.1.4		Ascom Systech ideaOFB 
static const unsigned char cvOID_ideaOFB [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x81, 0x3C, 0x07, 0x01, 0x01, 0x04};
//1.2.840.113556.4.3		Microsoft microsoftExcel 
static const unsigned char cvOID_microsoftExcel [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x14, 0x04, 0x03};
//1.2.840.113556.4.4		Microsoft titledWithOID 
static const unsigned char cvOID_titledWithOID [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x14, 0x04, 0x04};
//1.2.840.113556.4.5		Microsoft microsoftPowerPoint 
static const unsigned char cvOID_microsoftPowerPoint [] = {  0x2A, 0x86, 0x48, 0x86, 0xF7, 0x14, 0x04, 0x05};
//1.3.6.1.4.1.311.2.1.4		Microsoft code signing spcIndirectDataContext 
static const unsigned char cvOID_spcIndirectDataContext [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x04};
//1.3.6.1.4.1.311.2.1.10		Microsoft code signing.  Also known as policyLink spcAgencyInfo 
static const unsigned char cvOID_spcAgencyInfo [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x0A};
//1.3.6.1.4.1.311.2.1.11		Microsoft code signing spcStatementType 
static const unsigned char cvOID_spcStatementType [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x0B};
//1.3.6.1.4.1.311.2.1.12		Microsoft code signing spcSpOpusInfo 
static const unsigned char cvOID_spcSpOpusInfo [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x0C};
//1.3.6.1.4.1.311.2.1.14		Microsoft certReqExtensions 
static const unsigned char cvOID_certReqExtensions [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x0E};
//1.3.6.1.4.1.311.2.1.15		Microsoft code signing spcPelmageData 
static const unsigned char cvOID_spcPelmageData [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x0F};
//1.3.6.1.4.1.311.2.1.20		Microsoft code signing.  Also known as "glue extension" spcLink (type 1) 
static const unsigned char cvOID_spcLink_1[] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x14};
//1.3.6.1.4.1.311.2.1.21		Microsoft individualCodeSigning 
static const unsigned char cvOID_individualCodeSigning [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x15};
//1.3.6.1.4.1.311.2.1.22		Microsoft commercialCodeSigning 
static const unsigned char cvOID_commercialCodeSigning [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x16};
//1.3.6.1.4.1.311.2.1.25		Microsoft code signing.  Also known as "glue extension" spcLink (type 2) 
static const unsigned char cvOID_spcLink_2[] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x19};
//1.3.6.1.4.1.311.2.1.26		Microsoft code signing spcMinimalCriteriaInfo 
static const unsigned char cvOID_spcMinimalCriteriaInfo [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x1A};
//1.3.6.1.4.1.311.2.1.27		Microsoft code signing spcFinancialCriteriaInfo 
static const unsigned char cvOID_spcFinancialCriteriaInfo [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x1B};
//1.3.6.1.4.1.311.2.1.28		Microsoft code signing.  Also known as "glue extension" spcLink (type 3) 
static const unsigned char cvOID_spcLink_3[] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x1C};
//1.3.6.1.4.1.311.3.2.1		Microsoft code signing timestampCountersignature 
static const unsigned char cvOID_timestampCountersignature [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x03, 0x02, 0x01};
//1.3.6.1.4.1.311.10.1		Microsoft PKCS #7 contentType certTrustList 
static const unsigned char cvOID_certTrustList [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x01};
//1.3.6.1.4.1.311.10.2		Microsoft nextUpdateLocation 
static const unsigned char cvOID_nextUpdateLocation [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x02};
//1.3.6.1.4.1.311.10.3.1		Microsoft enhanced key usage certTrustListSigning 
static const unsigned char cvOID_certTrustListSigning [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x03, 0x01};
//1.3.6.1.4.1.311.10.3.2		Microsoft enhanced key usage timeStampSigning 
static const unsigned char cvOID_timeStampSigning [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x03, 0x02};
//1.3.6.1.4.1.311.10.3.3		Microsoft enhanced key usage serverGatedCrypto 
static const unsigned char cvOID_serverGatedCrypto [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x03, 0x03};
//1.3.6.1.4.1.311.10.3.4		Microsoft enhanced key usage encryptedFileSystem 
static const unsigned char cvOID_encryptedFileSystem [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x03, 0x04};
//1.3.6.1.4.1.311.10.4.1		Microsoft attribute yesnoTrustAttr 
static const unsigned char cvOID_yesnoTrustAttr [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x04, 0x01};
//1.3.6.1.4.1.311.16.4		Microsoft S/MIME cert attribute microsoftEncryptionCert 
static const unsigned char cvOID_microsoftEncryptionCert [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x10, 0x04};
//1.3.6.1.4.1.311.20.2.2		Microsoft enhanced key usage smartcardLogon
static const unsigned char cvOID_smartcardLogon [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x14, 0x02, 0x02};
//1.3.6.1.4.1.311.21.1		Microsoft attribute cAKeyCertIndexPair 
static const unsigned char cvOID_cAKeyCertIndexPair [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x15, 0x01};
//1.3.6.1.4.1.311.13.2.2		Microsoft attribute Unknown MS CryptoAPI-related extension 
static const unsigned char cvOID_Unknown_MS_CryptoAPI_related_extension [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0D, 0x02, 0x02};
//1.3.6.1.4.1.311.16.4		Microsoft attribute microsoftRecipientInfo 
static const unsigned char cvOID_microsoftRecipientInfo [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x10, 0x04};
//1.3.6.1.4.1.2428.10.1.1		UNINETT PCA UNINETT policyIdentifier 
static const unsigned char cvOID_UNINETT_policyIdentifier [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x92, 0x7C, 0x0A, 0x01, 0x01};
//1.3.6.1.4.1.2712.10		ICE-TEL CA ICE-TEL policyIdentifier 
static const unsigned char cvOID_ICE_TEL_policyIdentifier [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x95, 0x18, 0x0A};
//1.3.6.1.4.1.2786.1.1.1		ICE-TEL CA policy ICE-TEL Italian policyIdentifier 
static const unsigned char cvOID_ICE_TEL_Italian_policyIdentifier [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x95, 0x62, 0x01, 0x01, 0x01};
//1.3.6.1.4.1.3029.1.1		cryptlib encryption algorithm blowfishECB 
static const unsigned char cvOID_blowfishECB [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x01, 0x01};
//1.3.6.1.4.1.3029.1.2		cryptlib encr
static const unsigned char cvOID_blowfishCBC [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x01, 0x02};
//1.3.6.1.4.1.3029.1.3		cryptlib encryption algorithm blowfishCFB 
static const unsigned char cvOID_blowfishCFB [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x01, 0x03};
//1.3.6.1.4.1.3029.1.4		cryptlib encryption algorithm blowfishOFB 
static const unsigned char cvOID_blowfishOFB [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x01, 0x04};
//1.3.6.1.4.1.3029.3.1		cryptlib public-key algorithm elgamal 
static const unsigned char cvOID_elgamal [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x03, 0x01};
//1.3.6.1.4.1.3029.3.1.1		cryptlib public-key algorithm elgamalWithSHA-1 
static const unsigned char cvOID_elgamalWithSHA_1 [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x03, 0x01, 0x01};
//1.3.6.1.4.1.3029.3.1.2		cryptlib public-key algorithm elgamalWithRIPEMD-160 
static const unsigned char cvOID_elgamalWithRIPEMD_160 [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x03, 0x01, 0x02};
//1.3.6.1.4.1.3029.32.1		cryptlib cryptlibPrivateKey 
static const unsigned char cvOID_cryptlibPrivateKey [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x20, 0x01};
//1.3.6.1.4.1.3029.42.11172.1		cryptlib special MPEG-of-cat OID mpeg-1 
static const unsigned char cvOID_mpeg_1 [] = {  0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x2A, 0xD7, 0x24, 0x01};
//1.3.6.1.5.5.7.1		PKIX privateExtension 
static const unsigned char cvOID_privateExtension [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x01};
//1.3.6.1.5.5.7.1.1		PKIX private extension authorityInfoAccess 
static const unsigned char cvOID_authorityInfoAccess [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x01, 0x01};

//ame
//1.3.6.1.5.5.7.1.11		PKIX private extension subjectInfoAccess
static const unsigned char cvOID_subjectInfoAccess [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x01, 0x0a};

//1.3.6.1.5.5.7.2		PKIX policyQualifierIds 
static const unsigned char cvOID_policyQualifierIds [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x02};
//1.3.6.1.5.5.7.2.1		PKIX policy qualifier cps 
static const unsigned char cvOID_cps [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x02, 0x01};
//1.3.6.1.5.5.7.2.2		PKIX policy qualifier unotice 
static const unsigned char cvOID_unotice [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x02, 0x02};
//1.3.6.1.5.5.7.3		PKIX keyPurpose 
static const unsigned char cvOID_keyPurpose [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03};
//1.3.6.1.5.5.7.3.1		PKIX key purpose serverAuth 
static const unsigned char cvOID_serverAuth [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x01};
//1.3.6.1.5.5.7.3.2		PKIX key purpose clientAuth 
static const unsigned char cvOID_clientAuth [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x02};
//1.3.6.1.5.5.7.3.3		PKIX key purpose codeSigning 
static const unsigned char cvOID_codeSigning [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x03};
//1.3.6.1.5.5.7.3.4		PKIX key purpose emailProtection 
static const unsigned char cvOID_emailProtection [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x04};
//1.3.6.1.5.5.7.3.5		PKIX key purpose ipsecEndSystem 
static const unsigned char cvOID_ipsecEndSystem [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x05};
//1.3.6.1.5.5.7.3.6		PKIX key purpose ipsecTunnel 
static const unsigned char cvOID_ipsecTunnel [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x06};
//1.3.6.1.5.5.7.3.7		PKIX key purpose ipsecUser 
static const unsigned char cvOID_ipsecUser [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x07};
//1.3.6.1.5.5.7.3.8		PKIX key purpose timeStamping 
static const unsigned char cvOID_timeStamping [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x08};
//ame
//1.3.6.1.5.5.7.3.9		PKIX key purpose OCSPSigning 
static const unsigned char cvOID_OCSPSigning [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x09};
//1.3.6.1.5.5.7.4		PKIX cmpInformationTypes 
static const unsigned char cvOID_cmpInformationTypes [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04};
//1.3.6.1.5.5.7.4.1		PKIX CMP information caProtEncCert 
static const unsigned char cvOID_caProtEncCert [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04, 0x01};
//1.3.6.1.5.5.7.4.2		PKIX CMP information signKeyPairTypes 
static const unsigned char cvOID_signKeyPairTypes [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04, 0x02};
//1.3.6.1.5.5.7.4.3		PKIX CMP information encKeyPairTypes 
static const unsigned char cvOID_encKeyPairTypes [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04, 0x03};
//1.3.6.1.5.5.7.4.4		PKIX CMP information preferredSymmAlg 
static const unsigned char cvOID_preferredSymmAlg [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04, 0x04};
//1.3.6.1.5.5.7.4.5		PKIX CMP information caKeyUpdateInfo 
static const unsigned char cvOID_caKeyUpdateInfo [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04, 0x05};
//1.3.6.1.5.5.7.4.6		PKIX CMP information currentCRL 
static const unsigned char cvOID_currentCRL [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04, 0x06};
//1.3.6.1.5.5.7.6.3		PKIX algorithm dh-sig-hmac-sha1 
static const unsigned char cvOID_dh_sig_hmac_sha1 [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x06, 0x03};
//1.3.6.1.5.5.7.6.4		PKIX algorithm dh-pop 
static const unsigned char cvOID_dh_pop [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x06, 0x04};
//1.3.6.1.5.5.7.48.1		PKIX authority info access descriptor ocsp 
static const unsigned char cvOID_ocsp [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x01};
//1.3.6.1.5.5.7.48.2		PKIX authority info access descriptor caIssuers 
static const unsigned char cvOID_caIssuers [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x02};

//ame
//1.3.6.1.5.5.7.48.3		PKIX subject info access descriptor timeStamping
static const unsigned char cvOID_info_timeStamping [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x03};
//1.3.6.1.5.5.7.48.5		PKIX subject info access descriptor caRepository
static const unsigned char cvOID_caRepository [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x05};

//1.3.6.1.5.5.8.1.1		ISAKMP HMAC algorithm HMAC-MD5 
static const unsigned char cvOID_HMAC_MD5 [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x08, 0x01, 0x01};
//1.3.6.1.5.5.8.1.2		ISAKMP HMAC algorithm HMAC-SHA 
static const unsigned char cvOID_HMAC_SHA [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x08, 0x01, 0x02};
//1.3.6.1.5.5.8.1.3		ISAKMP HMAC algorithm HMAC-Tiger 
static const unsigned char cvOID_HMAC_Tiger [] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x08, 0x01, 0x03};
//1.3.6.1.5.5.8.2.2		ipsec_kp_ike_intermediate
static const unsigned char cvOID_iKEIntermediate[] = {  0x2B, 0x06, 0x01, 0x05, 0x05, 0x08, 0x02, 0x02};

//1.3.12.2.1011.7.1		DASS algorithm decEncryptionAlgorithm 
static const unsigned char cvOID_decEncryptionAlgorithm [] = {  0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x01};
//1.3.12.2.1011.7.1.2		DASS encryption algorithm decDEA 
static const unsigned char cvOID_decDEA [] = {  0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x01, 0x02};
//1.3.12.2.1011.7.2		DASS algorithm decHashAlgorithm 
static const unsigned char cvOID_decHashAlgorithm [] = {  0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x02};
//1.3.12.2.1011.7.2.1		DASS hash algorithm decMD2 
static const unsigned char cvOID_decMD2 [] = {  0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x02, 0x01};
//1.3.12.2.1011.7.2.2		DASS hash algorithm decMD4 
static const unsigned char cvOID_decMD4 [] = {  0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x02, 0x02};
//1.3.12.2.1011.7.3		DASS algorithm decSignatureAlgorithm 
static const unsigned char cvOID_decSignatureAlgorithm [] = {  0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x03};
//1.3.12.2.1011.7.3.1		DASS signature algorithm decMD2withRSA 
static const unsigned char cvOID_decMD2withRSA [] = {  0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x03, 0x01};
//1.3.12.2.1011.7.3.2		DASS signature algorithm decMD4withRSA 
static const unsigned char cvOID_decMD4withRSA [] = {  0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x03, 0x02};
//1.3.12.2.1011.7.3.3		DASS signature algorithm decDEAMAC 
static const unsigned char cvOID_decDEAMAC [] = {  0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x03, 0x03};
//1.3.14.2.26.5		Unsure about this OID sha 
static const unsigned char cvOID_sha [] = {  0x2B, 0x0E, 0x02, 0x1A, 0x05};
//1.3.14.3.2.1.1		X.509.  Unsure about this OID rsa 
static const unsigned char cvOID_rsa [] = {  0x2B, 0x0E, 0x03, 0x02, 0x01, 0x01};
//1.3.14.3.2.2		Oddball OIW OID md4WitRSA 
static const unsigned char cvOID_md4WitRSA [] = {  0x2B, 0x0E, 0x03, 0x02, 0x02};
//1.3.14.3.2.3		Oddball OIW OID md5WithRSA 
static const unsigned char cvOID_md5WithRSA [] = {  0x2B, 0x0E, 0x03, 0x02, 0x03};
//1.3.14.3.2.4		Oddball OIW OID md4WithRSAEncryption 
static const unsigned char cvOID_md4WithRSAEncryption [] = {  0x2B, 0x0E, 0x03, 0x02, 0x04};
//1.3.14.3.2.2.1		X.509.  Deprecated sqmod-N 
static const unsigned char cvOID_sqmod_N [] = {  0x2B, 0x0E, 0x03, 0x02, 0x02, 0x01};
//1.3.14.3.2.3.1		X.509.  Deprecated sqmod-NwithRSA 
static const unsigned char cvOID_sqmod_NwithRSA [] = {  0x2B, 0x0E, 0x03, 0x02, 0x03, 0x01};
//1.3.14.3.2.11		ISO 9796-2, also X9.31 Part 1 rsaSignature 
static const unsigned char cvOID_rsaSignature [] = {  0x2B, 0x0E, 0x03, 0x02, 0x0B};
////1.3.14.3.2.12		OIW?, supposedly from an incomplete version of SDN.701 (doesn't match final SDN.701) dsa 
//static const unsigned char cvOID_dsa [] = {  0x2B, 0x0E, 0x03, 0x02, 0x0C};
//1.3.14.3.2.14		Oddball OIW OID using 9796-2 padding rules mdc2WithRSASignature 
static const unsigned char cvOID_mdc2WithRSASignature [] = {  0x2B, 0x0E, 0x03, 0x02, 0x0E};
//1.3.14.3.2.15		Oddball OIW OID using 9796-2 padding rules shaWithRSASignature 
static const unsigned char cvOID_shaWithRSASignature [] = {  0x2B, 0x0E, 0x03, 0x02, 0x0F};
//1.3.14.3.2.16		Oddball OIW OID.  Deprecated, use a plain DH OID instead dhWithCommonModulus 
static const unsigned char cvOID_dhWithCommonModulus [] = {  0x2B, 0x0E, 0x03, 0x02, 0x10};
//1.3.14.3.2.17		Oddball OIW OID.  Mode is ECB desEDE 
static const unsigned char cvOID_desEDE [] = {  0x2B, 0x0E, 0x03, 0x02, 0x11};
////1.3.14.3.2.18		Oddball OIW OID sha 
//static const unsigned char cvOID_sha [] = {  0x2B, 0x0E, 0x03, 0x02, 0x12};
//1.3.14.3.2.19		Oddball OIW OID, DES-based hash, planned for X9.31 Part 2 mdc-2 
static const unsigned char cvOID_mdc_2 [] = {  0x2B, 0x0E, 0x03, 0x02, 0x13};
//1.3.14.3.2.20		Oddball OIW OID.  Deprecated, use a plain DSA OID instead dsaCommon 
static const unsigned char cvOID_dsaCommon [] = {  0x2B, 0x0E, 0x03, 0x02, 0x14};
//1.3.14.3.2.21		Oddball OIW OID.  Deprecated, use a plain dsaWithSHA OID instead dsaCommonWithSHA 
static const unsigned char cvOID_dsaCommonWithSHA [] = {  0x2B, 0x0E, 0x03, 0x02, 0x15};
//1.3.14.3.2.22		Oddball OIW OID rsaKeyTransport 
static const unsigned char cvOID_rsaKeyTransport [] = {  0x2B, 0x0E, 0x03, 0x02, 0x16};
//1.3.14.3.2.23		Oddball OIW OID keyed-hash-seal 
static const unsigned char cvOID_keyed_hash_seal [] = {  0x2B, 0x0E, 0x03, 0x02, 0x17};
//1.3.14.3.2.24		Oddball OIW OID using 9796-2 padding rules md2WithRSASignature 
static const unsigned char cvOID_md2WithRSASignature [] = {  0x2B, 0x0E, 0x03, 0x02, 0x18};
//1.3.14.3.2.25		Oddball OIW OID using 9796-2 padding rules md5WithRSASignature 
static const unsigned char cvOID_md5WithRSASignature [] = {  0x2B, 0x0E, 0x03, 0x02, 0x19};
//1.3.14.3.2.26		OIW sha1 
static const unsigned char cvOID_sha1 [] = {  0x2B, 0x0E, 0x03, 0x02, 0x1A};
//1.3.14.3.2.27		OIW.  This OID may also be assigned as ripemd-160 dsaWithSHA1 
static const unsigned char cvOID_dsaWithSHA1 [] = {  0x2B, 0x0E, 0x03, 0x02, 0x1B};
//1.3.14.3.2.28		OIW dsaWithCommonSHA1 
static const unsigned char cvOID_dsaWithCommonSHA1 [] = {  0x2B, 0x0E, 0x03, 0x02, 0x1C};
//1.3.14.3.2.29		Oddball OIW OID sha-1WithRSAEncryption 
static const unsigned char cvOID_sha_1WithRSAEncryption [] = {  0x2B, 0x0E, 0x03, 0x02, 0x1D};
//1.3.14.3.3.1		Oddball OIW OID simple-strong-auth-mechanism 
static const unsigned char cvOID_simple_strong_auth_mechanism [] = {  0x2B, 0x0E, 0x03, 0x03, 0x01};
//1.3.14.7.2.1.1		Unsure about this OID ElGamal 
static const unsigned char cvOID_ElGamal [] = {  0x2B, 0x0E, 0x07, 0x02, 0x01, 0x01};
//1.3.14.7.2.3.1		Unsure about this OID md2WithRSA 
static const unsigned char cvOID_md2WithRSA [] = {  0x2B, 0x0E, 0x07, 0x02, 0x03, 0x01};
//1.3.14.7.2.3.2		Unsure about this OID md2WithElGamal 
static const unsigned char cvOID_md2WithElGamal [] = {  0x2B, 0x0E, 0x07, 0x02, 0x03, 0x02};
//1.3.36.1		Teletrust document document 
static const unsigned char cvOID_document [] = {  0x2B, 0x24, 0x01};
//1.3.36.1.1		Teletrust document finalVersion 
static const unsigned char cvOID_finalVersion [] = {  0x2B, 0x24, 0x01, 0x01};
//1.3.36.1.2		Teletrust document draft 
static const unsigned char cvOID_draft [] = {  0x2B, 0x24, 0x01, 0x02};
//1.3.36.2		Teletrust sio sio 
static const unsigned char cvOID_sio [] = {  0x2B, 0x24, 0x02};
//1.3.36.2.1		Teletrust sio sedu 
static const unsigned char cvOID_sedu [] = {  0x2B, 0x24, 0x02, 0x01};
//1.3.36.3		Teletrust algorithm algorithm 
static const unsigned char cvOID_algorithm_Teletrust[] = {  0x2B, 0x24, 0x03};
//1.3.36.3.1		Teletrust algorithm encryptionAlgorithm 
static const unsigned char cvOID_encryptionAlgorithm_Teletrust [] = {  0x2B, 0x24, 0x03, 0x01};
//1.3.36.3.1.1		Teletrust encryption algorithm des 
static const unsigned char cvOID_des_Teletrust [] = {  0x2B, 0x24, 0x03, 0x01, 0x01};
//1.3.36.3.1.1.1		Teletrust encryption algorithm desECB_pad 
static const unsigned char cvOID_desECB_pad [] = {  0x2B, 0x24, 0x03, 0x01, 0x01, 0x01};
//1.3.36.3.1.1.1.1		Teletrust encryption algorithm desECB_ISOpad 
static const unsigned char cvOID_desECB_ISOpad [] = {  0x2B, 0x24, 0x03, 0x01, 0x01, 0x01, 0x01};
//1.3.36.3.1.1.2.1		Teletrust encryption algorithm desCBC_pad 
static const unsigned char cvOID_desCBC_pad [] = {  0x2B, 0x24, 0x03, 0x01, 0x01, 0x02, 0x01};
//1.3.36.3.1.1.2.1.1		Teletrust encryption algorithm desCBC_ISOpad 
static const unsigned char cvOID_desCBC_ISOpad [] = {  0x2B, 0x24, 0x03, 0x01, 0x01, 0x02, 0x01, 0x01};
//1.3.36.3.1.3		Teletrust encryption algorithm des_3 
static const unsigned char cvOID_des_3 [] = {  0x2B, 0x24, 0x03, 0x01, 0x03};
//1.3.36.3.1.3.1.1		Teletrust encryption algorithm.  EDE triple DES des_3ECB_pad 
static const unsigned char cvOID_des_3ECB_pad [] = {  0x2B, 0x24, 0x03, 0x01, 0x03, 0x01, 0x01};
//1.3.36.3.1.3.1.1.1		Teletrust encryption algorithm.  EDE triple DES des_3ECB_ISOpad 
static const unsigned char cvOID_des_3ECB_ISOpad [] = {  0x2B, 0x24, 0x03, 0x01, 0x03, 0x01, 0x01, 0x01};
//1.3.36.3.1.3.2.1		Teletrust encryption algorithm.  EDE triple DES des_3CBC_pad 
static const unsigned char cvOID_des_3CBC_pad [] = {  0x2B, 0x24, 0x03, 0x01, 0x03, 0x02, 0x01};
//1.3.36.3.1.3.2.1.1		Teletrust encryption algorithm.  EDE triple DES des_3CBC_ISOpad 
static const unsigned char cvOID_des_3CBC_ISOpad [] = {  0x2B, 0x24, 0x03, 0x01, 0x03, 0x02, 0x01, 0x01};
//1.3.36.3.1.2		Teletrust encryption algorithm idea 
static const unsigned char cvOID_idea_Teletrust [] = {  0x2B, 0x24, 0x03, 0x01, 0x02};
//1.3.36.3.1.2.1		Teletrust encryption algorithm ideaECB 
static const unsigned char cvOID_ideaECB_Teletrust [] = {  0x2B, 0x24, 0x03, 0x01, 0x02, 0x01};
//1.3.36.3.1.2.1.1		Teletrust encryption algorithm ideaECB_pad 
static const unsigned char cvOID_ideaECB_pad [] = {  0x2B, 0x24, 0x03, 0x01, 0x02, 0x01, 0x01};
//1.3.36.3.1.2.1.1.1		Teletrust encryption algorithm ideaECB_ISOpad 
static const unsigned char cvOID_ideaECB_ISOpad [] = {  0x2B, 0x24, 0x03, 0x01, 0x02, 0x01, 0x01, 0x01};
//1.3.36.3.1.2.2		Teletrust encryption algorithm ideaCBC 
static const unsigned char cvOID_ideaCBC_Teletrust [] = {  0x2B, 0x24, 0x03, 0x01, 0x02, 0x02};
//1.3.36.3.1.2.2.1		Teletrust encryption algorithm ideaCBC_pad 
static const unsigned char cvOID_ideaCBC_pad [] = {  0x2B, 0x24, 0x03, 0x01, 0x02, 0x02, 0x01};
//1.3.36.3.1.2.2.1.1		Teletrust encryption algorithm ideaCBC_ISOpad 
static const unsigned char cvOID_ideaCBC_ISOpad [] = {  0x2B, 0x24, 0x03, 0x01, 0x02, 0x02, 0x01, 0x01};
//1.3.36.3.1.2.3		Teletrust encryption algorithm ideaOFB 
static const unsigned char cvOID_ideaOFB_Teletrust [] = {  0x2B, 0x24, 0x03, 0x01, 0x02, 0x03};
//1.3.36.3.1.2.4		Teletrust encryption algorithm ideaCFB 
static const unsigned char cvOID_ideaCFB_Teletrust [] = {  0x2B, 0x24, 0x03, 0x01, 0x02, 0x04};
//1.3.36.3.1.4		Teletrust encryption algorithm rsaEncryption 
static const unsigned char cvOID_rsaEncryption_Teletrust [] = {  0x2B, 0x24, 0x03, 0x01, 0x04};
//1.3.36.3.1.4.512.17		Teletrust encryption algorithm rsaEncryptionWithlmod512expe17 
static const unsigned char cvOID_rsaEncryptionWithlmod512expe17 [] = {  0x2B, 0x24, 0x03, 0x01, 0x04, 0x84, 0x00, 0x11};
//1.3.36.3.1.5		Teletrust encryption algorithm bsi-1 
static const unsigned char cvOID_bsi_1 [] = {  0x2B, 0x24, 0x03, 0x01, 0x05};
//1.3.36.3.1.5.1		Teletrust encryption algorithm bsi_1ECB_pad 
static const unsigned char cvOID_bsi_1ECB_pad [] = {  0x2B, 0x24, 0x03, 0x01, 0x05, 0x01};
//1.3.36.3.1.5.2		Teletrust encryption algorithm bsi_1CBC_pad 
static const unsigned char cvOID_bsi_1CBC_pad [] = {  0x2B, 0x24, 0x03, 0x01, 0x05, 0x02};
//1.3.36.3.1.5.2.1		Teletrust encryption algorithm bsi_1CBC_PEMpad 
static const unsigned char cvOID_bsi_1CBC_PEMpad [] = {  0x2B, 0x24, 0x03, 0x01, 0x05, 0x02, 0x01};
//1.3.36.3.2		Teletrust algorithm hashAlgorithm 
static const unsigned char cvOID_hashAlgorithm [] = {  0x2B, 0x24, 0x03, 0x02};
//1.3.36.3.2.1		Teletrust hash algorithm ripemd160 
static const unsigned char cvOID_ripemd160_Teletrust [] = {  0x2B, 0x24, 0x03, 0x02, 0x01};
//1.3.36.3.2.2		Teletrust hash algorithm ripemd128 
static const unsigned char cvOID_ripemd128_Teletrust [] = {  0x2B, 0x24, 0x03, 0x02, 0x02};
//1.3.36.3.2.3		Teletrust hash algorithm ripemd256 
static const unsigned char cvOID_ripemd256 [] = {  0x2B, 0x24, 0x03, 0x02, 0x03};
//1.3.36.3.2.4		Teletrust hash algorithm mdc2singleLength 
static const unsigned char cvOID_mdc2singleLength [] = {  0x2B, 0x24, 0x03, 0x02, 0x04};
//1.3.36.3.2.5		Teletrust hash algorithm mdc2doubleLength 
static const unsigned char cvOID_mdc2doubleLength [] = {  0x2B, 0x24, 0x03, 0x02, 0x05};
//1.3.36.3.3		Teletrust algorithm signatureAlgorithm 
static const unsigned char cvOID_signatureAlgorithm [] = {  0x2B, 0x24, 0x03, 0x03};
//1.3.36.3.3.1		Teletrust signature algorithm rsaSignature 
static const unsigned char cvOID_rsaSignature_Teletrust [] = {  0x2B, 0x24, 0x03, 0x03, 0x01};
//1.3.36.3.3.1.1		Teletrust signature algorithm rsaSignatureWithsha1 
static const unsigned char cvOID_rsaSignatureWithsha1 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01};
//1.3.36.3.3.1.1.512.2		Teletrust signature algorithm rsaSignatureWithsha1_l512_l2 
static const unsigned char cvOID_rsaSignatureWithsha1_l512_l2 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x84, 0x00, 0x02};
//1.3.36.3.3.1.1.640.2		Teletrust signature algorithm rsaSignatureWithsha1_l640_l2 
static const unsigned char cvOID_rsaSignatureWithsha1_l640_l2 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x85, 0x00, 0x02};
//1.3.36.3.3.1.1.768.2		Teletrust signature algorithm rsaSignatureWithsha1_l768_l2 
static const unsigned char cvOID_rsaSignatureWithsha1_l768_l2 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x86, 0x00, 0x02};
//1.3.36.3.3.1.1.892.2		Teletrust signature algorithm rsaSignatureWithsha1_l896_l2 
static const unsigned char cvOID_rsaSignatureWithsha1_l896_l2 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x87, 0x00, 0x02};
//1.3.36.3.3.1.1.1024.2		Teletrust signature algorithm rsaSignatureWithsha1_l1024_l2 
static const unsigned char cvOID_rsaSignatureWithsha1_l1024_l2 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x88, 0x00, 0x02};
//1.3.36.3.3.1.1.512.3		Teletrust signature algorithm rsaSignatureWithsha1_l512_l3 
static const unsigned char cvOID_rsaSignatureWithsha1_l512_l3 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x84, 0x00, 0x03};
//1.3.36.3.3.1.1.640.3		Teletrust signature algorithm rsaSignatureWithsha1_l640_l3 
static const unsigned char cvOID_rsaSignatureWithsha1_l640_l3 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x85, 0x00, 0x03};
//1.3.36.3.3.1.1.768.3		Teletrust signature algorithm rsaSignatureWithsha1_l768_l3 
static const unsigned char cvOID_rsaSignatureWithsha1_l768_l3 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x86, 0x00, 0x03};
//1.3.36.3.3.1.1.896.3		Teletrust signature algorithm rsaSignatureWithsha1_l896_l3 
static const unsigned char cvOID_rsaSignatureWithsha1_l896_l3 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x87, 0x00, 0x03};
//1.3.36.3.3.1.1.1024.3		Teletrust signature algorithm rsaSignatureWithsha1_l1024_l3 
static const unsigned char cvOID_rsaSignatureWithsha1_l1024_l3 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x88, 0x00, 0x03};
//1.3.36.3.3.1.1.512.5		Teletrust signature algorithm rsaSignatureWithsha1_l512_l5 
static const unsigned char cvOID_rsaSignatureWithsha1_l512_l5 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x84, 0x00, 0x05};
//1.3.36.3.3.1.1.640.5		Teletrust signature algorithm rsaSignatureWithsha1_l640_l5 
static const unsigned char cvOID_rsaSignatureWithsha1_l640_l5 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x85, 0x00, 0x05};
//1.3.36.3.3.1.1.768.5		Teletrust signature algorithm rsaSignatureWithsha1_l768_l5 
static const unsigned char cvOID_rsaSignatureWithsha1_l768_l5 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x86, 0x00, 0x05};
//1.3.36.3.3.1.1.896.5		Teletrust signature algorithm rsaSignatureWithsha1_l896_l5 
static const unsigned char cvOID_rsaSignatureWithsha1_l896_l5 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x87, 0x00, 0x05};
//1.3.36.3.3.1.1.1024.5		Teletrust signature algorithm rsaSignatureWithsha1_l1024_l5 
static const unsigned char cvOID_rsaSignatureWithsha1_l1024_l5 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x88, 0x00, 0x05};
//1.3.36.3.3.1.1.512.9		Teletrust signature algorithm rsaSignatureWithsha1_l512_l9 
static const unsigned char cvOID_rsaSignatureWithsha1_l512_l9 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x84, 0x00, 0x09};
//1.3.36.3.3.1.1.640.9		Teletrust signature algorithm rsaSignatureWithsha1_l640_l9 
static const unsigned char cvOID_rsaSignatureWithsha1_l640_l9 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x85, 0x00, 0x09};
//1.3.36.3.3.1.1.768.9		Teletrust signature algorithm rsaSignatureWithsha1_l768_l9 
static const unsigned char cvOID_rsaSignatureWithsha1_l768_l9 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x86, 0x00, 0x09};
//1.3.36.3.3.1.1.896.9		Teletrust signature algorithm rsaSignatureWithsha1_l896_l9 
static const unsigned char cvOID_rsaSignatureWithsha1_l896_l9 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x87, 0x00, 0x09};
//1.3.36.3.3.1.1.1024.9		Teletrust signature algorithm rsaSignatureWithsha1_l1024_l9 
static const unsigned char cvOID_rsaSignatureWithsha1_l1024_l9 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x88, 0x00, 0x09};
//1.3.36.3.3.1.1.512.11		Teletrust signature algorithm rsaSignatureWithsha1_l512_l11 
static const unsigned char cvOID_rsaSignatureWithsha1_l512_l11 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x84, 0x00, 0x11};
//1.3.36.3.3.1.1.640.11		Teletrust signature algorithm rsaSignatureWithsha1_l640_l11 
static const unsigned char cvOID_rsaSignatureWithsha1_l640_l11 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x85, 0x00, 0x11};
//1.3.36.3.3.1.1.768.11		Teletrust signature algorithm rsaSignatureWithsha1_l768_l11 
static const unsigned char cvOID_rsaSignatureWithsha1_l768_l11 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x86, 0x00, 0x11};
//1.3.36.3.3.1.1.896.11		Teletrust signature algorithm rsaSignatureWithsha1_l896_l11 
static const unsigned char cvOID_rsaSignatureWithsha1_l896_l11 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x87, 0x00, 0x11};
//1.3.36.3.3.1.1.1024.11		Teletrust signature algorithm rsaSignatureWithsha1_l1024_l11 
static const unsigned char cvOID_rsaSignatureWithsha1_l1024_l11 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x88, 0x00, 0x11};
//1.3.36.3.3.1.2		Teletrust signature algorithm rsaSignatureWithripemd160 
static const unsigned char cvOID_rsaSignatureWithripemd160 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02};
//1.3.36.3.3.1.2.512.2		Teletrust signature algorithm rsaSignatureWithripemd160_l512_l2 
static const unsigned char cvOID_rsaSignatureWithripemd160_l512_l2 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x84, 0x00, 0x02};
//1.3.36.3.3.1.2.640.2		Teletrust signature algorithm rsaSignatureWithripemd160_l640_l2 
static const unsigned char cvOID_rsaSignatureWithripemd160_l640_l2 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x85, 0x00, 0x02};
//1.3.36.3.3.1.2.768.2		Teletrust signature algorithm rsaSignatureWithripemd160_l768_l2 
static const unsigned char cvOID_rsaSignatureWithripemd160_l768_l2 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x86, 0x00, 0x02};
//1.3.36.3.3.1.2.892.2		Teletrust signature algorithm rsaSignatureWithripemd160_l896_l2 
static const unsigned char cvOID_rsaSignatureWithripemd160_l896_l2 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x87, 0x00, 0x02};
//1.3.36.3.3.1.2.1024.2		Teletrust signature algorithm rsaSignatureWithripemd160_l1024_l2 
static const unsigned char cvOID_rsaSignatureWithripemd160_l1024_l2 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x88, 0x00, 0x02};
//1.3.36.3.3.1.2.512.3		Teletrust signature algorithm rsaSignatureWithripemd160_l512_l3 
static const unsigned char cvOID_rsaSignatureWithripemd160_l512_l3 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x84, 0x00, 0x03};
//1.3.36.3.3.1.2.640.3		Teletrust signature algorithm rsaSignatureWithripemd160_l640_l3 
static const unsigned char cvOID_rsaSignatureWithripemd160_l640_l3 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x85, 0x00, 0x03};
//1.3.36.3.3.1.2.768.3		Teletrust signature algorithm rsaSignatureWithripemd160_l768_l3 
static const unsigned char cvOID_rsaSignatureWithripemd160_l768_l3 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x86, 0x00, 0x03};
//1.3.36.3.3.1.2.896.3		Teletrust signature algorithm rsaSignatureWithripemd160_l896_l3 
static const unsigned char cvOID_rsaSignatureWithripemd160_l896_l3 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x87, 0x00, 0x03};
//1.3.36.3.3.1.2.1024.3		Teletrust signature algorithm rsaSignatureWithripemd160_l1024_l3 
static const unsigned char cvOID_rsaSignatureWithripemd160_l1024_l3 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x88, 0x00, 0x03};
//1.3.36.3.3.1.2.512.5		Teletrust signature algorithm rsaSignatureWithripemd160_l512_l5 
static const unsigned char cvOID_rsaSignatureWithripemd160_l512_l5 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x84, 0x00, 0x05};
//1.3.36.3.3.1.2.640.5		Teletrust signature algorithm rsaSignatureWithripemd160_l640_l5 
static const unsigned char cvOID_rsaSignatureWithripemd160_l640_l5 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x85, 0x00, 0x05};
//1.3.36.3.3.1.2.768.5		Teletrust signature algorithm rsaSignatureWithripemd160_l768_l5 
static const unsigned char cvOID_rsaSignatureWithripemd160_l768_l5 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x86, 0x00, 0x05};
//1.3.36.3.3.1.2.896.5		Teletrust signature algorithm rsaSignatureWithripemd160_l896_l5 
static const unsigned char cvOID_rsaSignatureWithripemd160_l896_l5 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x87, 0x00, 0x05};
//1.3.36.3.3.1.2.1024.5		Teletrust signature algorithm rsaSignatureWithripemd160_l1024_l5 
static const unsigned char cvOID_rsaSignatureWithripemd160_l1024_l5 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x88, 0x00, 0x05};
//1.3.36.3.3.1.2.512.9		Teletrust signature algorithm rsaSignatureWithripemd160_l512_l9 
static const unsigned char cvOID_rsaSignatureWithripemd160_l512_l9 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x84, 0x00, 0x09};
//1.3.36.3.3.1.2.640.9		Teletrust signature algorithm rsaSignatureWithripemd160_l640_l9 
static const unsigned char cvOID_rsaSignatureWithripemd160_l640_l9 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x85, 0x00, 0x09};
//1.3.36.3.3.1.2.768.9		Teletrust signature algorithm rsaSignatureWithripemd160_l768_l9 
static const unsigned char cvOID_rsaSignatureWithripemd160_l768_l9 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x86, 0x00, 0x09};
//1.3.36.3.3.1.2.896.9		Teletrust signature algorithm rsaSignatureWithripemd160_l896_l9 
static const unsigned char cvOID_rsaSignatureWithripemd160_l896_l9 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x87, 0x00, 0x09};
//1.3.36.3.3.1.2.1024.9		Teletrust signature algorithm rsaSignatureWithripemd160_l1024_l9 
static const unsigned char cvOID_rsaSignatureWithripemd160_l1024_l9 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x88, 0x00, 0x09};
//1.3.36.3.3.1.2.512.11		Teletrust signature algorithm rsaSignatureWithripemd160_l512_l11 
static const unsigned char cvOID_rsaSignatureWithripemd160_l512_l11 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x84, 0x00, 0x11};
//1.3.36.3.3.1.2.640.11		Teletrust signature algorithm rsaSignatureWithripemd160_l640_l11 
static const unsigned char cvOID_rsaSignatureWithripemd160_l640_l11 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x85, 0x00, 0x11};
//1.3.36.3.3.1.2.768.11		Teletrust signature algorithm rsaSignatureWithripemd160_l768_l11 
static const unsigned char cvOID_rsaSignatureWithripemd160_l768_l11 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x86, 0x00, 0x11};
//1.3.36.3.3.1.2.896.11		Teletrust signature algorithm rsaSignatureWithripemd160_l896_l11 
static const unsigned char cvOID_rsaSignatureWithripemd160_l896_l11 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x87, 0x00, 0x11};
//1.3.36.3.3.1.2.1024.11		Teletrust signature algorithm rsaSignatureWithripemd160_l1024_l11 
static const unsigned char cvOID_rsaSignatureWithripemd160_l1024_l11 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x88, 0x00, 0x11};
//1.3.36.3.3.1.3		Teletrust signature algorithm rsaSignatureWithrimpemd128 
static const unsigned char cvOID_rsaSignatureWithrimpemd128 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x03};
//1.3.36.3.3.1.4		Teletrust signature algorithm rsaSignatureWithrimpemd256 
static const unsigned char cvOID_rsaSignatureWithrimpemd256 [] = {  0x2B, 0x24, 0x03, 0x03, 0x01, 0x04};
//1.3.36.3.3.2		Teletrust signature algorithm ecsieSign 
static const unsigned char cvOID_ecsieSign [] = {  0x2B, 0x24, 0x03, 0x03, 0x02};
//1.3.36.3.3.2.1		Teletrust signature algorithm ecsieSignWithsha1 
static const unsigned char cvOID_ecsieSignWithsha1 [] = {  0x2B, 0x24, 0x03, 0x03, 0x02, 0x01};
//1.3.36.3.3.2.2		Teletrust signature algorithm ecsieSignWithripemd160 
static const unsigned char cvOID_ecsieSignWithripemd160 [] = {  0x2B, 0x24, 0x03, 0x03, 0x02, 0x02};
//1.3.36.3.3.2.3		Teletrust signature algorithm ecsieSignWithmd2 
static const unsigned char cvOID_ecsieSignWithmd2 [] = {  0x2B, 0x24, 0x03, 0x03, 0x02, 0x03};
//1.3.36.3.3.2.4		Teletrust signature algorithm ecsieSignWithmd5 
static const unsigned char cvOID_ecsieSignWithmd5 [] = {  0x2B, 0x24, 0x03, 0x03, 0x02, 0x04};
//1.3.36.3.4		Teletrust algorithm signatureScheme 
static const unsigned char cvOID_signatureScheme [] = {  0x2B, 0x24, 0x03, 0x04};
//1.3.36.3.4.1		Teletrust signature scheme sigS_ISO9796-1 
static const unsigned char cvOID_sigS_ISO9796_1 [] = {  0x2B, 0x24, 0x03, 0x04, 0x01};
//1.3.36.3.4.2		Teletrust signature scheme sigS_ISO9796-2 
static const unsigned char cvOID_sigS_ISO9796_2 [] = {  0x2B, 0x24, 0x03, 0x04, 0x02};
//1.3.36.3.4.2.1		Teletrust signature scheme.  Unsure what this is supposed to be sigS_ISO9796-2Withred 
static const unsigned char cvOID_sigS_ISO9796_2Withred [] = {  0x2B, 0x24, 0x03, 0x04, 0x02, 0x01};
//1.3.36.3.4.2.2		Teletrust signature scheme.  Unsure what this is supposed to be sigS_ISO9796-2Withrsa 
static const unsigned char cvOID_sigS_ISO9796_2Withrsa [] = {  0x2B, 0x24, 0x03, 0x04, 0x02, 0x02};
//1.3.36.3.4.2.3		Teletrust signature scheme.  9796-2 with random number in padding field sigS_ISO9796-2Withrnd 
static const unsigned char cvOID_sigS_ISO9796_2Withrnd [] = {  0x2B, 0x24, 0x03, 0x04, 0x02, 0x03};
//1.3.36.4		Teletrust attribute attribute 
static const unsigned char cvOID_attribute_Teletrust [] = {  0x2B, 0x24, 0x04};
//1.3.36.5		Teletrust policy policy 
static const unsigned char cvOID_policy [] = {  0x2B, 0x24, 0x05};
//1.3.36.6		Teletrust API api 
static const unsigned char cvOID_api [] = {  0x2B, 0x24, 0x06};
//1.3.36.6.1		Teletrust API manufacturer-specific_api 
static const unsigned char cvOID_manufacturer_specific_api [] = {  0x2B, 0x24, 0x06, 0x01};
//1.3.36.6.1.1		Teletrust API utimaco-api 
static const unsigned char cvOID_utimaco_api [] = {  0x2B, 0x24, 0x06, 0x01, 0x01};
//1.3.36.6.2		Teletrust API functionality-specific_api 
static const unsigned char cvOID_functionality_specific_api [] = {  0x2B, 0x24, 0x06, 0x02};
//1.3.36.7		Teletrust key management keymgmnt 
static const unsigned char cvOID_keymgmnt [] = {  0x2B, 0x24, 0x07};
//1.3.36.7.1		Teletrust key management keyagree 
static const unsigned char cvOID_keyagree [] = {  0x2B, 0x24, 0x07, 0x01};
//1.3.36.7.1.1		Teletrust key management bsiPKE 
static const unsigned char cvOID_bsiPKE [] = {  0x2B, 0x24, 0x07, 0x01, 0x01};
//1.3.36.7.2		Teletrust key management keytrans 
static const unsigned char cvOID_keytrans [] = {  0x2B, 0x24, 0x07, 0x02};
//1.3.36.7.2.1		Teletrust key management.  9796-2 with key stored in hash field encISO9796-2Withrsa 
static const unsigned char cvOID_encISO9796_2Withrsa [] = {  0x2B, 0x24, 0x07, 0x02, 0x01};
//1.3.36.8.1.1		Teletrust policy sigiSigConform 
static const unsigned char cvOID_sigiSigConform [] = {  0x2B, 0x24, 0x08, 0x01, 0x01};
//1.3.36.8.2.1		Teletrust extended key usage directoryService 
static const unsigned char cvOID_directoryService [] = {  0x2B, 0x24, 0x08, 0x02, 0x01};
//1.3.36.8.3.1		Teletrust attribute dateOfCertGen 
static const unsigned char cvOID_dateOfCertGen [] = {  0x2B, 0x24, 0x08, 0x03, 0x01};
//1.3.36.8.3.2		Teletrust attribute procuration 
static const unsigned char cvOID_procuration [] = {  0x2B, 0x24, 0x08, 0x03, 0x02};
//1.3.36.8.3.3		Teletrust attribute admission 
static const unsigned char cvOID_admission [] = {  0x2B, 0x24, 0x08, 0x03, 0x03};
//1.3.36.8.3.4		Teletrust attribute monetaryLimit 
static const unsigned char cvOID_monetaryLimit [] = {  0x2B, 0x24, 0x08, 0x03, 0x04};
//1.3.36.8.3.5		Teletrust attribute declarationOfMajority 
static const unsigned char cvOID_declarationOfMajority [] = {  0x2B, 0x24, 0x08, 0x03, 0x05};
//1.3.36.8.3.6		Teletrust attribute integratedCircuitCardSerialNumber 
static const unsigned char cvOID_integratedCircuitCardSerialNumber [] = {  0x2B, 0x24, 0x08, 0x03, 0x06};
//1.3.36.8.3.7		Teletrust attribute pKReference 
static const unsigned char cvOID_pKReference [] = {  0x2B, 0x24, 0x08, 0x03, 0x07};
//1.3.36.8.3.8		Teletrust attribute restriction 
static const unsigned char cvOID_restriction_1 [] = {  0x2B, 0x24, 0x08, 0x03, 0x08};
//1.3.36.8.3.9		Teletrust attribute retrieveIfAllowed 
static const unsigned char cvOID_retrieveIfAllowed [] = {  0x2B, 0x24, 0x08, 0x03, 0x09};
//1.3.36.8.3.10		Teletrust attribute requestedCertificate 
static const unsigned char cvOID_requestedCertificate [] = {  0x2B, 0x24, 0x08, 0x03, 0x0A};
//1.3.36.8.3.11		Teletrust attribute namingAuthorities 
static const unsigned char cvOID_namingAuthorities [] = {  0x2B, 0x24, 0x08, 0x03, 0x0B};
//1.3.36.8.3.12		Teletrust attribute certInDirSince 
static const unsigned char cvOID_certInDirSince [] = {  0x2B, 0x24, 0x08, 0x03, 0x0C};
//1.3.36.8.3.13		Teletrust attribute certHash 
static const unsigned char cvOID_certHash [] = {  0x2B, 0x24, 0x08, 0x03, 0x0D};
//1.3.36.8.4.1		Teletrust OtherName attribute personalData 
static const unsigned char cvOID_personalData [] = {  0x2B, 0x24, 0x08, 0x04, 0x01};
//1.3.36.8.4.8		Teletrust attribute certificate attribute restriction 
static const unsigned char cvOID_restriction_2 [] = {  0x2B, 0x24, 0x08, 0x04, 0x08};
//1.3.36.8.5.1.1.1		Teletrust signature algorithm rsaIndicateSHA1 
static const unsigned char cvOID_rsaIndicateSHA1 [] = {  0x2B, 0x24, 0x08, 0x05, 0x01, 0x01, 0x01};
//1.3.36.8.5.1.1.2		Teletrust signature algorithm rsaIndicateRIPEMD160 
static const unsigned char cvOID_rsaIndicateRIPEMD160 [] = {  0x2B, 0x24, 0x08, 0x05, 0x01, 0x01, 0x02};
//1.3.36.8.5.1.1.3		Teletrust signature algorithm rsaWithSHA1 
static const unsigned char cvOID_rsaWithSHA1 [] = {  0x2B, 0x24, 0x08, 0x05, 0x01, 0x01, 0x03};
//1.3.36.8.5.1.1.4		Teletrust signature algorithm rsaWithRIPEMD160 
static const unsigned char cvOID_rsaWithRIPEMD160 [] = {  0x2B, 0x24, 0x08, 0x05, 0x01, 0x01, 0x04};
//1.3.36.8.5.1.2.1		Teletrust signature algorithm dsaExtended 
static const unsigned char cvOID_dsaExtended [] = {  0x2B, 0x24, 0x08, 0x05, 0x01, 0x02, 0x01};
//1.3.36.8.5.1.2.2		Teletrust signature algorithm dsaWithRIPEMD160 
static const unsigned char cvOID_dsaWithRIPEMD160 [] = {  0x2B, 0x24, 0x08, 0x05, 0x01, 0x02, 0x02};
//1.3.36.8.6.1		Teletrust signature attributes cert 
static const unsigned char cvOID_cert [] = {  0x2B, 0x24, 0x08, 0x06, 0x01};
//1.3.36.8.6.2		Teletrust signature attributes certRef 
static const unsigned char cvOID_certRef [] = {  0x2B, 0x24, 0x08, 0x06, 0x02};
//1.3.36.8.6.3		Teletrust signature attributes attrCert 
static const unsigned char cvOID_attrCert [] = {  0x2B, 0x24, 0x08, 0x06, 0x03};
//1.3.36.8.6.4		Teletrust signature attributes attrRef 
static const unsigned char cvOID_attrRef [] = {  0x2B, 0x24, 0x08, 0x06, 0x04};
//1.3.36.8.6.5		Teletrust signature attributes fileName 
static const unsigned char cvOID_fileName [] = {  0x2B, 0x24, 0x08, 0x06, 0x05};
//1.3.36.8.6.6		Teletrust signature attributes storageTime 
static const unsigned char cvOID_storageTime [] = {  0x2B, 0x24, 0x08, 0x06, 0x06};
//1.3.36.8.6.7		Teletrust signature attributes fileSize 
static const unsigned char cvOID_fileSize [] = {  0x2B, 0x24, 0x08, 0x06, 0x07};
//1.3.36.8.6.8		Teletrust signature attributes location 
static const unsigned char cvOID_location [] = {  0x2B, 0x24, 0x08, 0x06, 0x08};
//1.3.36.8.6.9		Teletrust signature attributes sigNumber 
static const unsigned char cvOID_sigNumber [] = {  0x2B, 0x24, 0x08, 0x06, 0x09};
//1.3.36.8.6.10		Teletrust signature attributes autoGen 
static const unsigned char cvOID_autoGen [] = {  0x2B, 0x24, 0x08, 0x06, 0x0A};
//1.3.36.8.7.1.1		Teletrust presentation types ptAdobeILL 
static const unsigned char cvOID_ptAdobeILL [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x01};
//1.3.36.8.7.1.2		Teletrust presentation types ptAmiPro 
static const unsigned char cvOID_ptAmiPro [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x02};
//1.3.36.8.7.1.3		Teletrust presentation types ptAutoCAD 
static const unsigned char cvOID_ptAutoCAD [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x03};
//1.3.36.8.7.1.4		Teletrust presentation types ptBinary 
static const unsigned char cvOID_ptBinary [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x04};
//1.3.36.8.7.1.5		Teletrust presentation types ptBMP 
static const unsigned char cvOID_ptBMP [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x05};
//1.3.36.8.7.1.6		Teletrust presentation types ptCGM 
static const unsigned char cvOID_ptCGM [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x06};
//1.3.36.8.7.1.7		Teletrust presentation types ptCorelCRT 
static const unsigned char cvOID_ptCorelCRT [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x07};
//1.3.36.8.7.1.8		Teletrust presentation types ptCorelDRW 
static const unsigned char cvOID_ptCorelDRW [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x08};
//1.3.36.8.7.1.9		Teletrust presentation types ptCorelEXC 
static const unsigned char cvOID_ptCorelEXC [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x09};
//1.3.36.8.7.1.10		Teletrust presentation types ptCorelPHT 
static const unsigned char cvOID_ptCorelPHT [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x0A};
//1.3.36.8.7.1.11		Teletrust presentation types ptDraw 
static const unsigned char cvOID_ptDraw [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x0B};
//1.3.36.8.7.1.12		Teletrust presentation types ptDVI 
static const unsigned char cvOID_ptDVI [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x0C};
//1.3.36.8.7.1.13		Teletrust presentation types ptEPS 
static const unsigned char cvOID_ptEPS [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x0D};
//1.3.36.8.7.1.14		Teletrust presentation types ptExcel 
static const unsigned char cvOID_ptExcel [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x0E};
//1.3.36.8.7.1.15		Teletrust presentation types ptGEM 
static const unsigned char cvOID_ptGEM [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x0F};
//1.3.36.8.7.1.16		Teletrust presentation types ptGIF 
static const unsigned char cvOID_ptGIF [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x10};
//1.3.36.8.7.1.17		Teletrust presentation types ptHPGL 
static const unsigned char cvOID_ptHPGL [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x11};
//1.3.36.8.7.1.18		Teletrust presentation types ptJPEG 
static const unsigned char cvOID_ptJPEG [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x12};
//1.3.36.8.7.1.19		Teletrust presentation types ptKodak 
static const unsigned char cvOID_ptKodak [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x13};
//1.3.36.8.7.1.20		Teletrust presentation types ptLaTeX 
static const unsigned char cvOID_ptLaTeX [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x14};
//1.3.36.8.7.1.21		Teletrust presentation types ptLotus 
static const unsigned char cvOID_ptLotus [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x15};
//1.3.36.8.7.1.22		Teletrust presentation types ptLotusPIC 
static const unsigned char cvOID_ptLotusPIC [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x16};
//1.3.36.8.7.1.23		Teletrust presentation types ptMacPICT 
static const unsigned char cvOID_ptMacPICT [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x17};
//1.3.36.8.7.1.24		Teletrust presentation types ptMacWord 
static const unsigned char cvOID_ptMacWord [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x18};
//1.3.36.8.7.1.25		Teletrust presentation types ptMSWfD 
static const unsigned char cvOID_ptMSWfD [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x19};
//1.3.36.8.7.1.26		Teletrust presentation types ptMSWord 
static const unsigned char cvOID_ptMSWord [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x1A};
//1.3.36.8.7.1.27		Teletrust presentation types ptMSWord2 
static const unsigned char cvOID_ptMSWord2 [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x1B};
//1.3.36.8.7.1.28		Teletrust presentation types ptMSWord6 
static const unsigned char cvOID_ptMSWord6 [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x1C};
//1.3.36.8.7.1.29		Teletrust presentation types ptMSWord8 
static const unsigned char cvOID_ptMSWord8 [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x1D};
//1.3.36.8.7.1.30		Teletrust presentation types ptPDF 
static const unsigned char cvOID_ptPDF [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x1E};
//1.3.36.8.7.1.31		Teletrust presentation types ptPIF 
static const unsigned char cvOID_ptPIF [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x1F};
//1.3.36.8.7.1.32		Teletrust presentation types ptPostscript 
static const unsigned char cvOID_ptPostscript [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x20};
//1.3.36.8.7.1.33		Teletrust presentation types ptRTF 
static const unsigned char cvOID_ptRTF [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x21};
//1.3.36.8.7.1.34		Teletrust presentation types ptSCITEX 
static const unsigned char cvOID_ptSCITEX [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x22};
//1.3.36.8.7.1.35		Teletrust presentation types ptTAR 
static const unsigned char cvOID_ptTAR [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x23};
//1.3.36.8.7.1.36		Teletrust presentation types ptTarga 
static const unsigned char cvOID_ptTarga [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x24};
//1.3.36.8.7.1.37		Teletrust presentation types ptTeX 
static const unsigned char cvOID_ptTeX [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x25};
//1.3.36.8.7.1.38		Teletrust presentation types ptText 
static const unsigned char cvOID_ptText [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x26};
//1.3.36.8.7.1.39		Teletrust presentation types ptTIFF 
static const unsigned char cvOID_ptTIFF [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x27};
//1.3.36.8.7.1.40		Teletrust presentation types ptTIFF-FC 
static const unsigned char cvOID_ptTIFF_FC [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x28};
//1.3.36.8.7.1.41		Teletrust presentation types ptUID 
static const unsigned char cvOID_ptUID [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x29};
//1.3.36.8.7.1.42		Teletrust presentation types ptUUEncode 
static const unsigned char cvOID_ptUUEncode [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x2A};
//1.3.36.8.7.1.43		Teletrust presentation types ptWMF 
static const unsigned char cvOID_ptWMF [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x2B};
//1.3.36.8.7.1.44		Teletrust presentation types ptWordPerfect 
static const unsigned char cvOID_ptWordPerfect [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x2C};
//1.3.36.8.7.1.45		Teletrust presentation types ptWPGrph 
static const unsigned char cvOID_ptWPGrph [] = {  0x2B, 0x24, 0x08, 0x07, 0x01, 0x2D};
//1.3.101.1.4		Thawte thawte-ce 
static const unsigned char cvOID_thawte_ce [] = {  0x2B, 0x65, 0x01, 0x04};
//1.3.101.1.4.1		Thawte certificate extension strongExtranet 
static const unsigned char cvOID_strongExtranet [] = {  0x2B, 0x65, 0x01, 0x04, 0x01};
//2.5.4.0		X.520 id-at (2 5 4) objectClass 
static const unsigned char cvOID_objectClass [] = {  0x55, 0x04, 0x00};
//2.5.4.1		X.520 id-at (2 5 4) aliasedEntryName 
static const unsigned char cvOID_aliasedEntryName [] = {  0x55, 0x04, 0x01};
//2.5.4.2		X.520 id-at (2 5 4) knowledgeInformation 
static const unsigned char cvOID_knowledgeInformation [] = {  0x55, 0x04, 0x02};
//2.5.4.3		X.520 id-at (2 5 4) commonName 
static const unsigned char cvOID_commonName [] = {  0x55, 0x04, 0x03};
//2.5.4.4		X.520 id-at (2 5 4) surname 
static const unsigned char cvOID_surname [] = {  0x55, 0x04, 0x04};
//2.5.4.5		X.520 id-at (2 5 4) serialNumber 
static const unsigned char cvOID_serialNumber [] = {  0x55, 0x04, 0x05};
//2.5.4.6		X.520 id-at (2 5 4) countryName 
static const unsigned char cvOID_countryName [] = {  0x55, 0x04, 0x06};
//2.5.4.7		X.520 id-at (2 5 4) localityName 
static const unsigned char cvOID_localityName [] = {  0x55, 0x04, 0x07};
//2.5.4.7.1		X.520 id-at (2 5 4) collectiveLocalityName 
static const unsigned char cvOID_collectiveLocalityName [] = {  0x55, 0x04, 0x07, 0x01};
//2.5.4.8		X.520 id-at (2 5 4) stateOrProvinceName 
static const unsigned char cvOID_stateOrProvinceName [] = {  0x55, 0x04, 0x08};
//2.5.4.8.1		X.520 id-at (2 5 4) collectiveStateOrProvinceName 
static const unsigned char cvOID_collectiveStateOrProvinceName [] = {  0x55, 0x04, 0x08, 0x01};
//2.5.4.9		X.520 id-at (2 5 4) streetAddress 
static const unsigned char cvOID_streetAddress [] = {  0x55, 0x04, 0x09};
//2.5.4.9.1		X.520 id-at (2 5 4) collectiveStreetAddress 
static const unsigned char cvOID_collectiveStreetAddress [] = {  0x55, 0x04, 0x09, 0x01};
//2.5.4.10		X.520 id-at (2 5 4) organizationName 
static const unsigned char cvOID_organizationName [] = {  0x55, 0x04, 0x0A};
//2.5.4.10.1		X.520 id-at (2 5 4) collectiveOrganizationName 
static const unsigned char cvOID_collectiveOrganizationName [] = {  0x55, 0x04, 0x0A, 0x01};
//2.5.4.11		X.520 id-at (2 5 4) organizationalUnitName 
static const unsigned char cvOID_organizationalUnitName [] = {  0x55, 0x04, 0x0B};
//2.5.4.11.1		X.520 id-at (2 5 4) collectiveOrganizationalUnitName 
static const unsigned char cvOID_collectiveOrganizationalUnitName [] = {  0x55, 0x04, 0x0B, 0x01};
//2.5.4.12		X.520 id-at (2 5 4) title 
static const unsigned char cvOID_title [] = {  0x55, 0x04, 0x0C};
//2.5.4.13		X.520 id-at (2 5 4) description 
static const unsigned char cvOID_description [] = {  0x55, 0x04, 0x0D};
//2.5.4.14		X.520 id-at (2 5 4) searchGuide 
static const unsigned char cvOID_searchGuide [] = {  0x55, 0x04, 0x0E};
//2.5.4.15		X.520 id-at (2 5 4) businessCategory 
static const unsigned char cvOID_businessCategory [] = {  0x55, 0x04, 0x0F};
//2.5.4.16		X.520 id-at (2 5 4) postalAddress 
static const unsigned char cvOID_postalAddress [] = {  0x55, 0x04, 0x10};
//2.5.4.16.1		X.520 id-at (2 5 4) collectivePostalAddress 
static const unsigned char cvOID_collectivePostalAddress [] = {  0x55, 0x04, 0x10, 0x01};
//2.5.4.17		X.520 id-at (2 5 4) postalCode 
static const unsigned char cvOID_postalCode [] = {  0x55, 0x04, 0x11};
//2.5.4.17.1		X.520 id-at (2 5 4) collectivePostalCode 
static const unsigned char cvOID_collectivePostalCode [] = {  0x55, 0x04, 0x11, 0x01};
//2.5.4.18		X.520 id-at (2 5 4) postOfficeBox 
static const unsigned char cvOID_postOfficeBox [] = {  0x55, 0x04, 0x12};
//2.5.4.18.1		X.520 id-at (2 5 4) collectivePostOfficeBox 
static const unsigned char cvOID_collectivePostOfficeBox [] = {  0x55, 0x04, 0x12, 0x01};
//2.5.4.19		X.520 id-at (2 5 4) physicalDeliveryOfficeName 
static const unsigned char cvOID_physicalDeliveryOfficeName [] = {  0x55, 0x04, 0x13};
//2.5.4.19.1		X.520 id-at (2 5 4) collectivePhysicalDeliveryOfficeName 
static const unsigned char cvOID_collectivePhysicalDeliveryOfficeName [] = {  0x55, 0x04, 0x13, 0x01};
//2.5.4.20		X.520 id-at (2 5 4) telephoneNumber 
static const unsigned char cvOID_telephoneNumber [] = {  0x55, 0x04, 0x14};
//2.5.4.20.1		X.520 id-at (2 5 4) collectiveTelephoneNumber 
static const unsigned char cvOID_collectiveTelephoneNumber [] = {  0x55, 0x04, 0x14, 0x01};
//2.5.4.21		X.520 id-at (2 5 4) telexNumber 
static const unsigned char cvOID_telexNumber [] = {  0x55, 0x04, 0x15};
//2.5.4.21.1		X.520 id-at (2 5 4) collectiveTelexNumber 
static const unsigned char cvOID_collectiveTelexNumber [] = {  0x55, 0x04, 0x15, 0x01};
//2.5.4.22		X.520 id-at (2 5 4) teletexTerminalIdentifier 
static const unsigned char cvOID_teletexTerminalIdentifier [] = {  0x55, 0x04, 0x16};
//2.5.4.22.1		X.520 id-at (2 5 4) collectiveTeletexTerminalIdentifier 
static const unsigned char cvOID_collectiveTeletexTerminalIdentifier [] = {  0x55, 0x04, 0x16, 0x01};
//2.5.4.23		X.520 id-at (2 5 4) facsimileTelephoneNumber 
static const unsigned char cvOID_facsimileTelephoneNumber [] = {  0x55, 0x04, 0x17};
//2.5.4.23.1		X.520 id-at (2 5 4) collectiveFacsimileTelephoneNumber 
static const unsigned char cvOID_collectiveFacsimileTelephoneNumber [] = {  0x55, 0x04, 0x17, 0x01};
//2.5.4.24		X.520 id-at (2 5 4) x121Address 
static const unsigned char cvOID_x121Address [] = {  0x55, 0x04, 0x18};
//2.5.4.25		X.520 id-at (2 5 4) internationalISDNNumber 
static const unsigned char cvOID_internationalISDNNumber [] = {  0x55, 0x04, 0x19};
//2.5.4.25.1		X.520 id-at (2 5 4) collectiveInternationalISDNNumber 
static const unsigned char cvOID_collectiveInternationalISDNNumber [] = {  0x55, 0x04, 0x19, 0x01};
//2.5.4.26		X.520 id-at (2 5 4) registeredAddress 
static const unsigned char cvOID_registeredAddress [] = {  0x55, 0x04, 0x1A};
//2.5.4.27		X.520 id-at (2 5 4) destinationIndicator 
static const unsigned char cvOID_destinationIndicator [] = {  0x55, 0x04, 0x1B};
//2.5.4.28		X.520 id-at (2 5 4) preferredDeliveryMehtod 
static const unsigned char cvOID_preferredDeliveryMehtod [] = {  0x55, 0x04, 0x1C};
//2.5.4.29		X.520 id-at (2 5 4) presentationAddress 
static const unsigned char cvOID_presentationAddress [] = {  0x55, 0x04, 0x1D};
//2.5.4.30		X.520 id-at (2 5 4) supportedApplicationContext 
static const unsigned char cvOID_supportedApplicationContext [] = {  0x55, 0x04, 0x1E};
//2.5.4.31		X.520 id-at (2 5 4) member 
static const unsigned char cvOID_member [] = {  0x55, 0x04, 0x1F};
//2.5.4.32		X.520 id-at (2 5 4) owner 
static const unsigned char cvOID_owner [] = {  0x55, 0x04, 0x20};
//2.5.4.33		X.520 id-at (2 5 4) roleOccupant 
static const unsigned char cvOID_roleOccupant [] = {  0x55, 0x04, 0x21};
//2.5.4.34		X.520 id-at (2 5 4) seeAlso 
static const unsigned char cvOID_seeAlso [] = {  0x55, 0x04, 0x22};
//2.5.4.35		X.520 id-at (2 5 4) userPassword 
static const unsigned char cvOID_userPassword [] = {  0x55, 0x04, 0x23};
//2.5.4.36		X.520 id-at (2 5 4) userCertificate 
static const unsigned char cvOID_userCertificate [] = {  0x55, 0x04, 0x24};
//2.5.4.37		X.520 id-at (2 5 4) caCertificate 
static const unsigned char cvOID_caCertificate [] = {  0x55, 0x04, 0x25};
//2.5.4.38		X.520 id-at (2 5 4) authorityRevocationList 
static const unsigned char cvOID_authorityRevocationList [] = {  0x55, 0x04, 0x26};
//2.5.4.39		X.520 id-at (2 5 4) certificateRevocationList 
static const unsigned char cvOID_certificateRevocationList [] = {  0x55, 0x04, 0x27};
//2.5.4.40		X.520 id-at (2 5 4) crossCertificatePair 
static const unsigned char cvOID_crossCertificatePair_2 [] = {  0x55, 0x04, 0x28};
//2.5.4.41		X.520 id-at (2 5 4) name 
static const unsigned char cvOID_name [] = {  0x55, 0x04, 0x29};
//2.5.4.42		X.520 id-at (2 5 4) givenName 
static const unsigned char cvOID_givenName [] = {  0x55, 0x04, 0x2A};
//2.5.4.43		X.520 id-at (2 5 4) initials 
static const unsigned char cvOID_initials [] = {  0x55, 0x04, 0x2B};
//2.5.4.44		X.520 id-at (2 5 4) generationQualifier 
static const unsigned char cvOID_generationQualifier [] = {  0x55, 0x04, 0x2C};
//2.5.4.45		X.520 id-at (2 5 4) uniqueIdentifier 
static const unsigned char cvOID_uniqueIdentifier [] = {  0x55, 0x04, 0x2D};
//2.5.4.46		X.520 id-at (2 5 4) dnQualifier 
static const unsigned char cvOID_dnQualifier [] = {  0x55, 0x04, 0x2E};
//2.5.4.47		X.520 id-at (2 5 4) enhancedSearchGuide 
static const unsigned char cvOID_enhancedSearchGuide [] = {  0x55, 0x04, 0x2F};
//2.5.4.48		X.520 id-at (2 5 4) protocolInformation 
static const unsigned char cvOID_protocolInformation [] = {  0x55, 0x04, 0x30};
//2.5.4.49		X.520 id-at (2 5 4) distinguishedName 
static const unsigned char cvOID_distinguishedName [] = {  0x55, 0x04, 0x31};
//2.5.4.50		X.520 id-at (2 5 4) uniqueMember 
static const unsigned char cvOID_uniqueMember [] = {  0x55, 0x04, 0x32};
//2.5.4.51		X.520 id-at (2 5 4) houseIdentifier 
static const unsigned char cvOID_houseIdentifier [] = {  0x55, 0x04, 0x33};
//2.5.4.52		X.520 id-at (2 5 4) supportedAlgorithms 
static const unsigned char cvOID_supportedAlgorithms [] = {  0x55, 0x04, 0x34};
//2.5.4.53		X.520 id-at (2 5 4) deltaRevocationList 
static const unsigned char cvOID_deltaRevocationList [] = {  0x55, 0x04, 0x35};
//2.5.4.55		X.520 id-at (2 5 4) clearance 
static const unsigned char cvOID_clearance [] = {  0x55, 0x04, 0x36};
//2.5.4.58		X.520 id-at (2 5 4) crossCertificatePair 
static const unsigned char cvOID_crossCertificatePair_1 [] = {  0x55, 0x04, 0x3A};
//2.5.4.65		Naming attributes of type X520Pseudonym
static const unsigned char cvOID_pseudonym[]			=    {  0x55, 0x04, 0x41};
//2.5.8.1.1		X.500 algorithms.  Ambiguous, since no padding rules specified rsa 
static const unsigned char cvOID_rsa_X500 [] = {  0x55, 0x08, 0x01, 0x01};
//2.5.29.1		X.509 id-ce (2 5 29).  Deprecated, use (2 5 29 35) instead authorityKeyIdentifier 
static const unsigned char cvOID_authorityKeyIdentifier_old[] = {  0x55, 0x1D, 0x01};
//2.5.29.2		X.509 id-ce (2 5 29).  Obsolete, use keyUsage/extKeyUsage instead keyAttributes 
static const unsigned char cvOID_keyAttributes [] = {  0x55, 0x1D, 0x02};
//2.5.29.3		X.509 id-ce (2 5 29).  Deprecated, use (2 5 29 32) instead certificatePolicies 
static const unsigned char cvOID_certificatePolicies_old [] = {  0x55, 0x1D, 0x03};
//2.5.29.4		X.509 id-ce (2 5 29).  Obsolete, use keyUsage/extKeyUsage instead keyUsageRestriction 
static const unsigned char cvOID_keyUsageRestriction [] = {  0x55, 0x1D, 0x04};
//2.5.29.5		X.509 id-ce (2 5 29).  Deprecated, use (2 5 29 33) instead policyMapping 
static const unsigned char cvOID_policyMapping [] = {  0x55, 0x1D, 0x05};
//2.5.29.6		X.509 id-ce (2 5 29).  Obsolete, use namestatic constraints instead subtreesstatic constraint 
static const unsigned char cvOID_subtreesconstraint [] = {  0x55, 0x1D, 0x06};
//2.5.29.7		X.509 id-ce (2 5 29).  Deprecated, use (2 5 29 17) instead subjectAltName 
static const unsigned char cvOID_subjectAltName_old [] = {  0x55, 0x1D, 0x07};
//2.5.29.8		X.509 id-ce (2 5 29).  Deprecated, use (2 5 29 18) instead issuerAltName 
static const unsigned char cvOID_issuerAltName_old [] = {  0x55, 0x1D, 0x08};
//2.5.29.9		X.509 id-ce (2 5 29) subjectDirectoryAttributes 
static const unsigned char cvOID_subjectDirectoryAttributes [] = {  0x55, 0x1D, 0x09};
//2.5.29.10		X.509 id-ce (2 5 29).  Deprecated, use (2 5 29 19) instead basicstatic constraints 
static const unsigned char cvOID_basicconstraints_old [] = {  0x55, 0x1D, 0x0A};
//2.5.29.11		X.509 id-ce (2 5 29).  Deprecated, use (2 5 29 30) instead namestatic constraints 
static const unsigned char cvOID_nameconstraints_old [] = {  0x55, 0x1D, 0x0B};
//2.5.29.12		X.509 id-ce (2 5 29).  Deprecated, use (2 5 29 36) instead policystatic constraints 
static const unsigned char cvOID_policyconstraints_old_1 [] = {  0x55, 0x1D, 0x0C};
//2.5.29.13		X.509 id-ce (2 5 29).  Deprecated, use (2 5 29 19) instead basicstatic constraints 
static const unsigned char cvOID_basicconstraints_2 [] = {  0x55, 0x1D, 0x0D};
//2.5.29.14		X.509 id-ce (2 5 29) subjectKeyIdentifier 
static const unsigned char cvOID_subjectKeyIdentifier[] = {  0x55, 0x1D, 0x0E};
//2.5.29.15		X.509 id-ce (2 5 29) keyUsage 
static const unsigned char cvOID_keyUsage[] = {  0x55, 0x1D, 0x0F};
//2.5.29.16		X.509 id-ce (2 5 29) privateKeyUsagePeriod 
static const unsigned char cvOID_privateKeyUsagePeriod [] = {  0x55, 0x1D, 0x10};
//2.5.29.17		X.509 id-ce (2 5 29) subjectAltName 
static const unsigned char cvOID_subjectAltName [] = {  0x55, 0x1D, 0x11};
//2.5.29.18		X.509 id-ce (2 5 29) issuerAltName 
static const unsigned char cvOID_issuerAltName [] = {  0x55, 0x1D, 0x12};
//2.5.29.19		X.509 id-ce (2 5 29) basicstatic constraints 
static const unsigned char cvOID_basicconstraints[] = {  0x55, 0x1D, 0x13};
//2.5.29.20		X.509 id-ce (2 5 29) cRLNumber 
static const unsigned char cvOID_cRLNumber [] = {  0x55, 0x1D, 0x14};
//2.5.29.21		X.509 id-ce (2 5 29) cRLReason 
static const unsigned char cvOID_cRLReason [] = {  0x55, 0x1D, 0x15};
//2.5.29.22		X.509 id-ce (2 5 29).  Deprecated, alternative OID uncertain expirationDate 
static const unsigned char cvOID_expirationDate [] = {  0x55, 0x1D, 0x16};
//2.5.29.23		X.509 id-ce (2 5 29) instructionCode 
static const unsigned char cvOID_instructionCode [] = {  0x55, 0x1D, 0x17};
//2.5.29.24		X.509 id-ce (2 5 29) invalidityDate 
static const unsigned char cvOID_invalidityDate [] = {  0x55, 0x1D, 0x18};
//2.5.29.25		X.509 id-ce (2 5 29).  Deprecated, use (2 5 29 31) instead cRLDistributionPoints 
static const unsigned char cvOID_cRLDistributionPoints_old [] = {  0x55, 0x1D, 0x19};
//2.5.29.26		X.509 id-ce (2 5 29).  Deprecated, use (2 5 29 28) instead issuingDistributionPoint 
static const unsigned char cvOID_issuingDistributionPoint_old [] = {  0x55, 0x1D, 0x1A};
//2.5.29.27		X.509 id-ce (2 5 29) deltaCRLIndicator 
static const unsigned char cvOID_deltaCRLIndicator [] = {  0x55, 0x1D, 0x1B};
//2.5.29.28		X.509 id-ce (2 5 29) issuingDistributionPoint 
static const unsigned char cvOID_issuingDistributionPoint [] = {  0x55, 0x1D, 0x1C};
//2.5.29.29		X.509 id-ce (2 5 29) certificateIssuer 
static const unsigned char cvOID_certificateIssuer [] = {  0x55, 0x1D, 0x1D};
//2.5.29.30		X.509 id-ce (2 5 29) namestatic constraints 
static const unsigned char cvOID_nameconstraints [] = {  0x55, 0x1D, 0x1E};
//2.5.29.31		X.509 id-ce (2 5 29) cRLDistributionPoints 
static const unsigned char cvOID_cRLDistributionPoints[] = {  0x55, 0x1D, 0x1F};
//2.5.29.32		X.509 id-ce (2 5 29) certificatePolicies 
static const unsigned char cvOID_certificatePolicies [] = {  0x55, 0x1D, 0x20};
//2.5.29.32.0	X.509 id-ce (2 5 29.0) anyPolicies 
static const unsigned char cvOID_anyPolicies [] = {  0x55, 0x1D, 0x20, 0x00};
//2.5.29.33		X.509 id-ce (2 5 29) policyMappings 
static const unsigned char cvOID_policyMappings [] = {  0x55, 0x1D, 0x21};
//2.5.29.34		X.509 id-ce (2 5 29).  Deprecated, use (2 5 29 36) instead policystatic constraints 
static const unsigned char cvOID_policyconstraints_old_2 [] = {  0x55, 0x1D, 0x22};
//2.5.29.35		X.509 id-ce (2 5 29) authorityKeyIdentifier 
static const unsigned char cvOID_authorityKeyIdentifier [] = {  0x55, 0x1D, 0x23};
//2.5.29.36		X.509 id-ce (2 5 29) policystatic constraints 
static const unsigned char cvOID_policyconstraints [] = {  0x55, 0x1D, 0x24};
//2.5.29.37		X.509 id-ce (2 5 29) extKeyUsage 
static const unsigned char cvOID_extKeyUsage [] = {  0x55, 0x1D, 0x25};
//2.5.29.37.0	anyExtendedKeyUsage id-ce-extKeyUsage 0
static const unsigned char cvOID_anyExtendedKeyUsage [] = {  0x55, 0x1D, 0x25, 0x00};
//ame
//2.5.29.46		X.509 id-ce (2 5 29) id-ce-freshestCRL 
static const unsigned char cvOID_freshestCRL [] = {  0x55, 0x1D, 0x2E};
//2.5.29.54		X.509 id-ce (2 5 29) inhibitAnyPolicy 
static const unsigned char cvOID_inhibitAnyPolicy [] = {  0x55, 0x1D, 0x36};

//2.16.840.1.101.2.1.1.1		SDN.700 INFOSEC algorithms sdnsSignatureAlgorithm 
static const unsigned char cvOID_sdnsSignatureAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x01};
//2.16.840.1.101.2.1.1.2		SDN.700 INFOSEC algorithms.  Formerly known as mosaicSignatureAlgorithm, this OID is better known as dsaWithSHA-1. fortezzaSignatureAlgorithm 
static const unsigned char cvOID_fortezzaSignatureAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x02};
//2.16.840.1.101.2.1.1.3		SDN.700 INFOSEC algorithms sdnsConfidentialityAlgorithm 
static const unsigned char cvOID_sdnsConfidentialityAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x03};
//2.16.840.1.101.2.1.1.4		SDN.700 INFOSEC algorithms.  Formerly known as mosaicConfidentialityAlgorithm fortezzaConfidentialityAlgorithm 
static const unsigned char cvOID_fortezzaConfidentialityAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x04};
//2.16.840.1.101.2.1.1.5		SDN.700 INFOSEC algorithms sdnsIntegrityAlgorithm 
static const unsigned char cvOID_sdnsIntegrityAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x05};
//2.16.840.1.101.2.1.1.6		SDN.700 INFOSEC algorithms.  Formerly known as mosaicIntegrityAlgorithm fortezzaIntegrityAlgorithm 
static const unsigned char cvOID_fortezzaIntegrityAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x06};
//2.16.840.1.101.2.1.1.7		SDN.700 INFOSEC algorithms sdnsTokenProtectionAlgorithm 
static const unsigned char cvOID_sdnsTokenProtectionAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x07};
//2.16.840.1.101.2.1.1.8		SDN.700 INFOSEC algorithms.  Formerly know as mosaicTokenProtectionAlgorithm fortezzaTokenProtectionAlgorithm 
static const unsigned char cvOID_fortezzaTokenProtectionAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x08};
//2.16.840.1.101.2.1.1.9		SDN.700 INFOSEC algorithms sdnsKeyManagementAlgorithm 
static const unsigned char cvOID_sdnsKeyManagementAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x09};
//2.16.840.1.101.2.1.1.10		SDN.700 INFOSEC algorithms.  Formerly known as mosaicKeyManagementAlgorithm fortezzaKeyManagementAlgorithm 
static const unsigned char cvOID_fortezzaKeyManagementAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x0A};
//2.16.840.1.101.2.1.1.11		SDN.700 INFOSEC algorithms sdnsKMandSigAlgorithm 
static const unsigned char cvOID_sdnsKMandSigAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x0B};
//2.16.840.1.101.2.1.1.12		SDN.700 INFOSEC algorithms.  Formerly known as mosaicKMandSigAlgorithm fortezzaKMandSigAlgorithm 
static const unsigned char cvOID_fortezzaKMandSigAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x0C};
//2.16.840.1.101.2.1.1.13		SDN.700 INFOSEC algorithms suiteASignatureAlgorithm 
static const unsigned char cvOID_suiteASignatureAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x0D};
//2.16.840.1.101.2.1.1.14		SDN.700 INFOSEC algorithms suiteAConfidentialityAlgorithm 
static const unsigned char cvOID_suiteAConfidentialityAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x0E};
//2.16.840.1.101.2.1.1.15		SDN.700 INFOSEC algorithms suiteAIntegrityAlgorithm 
static const unsigned char cvOID_suiteAIntegrityAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x0F};
//2.16.840.1.101.2.1.1.16		SDN.700 INFOSEC algorithms suiteATokenProtectionAlgorithm 
static const unsigned char cvOID_suiteATokenProtectionAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x10};
//2.16.840.1.101.2.1.1.17		SDN.700 INFOSEC algorithms suiteAKeyManagementAlgorithm 
static const unsigned char cvOID_suiteAKeyManagementAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x11};
//2.16.840.1.101.2.1.1.18		SDN.700 INFOSEC algorithms suiteAKMandSigAlgorithm 
static const unsigned char cvOID_suiteAKMandSigAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x12};
//2.16.840.1.101.2.1.1.19		SDN.700 INFOSEC algorithms.  Formerly known as mosaicUpdatedSigAlgorithm fortezzaUpdatedSigAlgorithm 
static const unsigned char cvOID_fortezzaUpdatedSigAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x13};
//2.16.840.1.101.2.1.1.20		SDN.700 INFOSEC algorithms.  Formerly known as mosaicKMandUpdSigAlgorithms fortezzaKMandUpdSigAlgorithms 
static const unsigned char cvOID_fortezzaKMandUpdSigAlgorithms [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x14};
//2.16.840.1.101.2.1.1.21		SDN.700 INFOSEC algorithms.  Formerly known as mosaicUpdatedIntegAlgorithm fortezzaUpdatedIntegAlgorithm 
static const unsigned char cvOID_fortezzaUpdatedIntegAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x15};
//2.16.840.1.101.2.1.1.22		SDN.700 INFOSEC algorithms.  Formerly known as mosaicKeyEncryptionAlgorithm keyExchangeAlgorithm 
static const unsigned char cvOID_keyExchangeAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x16};
//2.16.840.1.101.2.1.1.23		SDN.700 INFOSEC algorithms fortezzaWrap80Algorithm 
static const unsigned char cvOID_fortezzaWrap80Algorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x17};
//2.16.840.1.101.2.1.1.24		SDN.700 INFOSEC algorithms kEAKeyEncryptionAlgorithm 
static const unsigned char cvOID_kEAKeyEncryptionAlgorithm [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x18};
//2.16.840.1.101.2.1.2.1		SDN.700 INFOSEC format rfc822MessageFormat 
static const unsigned char cvOID_rfc822MessageFormat [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x01};
//2.16.840.1.101.2.1.2.2		SDN.700 INFOSEC format emptyContent 
static const unsigned char cvOID_emptyContent [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x02};
//2.16.840.1.101.2.1.2.3		SDN.700 INFOSEC format cspContentType 
static const unsigned char cvOID_cspContentType [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x03};
//2.16.840.1.101.2.1.2.42		SDN.700 INFOSEC format mspRev3ContentType 
static const unsigned char cvOID_mspRev3ContentType [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x2A};
//2.16.840.1.101.2.1.2.48		SDN.700 INFOSEC format mspContentType 
static const unsigned char cvOID_mspContentType [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x30};
//2.16.840.1.101.2.1.2.49		SDN.700 INFOSEC format mspRekeyAgentProtocol 
static const unsigned char cvOID_mspRekeyAgentProtocol [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x31};
//2.16.840.1.101.2.1.2.50		SDN.700 INFOSEC format mspMMP 
static const unsigned char cvOID_mspMMP [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x32};
//2.16.840.1.101.2.1.2.66		SDN.700 INFOSEC format mspRev3-1ContentType 
static const unsigned char cvOID_mspRev3_1ContentType [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x42};
//2.16.840.1.101.2.1.2.72		SDN.700 INFOSEC format forwardedMSPMessageBodyPart 
static const unsigned char cvOID_forwardedMSPMessageBodyPart [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x48};
//2.16.840.1.101.2.1.2.73		SDN.700 INFOSEC format mspForwardedMessageParameters 
static const unsigned char cvOID_mspForwardedMessageParameters [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x49};
//2.16.840.1.101.2.1.2.74		SDN.700 INFOSEC format forwardedCSPMsgBodyPart 
static const unsigned char cvOID_forwardedCSPMsgBodyPart [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x50};
//2.16.840.1.101.2.1.2.75		SDN.700 INFOSEC format cspForwardedMessageParameters 
static const unsigned char cvOID_cspForwardedMessageParameters [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x51};
//2.16.840.1.101.2.1.2.76		SDN.700 INFOSEC format mspMMP2 
static const unsigned char cvOID_mspMMP2 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x52};
//2.16.840.1.101.2.1.3.1		SDN.700 INFOSEC policy sdnsSecurityPolicy 
static const unsigned char cvOID_sdnsSecurityPolicy [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x01};
//2.16.840.1.101.2.1.3.2		SDN.700 INFOSEC policy sdnsPRBAC 
static const unsigned char cvOID_sdnsPRBAC [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x02};
//2.16.840.1.101.2.1.3.3		SDN.700 INFOSEC policy mosaicPRBAC 
static const unsigned char cvOID_mosaicPRBAC [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x03};
//2.16.840.1.101.2.1.3.10		SDN.700 INFOSEC policy siSecurityPolicy 
static const unsigned char cvOID_siSecurityPolicy [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A};
//2.16.840.1.101.2.1.3.10.0		SDN.700 INFOSEC policy (obsolete) siNASP 
static const unsigned char cvOID_siNASP [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x00};
//2.16.840.1.101.2.1.3.10.1		SDN.700 INFOSEC policy (obsolete) siELCO 
static const unsigned char cvOID_siELCO [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x01};
//2.16.840.1.101.2.1.3.10.2		SDN.700 INFOSEC policy (obsolete) siTK 
static const unsigned char cvOID_siTK [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x02};
//2.16.840.1.101.2.1.3.10.3		SDN.700 INFOSEC policy (obsolete) siDSAP 
static const unsigned char cvOID_siDSAP [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x03};
//2.16.840.1.101.2.1.3.10.4		SDN.700 INFOSEC policy (obsolete) siSSSS 
static const unsigned char cvOID_siSSSS [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x04};
//2.16.840.1.101.2.1.3.10.5		SDN.700 INFOSEC policy (obsolete) siDNASP 
static const unsigned char cvOID_siDNASP [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x05};
//2.16.840.1.101.2.1.3.10.6		SDN.700 INFOSEC policy (obsolete) siBYEMAN 
static const unsigned char cvOID_siBYEMAN [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x06};
//2.16.840.1.101.2.1.3.10.7		SDN.700 INFOSEC policy (obsolete) siREL-US 
static const unsigned char cvOID_siREL_US [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x07};
//2.16.840.1.101.2.1.3.10.8		SDN.700 INFOSEC policy (obsolete) siREL-AUS 
static const unsigned char cvOID_siREL_AUS [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x08};
//2.16.840.1.101.2.1.3.10.9		SDN.700 INFOSEC policy (obsolete) siREL-CAN 
static const unsigned char cvOID_siREL_CAN [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x09};
//2.16.840.1.101.2.1.3.10.10		SDN.700 INFOSEC policy (obsolete) siREL_UK 
static const unsigned char cvOID_siREL_UK [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x0A};
//2.16.840.1.101.2.1.3.10.11		SDN.700 INFOSEC policy (obsolete) siREL-NZ 
static const unsigned char cvOID_siREL_NZ [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x0B};
//2.16.840.1.101.2.1.3.10.12		SDN.700 INFOSEC policy (obsolete) siGeneric 
static const unsigned char cvOID_siGeneric [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x0C};
//2.16.840.1.101.2.1.3.11		SDN.700 INFOSEC policy genser 
static const unsigned char cvOID_genser [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0B};
//2.16.840.1.101.2.1.3.11.0		SDN.700 INFOSEC policy (obsolete) genserNations 
static const unsigned char cvOID_genserNations [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0B, 0x00};
//2.16.840.1.101.2.1.3.11.1		SDN.700 INFOSEC policy (obsolete) genserComsec 
static const unsigned char cvOID_genserComsec [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0B, 0x01};
//2.16.840.1.101.2.1.3.11.2		SDN.700 INFOSEC policy (obsolete) genserAcquisition 
static const unsigned char cvOID_genserAcquisition [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0B, 0x02};
//2.16.840.1.101.2.1.3.11.3		SDN.700 INFOSEC policy genserSecurityCategories 
static const unsigned char cvOID_genserSecurityCategories [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0B, 0x03};
//2.16.840.1.101.2.1.3.11.3.0		SDN.700 INFOSEC GENSER policy genserTagSetName 
static const unsigned char cvOID_genserTagSetName [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0B, 0x03, 0x00};
//2.16.840.1.101.2.1.3.12		SDN.700 INFOSEC policy defaultSecurityPolicy 
static const unsigned char cvOID_defaultSecurityPolicy [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0C};
//2.16.840.1.101.2.1.3.13		SDN.700 INFOSEC policy capcoMarkings 
static const unsigned char cvOID_capcoMarkings [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0D};
//2.16.840.1.101.2.1.3.13.0		SDN.700 INFOSEC policy CAPCO markings capcoSecurityCategories 
static const unsigned char cvOID_capcoSecurityCategories [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0D, 0x00};
//2.16.840.1.101.2.1.3.13.0.1		SDN.700 INFOSEC policy CAPCO markings capcoTagSetName1 
static const unsigned char cvOID_capcoTagSetName1 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0D, 0x00, 0x01};
//2.16.840.1.101.2.1.3.13.0.2		SDN.700 INFOSEC policy CAPCO markings capcoTagSetName2 
static const unsigned char cvOID_capcoTagSetName2 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0D, 0x00, 0x02};
//2.16.840.1.101.2.1.3.13.0.3		SDN.700 INFOSEC policy CAPCO markings capcoTagSetName3 
static const unsigned char cvOID_capcoTagSetName3 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0D, 0x00, 0x03};
//2.16.840.1.101.2.1.3.13.0.4		SDN.700 INFOSEC policy CAPCO markings capcoTagSetName4 
static const unsigned char cvOID_capcoTagSetName4 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0D, 0x00, 0x04};
//2.16.840.1.101.2.1.5.1		SDN.700 INFOSEC attributes (superseded) sdnsKeyManagementCertificate 
static const unsigned char cvOID_sdnsKeyManagementCertificate [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x01};
//2.16.840.1.101.2.1.5.2		SDN.700 INFOSEC attributes (superseded) sdnsUserSignatureCertificate 
static const unsigned char cvOID_sdnsUserSignatureCertificate [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x02};
//2.16.840.1.101.2.1.5.3		SDN.700 INFOSEC attributes (superseded) sdnsKMandSigCertificate 
static const unsigned char cvOID_sdnsKMandSigCertificate [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x03};
//2.16.840.1.101.2.1.5.4		SDN.700 INFOSEC attributes (superseded) fortezzaKeyManagementCertificate 
static const unsigned char cvOID_fortezzaKeyManagementCertificate [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x04};
//2.16.840.1.101.2.1.5.5		SDN.700 INFOSEC attributes (superseded) fortezzaKMandSigCertificate 
static const unsigned char cvOID_fortezzaKMandSigCertificate [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x05};
//2.16.840.1.101.2.1.5.6		SDN.700 INFOSEC attributes (superseded) fortezzaUserSignatureCertificate 
static const unsigned char cvOID_fortezzaUserSignatureCertificate [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x06};
//2.16.840.1.101.2.1.5.7		SDN.700 INFOSEC attributes (superseded) fortezzaCASignatureCertificate 
static const unsigned char cvOID_fortezzaCASignatureCertificate [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x07};
//2.16.840.1.101.2.1.5.8		SDN.700 INFOSEC attributes (superseded) sdnsCASignatureCertificate 
static const unsigned char cvOID_sdnsCASignatureCertificate [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x08};
//2.16.840.1.101.2.1.5.10		SDN.700 INFOSEC attributes (superseded) auxiliaryVector 
static const unsigned char cvOID_auxiliaryVector [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x0A};
//2.16.840.1.101.2.1.5.11		SDN.700 INFOSEC attributes mlReceiptPolicy 
static const unsigned char cvOID_mlReceiptPolicy [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x0B};
//2.16.840.1.101.2.1.5.12		SDN.700 INFOSEC attributes mlMembership 
static const unsigned char cvOID_mlMembership [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x0C};
//2.16.840.1.101.2.1.5.13		SDN.700 INFOSEC attributes mlAdministrators 
static const unsigned char cvOID_mlAdministrators [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x0D};
//2.16.840.1.101.2.1.5.14		SDN.700 INFOSEC attributes alid 
static const unsigned char cvOID_alid [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x0E};
//2.16.840.1.101.2.1.5.20		SDN.700 INFOSEC attributes janUKMs 
static const unsigned char cvOID_janUKMs [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x14};
//2.16.840.1.101.2.1.5.21		SDN.700 INFOSEC attributes febUKMs 
static const unsigned char cvOID_febUKMs [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x15};
//2.16.840.1.101.2.1.5.22		SDN.700 INFOSEC attributes marUKMs 
static const unsigned char cvOID_marUKMs [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x16};
//2.16.840.1.101.2.1.5.23		SDN.700 INFOSEC attributes aprUKMs 
static const unsigned char cvOID_aprUKMs [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x17};
//2.16.840.1.101.2.1.5.24		SDN.700 INFOSEC attributes mayUKMs 
static const unsigned char cvOID_mayUKMs [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x18};
//2.16.840.1.101.2.1.5.25		SDN.700 INFOSEC attributes junUKMs 
static const unsigned char cvOID_junUKMs [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x19};
//2.16.840.1.101.2.1.5.26		SDN.700 INFOSEC attributes julUKMs 
static const unsigned char cvOID_julUKMs [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x1A};
//2.16.840.1.101.2.1.5.27		SDN.700 INFOSEC attributes augUKMs 
static const unsigned char cvOID_augUKMs [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x1B};
//2.16.840.1.101.2.1.5.28		SDN.700 INFOSEC attributes sepUKMs 
static const unsigned char cvOID_sepUKMs [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x1C};
//2.16.840.1.101.2.1.5.29		SDN.700 INFOSEC attributes octUKMs 
static const unsigned char cvOID_octUKMs [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x1D};
//2.16.840.1.101.2.1.5.30		SDN.700 INFOSEC attributes novUKMs 
static const unsigned char cvOID_novUKMs [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x1E};
//2.16.840.1.101.2.1.5.21		SDN.700 INFOSEC attributes decUKMs 
static const unsigned char cvOID_decUKMs [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x1F};
//2.16.840.1.101.2.1.5.40		SDN.700 INFOSEC attributes metaSDNSckl 
static const unsigned char cvOID_metaSDNSckl [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x28};
//2.16.840.1.101.2.1.5.41		SDN.700 INFOSEC attributes sdnsCKL 
static const unsigned char cvOID_sdnsCKL [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x29};
//2.16.840.1.101.2.1.5.42		SDN.700 INFOSEC attributes metaSDNSsignatureCKL 
static const unsigned char cvOID_metaSDNSsignatureCKL [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x2A};
//2.16.840.1.101.2.1.5.43		SDN.700 INFOSEC attributes sdnsSignatureCKL 
static const unsigned char cvOID_sdnsSignatureCKL [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x2B};
//2.16.840.1.101.2.1.5.44		SDN.700 INFOSEC attributes sdnsCertificateRevocationList 
static const unsigned char cvOID_sdnsCertificateRevocationList [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x2C};
//2.16.840.1.101.2.1.5.45		SDN.700 INFOSEC attributes (superseded) fortezzaCertificateRevocationList 
static const unsigned char cvOID_fortezzaCertificateRevocationList [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x2D};
//2.16.840.1.101.2.1.5.46		SDN.700 INFOSEC attributes fortezzaCKL 
static const unsigned char cvOID_fortezzaCKL [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x2E};
//2.16.840.1.101.2.1.5.47		SDN.700 INFOSEC attributes alExemptedAddressProcessor 
static const unsigned char cvOID_alExemptedAddressProcessor [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x2F};
//2.16.840.1.101.2.1.5.48		SDN.700 INFOSEC attributes (obsolete) guard 
static const unsigned char cvOID_guard [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x30};
//2.16.840.1.101.2.1.5.49		SDN.700 INFOSEC attributes (obsolete) algorithmsSupported 
static const unsigned char cvOID_algorithmsSupported [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x31};
//2.16.840.1.101.2.1.5.50		SDN.700 INFOSEC attributes (obsolete) suiteAKeyManagementCertificate 
static const unsigned char cvOID_suiteAKeyManagementCertificate [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x32};
//2.16.840.1.101.2.1.5.51		SDN.700 INFOSEC attributes (obsolete) suiteAKMandSigCertificate 
static const unsigned char cvOID_suiteAKMandSigCertificate [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x33};
//2.16.840.1.101.2.1.5.52		SDN.700 INFOSEC attributes (obsolete) suiteAUserSignatureCertificate 
static const unsigned char cvOID_suiteAUserSignatureCertificate [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x34};
//2.16.840.1.101.2.1.5.53		SDN.700 INFOSEC attributes prbacInfo 
static const unsigned char cvOID_prbacInfo [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x35};
//2.16.840.1.101.2.1.5.54		SDN.700 INFOSEC attributes prbacCAstatic constraints 
static const unsigned char cvOID_prbacCAconstraints [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x36};
//2.16.840.1.101.2.1.5.55		SDN.700 INFOSEC attributes sigOrKMPrivileges 
static const unsigned char cvOID_sigOrKMPrivileges [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x37};
//2.16.840.1.101.2.1.5.56		SDN.700 INFOSEC attributes commPrivileges 
static const unsigned char cvOID_commPrivileges [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x38};
//2.16.840.1.101.2.1.5.57		SDN.700 INFOSEC attributes labeledAttribute 
static const unsigned char cvOID_labeledAttribute [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x39};
//2.16.840.1.101.2.1.5.58		SDN.700 INFOSEC attributes (obsolete) policyInformationFile 
static const unsigned char cvOID_policyInformationFile [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x3A};
//2.16.840.1.101.2.1.5.59		SDN.700 INFOSEC attributes secPolicyInformationFile 
static const unsigned char cvOID_secPolicyInformationFile [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x3B};
//2.16.840.1.101.2.1.5.60		SDN.700 INFOSEC attributes cAClearancestatic constraint 
static const unsigned char cvOID_cAClearanceconstraint [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x3C};
//2.16.840.1.101.2.1.7.1		SDN.700 INFOSEC extensions cspExtns 
static const unsigned char cvOID_cspExtns [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x07, 0x01};
//2.16.840.1.101.2.1.7.1.0		SDN.700 INFOSEC extensions cspCsExtn 
static const unsigned char cvOID_cspCsExtn [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x07, 0x01, 0x00};
//2.16.840.1.101.2.1.8.1		SDN.700 INFOSEC security category mISSISecurityCategories 
static const unsigned char cvOID_mISSISecurityCategories [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x08, 0x01};
//2.16.840.1.101.2.1.8.2		SDN.700 INFOSEC security category standardSecurityLabelPrivileges 
static const unsigned char cvOID_standardSecurityLabelPrivileges [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x08, 0x02};
//2.16.840.1.101.2.1.10.1		SDN.700 INFOSEC privileges sigPrivileges 
static const unsigned char cvOID_sigPrivileges [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0A, 0x01};
//2.16.840.1.101.2.1.10.2		SDN.700 INFOSEC privileges kmPrivileges 
static const unsigned char cvOID_kmPrivileges [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0A, 0x02};
//2.16.840.1.101.2.1.10.3		SDN.700 INFOSEC privileges namedTagSetPrivilege 
static const unsigned char cvOID_namedTagSetPrivilege [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0A, 0x03};
//2.16.840.1.101.2.1.11.1		SDN.700 INFOSEC certificate policy ukDemo 
static const unsigned char cvOID_ukDemo [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0B, 0x01};
//2.16.840.1.101.2.1.11.2		SDN.700 INFOSEC certificate policy usDODClass2 
static const unsigned char cvOID_usDODClass2 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0B, 0x02};
//2.16.840.1.101.2.1.11.3		SDN.700 INFOSEC certificate policy usMediumPilot 
static const unsigned char cvOID_usMediumPilot [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0B, 0x03};
//2.16.840.1.101.2.1.11.4		SDN.700 INFOSEC certificate policy usDODClass4 
static const unsigned char cvOID_usDODClass4 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0B, 0x04};
//2.16.840.1.101.2.1.11.5		SDN.700 INFOSEC certificate policy usDODClass3 
static const unsigned char cvOID_usDODClass3 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0B, 0x05};
//2.16.840.1.101.2.1.11.6		SDN.700 INFOSEC certificate policy usDODClass5 
static const unsigned char cvOID_usDODClass5 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0B, 0x06};
//2.16.840.1.101.2.1.12.0		SDN.700 INFOSEC test objects testSecurityPolicy 
static const unsigned char cvOID_testSecurityPolicy [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00};
//2.16.840.1.101.2.1.12.0.1		SDN.700 INFOSEC test objects tsp1 
static const unsigned char cvOID_tsp1 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x01};
//2.16.840.1.101.2.1.12.0.1.0		SDN.700 INFOSEC test objects tsp1SecurityCategories 
static const unsigned char cvOID_tsp1SecurityCategories [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x01, 0x00};
//2.16.840.1.101.2.1.12.0.1.0.0		SDN.700 INFOSEC test objects tsp1TagSetZero 
static const unsigned char cvOID_tsp1TagSetZero [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x01, 0x00, 0x00};
//2.16.840.1.101.2.1.12.0.1.0.1		SDN.700 INFOSEC test objects tsp1TagSetOne 
static const unsigned char cvOID_tsp1TagSetOne [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x01, 0x00, 0x01};
//2.16.840.1.101.2.1.12.0.1.0.2		SDN.700 INFOSEC test objects tsp1TagSetTwo 
static const unsigned char cvOID_tsp1TagSetTwo [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x01, 0x00, 0x02};
//2.16.840.1.101.2.1.12.0.2		SDN.700 INFOSEC test objects tsp2 
static const unsigned char cvOID_tsp2 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x02};
//2.16.840.1.101.2.1.12.0.2.0		SDN.700 INFOSEC test objects tsp2SecurityCategories 
static const unsigned char cvOID_tsp2SecurityCategories [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x02, 0x00};
//2.16.840.1.101.2.1.12.0.2.0.0		SDN.700 INFOSEC test objects tsp2TagSetZero 
static const unsigned char cvOID_tsp2TagSetZero [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x02, 0x00, 0x00};
//2.16.840.1.101.2.1.12.0.2.0.1		SDN.700 INFOSEC test objects tsp2TagSetOne 
static const unsigned char cvOID_tsp2TagSetOne [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x02, 0x00, 0x01};
//2.16.840.1.101.2.1.12.0.2.0.2		SDN.700 INFOSEC test objects tsp2TagSetTwo 
static const unsigned char cvOID_tsp2TagSetTwo [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x02, 0x00, 0x02};
//2.16.840.1.101.2.1.12.0.3		SDN.700 INFOSEC test objects kafka 
static const unsigned char cvOID_kafka [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x03};
//2.16.840.1.101.2.1.12.0.3.0		SDN.700 INFOSEC test objects kafkaSecurityCategories 
static const unsigned char cvOID_kafkaSecurityCategories [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x03, 0x00};
//2.16.840.1.101.2.1.12.0.3.0.1		SDN.700 INFOSEC test objects kafkaTagSetName1 
static const unsigned char cvOID_kafkaTagSetName1 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x03, 0x00, 0x01};
//2.16.840.1.101.2.1.12.0.3.0.2		SDN.700 INFOSEC test objects kafkaTagSetName2 
static const unsigned char cvOID_kafkaTagSetName2 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x03, 0x00, 0x02};
//2.16.840.1.101.2.1.12.0.3.0.3		SDN.700 INFOSEC test objects kafkaTagSetName3 
static const unsigned char cvOID_kafkaTagSetName3 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x03, 0x00, 0x03};
//2.16.840.1.101.2.1.12.1.1		SDN.700 INFOSEC test objects tcp1 
static const unsigned char cvOID_tcp1 [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x01, 0x01};
//2.16.840.1.101.3.1		CSOR GAK slabel 
static const unsigned char cvOID_slabel [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x01};
//2.16.840.1.101.3.2		CSOR GAK pki 
static const unsigned char cvOID_pki [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02};
//2.16.840.1.101.3.2.1		CSOR GAK policy GAK policyIdentifier 
static const unsigned char cvOID_GAK_policyIdentifier [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x01};
//2.16.840.1.101.3.2.2		CSOR GAK extended key usage GAK 
static const unsigned char cvOID_GAK [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x02};
//2.16.840.1.101.3.2.2.1		CSOR GAK extended key usage kRAKey 
static const unsigned char cvOID_kRAKey [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x02, 0x01};
//2.16.840.1.101.3.2.3		CSOR GAK extensions extensions 
static const unsigned char cvOID_extensions [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x03};
//2.16.840.1.101.3.2.3.1		CSOR GAK extensions kRTechnique 
static const unsigned char cvOID_kRTechnique [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x03, 0x01};
//2.16.840.1.101.3.2.3.2		CSOR GAK extensions kRecoveryCapable 
static const unsigned char cvOID_kRecoveryCapable [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x03, 0x02};
//2.16.840.1.101.3.2.3.3		CSOR GAK extensions kR 
static const unsigned char cvOID_kR [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x03, 0x03};
//2.16.840.1.101.3.2.4		CSOR GAK keyrecoveryschemes 
static const unsigned char cvOID_keyrecoveryschemes [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x04};
//2.16.840.1.101.3.2.5		CSOR GAK krapola 
static const unsigned char cvOID_krapola [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x05};
//2.16.840.1.101.3.3		CSOR GAK arpa 
static const unsigned char cvOID_arpa [] = {  0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x03};
//2.16.840.1.113719.1.9		Novell pki 
static const unsigned char cvOID_pki_Novell [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x37, 0x01, 0x09};
//2.16.840.1.113719.1.9.4		Novell PKI pkiAttributeType 
static const unsigned char cvOID_pkiAttributeType [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x37, 0x01, 0x09, 0x04};
//2.16.840.1.113719.1.9.4.1		Novell PKI attribute type registeredAttributes 
static const unsigned char cvOID_registeredAttributes [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x37, 0x01, 0x09, 0x04, 0x01};
//2.16.840.1.113719.1.9.4.2		Novell PKI attribute type relianceLimit 
static const unsigned char cvOID_relianceLimit [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x37, 0x01, 0x09, 0x04, 0x02};
//2.16.840.1.113730.1		Netscape cert-extension 
static const unsigned char cvOID_cert_extension [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01};
//2.16.840.1.113730.1.1		Netscape certificate extension netscape-cert-type 
static const unsigned char cvOID_netscape_cert_type [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x01};
//2.16.840.1.113730.1.2		Netscape certificate extension netscape-base-url 
static const unsigned char cvOID_netscape_base_url [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x02};
//2.16.840.1.113730.1.3		Netscape certificate extension netscape-revocation-url 
static const unsigned char cvOID_netscape_revocation_url [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x03};
//2.16.840.1.113730.1.4		Netscape certificate extension netscape-ca-revocation-url 
static const unsigned char cvOID_netscape_ca_revocation_url [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x04};
//2.16.840.1.113730.1.7		Netscape certificate extension netscape-cert-renewal-url 
static const unsigned char cvOID_netscape_cert_renewal_url [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x07};
//2.16.840.1.113730.1.8		Netscape certificate extension netscape-ca-policy-url 
static const unsigned char cvOID_netscape_ca_policy_url [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x08};
//2.16.840.1.113730.1.9		Netscape certificate extension HomePage-url 
static const unsigned char cvOID_HomePage_url [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x09};
//2.16.840.1.113730.1.10		Netscape certificate extension EntityLogo 
static const unsigned char cvOID_EntityLogo [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x0A};
//2.16.840.1.113730.1.11		Netscape certificate extension UserPicture 
static const unsigned char cvOID_UserPicture [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x0B};
//2.16.840.1.113730.1.12		Netscape certificate extension netscape-ssl-server-name 
static const unsigned char cvOID_netscape_ssl_server_name [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x0C};
//2.16.840.1.113730.1.13		Netscape certificate extension netscape-comment 
static const unsigned char cvOID_netscape_comment [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x0D};
//2.16.840.1.113730.2		Netscape data-type 
static const unsigned char cvOID_data_type [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02};
//2.16.840.1.113730.2.1		Netscape data type dataGIF 
static const unsigned char cvOID_dataGIF [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02, 0x01};
//2.16.840.1.113730.2.2		Netscape data type dataJPEG 
static const unsigned char cvOID_dataJPEG [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02, 0x02};
//2.16.840.1.113730.2.3		Netscape data type dataURL 
static const unsigned char cvOID_dataURL [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02, 0x03};
//2.16.840.1.113730.2.4		Netscape data type dataHTML 
static const unsigned char cvOID_dataHTML [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02, 0x04};
//2.16.840.1.113730.2.5		Netscape data type certSequence 
static const unsigned char cvOID_certSequence [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02, 0x05};
//2.16.840.1.113730.2.6		Netscape certificate extension certURL 
static const unsigned char cvOID_certURL [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02, 0x06};
//2.16.840.1.113730.3		Netscape directory 
static const unsigned char cvOID_directory [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03};
//2.16.840.1.113730.3.1		Netscape directory ldapDefinitions 
static const unsigned char cvOID_ldapDefinitions [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03, 0x01};
//2.16.840.1.113730.3.1.1		Netscape LDAP definitions carLicense 
static const unsigned char cvOID_carLicense [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03, 0x01, 0x01};
//2.16.840.1.113730.3.1.2		Netscape LDAP definitions departmentNumber 
static const unsigned char cvOID_departmentNumber [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03, 0x01, 0x02};
//2.16.840.1.113730.3.1.3		Netscape LDAP definitions employeeNumber 
static const unsigned char cvOID_employeeNumber [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03, 0x01, 0x03};
//2.16.840.1.113730.3.1.4		Netscape LDAP definitions employeeType 
static const unsigned char cvOID_employeeType [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03, 0x01, 0x04};
//2.16.840.1.113730.3.2.2		Netscape LDAP definitions inetOrgPerson 
static const unsigned char cvOID_inetOrgPerson [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03, 0x02, 0x02};
//2.16.840.1.113730.4.1		Netscape serverGatedCrypto 
static const unsigned char cvOID_serverGatedCrypto_Netscape [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x04, 0x01};
//2.16.840.1.113733.1.6.3		Verisign Unknown Verisign extension 
static const unsigned char cvOID_Unknown_Verisign_extension_1 [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x45, 0x01, 0x06, 0x03};
//2.16.840.1.113733.1.6.6		Verisign Unknown Verisign extension 
static const unsigned char cvOID_Unknown_Verisign_extension_2 [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x45, 0x01, 0x06, 0x06};
//2.16.840.1.113733.1.7.1.1		Verisign Verisign certificatePolicy 
static const unsigned char cvOID_Verisign_certificatePolicy [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x45, 0x01, 0x07, 0x01, 0x01};
//2.16.840.1.113733.1.7.1.1.1		Verisign Unknown Verisign policy qualifier 
static const unsigned char cvOID_Unknown_Verisign_policy_qualifier_1 [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x45, 0x01, 0x07, 0x01, 0x01, 0x01};
//2.16.840.1.113733.1.7.1.1.2		Verisign Unknown Verisign policy qualifier 
static const unsigned char cvOID_Unknown_Verisign_policy_qualifier_2 [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x45, 0x01, 0x07, 0x01, 0x01, 0x02};
//2.16.840.1.113733.1.8.1		Verisign Verisign SGC CA? 
static const unsigned char cvOID_Verisign_SGC_CA [] = {  0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x45, 0x01, 0x08, 0x01};
//2.23.42.0		SET contentType 
static const unsigned char cvOID_contentType_SET [] = {  0x67, 0x2A, 0x00};
//2.23.42.0.0		SET contentType PANData 
static const unsigned char cvOID_PANData [] = {  0x67, 0x2A, 0x00, 0x00};
//2.23.42.0.1		SET contentType PANToken 
static const unsigned char cvOID_PANToken [] = {  0x67, 0x2A, 0x00, 0x01};
//2.23.42.0.2		SET contentType PANOnly 
static const unsigned char cvOID_PANOnly [] = {  0x67, 0x2A, 0x00, 0x02};
//2.23.42.1		SET msgExt 
static const unsigned char cvOID_msgExt [] = {  0x67, 0x2A, 0x01};
//2.23.42.2		SET field 
static const unsigned char cvOID_field [] = {  0x67, 0x2A, 0x02};
//2.23.42.2.0		SET field fullName 
static const unsigned char cvOID_fullName [] = {  0x67, 0x2A, 0x02, 0x00};
//2.23.42.2.1		SET field givenName 
static const unsigned char cvOID_givenName_SET [] = {  0x67, 0x2A, 0x02, 0x01};
//2.23.42.2.2		SET field familyName 
static const unsigned char cvOID_familyName [] = {  0x67, 0x2A, 0x02, 0x02};
//2.23.42.2.3		SET field birthFamilyName 
static const unsigned char cvOID_birthFamilyName [] = {  0x67, 0x2A, 0x02, 0x03};
//2.23.42.2.4		SET field placeName 
static const unsigned char cvOID_placeName [] = {  0x67, 0x2A, 0x02, 0x04};
//2.23.42.2.5		SET field identificationNumber 
static const unsigned char cvOID_identificationNumber [] = {  0x67, 0x2A, 0x02, 0x05};
//2.23.42.2.6		SET field month 
static const unsigned char cvOID_month [] = {  0x67, 0x2A, 0x02, 0x06};
//2.23.42.2.7		SET field date 
static const unsigned char cvOID_date [] = {  0x67, 0x2A, 0x02, 0x07};
//2.23.42.2.8		SET field address 
static const unsigned char cvOID_address [] = {  0x67, 0x2A, 0x02, 0x08};
//2.23.42.2.9		SET field telephone 
static const unsigned char cvOID_telephone [] = {  0x67, 0x2A, 0x02, 0x09};
//2.23.42.2.10		SET field amount 
static const unsigned char cvOID_amount [] = {  0x67, 0x2A, 0x02, 0x0A};
//2.23.42.2.7.11		SET field accountNumber 
static const unsigned char cvOID_accountNumber [] = {  0x67, 0x2A, 0x02, 0x0B};
//2.23.42.2.7.12		SET field passPhrase 
static const unsigned char cvOID_passPhrase [] = {  0x67, 0x2A, 0x02, 0x0C};
//2.23.42.3		SET attribute 
static const unsigned char cvOID_attribute_SET [] = {  0x67, 0x2A, 0x03};
//2.23.42.3.0		SET attribute cert 
static const unsigned char cvOID_cert_SET [] = {  0x67, 0x2A, 0x03, 0x00};
//2.23.42.3.0.0		SET cert attribute rootKeyThumb 
static const unsigned char cvOID_rootKeyThumb [] = {  0x67, 0x2A, 0x03, 0x00, 0x00};
//2.23.42.3.0.1		SET cert attribute additionalPolicy 
static const unsigned char cvOID_additionalPolicy [] = {  0x67, 0x2A, 0x03, 0x00, 0x01};
//2.23.42.4		SET algorithm 
static const unsigned char cvOID_algorithm_SET [] = {  0x67, 0x2A, 0x04};
//2.23.42.5		SET policy 
static const unsigned char cvOID_policy_SET [] = {  0x67, 0x2A, 0x05};
//2.23.42.5.0		SET policy root 
static const unsigned char cvOID_root [] = {  0x67, 0x2A, 0x05, 0x00};
//2.23.42.6		SET module 
static const unsigned char cvOID_module_SET [] = {  0x67, 0x2A, 0x06};
//2.23.42.7		SET certExt 
static const unsigned char cvOID_certExt [] = {  0x67, 0x2A, 0x07};
//2.23.42.7.0		SET cert extension hashedRootKey 
static const unsigned char cvOID_hashedRootKey [] = {  0x67, 0x2A, 0x07, 0x00};
//2.23.42.7.1		SET cert extension certificateType 
static const unsigned char cvOID_certificateType_SET [] = {  0x67, 0x2A, 0x07, 0x01};
//2.23.42.7.2		SET cert extension merchantData 
static const unsigned char cvOID_merchantData [] = {  0x67, 0x2A, 0x07, 0x02};
//2.23.42.7.3		SET cert extension cardCertRequired 
static const unsigned char cvOID_cardCertRequired [] = {  0x67, 0x2A, 0x07, 0x03};
//2.23.42.7.4		SET cert extension tunneling 
static const unsigned char cvOID_tunneling [] = {  0x67, 0x2A, 0x07, 0x04};
//2.23.42.7.5		SET cert extension setExtensions 
static const unsigned char cvOID_setExtensions [] = {  0x67, 0x2A, 0x07, 0x05};
//2.23.42.7.6		SET cert extension setQualifier 
static const unsigned char cvOID_setQualifier [] = {  0x67, 0x2A, 0x07, 0x06};
//2.23.42.8		SET brand 
static const unsigned char cvOID_brand [] = {  0x67, 0x2A, 0x08};
//2.23.42.8.1		SET brand IATA-ATA 
static const unsigned char cvOID_IATA_ATA [] = {  0x67, 0x2A, 0x08, 0x01};
//2.23.42.8.4		SET brand VISA 
static const unsigned char cvOID_VISA [] = {  0x67, 0x2A, 0x08, 0x04};
//2.23.42.8.5		SET brand MasterCard 
static const unsigned char cvOID_MasterCard [] = {  0x67, 0x2A, 0x08, 0x05};
//2.23.42.8.30		SET brand Diners 
static const unsigned char cvOID_Diners [] = {  0x67, 0x2A, 0x08, 0x1E};
//2.23.42.8.34		SET brand AmericanExpress 
static const unsigned char cvOID_AmericanExpress [] = {  0x67, 0x2A, 0x08, 0x22};
//2.23.42.8.6011		SET brand Novus 
static const unsigned char cvOID_Novus [] = {  0x67, 0x2A, 0x08, 0xAE, 0x7B};
//2.23.42.9		SET vendor 
static const unsigned char cvOID_vendor [] = {  0x67, 0x2A, 0x09};
//2.23.42.9.0		SET vendor GlobeSet 
static const unsigned char cvOID_GlobeSet [] = {  0x67, 0x2A, 0x09, 0x00};
//2.23.42.9.1		SET vendor IBM 
static const unsigned char cvOID_IBM [] = {  0x67, 0x2A, 0x09, 0x01};
//2.23.42.9.2		SET vendor CyberCash 
static const unsigned char cvOID_CyberCash [] = {  0x67, 0x2A, 0x09, 0x02};
//2.23.42.9.3		SET vendor Terisa 
static const unsigned char cvOID_Terisa [] = {  0x67, 0x2A, 0x09, 0x03};
//2.23.42.9.4		SET vendor RSADSI 
static const unsigned char cvOID_RSADSI [] = {  0x67, 0x2A, 0x09, 0x04};
//2.23.42.9.5		SET vendor VeriFone 
static const unsigned char cvOID_VeriFone [] = {  0x67, 0x2A, 0x09, 0x05};
//2.23.42.9.6		SET vendor TrinTech 
static const unsigned char cvOID_TrinTech [] = {  0x67, 0x2A, 0x09, 0x06};
//2.23.42.9.7		SET vendor BankGate 
static const unsigned char cvOID_BankGate [] = {  0x67, 0x2A, 0x09, 0x07};
//2.23.42.9.8		SET vendor GTE 
static const unsigned char cvOID_GTE [] = {  0x67, 0x2A, 0x09, 0x08};
//2.23.42.9.9		SET vendor CompuSource 
static const unsigned char cvOID_CompuSource [] = {  0x67, 0x2A, 0x09, 0x09};
//2.23.42.9.10		SET vendor Griffin 
static const unsigned char cvOID_Griffin [] = {  0x67, 0x2A, 0x09, 0x0A};
//2.23.42.9.11		SET vendor Certicom 
static const unsigned char cvOID_Certicom [] = {  0x67, 0x2A, 0x09, 0x0B};
//2.23.42.9.12		SET vendor OSS 
static const unsigned char cvOID_OSS [] = {  0x67, 0x2A, 0x09, 0x0C};
//2.23.42.9.13		SET vendor TenthMountain 
static const unsigned char cvOID_TenthMountain [] = {  0x67, 0x2A, 0x09, 0x0D};
//2.23.42.9.14		SET vendor Antares 
static const unsigned char cvOID_Antares [] = {  0x67, 0x2A, 0x09, 0x0E};
//2.23.42.9.15		SET vendor ECC 
static const unsigned char cvOID_ECC [] = {  0x67, 0x2A, 0x09, 0x0F};
//2.23.42.9.16		SET vendor Maithean 
static const unsigned char cvOID_Maithean [] = {  0x67, 0x2A, 0x09, 0x10};
//2.23.42.9.17		SET vendor Netscape 
static const unsigned char cvOID_Netscape [] = {  0x67, 0x2A, 0x09, 0x11};
//2.23.42.9.18		SET vendor Verisign 
static const unsigned char cvOID_Verisign [] = {  0x67, 0x2A, 0x09, 0x12};
//2.23.42.9.19		SET vendor BlueMoney 
static const unsigned char cvOID_BlueMoney [] = {  0x67, 0x2A, 0x09, 0x13};
//2.23.42.9.20		SET vendor Lacerte 
static const unsigned char cvOID_Lacerte [] = {  0x67, 0x2A, 0x09, 0x14};
//2.23.42.9.21		SET vendor Fujitsu 
static const unsigned char cvOID_Fujitsu [] = {  0x67, 0x2A, 0x09, 0x15};
//2.23.42.9.22		SET vendor eLab 
static const unsigned char cvOID_eLab [] = {  0x67, 0x2A, 0x09, 0x16};
//2.23.42.9.23		SET vendor Entrust 
static const unsigned char cvOID_Entrust [] = {  0x67, 0x2A, 0x09, 0x17};
//2.23.42.9.24		SET vendor VIAnet 
static const unsigned char cvOID_VIAnet [] = {  0x67, 0x2A, 0x09, 0x18};
//2.23.42.9.25		SET vendor III 
static const unsigned char cvOID_III [] = {  0x67, 0x2A, 0x09, 0x19};
//2.23.42.9.26		SET vendor OpenMarket 
static const unsigned char cvOID_OpenMarket [] = {  0x67, 0x2A, 0x09, 0x1A};
//2.23.42.9.27		SET vendor Lexem 
static const unsigned char cvOID_Lexem [] = {  0x67, 0x2A, 0x09, 0x1B};
//2.23.42.9.28		SET vendor Intertrader 
static const unsigned char cvOID_Intertrader [] = {  0x67, 0x2A, 0x09, 0x1C};
//2.23.42.9.29		SET vendor Persimmon 
static const unsigned char cvOID_Persimmon [] = {  0x67, 0x2A, 0x09, 0x1D};
//2.23.42.9.30		SET vendor NABLE 
static const unsigned char cvOID_NABLE [] = {  0x67, 0x2A, 0x09, 0x1E};
//2.23.42.9.31		SET vendor espace-net 
static const unsigned char cvOID_espace_net [] = {  0x67, 0x2A, 0x09, 0x1F};
//2.23.42.9.32		SET vendor Hitachi 
static const unsigned char cvOID_Hitachi [] = {  0x67, 0x2A, 0x09, 0x20};
//2.23.42.9.33		SET vendor Microsoft 
static const unsigned char cvOID_Microsoft [] = {  0x67, 0x2A, 0x09, 0x21};
//2.23.42.9.34		SET vendor NEC 
static const unsigned char cvOID_NEC [] = {  0x67, 0x2A, 0x09, 0x22};
//2.23.42.9.35		SET vendor Mitsubishi 
static const unsigned char cvOID_Mitsubishi [] = {  0x67, 0x2A, 0x09, 0x23};
//2.23.42.9.36		SET vendor NCR 
static const unsigned char cvOID_NCR [] = {  0x67, 0x2A, 0x09, 0x24};
//2.23.42.9.37		SET vendor e-COMM 
static const unsigned char cvOID_e_COMM [] = {  0x67, 0x2A, 0x09, 0x25};
//2.23.42.9.38		SET vendor Gemplus 
static const unsigned char cvOID_Gemplus [] = {  0x67, 0x2A, 0x09, 0x26};
//2.23.42.10		SET national 
static const unsigned char cvOID_national [] = {  0x67, 0x2A, 0x0A};
//2.23.42.10.192		SET national Japan 
static const unsigned char cvOID_Japan [] = {  0x67, 0x2A, 0x0A, 0x81, 0x40};
//2.54.1775.2		SET.  Deprecated, use (2 23 42 7 0) instead hashedRootKey 
static const unsigned char cvOID_hashedRootKey_old [] = {  0x86, 0x8D, 0x6F, 0x02};
//2.54.1775.3		SET.  Deprecated, use (2 23 42 7 0) instead certificateType 
static const unsigned char cvOID_certificateType_old [] = {  0x86, 0x8D, 0x6F, 0x03};
//2.54.1775.4		SET.  Deprecated, use (2 23 42 7 0) instead merchantData 
static const unsigned char cvOID_merchantData_old [] = {  0x86, 0x8D, 0x6F, 0x04};
//2.54.1775.5		SET.  Deprecated, use (2 23 42 7 0) instead cardCertRequired 
static const unsigned char cvOID_cardCertRequired_old [] = {  0x86, 0x8D, 0x6F, 0x05};
//2.54.1775.6		SET.  Deprecated, use (2 23 42 7 0) instead tunneling 
static const unsigned char cvOID_tunneling_old [] = {  0x86, 0x8D, 0x6F, 0x06};
//2.54.1775.7		SET.  Deprecated, use (2 23 42 7 0) instead setQualifier 
static const unsigned char cvOID_setQualifier_old [] = {  0x86, 0x8D, 0x6F, 0x07};
//2.54.1775.99		SET.  Deprecated, use (2 23 42 7 0) instead set-data 
static const unsigned char cvOID_set_data_old [] = {  0x86, 0x8D, 0x6F, 0x63};

#ifdef _MSC_VER
#pragma warning(default : 4305)
#pragma warning(default : 4309)
#endif

#endif

