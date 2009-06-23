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

#include "SBox.h"

#ifndef _ITERATOR2_H
#include "Iterator2.h"
#endif


SBoxTable::SBoxTable(int sr, int dr, domain table[]) : m_SBoxTable(sr,table)
{ 
	m_SourceRange=sr; 
	m_DestRange=dr;	
}

SBoxTable::SBoxTable(const SymbolArray& Vec)
{
	m_SourceRange=Vec.GetSize();
	m_DestRange=Vec.GetModulus();
	m_SBoxTable.SetSize(m_SourceRange);
	for (int i=0;i<m_SourceRange;i++)
		m_SBoxTable[i]=Vec[i];
}

SBoxTable::SBoxTable(const NTuple<long>& Vec, int dr /*=0*/)
{
	m_SourceRange=Vec.GetSize();
	if (dr==0) dr=Vec.GetMax()+1;
	m_DestRange=dr;
	m_SBoxTable.SetSize(m_SourceRange);
	for (int i=0;i<m_SourceRange;i++)
		m_SBoxTable[i]=Vec[i];
}
SBoxTable::SBoxTable(const NTuple<unsigned long>& Vec, int dr /*=0*/)
{
	m_SourceRange=Vec.GetSize();
	if (dr==0) dr=Vec.GetMax()+1;
	m_DestRange=dr;
	m_SBoxTable.SetSize(m_SourceRange);
	for (int i=0;i<m_SourceRange;i++)
		m_SBoxTable[i]=Vec[i];
}

SBoxTable::SBoxTable(Permutation& Perm) : m_SBoxTable()
{
	m_SourceRange=m_DestRange=1<<Perm.GetSize();
	m_SBoxTable.SetSize(m_SourceRange);
	for (range i=0; i<m_SourceRange; i++) {
		domain r=0;
		int l=Perm.GetSize();
		for (int j=0; j<l; j++) {
			if (testbit(i,j)) setbit(r,Perm(j));
		}
		m_SBoxTable[i]=r;
	}
}

// invert SBox, return 1 if inversion was successfull, return 0 otherwise
// if inversion fails, SBox(i)=-1 where some i
int SBoxTable::invert() 
{
	const domain unused = 0xFFFFFFFF; //-1;

	int r=(m_SourceRange==m_DestRange)?1:0; // if sourcesize!=destsize invert cannot succeed
	arraytype tmp(m_DestRange);
	for (range i=0;i<m_DestRange;i++) tmp[i]= unused;

	for (range j=0;j<m_SourceRange;j++) {
		if (tmp[m_SBoxTable[j]]==unused) tmp[m_SBoxTable[j]]=j;
		else r=0;
	}

#if !defined(_MSC_VER) || _MSC_VER <= 1200
	swap(m_SourceRange,m_DestRange);
#else
    std::swap(m_SourceRange,m_DestRange);
#endif
	m_SBoxTable.Copy(tmp);

	return r;
}


void SBox::Show(OStream& out /*=DefaultOStream*/) const
{
	if (out[OStream::Title]) 
		out << "SBox (f: Z" << InRange() << "->Z" << OutRange() << ")" << endl;
	range l=InRange();
	for (range i=0;i<l;i++)
		out << i << "->" << (*this)(i) << " ";
	out << endl;
}

/////////////////////////////////////////////////////////////////////

void SBoxPerm::operator()(NTupleRW<symbol>& Vec, int mode /*=Encrypt*/) const
{
	static Array<symbol,symbol> tmp(m_size);  tmp.Clear();

	if (mode==Encrypt) {
		int l=InBits();
		for (int i=0; i<l; i++) {
			if (testbit(Vec[i/SymbolArray::MaxBits()],i%SymbolArray::MaxBits())) {
				int j=m_Perm(i);
				setbit(tmp[j/SymbolArray::MaxBits()],j%SymbolArray::MaxBits());
			}
		}
	} else { // mode==Decrypt
		int l=OutBits();
		for (int i=0; i<l; i++) {
			int j=m_Perm(i);
			if (testbit(Vec[j/SymbolArray::MaxBits()],j%SymbolArray::MaxBits())) 
				setbit(tmp[i/SymbolArray::MaxBits()],i%SymbolArray::MaxBits());
		}
	}
	for (int j=0; j<m_size; j++)
		Vec[j]=tmp[j];
}

SBox::domain SBoxPerm::operator()(SBox::codomain x, int mode /*=Encrypt*/) const
{
	SBox::domain r=0;
	if (mode==Encrypt) {
		int l=InBits();
		for (int i=0; i<l; i++) {
			if (testbit(x,i)) setbit(r,m_Perm(i));
		}
	} else { // mode==Decrypt
		int l=OutBits();
		for (int i=0; i<l; i++) {
			int j=m_Perm(i);
			if (testbit(x,j)) setbit(r,i);
		}
	}
	return r;
}

