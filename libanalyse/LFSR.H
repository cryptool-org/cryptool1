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

#ifndef _LFSR_H
#define _LFSR_H 1

#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _String_h
#include "la_string.h"
#endif
#ifndef _SYMBOL_H
#include "Symbol.h"
#endif
#ifndef _ARRAY_H
#include "Array.h"
#endif

class SymbolArray;
class String;

///////////////////////////////////////////////////////////////////
//  LFSR: Linear Feedback Shift Register

class LFSR : public Iterator<Symbol>
{
public:
	typedef Symbol symbol;
	typedef Modulus modulus;
private:
	typedef Array<symbol,symbol> arraytype;
public:
// Constructors
	EXPLICIT LFSR(int mod=2);
	EXPLICIT LFSR(const SymbolArray& Vec);
	EXPLICIT LFSR(const NTuple<symbol>& Vec, modulus mod=2); 
	EXPLICIT LFSR(const char* polynom, modulus mod=2);
	LFSR(const LFSR& src);
// Berlekamp-Massey
	void BerlekampMassey();
	void BerlekampMassey(const NTuple<symbol>& vec);
// Accessors
	modulus GetModulus() const;
	int GetDegree() const;
//
	symbol GetCoeff(int i) const;
	symbol GetInitialState(int i) const;
	symbol GetCurrentState(int i) const;
//
	String GetPolynomial() const;
	String GetInitialState() const;
	String GetCurrentState() const;

// Attributes
	int Init();
	void SetState();
	void SetState(const NTuple<symbol>& vec);
// Operations
	symbol next();
	int eof() const {return 0;}
	// Analysis TODO
	//SymbolArray Linearitaetsprofil
	// I/O
	void Load(istream& stream); 
	void Save(ostream& stream) const; 
	void Show(OStream& out=DefaultOStream) const;

// Implementation
private:
	void operator=(const LFSR& src);
	// Helpers
private:
	void ReadString(const char *polynom);
	// Data
private:
	modulus m_Modulus;
	arraytype m_Coeff;
	arraytype m_State; // [0] is the highest register, i.e. it is output next
	arraytype m_InitialState;
};

/////////////////////////////////////////////////////////////////////
// inline functions

inline int LFSR::Init()
{
	m_State.Copy(m_InitialState);
	return 1;
}

inline int LFSR::GetDegree() const
{
	return m_Coeff.GetSize(); 
}
inline LFSR::symbol LFSR::GetCoeff(int i) const
{
	ASSERT (0>=i && i<GetDegree());
	return m_Coeff[i]; 
}
inline LFSR::symbol LFSR::GetCurrentState(int i) const
{ 
	ASSERT (0>=i && i<GetDegree());
	return m_State[i]; 
}
inline LFSR::modulus LFSR::GetModulus() const 
{
	return m_Modulus;
}

inline LFSR::LFSR(int mod /*=2*/) : m_Coeff() , m_State(), m_InitialState()
{
	m_Modulus=mod;
	SetState();		
}

inline void LFSR::BerlekampMassey()
{
	arraytype vec;
	vec.Copy(m_Coeff);
	BerlekampMassey(vec); 
}


#endif /* _LFSR_H */
