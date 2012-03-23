//////////////////////////////////////////////////////////////////////////////////
// Name:      actCertificate.h
// Product:   cv act library
// Purpose:   The concrete class Certificate enables direct access to a certificate,
//             e.g. its public key and the corresponding validity. 
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_Certificate_h
#define ACT_Certificate_h
#include "actBasics.h"

namespace act
{
	class IKey;
	class Blob;
	class ICertificate;

	class Certificate
	{
	public:
		Certificate();
		Certificate(const char* type);
		Certificate(const char* type, const Blob &certblob); 
		Certificate(const Certificate& cert);

		void SetParam(paramid_t id,const Blob &blob);
		void SetParam(paramid_t id,int val);
		void SetParam(paramid_t id,const char* cstr);
		void GetParam(paramid_t id,Blob &blob) const;
		int  GetParam(paramid_t) const;

		void Import(const Blob &certblob);
		void Export(Blob &certblob) const;

		void SetPublicKey(const IKey* pubkey);
		IKey* CreatePublicKey(const char* = 0) const;

		void Sign(const IKey* privkey);
		int Verify(const IKey* pubkey) const;

		const ICertificate* GetPointer() const;
		ICertificate* GetPointer();

		operator const ICertificate* () const;
		operator ICertificate* ();

		ICertificate* ReleasePointer();

		Certificate& operator= (const Certificate& cert);

		~Certificate();
	private:
		ICertificate* mCert;
	};

}; // namespace act

#endif

