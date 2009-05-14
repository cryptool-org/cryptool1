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

#include "ZZ_helpers.h"
#include "NTL/ZZ.h"
#include "NTL/RR.h"
#include "NTL/mat_ZZ.h"
#include "NTL/LLL.h"
#include "afx.h"
#include <NTL/ZZXFactoring.h>

using namespace NTL;

class FactorHint
{
public:
	void setBitsOfP(int bop);
	FactorHint();
	~FactorHint();
	void MSBFact();
	void LSBFact();
	void cancel();
	static int status;
	static long reductions;
	void setN(ZZ N);
	void setP(ZZ p);
	void setB(int b);
	ZZ getN();
	ZZ getQ();
	ZZ getP();
	int getLatticeTime();
	int getReductionTime();
	int getOverallTime();
	CString log;
private:
	CString timeStamp();
	int bitsOfP;
	mat_ZZ Lattice; // the lattice to be reduced
	int dim;
	ZZ N; // modulus
	ZZ P;
	ZZ p;
	ZZ q;
	ZZ X;
	int m;
	int b;
	int d;
	int n;
	double buildLatticeTime;
	double reduceLatticeTime;
	double startTime;
	ZZX *polyPowers;
	void buildMSBPolyPowers();
	void buildLSBPolyPowers();
	void getMSBSolution();
	void getLSBSolution();
	void buildLattice();
	void reduceLattice();
	bool FindRoots(ZZX f, vec_ZZ& r);
	ZZ binom(int i, int j);
	static long StopLLL(const vec_ZZ& z);

};

