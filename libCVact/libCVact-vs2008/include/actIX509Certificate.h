//////////////////////////////////////////////////////////////////////////////////
// Name:      actIX509Certificate.h
// Product:   cv act library
// Purpose:   The abstract class IX509Certificate enables access to a certificate, 
//			  e.g. its public key and the corresponding validity. 
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IX509Certificate_h
#define ACT_IX509Certificate_h

#include "actBasics.h"
#include "actDate.h"
#include "actICertificate.h"
#include "actX509Extension.h"

namespace act
{
	class IKey;
	class Blob;

	class IX509Certificate : public ICertificate
	{
	public:

		virtual void SetValidityNotBefore( const Date &vnbefore ) =0;
		virtual void SetValidityNotAfter( const Date &vnafter ) =0;
		virtual void GetValidityNotBefore(Date &vnbefore ) const =0;
		virtual void GetValidityNotAfter(Date &vnafter ) const =0;

		virtual bool CheckValidity(const Date& date = Date() ) const =0;

		virtual X509Extension GetExtension( const char* oid) const=0;
		virtual X509Extension GetExtension( const act::Blob &oidbl) const=0;
		virtual void SetExtension( const X509Extension &ext)=0;
		virtual X509Extension GetNextExtension(const X509Extension& ext) const=0;
		virtual void RemoveExtension(const char* oid)=0;
	};
} // namespace act

#endif

