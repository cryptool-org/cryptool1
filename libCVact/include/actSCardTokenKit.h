// ---------------------------------------------------------------------------
// Name:      actSCardTokenKit.h
// Product:   cv act library
// Purpose:   registry for factory functions to create SCardOS and SCardToken objects
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  05/14/2002
// ---------------------------------------------------------------------------

#ifndef SCARDTOKENKIT_H
#define SCARDTOKENKIT_H

namespace act
{
	class ISCardOS;
	class SCardToken;

	bool IsStarCOSToken(ISCardOS* os);					
	SCardToken* CreateStarCOSToken(ISCardOS* os);

	bool IsCardOSM4Token(ISCardOS* os);
	SCardToken* CreateCardOSM4Token(ISCardOS* os);

	bool IsV4cvProfile(ISCardOS* os);
	SCardToken* CreateV4cvProfile(ISCardOS* os);

	bool IsV4CNSProfile(ISCardOS* os);
	SCardToken* CreateV4CNSProfile(ISCardOS* os);

	bool IsNetKey2000Token(ISCardOS* os);
	SCardToken* CreateNetKey2000Token(ISCardOS* os);

	bool IsNetKeyE4Token(ISCardOS* os);
	SCardToken* CreateNetKeyE4Token(ISCardOS* os);

	bool IsNetKeyPKSToken(ISCardOS* os);
	SCardToken* CreateNetKeyPKSToken(ISCardOS* os);

	bool IsNetKeyOldToken(ISCardOS* os);
	SCardToken* CreateNetKeyOldToken(ISCardOS* os);

	bool IseTrustToken(ISCardOS* os);
	SCardToken* CreateeTrustToken(ISCardOS* os);

	bool IsPKCS15Token(ISCardOS* os);
	SCardToken* CreatePKCS15Token(ISCardOS* os);

	bool IsMicardoECToken(ISCardOS* os);
	SCardToken* CreateMicardoECToken(ISCardOS* os);

	bool IsM4cvProfile(ISCardOS* os);
	SCardToken* CreateM4cvProfile(ISCardOS* os);

	bool IsACOScvProfile(ISCardOS* os);
	SCardToken* CreateACOScvProfile(ISCardOS* os);

	bool IsM4SiemensProfile(ISCardOS* os);
	SCardToken* CreateM4SiemensProfile(ISCardOS* os);

	bool IsM4cvECProfile(ISCardOS* os);
	SCardToken* CreateM4cvECProfile(ISCardOS* os);

	bool IsJavaCardEdgeTestToken(ISCardOS* os);
	SCardToken* CreateJavaCardEdgeTestToken(ISCardOS* os);

	bool IsJavaCardAppletManager(ISCardOS* os);
	SCardToken* CreateJavaCardAppletManager(ISCardOS* os);

}
#endif

