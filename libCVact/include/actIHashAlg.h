//////////////////////////////////////////////////////////////////////////////////
// Name:      actIHashAlg.h
// Product:   cv act library
// Purpose:   IHashAlg is an abstract base class, which provides the interface
//            of all hash-algorithms.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IHASHALG_H
#define ACT_IHASHALG_H

#include "actIAlgorithm.h"

namespace act
{

	class IHashAlg : public IAlgorithm
	{
	public:
		virtual IHashAlg* Clone() const =0;
		virtual void Import(const Blob& indata) =0;
		virtual void Export(Blob& outdata) const =0;
		virtual void SetParam(paramid_t id,const Blob &blob) =0;
		virtual void SetParam(paramid_t id,int val) =0;
		virtual void SetParam(paramid_t id,const char* cstr) =0;
		virtual void GetParam(paramid_t id,Blob &blob) const =0;
		virtual int  GetParam(paramid_t) const =0;
		virtual size_t GetBlockSize() const = 0;
		virtual size_t GetHashSize() const = 0;
		virtual void Reset() =0;
		virtual void* GetCreatePointer() const =0;
		virtual ~IHashAlg() {}
	};

} // namespace act
#endif


