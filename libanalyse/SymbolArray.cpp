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

#include "SymbolArray.h"

#ifndef _LFSR_H
#include "LFSR.h"
#endif
#ifndef _SBOX_H
#include "SBox.h"
#endif
#ifndef _PERMUTATION_H
#include "Permutation.h"
#endif
#ifndef _SUBARRAY_H
#include "SubArray.h"
#endif
#ifndef _ITERATOR2_H
#include "Iterator2.h"
#endif

// Constructors

SymbolArray::SymbolArray(int size /*=0*/, const Converter& cnv /*=DefaultConv*/) : baseclass(size) 
{
	Init(cnv);
}

SymbolArray::SymbolArray(const Converter& cnv,int size /*=0*/) : baseclass(size) 
{
	Init(cnv);
}

SymbolArray::SymbolArray(const SymbolArray& src) : baseclass(src)
{ 
	m_Modulus=src.m_Modulus;
	m_Converter=src.m_Converter->Clone();
}

// special constructors
SymbolArray::SymbolArray(const char *s, const Converter& cnv /*=DefaultConv*/) : baseclass()
{
	Init(cnv);
	ReadString(s);
}

SymbolArray::SymbolArray(const LFSR& lfsr, int len /*=10000*/)
{
	LFSR lsr(lfsr); // HACK only needed due to 'const LFSR'

	Init(lsr.GetModulus());
	SetSize(len);
	for (int i=0; i<len; i++)
		(*this)[i]=lsr.next();
}

SymbolArray::SymbolArray(const NTuple<symbol> &Vec, const Converter& cnv /*=DefaultConv*/)
{
	Init(cnv);
	*this=Vec;
}


// tuple/triple constructors
SymbolArray::SymbolArray(Converter& cnv1, Converter& cnv2) : baseclass()
{
	TupleConverter* cnv=new TupleConverter(cnv1,cnv2); 
	Init(cnv);
}
SymbolArray::SymbolArray(Converter& cnv1, Converter& cnv2, Converter& cnv3) : baseclass()
{
	TripleConverter* cnv=new TripleConverter(cnv1,cnv2,cnv3); 
	Init(cnv);
}

SymbolArray::SymbolArray(SymbolArray& s1, SymbolArray& s2) : baseclass()
{
	TupleConverter* cnv=new TupleConverter(*s1.GetConverter(),*s2.GetConverter()); 
	Init(cnv);
	int l=min(s1.GetSize(),s2.GetSize());
	SetSize(l);
	for (int i=0;i<l;i++) 
		(*this)[i]=cnv->Combine(s1[i],s2[i]);
}
SymbolArray::SymbolArray(SymbolArray& s1, SymbolArray& s2, SymbolArray& s3) : baseclass()
{
	TripleConverter* cnv=new TripleConverter(*s1.GetConverter(),*s2.GetConverter(),*s3.GetConverter()); 
	Init(cnv);
	int l=min(s1.GetSize(),min(s2.GetSize(),s3.GetSize()));
	SetSize(l);
	for (int i=0;i<l;i++) 
		(*this)[i]=cnv->Combine(s1[i],s2[i],s3[i]);
}

// special "constructors"
SymbolArray::SymbolArray(const SymbolArray& s,c_BitStream* t)
{
	Init(BinConv);
	int l=s.GetSize();
	int m=ilog2(s.GetModulus());
	SetSize(l*m);
	for (int i=0;i<l;i++) 
		for (int j=0;j<m;j++)
			(*this)[i*m+j]=(s[i] & (1<<(m-j-1)))?1:0;
}
SymbolArray::SymbolArray(const SymbolArray& s,c_ByteStream* t, int n)
{
	Init(NumConverter(1<<n));
	int l=s.GetSize();
	int m=ilog2(s.GetModulus());
	SetSize(l*m/n);
	unsigned long x=0;
	int q=n-1;
	int p=0;
	for (int i=0;i<l;i++) {
		for (int j=0;j<m;j++) {
			x|= ((s[i] & (1<<(m-j-1)))?1:0)<<q;
			if (q--==0) {
				(*this)[p++]=x;
				q=n-1; x=0;
			}
		}
	}
}


SymbolArray::SymbolArray(const SymbolArray& s, int part, c_GetPart* t)
{
	Init(s.GetConverter()->GetConverterPart(part));
	int l=s.GetSize();
	SetSize(l);
	for (int i=0;i<l;i++) 
		(*this)[i]=s.GetConverter()->GetPart(s[i],part);
}

SymbolArray::SymbolArray(const SymbolArray& s, int k, int mod, int k2, int k3, c_Extract* t)
{
	Init(*(s.GetConverter()));
	int l=s.GetSize();
	Allocate(l/mod*(1+(k2>=0?1:0)+(k3>=0?1:0)) +1);

	for (int i=0;i<l;i++) { 
		if ((i%mod)==k) Add(s[i]);
		if ((i%mod)==k2) Add(s[i]);
		if ((i%mod)==k3) Add(s[i]);
	}
}

