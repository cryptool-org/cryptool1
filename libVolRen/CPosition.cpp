
// ****************************************************************************
// *** Includes
// ****************************************************************************

#include <stdio.h>
#include <math.h>
#include "CPosition.h"

#define _EPSILON (0.0001)

CPosition::CPosition( )
{
	value_[0] = 0.0;
	value_[1] = 0.0;
}

CPosition::CPosition(const CPosition& vector_in)
{
	value_[0] = vector_in.value_[0];
	value_[1] = vector_in.value_[1];
}

CPosition::CPosition(const double& a_in,const double& b_in)
{
	value_[0] = a_in;
	value_[1] = b_in;
}

CPosition&
CPosition::operator=(const CPosition& vector_in)
{
	if(&vector_in != this)
	{
		value_[0] = vector_in.value_[0];
		value_[1] = vector_in.value_[1];
	}

	return *this;
}

double&
CPosition::operator[](const unsigned short index_in)
{
	if(index_in > 1)
		throw;

	return value_[index_in];
}

double
CPosition::operator[](const unsigned short index_in) const
{
	if(index_in > 1)
		throw;

	return value_[index_in];
}

double&
CPosition::operator()(const unsigned short index_in)
{
	if(index_in > 1)
		throw;

	return value_[index_in];
}

double
CPosition::operator()(const unsigned short index_in) const
{
	if(index_in > 1)
		throw;

	return value_[index_in];
}


void
CPosition::set(const double& a_in, const double& b_in)

{
	value_[0] = a_in;
	value_[1] = b_in;
}

void
CPosition::get( double& a_out, double& b_out) const

{
	a_out = value_[0];
	b_out = value_[1];
}

bool
CPosition::operator==( const CPosition& vector_in ) const

{
	if( (fabs(value_[0] - vector_in.value_[0]) > _EPSILON)
		|| (fabs(value_[1] - vector_in.value_[1]) > _EPSILON) )
		return false;
	return true;
}

bool
CPosition::operator!=(const CPosition& vector_in) const

{
	return( !(*this == vector_in) );
}


CPosition
CPosition::operator-( ) const

{
	return CPosition(
		-value_[0],
		-value_[1]
		);
}


CPosition
operator-(const CPosition& vector0_in,const CPosition& vector1_in)

{
	return CPosition(
		vector0_in.value_[0] - vector1_in.value_[0],
		vector0_in.value_[1] - vector1_in.value_[1]
		);
}


CPosition
operator+(const CPosition& vector0_in,const CPosition& vector1_in)

{
	return CPosition(
		vector0_in.value_[0] + vector1_in.value_[0],
		vector0_in.value_[1] + vector1_in.value_[1]
		);
}


double
operator*(const CPosition& vector0_in,const CPosition& vector1_in)

{
	return(
		vector0_in.value_[0] * vector1_in.value_[0]
		+ vector0_in.value_[1] * vector1_in.value_[1]
		);
}


CPosition
operator*(const double& scalar_in,const CPosition& vector_in)

{
	return CPosition(
		scalar_in * vector_in.value_[0],
		scalar_in * vector_in.value_[1]
		);
}


CPosition
operator*(const CPosition& vector_in,const double& scalar_in)

{
	return CPosition(
		vector_in.value_[0] * scalar_in,
		vector_in.value_[1] * scalar_in
		);
}


CPosition
operator/(const CPosition& vector_in,const double& scalar_in)

{
	return CPosition(
		vector_in.value_[0] / scalar_in,
		vector_in.value_[1] / scalar_in
		);
}


CPosition&
CPosition::operator+=(const CPosition& vector_in)

{
	value_[0] += vector_in.value_[0];
	value_[1] += vector_in.value_[1];

	return *this;
}


CPosition&
CPosition::operator-=(const CPosition& vector_in)

{
	value_[0] -= vector_in.value_[0];
	value_[1] -= vector_in.value_[1];

	return *this;
}


CPosition&
CPosition::operator*=(const double& scalar_in)

{
	value_[0] *= scalar_in;
	value_[1] *= scalar_in;

	return *this;
}


CPosition&
CPosition::operator/=(const double& scalar_in)

{
	value_[0] /= scalar_in;
	value_[1] /= scalar_in;

	return *this;
}


double
CPosition::getLength( ) const

{
    return sqrt(
		value_[0] * value_[0]
		+ value_[1] * value_[1]
		);
}


void
CPosition::getNormalized(CPosition& vector_out) const

{
	double length;
	length = getLength();
	if( fabs( length ) < _EPSILON )
		throw;

	vector_out = CPosition( value_[0] / length,value_[1] / length );
}


CPosition
CPosition::getNormalized() const

{
	double length;
	length = getLength();
	if( fabs( length ) < _EPSILON )
		throw;

	return CPosition(
		value_[0] / length,
		value_[1] / length
		);
}


void
CPosition::normalize()

{
	double length;
	length = getLength();

	if( fabs( length ) < _EPSILON )
		throw;

	value_[0] /= length;
	value_[1] /= length;
}


bool
CPosition::isNormalized() const

{
	double length;
	length = getLength();

	if(fabs(length - 1.0) > _EPSILON)
		return false;
	return true;
}


bool
CPosition::isNil() const

{
	double length;
	length = getLength();

	if(fabs(length) > _EPSILON)
		return false;
	return true;
}
