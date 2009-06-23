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

#include "LFSR.h"

#ifndef _SYMBOLARRAY_H
#include "SymbolArray.h"
#endif
#ifndef _OSTREAM_H
#include "la_ostream.h"
#endif

/////////////////////////////////////////////////////////////////////
// LFSR


LFSR::LFSR(const LFSR& src) : m_Coeff(), m_State(), m_InitialState()
{
	m_Modulus=src.m_Modulus;
	m_Coeff.Copy(src.m_Coeff);
	m_InitialState.Copy(src.m_InitialState);
	m_State.Copy(src.m_State);
}
LFSR::LFSR(const NTuple<symbol>& Vec, modulus mod /*=2*/) : m_Coeff(0), m_State(0), m_InitialState(0)
{
	m_Modulus=mod;
	m_Coeff.Copy(Vec);
	SetState();
}
LFSR::LFSR(const SymbolArray& Vec) : m_Coeff(0), m_State(0), m_InitialState(0)
{
	m_Modulus=Vec.GetModulus();
	m_Coeff.Copy(Vec);
	SetState();
}
LFSR::LFSR(const char* polynom, modulus mod /*=2*/) : m_Coeff(0), m_State(0), m_InitialState(0)
// polynom: ([+|-][Zahl][x[^Zahl]])*, e.g. 1-2x-x^3
{
	m_Modulus=mod;
	ReadString(polynom);
	SetState();
}

	
//Create minimal LFSR that outputs vec using Berlekamp-Massey algorithm
void LFSR::BerlekampMassey(const NTuple<symbol>& vec)
{
	m_Coeff.SetSize(0);
	m_State.SetSize(0);	// for computation fm is stored in m_State

	m_Coeff.Allocate(vec.GetSize()/2+6); // to minimize reallocations!
	m_State.Allocate(vec.GetSize()/2+6);

	// arraytype lprofil; lprofil.SetSize(0);

	int m=-1;
	symbol dm=1;
	int n=vec.GetSize();

	for (int k=0;k<n;k++) {
		// Invariant: fk (m_Coeff) is feedback polynom with minimal degree

		// calculate next discrepancy d
		symbol d=0;
		int len=0; if (k) len=m_Coeff.GetSize();
		for (int i=0;i<len;i++) {
			d=d+m_Coeff[i]*vec[k-i-1];
			d=mod(d,m_Modulus);
		}
		d=mod(d-vec[k],m_Modulus);

		// now adjust feedback polynom, if neccessary
		if (d) {
			int m2=-1;
			arraytype fm2;

			if ((k+1)<=(2*len)) ;
			else {
				// m=k; fm=m_Coeff; (part I)
				m2=k;
				fm2.Copy(m_Coeff);
				// Lk+1=k+1-lk
				m_Coeff.SetSize(k+1-len); 
			}
			
			// fk+1 = fk - (dk dm^-1) x^(k-m)fm
			int /*symbol*/ c=(m_Modulus==2) ? 1 : mod(-(int)(symbol)(d*dm),m_Modulus);
			m_Coeff[k-m-1]=mod(m_Coeff[k-m-1]-c,m_Modulus);
			for (int i=0;i<m_State.GetSize();i++) 
				m_Coeff[i+k-m]=mod(m_Coeff[i+k-m]+c*m_State[i],m_Modulus);
			
			if (m2>=0) { // m=k; fm=m_Coeff; (part II)
				m=m2;
				m_State.Copy(fm2);
				dm=minverse(d,m_Modulus);
			}
		} /* if(d) */
		//lrprofil.Add(GetDegree()); // TODO Linearitaetsprofil
	} /* for i */

	// finally initialize m_State with the first Lk elements of vec
	SetState(vec);
}

