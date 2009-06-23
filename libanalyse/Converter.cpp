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
#include <string.h>

#define IMPLEMENT_CONVERTERCLASS 1
#include "Converter.h"

#ifndef _SYMBOLARRAY_H
#include "SymbolArray.h"
#endif

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#include <fstream.h>
#include <strstrea.h>
#else
#include <iostream>
#include <fstream>
#include <strstream>
using namespace std;
#endif

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// Converter functions

Converter::Converter()
{
	(*this) << Sep(" ") << LF("\n");
}

int Converter::ReadSymbolArray(SymbolArray& vec,istream& in, int maxcount /*=-1*/) const
{
	int num=0;

	while (in && (maxcount--)) {
		symbol s;
		if (ReadSymbol(in,s)) {
			vec.Add(s);
			num++;
		} else break;
	} /* while */
	return num;
}
int Converter::ReadSymbolArray(SymbolArray& vec, const char *str, int maxcount /*=-1*/) const
{
	istrstream in((char*)str); // HACK cast const away, str is not modified by istrstream
	return ReadSymbolArray(vec,in,maxcount);
}

int Converter::WriteSymbolArray(const SymbolArray& vec,ostream& out, int maxcount /*=-1*/) const
{
	if (maxcount<0) maxcount=vec.GetSize();
	else maxcount=min(maxcount,vec.GetSize());

	int i=0;
	while (out && (i<maxcount)) {
		if (GetFormat(RawData)) {
			if (GetFormat(Converter::Hex)) out << hex << vec[i] << dec;
			else out << vec[i];
		} else {
			WriteSymbol(out,vec[i]);
		}
		i++;
		if (GetFormat(SymbolsperLine) && (i%GetFormat(SymbolsperLine)==0)) 
			out << GetFormat(LF);
		else
			out << GetFormat(Sep);
//			out << "\n";
	} /* while */
	return i;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// ByteConverter

int ByteConverter::ReadSymbol(istream& in, symbol& s) const
{
	unsigned char c;
	while (in) {
		c=(unsigned char)in.get();
        if(in.rdstate()&ios::eofbit) return 0;
		int r=Filter(c);
		if (r>=0 && (unsigned long)r<m_Modulus) {
			s=r;
			return 1;
		}
	}
	return 0;
}
void ByteConverter::WriteSymbol(ostream& out, symbol_arg s) const
{
	out.put(Conv(s));
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// NumConverter

int NumConverter::ReadSymbol(istream& in, symbol& s) const
{
	long l=-1;
	if (GetFormat(Converter::Hex)) in >> hex >> l >> dec;
	else in >> l;
	if (l==-1) {
		s=0;
		return 0;
	}
	s=l % m_Modulus;
	int c=in.peek();
	if (c==';' || c== ',') in.get();
	return 1;
}
void NumConverter::WriteSymbol(ostream& out, symbol_arg s) const
{
	if (GetFormat(Converter::Hex)) out << hex << s << dec;
	else out << s;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// IdConverter

int IdConverter::Filter(char c) const
{
	return (unsigned char) c;
}
char IdConverter::Conv(symbol_arg s) const
{
	return (unsigned char) s;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// AlphaConverter, AlphaSpaceConverter

int AlphaConverter::Filter(char c) const
{
	c=toupper((unsigned char)c)-'A';
	if (c>=0 && c<26) return c; // only A..Z
	return -1;
}
char AlphaConverter::Conv(symbol_arg s) const
{
	return 'A'+(char)s;
}

int AlphaSpaceConverter::Filter(char c) const
{
	if (c==' ') return 26;
	c=toupper(c)-'A';
	if (c>=0 && c<26) return c; // only A..Z
	return -1;
}
char AlphaSpaceConverter::Conv(symbol_arg s) const
{
	if (s==26) return ' ';
	return 'A'+(char)s;
}


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// ApplicationConverter
int AppConverter::Filter(char c) const
{
	return Alphabet[(unsigned char)c];
}
char AppConverter::Conv(symbol_arg s) const
{
	return InvAlphabet[(unsigned char)s];
}

void AppConverter::SetAlphabet(char *NewAlphabet, int CaseMode)
{
	int i;

	m_Modulus = strlen(NewAlphabet);
	for(i=0;i<256;i++) Alphabet[i]=-1;

	if(CaseMode) { // Case insensitive
		_strlwr(NewAlphabet);
		for(i=0;i<((int)m_Modulus);i++) {
			Alphabet[(unsigned char)NewAlphabet[i]] = i;
			InvAlphabet[i] = NewAlphabet[i];
		}
		_strupr(NewAlphabet);
		for(i=0;i<((int)m_Modulus);i++) {
			Alphabet[(unsigned char)NewAlphabet[i]] = i;
			InvAlphabet[i] = NewAlphabet[i];
		}
	}
	else { // Case sensitive
		for(i=0;i<((int)m_Modulus);i++) {
			Alphabet[(unsigned char)NewAlphabet[i]] = i;
			InvAlphabet[i] = NewAlphabet[i];
		}
	}
}

int AppConverter::IsInAlphabet(unsigned char c)
{
	if(Alphabet[c] != -1) return 1;
	return 0;
}
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// BinConverter
int BinConverter::Filter(char c) const
{
	if (c=='0' || c=='1') return c-'0'; // only 0 and 1
	return -1;
}

char BinConverter::Conv(symbol_arg s) const
{
	return '0'+(char)s;
}


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// TupleConverter/TripleConverter

TupleConverter::TupleConverter(const TupleConverter &src) 
{
	m_Cnv1= src.m_Cnv1->Clone();
	m_Cnv2= src.m_Cnv2->Clone();
	m_Modulus=src.m_Modulus;
}
TupleConverter::~TupleConverter() 
{
	delete m_Cnv1;
	delete m_Cnv2;
}
TupleConverter::TupleConverter(const Converter& c1, const Converter& c2) 
{
	m_Cnv1=c1.Clone(); m_Cnv2=c2.Clone();
	m_Modulus=m_Cnv1->GetModulus()*m_Cnv2->GetModulus();
}


int TupleConverter::ReadSymbol(istream& in, symbol& s) const
{
	symbol s1,s2;
	int r=m_Cnv1->ReadSymbol(in,s1);
	if (r) r=m_Cnv2->ReadSymbol(in,s2);
	if (r) s=Combine(s1,s2);
	return r;
}
void TupleConverter::WriteSymbol(ostream& out, symbol_arg s) const
{
	out << GetFormat(TupleBegin);
	m_Cnv1->WriteSymbol(out,Part1(s));
	out << GetFormat(TupleSep);
	m_Cnv2->WriteSymbol(out,Part2(s));
	out << GetFormat(TupleEnd);
}

/////////////////////////////////////////////////////////////////////

TripleConverter::TripleConverter(const TripleConverter &src) 
{
	m_Cnv1= src.m_Cnv1->Clone();
	m_Cnv2= src.m_Cnv2->Clone();
	m_Cnv3= src.m_Cnv3->Clone();
	m_Modulus=src.m_Modulus;
}
TripleConverter::~TripleConverter() 
{
	delete m_Cnv1;
	delete m_Cnv2;
	delete m_Cnv3;
}

TripleConverter::TripleConverter(const Converter& c1, const Converter& c2, const Converter& c3) 
{
	m_Cnv1=c1.Clone(); m_Cnv2=c2.Clone(); m_Cnv3=c3.Clone();
	m_Modulus=m_Cnv1->GetModulus()*m_Cnv2->GetModulus()*m_Cnv3->GetModulus();
}


int TripleConverter::ReadSymbol(istream& in, symbol& s) const
{
	symbol s1,s2,s3;
	int r=m_Cnv1->ReadSymbol(in,s1);
	if (r) r=m_Cnv2->ReadSymbol(in,s2);
	if (r) r=m_Cnv3->ReadSymbol(in,s3);
	if (r) s=Combine(s1,s2,s3);
	return r;
}
void TripleConverter::WriteSymbol(ostream& out, symbol_arg s) const
{
	out << GetFormat(TupleBegin);
	m_Cnv1->WriteSymbol(out,Part1(s));
	out << GetFormat(TupleSep);
	m_Cnv2->WriteSymbol(out,Part2(s));
	out << GetFormat(TupleSep);
	m_Cnv3->WriteSymbol(out,Part3(s));
	out << GetFormat(TupleEnd);
}



