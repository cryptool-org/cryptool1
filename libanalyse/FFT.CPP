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

#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _ITERATOR_H
#include "Iterator.h"
#endif

#include "mymath.h"

inline int bitrev(int u, int v)
{
	int u1=0;
	for (int j=0;j<v;j++) {
		int u2=u/2;
		u1=u+2*(u1-u2);
		u=u2;
	}
	return u1;
}

void FFT(NTupleRW<double>& X, NTupleRW<double>& Y, int N, int k)
{
	const double pi2=2*3.14159265358979323846;
	//const double pi2=4*asin(1);

	int k1=k-1,k2=N/2,k3=0;
	for (int n=0;n<k;n++) {
		do {
			for (int m=0; m<k2; m++) {
				int f=bitrev(k3/k2,k);
				double c=cos(pi2*f/N);
				double s=sin(pi2*f/N);
				int k23=k2+k3;
				double XR=X[k23]*c+Y[k23]*s;
				double XI=Y[k23]*c-X[k23]*s;
				X[k23]=X[k3]-XR;Y[k23]=Y[k3]-XI;
				X[k3]=X[k3]+XR;Y[k3]=Y[k3]+XI;
				k3++;
			} // m
			k3+=k2;
		} while (k3<N);
		k3=0;
		k1--;
		k2=k2/2;
	} // n

	for (int i=0;i<N;i++) {
		int f=bitrev(i,k);
		if (f>i) {
			double XT=X[i],YT=Y[i];
			X[i]=X[f];Y[i]=Y[f];
			X[f]=XT;Y[f]=YT;
		}
	} // i
}
