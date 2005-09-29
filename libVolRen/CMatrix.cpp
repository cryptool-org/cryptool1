#include <stdio.h>
#include <math.h>

#include "CMatrix.h"
#include "CVector.h"

#define _EPSILON (0.0001)

CMatrix::CMatrix(
	)
{
	value_[0][0] = 0.0;
	value_[0][1] = 0.0;
	value_[0][2] = 0.0;
	value_[0][3] = 0.0;

	value_[1][0] = 0.0;
	value_[1][1] = 0.0;
	value_[1][2] = 0.0;
	value_[1][3] = 0.0;

	value_[2][0] = 0.0;
	value_[2][1] = 0.0;
	value_[2][2] = 0.0;
	value_[2][3] = 0.0;

	value_[3][0] = 0.0;
	value_[3][1] = 0.0;
	value_[3][2] = 0.0;
	value_[3][3] = 0.0;
}

CMatrix::CMatrix(
	const CMatrix& matrix_in
	)
{
	value_[0][0] = matrix_in.value_[0][0];
	value_[0][1] = matrix_in.value_[0][1];
	value_[0][2] = matrix_in.value_[0][2];
	value_[0][3] = matrix_in.value_[0][3];

	value_[1][0] = matrix_in.value_[1][0];
	value_[1][1] = matrix_in.value_[1][1];
	value_[1][2] = matrix_in.value_[1][2];
	value_[1][3] = matrix_in.value_[1][3];

	value_[2][0] = matrix_in.value_[2][0];
	value_[2][1] = matrix_in.value_[2][1];
	value_[2][2] = matrix_in.value_[2][2];
	value_[2][3] = matrix_in.value_[2][3];

	value_[3][0] = matrix_in.value_[3][0];
	value_[3][1] = matrix_in.value_[3][1];
	value_[3][2] = matrix_in.value_[3][2];
	value_[3][3] = matrix_in.value_[3][3];
}



CMatrix::CMatrix(
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
	)
{
	value_[0][0] = a00_in;
	value_[0][1] = a01_in;
	value_[0][2] = a02_in;
	value_[0][3] = a03_in;

	value_[1][0] = a10_in;
	value_[1][1] = a11_in;
	value_[1][2] = a12_in;
	value_[1][3] = a13_in;

	value_[2][0] = a20_in;
	value_[2][1] = a21_in;
	value_[2][2] = a22_in;
	value_[2][3] = a23_in;

	value_[3][0] = a30_in;
	value_[3][1] = a31_in;
	value_[3][2] = a32_in;
	value_[3][3] = a33_in;
}

CMatrix::CMatrix(
	const double a_in[16]
	)
{
	value_[0][0] = a_in[0];
	value_[0][1] = a_in[1];
	value_[0][2] = a_in[2];
	value_[0][3] = a_in[3];

	value_[1][0] = a_in[4];
	value_[1][1] = a_in[5];
	value_[1][2] = a_in[6];
	value_[1][3] = a_in[7];

	value_[2][0] = a_in[8];
	value_[2][1] = a_in[9];
	value_[2][2] = a_in[10];
	value_[2][3] = a_in[11];

	value_[3][0] = a_in[12];
	value_[3][1] = a_in[13];
	value_[3][2] = a_in[14];
	value_[3][3] = a_in[15];
}

CMatrix&
CMatrix::operator=(
	const CMatrix& matrix_in
	)
{
	if(&matrix_in != this)
	{
		value_[0][0] = matrix_in.value_[0][0];
		value_[0][1] = matrix_in.value_[0][1];
		value_[0][2] = matrix_in.value_[0][2];
		value_[0][3] = matrix_in.value_[0][3];

		value_[1][0] = matrix_in.value_[1][0];
		value_[1][1] = matrix_in.value_[1][1];
		value_[1][2] = matrix_in.value_[1][2];
		value_[1][3] = matrix_in.value_[1][3];

		value_[2][0] = matrix_in.value_[2][0];
		value_[2][1] = matrix_in.value_[2][1];
		value_[2][2] = matrix_in.value_[2][2];
		value_[2][3] = matrix_in.value_[2][3];

		value_[3][0] = matrix_in.value_[3][0];
		value_[3][1] = matrix_in.value_[3][1];
		value_[3][2] = matrix_in.value_[3][2];
		value_[3][3] = matrix_in.value_[3][3];
	}

	return *this;
}

