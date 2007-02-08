//////////////////////////////////////////////////////////////////////////////////
// Name:      actInit.h
// Product:   cv act library
// Purpose:   initialize the map entries of the objects
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
// remarks:
//			  declare NO_OLD_SCARD: no old smartcard interface required
//			  declare NO_SMARTCARD: no smartcard support required. 
//									NO_SMARTCARD implicits NO_OLD_SCARD
//////////////////////////////////////////////////////////////////////////////////

#ifndef actInit_h
#define actInit_h

#include "actKeyKit.h"
#include "actKeyReg.h"
#include "actBlockCipherKit.h"
#include "actBlockCipherReg.h"
#include "actBlockCipherModeReg.h"
#include "actBlockCipherModeKit.h"
#include "actStreamCipherKit.h"
#include "actStreamCipherReg.h"
#include "actHashKit.h"
#include "actHashReg.h"
#include "actEMSAReg.h"
#include "actEMSAKit.h"
#include "actDerivatorReg.h"
#include "actDerivatorKit.h"
#include "actPaddingReg.h"
#include "actPaddingKit.h"
#include "actCertificateReg.h"
#include "actCertificateKit.h"
#include "actX509KeyReg.h"
#include "actX509SignReg.h"
#include "actX509SignHashReg.h"
#include "actX509Kit.h"
#include "actDefaultRNG.h"
#include "actRNGKit.h"
#ifndef NO_SMARTCARD
	#include "actSCardOSReg.h"
	#include "actSCardOSKit.h"
	#include "actSCardTokenReg.h"
	#include "actSCardTokenKit.h"
	#include "actSubsystemReg.h"
	#include "actSubsystemKit.h"
	#include "actJCAppletKit.h"
	#include "actJCAppletReg.h"
#endif // NO_SMARTCARD

namespace act
{
	// ------------------------------------------------------------------------
	const KeyMapEntry KeyMap[] =
	{
		{ "BlockCipher" , CreateBlockCipherKey },
		{ "StreamCipher" , CreateStreamCipherKey },

		{ "IES" , CreateIESKey },
		{ "DSA" , CreateDSAKey }, 
		{ "RSA" , CreateRSAKey },
		{ "ECDSA" , CreateECDSAKey },
		{ "ECGDSA" , CreateECGDSAKey },

		{ "DH",	CreateDHKey },
		{ "ECDH",	CreateECDHKey },
	
		{ "HashMAC", CreateHashMACKey },
		{ "CBCMAC", CreateCBCMACKey },
		{ "SecretKeyMAC", CreateSecretKeyMACKey },
		{ "RetailCFBMAC", CreateRetailCFBMACKey },
#if !defined (NO_SMARTCARD) && !defined (NO_OLD_SCARD)
		{ "SmartCard" , CreateSCardKey },
#endif
		{ 0, 0}
	};

	// ------------------------------------------------------------------------
	const BlockCipherMapEntry BlockCipherMap[]= 
	{
		{ "AES" , CreateRijndael },
		{ "DES" , CreateDES },
		{ "TripleDES" , CreateTripleDES },
		{ "CAST128" , CreateCAST128 },
		{ "BlowFish" , CreateBlowFish },
		{ "Mars" , CreateMars },
		{ "Serpent" , CreateSerpent },
		{ "Rijndael" , CreateRijndael },
		{ "TwoFish" , CreateTwoFish },
		{ "RC2" , CreateRC2 },
		//{ "RC6" , CreateRC6 },
		{ 0 , 0 }
	};

	// ------------------------------------------------------------------------
	const BlockCipherModeMapEntry BlockCipherModeMap[]= 
	{
		{ "ECB", CreateECBMode },
		{ "CBC", CreateCBCMode },
		{ "CFB", CreateCFBMode },
		{ 0 , 0 }
	};

	// ------------------------------------------------------------------------
	const StreamCipherMapEntry StreamCipherMap[]= 
	{
		{ "ARC4" , CreateARC4 },
		{ 0 , 0 }
	};

