#include <pybind11/pybind11.h>
#include <iostream>
#include "ekf.h"
#include <pybind11/stl.h>
//#include <functional>
#include <pybind11/functional.h>

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
    m.def("create_vomeasurement", &create_vomeasurement);
    m.def("create_wheelmeasurement", &create_wheelmeasurement);
    m.def("do_it", &do_it);
    m.def("func_arg", &func_arg);

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

    py::class_<Pet>(m, "Pet")
           .def(py::init<const std::string &>())
           .def("setName", &Pet::setName)
           .def("getName", &Pet::getName);
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
