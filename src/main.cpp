#include <pybind11/pybind11.h>
#include <iostream>
#include "ekf.h"

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

struct Pet {
    Pet(const std::string &name) : name(name) { }
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }

    std::string name;
};


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
			   .def("process_measurement", &ekf::process_measurement);
}
