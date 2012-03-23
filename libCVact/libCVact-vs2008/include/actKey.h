//////////////////////////////////////////////////////////////////////////////////
// Name:      actKey.h
// Product:   cv act library
// Purpose:   The class Key manages information relevant to keys (e.g.
//            domain parameters or the key itself). In the case of symmetric 
//            encryption only a (the) secret key is generated. In the case of
//            of asymetric encryption a private and a public key are generated.
//            This handle allows a universal approach for different families of 
//            algorithms.
//            
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_KEY_H
#define ACT_KEY_H

#include "actBasics.h"
#include "actBlob.h"

namespace act
{
	class IRNGAlg;
	class IAlgorithm;
	class IKey;
	class ICertificate;

	class Key
	{
	public:
		Key();
		Key(const Key &key);
		Key(IKey* keyptr);
		Key(const Blob &keyblob);
		Key(const ICertificate* cert);
		Key(const char* keytype);

		void Import(const Blob &keyblob);
		void Export(Blob &keyblob,export_t type=DEFAULT) const;

		void SetParam(paramid_t id,const Blob &blob);
		void SetParam(paramid_t id,int  val);
		void SetParam(paramid_t id,const char *cstr);

		int  GetParam(paramid_t id) const;
		void GetParam(paramid_t id, Blob &blob) const;

		void Generate(IAlgorithm *prng=0);
		void Derive(const Blob &data, const Blob &salt=Blob());

		IAlgorithm* CreateAlgorithm( mode_t Mode) const;
		IAlgorithm* CreateAlgorithm( mode_t Mode, const Blob &data) const;

		IKey* GetPointer();
		const IKey* GetPointer() const;
		operator IKey* ();
		operator const IKey* () const;

		IKey* ReleasePointer();

		Key& operator= (const Key& key);

		~Key();
	private:
		IKey *mKey;

	};

} // namespace act
#endif

