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

#include "Permutation.h"

#ifndef _SYMBOLARRAY_H
#include "SymbolArray.h"
#endif
#ifndef _ITERATOR2_H
#include "Iterator2.h"
#endif
#ifndef _OSTREAM_H
#include "la_ostream.h"
#endif

#include "la_string.h"
#include "mymath.h"

////////////////////////////////////////////////////////////////////
// Permutation

////////////////////////////////////////////////////////////////////
// Note: for last block handling: 
// X.Apply(perm).Apply(perm.invert()) != X - use Encrypt/Decrypt option for that purpose
void Permutation::operator()(NTupleRW<symbol>& Vec, int mode /*=Encrypt*/) const
{
	int plen=GetSize();
	int len=Vec.GetSize();
	ASSERT(len<=plen);

	Array<symbol,symbol> tmp(plen);

	const Permutation& perm=*this;

	int i,j;
	if (mode==Encrypt) {
		if (len==plen) { 
			for (i=0; i<plen; i++) 
				tmp[perm(i)]=Vec[i];
		} else { // last block handling
			for (i=0, j=0; i<len; i++, j++) {
				while (perm(j)>=len) j++;
				tmp[perm(j)]=Vec[i];
			}
		}
	} else { // mode==Decrypt
		if (len==plen) {
			for (i=0; i<plen; i++) 
				tmp[i]=Vec[perm(i)];
		} else { // last block handling 
			for (i=0, j=0; i<len; i++, j++) {
				while (perm(j)>=len) j++;
				tmp[i]=Vec[perm(j)];
			}
		}
	} // if(mode) 
	for (i=0; i<len; i++) 
		Vec[i]=tmp[i];
}

////////////////////////////////////////////////////////////////////
// Permutation - Show

void Permutation::Show(OStream& out /*=DefaultOStream*/) const
{
	if (out[OStream::Title]) 
		out << "Permutation (length=" << GetSize() << ")" << endl;
	for (int i=0;i<GetSize();i++)
		//out << "(" << i << "," << (*this)(i) << ") ";
		out << (*this)(i)+1 << " ";
	out << endl;
}

////////////////////////////////////////////////////////////////////
// Permutation - Analyse

// ...x... -> ...x...
int Permutation::FixPunkte() const
{
	const Permutation &perm=*this;
	int f=0;
	int l=perm.GetSize();
	for (int i=0; i<l; i++)
		if (perm(i)==i) f++;
	return f;
}

// ...xy... -> .....xy..
int Permutation::FixTupel() const
{
	const Permutation &perm=*this;
	int f=0;
	int l=perm.GetSize();
	for (int i=0; i<l-1; i++)
		if (perm(i)+1==perm(i+1)) f++;
	if (perm(l-1)==(l-1) && perm(0)==0) f++; // ....x|y... -> ..x|y...
	return f;
}

// ...xy... -> .....yx..
int Permutation::IFixTupel() const
{
	const Permutation &perm=*this;
	int f=0;
	int l=perm.GetSize();
	for (int i=0; i<l-1; i++)
		if (perm(i)==perm(i+1)+1) f++;
	return f;
}

// Summe |i-perm(i)|
double Permutation::MittlererAbstand() const
{
	const Permutation &perm=*this;
	int f=0;
	int l=perm.GetSize();
	for (int i=0; i<l; i++)
		f+=abs(i-perm(i));
	return (double)f/perm.GetSize();
}

// Summe |perm(i)-perm(i+1)|
double Permutation::MittlererAbstand2() const
{
	const Permutation &perm=*this;
	int f=0;
	int l=perm.GetSize();
	for (int i=0; i<l-1; i++)
		f+=abs(perm(i)-perm(i+1));
	f+=abs(perm(l-1)-perm(0));
	return (double)f/perm.GetSize();
}

////////////////////////////////////////////////////////////////////
// Permutation::GetPerm