void LFSR::ReadString(const char* polynom)
// polynom: ([+|-][Zahl][x[^Zahl]])*, e.g. 1-2x-x^3
{
	while (*polynom) {
		int neg=0, a=0, e=0;
		// initial '-' sign
		if (*polynom=='-') {
			neg=1;
			polynom++;
		}
		if (*polynom=='+') polynom++;
		// number
		if (*polynom=='x') a=1;
		else {
			a=stol(polynom);
		}
		if (*polynom=='x') {
			polynom++; if (*polynom=='^') polynom++;
			if (*polynom=='+' || *polynom=='-') e=1;
			else {
				e=stol(polynom);
			}
			if (e<=0) break;
			m_Coeff.SetGrow(e-1,mod(a,m_Modulus));
		}
	} /* while */
}


/////////////////////////////////////////////////////////////////////

LFSR::symbol LFSR::next()
{
	ASSERT (m_State.GetSize()>=m_Coeff.GetSize());
	int len=m_Coeff.GetSize();

	if (len==0) return 0;
	symbol r=m_State[0];
	symbol s=0;
	for (int i=0;i<len;i++) {
		s=mod(s+m_Coeff[len-1-i]*m_State[i],m_Modulus);
		m_State[i]=(i<len-1)?m_State[i+1]:s;
	}
	return r;
}


/////////////////////////////////////////////////////////////////////
void LFSR::SetState()
{
	// initialize m_InitialState with (0,...0,1)
	int len=m_Coeff.GetSize();
	m_InitialState.SetSize(len);
	for (int i=0;i<len;i++)	m_InitialState[i]=(i==(len-1))?1:0;
	Init();
}
void LFSR::SetState(const NTuple<symbol>& vec) 
{
	// initialize m_InitialState with vec (periodically repeated if necc.)
	int len=m_Coeff.GetSize();
	int vlen=vec.GetSize(); // if vec is emtpy initialize with (0,...0,1)
	if (!vlen) {SetState(); return;}
	m_InitialState.SetSize(len);
	for (int i=0;i<len;i++)
		m_InitialState[i]=vec[i%vlen];
	Init();
}

/////////////////////////////////////////////////////////////////////
String LFSR::GetPolynomial() const
{
	String s("1");

	int len=m_Coeff.GetSize();
	for (int i=0;i<len;i++) {
		if (m_Coeff[i]) 
		{
			s+="-";
			if (m_Coeff[i]!=1) s+=ToString(m_Coeff[i]);
			if (i) {
				s+="x^";
				s+=ToString(i+1);
			} else s+="x";
		}
	}
	return s;
};

String LFSR::GetInitialState() const
{
	String s("[");

	int len=m_InitialState.GetSize();
	for (int i=0;i<len;i++) {
		s+=ToString(m_InitialState[i]);
		if (i<(len-1)) s+=";";
	}
	s+="]";
	return s;
}
String LFSR::GetCurrentState() const
{
	String s("[");

	int len=m_State.GetSize();
	for (int i=0;i<len;i++) {
		s+=ToString(m_State[i]);
		if (i<(len-1)) s+=";";
	}
	s+="]";
	return s;
}

/////////////////////////////////////////////////////////////////////
void LFSR::Load(istream& stream)
{
	LoadObject(m_Modulus,stream);
	m_Coeff.Load(stream);
	m_InitialState.Load(stream);
	m_State.Load(stream);
}

void LFSR::Save(ostream& stream) const
{
	SaveObject(m_Modulus,stream);
	m_Coeff.Save(stream);
	m_InitialState.Save(stream);
	m_State.Save(stream);
}

/////////////////////////////////////////////////////////////////////
void LFSR::Show(OStream& out /*=DefaultOStream*/) const
{
	out << "LFSR Modulus: " << GetModulus() << "  -  Grad:   " << GetDegree() << endl;
	out << "     Polynom: " << GetPolynomial() << endl;
	out << "     Zustand: " << GetCurrentState() << endl;

	if (out[OStream::Details]) {
		out << "[";
		LFSR lfsr=*this;
		for (int i=0;i<20;i++) 
			out << lfsr.next() << sep;
		out << "]" << endl;
	}
}