//
void SymbolArray::Put(const NTuple<symbol>& Vec, int k, int mod /*=2*/, int k2 /*=-1*/, int k3 /*=-1*/)
{
	int l=Vec.GetSize(); 
	if (l==0) return;
	int i=0;
	while (1) { 
		SetGrow(k,Vec[i++]);
		k+=mod;
		if (i>=l) break;
		if (k2>=0) {
			SetGrow(k2,Vec[i++]);
			k2+=mod;
			if (i>=l) break;
		}
		if (k3>=0) {
			SetGrow(k3,Vec[i++]);
			k3+=mod;
			if (i>=l) break;
		}
	} /* while */
}
//Merge(a,b): a.PutInsert(b,1,2)
void SymbolArray::PutInsert(const NTuple<symbol>& Vec, int k, int mod /*=2*/, int k2 /*=-1*/, int k3 /*=-1*/)
// Wichtig: es muss gelten: k<k2<k3 (fuer k2,k3>=0)
{
	int l=Vec.GetSize(); 
	if (l==0) return;
	int i=0;
	Allocate(GetSize()+l);
	while (1) { 
		Insert(k,Vec[i++]);
		k+=mod;
		if (i>=l) break;
		if (k2>=0) {
			Insert(k2,Vec[i++]);
			k2+=mod;
			if (i>=l) break;
		}
		if (k3>=0) {
			Insert(k3,Vec[i++]);
			k3+=mod;
			if (i>=l) break;
		}
	} /* while */
}

void SymbolArray::Rotate(int step, int mode /*=0*/)
// step>0: am Anfang einfuegen, d.h. nach rechts schieben
// mode: 0=rotieren, 1= verschieben und mit 0 auffuellen, 2=einfuegen
{
	if (step>0) { // am Anfang einfuegen, d.h. nach rechts schieben
		step=step%GetSize();
		if (step==0) return;
		switch(mode) {
		case 0: //rotieren
			{
				for (int i=0;i<step;i++) {
					symbol tmp=Get(GetSize()-1);
					Remove(GetSize()-1,1);
					Insert(0,tmp);
				}
				break;
			}
		case 1: // verschieben und mit 0 auffuellen
			Remove(GetSize()-step,step);
			Insert(0,0,step);
			break;
		case 2: // einfuegen
			Insert(0,0,step);
			break;
		} // switch
	} else { // am Ende einfuegen, d.h. nach links schieben
		step=(-step)%GetSize();
		if (step==0) return;
		switch(mode) {
		case 0: //rotieren
			{
				for (int i=0;i<step;i++) {
					symbol tmp=Get(0);
					Remove(0,1);
					Insert(GetSize(),tmp);
				}
				break;
			}
		case 1: // verschieben und mit 0 auffuellen
			Remove(0,step);
			Insert(GetSize(),0,step);
			break;
		case 2: // einfuegen
			Insert(GetSize(),0,step);
			break;
		} // switch
	} // if
}
// special operator=
const SymbolArray& SymbolArray::operator=(const SymbolArray& src)
{
	if (this != &src) {
		baseclass::operator=(src);
		m_Modulus=src.m_Modulus;
		delete m_Converter;
		m_Converter=src.m_Converter->Clone();
	}
	return *this;
}
const SymbolArray& SymbolArray::operator=(const NTuple<symbol>& src)
{
	if (this != &src) {
		Copy(src);
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////
void SymbolArray::Load(istream& stream)
{
	LoadObject(m_Modulus,stream);
	baseclass::Load(stream);
}

void SymbolArray::Save(ostream& stream) const
{
	SaveObject(m_Modulus,stream);
	baseclass::Save(stream);
}

void SymbolArray::Show(OStream& out /*=DefaultOStream*/) const
{
	if (out[OStream::Title]) 
		out << "SymbolArray (Modulus=" << m_Modulus << ")" << endl;
	if (m_Converter) {
		Write(out);
	} else {
		baseclass::Show(out);
	}
}


/////////////////////////////////////////////////////////////////////

// I/O Operations
int SymbolArray::Read(istream& in, int maxcount /*=-1*/)
{
	ASSERT(m_Converter);
	return m_Converter->ReadSymbolArray(*this,in,maxcount);
}
int SymbolArray::Read(const char* filename, int maxcount /*=-1*/)
{
	ifstream ifile(filename,ios::binary|ios::in);
	return Read(ifile,maxcount);
}

int SymbolArray::ReadString(const char* text, int maxcount /*=-1*/)
{
	ASSERT(m_Converter);
	return m_Converter->ReadSymbolArray(*this,text,maxcount);
}

int SymbolArray::Write(ostream& out, int maxcount /*=-1*/) const
{
	ASSERT(m_Converter);
	return m_Converter->WriteSymbolArray(*this,out,maxcount);
}
int SymbolArray::Write(const char* filename, int maxcount /*=-1*/)
{
    ofstream ofile(filename,ios::binary);
	return Write(ofile,maxcount);
}


/////////////////////////////////////////////////////////////////////

SymbolArray& SymbolArray::operator+=(const NTuple<symbol>& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++)
		Set(i,mod(Get(i)+x[i%x.GetSize()],m_Modulus));
	return *this;
}
SymbolArray& SymbolArray::operator-=(const NTuple<symbol>& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++)
		Set(i,mod(Get(i)-x[i%x.GetSize()],m_Modulus));
	return *this;
}
SymbolArray& SymbolArray::operator*=(const NTuple<symbol>& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++)
		Set(i,mod(Get(i)*x[i%x.GetSize()],m_Modulus));
	return *this;
}
SymbolArray& SymbolArray::operator^=(const NTuple<symbol>& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++)
		Set(i,mod(Get(i)^x[i%x.GetSize()],m_Modulus));
	return *this;
}
SymbolArray& SymbolArray::operator|=(const NTuple<symbol>& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++)
		Set(i,mod(Get(i)|x[i%x.GetSize()],m_Modulus));
	return *this;
}
SymbolArray& SymbolArray::operator&=(const NTuple<symbol>& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++)
		Set(i,mod(Get(i)&x[i%x.GetSize()],m_Modulus));
	return *this;
}

