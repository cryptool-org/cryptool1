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

#include "Des.h"

// DES' Data - die eigentlichen Tabllen sind am Ende der Datei
extern unsigned long s_table[8][64];
extern long ip_table[],p_table[],e_table[];
extern long pc1_table[],pc20_table[],pc21_table[];
extern short shift_table[];

PermTable DESData::m_IPperm(64,ip_table);
PermTable DESData::m_IPperminv(64,ip_table);
PermTable DESData::m_Pperm(32,p_table);
PermTable DESData::m_Eperm(48+8,e_table);

SBoxPerm2 DESData::IP(m_IPperm);
SBoxPerm2 DESData::IPinv(m_IPperminv);
SBoxPerm2 DESData::P(m_Pperm);
SBoxPerm2 DESData::E(m_Eperm);
int DESData::m_count=0;

DESData::DESData()
{
	if (!m_count++) {
		//IPinv
		IPinv.invert();

		// SBoxen initialisieren
		for (int s=0; s<8; s++)
			m_S[s]=new SBoxTable(64,16,s_table[s]);
	} /* if */
}

DESData::~DESData()
{
	if (!--m_count) {
		for (int s=0;s<8; s++)
			delete m_S[s];
	}
}

DESData desdata;

/////////////////////////////////////////////////////////////////////
// DES

DES::DES(unsigned long k1, unsigned long k2) : m_desf(k1,k2), FeistelCipher(m_desf,16,desdata.IPinv,desdata.IP)
{}

/////////////////////////////////////////////////////////////////////
// DESF: DES' function

// Constructor: Key Generation
DESF::DESF(unsigned long k1, unsigned long k2)
{
	// Teilschluessel m_Key[round][0/1] berechnen
	SimpleArray<unsigned long,2> K; // Ci, Di - jeweils 28 bit
	K[0]=k1; K[1]=k2;

	PermTable pc1perm(60,pc1_table);SBoxPerm2 PC1(pc1perm);
	PermTable pc20perm(24,pc20_table);SBoxPerm2 PC20(pc20perm);
	PermTable pc21perm(24,pc21_table);SBoxPerm2 PC21(pc21perm);

	PC1(K,Cipher::Decrypt);
	K[0]&=0xFFFFFFF0;
	K[1]&=0xFFFFFFF0;

	for (int r=0;r<16;r++) {
		int j=shift_table[r];
		K[0] = ((K[0] << j) | (K[0] >> (28-j))) & 0xFFFFFFF0;
		K[1] = ((K[1] << j) | (K[1] >> (28-j))) & 0xFFFFFFF0;

		m_Key[r][0]=PC20(K[0],Cipher::Decrypt);
		m_Key[r][1]=PC21(K[1],Cipher::Decrypt);
	} /* for(rounds)*/
}
   

// DES' f function
Cipher::domain DESF::operator()(codomain x, int round) const
{
	SimpleArray<unsigned long,2> ex;	// 24 bit
	ex[0]=x;

	desdata.E(ex,Cipher::Decrypt); // Expansion ex[0]-> ex[0/1]

	ex[0]^=m_Key[round][0];
	ex[1]^=m_Key[round][1];

	unsigned long tmp=0;
	for (int i=0;i<8;i++) {
		int a=(ex[(i<4)?0:1]>>(26-(i&3)*6) )&63;
		tmp <<= 4;
		tmp |=  (long) desdata.S(i)(a);
    }

	return desdata.P(tmp,Cipher::Decrypt);
}

/////////////////////////////////////////////////////////////////////
// DES' Data

long ip_table[]=
	{57,49,41,33,25,17, 9, 1, 59,51,43,35,27,19,11, 3,
	 61,53,45,37,29,21,13, 5, 63,55,47,39,31,23,15, 7,
	 56,48,40,32,24,16, 8, 0, 58,50,42,34,26,18,10, 2,
	 60,52,44,36,28,20,12, 4, 62,54,46,38,30,22,14, 6};

long p_table[]=
	{15, 6,19,20,28,11,27,16, 0,14,22,25, 4,17,30, 9,
	  1, 7,23,13,31,26, 2, 8,18,12,29, 5,21,10, 3,24};

long e_table[] =
	{31, 0, 1, 2, 3, 4,  3, 4, 5, 6, 7, 8,
	  7, 8, 9,10,11,12, 11,12,13,14,15,16,
	  0,0,0,0,0,0,0,0, // word gap
	 15,16,17,18,19,20, 19,20,21,22,23,24,
	 23,24,25,26,27,28, 27,28,29,30,31, 0};

