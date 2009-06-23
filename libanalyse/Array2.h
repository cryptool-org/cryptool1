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

#ifndef _ARRAY2_H
#define _ARRAY2_H 1

// Array2.h enthaelt die "nicht-inline" Template-Funktionen
// zu Array<TYPE, ARGTYPE> aus Array.h
// Muss daher nur eingebunden werden, wenn eine entsprechendes
// Array<TYPE, ARGTYPE> instantiiert werden soll.

#ifndef _ARRAY_H
#include "Array.h"
#endif

#include "mymath.h"		// templates for min and max

/////////////////////////////////////////////////////////////////////////////
// Array<TYPE, ARGTYPE> out-of-line functions
// muss nur eingebunden werden, um einen neuen Typ zu instantiieren

template<class TYPE, class ARGTYPE>
inline void Array<TYPE, ARGTYPE>::Init()
{
	m_Array=NULL; m_Size=m_AllocSize=0; 
}

template<class TYPE, class ARGTYPE>
Array<TYPE, ARGTYPE>::Array(int Size /*=0*/)
{
	Init();	if (Size) SetSize(Size);
}
template<class TYPE, class ARGTYPE>
Array<TYPE, ARGTYPE>::Array(int Size, TYPE data[])
{
	Init();	SetSize(Size);
	for (int i=0;i<Size;i++) Set(i,data[i]);
}

template<class TYPE, class ARGTYPE>
Array<TYPE, ARGTYPE>::Array(const Array& src)
{
	Init();	Copy(src);
}

template<class TYPE, class ARGTYPE>
const Array<TYPE, ARGTYPE>& Array<TYPE, ARGTYPE>::operator=(const Array& src)
{
	if (this != &src) Copy(src);
	return *this;
}
template<class TYPE, class ARGTYPE>
Array<TYPE, ARGTYPE>::Array(const NTuple<TYPE>& src)
{
	Init();	Copy(src);
}

template<class TYPE, class ARGTYPE>
const Array<TYPE, ARGTYPE>& Array<TYPE, ARGTYPE>::operator=(const NTuple<TYPE>& src)
{
	if (this != &src) Copy(src);
	return *this;
}


template<class TYPE, class ARGTYPE>
Array<TYPE, ARGTYPE>::~Array()
{
	SetSize(0);
}

template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::SetSize(int Size)
{
	ASSERT(Size >= 0);

	if (Size == 0) {	// alles entfernen
		if (m_Array != NULL) {
			DestructObjects(m_Array, m_Size);
			delete[] (BYTE*)m_Array;
			m_Array = NULL;
		}
		m_Size = m_AllocSize = 0;
	} else if (m_Array == NULL)	{ // neu
		m_Array = (TYPE*) new BYTE[Size * sizeof(TYPE)];
		ConstructObjects(m_Array, Size);
		m_Size = m_AllocSize = Size;
	} else if (Size <= m_AllocSize) { // Speicher vorhanden
		if (Size > m_Size) {	
			ConstructObjects(&m_Array[m_Size], Size-m_Size);
		} else if (m_Size > Size) { 
			DestructObjects(&m_Array[Size], m_Size-Size);
		}
		m_Size = Size;
	} else { // neuer Speicher benoetigt
		int NewSize;
		NewSize=max(8,min(m_Size/2,8192));
		NewSize=max(Size,m_AllocSize+NewSize);
		Allocate(NewSize);
		// construct remaining elements
		ASSERT(Size > m_Size);
		ConstructObjects(&m_Array[m_Size], Size-m_Size);
		m_Size = Size;
	}
}
template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Allocate(int Size)
{
	ASSERT(Size >= 0);
	ASSERT(Size>=m_Size);

	if (Size<m_Size) return;
	if (Size==m_AllocSize) return; // nothing to do

	TYPE* temp = (TYPE*) new BYTE[Size * sizeof(TYPE)];
	memcpy(temp, m_Array, m_Size * sizeof(TYPE));
	delete[] (BYTE*)m_Array;
	m_Array = temp;
	m_AllocSize = Size;
}

