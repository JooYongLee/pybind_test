#pragma once

#include <Eigen/Core>
#include <pybind11/buffer_info.h>

template<class Derived>
class MyBuffer
{
public:


	MyBuffer(const Eigen::PlainObjectBase<Derived>& mat);
	MyBuffer() = default;
	~MyBuffer() = default;

	typedef typename Derived::Scalar _Scalar;
	
	Derived* pmat;
	_Scalar *_scalar = nullptr;
	size_t _size = 0;
	void print();
	//Scalar * _pdata;
};


class BufferArray : public bufferinfo
{
public:
	BufferArray()
		: bufferinfo()
	{}

	void create(const std::vector<size_t>& size)
	{

	}


};


