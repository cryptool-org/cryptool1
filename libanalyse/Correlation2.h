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

#ifndef _CORRELATION2_H
#define _CORRELATION2_H 1

#ifndef _ITERATOR_H
#include "Iterator.h"
#endif

void FFT(NTupleRW<double>& X, NTupleRW<double>& Y, int N, int k);

/////////////////////////////////////////////////////////////////////////////
// Correlation<TYPE> out-of-line functions
// muss nur eingebunden werden, um einen neuen Typ zu instantiieren

/////////////////////////////////////////////////////////////////////
// pricate CalcMittelwertVarianz

template <class TYPE> static void CalcMittelwertVarianz(const NTuple<TYPE>& Vec, double* mittelwert, double* varianz, int len=0)
// Mittelwert und Varianz von Vec
{
	if (!len) len=Vec.GetSize();
	double x=Vec[0],sx=0.0;

	for (int i=1;i<len;i++) {
		sx=sx+sqr(Vec[i]-x)*i/(i+1);
		x=(x*i+Vec[i])/(i+1);
	}
	if (mittelwert) *mittelwert=x;
	if (varianz) *varianz=(len<=1) ? 0.0 : sqrt(sx/(len-1));
}

#include "Correlation.h"

#ifndef _OSTREAM_H
#include "la_ostream.h"
#endif

#include "mymath.h"

#define CHECKMODE(x) (mode&CorMode::x)
#define IFMODE(x) if(mode&CorMode::x)
#define IFNOTMODE(x) if(!(mode&CorMode::x))

template<class TYPE, int mode>
void Correlation<TYPE,mode>::Init(int size)
{
	m_NX=m_X->GetSize();
	m_NY=m_Y->GetSize();

	IFMODE(cyclic) m_size=m_N=min(m_NX,m_NY);
	else m_size=m_N=m_NX+m_NY;
	
	if (size) m_size=size;
	
	m_mu=0.0; 
	m_sigma=1.0;
	//m_sigma=m_N; //-1

	m_Mittelwert=m_Varianz=0.0;
	m_Mittelwert2=m_Varianz2=0.0;
	if ((CHECKMODE(covariance) || CHECKMODE(normalize)) && !CHECKMODE(delta)) {
		CalcMittelwertVarianz(*m_X,&m_Mittelwert,&m_Varianz,m_N);
		if (m_X==m_Y) {
			m_Mittelwert2=m_Mittelwert;
			m_Varianz2=m_Varianz;
		} else {
			CalcMittelwertVarianz(*m_Y,&m_Mittelwert2,&m_Varianz2,m_N);
		}
		
		IFMODE(covariance) m_mu=m_N*m_Mittelwert*m_Mittelwert2;
		if (m_Varianz*m_Varianz2!=0.0) m_sigma*=m_Varianz*m_Varianz2;
		IFNOTMODE(covariance) m_sigma+=m_N*m_Mittelwert*m_Mittelwert2;
	}

	if (CHECKMODE(normalize) && CHECKMODE(delta)) {
		m_mu=m_sigma=(double)m_N/2.0;
	}

	IFMODE(store) {
		m_corr.Allocate(min(1024,m_size));
	}

// FFT
	IFMODE(fft) {
		int N=m_NX+m_NY;
		IFMODE(cyclic) N+=m_NX;
		int k=ilog2(N);
		ASSERT( (1<<k) >=N);
		N=1<<k;

		Array<double,double> /*ZR(N),*/ZI(N);
		Array<double,double>& ZR=m_corr;
		m_corr.SetSize(N);

		for (int j=0;j<m_NX;j++) {
			ZI[N-m_NX+j]=(*m_X)[j];
			IFMODE(cyclic) ZI[j]=(*m_X)[j];
		}
		for (int j2=0;j2<m_NY;j2++) {
			ZR[j2]=(*m_Y)[j2];
		}

		FFT(ZR,ZI,N,k);

		for (int n=0;n<=N/2;n++) {
			int n2=n?(N-n):0;
			double xr=(ZR[n]+ZR[n2])/2.0;
			double xi=(ZI[n]-ZI[n2])/2.0;
			double yr=(ZI[n]+ZI[n2])/2.0;
			double yi=-(ZR[n]-ZR[n2])/2.0;

			double zr=(xr*yr+xi*yi)/N;
			double zi=-(xi*yr-xr*yi)/N;
			ZR[n]=zr;
			ZI[n]=zi;
			ZR[n2]=zr;	// da xi=-xi; yi=-yi;
			ZI[n2]=-zi;
		}

		FFT(ZR,ZI,N,k);
		m_corr.SetSize(m_N);
/*
		IFMODE(cyclic) {
			//m_corr.Remove(0,NX);
			//m_corr.SetSize(NX+NY+NX);
			m_N=m_corr.GetSize()-20;
			m_size=m_N;
		} else
			m_corr.SetSize(m_N);
*/
	} // FFT

}