CVector
CMatrix::operator[](
	const unsigned short rowIndex_in
	) const
{
	if(rowIndex_in > 3)
		throw;

	return CVector(
		value_[rowIndex_in][0],
		value_[rowIndex_in][1],
		value_[rowIndex_in][2],
		value_[rowIndex_in][3]
		);
}

double&
CMatrix::operator()(
	const unsigned short rowIndex_in,
	const unsigned short colIndex_in
	)
{
	if( (rowIndex_in > 3) || (colIndex_in > 3) )
		throw;

	return value_[rowIndex_in][colIndex_in];
}

double
CMatrix::operator()(
	const unsigned short rowIndex_in,
	const unsigned short colIndex_in
	) const
{
	if( (rowIndex_in > 3) || (colIndex_in > 3) )
		throw;

	return value_[rowIndex_in][colIndex_in];
}

void
CMatrix::set(
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
	)
{
	value_[0][0] = a00_in;
	value_[0][1] = a01_in;
	value_[0][2] = a02_in;
	value_[0][3] = a03_in;

	value_[1][0] = a10_in;
	value_[1][1] = a11_in;
	value_[1][2] = a12_in;
	value_[1][3] = a13_in;

	value_[2][0] = a20_in;
	value_[2][1] = a21_in;
	value_[2][2] = a22_in;
	value_[2][3] = a23_in;

	value_[3][0] = a30_in;
	value_[3][1] = a31_in;
	value_[3][2] = a32_in;
	value_[3][3] = a33_in;
}

void
CMatrix::get(
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
	) const
{
	a00_out = value_[0][0];
	a01_out = value_[0][1];
	a02_out = value_[0][2];
	a03_out = value_[0][3];

	a10_out = value_[1][0];
	a11_out = value_[1][1];
	a12_out = value_[1][2];
	a13_out = value_[1][3];

	a20_out = value_[2][0];
	a21_out = value_[2][1];
	a22_out = value_[2][2];
	a23_out = value_[2][3];

	a30_out = value_[3][0];
	a31_out = value_[3][1];
	a32_out = value_[3][2];
	a33_out = value_[3][3];
}

void
CMatrix::setZeroMatrix(
	)
{
	*this = zeroMatrix();
}

CMatrix
CMatrix::zeroMatrix(
	)
{
	return CMatrix(
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0
		);
}

void
CMatrix::setIdentityMatrix(
	)
{
	*this = identityMatrix();
}

CMatrix
CMatrix::identityMatrix(
	)
{
	return CMatrix(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
		);
}

bool
CMatrix::operator==(
	const CMatrix& matrix_in
	) const
{
	if( (fabs(value_[0][0] - matrix_in.value_[0][0]) > _EPSILON)
		|| (fabs(value_[0][1] - matrix_in.value_[0][1]) > _EPSILON)
		|| (fabs(value_[0][2] - matrix_in.value_[0][2]) > _EPSILON)
		|| (fabs(value_[0][3] - matrix_in.value_[0][3]) > _EPSILON)

		|| (fabs(value_[1][0] - matrix_in.value_[1][0]) > _EPSILON)
		|| (fabs(value_[1][1] - matrix_in.value_[1][1]) > _EPSILON)
		|| (fabs(value_[1][2] - matrix_in.value_[1][2]) > _EPSILON)
		|| (fabs(value_[1][3] - matrix_in.value_[1][3]) > _EPSILON)

		|| (fabs(value_[2][0] - matrix_in.value_[2][0]) > _EPSILON)
		|| (fabs(value_[2][1] - matrix_in.value_[2][1]) > _EPSILON)
		|| (fabs(value_[2][2] - matrix_in.value_[2][2]) > _EPSILON)
		|| (fabs(value_[2][3] - matrix_in.value_[2][3]) > _EPSILON)

		|| (fabs(value_[3][0] - matrix_in.value_[3][0]) > _EPSILON)
		|| (fabs(value_[3][1] - matrix_in.value_[3][1]) > _EPSILON)
		|| (fabs(value_[3][2] - matrix_in.value_[3][2]) > _EPSILON)
		|| (fabs(value_[3][3] - matrix_in.value_[3][3]) > _EPSILON) )
		return false;
	return true;
}

