/////////////////////////////////////////////////////////////////
//
// Diese Datei ist Bestandteil der Diplomarbeit
// "Eine C++-Bibliothek zur informationstheoretischen Kryptanalyse 
// von Stromchiffren und PZ-Folgen" am Europaeischen Institut fuer
// Systemsicherheit, Prof. Dr. Th. Beth
//
// von und (c) 1997-98 Michael Friedrich
//
/////////////////////////////////////////////////////////////////
 
#ifndef _CIPHER_H
#define _CIPHER_H 1

// Cipher.h definiert folgende Klassen:
// ************************************
// Cipher
//		BlockCipher
//			FeistelCipher
//		StreamCipher
//			CBC

#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _SYMBOL_H
#include "Symbol.h"
#endif
#ifndef _ARRAY_H
#include "Array.h"
#endif

class SymbolArray;

/////////////////////////////////////////////////////////////////////
// Cipher: Abstrakte Klasse einer Chiffre

class Cipher
{
public:
	typedef Symbol symbol;
	typedef unsigned long domain;
	typedef unsigned long codomain;
	typedef int range;
	enum CryptMode {Encrypt=0, Decrypt=1 }; // used by Apply
public:
	virtual int GetSize() const=0; // block length
// Operations
	virtual void operator()(NTupleRW<symbol>& Vec, int mode=Encrypt)=0;
	// optionally used if GetSize()<=1
	virtual domain operator()(codomain x, int mode=Encrypt) {return 0;}
	// Show
	//virtual void Show(OStream& out=DefaultOStream) const=0;
};

/////////////////////////////////////////////////////////////////////
// (BLOCK)CIPHER_WITH_SIZE_1
// Im public-Teil der Klasendefinition angeben, definiert:
// GetSize() liefert 1
// void operator()(NTuple,mode) benutzt domain operator()(codomain,mode)

#define CIPHER_WITH_SIZE_1 \
	virtual int GetSize() const {return 1;} \
	void operator()(NTupleRW<symbol>& Vec, int mode=Encrypt) \
	{ Vec[0]=(*this)(Vec[0],mode); }

#define BLOCKCIPHER_WITH_SIZE_1 \
	virtual int GetSize() const {return 1;} \
	void operator()(NTupleRW<symbol>& Vec, int mode=Encrypt) const \
	{ Vec[0]=(*this)(Vec[0],mode); } \
	void operator()(NTupleRW<symbol>& Vec, int mode=Encrypt) \
	{ Vec[0]=(*this)(Vec[0],mode); }


/////////////////////////////////////////////////////////////////////
// BlockCipher: Abstrakte Klasse einer Block-Chiffre

class BlockCipher : public Cipher
{
public:
	// BlockCipher hat keinen internen Zustand, entsprechend: operator() CONST
	virtual void operator()(NTupleRW<symbol>& Vec, int mode=Encrypt) const=0;
	virtual domain operator()(codomain x, int mode=Encrypt) const {return 0;}

	// the non-const member functions simply call their const versions!
	void operator()(NTupleRW<symbol>& Vec, int mode=Encrypt)
	{ ((const BlockCipher*)this)->operator()(Vec,mode);}
	domain operator()(codomain x, int mode=Encrypt)
	{ return ((const BlockCipher*)this)->operator()(x,mode);}
};

/////////////////////////////////////////////////////////////////////
// StreamCipher: Abstrakte Klasse einer Strom-Chiffre

typedef Cipher StreamCipher;

/////////////////////////////////////////////////////////////////////
// IdendityCipher: Macht nichts, als Parameter fuer FeistelCipher sinnvoll.
class IdendityCipher : public BlockCipher
{
	int GetSize() const {return 0;}
	void operator()(NTupleRW<symbol>& Vec, int mode=Encrypt) const {}
};

static IdendityCipher None;

/////////////////////////////////////////////////////////////////////
// FeistelCipher: Hilfsklasse zur einfachen Implementation einer Feistel-Chiffre
class FeistelCipher : public BlockCipher
{
public:
	FeistelCipher(const BlockCipher& f, int Rounds, const BlockCipher& Init=None, const BlockCipher& End=None) : m_f(f), m_Init(Init), m_End(End), m_Rounds(Rounds) {}
	int GetSize() const {return 2*m_f.GetSize();}
	void operator()(NTupleRW<symbol>& Vec, int mode=Encrypt) const;
//Implementation
private:
	const BlockCipher& m_f;
	const BlockCipher& m_Init;
	const BlockCipher& m_End;
	int m_Rounds;
};

class CBC : public StreamCipher
{
public:
	CBC(Cipher& f, NTuple<symbol>& IV);
	int GetSize() const {return m_f.GetSize();}
	void operator()(NTupleRW<symbol>& Vec, int mode=Encrypt);
// Attributes
	void SetIV(NTuple<symbol>& IV);
//Implementation
private:
	Cipher& m_f;
	Array<symbol,symbol> m_lastblock;
};

#ifdef TODO
// Folgende beiden Klassen lassen sich analog zu CBC
// implementieren und anwenden.
class CFB : public StreamCipher
{
};
class OFB : public StreamCipher
{
};

#endif


#endif /* _CIPHER_H */