////////////////////////////////////////////////////////////////////
void SBoxPerm2::operator()(NTupleRW<symbol>& Vec, int mode /*=Encrypt*/) const
{
	static Array<symbol,symbol> tmp(m_size); tmp.Clear();

	if (mode==Encrypt) {
		int l=InBits();
		for (int i=0; i<l; i++) {
			if (testbit(Vec[i/SymbolArray::MaxBits()],SymbolArray::MaxBits()-1-i%SymbolArray::MaxBits())) {
				int j=m_Perm(i);
				setbit(tmp[j/SymbolArray::MaxBits()],SymbolArray::MaxBits()-1-j%SymbolArray::MaxBits());
			}
		}
	} else { // mode==Decrypt
		int l=OutBits();
		for (int i=0; i<l; i++) {
			int j=m_Perm(i);
			if (testbit(Vec[j/SymbolArray::MaxBits()],SymbolArray::MaxBits()-1-j%SymbolArray::MaxBits())) 
				setbit(tmp[i/SymbolArray::MaxBits()],SymbolArray::MaxBits()-1-i%SymbolArray::MaxBits());
		}
	}
	for (int j=0; j<m_size; j++)
		Vec[j]=tmp[j];
}

SBox::domain SBoxPerm2::operator()(SBox::codomain x, int mode /*=Encrypt*/) const
{
	SBox::domain r=0;
	if (mode==Encrypt) {
		int l=InBits();
		for (int i=0; i<l; i++) {
			if (testbit(x,SymbolArray::MaxBits()-1-i))
				setbit(r,SymbolArray::MaxBits()-1-m_Perm(i));
		}
	} else { // mode==Decrypt
		int l=OutBits();
		for (int i=0; i<l; i++) {
			int j=m_Perm(i);
			if (testbit(x,SymbolArray::MaxBits()-1-j))
				setbit(r,SymbolArray::MaxBits()-1-i);
		}
	}
	return r;
}


////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//  DifferenceDistributionTable
// (2^n,2^m)-Matrix

DifferenceDistributionTable::DifferenceDistributionTable(const SBox& sbox) : baseclass(sbox.InRange(),sbox.OutRange()), m_SBox(sbox)
{
	int n=sbox.InRange();
	int m=sbox.OutRange();

	for (int x=0;x<n;x++) { // check completely
		int f=sbox(x);
		for (int i=0;i<n;i++) {
			int v=f^sbox(x^i);
			// mark (i,v)
			Set2(i*m+v); 
		} /* for i */
		IncrementTotalCount();
	} /* for x */
}

void DifferenceDistributionTable::Show(OStream& out /*=DefaultOStream*/) const
{
	if (out[OStream::Title]) 
		out << "Difference Distribution Table" << endl;
	baseclass::Show(out);
}

///////////////////////////////////////////////////////////////////
//  DependenceTable
//  Abhängigkeitsmatrix einer Funktion f: F2(n) -> F2(m)
//  ist (n,m)-Matrix

DependenceTable::DependenceTable(const SBox& sbox, int mode /*=0*/) : baseclass(sbox.InBits(),sbox.OutBits())
{
	int n=sbox.InBits();
	int m=sbox.OutBits();
	ASSERT (sbox.InRange()==1<<n);
	ASSERT (sbox.OutRange()==1<<m);

	if (mode==0 && n>16) mode=65535;

	int f,v;
	if (mode<=1) { // check completely
		for (int x=0;x<sbox.InRange();x++) {
			f=sbox(x);
			for (int i=0;i<n;i++) {
				v=f^sbox(x^(1<<i));
				// mark the modified bits (i,j)
				int j=0;
				while (v) {
					if (v&1) Set2(i*m+j); 
					v>>=1; j++;
				}
			} /* for i */
			IncrementTotalCount();
		} /* for x */
	} else { // choose x at random
		for (int x2=0;x2<mode;x2++) {
			int x=RANDOM(sbox.InRange());
			f=sbox(x);
			for (int i=0;i<n;i++) {
				v=f^sbox(x^(1<<i));
				// mark the modified bits (i,j)
				int j=0;
				while (v) {
					if (v&1) Set2(i*m+j); 
					v>>=1; j++;
				}
			} /* for i */
			IncrementTotalCount();
		} /* for x2 */
	}
}
void DependenceTable::Show(OStream& out /*=DefaultOStream*/) const
{
	if (out[OStream::Title]) 
		out << "Abhängigkeitsmatrix" << endl;
	baseclass::Show(out);
}


////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//  LinearDistributionTable
// (2^n,2^m)-Matrix

static inline int ODDBITS(int x)
{
	int n=0;
	while (x) {
		if (x&1) n^=1;
		x>>=1;
	}
	return n;
}

LinearDistributionTable::LinearDistributionTable(const SBox& sbox) : baseclass(sbox.InRange(),sbox.OutRange()), m_SBox(sbox)
{
	int n=sbox.InRange();
	int m=sbox.OutRange();
	
	for (int i=0;i<n;i++) { // check completely
		int f=sbox(i);
		for (int x=0;x<n;x++)
			for (int y=0;y<m;y++) {
				if (ODDBITS((x&i) ^ (y&f)))
					Set2(x*m+y); 
		} /* for y */
		IncrementTotalCount();
	} /* for i */
}

void LinearDistributionTable::Show(OStream& out /*=DefaultOStream*/) const
{
	if (out[OStream::Title]) 
		out << "Linear Distribution Table" << endl;
	baseclass::Show(out);
}



