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

#ifndef _ITERATOR2_H
#define _ITERATOR2_H 1

// Iterator2.h enthaelt die "nicht-inline" Template-Funktionen
// zu NTuple<TYPE> aus Iterator.h
// Muss daher nur eingebunden werden, wenn eine entsprechendes
// NTuple<TYPE> instantiiert werden soll.

#ifndef _ITERATOR_H
#include "Iterator.h"
#endif

//#include "la_ostream.h"
// using namespace std;

/////////////////////////////////////////////////////////////////////
// NTuple<TYPE> functions ('extern' declarations)

#ifdef GCC_WORKAROUND
class String;
#ifndef _SORTPAIR_H
#include "SortPair.h"
#endif

#define DONTINST(X)									 \
	X NTuple < ## X >::GetAverage(int,int) const;	 \
	X NTuple < ## X >::GetSum(int,int) const;
#define DONTINST2(X) DONTINST(X)					 \
	int NTuple < ## X >::GetMinPos(int,int) const;	 \
	int NTuple < ## X >::GetMaxPos(int,int) const;	 \
	X NTuple < ## X >::GetMin(int,int) const;		 \
	X NTuple < ## X >::GetMax(int,int) const;

// NTuple mit folgenden Basisklassen erlauben keine
// Berechnungen. Deswegen die Funktionen GetMin/Max/...
// als extern deklarieren, so dass sie nicht per
// Template instantiiert werden.
/*DONTINST2(String)
DONTINST2(SortPair<double>)
DONTINST2(SortPair<long>)
DONTINST2(SortPair<unsigned long>)
DONTINST2(SortPair<int>)*/

#undef DONTINST
#undef DONTINST2
#endif /* GCC_WORKAROUND */

/////////////////////////////////////////////////////////////////////
// NTuple<TYPE> functions

template <class TYPE>
int NTuple<TYPE>::GetMinPos(int start /*=0*/, int len /*=0*/) const
{
	int end=len?start+len:GetSize();
	if (start>=end) return start;
	int pos;
	TYPE value,tmp;
	pos=start; value=(*this)[pos];

	for (int i=start+1;i<end;i++) {
		if ((tmp=(*this)[i])<value) {
			pos=i; value=tmp;
		}
	}
	return pos;
}

template <class TYPE>
int NTuple<TYPE>::GetMaxPos(int start /*=0*/, int len /*=0*/) const
{
	int end=len?start+len:GetSize();
	if (start>=end) return start;
	int pos;
	TYPE value,tmp;
	pos=start; value=(*this)[pos];

	for (int i=start+1;i<end;i++) {
		if ((tmp=(*this)[i])>value) {
			pos=i; value=tmp;
		}
	}
	return pos;
}

template <class TYPE>
TYPE NTuple<TYPE>::GetSum(int start /*=0*/, int len /*=0*/) const
{
	int end=len?start+len:GetSize();
	TYPE value=(TYPE)0;
	for (int i=start;i<end;i++)
		value+=(*this)[i];
	return value;
}

template <class TYPE>
inline TYPE NTuple<TYPE>::GetMin(int start /*=0*/, int len /*=0*/) const
{
	return (*this)[GetMinPos(start,len)];
}

template <class TYPE>
inline TYPE NTuple<TYPE>::GetMax(int start /*=0*/, int len /*=0*/) const
{
	return (*this)[this->GetMaxPos(start,len)];
}

template <class TYPE>
inline TYPE NTuple<TYPE>::GetAverage(int start /*=0*/, int len /*=0*/) const
{
	return this->GetSum(start,len)/(len?len:GetSize());
}

/////////////////////////////////////////////////////////////////////
// NTuple<TYPE> Show

// die folgende Include-Datei kann erst hier eingebunden werden, da dort
// Array.h benoetigt wird - und dazu NTuple!
#ifndef _OSTREAM_H
#include "la_ostream.h"
#endif

template <class TYPE>
void NTuple<TYPE>::Show(OStream& out /*=DefaultOStream*/) const
{
	if (out[OStream::Title])
		out << "(Length: " << GetSize() << ")" << endl;
	int l=GetSize()-out[OStream::Start];
	if (out[OStream::Size] && out[OStream::Size]<l) l=out[OStream::Size];
	for (int i=out[OStream::Start];i<l;i++)
		out << (*this)[i] << sep;
	out << endl;
}

/////////////////////////////////////////////////////////////////////

#ifndef _SUBARRAY_H
#include "SubArray.h"
#endif

#ifndef _SORTEDARRAY_H
#include "SortedArray.h"
#endif

#include "mymath.h"


template <class TYPE>
void NTuple<TYPE>::Show(OStream& out, int ignore) const
{
	NTuple<TYPE>* v=NULL;

	if (out[OStream::Start] || out[OStream::Size]) {
		int len=GetSize()-out[OStream::Start];
		if (out[OStream::Size]) len=min((int)out[OStream::Size],(int)len);
		v= new SubArrayRO<TYPE>(*this,out[OStream::Start],len);
	}
	SortedArray<TYPE> s(v?*v:*this, out[OStream::Sorted]);

	int l=s.GetSize();
	int l1=0;
	int l2=0;
	if (out[OStream::MaxN]>=0) {
		l1= (out[OStream::Sorted]==OStream::Descending) ? out[OStream::MaxN] : out[OStream::MinN];
		l2= l-((out[OStream::Sorted]==OStream::Descending) ? out[OStream::MinN] : out[OStream::MaxN]);
	}
	// Gib [0..l1[ und [l2..l[ aus
	int i;
	for (i=0;i<l1; i++) {
		if (out[OStream::Description]) out << (s[i]+out[OStream::Start]) << ": ";
		out << s.GetValue(i) << endl;
	}
	for (i=l2;i<l; i++) {
		if (out[OStream::Description]) out << (s[i]+out[OStream::Start]) << ": ";
		out << s.GetValue(i) << endl;
	}
	if (v) delete v;
}

template <class TYPE>
void NTuple<TYPE>::Show(OStream& out, int rows, int columns) const
{
	int width=out[OStream::Width];
	int twidth=out[OStream::Width];

	if (out[OStream::Description]) {
		// print the title line
		if (rows>1 && columns>1) {
			(ostream&)out << setw(twidth) << " ";
			out << "  ";
			for (int i=0; i<columns; i++) {
				(ostream&)out << setw(width) << i;
				if (i<columns-1) out << sep;
			}
			out << endl;
			(ostream&)out << setw(twidth) << " ";
			out << "  ";
			int l=columns*width+(columns-1)*strlen(out[OStream::Sep]);
			for (int j=0; j<l; j++)
				out << "-";
			out << endl;
		}
	}
	// print the rows
	for (int j=0;j<rows;j++) {
		if (out[OStream::Description]) {
			//if (m_Converter)  m_converter->WriteSymbol(out,j);
			//else
			(ostream&)out << setw(twidth) << j << ": ";
		}
		for (int i=j*columns, l=min(GetSize(),(j+1)*columns);i<l;i++) {
			(ostream&)out << setw(width) << (*this)[i];
			if (i<l-1)out << sep;
		}
		out << endl;
	}
}


#endif /* _ITERATOR2_H */
