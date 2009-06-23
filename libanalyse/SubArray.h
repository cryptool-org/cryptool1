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

#ifndef _SUBARRAY_H
#define _SUBARRAY_H 1

// SubArray.h definiert folgende Klassen:
// **************************************
// SubArrayRO
// SubArray

#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _ITERATOR_H
#include "Iterator.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// SubArrayRO<TYPE>

template<class TYPE>
class SubArrayRO : public NTuple<TYPE>
{
public:
// Constructors
	SubArrayRO(const NTuple<TYPE>& array, int start, int size);
// Accessors
	int GetSize() const;
	TYPE operator[](int Index) const;
// Attributes
	SubArrayRO& SetStart(int start);
	SubArrayRO& SetSize(int size);
// Implementation
protected:
	const NTuple<TYPE>& m_Array;
	int m_Start;			
	int m_Size;	
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// SubArray<TYPE>

template<class TYPE>
class SubArray : public NTupleRW<TYPE>
{
public:
// Constructors
	SubArray(NTupleRW<TYPE>& array, int start, int size);
// Accessors
	int GetSize() const;
	TYPE operator[](int Index) const;
	TYPE& operator[](int Index);
// Attributes
	SubArray& SetStart(int start);
	SubArray& SetSize(int size);
// Implementation
protected:
	NTupleRW<TYPE>& m_Array;
	int m_Start;			
	int m_Size;	
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// SubArrayRO<TYPE> inline functions

template<class TYPE>
inline int SubArrayRO<TYPE>::GetSize() const 
{ return m_Size; }

template<class TYPE>
inline TYPE SubArrayRO<TYPE>::operator[](int Index) const
{
	ASSERT(Index >= 0 && Index < m_Size);
	return m_Array[Index+m_Start];
}


template<class TYPE>
inline SubArrayRO<TYPE>& SubArrayRO<TYPE>::SetStart(int start)
{ m_Start=start; return *this;}

template<class TYPE>
inline SubArrayRO<TYPE>& SubArrayRO<TYPE>::SetSize(int size)
{ m_Size=size; return *this;}

/////////////////////////////////////////////////////////////////////////////
// SubArrayRO<TYPE> out-of-line functions

template<class TYPE>
SubArrayRO<TYPE>::SubArrayRO(const NTuple<TYPE>& array, int start, int size) : m_Array(array), m_Start(start), m_Size(size)
{
	ASSERT(m_Size+m_Start<=m_Array.GetSize());
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// SubArray<TYPE> inline functions

template<class TYPE>
inline int SubArray<TYPE>::GetSize() const 
{ return m_Size; }

template<class TYPE>
inline TYPE SubArray<TYPE>::operator[](int Index) const
{ 
	ASSERT(Index >= 0 && Index < m_Size);
	return m_Array[Index+m_Start];
}

template<class TYPE>
inline TYPE& SubArray<TYPE>::operator[](int Index)
{
	ASSERT(Index >= 0 && Index < m_Size);
	return m_Array[Index+m_Start];
}

template<class TYPE>
inline SubArray<TYPE>& SubArray<TYPE>::SetStart(int start)
{ m_Start=start; return *this;}
template<class TYPE>
inline SubArray<TYPE>& SubArray<TYPE>::SetSize(int size)
{ m_Size=size; return *this;}


/////////////////////////////////////////////////////////////////////////////
// SubArray<TYPE> out-of-line functions

template<class TYPE>
SubArray<TYPE>::SubArray(NTupleRW<TYPE>& array, int start, int size) : m_Array(array), m_Start(start), m_Size(size)
{
	ASSERT(m_Size+m_Start<=m_Array.GetSize());
}

#endif /* _SUBARRAY_H */