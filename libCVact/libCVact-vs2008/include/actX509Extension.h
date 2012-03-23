//////////////////////////////////////////////////////////////////////////////////
// Name:      actX509Extension.h
// Product:   cv act library
// Purpose:   
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_X509Extension_H
#define ACT_X509Extension_H

#include "actBlob.h"

namespace act
{

	class X509Extension
	{
	public:
		X509Extension();
		X509Extension(const Blob &oid, const Blob &value , bool critflag);
		X509Extension(const char* oid, const Blob &value , bool critflag);
		void GetOID(Blob &oid) const;
		void GetOIDString(Blob &oid) const;
		void SetOID(const Blob &oid); 
		void SetOIDString(const char* oid);
		void GetValue(Blob &value) const;
		void SetValue(const Blob &value);
		bool IsCritical() const;
		void SetCritical(bool crit=true);
		void GetDER(Blob &der) const;
		void SetDER(const Blob &der);
		bool IsPresent(){return mValue.size() > 0;};
	private:
		Blob mOID;
		Blob mValue;
		bool mCrit;
	};

} // namespace act

#endif

