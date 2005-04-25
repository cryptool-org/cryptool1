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
