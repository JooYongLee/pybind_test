#include "function_callback.h"

void CallbackTest::run(const Eigen::MatrixXf& in)
{
	Eigen::MatrixXf res = in.array() * 10;
	if (this->_callback)
	{
		this->_callback(res);
	}
}

void CallbackTest::set_callback(const CallbackFun& callback)
{
	this->_callback = callback;
}
