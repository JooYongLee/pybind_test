#include <iostream>

#include <Eigen/Eigen>
#include <Eigen/Core>
//#include <Eigen>
#include <Eigen/Dense>
#include "function_callback.h"

#include "eigen_raw_buffer.h"

#include <fstream>

void test_callback_func();

class Header
{
public:
	Header() = default;
	~Header() = default;
	size_t itemsize = 0;         // Size of individual items in bytes
	size_t size = 0;             // Total number of entries
	//std::string format;           // For homogeneous buffers, this should be set to
								  // format_descriptor<T>::format()
	size_t ndim = 0;
	//std::string format = "none";
	char format[30] = "none";
	size_t shape[5] = { 0, };
	size_t strides[5] = { 0, };
};

std::ostream& operator<<(std::ostream& os, const Header& header)
{
	os << "itemsize:" << header.itemsize << ","
		<< "size" << header.size << ","
		<< "ndim" << header.ndim << ","
		<< "format:" << header.format;
	return os;
}
void shallow_test();
int main(int argc, char* argv[])
{
	std::vector<char> buff;
	std::ifstream file("test.bin", std::ios::binary );
	if (file.is_open())
	{
		// get length of file:
		file.seekg(0, std::ios::end);
		size_t length = file.tellg();
		file.seekg(0, std::ios::beg);
		std::cout << "file size:" << length << "\n";

		buff.resize(length);
		file.read(buff.data(), length);
	}
	float* ptr = (float*)buff.data();

	for (int i = 0; i < (buff.size() / sizeof(float)); i++)
	{
		std::cout << ptr[i] << ",";

	}
	Header h;
	h.itemsize = 1000;
	h.ndim = 5;
	//h.format = "float32aaaaaaa";

	strcpy(h.format, "float32");
	std::cout << h << "\n\n";
	std::ofstream file2("test2.bin", std::ios::binary);
	//file2 << h;
	file2.write((char*)&h, sizeof(h));
	file2.close();


	Header h2;
	std::cout << "is pod:" << std::is_pod<Header>::value;

	std::ifstream file3("test2.bin", std::ios::binary);

	if (file3.is_open())
	{
		// get length of file:
		file3.seekg(0, std::ios::end);
		size_t length = file.tellg();
		file3.seekg(0, std::ios::beg);
		std::cout << "file size:" << length << "\n";
		std::cout << sizeof(h2) << "\n";
		//buff.resize(length);
		file3.read((char*)&h2, sizeof(h2));
	}
	//file2 >> h2;
	//file2.close();

	std::cout << h2 << "\n\n";
	//x *= 2;
	//buffer.print();
	
	//buffer.<Eigen::MatrixXd>print();
	//shallow_test();
	return 0;
}


typedef Eigen::MatrixXf Matrix;

typedef Matrix::Scalar Scalar;

void get_mapping( const Matrix& x, Eigen::Map<Matrix>& y)
{
	y = Eigen::Map<Matrix>(
		(Scalar*)x.data(), x.rows(), x.cols());
}

class Warp
{
public:
	Warp() = default;
	~Warp() = default;
	//void set(const Matrix& x)
	//{
	//	a = Eigen::Map<Matrix>(
	//		(Scalar*)x.data(), x.rows(), x.cols());
	//}
	Eigen::Map<Matrix> a;
	friend std::ostream& operator<<(std::ostream& os, const Warp &r)
	{
		os << "df";
		//os << r.a;
		return os;
	}
};
void shallow_test()
{
	constexpr bool rowMajor = Matrix::Flags & Eigen::RowMajorBit;
	Matrix x = Matrix::Random(3, 2);
	Eigen::MatrixXf xx = Eigen::VectorXf::Random(10).reshaped(5, 2);

	//Eigen::Stride
	//EIGEN_MAJOR_VERSION
	//auto map1 = Eigen::Map<Matrix>(
	//	static_cast<Scalar*>(x.data()), x.rows(), x.cols());

	//Eigen::Map<Matrix> t;
	//Warp w;
	Eigen::Map<Matrix> map1 = Eigen::Map<Matrix>(
		static_cast<Scalar*>(x.data()), x.rows(), x.cols());

	Matrix y = Eigen::Map<Matrix>(
		static_cast<Scalar*>(x.data()), x.rows(), x.cols());
	//w.set(x);

	std::cout << x << "\n\n";
	std::cout << map1 << "\n\n";
	x(0, 0) = 0;

	std::cout << x << "\n\n";
	std::cout << map1 << "\n\n";
	map1(0, 1) = 10;


	std::cout << x << "\n\n";
	std::cout << map1 << "\n\n";

	//Eigen::Map<Matrix, 0> z;

	//get_mapping
	//auto strides = Eigen::Strides(
	//	info.strides[rowMajor ? 0 : 1] / (py::ssize_t)sizeof(Scalar),
	//	info.strides[rowMajor ? 1 : 0] / (py::ssize_t)sizeof(Scalar));

}

void test_callback_func()
{
	using namespace Eigen;

	MatrixXf x = MatrixXf::Random(2, 2);

	CallbackTest t0, t1, tt2;
	t0.run(x);

	CallbackFun fun = [](const MatrixXf& res)->int
	{
		std::cout << "this is  call back result\n" << res << "\n\n";
		return 0;
	};
	t1.set_callback(fun);
	t1.run(x);


}
