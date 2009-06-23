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

#ifndef _CONVERTER_H
#define _CONVERTER_H 1

#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _String_h
#include "la_string.h"
#endif
#ifndef _SYMBOL_H
#include "Symbol.h"
#endif
#ifndef _FORMAT_H
#include "Format.h"
#endif

class SymbolArray;

#ifndef __GNUC__
#define IMPLEMENT_CONVERTERCLASS 1
#endif

/////////////////////////////////////////////////////////////////////
// Converter
// these converters map any type onto Zn
//
//	Converter
//		ByteConverter
//			AlphaConverter
//			*AlphaNumConverter
//		NumConverter
//			-BinConverter
//		
//		TupleConverter
//		TripleConverter

/////////////////////////////////////////////////////////////////////

class Converter : public ConverterFormat
{
	friend class SymbolArray;
public:
	typedef Symbol symbol;
	typedef Modulus modulus;
	typedef symbol symbol_arg;			// choose one of those two for passing either
	//typedef const symbol& symbol_arg;	// by value (longs) or reference (larger objects)
public:
// Constructors
	Converter();
	virtual Converter* Clone() const=0;	// virtual cloning
	virtual ~Converter() {}
// Attributes
	virtual modulus GetModulus() const {return m_Modulus;}
// Operations
	// I/O Operations
	virtual int ReadSymbol(istream& in, symbol& s) const =0;
	virtual void WriteSymbol(ostream& out, symbol_arg s) const=0;
	// Tuple only: extraction
	virtual symbol GetPart(symbol_arg s, int i) const; // for Tuple/TripleConverter
	virtual const Converter& GetConverterPart(int i) const;
	// complex I/O Operations
	virtual int ReadSymbolArray(SymbolArray& vec, istream& in, int maxcount=-1) const;
	virtual int ReadSymbolArray(SymbolArray& vec, const char *str, int maxcount=-1) const;
	virtual int WriteSymbolArray(const SymbolArray& vec, ostream& out, int maxcount=-1) const;
// Format
    Converter& operator<<(const Manipulator<Format>& m) { m.manip(*this); return *this; }
protected:
	long GetFormat(Format::Index i) const {return Get(i);}
	const String& GetFormat(Format::SIndex i) const {return Get(i);}
// Implementation
private:
	const Converter& operator=(const Converter& src);
	// Data
protected:
	modulus m_Modulus;
};

/////////////////////////////////////////////////////////////////////
#ifdef IMPLEMENT_CONVERTERCLASS
#define CLONE(TYPE) virtual Converter* TYPE::Clone() const { return new TYPE(*this); }
#else
#define CLONE(TYPE) virtual Converter* TYPE::Clone() const;
#endif
/////////////////////////////////////////////////////////////////////

class NumConverter : public Converter
{
	typedef Converter baseclass;
public:
// Constructors
	NumConverter(modulus mod=0xFFFFFFFF) {m_Modulus=mod;}
	CLONE(NumConverter);
// Operations: I/O
	int ReadSymbol(istream& in, symbol& s) const;
	void WriteSymbol(ostream& out, symbol_arg s) const;
};

/////////////////////////////////////////////////////////////////////

class ByteConverter : public Converter
{
	typedef Converter baseclass;
public:
// Constructors
	ByteConverter(modulus mod=256) {m_Modulus=mod;(*this)<<Sep("");}
	CLONE(ByteConverter);
// Operations: I/O
	int ReadSymbol(istream& in, symbol& s) const;
	void WriteSymbol(ostream& out, symbol_arg s) const;
// Implementation
protected:
	virtual int Filter(char c) const {return c;}
	virtual char Conv(symbol_arg s) const {return (char)s;}
};

/////////////////////////////////////////////////////////////////////

class IdConverter : public ByteConverter
{
	typedef ByteConverter baseclass;
public:
// Constructors
	IdConverter() : baseclass(256) {}
	CLONE(IdConverter);
// Implementation
protected:
	int Filter(char c) const;
	char Conv(symbol_arg s) const;
};

class AlphaConverter : public ByteConverter
{
	typedef ByteConverter baseclass;
public:
// Constructors
	AlphaConverter() : baseclass(26) {}
	CLONE(AlphaConverter);
// Implementation
protected:
	int Filter(char c) const;
	char Conv(symbol_arg s) const;
};

class AlphaSpaceConverter : public ByteConverter
{
	typedef ByteConverter baseclass;
public:
// Constructors
	AlphaSpaceConverter() : baseclass(27) {}
	CLONE(AlphaSpaceConverter);
// Implementation
protected:
	int Filter(char c) const;
	char Conv(symbol_arg s) const;
};

/////////////////////////////////////////////////////////////////////

class AppConverter : public ByteConverter
{
	typedef ByteConverter baseclass;
public:
	int IsInAlphabet(unsigned char c);
// Constructors
	AppConverter() : baseclass(1) {}
	CLONE(AppConverter);
// Implementation
	void SetAlphabet(char *NewAlphabet, int CaseMode);

// Die beiden folgenden Funktionen public gemacht (H. Koy)
	int Filter(char c) const;
	char Conv(symbol_arg s) const;

protected:
	signed int Alphabet[256];
	char InvAlphabet[256];
};

/////////////////////////////////////////////////////////////////////