String Permutation::GetPerm() const
{
	String s;
	int l=GetSize();
	Array<long,long> used(l+1); // used[l+1] is used as upper bound
	int i=0;

	while (i<l) {
		s+="(";
		int j=i;
		do {
			s+=ToString(j+1);
			used[j]=1;
			j=(*this)(j);
			if (i!=j) s+=" ";
		} while (i!=j);
		s+=")";
		while (used[++i]) ; // finally stops at used[l+1]!
	}
	return s;
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
// PermTable

PermTable::PermTable(const NTuple<long>& Vec)
{
	m_Length=Vec.GetSize();
	m_PermTable.SetSize(m_Length);
	for (int i=0;i<m_Length;i++)
		m_PermTable[i]=Vec[i];
}
PermTable::PermTable(const NTuple<unsigned long>& Vec)
{
	m_Length=Vec.GetSize();
	m_PermTable.SetSize(m_Length);
	for (int i=0;i<m_Length;i++)
		m_PermTable[i]=Vec[i];
}
PermTable::PermTable(int len /*=1*/) : m_PermTable(len)
{
	m_Length=len;
	for (int i=0;i<m_Length;i++) 
		m_PermTable[i]=i;
}
PermTable::PermTable(const char* s)
{
	ReadString(s);
}
PermTable::PermTable(const Permutation& p1, const Permutation& p2)
{
	m_Length=kgv(p1.GetSize(),p2.GetSize());
	m_PermTable.SetSize(m_Length);
	for (int i=0;i<m_Length;i++) {
		long t=p1(i%p1.GetSize())+(i-i%p1.GetSize());
		m_PermTable[i]=p2(t%p2.GetSize())+(t-t%p2.GetSize());
	}
}

////////////////////////////////////////////////////////////////////
void PermTable::invert() 
{
	arraytype tmp;
	tmp.Copy(m_PermTable);
	for (int i=0;i<m_Length;i++)
		m_PermTable[tmp[i]]=i;
}

////////////////////////////////////////////////////////////////////
int PermTable::next() //next in lexicographical order
// return: 1=ok, 0=no nextz (i.e. is (l-1,l-2,...0) )
{
	int i=m_Length-2;
	while (m_PermTable[i]>m_PermTable[i+1]) 
		if ((i--)==0) return 0;

	int j=m_Length-1;
	while (m_PermTable[j]<=m_PermTable[i]) j--;

	#if !defined(_MSC_VER) || _MSC_VER <= 1200
	swap(m_PermTable[i],m_PermTable[j]);
    #else
	std::swap(m_PermTable[i],m_PermTable[j]);
    #endif
	
	j=m_Length;
	while ((++i)<(--j)) {
#if !defined(_MSC_VER) || _MSC_VER <= 1200
	swap(m_PermTable[i],m_PermTable[j]);
#else
    std::swap(m_PermTable[i],m_PermTable[j]);
#endif
	}
	return 1;
}

////////////////////////////////////////////////////////////////////

void PermTable::ReadString(const char* s)
{
	// Zahlen beginnen bei 1
	if (*s!='(') { // normale Tabellenform
		SymbolArray tmp(s);
		m_Length=tmp.GetSize();

		m_PermTable.SetSize(m_Length);
		int offset=1; // Zahlen beginnen bei 1, ausser 0 kommt vor
		if (tmp.GetMin()<=0) offset=0;
		for (int i=0;i<m_Length;i++) 
			m_PermTable[i]=tmp[i]-offset;

		return;
	}
	while (*s) { // Zyklenform: Beginnt mit ( - Zahlen ab 1
		if (*s=='(') if (!*(++s)) break;
		long f,i;
		f=i=stol(s)-1;
		if (i<0) break;
		while (*s && *s!=')') {
			long j=stol(s)-1;
			if (j<0 || (i<m_PermTable.GetSize() && m_PermTable[i]))
			{ i=-1; break; }
			m_PermTable.SetGrow(i,j+1);
			i=j;
		}
		if (i<0) break;
		m_PermTable.SetGrow(i,f+1);
		s++;
	}
	m_Length=m_PermTable.GetSize();
	for (int i=0;i<m_Length;i++)
		m_PermTable[i]=m_PermTable[i]?m_PermTable[i]-1:i;
}



