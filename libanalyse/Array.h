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

#ifndef _ARRAY_H
#define _ARRAY_H 1

#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _ITERATOR_H
#include "Iterator.h"
#endif

#include "Array3.h"

// Note: more template functions in Array2.h
/////////////////////////////////////////////////////////////////////////////
// Array<TYPE, ARGTYPE>

template<class TYPE, class ARGTYPE>
class Array : public NTupleRW<TYPE>
{
	typedef unsigned char BYTE;
public:
// Constructors
	EXPLICIT Array(int Size=0);
	Array(int Size, TYPE data[]);
	~Array();
// Accessors
	TYPE Get(int Index) const;
	void Set(int Index, ARGTYPE Element);
	TYPE operator[](int Index) const;
	TYPE& operator[](int Index);

// Attributes
	int GetSize() const;
	void SetSize(int Size);
	void Allocate(int Size); //use this to initially allocate memory

// Operations
	void SetGrow(int Index, ARGTYPE Element);
	void Add(ARGTYPE Element);
	void Append(const Array& src);
	void Append(const NTuple<TYPE>& src);
	void Copy(const Array& src);
	void Copy(const NTuple<TYPE>& src);

	void Insert(int Index, ARGTYPE Element, int Count=1);
	void Insert(int Index, const NTuple<TYPE>& src, int Count=-1);
	void Remove(int Index, int Count=1);
	void RemoveAll();

	// Sorting
	void Sort(int descending=0);

	// Misc
	void Load(istream& stream); 
	void Save(ostream& stream) const; 

	// Clean up
	void Clear();
	void Pack();

public:
	Array(const Array& src);
	const Array& operator=(const Array& src);
	Array(const NTuple<TYPE>& src);
	const Array& operator=(const NTuple<TYPE>& src);

// Helpers
private:
	void Init();

// Implementation
protected:
	TYPE* m_Array;		
	int m_Size;			
	int m_AllocSize;	
};


typedef Array<unsigned long, unsigned long> ULongArray;
typedef Array<long, long> LongArray;
typedef Array<int, int> IntArray;
typedef Array<double, double> DoubleArray;
//class String;
//typedef Array<String, String&> StringArray;

/////////////////////////////////////////////////////////////////////////////
// Array<TYPE, ARGTYPE> inline functions

template<class TYPE, class ARGTYPE>
inline int Array<TYPE, ARGTYPE>::GetSize() const 
{ return m_Size; }

template<class TYPE, class ARGTYPE>
inline TYPE Array<TYPE, ARGTYPE>::Get(int Index) const
{
	ASSERT(Index >= 0 && Index < m_Size);
	return m_Array[Index];
}

template<class TYPE, class ARGTYPE>
inline void Array<TYPE, ARGTYPE>::Set(int Index, ARGTYPE Element)
{
	ASSERT(Index >= 0 && Index < m_Size);
	m_Array[Index] = Element;
}

template<class TYPE, class ARGTYPE>
inline TYPE Array<TYPE, ARGTYPE>::operator[](int Index) const
{
	ASSERT(Index >= 0 && Index < m_Size);
	return m_Array[Index];
}

template<class TYPE, class ARGTYPE>
inline TYPE& Array<TYPE, ARGTYPE>::operator[](int Index)
{
	ASSERT(Index >= 0 && Index < m_Size);
	return m_Array[Index];
}

template<class TYPE, class ARGTYPE>
inline void Array<TYPE, ARGTYPE>::Add(ARGTYPE Element)
{ 
	SetGrow(m_Size, Element);
}

template<class TYPE, class ARGTYPE>
inline void Array<TYPE, ARGTYPE>::RemoveAll()
{ SetSize(0); }

////////////////////////////////////////////////////////

#ifndef _ARRAY2_H
#include "Array2.h"
#endif

#endif /* _ARRAY_H */



