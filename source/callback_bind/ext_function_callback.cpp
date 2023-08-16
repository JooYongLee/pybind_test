

#include <pybind11/pybind11.h>
#include <pybind11/chrono.h>
#include <pybind11/functional.h>
#include <pybind11/eigen.h>

#include <pybind11/stl.h>
#include <iostream>
#include <string>
#include <Eigen/Core>
namespace py = pybind11;

using namespace pybind11::literals;  // 
#include "function_callback.h"


int argv(CallbackTest &self, const CallbackFun  &fun)
{
	self.set_callback(fun);
	return 0;
}

void function_callback(pybind11::module_ &m) {

	py::class_<CallbackTest>(m, "CallbackTest")
		.def(py::init<>())
		.def("run", &CallbackTest::run, py::arg_v("in", "some input"))
		.def("set_callback", &argv);
};

#ifdef EXT_ALL

//void function_callback(pybind11::module_ &m) {
//
//	py::class_<CallbackTest>(m, "CallbackTest")
//		.def(py::init<>())
//		.def("run", &CallbackTest::run, py::arg_v("in", "some input"))
//		.def("set_callback", &argv);
//};

#else 

PYBIND11_MODULE(mycallback, m) {
	function_callback(m);
}
#endif // 
