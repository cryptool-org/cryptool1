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

#ifndef _SORTEDARRAY_H
#define _SORTEDARRAY_H 1

#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _SORTPAIR_H
#include "SortPair.h"
#endif
#ifndef _ARRAY_H
#include "Array.h"
#endif

/////////////////////////////////////////////////////////////////////
// SortedArray

template<class TYPE>
class SortedArray : public NTuple<int>
{
public:
// Implementation
	SortedArray(const NTuple<TYPE>& Vec, int sorted=1);
// Accessors
	int GetSize() const {return m_Array.GetSize();}
	int operator[](int i) const {return m_Array[i].index;}
	int GetIndex(int i) const {return m_Array[i].index;}
	TYPE GetValue(int i) const {return m_Array[i].data;}
// Implementation
private:
	Array< SortPair<TYPE>, const SortPair<TYPE>& > m_Array;
};

template<class TYPE>
SortedArray<TYPE>::SortedArray(const NTuple<TYPE>& Vec, int sorted /*=1*/)
{
	int l=Vec.GetSize();
	m_Array.SetSize(l);
	for (int i=0; i<l; i++) {
		SortPair<TYPE> pair;
		pair.data=Vec[i];
		pair.index=i;
		m_Array[i]=pair;
	}
	if (sorted) m_Array.Sort(sorted-1);
};


#endif /* _SORTEDARRAY_H */