template<class TYPE, int mode>
Correlation<TYPE,mode>::Correlation(const NTuple<TYPE>& Vec, int size /*=0*/)
{
	m_X=m_Y=&Vec;
	Init(size);
}

template<class TYPE, int mode>
Correlation<TYPE,mode>::Correlation(const NTuple<TYPE>& Vec1, const NTuple<TYPE>& Vec2, int size /*=0*/)
{
	m_X=&Vec1;
	m_Y=&Vec2;
	Init(size);
}

template<class TYPE, int mode>
double Correlation<TYPE,mode>::GetCorrelation(int n /*=0*/) const
{
	n=mod(n,m_N);
	IFMODE(fft) {
		return m_corr[(n+m_NX)%m_N];
	}
	
	const double NOTCALCULATED=1e300;
	double cor=0.0;

	//is this value already computed (and stored)?
	IFMODE(store) {
		if (m_corr.GetSize()>n) {
			cor=m_corr[n];
			if (cor!=NOTCALCULATED) return cor;
		} 
	} // store
	// no, so compute!
	cor=0.0;
	int i=0,l=m_N;
	IFMODE(cyclic) {
		l=max(m_NX,m_NY);
	} else {
		if (n>=m_NY) n-=m_N;
		i=max(0,-n);
		l=min(m_NX,m_NY-n);
	}

	for (;i<l;i++) {
		TYPE x,y;
		IFMODE(cyclic) {
			x=(*m_X)[i%m_NX]; 
			y=(*m_Y)[(i+n)%m_NY];
		} else {
			x=(*m_X)[i];
			y=(*m_Y)[i+n];
		}

		IFMODE(delta) {
			if (x==y) cor++;
		} else {
			cor+=x*y;
		}
	} // for

	if (CHECKMODE(covariance) || CHECKMODE(normalize)) {
		cor=(cor-m_mu)/m_sigma;
	}

	//store this value
	IFMODE(store) {
		Array<double,double>& corrarray=(const_cast<Correlation*>(this))->m_corr; // HACK!
		int l=corrarray.GetSize();
		if (l<=n) {
			corrarray.SetSize(n+1);
			for (int j=l;j<n;j++) corrarray[j]=NOTCALCULATED; // mark as uncalculated
		}
		corrarray[n]=cor;
	} // store
	return cor;
}

template<class TYPE, int mode>
void Correlation<TYPE,mode>::SetSize(int size)
{
	m_size=size;
	IFMODE(store) {
		m_corr.Allocate(m_size);
	}
}

template<class TYPE, int mode>
void Correlation<TYPE,mode>::Show(OStream& out /*=DefaultOStream*/) const
{
	if (out[OStream::Title]) {
		if ((m_X==m_Y))
			out << "Auto-";
		out << "Korrelation" << endl;
	}

	((baseclass*)this)->Show(out,1);
}

#undef CHECKMODE
#undef IFMODE
#undef IFNOTMODE

#endif  /* _CORRELATION2_H */
