#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <iostream>
#include <string>

#include "meshSampling.h"
#include "meshTree.h"


namespace py = pybind11;

using namespace meshlibs;

bool debug_print = false;
template<typename Derived>
void print(Eigen::PlainObjectBase<Derived> &v, const std::string &name="")
{
    if(debug_print)
    {
        std::cout << name << ":" << v.rows() << "x" << v.cols() << "\n";
    }
}

class UniformSample
{
public:
	UniformSample()
	{}

	~UniformSample()
	{
	}

	bool setInput(const MatrixXfr& vin, const MatrixXlr& fin, int number)
	{
		this->_number = number;
		this->_vin = vin;
		this->_fin = fin;
		return true;
	}

	void update()
	{
	    std::vector<int> sample_inds;
		_vin_s = point_uniform_sampling_by_area(this->_vin, this->_fin, this->_number, &sample_inds, &this->_sample_coords);
		_sample_f_inds = Eigen::Map<VectorXi>(sample_inds.data(), sample_inds.size()).cast<long long>();
		print(this->_vin_s, "_vin_s");
//		std::cout << "update complete:" << this->_vin_s
	}

	void getOutput(MatrixXfr& v, VectorXl &inds, MatrixXfr &coords)
	{
	    print(this->_vin_s, "_vin_s");
		v = this->_vin_s;
		inds = this->_sample_f_inds;
		coords = this->_sample_coords;
		print(v, "output-v");
	}


    // input
	MatrixXfr _vin;
	MatrixXlr _fin;
	int _number;

    // output
	MatrixXfr _vin_s;
	VectorXl _sample_f_inds;
	MatrixXfr _sample_coords;
};

class AnchorGenerator
{
public:
	AnchorGenerator() = default;
	~AnchorGenerator() = default;

	bool setInput(const MatrixXfr& vin, const MatrixXlr& fin, const MatrixXfr& normal, int number)
	{
		this->_number = number;
		this->_vin = vin;
		this->_fin = fin;
		this->_normal = normal;

		//_tree.fit(this->_vin);
		return true;
	}

	bool update(const MatrixXfr &query, const VectorXi &sample_inds)
	{
//	    meshlibs::ExKdTree<meshlibs::PosePoints<float, 3>> _tree;
	    ExKdTree<PosePoints<float, 3>> kdtree;
//	    ExKdTree<std::array<float, 3>> _tree;
//	    ExKdTree<std::array<float, 3>> _tree;
	    kdtree.fit(this->_vin);

	    sampling_center(query, this->_vin, this->_normal, sample_inds, kdtree, this->_anchors, true, this->_fradius, this->_fangle);
	    return true;
	}

	bool getOutput(MatrixXfr &anchors)
	{
	    anchors = this->_anchors;
	    return true;
	}



    // parameters
    float _fradius = 5.0f;
    float _fangle = 80.0f;
    // input
	MatrixXfr _vin;
	MatrixXlr _fin;
	MatrixXfr _normal;
	int _number;

    // output
    MatrixXfr _anchors;

};

class GraphEdge
{
public:
    GraphEdge() = default;
    ~GraphEdge() = default;

    bool build(const MatrixXlr &f0)
    {
		bool res = true;
        if( f0.cols() == 3)
        {
            graph_edge_igl(f0, this->edge, this->edge_verts);
        }
        else if( f0.cols() == 4) // vtk 로 가정
        {
            MatrixXlr f00 = f0(Eigen::all, Eigen::seqN(1, 3));
            graph_edge_igl(f00, this->edge, this->edge_verts);			
        }
		else
		{
			res = false;
		}
		return res;
    }

    MatrixXlr edge;
	MatrixXlr edge_verts;

};


#ifdef EXTENSION_ALL

    // output
//	MatrixXfr _vin_s;
//	VectorXl _sample_f_inds;
//	MatrixXfr _sample_coords;
void pybinding_meshSampling(py::module_ &m)
{
    py::class_<UniformSample>(m, "UniformSample")
	.def(py::init<>())
	.def("setInput", &UniformSample::setInput, py::arg_v("vin", "vertices"), py::arg_v("fin", "face"), py::arg_v("number", "number-sample"))
	.def("update", &UniformSample::update)
	.def("getOutput", &UniformSample::getOutput)
	.def_readonly("v_sample", &UniformSample::_vin_s)
	.def_readonly("f_sample_args", &UniformSample::_sample_f_inds)
	.def_readonly("sample_coords", &UniformSample::_sample_coords)
	;

    py::class_<AnchorGenerator>(m, "AnchorGenerator")
	.def(py::init<>())
	.def("setInput", &AnchorGenerator::setInput,
	            py::arg_v("vin", "source vertices"),
	            py::arg_v("fin", "faces, may be not used"),
	            py::arg_v("normal", "normals of vertices"),
	            py::arg_v("number", "the number of sampling"))
	.def("update", &AnchorGenerator::update)
	.def("getOutput", &AnchorGenerator::getOutput)
	.def_readwrite("radius", &AnchorGenerator::_fradius, "radius to refer")
	.def_readwrite("angle", &AnchorGenerator::_fangle, "Only data within a certain angle is reflected")
    .def_readonly("anchors", &AnchorGenerator::_anchors, "the result of anchors")
	;

	py::class_<GraphEdge>(m, "GraphEdge")
	.def(py::init<>())
	.def("build", &GraphEdge::build,
	    py::arg_v("f0", "faces(3 or 4(vtk))"))
	.def_readonly("edge", &GraphEdge::edge, "the result of edge-topology(faces)")
	.def_readonly("edge_verts", &GraphEdge::edge_verts, "the result of edge-topology(verts)");

}

#else // EXTENSION_ALL

//py::class_<RegionGrow>(m, "RegionGrow")
//.def(py::init<>())
//.def("setInput", &RegionGrow::setInput)
//.def("update", &RegionGrow::update)
//.def("getOutputImage", &RegionGrow::getOutputImage)
//.def("getNumSegment", &RegionGrow::getNumSegment)
//.def("getAreas", &RegionGrow::getAreas)
//;

#endif //