bool
CMatrix::operator!=(
	const CMatrix& matrix_in
	) const
{
	return( !(*this == matrix_in) );
}

CMatrix
CMatrix::operator-(
	) const
{
	return CMatrix(
		-value_[0][0], -value_[0][1], -value_[0][2], -value_[0][3],
		-value_[1][0], -value_[1][1], -value_[1][2], -value_[1][3],
		-value_[2][0], -value_[2][1], -value_[2][2], -value_[2][3],
		-value_[3][0], -value_[3][1], -value_[3][2], -value_[3][3]
		);
}

CMatrix
operator-(
	const CMatrix& matrix0_in,
	const CMatrix& matrix1_in
	)
{
	return CMatrix(
		matrix0_in.value_[0][0] - matrix1_in.value_[0][0],
		matrix0_in.value_[0][1] - matrix1_in.value_[0][1],
		matrix0_in.value_[0][2] - matrix1_in.value_[0][2],
		matrix0_in.value_[0][3] - matrix1_in.value_[0][3],

		matrix0_in.value_[1][0] - matrix1_in.value_[1][0],
		matrix0_in.value_[1][1] - matrix1_in.value_[1][1],
		matrix0_in.value_[1][2] - matrix1_in.value_[1][2],
		matrix0_in.value_[1][3] - matrix1_in.value_[1][3],

		matrix0_in.value_[2][0] - matrix1_in.value_[2][0],
		matrix0_in.value_[2][1] - matrix1_in.value_[2][1],
		matrix0_in.value_[2][2] - matrix1_in.value_[2][2],
		matrix0_in.value_[2][3] - matrix1_in.value_[2][3],

		matrix0_in.value_[3][0] - matrix1_in.value_[3][0],
		matrix0_in.value_[3][1] - matrix1_in.value_[3][1],
		matrix0_in.value_[3][2] - matrix1_in.value_[3][2],
		matrix0_in.value_[3][3] - matrix1_in.value_[3][3]
		);
}

CMatrix
operator+(
	const CMatrix& matrix0_in,
	const CMatrix& matrix1_in
	)
{
	return CMatrix(
		matrix0_in.value_[0][0] + matrix1_in.value_[0][0],
		matrix0_in.value_[0][1] + matrix1_in.value_[0][1],
		matrix0_in.value_[0][2] + matrix1_in.value_[0][2],
		matrix0_in.value_[0][3] + matrix1_in.value_[0][3],

		matrix0_in.value_[1][0] + matrix1_in.value_[1][0],
		matrix0_in.value_[1][1] + matrix1_in.value_[1][1],
		matrix0_in.value_[1][2] + matrix1_in.value_[1][2],
		matrix0_in.value_[1][3] + matrix1_in.value_[1][3],

		matrix0_in.value_[2][0] + matrix1_in.value_[2][0],
		matrix0_in.value_[2][1] + matrix1_in.value_[2][1],
		matrix0_in.value_[2][2] + matrix1_in.value_[2][2],
		matrix0_in.value_[2][3] + matrix1_in.value_[2][3],

		matrix0_in.value_[3][0] + matrix1_in.value_[3][0],
		matrix0_in.value_[3][1] + matrix1_in.value_[3][1],
		matrix0_in.value_[3][2] + matrix1_in.value_[3][2],
		matrix0_in.value_[3][3] + matrix1_in.value_[3][3]
		);
}