	// ------------------------------------------------------------------------
	const HashMapEntry HashMap[]= 
	{
		{ "MD2" , CreateMD2 },
		{ "MD4" , CreateMD4 },
		{ "MD5" , CreateMD5 },
		{ "RIPEMD128" , CreateRipemd128 },
		{ "RIPEMD160" , CreateRipemd160 },
		{ "SHA0" , CreateSHA0 },
		{ "SHA1" , CreateSHA1 },
		{ "SHA224" , CreateSHA224 },
		{ "SHA256" , CreateSHA256 },
		{ "SHA384" , CreateSHA384 },
		{ "SHA512" , CreateSHA512 },
		{ "DummyHash" , CreateDummyHash },
		{ 0 , 0 }
	};

	// ------------------------------------------------------------------------
	const EMSAMapEntry EMSAMap[]= 
	{
		{ "EMSA1", CreateEMSA1 },
		{ "PKCS1V1_5EMSA", CreatePKCS1V1_5EMSA },
		{ "TLS_EMSA", CreateTLS_EMSA},
		{ "PKCS1_PSS_EMSA", CreatePKCS1_PSS_EMSA},
		{ 0 , 0 }
	};

	// ------------------------------------------------------------------------
	const DerivatorMapEntry DerivatorMap[]= 
	{
		{ "KDF1", CreateKDF1 },
		{ 0 , 0 }
	};

	// ------------------------------------------------------------------------
	const PaddingMapEntry PaddingMap[]= 
	{
		{ "PKCS5", CreatePKCS5Pad },
		{ "RSAES", CreatePKCS1V1_5EMEPad },
		{ "ISO", CreateOneAndZerosPad },
		{ "ISO9796", CreateISO9796Pad },
		{ "NOPAD", CreateNoPad },
		{ 0 , 0 }
	};

