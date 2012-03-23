//////////////////////////////////////////////////////////////////////////////////
// Name:      actIAlgorithm.h
// Product:   cv act library
// Purpose:   IAlgorithm is an abstract base. All concrete algorithm-classes are
//            derived from IAlgorithm.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IALGORITHM_H
#define ACT_IALGORITHM_H

#include "actBasics.h"

namespace act
{
	class Blob;

	class IAlgorithm
	{
	public:
		
		virtual void Write( const Blob& input ) = 0;
		virtual void Write( const byte* input, size_t insize ) = 0;
		virtual void Finalize() = 0;
		virtual size_t GetAvailableSize() const = 0;
		virtual size_t Read( Blob& output, size_t max = 0 ) = 0;
		virtual size_t Read( byte* outbuffer, size_t buffersize ) = 0;
		virtual status_t GetStatus() const = 0;
		virtual ~IAlgorithm() {}

	};

} // namespace act
#endif