class BinConverter : public ByteConverter
{
	typedef ByteConverter baseclass;
public:
// Constructors
	BinConverter() : baseclass(2) {}
	CLONE(BinConverter);
// Implementation
protected:
	int Filter(char c) const;
	char Conv(symbol_arg s) const;
};

/////////////////////////////////////////////////////////////////////

class TupleConverter : public Converter
{
	typedef Converter baseclass;
	friend class SymbolArray;
public:
// Constructors
	TupleConverter(const Converter& c1, const Converter& c2);
	TupleConverter(const TupleConverter &src); 
	CLONE(TupleConverter);
	~TupleConverter();
// Operations
	// I/O Operations
	int ReadSymbol(istream& in, symbol& s) const;
	void WriteSymbol(ostream& out, symbol_arg s) const;
	// Tuple only: extraction
	symbol GetPart(symbol_arg s, int i) const; // for Tuple/TripleConverter
	const Converter& GetConverterPart(int i) const;
// Special
protected:
	symbol Combine(symbol_arg s1, symbol_arg s2) const;
private:
	symbol Part1(symbol_arg s) const;
	symbol Part2(symbol_arg s) const;
// Implementation
private:
	Converter *m_Cnv1;
	Converter *m_Cnv2;
};

/////////////////////////////////////////////////////////////////////

class TripleConverter : public Converter
{
	friend class SymbolArray;
	typedef Converter baseclass;
public:
// Constructors
	TripleConverter(const Converter& c1, const Converter& c2, const Converter& c3);
	TripleConverter(const TripleConverter &src); 
	CLONE(TripleConverter);
	~TripleConverter();
// Operations
	// I/O Operations
	int ReadSymbol(istream& in, symbol& s) const;
	void WriteSymbol(ostream& out, symbol_arg s) const;
	// Tuple only: extraction
	symbol GetPart(symbol_arg s, int i) const; // for Tuple/TripleConverter
	const Converter& GetConverterPart(int i) const;
// Special
protected:
	symbol Combine(symbol_arg s1, symbol_arg s2, symbol_arg s3) const;
private:
	symbol Part1(symbol_arg s) const;
	symbol Part2(symbol_arg s) const;
	symbol Part3(symbol_arg s) const;
// Implementation
private:
	Converter *m_Cnv1;
	Converter *m_Cnv2;
	Converter *m_Cnv3;
};

#undef CLONE

/////////////////////////////////////////////////////////////////////
// global converters (as arguments for the SymbolArray constructor)

extern const ByteConverter ByteConv;
extern const IdConverter IdConv;
extern const AlphaConverter AlphaConv;
extern const AlphaSpaceConverter AlphaSpaceConv;
extern const BinConverter BinConv;
extern const NumConverter NumConv;
extern const NumConverter NullConv;
extern AppConverter AppConv;


//const Converter& DefaultConverter=NumConv;
#define DefaultConverter NumConverter
#define DefaultConv NumConv

/////////////////////////////////////////////////////////////////////
// Converter (and subclasses) inline functions 

inline Converter::symbol Converter::GetPart(symbol_arg s, int i) const
{
	if (i==0) return s;
	return 0;
}
inline const Converter& Converter::GetConverterPart(int i) const
{
	if (i==0) return *this;
	return NullConv;
}

// TupleConverter
inline TupleConverter::symbol TupleConverter::Combine(symbol_arg s1,symbol_arg s2) const
{
	return s1*m_Cnv2->GetModulus()+s2;
}
inline TupleConverter::symbol TupleConverter::Part1(symbol_arg s) const
{
	return s/m_Cnv2->GetModulus();
}
inline TupleConverter::symbol TupleConverter::Part2(symbol_arg s) const
{
	return s%m_Cnv2->GetModulus();
}
inline TupleConverter::symbol TupleConverter::GetPart(symbol_arg s, int i) const
{
	if (i==0) return Part1(s);
	if (i==1) return Part2(s);
	return 0;
}
inline const Converter& TupleConverter::GetConverterPart(int i) const
{
	if (i==0) return *m_Cnv1;
	if (i==1) return *m_Cnv2;
	return NullConv;
}


// TripleConverter
inline TripleConverter::symbol TripleConverter::Combine(symbol_arg s1,symbol_arg s2,symbol_arg s3) const
{
	return (s1*m_Cnv2->GetModulus()+s2)*m_Cnv3->GetModulus()+s3;
}
inline TripleConverter::symbol TripleConverter::Part1(symbol_arg s) const
{
	return s/(m_Cnv3->GetModulus()*m_Cnv2->GetModulus());
}
inline TripleConverter::symbol TripleConverter::Part2(symbol_arg s) const
{
	return (s/m_Cnv3->GetModulus())%m_Cnv2->GetModulus();
}
inline TripleConverter::symbol TripleConverter::Part3(symbol_arg s) const
{
	return s%m_Cnv3->GetModulus();
}
inline TripleConverter::symbol TripleConverter::GetPart(symbol_arg s, int i) const
{
	if (i==0) return Part1(s);
	if (i==1) return Part2(s);
	if (i==2) return Part3(s);
	return 0;
}
inline const Converter& TripleConverter::GetConverterPart(int i) const
{
	if (i==0) return *m_Cnv1;
	if (i==1) return *m_Cnv2;
	if (i==2) return *m_Cnv3;
	return NullConv;
}

#endif /* _CONVERTER_H */
