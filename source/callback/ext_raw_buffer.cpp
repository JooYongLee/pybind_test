#include "eigen_raw_buffer.h"

#include <iostream>

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
	py::class_<MyBuffer<Eigen::MatrixXf>>(m, "MyBufferf", py::buffer_protocol())
		.def(py::init<>())
		.def(py::init<const Eigen::MatrixXf&>())
		.def("print", &MyBuffer<Eigen::MatrixXf>::print)
		.def("get_memoryview", [](MyBuffer<Eigen::MatrixXf> &self) {
		return pybind11::memoryview::from_buffer(
			self._scalar, {self._size}, {sizeof(float)}
		);
			})
		.def("buffinfo", [](MyBuffer<Eigen::MatrixXf>& self, const py::buffer &b) {
					
					
				//.def(py::init([](const py::buffer& b) {
					py::buffer_info info = b.request();
					std::cout << info.ptr << "//"
						<< "size:" << info.size << "//"
						<< "format" << info.format << "//"
						<< "itemsize" << info.itemsize << "\n";
					ssize_t length = info.size;

					self._scalar = (Eigen::MatrixXf::Scalar*)info.ptr;// (Eigen::MatrixXf::Scalar*)buffer.ptr();

					self._size = (info.itemsize * info.size )/ sizeof(Eigen::MatrixXf::Scalar);
					//self._size = length;// / sizeof(Eigen::MatrixXf::Scalar);
					//self._size = length / sizeof(Eigen::MatrixXf::Scalar);
					
			})
		.def("frombuffer", [](MyBuffer<Eigen::MatrixXf>& self, py::bytes buffer) {
				//fread()
				//self._scalar = (Eigen::MatrixXf::Scalar*)buffer.ptr();
				py::buffer_info info(py::buffer(buffer).request());

				//py::buffer_info info = py::buffer(buffer).request();
				// https://github.com/pybind/pybind11/issues/2517

				//return { as_unsigned(info.ptr), as_unsigned(info.len) };

				char* cbuf = nullptr;

				//
				////buffer.m_
				//ssize_t length = 0;
				//if (PyBytes_AsStringAndSize((PyObject*)buffer.ptr(), &cbuf, &length) != 0) {
				//	throw  std::runtime_error("Incompatible buffer format!"); 
				//}
				
				self._scalar = (Eigen::MatrixXf::Scalar*)info.ptr;// (Eigen::MatrixXf::Scalar*)buffer.ptr();


				self._size = info.size / sizeof(Eigen::MatrixXf::Scalar);
				//std::cout << "buffer size:" << length << "//" << sizeof(Eigen::MatrixXf::Scalar) << "//" << self._size;
			})
			.def("fromstring", [](MyBuffer<Eigen::MatrixXf>& self, std::string& buffer) {
			//fread()
			//self._scalar = (Eigen::MatrixXf::Scalar*)buffer.ptr();

			char* cbuf = nullptr;


			//buffer.m_
			ssize_t length = buffer.length();
			//if (PyBytes_AsStringAndSize((PyObject*)buffer.ptr(), &cbuf, &length) != 0) {
			//	throw  std::runtime_error("Incompatible buffer format!");
			//}

			self._scalar = (Eigen::MatrixXf::Scalar*)buffer.data();// (Eigen::MatrixXf::Scalar*)buffer.ptr();


			self._size = length / sizeof(Eigen::MatrixXf::Scalar);
			std::cout << "buffer size:" << length << "//" << sizeof(Eigen::MatrixXf::Scalar) << "//" << self._size;
				});
	//m.def("get_memoryview2d", []() {
	//	return py::memoryview::from_buffer(
	//		buffer,                                    // buffer pointer
	//		{ 2, 4 },                                  // shape (rows, cols)
	//		{ sizeof(uint8_t) * 4, sizeof(uint8_t) }   // strides in bytes
	//	);
	//	});


	py::class_<MyBuffer<Eigen::MatrixXd>>(m, "MyBufferx")
		.def(py::init<const Eigen::MatrixXd&>())
		.def("print", &MyBuffer<Eigen::MatrixXd>::print);

};
#else
#endif // 
