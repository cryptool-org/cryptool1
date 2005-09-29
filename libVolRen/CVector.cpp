#include <stdio.h>
#include <math.h>

#include "CVector.h"

#define _EPSILON (0.0001)

CVector::CVector(
	)
{
	value_[0] = 0.0;
	value_[1] = 0.0;
	value_[2] = 0.0;
	value_[3] = 0.0;
}

CVector::CVector(
	const CVector& vector_in
	)
{
	value_[0] = vector_in.value_[0];
	value_[1] = vector_in.value_[1];
	value_[2] = vector_in.value_[2];
	value_[3] = vector_in.value_[3];
}

CVector::CVector(
	const double& a_in,
	const double& b_in,
	const double& c_in,
	const double& d_in
	)
{
	value_[0] = a_in;
	value_[1] = b_in;
	value_[2] = c_in;
	value_[3] = d_in;
}

CVector&
CVector::operator=(
	const CVector& vector_in
	)
{
	if(&vector_in != this)
	{
		value_[0] = vector_in.value_[0];
		value_[1] = vector_in.value_[1];
		value_[2] = vector_in.value_[2];
		value_[3] = vector_in.value_[3];
	}

	return *this;
}

double&
CVector::operator[](
	const unsigned short index_in
	)
{
	if(index_in > 3)
		throw;

	return value_[index_in];
}

double
CVector::operator[](
	const unsigned short index_in
	) const
{
	if(index_in > 3)
		throw;

	return value_[index_in];
}

double&
CVector::operator()(
	const unsigned short index_in
	)
{
	if(index_in > 3)
		throw;

	return value_[index_in];
}

double
CVector::operator()(
	const unsigned short index_in
	) const
{
	if(index_in > 3)
		throw;

	return value_[index_in];
}

void
CVector::set(
	const double& a_in, 
	const double& b_in,
	const double& c_in,
	const double& d_in
	)
{
	value_[0] = a_in;
	value_[1] = b_in;
	value_[2] = c_in;
	value_[3] = d_in;
}

void
CVector::get(
	double& a_out, 
	double& b_out,
	double& c_out,
	double& d_out
	) const
{
	a_out = value_[0];
	b_out = value_[1];
	c_out = value_[2];
	d_out = value_[3];
}

bool
CVector::operator==(
	const CVector& vector_in
	) const
{
	if( (fabs(value_[0] - vector_in.value_[0]) >    _EPSILON)
		|| (fabs(value_[1] - vector_in.value_[1]) > _EPSILON)
		|| (fabs(value_[2] - vector_in.value_[2]) > _EPSILON)
		|| (fabs(value_[3] - vector_in.value_[3]) > _EPSILON) )
		return false;
	return true;
}

bool
CVector::operator!=(
	const CVector& vector_in
	) const
{
	return( !(*this == vector_in) );
}

CVector
CVector::operator-(
	) const
{
	return CVector(
		-value_[0],
		-value_[1],
		-value_[2],
		-value_[3]
		);
}

CVector
operator-(
	const CVector& vector0_in,
	const CVector& vector1_in
	)
{
	return CVector(
		vector0_in.value_[0] - vector1_in.value_[0],
		vector0_in.value_[1] - vector1_in.value_[1],
		vector0_in.value_[2] - vector1_in.value_[2],
		vector0_in.value_[3] - vector1_in.value_[3]
		);
}

CVector
operator+(
	const CVector& vector0_in,
	const CVector& vector1_in
	)
{
	return CVector(
		vector0_in.value_[0] + vector1_in.value_[0],
		vector0_in.value_[1] + vector1_in.value_[1],
		vector0_in.value_[2] + vector1_in.value_[2],
		vector0_in.value_[3] + vector1_in.value_[3]
		);
}

double
operator*(
	const CVector& vector0_in,
	const CVector& vector1_in
	)
{
	return(
		vector0_in.value_[0] * vector1_in.value_[0]
		+ vector0_in.value_[1] * vector1_in.value_[1]
		+ vector0_in.value_[2] * vector1_in.value_[2]
		+ vector0_in.value_[3] * vector1_in.value_[3]
		);
}

double
CVector::getInnerProduct(
	const CVector& vector_in
	) const
{
	return(
		value_[0] * vector_in.value_[0]
		+ value_[1] * vector_in.value_[1]
		+ value_[2] * vector_in.value_[2]
		+ value_[3] * vector_in.value_[3]
		);
}
  
CVector
operator*(
	const double& scalar_in,
	const CVector& vector_in
	)
{
	return CVector(
		scalar_in * vector_in.value_[0],
		scalar_in * vector_in.value_[1],
		scalar_in * vector_in.value_[2],
		scalar_in * vector_in.value_[3]
		);
}

CVector
operator*(
	const CVector& vector_in,
	const double& scalar_in
	)
{
	return CVector(
		vector_in.value_[0] * scalar_in,
		vector_in.value_[1] * scalar_in,
		vector_in.value_[2] * scalar_in,
		vector_in.value_[3] * scalar_in
		);
}

CVector
operator/(
	const CVector& vector_in,
	const double& scalar_in
	)
{
	return CVector(
		vector_in.value_[0] / scalar_in,
		vector_in.value_[1] / scalar_in,
		vector_in.value_[2] / scalar_in,
		vector_in.value_[3] / scalar_in
		);
}

CVector&
CVector::operator+=(
	const CVector& vector_in
	)
{
	value_[0] += vector_in.value_[0];
	value_[1] += vector_in.value_[1];
	value_[2] += vector_in.value_[2];
	value_[3] += vector_in.value_[3];

	return *this;
}

CVector&
CVector::operator-=(
	const CVector& vector_in
	)
{
	value_[0] -= vector_in.value_[0];
	value_[1] -= vector_in.value_[1];
	value_[2] -= vector_in.value_[2];
	value_[3] -= vector_in.value_[3];

	return *this;
}

CVector&
CVector::operator*=(
	const double& scalar_in
	)
{
	value_[0] *= scalar_in;
	value_[1] *= scalar_in;
	value_[2] *= scalar_in;
	value_[3] *= scalar_in;

	return *this;
}

CVector&
CVector::operator/=(
	const double& scalar_in
	)
{
	value_[0] /= scalar_in;
	value_[1] /= scalar_in;
	value_[2] /= scalar_in;
	value_[3] /= scalar_in;

	return *this;
}

double
CVector::getLength(
	) const
{
    return sqrt(
		value_[0] * value_[0] 
		+ value_[1] * value_[1]
		+ value_[2] * value_[2]
		+ value_[3] * value_[3]
		);
}

void
CVector::normalize(
	)
{
	double length;
	length = getLength();

	if( fabs( length ) < _EPSILON )
		throw;

	value_[0] /= length;
	value_[1] /= length;
	value_[2] /= length;
	value_[3] /= length;
}

bool
CVector::isNormalized(
	) const
{
	double length;
	length = getLength();

	if(fabs(length - 1.0) > _EPSILON)
		return false;
	return true;
}

bool
CVector::isNil(
	) const
{
	double length;
	length = getLength();

	if(fabs(length) > _EPSILON)
		return false;
	return true;
}
