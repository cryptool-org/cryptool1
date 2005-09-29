#ifndef CMatrix_H
#define CMatrix_H

class CVector;

class  CMatrix
{
public:

private:
	double value_[4][4];	// [row][column]
	// (0,0) (0,1) (0,2) (0,3)
	// (1,0) (1,1) (1,2) (1,3)
	// (2,0) (2,1) (2,2) (2,3)
	// (3,0) (3,1) (3,2) (3,3)

public:
	CMatrix(
		);

	CMatrix(
		const CMatrix& matrix_in
		);

	CMatrix(
		const double& a00_in,
		const double& a01_in,
		const double& a02_in,
		const double& a03_in,
		const double& a10_in,
		const double& a11_in,
		const double& a12_in,
		const double& a13_in,
		const double& a20_in,
		const double& a21_in,
		const double& a22_in,
		const double& a23_in,
		const double& a30_in,
		const double& a31_in,
		const double& a32_in,
		const double& a33_in
		);

	CMatrix(
		const double a_in[16]
		);

	CMatrix&
	operator=(
		const CMatrix& matrix_in
		);

	CVector
	operator[](
		const unsigned short rowIndex_in
		) const;

	double&
	operator()(
		const unsigned short rowIndex_in,
		const unsigned short colIndex_in
		);

	double
	operator()(
		const unsigned short rowIndex_in,
		const unsigned short colIndex_in
		) const;

	void
	set(
		const double& a00_in,
		const double& a01_in,
		const double& a02_in,
		const double& a03_in,
		const double& a10_in,
		const double& a11_in,
		const double& a12_in,
		const double& a13_in,
		const double& a20_in,
		const double& a21_in,
		const double& a22_in,
		const double& a23_in,
		const double& a30_in,
		const double& a31_in,
		const double& a32_in,
		const double& a33_in
		);

	void
	get(
		double& a00_out,
		double& a01_out,
		double& a02_out,
		double& a03_out,
		double& a10_out,
		double& a11_out,
		double& a12_out,
		double& a13_out,
		double& a20_out,
		double& a21_out,
		double& a22_out,
		double& a23_out,
		double& a30_out,
		double& a31_out,
		double& a32_out,
		double& a33_out
		) const;

	void
	setZeroMatrix(
		);

	static CMatrix
	zeroMatrix(
		);

	void
	setIdentityMatrix(
		);

	static CMatrix
	identityMatrix(
		);


	bool
	operator==(
		const CMatrix& matrix_in
		) const;

	bool
	operator!=(
		const CMatrix& matrix_in
		) const;

	CMatrix
	operator-(
		) const;

	friend  CMatrix
	operator-(
		const CMatrix& matrix0_in,
		const CMatrix& matrix1_in
		);

	friend  CMatrix
	operator+(
		const CMatrix& matrix0_in,
		const CMatrix& matrix1_in
		);

	friend  CMatrix
	operator*(
		const CMatrix& matrix0_in,
		const CMatrix& matrix1_in
		);

	friend  CMatrix
	operator*(
		const double& scalar_in,
		const CMatrix& matrix_in
		);

	friend  CMatrix
	operator*(
		const CMatrix& matrix_in,
		const double& scalar_in
		);

	friend  CVector
	operator*(
		const CVector& rowVector_in,
		const CMatrix& matrix_in
		);

	friend  CVector
	operator*(
		const CMatrix& matrix_in,
		const CVector& colVector_in
		);

	CMatrix&
	operator+=(
		const CMatrix& matrix_in
		);

	CMatrix&
	operator-=(
		const CMatrix& matrix_in
		);

	CMatrix&
	operator*=(
		const CMatrix& matrix_in
		);

	CMatrix&
	operator*=(
		const double& scalar_in
		);

	void
	invert(
		);

	CMatrix
	getInverse(
		) const;

	void
	transpose(
		);

	CMatrix
	getTransposed(
		) const;

	bool
	isIdentityMatrix(
		) const;

	bool
	isZeroMatrix(
		) const;

	double 
	getSubDeterminant(
		const unsigned short rowIndex_in,
		const unsigned short colIndex_in
		) const;

	
	double
	getDeterminant(
		) const;
};

#endif // CMatrix_H
