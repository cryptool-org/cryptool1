/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

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

#ifndef _SYMBOLARRAY_H
#define _SYMBOLARRAY_H 1

#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _SYMBOL_H
#include "Symbol.h"
#endif
#ifndef _CONVERTER_H
#include "Converter.h"
#endif
#ifndef _ARRAY_H
#include "Array.h"
#endif
#ifndef _CIPHER_H
#include "Cipher.h"
#endif

class SBox;
class Permutation;
class LFSR;

///////////////////////////////////////////////////////////////////
// SymbolArray
class SymbolArray : public Array<Symbol,Symbol> 
{
	typedef Array<Symbol,Symbol> baseclass;
	typedef baseclass arraytype;
public:
	typedef Symbol symbol;		// kind of elements that are stored here
	typedef Modulus modulus;	// 
	typedef Cipher::CryptMode CryptMode; // used by Apply
private:
	class c_BitStream {};
	class c_ByteStream {};
	class c_GetPart {};
	class c_Extract {};
public:
	void Homophone(SymbolArray,bool,int);
// Constructors
	EXPLICIT SymbolArray(int size=0, const Converter& cnv=DefaultConv);
	EXPLICIT SymbolArray(const Converter& cnv,int size=0);
	EXPLICIT SymbolArray(const char *s, const Converter& cnv=DefaultConv);
	SymbolArray(const SymbolArray& src);
	~SymbolArray();

	// special constructors
	SymbolArray(const LFSR& lfsr, int len=10000);
	SymbolArray(const NTuple<symbol> &Vec, const Converter& cnv=DefaultConv); 

	// tuple/triple constructors
	SymbolArray(SymbolArray& s1, SymbolArray& s2);
	SymbolArray(SymbolArray& s1, SymbolArray& s2, SymbolArray& s3);
	SymbolArray(Converter& cnv1, Converter& cnv2);
	SymbolArray(Converter& cnv1, Converter& cnv2, Converter& cnv3);

	// special constructors, use with X.Name()
	SymbolArray BitStream() const {return SymbolArray(*this,(c_BitStream*)0);}	// any type->SymbolArray(BitConv)
	SymbolArray ByteStream(int n=8) const {return SymbolArray(*this,(c_ByteStream*)0,n);}	// any type->SymbolArray(ByteConv)
	SymbolArray Extract(int k, int mod=2, int k2=-1, int k3=-1) const {return SymbolArray(*this,k,mod,k2,k3,(c_Extract*)0);}
	SymbolArray GetPart(int part) const {return SymbolArray(*this,part,(c_GetPart*)0);} // Extract 1st, 2nd, 3rd element of tuple/triple
	SymbolArray First() const {return GetPart(0);}
	SymbolArray Second() const {return GetPart(1);}
	SymbolArray Third() const {return GetPart(2);}

	// operator=
	const SymbolArray& operator=(const SymbolArray& src);
	const SymbolArray& operator=(const NTuple<symbol>& src);
	//SymbolArray& operator=(long s[]);

// Attributes
	modulus GetModulus() const {return m_Modulus;}
	const Converter* GetConverter() const {return m_Converter;}
// Manipulate Attributes
	void SetConverter(Converter& cnv);	// be careful when using this
	void SetConverter(int mod);			// be careful when using this
// Format
    SymbolArray& operator<<(const Manipulator<Format>& m) { m.manip(*m_Converter); return *this; }
// Operations 
	SymbolArray& operator+=(const NTuple<symbol>& x);
	SymbolArray& operator-=(const NTuple<symbol>& x);
	SymbolArray& operator*=(const NTuple<symbol>& x);
	SymbolArray& operator^=(const NTuple<symbol>& x);
	SymbolArray& operator|=(const NTuple<symbol>& x);
	SymbolArray& operator&=(const NTuple<symbol>& x);
	SymbolArray& operator+=(Iterator<symbol>& x);
	SymbolArray& operator-=(Iterator<symbol>& x);
	SymbolArray& operator*=(Iterator<symbol>& x);
	SymbolArray& operator^=(Iterator<symbol>& x);
	SymbolArray& operator|=(Iterator<symbol>& x);
	SymbolArray& operator&=(Iterator<symbol>& x);
	SymbolArray& operator+=(const symbol& x);
	SymbolArray& operator-=(const symbol& x);
	SymbolArray& operator*=(const symbol& x);
	SymbolArray& operator^=(const symbol& x);
	SymbolArray& operator|=(const symbol& x);
	SymbolArray& operator&=(const symbol& x);
	// Special Operations
	void Put(const NTuple<symbol>& Vec, int k, int mod=2, int k2=-1, int k3=-1);
	void PutInsert(const NTuple<symbol>& Vec, int k, int mod=2, int k2=-1, int k3=-1);
	void Rotate(int step, int mode=0); // 0=cyclic, 1= insert 0s, 2=resize

	// Cipher Operations
	void Apply(Cipher& cipher, CryptMode mode=Cipher::Encrypt);

	// I/O Operations
	int Read(istream& in, int maxcount=-1);
	int Read(const char* filename, int maxcount=-1);
	int ReadString(const char* text, int maxcount=-1);
	int Write(ostream& out, int maxcount=-1) const;
	int Write(const char* filename, int maxcount=-1);

	void Load(istream& stream); 
	void Save(ostream& stream) const; 
	void Show(OStream& out=DefaultOStream) const;

// Static Members - (should be put in Symbol 'class')
	static int MaxBits() {return sizeof(symbol)*8;} 
	static symbol MaxNum() {return 0xFFFFFFFF;}

// Implementation
	// Helpers
private:
	void Init(const Converter& cnv);
	void Init(Converter* cnv);
	void Init(int mod);
	// private constructors - these are used inline by "function constructors" to avoid temporary objects (one extra copy)
	SymbolArray(const SymbolArray& s,c_BitStream* t);
	SymbolArray(const SymbolArray& s,c_ByteStream* t, int n);
	SymbolArray(const SymbolArray& s, int part, c_GetPart* t);
	SymbolArray(const SymbolArray& s, int k, int mod, int k2, int k3, c_Extract* t);
	// Data
private:
	modulus m_Modulus;
	Converter *m_Converter;
};

///////////////////////////////////////////////////////////////////
// SymbolArray inline functions

// Helpers
inline void SymbolArray::Init(const Converter& cnv)
{
	if (&cnv==NULL) m_Converter=new DefaultConverter;
	else m_Converter=cnv.Clone();
	m_Modulus=m_Converter->GetModulus();
}
inline void SymbolArray::Init(Converter* cnv)
{
	if (cnv==NULL) m_Converter=new DefaultConverter;
	m_Converter=cnv;
	m_Modulus=m_Converter->GetModulus();
}

inline void SymbolArray::Init(int mod)
{
	m_Modulus=mod;
	if (m_Modulus==2) m_Converter=new BinConverter;
	else m_Converter= new NumConverter(m_Modulus);
}

// 
inline SymbolArray::~SymbolArray() 
{
	delete m_Converter;
}

inline void SymbolArray::SetConverter(Converter& cnv) 
{
	delete m_Converter;
	Init(cnv);
}
inline void SymbolArray::SetConverter(int mod) 
{
	if (m_Modulus==(modulus)mod) return;
	delete m_Converter;
	Init(mod);
}


///////////////////////////////////////////////////////////////////

inline ostream& operator<<(ostream& os, SymbolArray& sa)
{
	sa.Write(os);
	return os;
}

inline istream& operator>>(istream& is, SymbolArray& sa)
{
	sa.Read(is);
	return is;
}


#endif /* _SYMBOLARRAY_H */