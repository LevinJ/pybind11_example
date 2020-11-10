/*
 * testimage.h
 *
 *  Created on: Nov 10, 2020
 *      Author: levin
 */

#ifndef SRC_TESTIMAGE_H_
#define SRC_TESTIMAGE_H_

#include <pybind11/numpy.h>
namespace py = pybind11;

class testimage {
public:
	testimage();
	void show_image(py::array_t<uint8_t>& img);
	virtual ~testimage();
};

#endif /* SRC_TESTIMAGE_H_ */