template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Pack()
{
	Allocate(m_Size);
}
/////////////////////////////////////////////////////////////////////////////

template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Append(const Array& src)
{
	ASSERT(this != &src);
	int OldSize= m_Size;
	SetSize(m_Size+src.m_Size);
	CopyObjects(m_Array+OldSize, src.m_Array, src.m_Size);
}
template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Append(const NTuple<TYPE>& src)
{
	ASSERT(this != &src);
	int OldSize = m_Size;
	int l=src.GetSize();
	SetSize(m_Size+l);

	for (int i=0;i<l;i++) 
		Set(i+OldSize,src[i]);
}

template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Copy(const Array& src)
{
	ASSERT(this != &src);
	SetSize(src.m_Size);
	CopyObjects(m_Array, src.m_Array, src.m_Size);
}
template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Copy(const NTuple<TYPE>& src)
{
	ASSERT(this != &src);
	int l=src.GetSize();
	SetSize(l);

	for (int i=0;i<l;i++) 
		Set(i,src[i]);
}

/////////////////////////////////////////////////////////////////////////////

template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::SetGrow(int Index, ARGTYPE Element)
{
	ASSERT(Index>=0);
	if (Index>=m_Size) SetSize(Index+1);
	m_Array[Index] = Element;
}

template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Insert(int Index, ARGTYPE Element, int Count /*=1*/)
{
	ASSERT(Index>=0 && Count>0);

	if (Index >= m_Size) {
		SetSize(Index + Count);	
	} else {
		int OldSize = m_Size;
		SetSize(m_Size + Count);	
		memmove(&m_Array[Index+Count], &m_Array[Index],(OldSize-Index)*sizeof(TYPE));
		ConstructObjects(&m_Array[Index], Count);
	}

	while (Count--) m_Array[Index++] = Element;
}

template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Insert(int Index,const NTuple<TYPE>& src, int Count /*=-1*/)
{
	ASSERT(&src != NULL);
	ASSERT(Index>=0);

	if (src.GetSize() > 0) {
		if (Count<0) Count=src.GetSize();
		else Count=min(src.GetSize(),Count);
		Insert(Index, src[0], Count);
		for (int i=1; i<Count; i++)
			Set(Index+i, src[i]);
	}
}

template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Remove(int Index, int Count)
{
	ASSERT(Index>=0 && Count>0);
	ASSERT(Index+Count <= m_Size);

	int MoveCount = m_Size-(Index+Count);
	DestructObjects(&m_Array[Index], Count);
	if (MoveCount)
		memcpy(&m_Array[Index], &m_Array[Index+Count],MoveCount*sizeof(TYPE));
	m_Size-=Count;
}

template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Clear()
{
	if (m_Size>0) {
		DestructObjects(m_Array, m_Size);
		ConstructObjects(m_Array, m_Size);
	}
}

/////////////////////////////////////////////////////////////////////////////
template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Load(istream& stream)
{
	int Size=0;
	LoadObject(Size,stream);
	SetSize(Size);
	for (int i=0;i<Size; i++) {
		LoadObject(m_Array[i],stream);
	}
}

template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Save(ostream& stream) const
{
	// Size, Elements...
	SaveObject(m_Size,stream);
	for (int i=0;i<m_Size; i++) {
		SaveObject(m_Array[i],stream);
	}
}


template<class TYPE, class ARGTYPE>
void Array<TYPE, ARGTYPE>::Sort(int descending /*=0*/)
{
	typedef int (*fcmp)(const TYPE*,const TYPE*);
	fcmp cmp;
	if (descending) cmp=RCompareObjects;
	else cmp=CompareObjects;
	qsort((void *)m_Array,m_Size,sizeof(TYPE),(int(*) (const void *,const void *))cmp);
}

/////////////////////////////////////////////////////////////////////////////

#endif /* _ARRAY2_H */