	// ------------------------------------------------------------------------
	const CertificateMapEntry CertificateMap[]= {
		{ "X509", CreateX509Certificate },
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const CRLMapEntry CRLMap[]= {
		{ "X509", CreateX509CRL },
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const X509KeyMapEntry X509KeyMap[]= {
		{ "1.2.840.113549.1.1.1", CreateRSAKey, X509ToRSA, RSAToX509 },
		{ "2.5.8.1.1", CreateRSAKey, X509ToRSA, RSAToX509 },
		{ "1.2.840.10040.4.1", CreateDSAKey, X509ToDSA, DSAToX509 },
		{ "1.3.14.3.2.20", CreateDSAKey, X509ToDSA, DSAToX509 },
		{ "1.3.14.3.2.12", CreateDSAKey, X509ToDSA, DSAToX509 },	// secude DSA oid
		{ "1.2.840.10046.2.1", CreateDHKey, X509ToDH, DHToX509 },
		{ "1.2.840.10045.2.1", CreateECDSAKey, X509ToECDSA, ECDSAToX509 },
		{ "1.2.840.10045.2.1", CreateECDHKey, X509ToECDSA, ECDSAToX509 },
#if !defined (NO_SMARTCARD) && !defined (NO_OLD_SCARD)
		{ "0.0.0.0.0.0", CreateSCardKey, 0, SCardToX509 },
#endif
		{0,0,0,0}
	};

	// ------------------------------------------------------------------------
	const X509SignMapEntry X509SignMap[]= {
		{ CreateRSAKey, RSAGetAlgID, RSASetAlgID },
		{ CreateDSAKey, DSAGetAlgID, DSASetAlgID },
		{ CreateECDSAKey, ECDSAGetAlgID, ECDSASetAlgID },
		{ CreateDHKey, DHGetAlgID, DHSetAlgID },
		{ CreateECDHKey, ECDHGetAlgID, ECDHSetAlgID },
#if !defined (NO_SMARTCARD) && !defined (NO_OLD_SCARD)
		{ CreateSCardKey, SCardGetAlgID, SCardSetAlgID },
#endif
		{0,0,0}
	};

	// ------------------------------------------------------------------------
	const X509SignHashMapEntry X509SignHashMap[]= {
		// RSA
		{ "1.2.840.113549.1.1.5",	"SHA1",			"RSA" },
		{ "1.3.14.3.2.29",			"SHA1",			"RSA" },
		{ "1.2.840.113549.1.1.2",	"MD2",			"RSA" },
		{ "1.2.840.113549.1.1.3",	"MD4",			"RSA" },
		{ "1.2.840.113549.1.1.4",	"MD5",			"RSA" },
		{ "1.3.36.3.3.1.2",			"RIPEMD160",	"RSA" },
		{ "1.3.36.3.3.1.3",			"RIPEMD128",	"RSA" },
		{ "1.2.840.113549.1.1.11",	"SHA256",		"RSA" }, //sha256WithRSAEncryption
		{ "1.2.840.113549.1.1.12",	"SHA384",		"RSA" }, //sha384WithRSAEncryption
		{ "1.2.840.113549.1.1.13",	"SHA512",		"RSA" }, //sha512WithRSAEncryption
		{ "1.2.840.113549.1.1.14",	"SHA224",		"RSA" }, //sha224WithRSAEncryption
		// DSA
		{ "1.2.840.10040.4.3",		"SHA1",			"DSA" },
		{ "1.3.14.3.2.28",			"SHA1",			"DSA" },
		{ "1.3.14.3.2.27",			"SHA1",			"DSA" }, // secude DSA oid
		// ECDSA
		{ "1.2.840.10045.2.1",		"SHA1",			"ECDSA" },
		{ "1.2.840.10045.4.1",		"SHA1",			"ECDSA" },
		// DH
		{ "1.3.6.1.5.5.7.6.4",		"SHA1",			"DH" }, // DH-POP
		// ECDH
		{ "1.2.840.10045.2.1",		"SHA1",			"ECDH" }, // "ECDH-POP"
		{0,0,0}
	};

#ifndef NO_SMARTCARD
	// ------------------------------------------------------------------------
	const SCardOSMapEntry SCardOSMap[]= 
	{
		{ "53504b32339000", CreateStarCOS},						// StarCOS SPK 2.3
		{ "c802", CreateCardOS_M4},								// CardOS M4.0		siemens profile
		{ "c803", CreateCardOS_M4},								// CardOS M4.01		siemens profile
		{ "c804", CreateCardOS_M4},								// CardOS M4.01a	siemens profile
		{ "c806", CreateCardOS_V4},								// CardOS V4.20
		{ "c807", CreateCardOS_V4},								// CardOS V4.30
		{ "56346376", CreateCardOS_V4},							// CardOS V4.20/4.30	cv profile
		{ "4d346376", CreateCardOS_M4},							// CardOS M4.01(a)	cv profile
		{ "4d3463765f45", CreateCardOS_M4_ECC},					// CardOS M4.01_E	cv profile
		{ "006b0508c806012101434e53103180", CreateCardOS_V4},	// CardOS V4.20	CNS profile, 2004.02.20
		{ "006b0508c807012101434e53103180", CreateCardOS_V4},	// CardOS V4.30	CNS profile, 2004.02.20
		{ "006b0508c806011101434e53103180", CreateCardOS_V4},	// CardOS V4.20	CNS profile, 2005.03.11
		{ "006b0508c807011101434e53103180", CreateCardOS_V4},	// CardOS V4.30	CNS profile, 2005.03.11
		{ "0064050a020131809000", CreateTCOS},					// NetKey (TCOS V2R1)
		{ "00640560020331809000", CreateTCOS},					// NetKey (TCOS V2R3)
		{ "00640514020231809000", CreateTCOS},					// etrust (TCOS V2R2)
		{ "00640561020331809000", CreateTCOS},					// TCOS USB Crypt Token
		{ "0068d276000028ff051e3180009000", CreateMicardOS},	// Micardo P2.1
		{ "4d4943323045", CreateMicardo20E},					// Micardo EC 2.0
		{ "0068d276000028ff05233180009000", CreateMicardo23E},	// Micardo EC 2.3
		// { "414331000000000227904000000000", CreateACOS},		// Austria Card ACOS EMV-A01
		// { "455041000000000000000000000000", CreateACOS},		// Austria Card ACOS without OID
		// { "414331000000000000000000000000", CreateACOS},		// Austria Card ACOS
		{ "410310000000000000000000000000", CreateACOS},		// Austria Card ACOS EMV-A03
		{ "455041000000000000000000000000", CreateACOS},		// Austria Card ACOS SMARTMX
		{ "4a434f503230", CreateJavaCardEdgeOS},				// JavaCard
		{ 0 , 0 }
	};

	// ------------------------------------------------------------------------
	const SCardTokenMapEntry SCardTokenMap[]= 
	{
		{ IsStarCOSToken, CreateStarCOSToken},
//		{ IsCardOSM4Token, CreateCardOSM4Token},				// CreateM4SiemensProfile is used
		{ IsNetKey2000Token, CreateNetKey2000Token},
		{ IsNetKeyE4Token, CreateNetKeyE4Token},
		{ IsNetKeyPKSToken, CreateNetKeyPKSToken},
		{ IsNetKeyOldToken, CreateNetKeyOldToken},
		{ IseTrustToken, CreateeTrustToken},
		{ IsPKCS15Token, CreatePKCS15Token},
		{ IsMicardoECToken, CreateMicardoECToken},
		{ IsM4cvProfile, CreateM4cvProfile},
		{ IsM4cvECProfile, CreateM4cvECProfile},
		{ IsV4cvProfile, CreateV4cvProfile},
		{ IsV4CNSProfile, CreateV4CNSProfile},
		{ IsACOScvProfile, CreateACOScvProfile},
		{ IsM4SiemensProfile, CreateM4SiemensProfile},
		{ IsJavaCardEdgeTestToken, CreateJavaCardEdgeTestToken},
		{ IsJavaCardAppletManager, CreateJavaCardAppletManager},
		{ 0 , 0 }
	};

	// ------------------------------------------------------------------------
	const SubsystemMapEntry SubsystemMap[]= 
	{
		{ "CTAPI", CreateCTAPISystem},
		{ "PCSC", CreatePCSCSystem},
#ifdef WIN32
		{ "CSP", CreateCSPSystem},
#endif
		{ "PKCS11", CreatePKCS11System},
		{ 0 , 0 }
	};

	// ------------------------------------------------------------------------
	const JCardAppletEntry JCardAppletMap[]= 
	{
//		{ 0 , IsEdgeApplet, CreateEdgeApplet, 1, 1, 0 },
		// AID if it is equal to 0 then all AID are able
		//     function  returns true if the Applet can used
		//                  creates an new applet
		//                                 number of PIN's Key's Certificate's
		//  if they are -1 then it will be checked
		//  if they are biger or equal to 0 they are const
		{ 0 , IsEdgeApplet, CreateEdgeApplet, 1, 1, 1 },
//		{ "01020304050601" , IsEdgeApplet, CreateEdgeApplet, 1, 1, 0 },
		{ 0 , 0, 0, 0, 0, 0 }
	};
#endif // NO_SMARTCARD

	// ------------------------------------------------------------------------
	inline void Init()
	{
		static bool loaded = false;
		if (loaded) return;

		KeyReg::Insert(KeyMap);
		BlockCipherReg::Insert(BlockCipherMap);
		BlockCipherModeReg::Insert(BlockCipherModeMap);
		StreamCipherReg::Insert(StreamCipherMap);
		HashReg::Insert(HashMap);
		EMSAReg::Insert(EMSAMap);
		DerivatorReg::Insert(DerivatorMap);
		PaddingReg::Insert(PaddingMap);
		CertificateReg::Insert(CertificateMap);
		CRLReg::Insert(CRLMap);
		X509KeyReg::Insert(X509KeyMap);
		X509SignReg::Insert(X509SignMap);
		X509SignHashReg::Insert(X509SignHashMap);

#ifndef NO_SMARTCARD
		SubsystemReg::Insert(SubsystemMap);
		SCardOSReg::Insert(SCardOSMap);
		SCardTokenReg::Insert(SCardTokenMap);
		JCardAppletReg::Insert(JCardAppletMap);
#endif

		CreateFastRNG=CreateFIPS186;
		CreateStrongRNG=CreateBBS;
		loaded = true;
	}

	// Version: V1R1M0
	const char* GetVersion();
} // namespace act 
#endif

