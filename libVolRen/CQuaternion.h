#ifndef CQuaternion_H
#define CQuaternion_H


// includes
#include "CMatrix.h"

class CQuaternion
{
private:
	double value_[4];

public:
	CQuaternion(
		);

	CQuaternion(
		const CQuaternion& quat_in
		);

	CQuaternion(
		const double& a_in,
		const double& b_in,
		const double& c_in,
		const double& d_in
		);

	CQuaternion(
		const CVector &vecAxis_in, 
		const double &dAngle_in
		);

	CQuaternion&
	operator=(
		const CQuaternion& quat_in
		);

	double&
	operator[](
		const unsigned short index_in
		);

	double
	operator[](
		const unsigned short index_in
		) const;

	double&
	operator()(
		const unsigned short index_in
		);

	double
	operator()(
		const unsigned short index_in
		) const;

	void
	set(
		const double& a_in, 
		const double& b_in,
		const double& c_in,
		const double& d_in
		);

	void
	get(
		double& a_out, 
		double& b_out,
		double& c_out,
		double& d_out
		) const;

	void
	getRotation(
		 CVector &axis, 
		 double &dAngle
		) const;

	void 
	setRotation(
		const CVector &vecAxis_in, 
		const double &dAngle_in
		);

	CQuaternion &
	setMatrix4x4(const CMatrix &m);

	bool
	operator==(
		const CQuaternion& vector_in
		) const;

	bool
	operator!=(
		const CQuaternion& vector_in
		) const;

	CQuaternion
	operator-(
		) const;

	friend  CQuaternion
	operator-(
		const CQuaternion& vector0_in,
		const CQuaternion& vector1_in
		);

	friend  CQuaternion
	operator+(
		const CQuaternion& vector0_in,
		const CQuaternion& vector1_in
		);

	friend  CQuaternion
	operator*(
		const CQuaternion& vector0_in,
		const CQuaternion& vector1_in
		);

	friend  CQuaternion
	operator*(
		const double& scalar_in,
		const CQuaternion& quat_in
		);

	friend  CQuaternion
	operator*(
		const CQuaternion& quat_in,
		const double& scalar_in
		);

	friend  CQuaternion
	operator/(
		const CQuaternion& quat_in,
		const double& scalar_in
		);

	friend  double
	dot(
		const CQuaternion& quat0_in,
		const CQuaternion& quat1_in
		);
	
	friend  CQuaternion
	conjugate(
		const CQuaternion& quat_in
		);
	
	friend  CQuaternion
	slerp(
		double weight_in,
		const CQuaternion& quat0_in,
		const CQuaternion& quat1_in
		);

	CQuaternion&
	operator+=(
		const CQuaternion& vector_in
		);

	CQuaternion&
	operator-=(
		const CQuaternion& vector_in
		);

	CQuaternion&
	operator*=(
		const double& scalar_in
		);

	CQuaternion&
	operator/=(
		const double& scalar_in
		);

	double
	getLength(
		) const;

	void
	getNormalized(
		CQuaternion& vector_out
		) const;

	CQuaternion
	getNormalized(
		) const;

	void
	normalize(
		);

	bool
	isNormalized(
		) const;

	bool
	isNil(
		) const;

	CMatrix 
	getMatrix4x4(
	    ) const;

};

#endif // CQuaternion_H
