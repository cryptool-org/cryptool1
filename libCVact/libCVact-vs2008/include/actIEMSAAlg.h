//////////////////////////////////////////////////////////////////////////////////
// Name:      actIEMSAAlg.h
// Product:   cv act library
// Purpose:   IEMSAAlg (Encoding Methods for Signatures with Appendix) is an 
//            abstract class derived from IAlgorithm. Encoding methods do not
//            use keys. These algorithms prepare the data to sign. They can be
//            implemented with or without hash functions.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IEMSAAlg_h
#define ACT_IEMSAAlg_h

#include "actBasics.h"
#include "actIAlgorithm.h"

namespace act
{

	class IEMSAAlg : public IAlgorithm 
	{
	public:
		virtual IEMSAAlg* Clone() const =0;

		virtual void Import(const Blob &blob) =0;
		virtual void Export(Blob &blob) const =0;
		virtual void SetParam(paramid_t id,const Blob &blob) =0;
		virtual void SetParam(paramid_t id,int val) =0;
		virtual void SetParam(paramid_t id,const char* cstr) =0;
		virtual void GetParam(paramid_t id,Blob &blob) const =0;
		virtual int  GetParam(paramid_t) const =0;

		virtual void Reset(size_t sizeinbits) =0;

		virtual void* GetCreatePointer() const =0;

		virtual bool Verify(const Blob &em, const Blob &sig_inv) =0;

		virtual ~IEMSAAlg(){}
	};
} // namespace act

#endif


