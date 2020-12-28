#include <pybind11/pybind11.h>
#include <iostream>
#include "ekf.h"
#include <pybind11/stl.h>
#include <functional>
#include <pybind11/functional.h>
#include "testimage.h"
//#include <eigen3/Eigen/Dense>
//#include <eigen3/Eigen/Geometry>
#include <pybind11/eigen.h>
#include "opencv_bind11.h"

int add(int i, int j) ;
//int add(int i, int j) {
//	std::cout<<"add func is called !!"<<std::endl;
//    return i + j;
//}

//struct Pet {
//    Pet(const std::string &name);
//    void setName(const std::string &name_);
//    const std::string &getName();
//
//    std::string name;
//};

class ComClass{
public:
	std::string name;
	Eigen::Vector3d P_;
	Eigen::Vector3d V_;
	Eigen::Matrix3d R_;
	Eigen::Matrix3d ric_;
	Eigen::Vector3d tic_;
	cv::Mat img1_;
};

std::vector<std::function<void(int)>>g_fs;
//int func_arg(const std::function<int(int)> &f) {
//	g_f = f;
//	return 0;
//}

void func_arg(const std::function<void(int)> &f) {
	g_fs.push_back(f);
    return;
}

void do_it(){
	for(auto & g_f : g_fs){
		g_f(100);
	}

}

std::vector<std::function<void(ComClass)>>g_fs2;

void register_comclasscb(std::function<void(ComClass)> f){
	g_fs2.push_back(f);
}

void do_it2(){
	for(auto & g_f : g_fs2){
		ComClass obj;
		obj.name = "this is fun";
		obj.P_ = {1, 2, 3};
		obj.V_ = {4, 5 ,6};
		obj.ric_ << 10, 20, 30,40,50,60,70,80,90;
		obj.img1_ = cv::imread("/home/levin/raw_data/loop_image/0-262-3pnp_match.jpg");
		g_f(obj);
	}

}


class VOStates{
public:
	void update_states(ComClass & obj){
		if(f1){
			f1(obj);
		}

	}
	void update_states2(ComClass & obj){
		if(f2){
			f2(obj);
		}
	}
	std::function<void(ComClass & obj)> f1;
	std::function<void(ComClass & obj)> f2;
};

std::shared_ptr<VOStates> create_callbacks(std::function<void(ComClass & obj)> f1, std::function<void(ComClass & obj)> f2){
	auto res = std::make_shared<VOStates>();
	if(f1){
		res->f1 = f1;
	}
	if(f2){
		res->f2 = f2;
	}
	return res;
}

void do_callbacks(std::shared_ptr<VOStates> vo){
	ComClass obj;
	obj.name = "this is fun";
	obj.P_ = {1, 2, 3};
	obj.V_ = {4, 5 ,6};
	obj.ric_ << 10, 20, 30,40,50,60,70,80,90;
	obj.img1_ = cv::imread("/home/levin/raw_data/loop_image/0-262-3pnp_match.jpg");

	vo->update_states(obj);
	vo->update_states2(obj);
}

struct Pet {
    Pet(const std::string &name) : name(name) { }
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }

    std::string name;
};

std::shared_ptr<VOMeasurement> create_vomeasurement(float timestamp, const std::vector<float> &data, int seq){
	return std::make_shared<VOMeasurement>(timestamp, data, seq);
}

std::shared_ptr<WheelMeasurement> create_wheelmeasurement(float timestamp, const std::vector<float> &data, int seq){
	return std::make_shared<WheelMeasurement>(timestamp, data, seq);
}

//! 点相加
cv::Point addpt(cv::Point& lhs, cv::Point&rhs){
    return cv::Point(lhs.x + rhs.x, lhs.y + rhs.y);
}


namespace py = pybind11;

PYBIND11_MODULE(example, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: cmake_example

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");
    m.def("addpt", &addpt, "add two point");
    m.def("create_vomeasurement", &create_vomeasurement);
    m.def("create_wheelmeasurement", &create_wheelmeasurement);
    m.def("do_it", &do_it);
    m.def("func_arg", &func_arg);
    m.def("register_comclasscb", &register_comclasscb);
    m.def("do_it2", &do_it2);
    m.def("create_callbacks", &create_callbacks);
    m.def("do_callbacks", &do_callbacks);

    py::class_<VOStates, std::shared_ptr<VOStates>>(m, "VOStates")
               .def(py::init<>());

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

    py::class_<ComClass>(m, "ComClass")
           .def(py::init<>())
		   .def_readwrite("name", &ComClass::name)
		   .def_readwrite("P_", &ComClass::P_)
		   .def_readwrite("V_", &ComClass::V_)
		   .def_readwrite("img1_", &ComClass::img1_)
		   .def_readwrite("ric_", &ComClass::ric_);

    py::class_<Pet>(m, "Pet")
               .def(py::init<const std::string &>())
               .def("setName", &Pet::setName)
               .def("getName", &Pet::getName);
    py::class_<testimage>(m, "testimage")
              .def(py::init<>())
              .def("show_image", &testimage::show_image);

    py::class_<ekf>(m, "ekf")
               .def(py::init<>())
			   .def("process_measurement", &ekf::process_measurement)
			   .def("regiger_state_sub", &ekf::regiger_state_sub);

    py::class_<Measurement, std::shared_ptr<Measurement>>(m, "Measurement")
                   .def(py::init<float , const std::vector<float> &, int >())
				   .def("info", &Measurement::info);

    py::class_<WheelMeasurement, Measurement, std::shared_ptr<WheelMeasurement>>(m, "WheelMeasurement")
                       .def(py::init<float , const std::vector<float> &, int >());

    py::class_<VOMeasurement, Measurement, std::shared_ptr<VOMeasurement>>(m, "VOMeasurement")
                           .def(py::init<float , const std::vector<float> &, int >());

}
