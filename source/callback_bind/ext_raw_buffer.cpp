#include "eigen_raw_buffer.h"


#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
namespace py = pybind11;

#ifdef EXT_ALL

//template<typename Deirved>
void eigen_raw_buffer(pybind11::module_& m)
{

	//py::class_<MyBuffer<Eigen::MatrixXf>>(m, "MyBuffer")
	//	.def(py::init<const Eigen::MatrixXf&>())
	//	.def("print", &MyBuffer<Eigen::MatrixXf>::print)
	//	.def(py::init<const Eigen::MatrixXd&>())
	//	.def("print", &MyBuffer<Eigen::MatrixXd>::print);
//
	py::class_<MyBuffer<Eigen::MatrixXf>>(m, "MyBufferf")
		.def(py::init<const Eigen::MatrixXf&>())
		.def("print", &MyBuffer<Eigen::MatrixXf>::print);

	py::class_<MyBuffer<Eigen::MatrixXd>>(m, "MyBufferx")
		.def(py::init<const Eigen::MatrixXd&>())
		.def("print", &MyBuffer<Eigen::MatrixXd>::print);

};
#else
#endif // 
