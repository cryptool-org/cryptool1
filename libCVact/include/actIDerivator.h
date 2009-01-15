//////////////////////////////////////////////////////////////////////////////////
// Name:      actIDerivator.h
// Product:   cv act library
// Purpose:   This interface provides a shared secret key (the last step in 
//            a Key Agreement Scheme).
//
// Copyright: (c) 2006 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IDerivator_h
#define ACT_IDerivator_h

#include"actBasics.h"

namespace act
{
	class Blob;

	class IDerivator
	{
	public:
		virtual IDerivator* Clone() const=0;

		virtual void Import(const Blob &blob)=0;
		virtual void Export(Blob &blob) const=0;

		virtual void SetParam(paramid_t id,const Blob &blob)=0;
		virtual void SetParam(paramid_t id,int val)=0;
		virtual void SetParam(paramid_t id,const char* cstr)=0;
		virtual void GetParam(paramid_t id,Blob &blob) const=0;
		virtual int  GetParam(paramid_t) const=0;

		virtual void Derive(const Blob& secret, const Blob& salt, Blob& keymat) const=0;

		virtual void* GetCreatePointer() const =0;
		virtual ~IDerivator() {}
	};
} // namespace act

#endif


