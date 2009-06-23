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

#include "Cipher.h"

#ifndef _SUBARRAY_H
#include "SubArray.h"
#endif

///////////////////////////////////////////////////////////////////
//  FeistelCipher

void FeistelCipher::operator()(NTupleRW<symbol>& Vec, int mode /*=Encrypt*/) const
{
	m_Init(Vec);
	if (m_f.GetSize()==1) {
		//SubArray<symbol> R(Vec,1,1);
		for (int i=0;i<m_Rounds;i++) {
			symbol t=Vec[1];
			//m_f(R,mode==Decrypt?m_Rounds-1-i:i);
			Vec[1]=m_f(Vec[1],mode==Decrypt?m_Rounds-1-i:i);
			Vec[1]=Vec[1]^Vec[0];
			Vec[0]=t;
		}
#if !defined(_MSC_VER) || _MSC_VER <= 1200
		swap(Vec[0],Vec[1]);
#else
		std::swap(Vec[0],Vec[1]);
#endif
	} else {
		int len=m_f.GetSize();
		//SubArray L(Vec,0,len); // benutze Vec stattdessen, ist schneller
		NTupleRW<symbol>& L=Vec;
		SubArray<symbol> R(Vec,len,len);
		static Array<symbol,symbol> t(len);
		for (int i=0;i<m_Rounds;i++) {
			//symbol t=Vec[1];
			Copy(t,R,len); //for (int j=0;j<len;j++) t[j]=R[j];
			m_f(R,mode==Decrypt?m_Rounds-1-i:i);
			//Vec[1]=Vec[1]^Vec[0];
			for (int j=0;j<len;j++) R[j]=R[j]^L[j];
			//Vec[0]=t;
			Copy(L,t,len); //for (int j=0;j<len;j++) L[j]=t[j];
		}
#if !defined(_MSC_VER) || _MSC_VER <= 1200
		for (int j=0;j<len;j++) swap(Vec[j],Vec[j+len]);
#else
		for (int j=0;j<len;j++) std::swap(Vec[j],Vec[j+len]);
#endif
	}
	m_End(Vec);
}


///////////////////////////////////////////////////////////////////
//  CBC

CBC::CBC(Cipher& f, NTuple<symbol>& IV) : m_f(f), m_lastblock(f.GetSize()) 
{
	Copy(m_lastblock,IV,m_f.GetSize());
}

void CBC::SetIV(NTuple<symbol>& IV)
{
	Copy(m_lastblock,IV,m_f.GetSize());
}

void CBC::operator()(NTupleRW<symbol>& Vec, int mode /*=Encrypt*/)
{
	int len=m_f.GetSize();

	if (mode==Encrypt) {
		//Vec=Vec^m_lastblock;
		for (int j=0;j<len;j++) Vec[j]=Vec[j]^m_lastblock[j];

		m_f(Vec,Cipher::Encrypt);
		Copy(m_lastblock,Vec,len);
	} else { // Decrypt
		static Array<symbol,symbol> tmp(len);
		Copy(tmp,Vec,len);
		m_f(Vec,Cipher::Decrypt);
		//Vec=Vec^m_lastblock;
		for (int j=0;j<len;j++) Vec[j]=Vec[j]^m_lastblock[j];
		Copy(m_lastblock,tmp,len);
	}
}
		
		
		
