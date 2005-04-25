
#include "ZZ_helpers.h"
#include "NTL/ZZ.h"
#include "NTL/RR.h"
#include "NTL/mat_ZZ.h"
#include "NTL/LLL.h"
#include "afx.h"
#include "ZZXY.h"
#include <NTL/ZZXFactoring.h>

#define BM_CANCELED 0
#define BM_BUILDING	1
#define BM_DELETING 2
#define BM_REDUCING 3
#define BM_RECONSTRUCTING 4
#define BM_BUILDINGRESULTANT 5
#define BM_SUCCESSFUL 6
#define BM_FAILED 7

using namespace NTL;

class BloemerMayAttack  
{
public:
	double maxDelta(int m, int t);
	int optimalT(int m);
	ZZ k;

	BloemerMayAttack();
	virtual ~BloemerMayAttack();
	void attack();
	void getSolution();
	void cancel();
	static int status;
	static long reductions;
	int getLatticeTime();
	int getReductionTime();
	int getResultantTime();
	int getOverallTime();
	int getResultants();
	void setN(ZZ N);
	void setE(ZZ e);
	void setM(int m);
	void setT(int t);
	void setDelta(double delta);
	ZZ getN();
	ZZ getE();
	ZZ getQ();
	ZZ getP();
	int getM();
	CString log;
	ZZ s;
private:
	CString timeStamp();
	int *columnXPowers;
	int *columnYPowers;
	bool *deletedVectors;
	mat_ZZ merk;
	int dim;
	ZZ N; // modulus
	ZZ e; // exponent e
	ZZ A; // N+1
	ZZ X; 
	ZZ Y;
	ZZ p;
	ZZ q;
	int m;
	int t;
	double delta;
	void buildPolyPowers();
	void buildLattice();
	void deleteBonehVectors();
	void deleteVectors();
	void reduceLattice();
	void reconstructLattice();
	bool FindRoots(ZZX f, vec_ZZ& r);
	ZZXY *polyPowers; // represent the f(xX,yX)^k polynomials
	mat_ZZ Lattice; // the lattice to be reduced
	ZZ BloemerMayAttack::binom(int i, int j);
	static long StopLLL(const vec_ZZ& z);

	
	int resultantsCheck;
	double startTime;
	double buildLatticeTime;
	double reduceLatticeTime;
	double findResultantTime;

};

