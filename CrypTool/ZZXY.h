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

#define NOMINMAX

#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <NTL/vector.h>
#include <NTL/matrix.h>
#include <afx.h>
#include "ZZ_helpers.h"

using namespace NTL;

NTL_vector_decl(vec_ZZX, vec_vec_ZZX)

NTL_matrix_decl(ZZX, vec_ZZX, vec_vec_ZZX, mat_ZZX)

NTL_vector_decl(vec_ZZ_pX, vec_vec_ZZ_pX)

NTL_matrix_decl(ZZ_pX, vec_ZZ_pX, vec_vec_ZZ_pX, mat_ZZ_pX)


class ZZXY{

public:
	int monomCount();
	ZZ norm(ZZ X, ZZ Y);
	ZZ content();
	ZZX subresultant(ZZXY B, int*);
	const ZZXY operator-(ZZXY& B);
	ZZXY operator*(ZZX& B);
	const ZZXY operator*(ZZXY& B);
	ZZXY operator *(ZZ &B);
	const ZZXY operator+(ZZXY& B);
	const ZZXY operator /(ZZ d);
	const ZZXY operator /(ZZX b);
	void pseudoDiv(ZZXY &B, ZZXY &Q, ZZXY &R, int*);
	ZZX resultant(const ZZXY b,int*);
	ZZ norm();
	void setCoeff(int xCoeff, int yCoeff, ZZ a);
	ZZ getCoeff(int xCoeff, int yCoeff);
	void changeXY();
	ZZX setX(ZZ x);
	ZZX setY(ZZ y);
	void kill();
	int getYDegree();
	CString print();
	void findRoots(ZZ&,ZZ&);
	ZZ eval(ZZ x, ZZ y);
	ZZXY& operator=(const ZZXY& f1);
private:

	int yDegree;
	vec_ZZX data;



};