CMatrix
operator*(
	const CMatrix& matrix0_in,
	const CMatrix& matrix1_in
	)
{
	return CMatrix(
		matrix0_in.value_[0][0] * matrix1_in.value_[0][0]
		+ matrix0_in.value_[0][1] * matrix1_in.value_[1][0]
		+ matrix0_in.value_[0][2] * matrix1_in.value_[2][0]
		+ matrix0_in.value_[0][3] * matrix1_in.value_[3][0],

		matrix0_in.value_[0][0] * matrix1_in.value_[0][1]
		+ matrix0_in.value_[0][1] * matrix1_in.value_[1][1]
		+ matrix0_in.value_[0][2] * matrix1_in.value_[2][1]
		+ matrix0_in.value_[0][3] * matrix1_in.value_[3][1],

		matrix0_in.value_[0][0] * matrix1_in.value_[0][2]
		+ matrix0_in.value_[0][1] * matrix1_in.value_[1][2]
		+ matrix0_in.value_[0][2] * matrix1_in.value_[2][2]
		+ matrix0_in.value_[0][3] * matrix1_in.value_[3][2],

		matrix0_in.value_[0][0] * matrix1_in.value_[0][3]
		+ matrix0_in.value_[0][1] * matrix1_in.value_[1][3]
		+ matrix0_in.value_[0][2] * matrix1_in.value_[2][3]
		+ matrix0_in.value_[0][3] * matrix1_in.value_[3][3],


		matrix0_in.value_[1][0] * matrix1_in.value_[0][0]
		+ matrix0_in.value_[1][1] * matrix1_in.value_[1][0]
		+ matrix0_in.value_[1][2] * matrix1_in.value_[2][0]
		+ matrix0_in.value_[1][3] * matrix1_in.value_[3][0],

		matrix0_in.value_[1][0] * matrix1_in.value_[0][1]
		+ matrix0_in.value_[1][1] * matrix1_in.value_[1][1]
		+ matrix0_in.value_[1][2] * matrix1_in.value_[2][1]
		+ matrix0_in.value_[1][3] * matrix1_in.value_[3][1],

		matrix0_in.value_[1][0] * matrix1_in.value_[0][2]
		+ matrix0_in.value_[1][1] * matrix1_in.value_[1][2]
		+ matrix0_in.value_[1][2] * matrix1_in.value_[2][2]
		+ matrix0_in.value_[1][3] * matrix1_in.value_[3][2],

		matrix0_in.value_[1][0] * matrix1_in.value_[0][3]
		+ matrix0_in.value_[1][1] * matrix1_in.value_[1][3]
		+ matrix0_in.value_[1][2] * matrix1_in.value_[2][3]
		+ matrix0_in.value_[1][3] * matrix1_in.value_[3][3],


		matrix0_in.value_[2][0] * matrix1_in.value_[0][0]
		+ matrix0_in.value_[2][1] * matrix1_in.value_[1][0]
		+ matrix0_in.value_[2][2] * matrix1_in.value_[2][0]
		+ matrix0_in.value_[2][3] * matrix1_in.value_[3][0],

		matrix0_in.value_[2][0] * matrix1_in.value_[0][1]
		+ matrix0_in.value_[2][1] * matrix1_in.value_[1][1]
		+ matrix0_in.value_[2][2] * matrix1_in.value_[2][1]
		+ matrix0_in.value_[2][3] * matrix1_in.value_[3][1],

		matrix0_in.value_[2][0] * matrix1_in.value_[0][2]
		+ matrix0_in.value_[2][1] * matrix1_in.value_[1][2]
		+ matrix0_in.value_[2][2] * matrix1_in.value_[2][2]
		+ matrix0_in.value_[2][3] * matrix1_in.value_[3][2],

		matrix0_in.value_[2][0] * matrix1_in.value_[0][3]
		+ matrix0_in.value_[2][1] * matrix1_in.value_[1][3]
		+ matrix0_in.value_[2][2] * matrix1_in.value_[2][3]
		+ matrix0_in.value_[2][3] * matrix1_in.value_[3][3],


		matrix0_in.value_[3][0] * matrix1_in.value_[0][0]
		+ matrix0_in.value_[3][1] * matrix1_in.value_[1][0]
		+ matrix0_in.value_[3][2] * matrix1_in.value_[2][0]
		+ matrix0_in.value_[3][3] * matrix1_in.value_[3][0],

		matrix0_in.value_[3][0] * matrix1_in.value_[0][1]
		+ matrix0_in.value_[3][1] * matrix1_in.value_[1][1]
		+ matrix0_in.value_[3][2] * matrix1_in.value_[2][1]
		+ matrix0_in.value_[3][3] * matrix1_in.value_[3][1],

		matrix0_in.value_[3][0] * matrix1_in.value_[0][2]
		+ matrix0_in.value_[3][1] * matrix1_in.value_[1][2]
		+ matrix0_in.value_[3][2] * matrix1_in.value_[2][2]
		+ matrix0_in.value_[3][3] * matrix1_in.value_[3][2],

		matrix0_in.value_[3][0] * matrix1_in.value_[0][3]
		+ matrix0_in.value_[3][1] * matrix1_in.value_[1][3]
		+ matrix0_in.value_[3][2] * matrix1_in.value_[2][3]
		+ matrix0_in.value_[3][3] * matrix1_in.value_[3][3]
		);
}

