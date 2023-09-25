#include <Eigen/Core>
#include <iostream>
#include "eigen_raw_buffer.h"

template<class Derived>
MyBuffer<Derived>::MyBuffer(const Eigen::PlainObjectBase<Derived>& mat)
{
	//this->pmat = const_cast<Derived*>(&mat);
	this->_scalar = const_cast<_Scalar*>(mat.data());
	this->_size = mat.size();
}

template<class Derived>
void MyBuffer<Derived>::print()
{
	typedef typename Derived::Scalar Scalar;
	if (this->_scalar)
	{
		//Scalar* pdata = this->pmat.data();
		Scalar* pdata = this->_scalar;
		for (size_t i = 0; i < this->_size; i++)
		{
			std::cout << pdata[i] << ", ";
		}
		std::cout << "\n";
	}
}

template<typename Deirved>
void implicit_ex()
{
	Deirved x;
	MyBuffer<Deirved> buffer(x);
	MyBuffer<Deirved> buffer2{};

	buffer.print();
}
void implicit()
{
	implicit_ex<Eigen::MatrixXd>();
	implicit_ex<Eigen::MatrixXf>();
	//Eigen::MatrixXd x;
	//MyBuffer<Eigen::MatrixXd> buffer(x);
	//buffer.print();
}
