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

#include "NGram.h"

#ifndef _SYMBOLARRAY_H
#include "SymbolArray.h"
#endif
#ifndef _CHI2_H
#include "Chi2.h"
#endif
#ifndef _OSTREAM_H
#include "la_ostream.h"
#endif

#include <limits.h>

///////////////////////////////////////////////////////////////////
//  NGram

void NGram::Init(int d, int n)
{
	ASSERT(d>0 && n>0);
	m_Rows=d;
	ASSERT(pow((double)m_Rows,(double)(n-1)) < INT_MAX);
	m_Columns=(int)pow((double)m_Rows,(double)(n-1));
	m_dim=d; m_N=n; 
	ASSERT(pow((double)d,n) < INT_MAX);
	m_hcount.SetSize((int)pow((long)d,n));
	//m_totalcount=0;
	m_Converter=NULL;
}

void NGram::Calc(const NTuple<symbol>& Vec, int step /*=1*/)
{
	int len=Vec.GetSize()-(m_N-1);
	symbol idx;
	for (int i=0;i<len;i+=step) { 
		idx=(symbol)Vec[i];
		for (int j=1;j<m_N;j++) { 
			idx*=m_dim; 
			idx+=(symbol)Vec[i+j];
		}	
		Set(idx);
	}
}


NGram::NGram(int d, int n /*=1*/ )  
{
	Init(d,n);
}

NGram::NGram(const SymbolArray& Vec, int n /*=1*/, int step /*=1*/)
{ // HACK
	Init(Vec.GetModulus(),n);
	Calc(Vec,step);
	m_Converter=Vec.GetConverter()->Clone();
}

NGram::NGram(int d, const NTuple<symbol>& Vec, int n /*=1*/, int step /*=1*/)
// Hinweis: d als 1. Parameter. um NGram(SymbolArray) von NGram(NTuple) zu unterscheiden
{
	Init(d,n);
	Calc(Vec,step);
}

NGram::~NGram()  
{
	if (m_Converter) delete m_Converter;
}


////////////////////////////////////////////////////////////////////

double NGram::Entropie() const
{
	double h=0.0;

	if (!m_N) return h;

	int l=GetSize();
	for (int i=0;i<l;i++) {
		double p=GetFrequency(i);
		if (p) h-=p*log2(p);
	}
	return h/m_N;
}

double NGram::NEntropie(const SymbolArray &s) const
{
	return NEntropie(NGram(s));
}
double NGram::NEntropie(const NGram& ng) const
{
	double h=0.0;

	ASSERT(ng.GetSize()==GetSize());
	int l=ng.GetSize();
	for (int i=0;i<l;i++) {
		double p=GetFrequency(i);
		if (p) h-=ng.GetCount(i)*log2(p);
	}
	return h;
}

double NGram::Redundanz() const
{
	return log2((double)m_dim)-Entropie();
}

double NGram::Gleichverteilt() const
{
	//Chi2 t(*this,GetTotalCount());
	Chi2 t(FreqCountTable(*this));
	double r=t();
	return r;
}

double NGram::Koinzidenz() const
{
	double s=0.0;

	for (int i=0;i<GetSize();i++) {
		s+=GetCount(i)*(GetCount(i)-1);
	}
	double n=GetTotalCount();
	if (n==0 || n==1) return 0.0;
	return s/(n*(n-1));
}

/////////////////////////////////////////////////////////////////////
void NGram::Load(istream& stream)
{
	LoadObject(m_dim,stream);
	LoadObject(m_N,stream);
	baseclass::Load(stream);
}

void NGram::Save(ostream& stream) const
{
	SaveObject(m_dim,stream);
	SaveObject(m_N,stream);
	baseclass::Save(stream);
}

void NGram::Show(OStream& out /*=DefaultOStream*/) const
{
	if (out[OStream::Title]) {
		if (m_N==1) out << "Histogramm" << endl; 
		else if (m_N==2) out << "Bigramm" << endl;
		else if (m_N==3) out << "Trigramm" << endl;
		else out << m_N << "-gramm" << endl;
	}
	baseclass::Show(out);
}


/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//  RunTable

RunTable::RunTable(const NTuple<symbol>& Vec, int mode /*=0*/, int maxrun /*=0*/) 
{
	int l=Vec.GetSize();
	int i=0;
	if (maxrun) m_hcount.SetSize(maxrun);
	while (i<l) {
		i++;
		long r=1;
		if (mode==0) { // aufsteigende Runs
			while (i<l && Vec[i]>=Vec[i-1]) { // max run length
				i++;
				r++; 
			}
		} else if (mode==1) { // mode==1, absteigende Runs
			while (i<l && Vec[i]<=Vec[i-1]) {
				i++;
				r++; 
			}
		} else { // mode==2, Gleichheit
			while (i<l && Vec[i]==Vec[i-1]) {
				i++;
				r++; 
			}
		}

		if (maxrun && r>maxrun) r=maxrun;
		// grow array if necc.
		if (r>=m_hcount.GetSize()) 
			m_hcount.SetSize(r+1);
		// set found run
		Set(r);
	}
	m_Rows=m_hcount.GetSize();
}
void RunTable::Show(OStream& out /*=DefaultOStream*/) const
{
	if (out[OStream::Title]) 
		out << "Anzahl Runs der Länge:" << endl;
	baseclass::Show(out);
}
