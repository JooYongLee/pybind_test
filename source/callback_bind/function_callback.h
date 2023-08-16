#pragma once
#include <functional>
#include <Eigen/Core>
typedef std::function<int(const Eigen::MatrixXf& res)> CallbackFun;
//using CallbackFun = std::function<int(const Eigen::MatrixXf& res)>;
//typedef 
class CallbackTest
{
public:
	CallbackTest() = default;
	~CallbackTest() = default;

	void run(const Eigen::MatrixXf &in);
	void set_callback(const CallbackFun &callback);

	CallbackFun _callback = nullptr;

};