CMatrix
operator*(
	const double& scalar_in,
	const CMatrix& matrix_in
	)
{
	return CMatrix(
		scalar_in * matrix_in.value_[0][0],
		scalar_in * matrix_in.value_[0][1],
		scalar_in * matrix_in.value_[0][2],
		scalar_in * matrix_in.value_[0][3],

		scalar_in * matrix_in.value_[1][0],
		scalar_in * matrix_in.value_[1][1],
		scalar_in * matrix_in.value_[1][2],
		scalar_in * matrix_in.value_[1][3],

		scalar_in * matrix_in.value_[2][0],
		scalar_in * matrix_in.value_[2][1],
		scalar_in * matrix_in.value_[2][2],
		scalar_in * matrix_in.value_[2][3],

		scalar_in * matrix_in.value_[3][0],
		scalar_in * matrix_in.value_[3][1],
		scalar_in * matrix_in.value_[3][2],
		scalar_in * matrix_in.value_[3][3]
		);
}

CMatrix
operator*(
	const CMatrix& matrix_in,
	const double& scalar_in
	)
{
	return CMatrix(
		matrix_in.value_[0][0] * scalar_in,
		matrix_in.value_[0][1] * scalar_in,
		matrix_in.value_[0][2] * scalar_in,
		matrix_in.value_[0][3] * scalar_in,

		matrix_in.value_[1][0] * scalar_in,
		matrix_in.value_[1][1] * scalar_in,
		matrix_in.value_[1][2] * scalar_in,
		matrix_in.value_[1][3] * scalar_in,

		matrix_in.value_[2][0] * scalar_in,
		matrix_in.value_[2][1] * scalar_in,
		matrix_in.value_[2][2] * scalar_in,
		matrix_in.value_[2][3] * scalar_in,

		matrix_in.value_[3][0] * scalar_in,
		matrix_in.value_[3][1] * scalar_in,
		matrix_in.value_[3][2] * scalar_in,
		matrix_in.value_[3][3] * scalar_in
		);
}

CVector
operator*(
	const CVector& rowVector_in,
	const CMatrix& matrix_in
	)
{
	return CVector(
		rowVector_in[0] * matrix_in.value_[0][0]
		+ rowVector_in[1] * matrix_in.value_[1][0]
		+ rowVector_in[2] * matrix_in.value_[2][0]
		+ rowVector_in[3] * matrix_in.value_[3][0],

		rowVector_in[0] * matrix_in.value_[0][1]
		+ rowVector_in[1] * matrix_in.value_[1][1]
		+ rowVector_in[2] * matrix_in.value_[2][1]
		+ rowVector_in[3] * matrix_in.value_[3][1],

		rowVector_in[0] * matrix_in.value_[0][2]
		+ rowVector_in[1] * matrix_in.value_[1][2]
		+ rowVector_in[2] * matrix_in.value_[2][2]
		+ rowVector_in[3] * matrix_in.value_[3][2],

		rowVector_in[0] * matrix_in.value_[0][3]
		+ rowVector_in[1] * matrix_in.value_[1][3]
		+ rowVector_in[2] * matrix_in.value_[2][3]
		+ rowVector_in[3] * matrix_in.value_[3][3]
		);
}

