#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "CQuaternion.h"
#include "CVector.h"

#define _EPSILON (0.0001)

CQuaternion::CQuaternion(
	)
{
	value_[0] = 0.0;
	value_[1] = 0.0;
	value_[2] = 0.0;
	value_[3] = 1.0;
}

CQuaternion::CQuaternion(
	const CQuaternion& quat_in
	)
{
	value_[0] = quat_in.value_[0];
	value_[1] = quat_in.value_[1];
	value_[2] = quat_in.value_[2];
	value_[3] = quat_in.value_[3];
}

CQuaternion::CQuaternion(
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


CQuaternion::CQuaternion(
		const CVector &vecAxis_in, 
		const double &dAngle_in
		)
{
	
	double dLength = vecAxis_in.getLength();
	
    if (dLength > _EPSILON) {
		
		double dScale = sin(0.5 * dAngle_in) / dLength;
		
		value_[0] = vecAxis_in[0]  * dScale;
		value_[1] = vecAxis_in[1] * dScale;
		value_[2] = vecAxis_in[2] * dScale;
		value_[3] = cos(0.5 * dAngle_in);
    }
    else {
		value_[0] = 0.0;
		value_[1] = 0.0;
		value_[2] = 0.0;
		value_[3] = 1.0;
    }
}

CQuaternion&
CQuaternion::operator=(
	const CQuaternion& quat_in
	)
{
	if(&quat_in != this)
	{
		value_[0] = quat_in.value_[0];
		value_[1] = quat_in.value_[1];
		value_[2] = quat_in.value_[2];
		value_[3] = quat_in.value_[3];
	}

	return *this;
}

double&
CQuaternion::operator[](
	const unsigned short index_in
	)
{
	if(index_in > 3)
		throw;

	return value_[index_in];
}

double
CQuaternion::operator[](
	const unsigned short index_in
	) const
{
	if(index_in > 3)
		throw;

	return value_[index_in];
}

double&
CQuaternion::operator()(
	const unsigned short index_in
	)
{
	if(index_in > 3)
		throw;

	return value_[index_in];
}

double
CQuaternion::operator()(
	const unsigned short index_in
	) const
{
	if(index_in > 3)
		throw;

	return value_[index_in];
}

void
CQuaternion::set(
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
CQuaternion::get(
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
CQuaternion::operator==(
	const CQuaternion& quat_in
	) const
{
	if( (fabs(value_[0] - quat_in.value_[0]) > _EPSILON)
		|| (fabs(value_[1] - quat_in.value_[1]) > _EPSILON)
		|| (fabs(value_[2] - quat_in.value_[2]) > _EPSILON)
		|| (fabs(value_[3] - quat_in.value_[3]) > _EPSILON) )
		return false;
	return true;
}

bool
CQuaternion::operator!=(
	const CQuaternion& quat_in
	) const
{
	return( !(*this == quat_in) );
}

CQuaternion
CQuaternion::operator-(
	) const
{
	return CQuaternion(
		-value_[0],
		-value_[1],
		-value_[2],
		-value_[3]
		);
}

CQuaternion
operator-(
	const CQuaternion& quat0_in,
	const CQuaternion& quat1_in
	)
{
	return CQuaternion(
		quat0_in.value_[0] - quat1_in.value_[0],
		quat0_in.value_[1] - quat1_in.value_[1],
		quat0_in.value_[2] - quat1_in.value_[2],
		quat0_in.value_[3] - quat1_in.value_[3]
		);
}

CQuaternion
operator+(
	const CQuaternion& quat0_in,
	const CQuaternion& quat1_in
	)
{
	return CQuaternion(
		quat0_in.value_[0] + quat1_in.value_[0],
		quat0_in.value_[1] + quat1_in.value_[1],
		quat0_in.value_[2] + quat1_in.value_[2],
		quat0_in.value_[3] + quat1_in.value_[3]
		);
}

CQuaternion
operator*(
	const CQuaternion& quatL_in,
	const CQuaternion& quatR_in
	)
{
	return CQuaternion(		
		quatL_in.value_[3] * quatR_in.value_[0] + quatL_in.value_[0] * quatR_in.value_[3] + quatL_in.value_[1] * quatR_in.value_[2]- quatL_in.value_[2] * quatR_in.value_[1],
		quatL_in.value_[3] * quatR_in.value_[1] + quatL_in.value_[1] * quatR_in.value_[3] + quatL_in.value_[2] * quatR_in.value_[0]- quatL_in.value_[0] * quatR_in.value_[2],		
		quatL_in.value_[3] * quatR_in.value_[2] + quatL_in.value_[2] * quatR_in.value_[3] + quatL_in.value_[0] * quatR_in.value_[1]- quatL_in.value_[1] * quatR_in.value_[0],
		
		quatL_in.value_[3] * quatR_in.value_[3] - quatL_in.value_[0] * quatR_in.value_[0] - quatL_in.value_[1] * quatR_in.value_[1]- quatL_in.value_[2] * quatR_in.value_[2]);
}

double
dot(
	const CQuaternion& vector0_in,
	const CQuaternion& vector1_in
	)
{
	return (vector0_in.value_[0] * vector1_in.value_[0] + 
			vector0_in.value_[1] * vector1_in.value_[1] + 
			vector0_in.value_[2] * vector1_in.value_[2] + 
			vector0_in.value_[3] * vector1_in.value_[3]);
}

CQuaternion
conjugate(
	const CQuaternion& quat_in
    )
{
	return CQuaternion(
		-quat_in.value_[0],
		-quat_in.value_[1],
		-quat_in.value_[2],
		quat_in.value_[3]
	);
}


CQuaternion
slerp(
	double weight_in,
	const CQuaternion& quatFrom_in,
	const CQuaternion& quatTo_in
	)
{
	// calc cosine omega
	double cosom = dot( quatFrom_in, quatTo_in );
	
	// adjust signs (if necessary)
	CQuaternion quatTo;
	if (cosom < 0.0)
	{
		cosom = -cosom;
		quatTo.value_[0] = -quatTo_in.value_[0];   // Reverse all signs
		quatTo.value_[1] = -quatTo_in.value_[1];
		quatTo.value_[2] = -quatTo_in.value_[2];
		quatTo.value_[3] = -quatTo_in.value_[3];
	}
	else
	{
		quatTo = quatTo_in;
	}
	
	// Calculate coefficients
	double sclp, sclq;
	if ((1.0 - cosom) > _EPSILON) 
	{
		// Standard case (slerp)
		double omega, sinom;
		omega = acos( cosom ); // extract theta from dot product's cos theta
		sinom = sin( omega );
		sclp  = sin( (1.0 - weight_in) * omega ) / sinom;
		sclq  = sin( weight_in * omega ) / sinom;
	}
	else
	{
		// Very close, do linear interp (because it's faster)
		sclp = 1.0 - weight_in;
		sclq = weight_in;
	}
	
	return CQuaternion(sclp * quatFrom_in.value_[0] + sclq * quatTo.value_[0], 
			            sclp * quatFrom_in.value_[1] + sclq * quatTo.value_[1], 
		                sclp * quatFrom_in.value_[2] + sclq * quatTo.value_[2],
		                sclp * quatFrom_in.value_[3] + sclq * quatTo.value_[3]);
}  


CQuaternion
operator*(
	const double& scalar_in,
	const CQuaternion& vector_in
	)
{
	return CQuaternion(
		scalar_in * vector_in.value_[0],
		scalar_in * vector_in.value_[1],
		scalar_in * vector_in.value_[2],
		scalar_in * vector_in.value_[3]
		);
}

CQuaternion
operator*(
	const CQuaternion& vector_in,
	const double& scalar_in
	)
{
	return CQuaternion(
		vector_in.value_[0] * scalar_in,
		vector_in.value_[1] * scalar_in,
		vector_in.value_[2] * scalar_in,
		vector_in.value_[3] * scalar_in
		);
}

CQuaternion
operator/(
	const CQuaternion& vector_in,
	const double& scalar_in
	)
{
	return CQuaternion(
		vector_in.value_[0] / scalar_in,
		vector_in.value_[1] / scalar_in,
		vector_in.value_[2] / scalar_in,
		vector_in.value_[3] / scalar_in
		);
}

CQuaternion&
CQuaternion::operator+=(
	const CQuaternion& quat_in
	)
{
	value_[0] += quat_in.value_[0];
	value_[1] += quat_in.value_[1];
	value_[2] += quat_in.value_[2];
	value_[3] += quat_in.value_[3];

	return *this;
}

CQuaternion&
CQuaternion::operator-=(
	const CQuaternion& quat_in
	)
{
	value_[0] -= quat_in.value_[0];
	value_[1] -= quat_in.value_[1];
	value_[2] -= quat_in.value_[2];
	value_[3] -= quat_in.value_[3];

	return *this;
}

CQuaternion&
CQuaternion::operator*=(
	const double& scalar_in
	)
{
	value_[0] *= scalar_in;
	value_[1] *= scalar_in;
	value_[2] *= scalar_in;
	value_[3] *= scalar_in;

	return *this;
}

CQuaternion&
CQuaternion::operator/=(
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
CQuaternion::getLength(
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
CQuaternion::getRotation(CVector &vecAxis_out, double &dAngle_out) const
{
    double dLength;

	CVector vecTmp(value_[0],value_[1],value_[2],1.0);

    if ((dLength = vecTmp.getLength()) > _EPSILON) {
		vecAxis_out	 = vecTmp / dLength;
		dAngle_out	 = 2.0 * acos(value_[3]);
    }
    else {
		vecAxis_out.set(0.0, 0.0, 1.0,1.0);
		dAngle_out = 0.0;
    }
}

void 
CQuaternion::setRotation(const CVector &vecAxis_in, const double &dAngle_in)
{
	CVector axis = vecAxis_in;
	axis[3] = 0.0;	

	double dLength = axis.getLength();
	
    if (dLength > _EPSILON) {
		
		double dScale = sin(0.5 * dAngle_in) / dLength;
		
		value_[0] = axis[0]  * dScale;
		value_[1] = axis[1] * dScale;
		value_[2] = axis[2] * dScale;
		value_[3] = cos(0.5 * dAngle_in);
    }
    else {
		value_[0] = 0.0;
		value_[1] = 0.0;
		value_[2] = 0.0;
		value_[3] = 1.0;
    }
	
}

void
CQuaternion::getNormalized(
	CQuaternion& vector_out
	) const
{
	double length;
	length = getLength();

	if( fabs( length ) < _EPSILON )
		throw;

	vector_out = CQuaternion(
		value_[0] / length,
		value_[1] / length,
		value_[2] / length,
		value_[3] / length
		);
}

CQuaternion
CQuaternion::getNormalized(
	) const
{
	double length;
	length = getLength();

	if( fabs( length ) < _EPSILON )
		throw;

	return CQuaternion(
		value_[0] / length,
		value_[1] / length,
		value_[2] / length,
		value_[3] / length
		);
}

void
CQuaternion::normalize(
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
CQuaternion::isNormalized(
	) const
{
	double length;
	length = getLength();

	if(fabs(length - 1.0) > _EPSILON)
		return false;
	return true;
}

bool
CQuaternion::isNil(
	) const
{
	double length;
	length = getLength();

	if(fabs(length) > _EPSILON)
		return false;
	return true;
}

CMatrix
CQuaternion::getMatrix4x4() const
{


    double dLength = getLength();
    double s = (dLength > 0.0) ? (2.0 / dLength) : 0.0;
    double xs = value_[0]*s,	      ys = value_[1]*s,	  zs = value_[2]*s;
    double wx = value_[3]*xs,	      wy = value_[3]*ys,	  wz = value_[3]*zs;
    double xx = value_[0]*xs,	      xy = value_[0]*ys,	  xz = value_[0]*zs;
    double yy = value_[1]*ys,	      yz = value_[1]*zs,	  zz = value_[2]*zs;

	/*return GtMatrix4x4(1.0 - (yy + zz),  //00
					   xy + wz,          //10
					   xz - wy,          //20
					   0.0,              //30
		               xy - wz,          //01
					   1.0 - (xx + zz),  //11
					   yz + wx,          //21
					   0.0,              //31
					   xz + wy,          //02
					   yz - wx,          //12
					   1.0 - (xx + yy),  //22
					   0.0,              //32
					   0.0,              //03
					   0.0,              //13
					   0.0,              //23
					   1.0);             //33
	*/
	return CMatrix(1.0 - (yy + zz),  //00
		               xy - wz,          //01
					   xz + wy,          //02
					   0.0,              //03

					   xy + wz,          //10
					   1.0 - (xx + zz),  //11
					   yz - wx,          //12
					   0.0,              //13

					   xz - wy,          //20
					   yz + wx,          //21
					   1.0 - (xx + yy),  //22
					   0.0,              //23

					   0.0,              //30
					   0.0,              //31
					   0.0,              //32
					   1.0);             //33
}






CQuaternion &
CQuaternion::setMatrix4x4(const CMatrix &m)
//
////////////////////////////////////////////////////////////////////////
{
    int i, j, k;

    // First, find largest diagonal in matrix:
    if (m(0,0) > m(1,1)) {
	if (m(0,0) > m(2,2)) {
	    i = 0;
	}
	else i = 2;
    }
    else {
	if (m(1,1) > m(2,2)) {
	    i = 1;
	}
	else i = 2;
    }
    if (m(0,0)+m(1,1)+m(2,2) > m(i,i)) {
	// Compute w first:
	value_[3] = sqrt(m(0,0)+m(1,1)+m(2,2)+m(3,3))/2.0;

	// And compute other values:
	//value_[0] = (m(1,2)-m(2,1))/(4*value_[3]);
	//value_[1] = (m(2,0)-m(0,2))/(4*value_[3]);
	//value_[2] = (m(0,1)-m(1,0))/(4*value_[3]);
	// And compute other values:
	value_[0] = (m(2,1)-m(1,2))/(4*value_[3]);
	value_[1] = (m(0,2)-m(2,0))/(4*value_[3]);
	value_[2] = (m(1,0)-m(0,1))/(4*value_[3]);
    }
    else {
	// Compute x, y, or z first:
	//j = (i+1)%3; k = (i+2)%3;
	j = (i+2)%3; k = (i+1)%3;
    
	// Compute first value:
	value_[i] = sqrt(m(i,i)-m(j,j)-m(k,k)+m(3,3))/2.0;
       
	// And the others:
	//value_[j] = (m(j,i)+m(i,j))/(4*value_[i]);
	//value_[k] = (m(k,i)+m(i,k))/(4*value_[i]);
	//value_[3] = (m(k,j)-m(j,k))/(4*value_[i]);
	
	// And the others:
	value_[j] = (m(i,j)+m(j,i))/(4*value_[i]);
	value_[k] = (m(i,k)+m(k,i))/(4*value_[i]);
	value_[3] = (m(j,k)-m(k,j))/(4*value_[i]);
    }

#ifdef _DEBUG
    // Check to be sure output matches input:
    CMatrix check =  getMatrix4x4();
    bool ok = true;
    for (i = 0; i < 4 && ok; i++) {
		for (j = 0; j < 4 && ok; j++) {
			if (fabs(m(i,j)-check(i,j)) > _EPSILON)
				ok = false;
		}
    }
	assert(ok);
#endif

    return (*this);
}

