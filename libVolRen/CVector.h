#ifndef CVector_H
#define CVector_H

class CVector
{
public:
private:
	double value_[4];

public:
	CVector(
		);

	CVector(
		const CVector& vector_in
		);

	CVector(
		const double& a_in,
		const double& b_in,
		const double& c_in,
		const double& d_in = 1.0
		);

	CVector&
	operator=(
		const CVector& vector_in
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

	bool
	operator==(
		const CVector& vector_in
		) const;

	bool
	operator!=(
		const CVector& vector_in
		) const;

	CVector
	operator-(
		) const;

	friend CVector
	operator-(
		const CVector& vector0_in,
		const CVector& vector1_in
		);

	friend CVector
	operator+(
		const CVector& vector0_in,
		const CVector& vector1_in
		);

	friend double
	operator*(
		const CVector& vector0_in,
		const CVector& vector1_in
		);

	double
	getInnerProduct(
		const CVector& vector_in
		) const;
   
	friend CVector
	operator*(
		const double& scalar_in,
		const CVector& vector_in
		);

	friend CVector
	operator*(
		const CVector& vector_in,
		const double& scalar_in
		);

	friend CVector
	operator/(
		const CVector& vector_in,
		const double& scalar_in
		);

	CVector&
	operator+=(
		const CVector& vector_in
		);

	CVector&
	operator-=(
		const CVector& vector_in
		);

	CVector&
	operator*=(
		const double& scalar_in
		);

	CVector&
	operator/=(
		const double& scalar_in
		);

	double
	getLength(
		) const;
#undef normalize //  HACK
	void
	normalize(
		);

	bool
	isNormalized(
		) const;

	bool
	isNil(
		) const;

};

#endif // CVector_H