CVector
operator*(
	const CMatrix& matrix_in,
	const CVector& colVector_in
	)
{
	return CVector(
		matrix_in.value_[0][0] * colVector_in[0]
		+ matrix_in.value_[0][1] * colVector_in[1]
		+ matrix_in.value_[0][2] * colVector_in[2]
		+ matrix_in.value_[0][3] * colVector_in[3],

		matrix_in.value_[1][0] * colVector_in[0]
		+ matrix_in.value_[1][1] * colVector_in[1]
		+ matrix_in.value_[1][2] * colVector_in[2]
		+ matrix_in.value_[1][3] * colVector_in[3],

		matrix_in.value_[2][0] * colVector_in[0]
		+ matrix_in.value_[2][1] * colVector_in[1]
		+ matrix_in.value_[2][2] * colVector_in[2]
		+ matrix_in.value_[2][3] * colVector_in[3],

		matrix_in.value_[3][0] * colVector_in[0]
		+ matrix_in.value_[3][1] * colVector_in[1]
		+ matrix_in.value_[3][2] * colVector_in[2]
		+ matrix_in.value_[3][3] * colVector_in[3]
		);
}

CMatrix&
CMatrix::operator+=(
	const CMatrix& matrix_in
	)
{
	value_[0][0] += matrix_in.value_[0][0];
	value_[0][1] += matrix_in.value_[0][1];
	value_[0][2] += matrix_in.value_[0][2];
	value_[0][3] += matrix_in.value_[0][3];

	value_[1][0] += matrix_in.value_[1][0];
	value_[1][1] += matrix_in.value_[1][1];
	value_[1][2] += matrix_in.value_[1][2];
	value_[1][3] += matrix_in.value_[1][3];

	value_[2][0] += matrix_in.value_[2][0];
	value_[2][1] += matrix_in.value_[2][1];
	value_[2][2] += matrix_in.value_[2][2];
	value_[2][3] += matrix_in.value_[2][3];

	value_[3][0] += matrix_in.value_[3][0];
	value_[3][1] += matrix_in.value_[3][1];
	value_[3][2] += matrix_in.value_[3][2];
	value_[3][3] += matrix_in.value_[3][3];

	return *this;
}

CMatrix&
CMatrix::operator-=(
	const CMatrix& matrix_in
	)
{
	value_[0][0] -= matrix_in.value_[0][0];
	value_[0][1] -= matrix_in.value_[0][1];
	value_[0][2] -= matrix_in.value_[0][2];
	value_[0][3] -= matrix_in.value_[0][3];

	value_[1][0] -= matrix_in.value_[1][0];
	value_[1][1] -= matrix_in.value_[1][1];
	value_[1][2] -= matrix_in.value_[1][2];
	value_[1][3] -= matrix_in.value_[1][3];

	value_[2][0] -= matrix_in.value_[2][0];
	value_[2][1] -= matrix_in.value_[2][1];
	value_[2][2] -= matrix_in.value_[2][2];
	value_[2][3] -= matrix_in.value_[2][3];

	value_[3][0] -= matrix_in.value_[3][0];
	value_[3][1] -= matrix_in.value_[3][1];
	value_[3][2] -= matrix_in.value_[3][2];
	value_[3][3] -= matrix_in.value_[3][3];

	return *this;
}

CMatrix&
CMatrix::operator*=(
	const CMatrix& matrix_in
	)
{
	*this = *this * matrix_in;

	return *this;
}

