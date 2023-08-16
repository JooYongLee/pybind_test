#include <pybind11/pybind11.h>

#ifdef EXT_ALL

void eigen_raw_buffer(pybind11::module_&);
void function_callback(pybind11::module_& );


PYBIND11_MODULE(mycallback, m)
{
	m.doc() = "mycallback binding";
	eigen_raw_buffer(m);
	function_callback(m);

}
#else
#endif // 
