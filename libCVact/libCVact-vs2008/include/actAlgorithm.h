//////////////////////////////////////////////////////////////////////////////////
// Name:      actAlgorithm.h
// Product:   cv act library
// Purpose:   The class Algorithm generates algorithms for encryption and signing.
//            The class Key defined these algorithms. By using this handle the
//            necessary methods (e.g. hash-algorithms, verifying-primitiva, etc.)
//            can be generated.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_Algorithm_h
#define ACT_Algorithm_h

#include "actBasics.h"

namespace act
{
	class IAlgorithm;
	class IKey;
	class Blob;

	class Algorithm 
	{
	public:
		Algorithm(IAlgorithm *alg);	
		Algorithm(const IKey *key, mode_t mode);
		Algorithm(const IKey *key, mode_t mode, const Blob &data);
		Algorithm(const char* name);	

		void Write(const Blob& indata);
		void Write(const byte* indata, size_t insize);

		void Finalize();

		size_t Read(Blob& outdata,size_t max = 0);
		size_t Read(byte* outbuffer,size_t buffersize);

		size_t GetAvailableSize() const ;
		status_t GetStatus() const ;

		Algorithm& operator<<(const Blob& indata) { Write(indata); return *this;}
		Algorithm& operator<<(Algorithm& (*manipulator)(Algorithm &alg)) { return manipulator(*this);}
		Algorithm& operator>>(Blob& outdata) { Read(outdata); return *this;}

		~Algorithm();

		operator IAlgorithm* ();
		operator const IAlgorithm* () const;
		IAlgorithm* GetPointer();
		const IAlgorithm* GetPointer() const;

		IAlgorithm* ReleasePointer();


	private:
		Algorithm(const Algorithm &alg);
		Algorithm &operator=(const Algorithm &alg);
		IAlgorithm *mAlg;

	};

	inline Algorithm& final(Algorithm &alg)
	{
		alg.Finalize();
		return alg;
	}

} // namespace act
#endif