CMatrix&
CMatrix::operator*=(
	const double& scalar_in
	)
{
	value_[0][0] *= scalar_in;
	value_[0][1] *= scalar_in;
	value_[0][2] *= scalar_in;
	value_[0][3] *= scalar_in;

	value_[1][0] *= scalar_in;
	value_[1][1] *= scalar_in;
	value_[1][2] *= scalar_in;
	value_[1][3] *= scalar_in;

	value_[2][0] *= scalar_in;
	value_[2][1] *= scalar_in;
	value_[2][2] *= scalar_in;
	value_[2][3] *= scalar_in;

	value_[3][0] *= scalar_in;
	value_[3][1] *= scalar_in;
	value_[3][2] *= scalar_in;
	value_[3][3] *= scalar_in;

	return *this;
}

void
CMatrix::invert(
	)
{
	*this = getInverse();
}

CMatrix
CMatrix::getInverse(
	) const
{
	double det;
	det = getDeterminant();

	if(fabs(det) < _EPSILON)
		throw;


	return CMatrix(
		getSubDeterminant(0,0) / det,
		-getSubDeterminant(1,0) / det,
		getSubDeterminant(2,0) / det,
		-getSubDeterminant(3,0) / det,

		-getSubDeterminant(0,1) / det,
		getSubDeterminant(1,1) / det,
		-getSubDeterminant(2,1) / det,
		getSubDeterminant(3,1) / det,

		getSubDeterminant(0,2) / det,
		-getSubDeterminant(1,2) / det,
		getSubDeterminant(2,2) / det,
		-getSubDeterminant(3,2) / det,

		-getSubDeterminant(0,3) / det,
		getSubDeterminant(1,3) / det,
		-getSubDeterminant(2,3) / det,
		getSubDeterminant(3,3) / det
		);
}

void
CMatrix::transpose(
	)
{
	*this = getTransposed();
}

CMatrix
CMatrix::getTransposed(
	) const
{
	return CMatrix(
		value_[0][0], value_[1][0], value_[2][0], value_[3][0],
		value_[0][1], value_[1][1], value_[2][1], value_[3][1],
		value_[0][2], value_[1][2], value_[2][2], value_[3][2],
		value_[0][3], value_[1][3], value_[2][3], value_[3][3]
		);
}

bool
CMatrix::isIdentityMatrix(
	) const
{
	return( *this == identityMatrix() );
}

bool
CMatrix::isZeroMatrix(
	) const
{
	return( *this == zeroMatrix() );
}

double
CMatrix::getDeterminant(
	) const
{
	return(
		value_[0][0] * getSubDeterminant(0,0)
		- value_[1][0] * getSubDeterminant(1,0)
		+ value_[2][0] * getSubDeterminant(2,0)
		- value_[3][0] * getSubDeterminant(3,0)
		);
}

double
CMatrix::getSubDeterminant(
	const unsigned short rowIndex_in,
	const unsigned short colIndex_in
	) const
{
	if( (rowIndex_in > 3) || (colIndex_in > 3) )
		throw;

	double subMatrix[3][3];
	int srcRow;
	int srcCol;

	srcRow = 0;
	for(int dstRow=0; dstRow<3; dstRow++)
	{
		if(dstRow == rowIndex_in)
			srcRow++;

		srcCol = 0;
		for(int dstCol=0; dstCol<3; dstCol++)
		{
			if(dstCol == colIndex_in)
				srcCol++;

			subMatrix[dstRow][dstCol] = value_[srcRow][srcCol];

			srcCol++;
		}

		srcRow++;
	}

	double dSubDet = 
		subMatrix[0][0] * subMatrix[1][1] * subMatrix[2][2]
	  + subMatrix[1][0] * subMatrix[2][1] * subMatrix[0][2]
	  + subMatrix[0][1] * subMatrix[1][2] * subMatrix[2][0]
	  -	subMatrix[2][0] * subMatrix[1][1] * subMatrix[0][2]
	  -	subMatrix[2][1] * subMatrix[1][2] * subMatrix[0][0]
	  -	subMatrix[1][0] * subMatrix[0][1] * subMatrix[2][2];

	return dSubDet;
}