///////////////////////////////////////
SymbolArray& SymbolArray::operator+=(Iterator<symbol>& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++) {
		if (x.eof()) {
			if (!x.Init()) { // x seems to be empty
				SetSize(i); 
				break;
			}
		}
		Set(i,mod(Get(i)+x.next(),m_Modulus));
	}
	return *this;
}
SymbolArray& SymbolArray::operator-=(Iterator<symbol>& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++) {
		if (x.eof()) {
			if (!x.Init()) { // x seems to be empty
				SetSize(i); 
				break;
			}
		}
		Set(i,mod(Get(i)-x.next(),m_Modulus));
	}
	return *this;
}
SymbolArray& SymbolArray::operator*=(Iterator<symbol>& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++) {
		if (x.eof()) {
			if (!x.Init()) { // x seems to be empty
				SetSize(i); 
				break;
			}
		}
		Set(i,mod(Get(i)*x.next(),m_Modulus));
	}
	return *this;
}
SymbolArray& SymbolArray::operator^=(Iterator<symbol>& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++) {
		if (x.eof()) {
			if (!x.Init()) { // x seems to be empty
				SetSize(i); 
				break;
			}
		}
		Set(i,mod(Get(i)^x.next(),m_Modulus));
	}
	return *this;
}
SymbolArray& SymbolArray::operator&=(Iterator<symbol>& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++) {
		if (x.eof()) {
			if (!x.Init()) { // x seems to be empty
				SetSize(i); 
				break;
			}
		}
		Set(i,mod(Get(i)&x.next(),m_Modulus));
	}
	return *this;
}
SymbolArray& SymbolArray::operator|=(Iterator<symbol>& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++) {
		if (x.eof()) {
			if (!x.Init()) { // x seems to be empty
				SetSize(i); 
				break;
			}
		}
		Set(i,mod(Get(i)|x.next(),m_Modulus));
	}
	return *this;
}

///////////////////////////////////////
SymbolArray& SymbolArray::operator+=(const symbol& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++)
		Set(i,mod(Get(i)+x,m_Modulus));
	return *this;
}
SymbolArray& SymbolArray::operator-=(const symbol& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++)
		Set(i,mod(Get(i)-x,m_Modulus));
	return *this;
}
SymbolArray& SymbolArray::operator*=(const symbol& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++)
		Set(i,mod(Get(i)*x,m_Modulus));
	return *this;
}
SymbolArray& SymbolArray::operator^=(const symbol& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++)
		Set(i,mod(Get(i)^x,m_Modulus));
	return *this;
}
SymbolArray& SymbolArray::operator|=(const symbol& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++)
		Set(i,mod(Get(i)|x,m_Modulus));
	return *this;
}
SymbolArray& SymbolArray::operator&=(const symbol& x)
{
	int l=GetSize();
	for (int i=0;i<l;i++)
		Set(i,mod(Get(i)&x,m_Modulus));
	return *this;
}

/////////////////////////////////////////////////////////////////////
void SymbolArray::Apply(Cipher& cipher, CryptMode mode /*=Encrypt*/)
{
	int len=GetSize();
	int plen=cipher.GetSize();
	int pos=0;


	if (plen<=1) {
		for (int i=0;i<len;i++)
			(*this)[i]=cipher((*this)[i],mode);
		return;
	}

	SubArray<symbol> v(*this,0,min(len,plen));
	while (len >= plen) {
		//SubArray<symbol> v(*this,pos,plen);
		v.SetStart(pos);
		cipher(v,mode);
		pos+= plen;
		len-= plen;
	}
	if (len) { // last block handling
		//SubArray<symbol> v(*this,pos,len);
		v.SetSize(len);
		v.SetStart(pos);
		cipher(v,mode);
	}
}

void SymbolArray::Homophone(SymbolArray key, bool decrypt,int value)
{
	if(true==decrypt)
	{
		for(int i=0;i<GetSize();i++)
		{
			Set(i,value);
		}
	}
	else
	{
		// Entschlüsselung
	}
}