long pc1_table[60]=
	{56,48,40,32,24,16, 8,  0,57,49,41,33,25,17,
	  9, 1,58,50,42,34,26, 18,10, 2,59,51,43,35,
	  0,0,0,0, // word gap
	 62,54,46,38,30,22,14,  6,61,53,45,37,29,21,
	 13, 5,60,52,44,36,28, 20,12, 4,27,19,11, 3};
long pc20_table[]= // erste Haelfte von PC20
	{13,16,10,23, 0, 4,  2,27,14, 5,20, 9,
	 22,18,11, 3,25, 7, 15, 6,26,19,12, 1};
long pc21_table[]= // zweite Haelfte von PC20 (-28)
	{12,23, 2, 8,18,26,  1,11,22,16, 4,19,
	 15,20,10,27, 5,24, 17,13,21, 7, 0, 3};

short shift_table[]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

// DES' SBoxen (umgeordnet, so dass sie per Index 0..63 
// angesprochen werden koennen)
unsigned long s_table[8][64]=
{{  14, 0, 4,15,13, 7, 1, 4, 2,14,15, 2,11,13, 8, 1,
	 3,10,10, 6, 6,12,12,11, 5, 9, 9, 5, 0, 3, 7, 8,
	 4,15, 1,12,14, 8, 8, 2,13, 4, 6, 9, 2, 1,11, 7,
	15, 5,12,11, 9, 3, 7,14, 3,10,10, 0, 5, 6, 0,13,},
 {	15, 3, 1,13, 8, 4,14, 7, 6,15,11, 2, 3, 8, 4,14,
	 9,12, 7, 0, 2, 1,13,10,12, 6, 0, 9, 5,11,10, 5,
	 0,13,14, 8, 7,10,11, 1,10, 3, 4,15,13, 4, 1, 2,
	 5,11, 8, 6,12, 7, 6,12, 9, 0, 3, 5, 2,14,15, 9,},
 {	10,13, 0, 7, 9, 0,14, 9, 6, 3, 3, 4,15, 6, 5,10,
	 1, 2,13, 8,12, 5, 7,14,11,12, 4,11, 2,15, 8, 1,
	13, 1, 6,10, 4,13, 9, 0, 8, 6,15, 9, 3, 8, 0, 7,
	11, 4, 1,15, 2,14,12, 3, 5,11,10, 5,14, 2, 7,12,},
 {	 7,13,13, 8,14,11, 3, 5, 0, 6, 6,15, 9, 0,10, 3,
	 1, 4, 2, 7, 8, 2, 5,12,11, 1,12,10, 4,14,15, 9,
	10, 3, 6,15, 9, 0, 0, 6,12,10,11, 1, 7,13,13, 8,
	15, 9, 1, 4, 3, 5,14,11, 5,12, 2, 7, 8, 2, 4,14,},
 {	 2,14,12,11, 4, 2, 1,12, 7, 4,10, 7,11,13, 6, 1,
	 8, 5, 5, 0, 3,15,15,10,13, 3, 0, 9,14, 8, 9, 6,
	 4,11, 2, 8, 1,12,11, 7,10, 1,13,14, 7, 2, 8,13,
	15, 6, 9,15,12, 0, 5, 9, 6,10, 3, 4, 0, 5,14, 3,},
 {	12,10, 1,15,10, 4,15, 2, 9, 7, 2,12, 6, 9, 8, 5,
	 0, 6,13, 1, 3,13, 4,14,14, 0, 7,11, 5, 3,11, 8,
	 9, 4,14, 3,15, 2, 5,12, 2, 9, 8, 5,12,15, 3,10,
	 7,11, 0,14, 4, 1,10, 7, 1, 6,13, 0,11, 8, 6,13,},
 {	 4,13,11, 0, 2,11,14, 7,15, 4, 0, 9, 8, 1,13,10,
	 3,14,12, 3, 9, 5, 7,12, 5, 2,10,15, 6, 8, 1, 6,
	 1, 6, 4,11,11,13,13, 8,12, 1, 3, 4, 7,10,14, 7,
	10, 9,15, 5, 6, 0, 8,15, 0,14, 5, 2, 9, 3, 2,12,},
 {	13, 1, 2,15, 8,13, 4, 8, 6,10,15, 3,11, 7, 1, 4,
	10,12, 9, 5, 3, 6,14,11, 5, 0, 0,14,12, 9, 7, 2,
	 7, 2,11, 1, 4,14, 1, 7, 9, 4,12,10,14, 8, 2,13,
	 0,15, 6,12,10, 9,13, 0,15, 3, 3, 5, 5, 6, 8,11,}};