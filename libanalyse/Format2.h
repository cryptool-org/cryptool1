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

/////////////////////////////////////////////////////////////////////
// Format

#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _ARRAY_H
#include "Array.h"
#endif

#include "la_string.h"
extern String NULLSTRING;


/////////////////////////////////////////////////////////////////////
// Manipulator, Manip, CManip & CManip2 templates

template <class BASE> class Manipulator 
{
public:
	virtual void manip(BASE& b) const=0;
	virtual ~Manipulator() {}
};

template <class BASE, class TYPE>
class Manip : public Manipulator<BASE>
{
public:
	Manip(BASE& (*f)(BASE&,TYPE), TYPE t) : m_f(f), m_t(t) {}
	void manip(BASE& b) const {(*m_f)(b,m_t);}
private:
	BASE& (* m_f)(BASE&,TYPE);
	TYPE m_t;
};

/////////////////////////////////////////////////////////////////////

template <class BASE, class TYPE>
class CManip : public Manipulator<BASE>
{
public:
	CManip(void (BASE::*f)(TYPE), TYPE t) : m_f(f), m_t(t) {}
	void manip(BASE& b) const {(b.*m_f)(m_t);}
private:
	void (BASE::*m_f)(TYPE);
	TYPE m_t;
};

/////////////////////////////////////////////////////////////////////

template <class BASE, class TYPE, class TYPE2>
class CManip2 : public Manipulator<BASE>
{
public:
	CManip2(void (BASE::*f)(TYPE, TYPE2), TYPE t, TYPE2 t2) : m_f(f), m_t(t), m_t2(t2) {}
	void manip(BASE& b) const {(b.*m_f)(m_t,m_t2);}
private:
	void (BASE::*m_f)(TYPE, TYPE2);
	TYPE m_t;
	TYPE2 m_t2;
};


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// Format

class Format
{
public:
	class Index;	// class definitions at end of class
	class SIndex;
	friend class Format::Index;
	friend class Format::SIndex;
	
	Format() {}
	virtual ~Format() {}
	virtual long Get(Index i) const {return 0;}
	virtual const String& Get(SIndex i) const {return NULLSTRING;}
#ifdef GCC_WORKAROUND
protected:
	virtual void Set(int i, long l) {}
	virtual void Set(int i, const String& s) {}
public:
#endif /* GCC_WORKAROUND */
	virtual void Set(Index i, long l) {Set(i.m_index,l);}
	virtual void Set(SIndex i, const String& s) {Set(i.m_index,s);}
	virtual long operator()(Index i) const {return Get(i);}
	virtual const String& operator()(SIndex i) const {return Get(i);}
// Implementation
private:
/////////////////////////////////////////////////////////////////////
// Format: Static Part
public:
	static Index NewIndex() {return Index(currentindex++);}
	static SIndex NewString() {return SIndex(currentstringindex++);}
	static int GetOffset() {currentoffset+=1024; return currentoffset;}
private:
	static int currentindex;
	static int currentstringindex;
	static int currentoffset;
public:
	//

/////////////////////////////////////////////////////////////////////
// Format: nested classes
	
	class SIndex
	{
		friend class Format;
	public:
		SIndex(int i) : m_index(i) {}
#ifdef GCC_WORKAROUND
		CManip2<Format,int,const String&> operator()(const String& s) const {return CManip2<Format,int,const String&>(&Format::Set,m_index,s);}
#else
		CManip2<Format,SIndex,const String&> operator()(const String& s) const {return CManip2<Format,SIndex,const String&>(Format::Set,*this,s);}
#endif
	public:
		int m_index;
	};

	class Index
	{
		friend class Format;
	public:
		Index(int i) : m_index(i) {}
#ifdef GCC_WORKAROUND
		CManip2<Format,int,long> operator()(long i=1) const {return CManip2<Format,int,long>(&Format::Set,m_index,i);}
#else
		CManip2<Format,Index,long> operator()(long i=1) const {return CManip2<Format,Index,long>(Format::Set,*this,i);}
#endif
	public:
		int m_index;
	};

};

inline Format& operator<<(Format& x, const Manipulator<Format>& m) { m.manip(x); return x; }

/////////////////////////////////////////////////////////////////////
// NFormat<NAME,BASE, offset>

template <class NAME, class BASE, int offset>
class NFormat : public BASE
{
	typedef BASE baseclass;
public:
	NFormat();
	long Get(Format::Index i) const;
	const String& Get(Format::SIndex i) const;
#ifdef GCC_WORKAROUND
protected:
	void Set(int i, long l);
	void Set(int i, const String& s);
#endif /* GCC_WORKAROUND */

private:
	Array<long,long> m_data;
	Array<String,const String&> m_sdata;
	
/////////////////////////////////////////////////////////////////////
// NFormat<NAME;BASE,offset>: Static Part
public:
	static Format::Index NewIndex() {return Index(currentindex++);}
	static Format::SIndex NewString() {return SIndex(currentstringindex++);}
private:
	static int currentindex;
	static int currentstringindex;
};


/////////////////////////////////////////////////////////////////////
// NFormat<NAME,BASE, offset> (inline) functions

template <class NAME, class BASE, int offset>
inline NFormat<NAME,BASE,offset>::NFormat() : m_data(currentindex-offset), m_sdata(currentstringindex-offset) 
{}

template <class NAME, class BASE, int offset>
void NFormat<NAME,BASE,offset>::Set(int i, long l) 
{
	int j=i-offset;
	if (j<0) {baseclass::Set(i,l);return;}
	ASSERT(j<=currentindex);
	m_data.SetGrow(j,l);
}
template <class NAME, class BASE, int offset>
void NFormat<NAME,BASE,offset>::Set(int i, const String& s)
{
	int j=i-offset;
	if (j<0) {baseclass::Set(i,s);return;}
	ASSERT(j<=currentstringindex);
	m_sdata.SetGrow(j,s);
}

template <class NAME, class BASE, int offset>
long NFormat<NAME,BASE,offset>::Get(Format::Index i) const
{
	int j=i.m_index-offset;
	if (j<0) return baseclass::Get(i);
	ASSERT(j<=currentindex);
	if (j<m_data.GetSize()) return m_data[j];
	return 0;
}
template <class NAME, class BASE, int offset>
const String& NFormat<NAME,BASE,offset>::Get(Format::SIndex i) const
{
	int j=i.m_index-offset;
	if (j<0) return baseclass::Get(i);
	ASSERT(j<=currentstringindex);
	static String r;
	if (j<m_sdata.GetSize()) {
		r=m_sdata[j];
		return r;
	}
	return NULLSTRING;
}


#ifndef NOSTATICTAMPLES
template <class NAME, class BASE, int offset>
int NFormat<NAME,BASE,offset>::currentindex=offset;
template <class NAME, class BASE, int offset>
int NFormat<NAME,BASE,offset>::currentstringindex=offset;
#endif