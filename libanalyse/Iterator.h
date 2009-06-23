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

#ifndef _ITERATOR_H
#define _ITERATOR_H 1

// Iterator.h definiert folgende Klassen:
// ***************************************
// Iterator
// NTuple
// NTupleRW
// SimpleArray

#ifndef _DEFAULT_H
#include "Default.h"
#endif

/////////////////////////////////////////////////////////////////////
// Iterator<TYPE>
template <class TYPE> class Iterator
{
public:
	virtual TYPE next()=0;
	virtual int eof() const=0;
	virtual int Init() {return 0;} //return 0 if no init, init fails, or 0 elements - else return 1
	virtual ~Iterator() {}
// Operators as short-cuts for eof()
	operator void *() const { if(eof()) return 0; return (void *)this; }
	int operator!() const {if (eof()) return 1; return 0;}
};

/////////////////////////////////////////////////////////////////////
// NTuple<TYPE>
template <class TYPE> class NTuple
{
public:
	virtual int GetSize() const=0;
	virtual TYPE operator[](int i) const=0;
	virtual ~NTuple() {}
// Show
	void Show(OStream& out=DefaultOStream) const;
	void Show(OStream& out, int ignore) const;
	void Show(OStream& out, int rows, int columns) const;
// Analysis
	int GetMinPos(int start=0, int len=0) const;
	int GetMaxPos(int start=0, int len=0) const;
	TYPE GetMin(int start=0, int len=0) const;
	TYPE GetMax(int start=0, int len=0) const;
	TYPE GetSum(int start=0, int len=0) const;
	TYPE GetAverage(int start=0, int len=0) const;
};

/////////////////////////////////////////////////////////////////////
// NTupleRW<TYPE>
template <class TYPE> 
class NTupleRW : public NTuple<TYPE>
{
public:
	virtual TYPE& operator[](int i)=0;
};

/////////////////////////////////////////////////////////////////////
// NTuple helper templates
template <class  D, class S> 
inline void Copy(D &d, S& s, int len)
{
	for (int i=0; i<len; i++) d[i]=s[i];
}

template <class  D, class S> 
inline void Copy(D &d, S& s, int len, int start)
{
	for (int i=start; i<len; i++) d[i]=s[i];
}


/////////////////////////////////////////////////////////////////////
// SimpleArray: implementiert NTupleRW mit Array statischer Groesse

template <class TYPE, int Size> class SimpleArray : public NTupleRW<TYPE>
{
public:
// Constructors
	SimpleArray() {}
	SimpleArray(TYPE x) {for (int i=0;i<Size;i++) m_Data[i]=x;}
// Accessors
	int GetSize() const {return Size;}
	TYPE operator[](int i) const {return m_Data[i];}
	TYPE& operator[](int i) {return m_Data[i];}
// Implementation
private:
	TYPE m_Data[Size];
};


/////////////////////////////////////////////////////////////////////
// NTupleCast<TYPE,STYPE>
// Erzeugt aus NTuple<STYPE> ein NTuple<TYPE>
template <class TYPE, class STYPE>
class NTupleCast : public NTuple<TYPE>
{
public:
	NTupleCast(NTuple<STYPE>& tuple) : m_NTuple(tuple) {}
	int GetSize() const {return m_NTuple.GetSize();}
	TYPE operator[](int i) const {return m_NTuple[i];}
// Implementation
private:
	STYPE m_NTuple;
};


#endif /* _ITERATOR_H */
