//////////////////////////////////////////////////////////////////////////////////
// Name:      actCRL.h
// Product:   cv act library
// Purpose:   
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_CRL_h
#define ACT_CRL_h
#include "actBasics.h"

namespace act
{
	class IKey;
	class Blob;
	class ICertificate;
	class ICRL;
	class CRL
	{
	public:
		CRL(const char* type);
		CRL(const char* type, const Blob &crlblob); 
		CRL(const CRL& crl);

		void SetParam(paramid_t id,const Blob &blob);
		void SetParam(paramid_t id,int val);
		void SetParam(paramid_t id,const char* cstr);
		void GetParam(paramid_t id,Blob &blob) const;
		int  GetParam(paramid_t) const;

		void Import(const Blob &crl);
		void Export(Blob &crl) const;

		void Revoke(const ICertificate* cert);
		bool IsRevoked( const ICertificate* Cert) const;
		void RemoveRevokation(const ICertificate* cert);

		void Revoke(const Blob &blob);
		bool IsRevoked(const Blob &blob) const;
		void RemoveRevokation(const Blob &blob);

		void Sign(const IKey* privkey);
		int Verify( const IKey* pubkey) const;

		const ICRL* GetPointer() const;
		ICRL* GetPointer();

		operator const ICRL* () const;
		operator ICRL* ();


		ICRL* ReleasePointer();

		CRL& operator= (const CRL& crl);

		~CRL();
	private:
		ICRL* mCRL;
	};

}; // namespace act

#endif

