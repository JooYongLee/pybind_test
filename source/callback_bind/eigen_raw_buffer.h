#pragma once

#include <Eigen/Core>
template<class Derived>
class MyBuffer
{
public:


	MyBuffer(const Eigen::PlainObjectBase<Derived>& mat);
	~MyBuffer() = default;

	typedef typename Derived::Scalar _Scalar;

	Derived* pmat;
	_Scalar *_scalar;
	size_t _size;
	void print();
	//Scalar * _pdata;
};

