//////////////////////////////////////////////////////////////////////////////////
// Name:      actIPadding.h
// Product:   cv act library
// Purpose:   With the abstract class IPadding input data can be filled to obtain
//            a certain length and also to invert this process. E.g. PKCS1-v1_5 is  
//            a padding.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IPadding_h
#define ACT_IPadding_h
#include "actBasics.h"

namespace act
{

	class Blob;

	class IPadding
	{
	public:

		virtual IPadding* Clone() const=0;

		virtual void Import(const Blob& indata) =0;
		virtual void Export(Blob& outdata) const =0;
		virtual void SetParam(paramid_t id,const Blob &blob) =0;
		virtual void SetParam(paramid_t id,int val) =0;
		virtual void SetParam(paramid_t id,const char* cstr) =0;
		virtual void GetParam(paramid_t id,Blob &blob) const =0;
		virtual int  GetParam(paramid_t) const =0;

		virtual void Pad(Blob& Buffer, size_t len) const =0;
		virtual size_t Unpad(Blob& Buffer) const =0;

		virtual void* GetCreatePointer() const =0;
		virtual ~IPadding() {}
	};


} //namespace act
#endif

