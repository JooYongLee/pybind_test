/*

With pybind11, how to split my code into multiple modules/files?
https://stackoverflow.com/questions/53762552/with-pybind11-how-to-split-my-code-into-multiple-modules-files

official
how can i reduce the build time?
https://pybind11.readthedocs.io/en/stable/faq.html#how-can-i-reduce-the-build-time



*/

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>

// #define EXTENSION_ALL


namespace py = pybind11;

// forward declare
void pybinding_meshSampling(py::module_ &);
//void init_mesh_filter(py::module_ &);
//void init_mesh_image(py::module_ &);

// #include "ext_meshFilter/ext_meshFilter.cpp"
// #include "ext_meshDicom/meshDicom_ext.cpp"


PYBIND11_MODULE(meshlibs, m){
	pybinding_meshSampling(m);
}
