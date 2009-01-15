//////////////////////////////////////////////////////////////////////////////////
// Name:      actX509Kit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_X509Kit_h
#define ACT_X509Kit_h

namespace act
{
	class Blob;
	class IKey;

	void X509ToRSA(const Blob& pkinfo, IKey* key);
	void RSAToX509(const IKey* key, Blob& pkinfo);
	void RSAGetAlgID(const IKey* key, Blob& algid);
	void RSASetAlgID(const Blob& algid, IKey* key );

	void X509ToDSA(const Blob& pkinfo, IKey* key);
	void DSAToX509(const IKey* key, Blob& pkinfo);
	void DSAGetAlgID(const IKey* key, Blob& algid);
	void DSASetAlgID(const Blob& algid, IKey* key );

	void X509ToECDSA(const Blob& pkinfo, IKey* key);
	void ECDSAToX509(const IKey* key, Blob& pkinfo);
	void ECDSAGetAlgID(const IKey* key, Blob& algid);
	void ECDSASetAlgID(const Blob& algid, IKey* key );

	void X509ToDH(const Blob& pkinfo, IKey* key);
	void DHToX509(const IKey* key, Blob& pkinfo);
	void DHGetAlgID(const IKey* key, Blob& algid);
	void DHSetAlgID(const Blob& algid, IKey* key );

	void ECDHGetAlgID(const IKey* key, Blob& algid);
	void ECDHSetAlgID(const Blob& algid, IKey* key );

}
#endif

