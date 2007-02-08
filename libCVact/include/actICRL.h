//////////////////////////////////////////////////////////////////////////////////
// Name:      actICRL.h
// Product:   cv act library
// Purpose:   The abstract class ICRL (Certificate Revocation List) can be used
//            to check whether a certificate has been revoked.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_ICRL_h
#define ACT_ICRL_h

namespace act
{
	class IKey;
	class ICertificate;
	class Blob;

	class ICRL
	{
	public:

		virtual ICRL* Clone() const=0;
		virtual void Import(const Blob &crlblob)=0;
		virtual void Export(Blob &crlblob) const =0;
		virtual void SetParam(paramid_t id,const Blob &blob) =0;
		virtual void SetParam(paramid_t id,int val) =0;
		virtual void SetParam(paramid_t id,const char* cstr) =0;
		virtual void GetParam(paramid_t id,Blob &blob) const =0;
		virtual int  GetParam(paramid_t) const =0;

		virtual void Revoke(const ICertificate* cert) =0;
		virtual bool IsRevoked( const ICertificate* Cert) const =0;
		virtual void RemoveRevokation(const ICertificate* cert) =0;

		virtual void Revoke(const Blob &blob) = 0;
		virtual bool IsRevoked(const Blob &blob) const = 0;
		virtual void RemoveRevokation(const Blob &blob) = 0;

		virtual void Sign(const IKey* privkey) =0;
		virtual int Verify( const IKey* pubkey) const =0;
		virtual void* GetCreatePointer() const=0;
		virtual ~ICRL() {};
	};
} // namespace act

#endif

