//////////////////////////////////////////////////////////////////////////////////
// Name:      actIX509CRL.h
// Product:   cv act library
// Purpose:   
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IX509CRL_h
#define ACT_IX509CRL_h
#include "actICRL.h"
#include "actX509Extension.h"

namespace act
{

	class IX509CRL: public ICRL
	{
	public:
		virtual void SetThisUpdate( const Date &date )=0;
		virtual void SetNextUpdate( const Date &date )=0;
		virtual void GetThisUpdate(Date &date ) const=0;
		virtual void GetNextUpdate(Date &date ) const=0;

		virtual X509Extension GetExtension( const char* oid) const=0;
		virtual X509Extension GetExtension( const act::Blob &oidbl) const=0;
		virtual void SetExtension( const X509Extension &ext)=0;
		virtual X509Extension GetNextExtension(const X509Extension& ext) const=0;
		virtual void RemoveExtension(const char* oid)=0;

		virtual Blob GetNextEntry(const Blob& certsernr) const=0;

		virtual void SetEntryRevocationDate(const Blob& certsn, const Date &vnbefore )=0;
		virtual void GetEntryRevocationDate(const Blob& certsn, Date &vnbefore ) const=0;

		virtual X509Extension GetEntryExtension(const Blob& certsn, const char* oid) const=0;
		virtual void SetEntryExtension(const Blob& certsn, const X509Extension &ext)=0;
		virtual X509Extension GetNextEntryExtension(const Blob& certsn,const X509Extension& ext) const=0;
		virtual void RemoveEntryExtension(const Blob& certsn,const char* oid)=0;

	};
} // namespace act

#endif

